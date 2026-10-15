#!/usr/bin/env bash
# setup_toolchain.sh -- install the native Linux toolchain for the NFS4 decomp (no Wine, no SN binaries).
#
#   tools/linux/setup_toolchain.sh            # required compilers + check host tools
#   tools/linux/setup_toolchain.sh --all      # also the unused ladder versions (2.6.0, 2.91.66, 2.95.2)
#   tools/linux/setup_toolchain.sh --apt      # additionally `sudo apt-get install` the host packages
#
# What it sets up:
#   toolchain/linux/gcc-<ver>/{cc1,cc1plus,cpp,gcc,g++}   from decompals/old-gcc release 0.17 (Linux x86-64 builds)
#       gcc-2.8.0-psx   main lane: stands in for SN CC1PSX / CC1PLPSX of PsyQ 4.3
#       gcc-2.8.1-psx   "2.8.1-sn" lane (PsyQ 4.4) and the 2.8.1 ladder rung
#       gcc-2.7.2-psx   CC1PSX 4.0 lane and the 2.7.2 ladder rung
#       gcc-2.7.2-cdk   the 2.7.2-970404 rung (Cygnus CDK; FSF 2.7.2 rejects its "+m" asm constraints)
#       gcc-2.6.3-psx   the 2.6.3 rung (function splice in syslib libetc/INTR.c)
#   Host packages (Debian/Ubuntu names): python3, binutils-mipsel-linux-gnu, cpp, curl (or wget), tar;
#   tools/dumpsym/dumpsym is vendored as a static x86-64 binary; a host C compiler is only a fallback on other CPUs.
#
# Override the install directory with NFS4_LINUX_TOOLCHAIN (the build reads the same variable).
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
DEST="${NFS4_LINUX_TOOLCHAIN:-$ROOT/toolchain/linux}"
RELEASE="${OLD_GCC_RELEASE:-0.17}"
BASE="https://github.com/decompals/old-gcc/releases/download/$RELEASE"

REQUIRED=(2.8.0-psx 2.8.1-psx 2.7.2-psx 2.7.2-cdk 2.6.3-psx)
OPTIONAL=(2.6.0-psx 2.91.66-psx 2.95.2-psx)

want=("${REQUIRED[@]}")
do_apt=0
for a in "$@"; do
  case "$a" in
    --all) want+=("${OPTIONAL[@]}") ;;
    --apt) do_apt=1 ;;
    -h|--help) sed -n '2,20p' "$0"; exit 0 ;;
    *) echo "unknown option: $a" >&2; exit 2 ;;
  esac
done

if [ "$do_apt" = 1 ]; then
  sudo apt-get update
  sudo apt-get install -y python3 binutils-mipsel-linux-gnu cpp gcc curl tar ninja-build
fi

fetch() {  # url -> file
  if command -v curl >/dev/null; then curl -fL --retry 3 -o "$2" "$1"
  elif command -v wget >/dev/null; then wget -q -O "$2" "$1"
  else echo "need curl or wget" >&2; exit 1; fi
}

mkdir -p "$DEST"
for v in "${want[@]}"; do
  d="$DEST/gcc-$v"
  if [ -x "$d/cc1" ]; then
    echo "[ok]   gcc-$v already in $d"
    continue
  fi
  echo "[get]  gcc-$v"
  tmp="$(mktemp -d)"
  fetch "$BASE/gcc-$v.tar.gz" "$tmp/gcc.tar.gz"
  mkdir -p "$d"
  tar -xzf "$tmp/gcc.tar.gz" -C "$d"         # the tarballs are flat: cc1 cc1plus cpp gcc g++
  rm -rf "$tmp"
  chmod +x "$d"/* || true
  [ -x "$d/cc1" ] || { echo "gcc-$v: no cc1 after extraction" >&2; exit 1; }
done

chmod +x "$ROOT/tools/psxiso/mkpsxiso" "$ROOT/tools/psxiso/dumpsxiso" "$ROOT/tools/dumpsym/dumpsym" 2>/dev/null || true

# ---- host tool check ---------------------------------------------------------------------------------------------
missing=0
check() { if command -v "$1" >/dev/null; then echo "[ok]   $1 -> $(command -v "$1")"; else echo "[MISS] $1  ($2)"; missing=1; fi; }
check python3 "apt install python3"
as_found=""
for p in mipsel-none-elf- mipsel-linux-gnu- mipsel-elf- mipsel-unknown-elf-; do
  if command -v "${p}as" >/dev/null; then as_found="$p"; break; fi
done
if [ -n "$as_found" ]; then
  echo "[ok]   MIPS binutils: ${as_found}{as,ld,objcopy,objdump}"
else
  echo "[MISS] mipsel binutils  (apt install binutils-mipsel-linux-gnu, or set NFS4_MIPS_BIN / NFS4_MIPS_PREFIX)"
  missing=1
fi
check cpp "apt install cpp"
if command -v ninja >/dev/null; then echo "[ok]   ninja -> $(command -v ninja) ($(ninja --version))"
else echo "[opt]  ninja not found (apt install ninja-build): the sequential python path still works"; fi

echo
echo "toolchain: $DEST"
python3 "$ROOT/tools/toolchain.py" 2>/dev/null || true
if [ "$missing" = 0 ]; then
  if command -v ninja >/dev/null; then echo "ready: python3 configure.py && ninja"
  else echo "ready: python3 tools/build.py --skip-asm && python3 tools/full_link.py && python3 tools/elf_to_exe.py --split --no-compare"; fi
fi
exit "$missing"
