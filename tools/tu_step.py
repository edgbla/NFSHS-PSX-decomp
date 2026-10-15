#!/usr/bin/env python3
"""tu_step.py -- compile one translation unit from its .i to its .o; build.ninja (configure.py) runs it.

    tu_step.py --lane LANE --src REL [--native] [--no-ver-splice] [--stdin] [--sig H] [--depfile D --dep-target T]
               -- CC1 FLAGS... I_FILE -o S_FILE  -- ASSEMBLER COMMAND... -o OBJ ...
    tu_step.py --lane c --src REL --raw40 OUTDIR [...] -- CC1 FLAGS... I_FILE -o S_FILE

The two commands after `--` are the TU's compiler and assembler invocations exactly as tools/build.py's plan has
them (configure.py writes them into build.ninja, so `ninja -t commands <object>` shows every flag of every TU).
This script runs them and adds the passes that are not separate programs (the same functions build.py uses):

    build.run_s    after cc1: the lane's text passes -- native jtbl post-processing, move->addu (2.7.2 lane) --
                   and the per-function splices of the TU (PER_FN_* tables)
    build.run_o    the assembler: maspsx (run inside this process: one interpreter per TU) + GNU as, or GNU as
                   alone; for C++ the cfront dtor rename first; fix_symsizes after
    build.run_raw40   instead of run_o for a PER_FN_RAW40_SPLICE TU (only when the PsyQ 4.0 cc1 is installed)

--stdin: the assembler command reads the .s on stdin (maspsx).
--depfile: the assembler's dependencies for Ninja -- every file the .s pulls in with `.include` (INCLUDE_ASM bodies
from asm/nonmatchings, asm/cert/*.s, macro.inc), resolved like GNU as does (the current directory = the repository
root, then the -I directories), recursively.  cpp's depfile cannot see these: the assembler reads them.
"""
import argparse
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as b  # noqa: E402

_INCLUDE_RE = re.compile(r'^[ \t]*\.include[ \t]+"([^"]+)"', re.M)


def asm_includes(s_file, inc_dirs):
    """Files reached through `.include` from `s_file` (recursively), as absolute paths."""
    found, todo, seen = [], [Path(s_file)], set()
    while todo:
        f = todo.pop()
        try:
            text = f.read_text(errors='replace')
        except OSError:
            continue
        for name in _INCLUDE_RE.findall(text):
            for d in [b.ROOT, *inc_dirs]:          # GNU as: the current directory, then -I
                cand = (Path(d) / name).resolve()
                if cand.is_file():
                    if cand not in seen:
                        seen.add(cand)
                        found.append(cand)
                        todo.append(cand)
                    break
    return found


def write_depfile(path, target, deps):
    esc = lambda s: str(s).replace('\\', '/').replace(' ', '\\ ')  # noqa: E731
    Path(path).write_text(f'{esc(target)}: ' + ' \\\n  '.join(esc(d) for d in deps) + '\n')


def _inc_dirs(cmd):
    return [cmd[i + 1] for i, c in enumerate(cmd[:-1]) if c == '-I']


def main(argv):
    parts, cur = [], []
    for a in argv:
        if a == '--':
            parts.append(cur)
            cur = []
        else:
            cur.append(a)
    parts.append(cur)
    opts, cmds = parts[0], parts[1:]

    ap = argparse.ArgumentParser(prog='tu_step.py')
    ap.add_argument('--lane', required=True, choices=['c', 'c272', 'cpp'])
    ap.add_argument('--src', required=True, help='TU path relative to the repository root')
    ap.add_argument('--native', action='store_true', help='the compiler is an FSF stand-in (native post-processing)')
    ap.add_argument('--no-ver-splice', action='store_true')
    ap.add_argument('--sig', help='hash of the TU\'s splice-table entries (only so Ninja sees table edits)')
    ap.add_argument('--stdin', action='store_true', help='the assembler command reads the .s on stdin (maspsx)')
    ap.add_argument('--raw40', metavar='OUTDIR', help='W73 raw-4.0 route; OUTDIR = object root (build, expected)')
    ap.add_argument('--depfile', help="write the assembler step's .include dependencies here")
    ap.add_argument('--dep-target', help="the depfile's target (Ninja's $out)")
    a = ap.parse_args(opts)
    if len(cmds) != (1 if a.raw40 else 2) or not all(cmds):
        ap.error('expected `-- <compiler command>` and (except --raw40) `-- <assembler command>`')
    os.chdir(b.ROOT)

    cc1_cmd = cmds[0]
    s_file = cc1_cmd[-1]
    b.run_s(a.lane, a.src, cc1_cmd, native=a.native, ver_splice=not a.no_ver_splice)
    if a.raw40:
        plan = b.plan_c(b.ROOT / a.src, skip_asm=False, out=b.ROOT / a.raw40)
        if not plan['raw40']:
            sys.exit(f'[tu_step] {a.src}: no raw40 route (not in PER_FN_RAW40_SPLICE, or the PsyQ 4.0 cc1 is missing)')
        b.run_raw40(plan)
        dep_root, inc = plan['raw40']['merged'], [str(b.ROOT / 'include'), str(b.ROOT)]
    else:
        asm_cmd = cmds[1]
        b.run_o(a.lane, a.src, asm_cmd, stdin=s_file if a.stdin else None, native=a.native, inproc=True)
        dep_root, inc = s_file, _inc_dirs(asm_cmd)
    if a.depfile:
        write_depfile(a.depfile, a.dep_target, asm_includes(dep_root, inc))


if __name__ == '__main__':
    main(sys.argv[1:])
