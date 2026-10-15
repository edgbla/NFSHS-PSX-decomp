#!/usr/bin/env python3
"""configure.py -- write build.ninja: the Ninja build of NFS4.EXE and FRONT.BIN (Route A, natural link).

    python3 configure.py            # once; build.ninja then regenerates itself (see below)
    ninja                           # = ninja disc: compile what changed, link, cut NFS4.EXE + FRONT.BIN
    ninja -j8                       # parallel jobs (default: number of CPUs + 2)

Targets:
    disc        (default) build/full_link/disc/NFS4.EXE and FRONT.BIN (+ build/full_link/nfs4.exe)
    link        build/full_link/full.elf (+ full.map)
    objects     every object the link uses (recon TUs, asm/header.s)
    split       the splat split objects src/**.c (-DSKIP_ASM, objdiff's base objects; not linked)
    expected    every TU without -DSKIP_ASM into expected/ (objdiff's target objects; what CI builds)
    all         disc + split
    sizes       print the linked section sizes next to retail (tools/full_link.py --report)

Every TU is two Ninja edges, with the TU's own parameters taken from tools/build.py (PER_TU_FLAGS, the compiler
lanes, the per-function splice tables):

    <obj>.i            cpp   the preprocessor command (header dependencies through cpp -MD)
    <obj>.o (+ .s)     cc    tools/tu_step.py -- <cc1 / cc1plus of the TU's lane, all its flags>
                                              -- <maspsx + GNU as, or GNU as alone>   (.include dependencies)

`ninja -t commands build/recon/game/common/ai.cpp.o` prints the exact commands of one object.  Ninja rebuilds an
edge when its inputs change or when its command line changes, so editing a TU's PER_TU_FLAGS entry rebuilds exactly
that TU.  TUs with per-function splice tables also carry a hash of their table entries (--sig), for the same reason.
What is *not* tracked per TU is build.py's compile logic itself (run_s / run_o code): after changing that, rebuild
everything with `ninja -t clean && ninja`.  Changes to tu_step.py, toolchain.py, maspsx or the compilers rebuild
every object automatically.

build.ninja regenerates itself when configure.py, tools/build.py or tools/toolchain.py change, when a source file is
added to or removed from recon/ or src/, and when the toolchain directory changes (the directories are listed in
build.ninja.d, a depfile, so a directory that disappears just triggers regeneration).  Re-run configure.py by hand
after changing NFS4_* environment variables (they are read when build.ninja is written).

options:
    --strict-link    unlisted object sections are a link error (gen_natural_ld.py --strict)
"""
import argparse
import hashlib
import os
import shlex
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT / "tools"))
import toolchain as tc  # noqa: E402
import build as b  # noqa: E402
import full_link  # noqa: E402

NINJA_FILE = ROOT / "build.ninja"
NINJA_DEPFILE = ROOT / "build.ninja.d"      # the directories build.ninja is regenerated on
IS_WINDOWS = os.name == "nt"
ROOT_S = str(ROOT)


# ---------------------------------------------------------------------------------------------------- ninja syntax
def esc_path(p) -> str:
    """A path in a build/default statement: repository-relative when inside ROOT, `$ `, `$:` and `$$` escaped."""
    p = Path(p)
    try:
        s = p.resolve().relative_to(ROOT).as_posix() if p.is_absolute() else p.as_posix()
    except ValueError:
        s = p.as_posix()
    return s.replace("$", "$$").replace(" ", "$ ").replace(":", "$:")


def _quote(arg) -> str:
    s = str(arg)
    return subprocess.list2cmdline([s]) if IS_WINDOWS else shlex.quote(s)


def cmdline(args) -> str:
    """argv -> one command-line string for a Ninja variable; the repository root is written as $root."""
    root_esc = ROOT_S.replace("$", "$$")
    return " ".join(_quote(a).replace("$", "$$").replace(root_esc, "$root") for a in args)


class Writer:
    def __init__(self):
        self.lines = []

    def comment(self, text=""):
        for ln in text.splitlines() or [""]:
            self.lines.append(("# " + ln).rstrip())

    def newline(self):
        self.lines.append("")

    def variable(self, name, value, indent=0):
        self.lines.append("  " * indent + f"{name} = {value}")

    def rule(self, name, **kv):
        self.lines.append(f"rule {name}")
        for k, v in kv.items():
            self.variable(k, v, 1)
        self.newline()

    def build(self, outputs, rule, inputs=(), implicit=(), implicit_outputs=(), order_only=(), variables=None):
        s = "build " + " ".join(esc_path(o) for o in outputs)
        if implicit_outputs:
            s += " | " + " ".join(esc_path(o) for o in implicit_outputs)
        s += f": {rule}"
        if inputs:
            s += " " + " ".join(esc_path(i) for i in inputs)
        if implicit:
            s += " | " + " ".join(esc_path(i) for i in implicit)
        if order_only:
            s += " || " + " ".join(esc_path(i) for i in order_only)
        self.lines.append(s)
        for k, v in (variables or {}).items():
            self.variable(k, v, 1)

    def default(self, targets):
        self.lines.append("default " + " ".join(esc_path(t) for t in targets))

    def text(self):
        return "\n".join(self.lines) + "\n"


# ---------------------------------------------------------------------------------------------------- the TU list
def main_tus():
    """(src TUs, recon TUs) exactly as build.py's full build compiles them."""
    srcs = sorted((ROOT / "src").rglob("*.c"))
    recon = [p for p in sorted(b.RECON.rglob("*.cpp")) if b.is_main_recon(p)]
    recon += [p for p in sorted(b.RECON.rglob("*.c")) if b.is_tu(p) and b.is_main_recon(p)]
    return srcs, recon


def _splice_tables():
    """build.py's per-function tables (dicts keyed by TU path), PER_TU_FLAGS excluded -- their TUs also depend on
    build.py because the splice code reads the table at build time."""
    return [v for k, v in vars(b).items()
            if k.startswith("PER_FN_") and isinstance(v, dict)]


def uses_splice(rel: str, tables) -> bool:
    return any(t.get(rel) for t in tables)


def _canon(v):
    """Deterministic form of a table value (sets/dicts sorted: repr(set of str) varies with PYTHONHASHSEED)."""
    if isinstance(v, dict):
        return sorted((str(k), _canon(x)) for k, x in v.items())
    if isinstance(v, (set, frozenset)):
        return sorted(repr(_canon(x)) for x in v)
    if isinstance(v, (list, tuple)):
        return [_canon(x) for x in v]
    return str(v) if isinstance(v, Path) else v


def splice_sig(rel: str, tables) -> str:
    """A short hash of everything build.py reads *at build time* for this TU: its entries in the PER_FN_* tables
    plus the cc1 rung maps the splices pick compilers from.  It goes on the TU's command line (tu_step ignores it),
    so Ninja rebuilds exactly the TUs whose table data changed -- not every splice TU on any build.py edit."""
    data = repr([_canon(t.get(rel)) for t in tables])
    data += repr(_canon({**b.CC1_SPECIAL_RUNGS, **b.CC1PLUS_RUNGS}))
    return hashlib.sha1(data.encode()).hexdigest()[:12]


# ---------------------------------------------------------------------------------------------------- writing
def write_tu(w: Writer, plan: dict, out_name: str, tables, deps, tag=""):
    """Two edges: <obj>.i (cpp, header deps via -MD) and <obj>.o (+ <obj>.s) through tools/tu_step.py."""
    rel = plan["rel"]
    i_file, s_file, obj = plan["i"], plan["s"], plan["obj"]
    w.build([i_file], "cpp", [ROOT / rel], variables={"cmd": cmdline(plan["cpp"]), "desc": f"CPP {tag}{rel}"})

    obj_rel = Path(obj).relative_to(ROOT).as_posix()
    opts = ["--lane", plan["lane"], "--src", rel]
    if plan["native"]:
        opts.append("--native")
    if not plan["ver_splice"]:
        opts.append("--no-ver-splice")
    if plan["raw40"]:
        opts += ["--raw40", out_name]
    elif plan["asm_stdin"]:
        opts.append("--stdin")
    if uses_splice(rel, tables):
        opts += ["--sig", splice_sig(rel, tables)]
    opts += ["--depfile", obj_rel + ".d", "--dep-target", obj_rel]      # = the rule's $out.d / $out
    cmd = "$python tools/tu_step.py " + cmdline(opts) + " -- " + cmdline(plan["cc1"])
    if not plan["raw40"]:
        cmd += " -- " + cmdline(plan["asm"])
    cc1_bin = Path(str(plan["cc1"][0]))
    w.build([obj], "cc", [i_file], implicit=[cc1_bin, *deps], implicit_outputs=[s_file],
            variables={"cmd": cmd, "desc": f"CC  {tag}{rel}  [{plan['lane']}: {cc1_bin.parent.name}/{cc1_bin.name}]"})


def configure(args):
    tables = _splice_tables()
    srcs, recon = main_tus()
    # what every compile edge runs besides its own compiler: the assembler, maspsx, the step scripts
    deps = [Path(str(b.AS)), Path(str(b.MASPSX)), ROOT / "tools" / "maspsx" / "maspsx" / "__init__.py",
            ROOT / "tools" / "fix_symsizes.py", ROOT / "tools" / "tu_step.py", ROOT / "tools" / "toolchain.py"]
    deps = [p for p in deps if p.is_file()]

    w = Writer()
    w.comment("GENERATED by configure.py -- do not edit; re-run `python3 configure.py` (or just `ninja`).")
    w.comment(f"host: {sys.platform}; cc1 {b.CC1}; cc1plus {b.CC1PL}; as {b.AS}")
    env = {k: v for k, v in sorted(os.environ.items()) if k.startswith("NFS4_")}
    w.comment("NFS4_* environment at configure time: " + (", ".join(f"{k}={v}" for k, v in env.items()) or "none"))
    w.newline()
    w.variable("ninja_required_version", "1.10")
    w.variable("builddir", "build")              # .ninja_log / .ninja_deps live in build/
    w.variable("root", ROOT_S.replace("$", "$$"))
    w.variable("python", cmdline([sys.executable]))
    w.newline()

    w.rule("cpp", command="$cmd -MD -MF $out.d -MT $out", depfile="$out.d", deps="gcc", description="$desc")
    w.rule("cc", command="$cmd", depfile="$out.d", deps="gcc", description="$desc")
    w.rule("as_s", command="$cmd", description="AS  $in")
    w.rule("gen_ld", command="$python tools/gen_natural_ld.py --out $ldscript --rsp $rsp $strict",
           description="GEN $ldscript (linkers/link_order.txt)", restat="1")
    w.rule("ld", command="$cmd", description="LD  $out")
    w.rule("exe", command="$python tools/elf_to_exe.py --split", description="EXE $in -> NFS4.EXE + FRONT.BIN")
    w.rule("report", command="$python tools/full_link.py --report", description="sizes of $in", pool="console")
    w.rule("configure", command="$python configure.py $configure_args", generator="1", depfile="build.ninja.d",
           description="CONFIGURE build.ninja")

    # ---- objects: build/ (-DSKIP_ASM; linked) and expected/ (objdiff targets, as CI builds them)
    variants = [("build", True, ""), ("expected", False, "[expected] ")]
    objs = {}
    for out_name, skip_asm, tag in variants:
        out = ROOT / out_name
        w.newline()
        w.comment(f"---- {out_name}/  ({'-DSKIP_ASM' if skip_asm else 'INCLUDE_ASM bodies assembled'})")
        hdr = out / "asm" / "header.s.o"
        w.build([hdr], "as_s", [ROOT / "asm" / "header.s"], implicit=deps[:1],
                variables={"cmd": cmdline([b.AS, *b.AS_ARCH, "-G0", "-I", ROOT / "include", "-I", ROOT,
                                           ROOT / "asm" / "header.s", "-o", hdr])})
        o_src, o_recon = [], []
        for group, lst in (("src", srcs), ("recon", recon)):
            for src in lst:
                plan = b.plan_tu(src, skip_asm, out)
                write_tu(w, plan, out_name, tables, deps, tag)
                (o_src if group == "src" else o_recon).append(plan["obj"])
        objs[out_name] = (hdr, o_src, o_recon)

    # ---- the natural link
    hdr, o_src, o_recon = objs["build"]
    fl = ROOT / "build" / "full_link"
    ldscript, rsp = fl / "nfs4_natural.ld", fl / "objects.rsp"
    elf, mapf = fl / "full.elf", fl / "full.map"
    disc = [fl / "disc" / "NFS4.EXE", fl / "disc" / "FRONT.BIN"]
    w.newline()
    w.comment("---- natural link: linkers/link_order.txt -> linker script -> full.elf -> disc files")
    w.build([ldscript, rsp], "gen_ld", [ROOT / "linkers" / "link_order.txt"],
            implicit=[hdr, *o_recon, ROOT / "tools" / "gen_natural_ld.py"],
            variables={"ldscript": esc_path(ldscript), "rsp": esc_path(rsp),
                       "strict": "--strict" if args.strict_link else ""})
    w.build([elf], "ld", [ldscript, rsp], implicit=[hdr, *o_recon], implicit_outputs=[mapf],
            variables={"cmd": cmdline(full_link.ld_command(rsp))})
    w.build([fl / "nfs4.exe", *disc], "exe", [elf], implicit=[ROOT / "tools" / "elf_to_exe.py"])
    w.build(["sizes"], "report", [elf])

    # ---- phony targets
    w.newline()
    w.build(["disc"], "phony", disc)
    w.build(["link"], "phony", [elf])
    w.build(["objects"], "phony", [hdr, *o_recon])
    w.build(["split"], "phony", o_src)       # not "src": that is a directory build.ninja depends on
    e_hdr, e_src, e_recon = objs["expected"]
    w.build(["expected"], "phony", [e_hdr, *e_src, *e_recon])
    w.build(["all"], "phony", ["disc", "split"])
    w.default(["disc"])

    # ---- regeneration
    dirs = sorted({p for top in (ROOT / "src", b.RECON) if top.is_dir()
                   for p in [top, *top.rglob("*")] if p.is_dir()})
    tc_dir = Path(str(b.GCC_LADDER))
    regen = [ROOT / "configure.py", ROOT / "tools" / "build.py", ROOT / "tools" / "toolchain.py"]
    # The directories go through a depfile, not the edge's inputs: a directory that disappears later is then just
    # a reason to regenerate (Ninja treats missing depfile inputs as dirty), not "missing and no known rule".
    watched = dirs + ([tc_dir] if tc_dir.is_dir() else [])
    w.newline()
    w.build([NINJA_FILE], "configure", implicit=regen,
            variables={"configure_args": cmdline(sys.argv[1:])})

    NINJA_FILE.write_text(w.text())
    def dep_path(p: Path) -> str:
        try:
            p = p.relative_to(ROOT)
        except ValueError:
            pass
        return p.as_posix().replace("\\", "/").replace(" ", "\\ ").replace("#", "\\#").replace("$", "$$")
    NINJA_DEPFILE.write_text(dep_path(NINJA_FILE) + ": \\\n" +
                             " \\\n".join("  " + dep_path(d) for d in watched) + "\n")
    n_tu = len(srcs) + len(recon)
    print(f"[configure] {NINJA_FILE.name}: {n_tu} TUs x 2 variants (build/, expected/), "
          f"{sum(1 for l in w.lines if l.startswith('build '))} edges; now run: ninja")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--strict-link", action="store_true", help="unlisted object sections are a link error")
    configure(ap.parse_args())


if __name__ == "__main__":
    main()
