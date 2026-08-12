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
