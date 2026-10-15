#!/usr/bin/env python3
"""full_link.py -- the production final link (Route A): a NATURAL link of the recon lane.

    python tools/full_link.py            # -> build/full_link/full.elf (+ full.map)
    python tools/elf_to_exe.py --split   # -> build/full_link/disc/{NFS4.EXE,FRONT.BIN}

What it does:
  1. tools/gen_natural_ld.py turns linkers/link_order.txt into build/full_link/nfs4_natural.ld;
  2. GNU ld links asm/header.s + every recon object with that script.

The link is natural: objects follow each other in the listed order and every address falls
out of the order and the object sizes.  There are no address files (no PROVIDE(sym = retail
address), no per-object placement), unresolved symbols are errors, duplicate definitions are
errors, and nothing is filled in from a retail image.  Whether the result is still
byte-identical to retail is a property of the sources -- tools/elf_to_exe.py reports it (sha1
of the disc files; a byte compare when rom/nfs4-f.exe is present).

usage: python tools/full_link.py [--strict]     (--strict: unlisted object sections are an error)
       python tools/full_link.py --report       (only print the section table of the existing full.elf;
                                                 `ninja sizes` runs this)

The Ninja build (configure.py, then `ninja`) runs the same two steps as separate edges; this script is the
one-shot equivalent.
"""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import toolchain as tc  # noqa: E402
import gen_natural_ld  # noqa: E402

LD = tc.mips('ld')
OUT = ROOT / 'build' / 'full_link'
ELF = OUT / 'full.elf'
MAPF = OUT / 'full.map'
SCRIPT = OUT / 'nfs4_natural.ld'

# retail section sizes (the SN link map of the shipped game) -- printed for reference only
RETAIL = {'.rdata': 0x4797C, '.text': 0xB5358, '.data': 0x2F878, '.sdata': 0x1830,
          '.sbss': 0x164, '.bss': 0xAC24, 'front.rdata': 0x28F0, 'front.text': 0x3E970,
          'front.data': 0x18D8, 'front.bss': 0x1A10}


def out_sections(elf):
    r = subprocess.run([tc.mips('objdump'), '-h', str(elf)], capture_output=True, text=True)
    secs = {}
    for ln in r.stdout.splitlines():
        m = re.match(r'^\s*\d+\s+(\S+)\s+([0-9a-f]{8})\s+([0-9a-f]{8})\s+([0-9a-f]{8})', ln)
        if m:
            secs[m.group(1)] = (int(m.group(2), 16), int(m.group(3), 16))   # (size, vma)
    return secs


def symbols(elf, names):
    r = subprocess.run([tc.mips('nm'), str(elf)], capture_output=True, text=True)
    got = {}
    for ln in r.stdout.splitlines():
        p = ln.split()
        if len(p) == 3 and p[2] in names:
            got[p[2]] = int(p[0], 16)
    return got


def ld_command(rsp):
    """The final link (cwd = repository root); configure.py writes the same command into build.ninja."""
    rel = lambda p: Path(p).relative_to(ROOT).as_posix()  # noqa: E731
    return [str(LD), '-T', rel(SCRIPT), '--orphan-handling=error', '--no-warn-rwx-segments',
            '-Map', rel(MAPF), '-o', rel(ELF), f'@{rel(rsp)}']


def report():
    secs = out_sections(ELF)
    print('[map] section       address     size     retail    diff')
    for name in gen_natural_ld.MAIN_SECTIONS + gen_natural_ld.FRONT_SECTIONS:
        if name in secs:
            sz, va = secs[name]
            ret = RETAIL.get(name)
            d = f'{sz - ret:+d}' if ret is not None else ''
            print(f'[map] {name:12s}  0x{va:08X}  0x{sz:06X}  0x{ret:06X}  {d}')
    s = symbols(ELF, {'__SN_ENTRY_POINT', '_gp', '__exe_t_size', '_bss_obj', '__last_org',
                      '_front_obj', '_front_objend'})
    print('[sym] ' + '  '.join(f'{k}=0x{v:08X}' for k, v in sorted(s.items())))


def main():
    if '--report' in sys.argv[1:]:
        if not ELF.is_file():
            sys.exit(f'[full_link] no {ELF.relative_to(ROOT).as_posix()} -- link first')
        report()
        return
    strict = '--strict' in sys.argv[1:]
    OUT.mkdir(parents=True, exist_ok=True)
    text, objs = gen_natural_ld.generate(strict)
    SCRIPT.write_text(text)
    print(f'[gen] {SCRIPT.relative_to(ROOT).as_posix()} from linkers/link_order.txt; {len(objs)} objects')
    if ELF.exists():
        ELF.unlink()
    rsp = OUT / 'objects.rsp'
    gen_natural_ld.write_rsp(rsp, objs)
    cmd = ld_command(rsp)
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    errs = [l for l in r.stderr.replace('\r\n', '\n').split('\n') if l.strip()]
    print(f'[ld] rc={r.returncode}  diagnostics={len(errs)}')
    for e in errs[:40]:
        print('   ', e)
    if r.returncode or not ELF.exists():
        sys.exit('[ld] link failed')

    report()
    print('next: python tools/elf_to_exe.py --split   (add --no-compare without rom/nfs4-f.exe)')


if __name__ == '__main__':
    main()
