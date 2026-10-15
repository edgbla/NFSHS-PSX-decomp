#!/usr/bin/env python3
"""fn_sizes.py -- per-function code size of built objects against the retail sizes.

asm/nonmatchings/{main,front}/<fn>.s (the committed splat output of the retail EXE) opens every function with
`nonmatching <name>, 0x<size>`.  This compares those sizes with the function symbols of the objects in build/, which
shows where a non-SN compiler (the native Linux toolchain) produced more or less code than retail.

    python tools/linux/fn_sizes.py OBJ.o [OBJ.o ...]      # functions of these objects whose size differs
    python tools/linux/fn_sizes.py --all                  # summary over every build/recon object

When build/full_link/full.map exists (tools/full_link.py), each function is looked up by its linked address first, so
file-static functions that share a name (e.g. the two `locaterequest`s of nasync.c and stream.c) are told apart;
otherwise, or for an address splat did not split, the lookup falls back to the name.
"""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import toolchain as tc  # noqa: E402

_NM = re.compile(r"^\s*nonmatching\s+(\S+),\s*0x([0-9A-Fa-f]+)", re.M)
_ADDR = re.compile(r"/\*\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s+\*/")


def retail_sizes():
    """-> ({name: size}, {retail address: size})"""
    by_name, by_addr = {}, {}
    for d in ("main", "front"):
        for p in (ROOT / "asm" / "nonmatchings" / d).glob("*.s"):
            head = p.read_text(errors="replace")[:1200]
            m = _NM.search(head)
            if m:
                size = int(m.group(2), 16)
                by_name.setdefault(m.group(1), size)
                a = _ADDR.search(head, m.end())
                if a:
                    by_addr[int(a.group(1), 16)] = size
    return by_name, by_addr


_OUT_RE = re.compile(r"^(\S+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)")
_IN_RE = re.compile(r"^ (\S+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) (\S.*)$")
_IN_NAME_RE = re.compile(r"^ (\S+)$")
_IN_CONT_RE = re.compile(r"^\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) (\S.*)$")


def input_sections(map_path: Path):
    """-> [(addr, size, outsec, insec, file)] from a GNU ld -Map file."""
    res, cur, pending = [], None, None
    text = map_path.read_text(errors="replace").splitlines()
    try:
        start = next(i for i, l in enumerate(text) if l.startswith("Linker script and memory map"))
    except StopIteration:
        start = 0
    for ln in text[start:]:
        m = _OUT_RE.match(ln)
        if m and not ln.startswith(" "):
            cur, pending = m.group(1), None
            continue
        if ln and not ln.startswith(" "):
            cur = ln.strip() if ln.strip().startswith(".") else cur   # long output name on its own line
            pending = None
            continue
        m = _IN_RE.match(ln)
        if m:
            res.append((int(m.group(2), 16), int(m.group(3), 16), cur, m.group(1), m.group(4).strip()))
            pending = None
            continue
        m = _IN_NAME_RE.match(ln)
        if m and m.group(1).startswith("."):
            pending = m.group(1)
            continue
        m = _IN_CONT_RE.match(ln)
        if m and pending:
            res.append((int(m.group(1), 16), int(m.group(2), 16), cur, pending, m.group(3).strip()))
            pending = None
    return res


def text_bases():
    """-> {object path relative to ROOT: link address of its .text} from the full_link map (empty if absent)."""
    mp = ROOT / "build" / "full_link" / "full.map"
    if not mp.is_file():
        return {}
    out = {}
    for addr, size, _osec, isec, f in input_sections(mp):
        if isec == ".text" and size:
            out.setdefault(f, addr)
    return out


def obj_functions(obj):
    r = subprocess.run([tc.mips("objdump"), "-t", str(obj)], capture_output=True, text=True).stdout
    fns = []
    for ln in r.splitlines():
        m = re.match(r"^([0-9a-f]{8})\s.*\bF \.text\s+([0-9a-f]{8})\s+(\S+)$", ln)
        if m:
            fns.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3)))
    return sorted(fns)


def main():
    ret, ret_addr = retail_sizes()
    bases = text_bases()
    objs = sorted((ROOT / "build" / "recon").rglob("*.o")) if "--all" in sys.argv else [Path(a) for a in sys.argv[1:]]
    tot_d = n_diff = n_cmp = 0
    for o in objs:
        rows = []
        try:
            key = str(Path(o).resolve().relative_to(ROOT))
        except ValueError:
            key = str(o)
        base = bases.get(key)
        for off, size, name in obj_functions(o):
            r = ret_addr.get(base + off) if base is not None else None
            if r is None:
                r = ret.get(name.replace(".", "_")) or ret.get(name)
            if r is None:
                continue
            n_cmp += 1
            if r != size:
                n_diff += 1
                tot_d += size - r
                rows.append(f"   {size - r:+6d}  {name}  (ours 0x{size:X}, retail 0x{r:X})")
        if rows and "--all" not in sys.argv or (rows and "-v" in sys.argv):
            print(o.relative_to(ROOT) if o.is_absolute() else o)
            print("\n".join(rows))
        elif rows:
            print(f"{len(rows):4d} fn(s) differ  {sum(int(r.split()[0]) for r in rows):+6d} B  {o.relative_to(ROOT)}")
    print(f"[fn_sizes] {n_cmp} functions compared, {n_diff} differ in size, net {tot_d:+d} bytes")


if __name__ == "__main__":
    main()
