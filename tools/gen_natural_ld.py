#!/usr/bin/env python3
"""gen_natural_ld.py -- linkers/link_order.txt -> build/full_link/nfs4_natural.ld (Route A, natural link).

The retail executable was linked by SN's linker from a list of objects; nothing in that link
was placed at a fixed address except the load address itself.  This generator rebuilds that
kind of link for GNU ld:

  * every input section listed in linkers/link_order.txt goes into its output section in the
    listed order, directly behind the previous one -- the addresses follow from the order and
    from the sizes of the objects actually built (edit a source and everything after it moves);
  * main sections start every chunk on 4 bytes (SUBALIGN(4)), the front-end overlay on 8
    (SN's `section.8 front.*`); the few per-chunk properties of the original objects are
    attributes in the order file: `pad=16` (Sony members pad each section to 16), `align=N`,
    `tail=N`;
  * the only numbers in the script are the PS-X EXE load address (0x80010000) -- where the text
    group starts and where the front-end overlay is loaded (over bigBuf) -- and the 2048-byte
    rounding of the EXE's t_size;
  * linker-defined symbols the game uses: _gp (start of .sdata), _bss_obj / __last_org (the
    BSS range the startup code clears), _front_obj / _front_objend (the overlay's extent), and
    for asm/header.s: __exe_t_addr / __exe_t_size.

Objects that are built but not listed (a new TU) are not lost: their sections are appended to
the end of the matching output section with a warning -- list them in the order file.

usage: python tools/gen_natural_ld.py [--out PATH] [--rsp PATH] [--strict]
       (--rsp: also write the linker's object list; --strict: unlisted sections are an error instead of a warning)
"""
import argparse
import fnmatch
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ORDER = ROOT / 'linkers' / 'link_order.txt'
OUT = ROOT / 'build' / 'full_link' / 'nfs4_natural.ld'
HEADER_OBJ = 'build/asm/header.s.o'

LOAD_ADDR = 0x80010000      # PS-X EXE t_addr; also the front-end overlay's load address (bigBuf)
FRONT_LMA = 0x01000000      # any LMA clear of the main image: FRONT.BIN is cut out by VMA (elf_to_exe.py)

MAIN_SECTIONS = ['.rdata', '.text', '.data', '.sdata', '.sbss', '.bss']
FRONT_SECTIONS = ['front.rdata', 'front.text', 'front.data', 'front.bss']
NOBITS_OUT = {'.sbss', '.bss', 'front.bss'}
GROUP_ALIGN = {'main': 4, 'front': 8}

# input sections nobody links: retail's /strip removed the functions, *_legacy are superseded
# data copies, the rest is assembler/compiler bookkeeping
DISCARD = ['*.strip', '*_legacy', '.rel.dyn', '.pdr', '.reginfo', '.MIPS.abiflags', '.gnu.attributes',
           '.comment', '.mdebug*', '.note*', '.gptab*']


def elf_sections(path):
    """[(name, type, flags, size)] of a 32-bit little-endian ELF object."""
    d = path.read_bytes()
    shoff, = struct.unpack_from('<I', d, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from('<HHH', d, 0x2E)
    hdrs = [struct.unpack_from('<10I', d, shoff + i * shentsize) for i in range(shnum)]
    stro = hdrs[shstrndx][4]
    out = []
    for h in hdrs[1:]:
        end = d.index(b'\0', stro + h[0])
        out.append((d[stro + h[0]:end].decode('ascii', 'replace'), h[1], h[2], h[5]))
    return out


def alloc_sections(path):
    """{name: size} of the allocated PROGBITS/NOBITS sections with content."""
    return {n: sz for n, t, fl, sz in elf_sections(path) if t in (1, 8) and fl & 2 and sz}


def discarded(sec):
    return any(fnmatch.fnmatchcase(sec, p) for p in DISCARD)


def read_order(path=None):
    """[(group, outsec, src, insec, attrs{})] in file order."""
    path = path or ORDER
    units, group = [], None
    for ln_no, raw in enumerate(path.read_text().splitlines(), 1):
        ln = raw.split('#', 1)[0].strip()
        if not ln:
            continue
        if ln.startswith('[') and ln.endswith(']'):
            group = ln[1:-1]
            if group not in GROUP_ALIGN:
                sys.exit(f'{path.name}:{ln_no}: unknown group [{group}]')
            continue
        f = ln.split()
        if group is None or len(f) < 3:
            sys.exit(f'{path.name}:{ln_no}: expected "<outsec> <source> <insec> [attrs]"')
        outsec, src, insec = f[:3]
        allowed = MAIN_SECTIONS if group == 'main' else FRONT_SECTIONS
        if outsec not in allowed:
            sys.exit(f'{path.name}:{ln_no}: output section {outsec} is not in [{group}]')
        attrs = {}
        for a in f[3:]:
            k, _, v = a.partition('=')
            if k not in ('pad', 'align', 'tail') or not v.isdigit():
                sys.exit(f'{path.name}:{ln_no}: bad attribute {a!r}')
            attrs[k] = int(v)
        units.append((group, outsec, src, insec, attrs))
    return units


def recon_objects():
    """Objects of every main recon TU (build.py's rule: is_main_recon, and for C is_tu), in link-command order."""
    sys.path.insert(0, str(ROOT / 'tools'))
    import build  # noqa: E402  (the TU rules live there)
    srcs = ([s for s in sorted((ROOT / 'recon').rglob('*.cpp')) if build.is_main_recon(s)] +
            [s for s in sorted((ROOT / 'recon').rglob('*.c')) if build.is_tu(s) and build.is_main_recon(s)])
    objs = []
    for s in srcs:
        o = ROOT / 'build' / (s.relative_to(ROOT).as_posix() + '.o')
        if o.is_file():
            objs.append(o.relative_to(ROOT).as_posix())
    return objs


def default_outsec(group, insec):
    base = insec.split('.')[1] if insec.count('.') >= 1 else insec
    m = {'rodata': 'rdata', 'rdata': 'rdata', 'text': 'text', 'data': 'data', 'sdata': 'sdata',
         'sbss': 'sbss', 'bss': 'bss'}.get(base)
    if m is None:
        return None
    if group == 'front':
        m = {'sdata': 'data', 'sbss': 'bss'}.get(m, m)
        return 'front.' + m
    return '.' + m


def generate(strict=False):
    units = read_order()
    objs = recon_objects()
    sizes = {}

    def size_of(obj, sec):
        if obj not in sizes:
            sizes[obj] = alloc_sections(ROOT / obj)
        return sizes[obj].get(sec, 0)

    # ---- missing objects / unlisted sections
    listed = {}
    for g, o, src, sec, a in units:
        listed.setdefault('build/' + src + '.o', {})[sec] = g
    problems = []
    for obj in listed:
        if not (ROOT / obj).is_file():
            problems.append(f'listed object not built: {obj}')
    extra = []                                   # (group, outsec, obj, sec)
    for obj in objs:
        have = listed.get(obj, {})
        group = 'front' if 'front' in have.values() else 'main'
        for sec, sz in sorted(alloc_sections(ROOT / obj).items()):
            if sec in have or discarded(sec):
                continue
            outsec = default_outsec(group, sec)
            if outsec is None:
                problems.append(f'{obj}: section {sec} has no output section')
                continue
            extra.append((group, outsec, obj, sec))
    for g, o, obj, sec in extra:
        print(f'[gen_natural_ld] WARNING unlisted: {obj} {sec} -> appended to {o} '
              f'(add it to linkers/link_order.txt)', file=sys.stderr)
    if problems or (strict and extra):
        for p in problems:
            print(f'[gen_natural_ld] ERROR {p}', file=sys.stderr)
        sys.exit(1)

    # ---- emit
    body = {s: [] for s in MAIN_SECTIONS + FRONT_SECTIONS}
    for g, outsec, src, sec, a in units:
        obj = 'build/' + src + '.o'
        lines = body[outsec]
        if 'align' in a:
            lines.append(f'. = ALIGN({a["align"]});')
        lines.append(f'{obj}({sec})')
        n = size_of(obj, sec)
        if 'pad' in a:
            p = -n % a['pad']
            if p:
                lines.append(f'. += {p};   /* pad={a["pad"]} */')
        if 'tail' in a:
            lines.append(f'. += {a["tail"]};   /* tail */')
    for g, outsec, obj, sec in extra:
        body[outsec].append(f'{obj}({sec})   /* UNLISTED */')
    bigbuf = 'build/recon/frontend/psx/bigbuf.c.o'
    bigbuf_size = size_of(bigbuf, '.rodata')

    def block(name, lines, addr, align, lma=None):
        typ = ' (NOLOAD)' if name in NOBITS_OUT else ''
        at = f' AT({lma})' if lma else ''
        out = [f'    {name} {addr}{typ} :{at} SUBALIGN({align})', '    {']
        out += ['        ' + l for l in lines]
        out += [f'        . = ALIGN({align});   /* SN rounds every chunk, the last one too */', '    }']
        return out

    L = ['/* GENERATED by tools/gen_natural_ld.py from linkers/link_order.txt -- do not edit.',
         ' * Natural link: input sections follow each other in the listed order; no object is',
         ' * placed at an address of its own. */',
         'OUTPUT_ARCH(mips)',
         'ENTRY(__SN_ENTRY_POINT)',
         'SECTIONS',
         '{',
         '    .header 0 : AT(0) { ' + HEADER_OBJ + '(.data) }',
         f'    __exe_t_addr = 0x{LOAD_ADDR:08X};',
         '    . = __exe_t_addr;']
    first = True
    for s in MAIN_SECTIONS:
        if s == '.sbss':
            L += ['    __text_group_end = .;',
                  '    __exe_t_size = ALIGN(__text_group_end - __exe_t_addr, 0x800);']
        L += block(s, body[s], '.' if first else 'ALIGN(4)', 4)
        first = False
        if s == '.sdata':
            L.append('    _gp = ADDR(.sdata);')
    L += ['    _bss_obj = ADDR(.sbss);',
          '    /* the `last` group (EA\'s script: `last group bss` behind .bss): endcode.cpp\'s marker',
          '     * `endofcode`; the startup code clears [_bss_obj, __last_org) and uses the rest as heap */',
          '    .last ALIGN(4) (NOLOAD) : { __last_obj = .; *(.last) }',
          '    __last_org = .;',
          '    _end = .;']
    lma = None
    for i, s in enumerate(FRONT_SECTIONS):
        addr = '__exe_t_addr' if i == 0 else 'ALIGN(8)'
        lma = f'0x{FRONT_LMA:08X}' if i == 0 else f'LOADADDR({FRONT_SECTIONS[i-1]}) + SIZEOF({FRONT_SECTIONS[i-1]})'
        L += block(s, body[s], addr, 8, lma)
    L += ['    _front_obj = ADDR(front.rdata);',
          '    _front_objend = ADDR(front.bss) + SIZEOF(front.bss);',
          f'    ASSERT(_front_objend - _front_obj <= {bigbuf_size}, "FRONT.BIN overlay no longer fits bigBuf")',
          '    ASSERT(_front_obj == bigBuf, "the overlay must load at bigBuf")',
          '    /DISCARD/ : { ' + ' '.join(f'*({p})' for p in DISCARD) + ' }',
          '    /* every listed section is placed above; what is left of the inputs are empty sections',
          '     * (generate() has already appended or rejected anything with content) */',
          '    .leftovers (NOLOAD) : { *(.text .rodata .rodata.* .rdata .data .data.* .sdata .sdata.* '
          '.sbss .sbss.* .bss .bss.* .scommon COMMON) }',
          '    ASSERT(SIZEOF(.leftovers) == 0, "an unlisted input section with content reached .leftovers")',
          '}']
    return '\n'.join(L) + '\n', ['build/asm/header.s.o'] + objs


def write_if_changed(path, text):
    """Write `text` unless the file already holds it (Ninja's restat then skips the relink)."""
    path = Path(path)
    if not path.is_file() or path.read_text() != text:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)


def write_rsp(path, objs):
    """The object list for `ld @path` (one quoted path per line, link-command order)."""
    write_if_changed(path, '\n'.join(f'"{o}"' for o in objs) + '\n')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--out', type=Path, default=OUT)
    ap.add_argument('--rsp', type=Path)
    ap.add_argument('--strict', action='store_true')
    a = ap.parse_args()
    text, objs = generate(a.strict)
    a.out = a.out if a.out.is_absolute() else ROOT / a.out
    write_if_changed(a.out, text)
    if a.rsp:
        write_rsp(a.rsp if a.rsp.is_absolute() else ROOT / a.rsp, objs)
    print(f'[gen_natural_ld] {a.out.relative_to(ROOT).as_posix()}: {len(objs)} objects')


if __name__ == '__main__':
    main()
