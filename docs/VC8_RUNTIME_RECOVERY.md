# VC8 runtime recovery

TH105 statically links the VC8 SP1 multithreaded runtime. The repository's
pinned toolchain contains the original `libcmt.lib` and `libcpmt.lib` archives,
so runtime recovery should replay their COFF members before attempting manual
decompilation or recompilation.

The extractor fails closed on both archive identity and i386 COFF identity:

```bash
python3 scripts/extract-msvc-library-object.py \
  --library libcmt --object build/intel/mt_obj/memset.obj \
  --output build/match-units/vc8_libcmt_memset.obj
```

Archive SHA-256 values are tied to the `msvc8_sp1` commit in
`config/tools.lock.toml`. The archives and extracted objects stay under
`.tools/` and `build/`; they must not be committed.

Use archive symbols and ledger sizes for a breadth-first candidate map, then
apply the same strict relocation rules as other library islands. A symbol or
size match is not acceptance. Every selected function needs 100% comparison
after all REL32 and DIR32 destinations are independently verified. Count a
linked target address once even if multiple archive members expose contextual
aliases for it.

Exact runtime rows retain `status=library`. Report them in reproducible-library
and combined progress, never in authored-game matching.

## Accepted breadth wave (2026-08-12)

Three disjoint address scans over the pinned `libcmt.lib` produced 74
symbol-unambiguous strict matches and 6,862 function bytes. They are grouped by
archive member into 58 `msvc_prebuilt` units in `config/match-units.toml`.
Together with the earlier runtime anchors and the dependency expansion below,
108 runtime functions and 19,228 bytes are now reproducible.

Every accepted unit was re-extracted through the repository build driver and
all 74 comparisons returned `result=exact`. Reproduce an individual unit with:

```bash
python3 scripts/build.py --unit vc8-libcmt-memchr --compare --json
python3 scripts/build.py --unit vc8-sp1-libcmt-p4-memcpy --compare --json
python3 scripts/build.py --unit vc8_sp1_libcmt_mantold --compare --json
```

The scan deliberately excluded byte-identical functions with more than one
possible COFF symbol. Register-ABI helpers such as `__alldiv`, `__chkstk`, EH
prologues, and x87 helpers are named from exact symbols but are not represented
as ordinary C-callable contracts. The `source_file` ledger field points to this
provenance document because the proprietary CRT source is not vendored; the
archive member and SHA-256 remain authoritative in each match unit.

## Dependency expansion: small-block heap and floating exceptions

The next dependency-first pass connected six target-unique functions and 2,767
bytes from `sbheap.obj` and `fpexcept.obj`. The accepted set contains the small
block heap initialization, allocation, region/group growth, and release core,
plus `__raise_exc_ex`. These are replayed through the existing canonical object
units rather than counted as new archive units.

The small-block heap object relocates into the zero-filled virtual tail of the
PE `.data` section. Acceptance therefore audits both the section header
(`VirtualSize=0x1e5a8`, `SizeOfRawData=0x15000`) and each linked virtual address;
an empty raw-file read is not evidence that the address is invalid. The import
slots were separately checked against the target PE bytes. Reproduce both
groups with:

```bash
python3 scripts/build.py --unit vc8-sp1-libcmt-sbheap --compare --json
python3 scripts/build.py --unit vc8-sp1-libcmt-fpexcept --compare --json
```

The following low-level I/O and decimal-format dependency pass adds five more
target-unique functions and 4,137 bytes: `__write_nolock`,
`__lseeki64_nolock`, `__isatty`, `__putwch_nolock`, and `_$I10_OUTPUT`.
Canonical replay uses five distinct archive members. Three byte-exact targets
remain excluded because the archive presents competing symbols (`__write` /
`__locking` / `__lseek`, and two `__ld12tod` / `__ld12tof` pairs).

The floating-point control dependency chain adds four functions and 994 bytes:
`__SEH_prolog4`, `__set_statfp`, `___set_fpsr_sse2`, and `__control87`.
`__SEH_prolog4` is accepted only after auditing its absolute handler and
security-cookie addresses; the dependent fpctrl and ieee87 objects then replay
without unresolved edges.

The next I/O and conversion pass adds seven functions and 3,324 bytes. Four
`osfinfo.obj` handle helpers extend the low-level write graph. Read-only Ghidra
callers identify the otherwise byte-ambiguous wrapper at `0x0068AF27` as
`__write`; its body delegates to the already exact three-argument
`__write_nolock`. The two 1,346-byte intrinsic conversions are distinguished
by their relocation tables: `0x0068DCC0` references `_DoubleFormat`, while
`0x0068E202` references `_FloatFormat`. Cross-assigning either COFF symbol
fails the strict literal audit.
