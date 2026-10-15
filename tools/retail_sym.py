#!/usr/bin/env python3
"""retail_sym.py -- the text dump of the retail NFS4.SYM, generated on demand.

The retail `NFS4.SYM` (from the disc, next to NFS4.MAP) is NOT in the repository: supply it as `rom/NFS4.SYM`.
`txt()` returns the path of its dumpsym text -- `build/sym/nfs4-f-v3.txt` -- and (re)creates it with the vendored
`tools/dumpsym/dumpsym.exe` (Windows) or `tools/dumpsym/dumpsym` (Linux x86-64, static build of `main.c`) when it is missing
or older than the SYM or the dumper.  Where the vendored Linux binary cannot run (another CPU, macOS), the dumper is built
from `tools/dumpsym/main.c` with the host C compiler ($CC, default `cc`) into `build/tools/dumpsym/dumpsym`.  The result is byte-identical to the
`nfs4-f-v3.txt` the project has always used (the "v3" = dumpsym with the bool/NULL fix).

    python tools/retail_sym.py          # make sure the dump exists, print its path
"""
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DUMPSYM_SRC = ROOT / 'tools' / 'dumpsym' / 'main.c'
if os.name == 'nt':
    DUMPSYM = ROOT / 'tools' / 'dumpsym' / 'dumpsym.exe'
else:
    DUMPSYM = ROOT / 'tools' / 'dumpsym' / 'dumpsym'            # vendored: cc -O2 -w -static -s main.c (x86-64)
DUMPSYM_BUILT = ROOT / 'build' / 'tools' / 'dumpsym' / 'dumpsym'
SYM = ROOT / 'rom' / 'NFS4.SYM'
TXT = ROOT / 'build' / 'sym' / 'nfs4-f-v3.txt'
SYM_SIZE, SYM_SHA1 = 7881225, None      # size of the retail file; a wrong file is refused below


def _runs(exe):
    try:
        return subprocess.run([str(exe)], capture_output=True, timeout=10).stdout.startswith(b'dumpsym')
    except (OSError, subprocess.SubprocessError):
        return False


def _ensure_dumpsym():
    """Windows: the vendored .exe.  Linux: the vendored static binary (the x bit is restored if a checkout lost it);
    where it cannot run, a host build of main.c in build/ (rebuilt when main.c is newer)."""
    global DUMPSYM
    if os.name == 'nt':
        return
    if DUMPSYM.is_file():
        if not os.access(DUMPSYM, os.X_OK):
            try:
                DUMPSYM.chmod(DUMPSYM.stat().st_mode | 0o111)
            except OSError:
                pass
        if _runs(DUMPSYM):
            return
    DUMPSYM = DUMPSYM_BUILT
    if DUMPSYM.is_file() and DUMPSYM.stat().st_mtime >= DUMPSYM_SRC.stat().st_mtime:
        return
    DUMPSYM.parent.mkdir(parents=True, exist_ok=True)
    cc = os.environ.get('CC', 'cc')
    r = subprocess.run([cc, '-O2', '-w', '-o', str(DUMPSYM), str(DUMPSYM_SRC)], capture_output=True, text=True)
    if r.returncode:
        sys.exit('[retail_sym] building dumpsym with %s failed:\n%s' % (cc, r.stderr[:500]))


def dumpsym():
    """path of the dumper (str)"""
    _ensure_dumpsym()
    return str(DUMPSYM)


def txt():
    """path of the retail SYM text dump (str), generating it when needed"""
    if not SYM.is_file():
        sys.exit('[retail_sym] %s not found -- copy the retail NFS4.SYM from the disc there (it is not committed, like '
                 'rom/nfs4-f.exe and rom/NFS4.MAP)' % SYM)
    if SYM.stat().st_size != SYM_SIZE:
        sys.exit('[retail_sym] %s is %d bytes, the retail file is %d' % (SYM, SYM.stat().st_size, SYM_SIZE))
    _ensure_dumpsym()
    fresh = TXT.is_file() and TXT.stat().st_size and TXT.stat().st_mtime >= max(SYM.stat().st_mtime, DUMPSYM.stat().st_mtime)
    if not fresh:
        TXT.parent.mkdir(parents=True, exist_ok=True)
        tmp = TXT.with_suffix('.tmp')
        with open(tmp, 'wb') as f:
            r = subprocess.run([str(DUMPSYM), str(SYM)], stdout=f, stderr=subprocess.PIPE)
        if r.returncode or not tmp.stat().st_size:
            sys.exit('[retail_sym] dumpsym failed: %s' % r.stderr.decode(errors='replace')[:300])
        tmp.replace(TXT)
    return str(TXT).replace(chr(92), '/')


if __name__ == '__main__':
    print(txt())
