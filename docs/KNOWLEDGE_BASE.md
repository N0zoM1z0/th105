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
- The accepted 1.06a authored set contains 62 functions / 5,821 bytes in 43
  VC8 match units. The structural-remap waves added fifteen functions / 2,517 bytes after
  structural-instruction fingerprinting selected candidates and current-target
  IDA/call evidence reconciled their relocations; canonical VC8 comparisons,
  not the fingerprints, established exactness.
- The current origin census also has 480 target-backed exclusions: 417 VC8 runtime functions selected from SHA-pinned VC8 SP1 archives, 44 zlib 1.2.3 functions bounded by current-target provenance strings, and 19 direct import thunks whose current names/opcodes are attested. `config/function-origin-rules.toml` is fail-closed on expected counts/bytes and `scripts/function-origins.py` materializes the census only after target/archive identity checks.

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
- A normalized VC8 instruction/operand fingerprint of retained exact source is
  useful for *prioritizing* 1.06a candidates when raw bytes changed. Normalize
  relocation/address-sensitive operands only, then independently reconcile the
  candidate boundary and current-target callees before comparing. Template and
  clone families can have identical normalized signatures, so structural ties
  must remain unresolved until class/xref/relocation evidence disambiguates
  them.
- Current IDA vtable names can close DIR32 constructor blockers when paired
  with exact target bytes. The `AttackObject` and `CharacterObject` constructors
  were accepted only after their 1.06a vtable destinations (`0x006C2B3C` and
  `0x006C400C`) were recorded in the relocation allowlist and the fresh VC8
  comparison became zero-difference.
- A historical exact ledger boundary may itself be incomplete. The current
  `BattleController_dispatch_battle_state_frame` body is 535 bytes and fresh VC8
  matches all 535; the old 529-byte ledger stopped immediately before the final
  six-byte epilogue. Treat size deltas as boundary questions before assuming a
  source-level patch.
- Never use bytes that happen to occupy file padding beyond a PE section's raw
  initialized data as proof of a BSS/global variable's contents. Keep such
  DIR32 candidates blocked until address/storage identity can be represented
  truthfully by the comparator.
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
