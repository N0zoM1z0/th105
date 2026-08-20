# Verified knowledge base

This is the small stable layer that new sessions should load before historical
notes or source hypotheses.

## Observed

- The canonical target is the original Japanese 1.06a executable described in
  `config/target.toml`; it is the payload named `app/th105.exe` in the official
  updater.
- The official payload and the selected game-directory `th105.exe` are
  byte-identical. The sibling `th105c.exe` is the older 1.06 binary and is not
  an acceptable substitute.
- The PE is x86, image base `0x00400000`, entry `0x0068B9D2`, with stripped
  relocations and Microsoft linker 8.0.
- Rich-header records point to compiler build 50727 and include 42 C++ LTCG
  inputs. This supports the VC8 family and warns against assuming independent
  object boundaries.
- The current IDA database exposes 4,001 function candidates. Their auto-names
  and unreviewed sizes remain provisional analysis output.
- The first accepted 1.06a authored wave contains 47 functions / 3,304 bytes in
  28 VC8 match units. A cold `scripts/verify-exact-units.py --all` replay passes
  all 47 with zero differences.

## Repository decisions

- Adopt TH08's separation of mapping, source presence, exact matches, library
  classification, public CI, current handoff, and cold exact replay.
- Retain `functions.csv` plus `function-origins.csv` as a TH105-specific layer
  because static libraries, compiler code, thunks/funclets, and LTCG make a
  flat authored mapping unsafe.
- Retained 1.06 source is archaeology and a hypothesis corpus. It counts only
  after a current 1.06a mapping, semantic audit, reproducible VC8 unit, and
  canonical exact comparison justify the corresponding ledgers.
- Cross-version raw-byte identity is a prioritization signal, never match proof.
  The accepted 47-function wave came from raw-identical candidates, but every
  function was freshly compiled and zero-diff compared against 1.06a before
  promotion.
- Do not infer current REL32 callees solely by applying an address delta from
  1.06. A failed `load_spell_data` probe demonstrated that an independently
  moved callee can violate the surrounding delta; current IDA disassembly gave
  the correct 1.06a target `0x00434300`, after which the canonical comparison
  became exact.
- A durable semantic mapping name and the COFF `symbol_base` used by the exact
  comparator may differ. Keep semantic names stable in the ledgers and use the
  actual compiled symbol for object extraction.
- Use one writable reconstruction session. Claims remain header-only.
- Use IDA Pro exclusively after exact attestation. There is no Ghidra fallback.
- Keep IDA client scripts independent of an interactive Python environment:
  they pin `mcp==1.26.0` and self-bootstrap it through `uv --no-project` when
  the selected interpreter does not provide it. This covers systemd/GPT-web
  login shells without modifying global Python packages.

## Unknown

- Exact VC8 service pack and compiler/linker flags used for every original
  object, despite the current probe profile reproducing the accepted wave.
- Original translation-unit partition and which classes/functions underwent
  LTCG transformation.
- Accepted boundaries and authored/library origins for the remaining 3,954
  provisional candidates.
- The complete authored denominator needed to measure the 95% function and byte
  goals honestly.
- Which additional retained 1.06 source implementations remain semantically
  identical or naturally reconstructable in 1.06a.

Add reusable facts here only after they survive a target-backed bounded
investigation. Detailed compiler- and comparator-shaping patterns belong in
`docs/BUILD_MATCHING.md` once supported by reproducible 1.06a examples.
