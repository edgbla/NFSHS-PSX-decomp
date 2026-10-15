# Building `NFS4.EXE` and `FRONT.BIN`

How to go from this repository's source to the two executable files on the *Need for Speed: High Stakes* (PSX) disc,
and how to check that they are byte-identical to retail.

State on 2026-10-13: both files build **byte-identical to the retail disc** through Route A below -- a **natural link**:
the objects follow each other in link order and every address falls out of that order and the object sizes; no object is
placed at an address of its own, no symbol is given a retail address, no retail byte is copied in.

On Linux, Route A also runs natively (no Wine, no SN binaries) with FSF stand-in compilers: see
[BUILDING_LINUX.md](BUILDING_LINUX.md) (in Russian).

The former Routes B, C and D (SN's PSYLINK / SLINK / CPE2X under an MS-DOS player, and the `recon/mod` relink on top of
Route C) have been removed together with `tools/psyq_pipe/` and `tools/msdos-player/`; what Route C established about the
original link is summarised in [How the natural link reproduces retail](#how-the-natural-link-reproduces-retail).

| File | Size | sha1 (first 12) |
|---|---|---|
| `NFS4.EXE` | 1,239,040 bytes | `c5c60d450bac` |
| `FRONT.BIN` | 279,880 bytes | `d6c5b5d16e55` |

## What the two files are

The game is one program linked as three groups:

```
        org     $80010000
text    group                   ; .rdata .text .data .sdata  -> NFS4.EXE
bss     group   bss             ; .sbss .bss
front   group   over(text)      ; front.rdata front.text front.data front.bss -> FRONT.BIN
```

- **`FRONT.BIN`** is the front end (menus, car select, tournament, memory card). It is an **overlay**: raw bytes, no header,
  loaded at `0x80010000`, 0x44548 bytes long. The file includes the zeros of `front.bss`.
- **`NFS4.EXE`** is a PS-X EXE (0x800-byte header + load image from `0x80010000`, size `0x12E000`, entry
  `0x800E402C`). Its first 282,000 bytes of `.rdata` are **`bigBuf`**, a zero-filled reservation made by `bigbuf.obj`
  (`recon/frontend/psx/bigbuf.c`). The overlay is linked over that same address.
- At run time `nfs3.cpp` loads the overlay with `asyncloadfileat("front.bin", bigBuf)`. `address.obj`
  (`recon/frontend/psx/address.c`) holds the overlay's start and end address.
- The disc has no `SYSTEM.CNF`; the console boots `PSX.EXE`, which loads `cdrom:nfs4.exe`.

Change front-end code and only `FRONT.BIN` changes; change game code and only `NFS4.EXE` does.

`rom/nfs4-f.exe`, the file every gate compares against, is a **merge** of the two: `NFS4.EXE` with `FRONT.BIN` written
into the `bigBuf` hole. Cutting it at `0x80010000..0x80054548` gives exactly the two disc files.

## Prerequisites

Nothing copyrighted is in the repository. You supply:

| What | Where it goes | Notes |
|---|---|---|
| The merged target | `rom/nfs4-f.exe` | sha1 `b48ea3452e64…`. Optional: only byte comparisons read it; the build and the sha1 check of the two disc files do not. |
| The retail link map | `rom/NFS4.MAP` | From the disc. Optional: analysis tools (`gen_symbols.py`, `fn_sizes.py` …) read it; the build does not. |
| The retail symbol file | `rom/NFS4.SYM` | From the disc, 7,881,225 bytes. Only the comparison tools need it; `tools/retail_sym.py` dumps it to `build/sym/nfs4-f-v3.txt` with the vendored `tools/dumpsym/dumpsym.exe` on first use. |
| PsyQ 4.3 compilers | `C:/Temp/psq43/COMPILER/CC1PSX.EXE`, `CC1PLPSX.EXE` | The real SN compilers (GNU C 2.8.0). Override with `NFS4_CC1`, `NFS4_CC1PL`. |
| PsyQ 4.0 `CC1PSX` | next to `CC1PSX.EXE` as `CC1PSX272.EXE` | gcc 2.7.2 lane used by some Sony library files. Without it those files fall back with a warning. |
| PsyQ 4.4 `CC1PLPSX` | next to `CC1PSX.EXE` as `CC1PLPSX44.EXE` | One per-function splice (`Night_CreateNightTableElement`). |
| PsyQ 4.3 libraries, extracted | `C:/Temp/nfs4-clean/psyq43/extracted/` | Made once from the SDK's `PSX/LIB` folder with `python tools/psyq_extract.py [LIBDIR [OUTDIR]]`: every library member as an `.obj`, every function as a `.bin`, plus `INDEX.tsv`. `tools/link_stripped_check.py` compares the link-stripped functions with these blobs. Not needed by the build. |
| MIPS binutils 2.43 | `C:/Tools/mips-ps1/mips/bin/` | `mipsel-none-elf-{cpp,as,ld,objcopy,objdump,nm}`. Override with `NFS4_MIPS_BIN`. |
| Python 3.12+ | | Standard library only for the build tools. |
| Ninja 1.10+ | on `PATH` | Optional but recommended: incremental, parallel builds (`python configure.py && ninja`). Without it the sequential scripts below do the same job. |

`maspsx` (the ASPSX 2.77 stand-in that lets GNU `as` assemble the compiler output) is vendored in `tools/maspsx/`.
The exact toolchain zip layout CI expects is described at the top of `.github/workflows/report.yml`.

The source the build compiles is `recon/` (the reconstructed C and C++) plus the PS-X EXE header `asm/header.s`.
`src/` and `asm/nonmatchings/` are the splat split (per-function matching with objdiff, `fn_sizes.py`); they are not
linked.

## Route A — the byte-identical build (natural link)

### With Ninja (incremental)

```bash
python configure.py      # once: writes build.ninja (it regenerates itself afterwards)
ninja                    # compile + natural link + NFS4.EXE / FRONT.BIN
```

`configure.py` turns the build plan of `tools/build.py` into `build.ninja`: per translation unit one preprocessor edge
(`<obj>.i`, header dependencies from `cpp -MD`) and one compile edge (`<obj>.o` + `<obj>.s`, run by `tools/tu_step.py`:
the TU's cc1 / cc1plus with all its flags, the `.s` passes and splices of `build.py`, maspsx + GNU `as`; `.include`d
assembly is tracked through a depfile). Every per-file parameter -- compiler lane, `PER_TU_FLAGS`, cc1 version -- is
written into that TU's command line, so editing one TU's entry rebuilds just that TU (TUs with per-function splice
tables carry a hash of their table entries for the same reason). Then the link: `gen_natural_ld.py` (restat: an
unchanged script does not relink), GNU `ld`, `elf_to_exe.py --split`. The objects are byte-identical to those of the
sequential build. From scratch on 2 cores the default target takes about 22 s; after editing one file, under a second.

| Target | What |
|---|---|
| `ninja` = `ninja disc` | the objects that are linked (`recon/` + `asm/header.s`), the link, `NFS4.EXE` + `FRONT.BIN` |
| `ninja link` / `ninja objects` | stop after `build/full_link/full.elf` / after the linked objects |
| `ninja split` | also `src/*.c` (the splat split; not linked) |
| `ninja expected` | `expected/**.o`, the objdiff targets as CI builds them (no `-DSKIP_ASM`) |
| `ninja all` | `disc` + `split` |
| `ninja sizes` | section sizes of the linked ELF next to retail (`full_link.py --report`) |

`ninja -t commands build/recon/game/common/ai.cpp.o` prints the exact commands of one object; `ninja -t cleandead`
deletes outputs of removed sources; `python configure.py --strict-link` makes sections missing from `link_order.txt` a
link error. Not tracked per TU is `build.py`'s compile *logic* (`run_s` / `run_o` code): after changing it, run
`ninja -t clean && ninja`. `NFS4_*` environment variables are read when `build.ninja` is written -- re-run
`configure.py` after changing them.

### One command

```bash
python tools/build_iso.py --no-iso
```

With `ninja` on `PATH` this runs `ninja disc` (writing `build.ninja` first if needed). Otherwise -- or with
`--no-ninja`, `--tolerant`, `--skip-compile`, `--skip-link` -- it runs the three scripts below: compile everything
(strict: any failing file aborts), the production link, and the cut into `build/full_link/disc/`. `--skip-compile`
reuses the objects already in `build/`.

### Step by step (the sequential scripts)

**1. Compile** every translation unit to an ELF object in `build/recon/…`:

```bash
python tools/build.py --skip-asm
```

Per file: `cpp` → `CC1PSX` / `CC1PLPSX` (`-O2`, per-file `-G`) → `maspsx` → GNU `as`. Per-file flags live in
`PER_TU_FLAGS` in `tools/build.py`. To rebuild only some files:

```bash
python tools/build.py --skip-asm --only game/common/stats,frontend/psx/psxfront
```

Set `NFS4_STRICT=1` to make a single failure abort; by default the build keeps going and lists failures at the end.

**2. Link:**

```bash
python tools/full_link.py
```

`tools/gen_natural_ld.py` turns the committed link order `linkers/link_order.txt` into
`build/full_link/nfs4_natural.ld` (generated on every link from the objects actually built; not committed), then GNU ld
links `asm/header.s` and every recon object into `build/full_link/full.elf` (+ `full.map`). The link is strict:
unresolved symbols, duplicate definitions and orphan sections are errors. It prints the section sizes next to retail's:

```
[map] .rdata        0x80010000  0x04797C  0x04797C  +0
[map] .text         0x8005797C  0x0B5358  0x0B5358  +0
...
[map] front.bss     0x80052B38  0x001A10  0x001A10  +0
[sym] __SN_ENTRY_POINT=0x800E402C  __exe_t_size=0x0012E000  ...  _front_objend=0x80054548  _gp=0x8013C54C
```

**3. Cut the two disc files:**

```bash
python tools/elf_to_exe.py --split
```

Writes `build/full_link/nfs4.exe` (the merged image) and `build/full_link/disc/NFS4.EXE` + `FRONT.BIN`, prints their
sha1 against the retail disc and, when `rom/nfs4-f.exe` is present, byte-compares (`--no-compare` skips that):

```
[split] …/disc/NFS4.EXE   1239040 bytes  sha1 c5c60d450bac == retail disc
[split] …/disc/FRONT.BIN   279880 bytes  sha1 d6c5b5d16e55 == retail disc
[cmp] MATCH (byte-identical)
```

`elf_to_exe.py` does not use `objcopy -O binary`: the header sits at load address 0 and the code at `0x8001xxxx`, so a
flat binary would span 2 GB. It takes the 0x800-byte header from the ELF's own `.header` section (`asm/header.s`, whose
pc0 / t_addr / t_size are linker symbols) and copies every loadable section to its address -- the main sections first,
then the overlay's, which land in `bigBuf`, as in `rom/nfs4-f.exe`. `FRONT.BIN` is cut at the linker symbols
`_front_obj` .. `_front_objend`.

### The link order: `linkers/link_order.txt`

One line per input section, grouped by output section, in link order:

```
[main]
.rdata       recon/frontend/psx/bigbuf.c        .rodata
.rdata       recon/frontend/psx/address.c       .rodata
...
.text        recon/syslib/psx/libgpu/FONT.c     .text      pad=16
.text        recon/syslib/psx/libpress/VLC.c    .text      align=16 pad=16
...
[front]
front.rdata  recon/game/common/minfront.cpp     .rodata
...
```

`[main]` is `NFS4.EXE`: the text group `.rdata .text .data .sdata` from `0x80010000` (the PS-X EXE load address) and the
bss group `.sbss .bss` behind it, then the `last` group (`.last`, endcode.cpp's `endofcode`). `[front]` is `FRONT.BIN`:
`front.rdata front.text front.data front.bss` linked over `bigBuf` at `0x80010000`. A section starts right behind the
previous one -- on 4 bytes in `[main]`, on 8 in `[front]` -- and each output section ends on that boundary. Attributes
describe the original objects, never an address:

| attribute | meaning | where |
|---|---|---|
| `pad=16` | the section's size is rounded up to 16 bytes from its own start | 218 sections of 158 Sony library members (PsyQ's assembler padded every section) |
| `align=N` | the section starts on an N-byte boundary | `VLC.obj` `.text` (16), newton.cpp's `static coorddef dummy` (8) |
| `tail=N` | N zero bytes follow the section | `PADENTRY.obj` `.text` (8) |

Input sections ending in `.strip` (functions retail's `/strip` link removed, `LINK_STRIPPED`) or `_legacy` are discarded.
The linker defines the symbols the game uses: `_gp` (= start of `.sdata`), `_bss_obj` / `__last_org` (the range the
startup code clears; the heap starts behind it), `_front_obj` / `_front_objend` (the overlay, read by `address.c`), and
`__exe_t_addr` / `__exe_t_size` for the header. The only numbers in the generated script are the load address
`0x80010000` and the 2048-byte rounding of `t_size`.

**Adding a file**: build it, then add its sections to `link_order.txt` where the object belongs in link order. Until you
do, `full_link.py` appends them to the end of the matching output section and warns (`--strict` makes that an error).
Editing a source needs nothing: if a function grows, everything behind it moves and every reference follows.

### How the natural link reproduces retail

The retail files were linked by SN's SLINK (`/strip`) from EA's link script: game objects in the script's order, the
EA and Sony library members in the order the linker pulled them in, the overlay objects renamed to `front.*` with every
chunk aligned to 8 (`section.8 front.*`). `link_order.txt` is that order (it was read off the retail layout once and is
now just the order -- adding or growing an object moves everything behind it). Route C (removed) had proved the model with
the original tools; reproducing it with GNU ld needed only facts about the original objects, now in the sources:

- three Sony assembler modules start their `.text` with the 8-byte library stamp (`Ps…`): `libc/A63.c`, `libapi/C114.c`,
  `libgte/MSC00.c` (like the `.data` stamps of `FERR`, `PADMAIN`, `SYS`, `LIBMCRD`);
- `2mbyte.c` owns the 4-byte `.sbss` word where the startup code parks `$ra` (`_ra_save`, formerly `D_8013DE5C`), and
  writes the KSEG0 constant as `%hi(0x80000004)` instead of an address symbol;
- the four certificate asm files (`asm/cert/`) reference their own object's data by name -- `mc`, `_mc_present`,
  `_mc_save_cb`, `$LC0`/`$LC5` (LIBMCRD), `_cd_idx`/`_dpcr`/`_dicr` (stcdint), `Font+0x24` (FONT) -- instead of
  `D_<retail address>`, exactly like the section-relative relocations of the original objects.

### Checks to run after a change

- `python tools/elf_to_exe.py --split` -- the sha1 lines say whether both files are still identical to the disc.
- `python tools/linux/fn_sizes.py --all` -- per-function code size against retail (`3522 functions compared, 0 differ`).
- A size change no longer breaks the link: it moves what follows. The `[map]` table of `full_link.py` shows which output
  section changed size.

Pitfall (sequential scripts only): `full_link.py` links whatever objects are in `build/`. After reverting a source file,
rebuild it before linking. Ninja tracks this itself.

The former address-pinned placement (`tools/gen_ld.py` → `linkers/nfs4_recon.ld` with its PROVIDE / `*_extra.json` /
`*.ldfrag` inputs, the splat link `linkers/nfs4.ld` + `asm/data/`, and the tools measured on them: `relink.py`,
`honest_measure.py`, `probe_link.py`, …) has been removed. A splat re-run of `configs/nfs4.yaml` writes `asm/data/` and
the `linkers/nfs4*.ld` / `undefined_*_auto.txt` files again; they are git-ignored and nothing reads them.

### A bootable disc image

`tools/build_iso.py` without `--no-iso` also stages the two files into an extracted disc tree and rebuilds the image
with `mkpsxiso` (`tools/psxiso/`). One-time setup — extract your own disc image:

```bash
tools/psxiso/dumpsxiso.exe -x "build/cd/Need For Speed 4 v9.0" -s "build/cd/Need For Speed 4 v9.0.xml" path/to/NFS4.bin
```

Then:

```bash
python tools/build_iso.py
```

The retail `NFS4.EXE` / `FRONT.BIN` are saved once to `build/cd/orig/`; `--restore` puts them back. The script reads the
finished image back and confirms both files are really on it. `--name` changes the disc folder / XML base name.

## Where things end up

| Path | What |
|---|---|
| `build.ninja`, `build.ninja.d` | generated by `configure.py` (not committed); `build/.ninja_log`, `build/.ninja_deps` are Ninja's state |
| `build/recon/**/*.o` | compiled objects (`.i`, `.s` next to them) |
| `build/asm/header.s.o` | assembled PS-X EXE header |
| `linkers/link_order.txt` | the link order (committed) |
| `build/full_link/nfs4_natural.ld` | linker script generated from it on every link |
| `build/full_link/full.elf`, `full.map` | production link |
| `build/full_link/nfs4.exe` | merged image, equals `rom/nfs4-f.exe` |
| `build/full_link/disc/NFS4.EXE`, `FRONT.BIN` | **the two disc files** |
| `build/cd/<name>.bin`, `.cue` | rebuilt disc image |
