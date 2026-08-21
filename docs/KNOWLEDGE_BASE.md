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
- The accepted 1.06a authored set contains 181 functions / 25,323 bytes in 101
  VC8 match units. The newest whole-corpus retained-source wave added eighty-one
  functions / 11,836 bytes beyond the previous 100-function checkpoint. Candidate
  ranking, current-target IDA/call evidence, and relocation reconciliation only
  establish hypotheses; canonical VC8 zero-difference comparisons establish
  exactness.
- The current origin census has 673 target-backed exclusions: 417 VC8 runtime functions selected from SHA-pinned VC8 SP1 archives, 44 zlib 1.2.3 functions bounded by current-target provenance strings, 19 direct import thunks whose current names/opcodes are attested, 39 Ogg/Vorbis functions whose current candidate bytes are inventory-unique matches of relocation-free COMDATs, and 154 additional Ogg/Vorbis functions whose non-relocation bytes uniquely match relocation-bearing COMDATs re-extracted from the SHA-pinned official Xiph Win32 SDK 1.0.1. The relocated anchors are fail-closed: every relocation must stay inside the candidate boundary, REL32 fields must belong to CALL/JMP/Jcc forms, at least 70% and 24 bytes of each candidate must remain exact non-relocation evidence, the COMDAT tail may contain only alignment bytes, and the fingerprint must be unique across all 4,001 candidates. `config/function-origin-rules.toml` and `scripts/function-origins.py` replay all target/archive checks before materializing the census.

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
- `scripts/rank_retained_exact.py` is the durable migration path for historical
  exact source not represented by old match units. The survey found 152
  historical unconfigured `.cpp` exact hypotheses and could uniquely extract
  147 COFF symbols under the pinned VC8 profiles. Structural score and zero
  non-relocation differences remain ranking evidence, not identity or exactness.
  The `CFileReader::read` / `WriteFile` clone is the reference counterexample.
- The stage-surface array at `0x006FA898` is 0x500 floats / 0x1400 bytes. Current
  stage-geometry helpers legitimately relocate the same symbol with addend
  `0x13FC`, selecting element `0x4FF` at `0x006FBC94`; do not model that last
  element as a separate global.
- Target-specific resource/error strings are part of exact authored recovery. The
  DirectSound secondary-buffer path only became canonical after the retained
  localized error bytes were replaced with the original Japanese 1.06a Shift-JIS
  string; source-language data must follow the canonical executable, not a
  translated release.
- Current semantic globals should replace retained old-target magic absolute
  addresses when the 1.06a target proves identity. `update_common_fighter_state_window`
  now references the verified `g_battle_input_gate` instead of `0x006e4e28`, and
  `emit_effect_at_collision_center` uses the verified `g_effect_sink` instead of
  `0x006e6250`; both natural C++ recoveries compile exact under the current target.
- Preserve a shared callee's proven ABI when only one caller consumes a narrower
  result. `is_y_at_or_below_stage_surface` remains an exact `int`-returning helper;
  `update_common_fighter_state_window` reproduces the current `test al, al` by
  narrowing at the call site. Do not mutate a return type merely because x86 name
  decoration cannot expose that mistake.
- One current address can support multiple truthful narrow semantic views.
  `0x006FA21C` is independently used as the render-mode service by exact UI code
  and as the static phase service by exact battle code. Keep the views distinct in
  source while address-validating the shared object identity.
- DirectSoundGlobals begins at `0x00703858`, with primary/direct-sound/listener
  pointers at addends `0/4/8`. A comparator mismatch caught the incorrect model
  that treated the `direct_sound` field at `0x0070385C` as the object base.
  `shutdown_direct_sound` independently exercises all three addends in listener,
  primary, device order and now matches 82/82; this is positive evidence for the
  full three-field layout. The unrelated shutdown cluster at
  `0x007036BC..0x007036C4` remains separate until independently proved otherwise.
- Exact byte recovery does not prove authored ownership. The retained
  `create_collision_list_node` source has a zero-non-relocation-difference
  51-byte candidate at `0x00421F30`, but current xrefs show that helper is shared
  broadly across engine and roster container code. It remains origin-review
  pending. By contrast, `create_collision_list_sentinel` at `0x00435E50` is
  authored-accepted because exact `initialize_collision_list` stores its result
  as the sentinel and accepted roster units independently resolve the same
  helper; fresh VC8 is 26/26 exact.
- Nearby vtables must not be conflated by address proximity. `ResultList` uses
  the vtable at `0x006C2058`, while current `CMenuResult` destruction writes the
  distinct vtable at `0x006C2070`; its slot `+8` points to the accepted 43-byte
  `CMenuResult::update` at `0x00447560`.
- Current indexed event dispatch uses the 128-entry handle table at `0x006FCA98`,
  service object at `0x00702288`, and dispatch helper `0x00401D50`. The 28-byte
  `dispatch_indexed_event` wrapper and multiple accepted callers agree on those
  identities, so later event/audio work should reuse them rather than rediscover
  old-target globals.
- The current input-selection global map is now exact-backed: player records at
  `0x006FBF20` with stride `0x33C`, source bytes at `0x006FBD38`, selected-input
  pointers at `0x006FBD3C`, session option at `0x006FBD44`, network-session
  pointer at `0x006FBD5C`, player2 input storage at `0x006FBDD0`, and combined
  menu input at `0x006FCF80`. The combined counter accessor is the same object at
  addend `+0x38`, not a separate global. Replacing retained 1.06 magic absolutes
  with these semantic externs made ten accessors naturally compile exact without
  changing control flow.
- The battle phase wrappers at `0x0046AF90` and `0x0046AFA0` are a
  reference normalized-clone tie that current tail destinations resolve. Both
  load exact-backed fighter-phase context `0x006FBC9C`, but `0x0046AF90` jumps
  to LTCG entry `0x00464630`, whose five passes are the action/owned-object
  callback phase, while `0x0046AFA0` jumps to `0x00464780`, whose three passes
  are position, transient-status, and timer cleanup. Both wrappers are 11/11
  exact after semantic global migration.
- A source-level callee may survive in the linked target only as an internal LTCG
  entry. It is valid to map a REL32 relocation to that observed entry when its
  body semantics establish identity; do not create or claim a standalone IDA
  function boundary merely to make the comparator happy. The two battle phase
  wrappers above are the reference case.
- `run_post_update_callbacks_and_global_state @ 0x0046AFB0` is 51/51 exact after
  replacing stale 1.06 globals with exact-backed `g_info_manager` at
  `0x006FBCA8` and shared battle-setup state at `0x006FBCC0`; its current helper
  destinations are `0x00426BB0` and `0x00426DF0`.
- Structural clone ties need class/caller evidence, not old address order. The
  367-byte Yukari mirrored-command gate at `0x0058C170` was accepted only after
  its sole current fighter dispatcher, nearby exact Yukari anchors, and all five
  current REL32 destinations established the specialization; it then compared
  367/367 exact.
- Source-owned vtable anchor data must migrate with the current class identity.
  The title/UI color anchor now points at current `IColor` scalar-deleting
  destructor `0x0040AE80`; that semantic correction makes the `/GS` CTitle
  destructor compare 161/161 exact.
- `process_fighter_transient_status` at `0x0045E3D0` demonstrates acceptable
  natural source shaping: an equivalent C++ conditional expression for the
  32-byte normalization loop restored the target VC8 schedule and all 301 bytes
  compare exactly. By contrast, shared-tail/LTCG register-allocation blockers
  remain blocked rather than being forced with assembly or register tricks.
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
- Accepted boundaries and authored/library origins for the remaining 3,147
  provisional candidates.
- The complete authored denominator needed to measure the 95% function and byte
  goals honestly.
- Which additional retained 1.06 source implementations remain semantically
  identical or naturally reconstructable in 1.06a.

Add reusable facts here only after they survive a target-backed bounded
investigation. Detailed compiler- and comparator-shaping patterns belong in
`docs/BUILD_MATCHING.md` once supported by reproducible 1.06a examples.

## Current battle globals

`config/known-globals.csv` now carries the current-target semantic identities
that have survived exact authored recovery: the battle input gate, match id,
stage-surface array, round/transition bytes, pair state, fighter phase context,
object/setup/effect/info managers, battle phase block, scenario-event map, and
title resource manager. These mappings come from current IDA semantics plus
accepted zero-difference functions; they are not cross-version delta guesses.

- The 237-byte roster object-manager spawn clone family is now class-disambiguated
  by current allocator-chain vtable writes, not address order. Fourteen classes
  represented by `RosterObjectSpawns.cpp` are canonical exact; the fifteenth,
  Sakuya, is positively identified but remains non-exact in its separate source.

- The 103-byte `TObjectManagerBase` ctor structural family contains twenty current
  clones. Current template-vtable writes separate five effect/UI instantiations
  from fifteen roster-character specializations; all fifteen roster ctors are
  canonical exact under the retained `/GS` profile.
