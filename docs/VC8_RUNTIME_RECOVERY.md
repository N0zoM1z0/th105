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
Together with the earlier runtime anchors, 86 runtime functions and 8,006
bytes are now reproducible.

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
