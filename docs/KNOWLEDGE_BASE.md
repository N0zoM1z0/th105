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
  and sizes are provisional analysis output.

## Repository decisions

- Adopt TH08's separation of mapping, source presence, exact matches, library
  classification, public CI, current handoff, and cold exact replay.
- Retain `functions.csv` plus `function-origins.csv` as a TH105-specific layer
  because static libraries, compiler code, thunks/funclets, and LTCG make a
  flat authored mapping unsafe.
- Keep the old source tree for archaeology but count none of it until a 1.06a
  mapping and semantic audit justify `implemented.csv`.
- Use one writable reconstruction session. Claims remain header-only.
- Use IDA Pro exclusively after exact attestation. There is no Ghidra fallback.
- Keep IDA client scripts independent of an interactive Python environment:
  they pin `mcp==1.26.0` and self-bootstrap it through `uv --no-project` when
  the selected interpreter does not provide it. This covers systemd/GPT-web
  login shells without modifying global Python packages.

## Unknown

- Exact VC8 service pack and compiler/linker flags used for every object.
- Original translation-unit partition and which classes/functions underwent
  LTCG transformation.
- Accepted boundaries and authored/library origins for all 4,001 candidates.
- Which retained 1.06 source implementations remain semantically identical in
  1.06a.
- First reproducible 1.06a authored exact unit.

Add reusable facts here only after they survive a target-backed bounded
investigation. Detailed compiler-shaping patterns belong in the matching skill
only after at least one reproducible 1.06a example exists.
