"""toolchain.py -- where the Route A tools live, on Windows and on native Linux.

Every Route A script (build.py, full_link.py, elf_to_exe.py, ...) asks this module for its tool paths instead of
hard-coding the Windows dev-box locations.  On Windows nothing changes: the defaults are exactly the paths the scripts
used before (C:/Tools/mips-ps1/..., C:/Temp/psq43/...), and every NFS4_* environment override keeps working.

On Linux (no Wine) the defaults are native tools:

  * MIPS binutils  -- the first of `mipsel-none-elf-*`, `mipsel-linux-gnu-*` (Debian/Ubuntu package
                      `binutils-mipsel-linux-gnu`) found in $NFS4_MIPS_BIN, toolchain/linux/binutils/bin or $PATH.
                      Override the prefix with NFS4_MIPS_PREFIX (e.g. `mipsel-elf-`).
  * cpp            -- `<prefix>cpp` when present, otherwise the host `cpp` (the build always runs it with -nostdinc
                      -undef, so the host predefines never leak into the output).
  * cc1 / cc1plus  -- FSF GCC builds for the `mips-sony-psx` target from https://github.com/decompals/old-gcc,
                      unpacked by tools/linux/setup_toolchain.sh into toolchain/linux/gcc-<ver>-psx/.  They replace
                      the proprietary SN Systems Windows compilers lane by lane:

                        PsyQ 4.3 CC1PSX / CC1PLPSX (2.8.0)   -> gcc-2.8.0-psx  cc1 / cc1plus
                        PsyQ 4.0 CC1PSX (2.7.2.SN32)         -> gcc-2.7.2-psx  cc1
                        PsyQ 4.4 CC1PSX / CC1PLPSX (2.8.1)   -> gcc-2.8.1-psx  cc1 / cc1plus
                        FSF ladder rungs gcc-<ver>-psx       -> the same rung, native build
                        ladder rung 2.7.2-970404             -> gcc-2.7.2-cdk (cygnus 2.7.2-970404)

                      The FSF compilers are not the SN binaries: the result is a working build, not a guaranteed
                      byte-identical one.  Override any of them with the usual NFS4_CC1, NFS4_CC1PL, NFS4_CC1_272, ...
                      or move the whole tree with NFS4_LINUX_TOOLCHAIN.
"""
import os
import shutil
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
IS_WINDOWS = os.name == "nt"
EXE = ".exe" if IS_WINDOWS else ""

# --------------------------------------------------------------------------------------------------------------------
# Linux toolchain tree (populated by tools/linux/setup_toolchain.sh)
LINUX_TC = Path(os.environ.get("NFS4_LINUX_TOOLCHAIN", ROOT / "toolchain" / "linux"))

# default C compiler generation on Linux for the main (PsyQ 4.3) lane; override with NFS4_LINUX_CC1_VER
LINUX_MAIN_VER = os.environ.get("NFS4_LINUX_CC1_VER", "2.8.0")


def linux_gcc(ver: str, prog: str = "cc1") -> Path:
    """toolchain/linux/gcc-<ver>-psx/<prog> (no existence check)."""
    v = ver if ver.endswith("-psx") else f"{ver}-psx"
    return LINUX_TC / f"gcc-{v}" / prog


# --------------------------------------------------------------------------------------------------------------------
# MIPS binutils
_WIN_MIPS_BIN = r"C:/Tools/mips-ps1/mips/bin"
_LINUX_PREFIXES = ("mipsel-none-elf-", "mipsel-linux-gnu-", "mipsel-elf-", "mipsel-unknown-elf-")


def _find_linux_binutils():
    """-> (dir or None, prefix).  dir None means "found on $PATH"."""
    prefixes = [os.environ["NFS4_MIPS_PREFIX"]] if os.environ.get("NFS4_MIPS_PREFIX") else list(_LINUX_PREFIXES)
    dirs = []
    if os.environ.get("NFS4_MIPS_BIN"):
        dirs.append(Path(os.environ["NFS4_MIPS_BIN"]))
    dirs.append(LINUX_TC / "binutils" / "bin")
    for d in dirs:
        for p in prefixes:
            if (d / f"{p}as").is_file():
                return d, p
    for p in prefixes:
        if shutil.which(f"{p}as"):
            return None, p
    return None, prefixes[0]          # nothing found -- report the first candidate in error messages


if IS_WINDOWS:
    MIPS_BIN = Path(os.environ.get("NFS4_MIPS_BIN", _WIN_MIPS_BIN))
    MIPS_PREFIX = os.environ.get("NFS4_MIPS_PREFIX", "mipsel-none-elf-")
else:
    _d, MIPS_PREFIX = _find_linux_binutils()
    MIPS_BIN = _d


def mips(tool: str) -> str:
    """Path (or bare $PATH name) of a MIPS binutils program: mips('ld'), mips('objdump') ..."""
    name = f"{MIPS_PREFIX}{tool}{EXE}"
    if MIPS_BIN is None:
        return shutil.which(name) or name
    return str(MIPS_BIN / name)


def mips_cpp() -> str:
    if IS_WINDOWS:
        return mips("cpp")
    c = mips("cpp")
    if Path(c).is_file() or shutil.which(c):
        return c
    return shutil.which("cpp") or "cpp"


# --------------------------------------------------------------------------------------------------------------------
# Compilers: platform defaults (env overrides are applied by the callers, as before)
if IS_WINDOWS:
    DEFAULT_CC1 = r"C:/Temp/psq43/COMPILER/CC1PSX.EXE"
    DEFAULT_CC1PL = r"C:/Temp/psq43/COMPILER/CC1PLPSX.EXE"
    DEFAULT_CC1_272 = r"C:/Temp/nfs3-clean/psyq400/COMPILER/CC1PSX.EXE"
    DEFAULT_CC1_281_SN = r"C:/Temp/psq44/pssn/bin/CC1PSX.EXE"
    DEFAULT_CC1PL_281_SN = r"C:/Temp/psq44/pssn/bin/CC1PLPSX.EXE"
    DEFAULT_GCC_LADDER = r"C:/Temp/windows-gcc-psx"
else:
    DEFAULT_CC1 = str(linux_gcc(LINUX_MAIN_VER, "cc1"))
    DEFAULT_CC1PL = str(linux_gcc(LINUX_MAIN_VER, "cc1plus"))
    DEFAULT_CC1_272 = str(linux_gcc("2.7.2", "cc1"))
    DEFAULT_CC1_281_SN = str(linux_gcc("2.8.1", "cc1"))
    DEFAULT_CC1PL_281_SN = str(linux_gcc("2.8.1", "cc1plus"))
    DEFAULT_GCC_LADDER = str(LINUX_TC)

# Ladder rungs whose old-gcc build has a different directory name.  old-gcc's `gcc-2.7.2-cdk` IS the
# cygnus-2.7.2-970404 snapshot (it reports "cygnus-2.7.2-970404 SN32.3.7.0004 (SonyPSX)").
LINUX_RUNG_DIRS = {
    "2.7.2-970404": "gcc-2.7.2-cdk",
}


def linux_rung_cc1(ver: str) -> Path:
    """Native cc1 for a gcc ladder rung name as used in PER_TU_FLAGS (cc1_alt / cc1_ver)."""
    d = LINUX_RUNG_DIRS.get(ver, f"gcc-{ver}-psx")
    return LINUX_TC / d / "cc1"


# Extra GNU as flags.  gas pads every section to its alignment unless the target OS is plain "elf"
# (tc-mips.c md_section_align), so mipsel-linux-gnu-as would grow each object's .text/.data to a 16-byte multiple
# where the Windows mipsel-none-elf-as does not.  --no-pad-sections restores the none-elf behaviour.
AS_EXTRA = [] if IS_WINDOWS else ["--no-pad-sections"]

# Extra cc1plus flags for the native FSF stand-in.  FSF gcc 2.8.x enables C++ exception handling by default and then
# emits .eh_frame / .gcc_except_table plus landing-pad code; SN's CC1PLPSX did not (retail has no EH data).
# Likewise RTTI: FSF emits a __tf<class> type_info function per polymorphic class; retail has none.
NATIVE_CC1PLUS_FLAGS = ["-fno-exceptions", "-fno-rtti"]


# Switch jump tables.  FSF cc1plus 2.8 writes each table into .rdata right after the function that uses it, and the
# class vtables / late string pools after it.  The retail objects split into two groups:
#   * FRONT.BIN (recon/frontend/...): SN kept exactly the FSF order -- e.g. feapp.obj has its jtbl at 0x80010078,
#     *before* the vtable at 0x80010098.  Built with the FSF order, FRONT.BIN comes out byte-identical to the disc.
#   * NFS4.EXE (everything else, recon/game/...): SN wrote the tables after everything else in the object -- retail
#     aih_btccop.obj .rodata is SimpleMem (12 + 4 pad) + 5 vtables + jtbl_80054F64 = 220 B.  With the FSF order the
#     8-byte-aligned vtables after a 4-byte table pick up pad bytes (aih_* outgrow their pinned slot) and the strings
#     after a table move (camera/replay/track/texture .rodata no longer match the retail bytes).
# Measured over all 26 C++ TUs that have jump tables: this split gives 0 slot overflows and 0 differing .rodata bytes
# against the retail pieces, while either order applied everywhere breaks one group.  The switch functions sit at
# their retail .text offsets in both builds, so only the .rdata emission order differs; no FSF flag reproduces it.
# NFS4_JTBL_TAIL="stem1,stem2" replaces the rule with an explicit list of TU stems ("" = never reorder,
# "*" = always reorder).
import re as _re
_JTBL_RE = _re.compile(r"^\t\.rdata\n(\t\.align\t\d+\n\$L\d+:\n(?:\t\.(?:word|gpword)\t\$L\d+\n)+)\t\.text\n", _re.M)


def jtbl_tail(src) -> bool:
    """Should the jump tables of TU `src` go to the end of its .rdata?"""
    env = os.environ.get("NFS4_JTBL_TAIL")
    if env is not None:
        stems = {s.strip().lower() for s in env.split(",") if s.strip()}
        return "*" in stems or Path(src).stem.lower() in stems
    return "frontend" not in Path(src).as_posix().lower().split("/")


def native_cc1plus_postprocess(s_text: str, src=None) -> str:
    """Post-process FSF cc1plus output for TU `src` (a path; its stem selects the jtbl reorder)."""
    if src is None or not jtbl_tail(src):
        return s_text
    return _move_jtbls_to_end(s_text)


def _move_jtbls_to_end(s_text: str) -> str:
    tables = []

    def _take(m):
        tables.append(m.group(1))
        return "\t.text\n"
    out = _JTBL_RE.sub(_take, s_text)
    if not tables:
        return s_text
    if not out.endswith("\n"):
        out += "\n"
    return out + "\t.rdata\n" + "".join(tables) + "\t.text\n"


# C TUs (cc1): FSF and SN agree almost everywhere, so the reorder is opt-in per TU stem.
# nfile.c (eacpsxz): retail has the string pool before its two jump tables.
JTBL_TAIL_C = {"nfile"}
if "NFS4_JTBL_TAIL_C" in os.environ:
    JTBL_TAIL_C = {s.strip().lower() for s in os.environ["NFS4_JTBL_TAIL_C"].split(",") if s.strip()}


def native_cc1_postprocess(s_text: str, src=None) -> str:
    """Post-process FSF cc1 (C) output for TU `src`."""
    if src is None or Path(src).stem.lower() not in JTBL_TAIL_C:
        return s_text
    return _move_jtbls_to_end(s_text)


def is_native_substitute(p) -> bool:
    """True for a native FSF stand-in compiler (not an SN Systems Windows binary).

    Off Windows every compiler that can run at all is a native ELF build (the SN compilers are Windows PE files and
    this build does not use Wine), so anything that is not a PE image counts -- independent of where it lives or of
    symlinks into the toolchain tree."""
    if IS_WINDOWS:
        return False
    try:
        with open(p, "rb") as f:
            return f.read(2) != b"MZ"
    except OSError:
        return True


def default_tmp() -> str:
    """Scratch dir for the 1996-era cc1s (they build cta<pid> paths from TMPDIR)."""
    if IS_WINDOWS:
        return os.environ.get("TEMP") or r"C:\Temp"
    return os.environ.get("TMPDIR") or "/tmp"


def describe() -> str:
    lines = [f"host        : {'windows' if IS_WINDOWS else 'linux/posix'}",
             f"binutils    : {mips('as')}",
             f"cpp         : {mips_cpp()}",
             f"cc1         : {os.environ.get('NFS4_CC1', DEFAULT_CC1)}",
             f"cc1plus     : {os.environ.get('NFS4_CC1PL', DEFAULT_CC1PL)}",
             f"cc1 (2.7.2) : {os.environ.get('NFS4_CC1_272', DEFAULT_CC1_272)}",
             f"gcc ladder  : {os.environ.get('NFS4_GCC_LADDER', DEFAULT_GCC_LADDER)}"]
    return "\n".join(lines)


if __name__ == "__main__":
    print(describe())
