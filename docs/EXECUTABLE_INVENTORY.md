# Whole-executable reconstruction inventory

This document answers a different question from `RECONSTRUCTION_MAP.md`.
The reconstruction map is an unlock graph for important gameplay; this file
tracks what the complete executable contains, which rows are authored work,
which rows are compiler/runtime/third-party output, and which areas still need
origin or subsystem classification.

The machine-readable sources are:

- `config/functions.csv`: accepted boundaries and reconstruction status;
- `config/function-origin-rules.toml`: audited, fail-closed provenance rules;
- `config/function-origins.csv`: one origin row for every ledger address;
- `config/modules.toml`: reconstruction subsystem vocabulary.

Run `python3 scripts/function-origins.py --check` before using the census.  A
rule is rejected if its selected function count or byte total changes.  This
prevents a later inventory refresh from silently widening a library range.

## Why the original percentage was misleading

At the start of the 2026-08-12 audit, the ledger contained 4,838 functions:

| Status | Functions | Function bytes |
| --- | ---: | ---: |
| `unclassified` | 4,136 | 2,250,539 |
| `identified` | 131 | 20,116 |
| `decompiled` | 179 | 285,703 |
| `implemented` | 131 | 49,554 |
| `compiles` | 3 | 428 |
| `matching` | 209 | 28,248 |
| `library` | 49 | 7,528 |

The old progress denominator treated every non-`library` row as authored.
That included import jump stubs, statically linked VC8 CRT, C++ exception
funclets, zlib, and Xiph codec code.  It therefore reported 209/4,789 even
though most of those support rows should never be reconstructed by hand.

The first evidence-backed provenance pass now excludes 1,861 rows and leaves
2,977 non-library rows.  It reports three separate populations rather than
pretending the unresolved population is authored:

- confirmed authored: 650 rows;
- confirmed non-authored: 1,861 rows;
- origin review: 2,327 rows.

The confirmed-authored population is a lower bound, not a new final
denominator.  Review rows remain outside that metric until evidence decides
their origin.  `docs/PROGRESS.md` retains the legacy non-library metric so the
transition is visible.

## Audited non-authored islands

### Static third-party libraries

| Selector | Rows | Bytes | Evidence and limit |
| --- | ---: | ---: | --- |
| `0x00664FA0..0x0066AC2D` | 44 | 21,553 | Target has the zlib 1.2.3 version string and `inflateReset`, `inflateInit2`, `inflate`, and `inflate_fast` fingerprints. |
| `0x0066BFD0..0x0067AFCF` | 151 | 52,055 | Static libogg/libvorbis/libvorbisfile cluster anchored by `ov_clear`, `ov_open_callbacks`, `ov_info`, `ov_time_seek`, `ov_time_tell`, and `ov_read`. The exact Xiph release is not yet established. |

The first audit hypothesis incorrectly treated `0x00662F80..0x0067AFCF` as
one codec island.  Read-only IDA call graphs disproved it: the prefix contains
character behavior, renderer helpers, and `WinMain` at `0x00664C20`.  Those
game rows remain authored/review work.  Library classification must use the
audited row set, not address adjacency.

The zlib provenance is additionally supported by the official
[zlib 1.2.3 source tag](https://github.com/madler/zlib/tree/v1.2.3). Xiph API
and cluster provenance is supported by the official
[libogg](https://github.com/xiph/ogg) and
[libvorbis](https://github.com/xiph/vorbis) repositories; external source is
supporting provenance, never target-instruction authority.

### VC8 runtime and compiler output

| Selector | Rows | Bytes | Origin |
| --- | ---: | ---: | --- |
| `0x0067B059..0x00690305` | 455 | 72,567 | static VC8 CRT/runtime core |
| `0x006A3DE0` | 1 | 31 | VC8 `__allshl` helper |
| `Unwind@*` in `0x006A3E00..0x006AB275` | 1,134 | 13,390 | compiler-generated EH cleanup funclets |
| `Catch_All@*` in the mixed Boost island | 12 | 208 | compiler-generated catch tails |
| `0x006AB4A0` | 1 | 12 | compiler-generated `atexit` registration wrapper |

The CRT core is anchored by supported identities including
`__CxxFrameHandler3`, CRT startup, `malloc`, `qsort`, `gmtime64_s`, the VC8
small-block heap, low-level I/O, and `strdup`.  The Unwind rows are referenced
by EH metadata and contain tiny cleanup/tail-jump bodies owned by parent C++
functions.  They are link output, not independent authored source routines.

Do not extend the CRT rule through `0x006A3DCF`.  The intervening 342-row
island contains Boost RTTI and templates but also wrappers that call project
functions in `0x0044xxxx`.  It remains origin review until a dedicated Boost
provenance pass separates library/template bodies from game adapters.

### Import thunks

Twenty-one audited rows are six-byte `FF 25` IAT jumps:

- five IMM32 thunks at `0x0066AC2E..0x0066AC4B`;
- one DirectInput8 thunk at `0x0066BC50`;
- fifteen D3DX9/D3D9/WS2_32 thunks at `0x0067AFD0..0x0067B024`.

They are recorded as `origin=import_thunk` and `status=library`.  The adjacent
`0x0067B02F/0x0067B03D` rows are VC8 `type_info` destructors, not imports.

## Current subsystem coverage

Subsystem assignments are not yet complete.  Before this census, all 4,136
unclassified ledger rows had an empty module, so module totals described only
functions already touched by agents.  The current census safely assigns
provenance to the audited islands and to evidence-backed authored ledger rows,
but 2,327 rows remain `review`.

The principal authored gaps are:

| Subsystem | Existing foothold | Large remaining area |
| --- | --- | --- |
| Characters | RTTI/vtables, command gates, action-change, input, CPU, lifecycle/event, object-manager clone families | Fifteen `+0x28` action-state roots, fifteen owned-object behavior monoliths, and real source bodies for the breadth manifests |
| Battle simulation | Core frame controller, fighter phases, collision/hit/score contracts | Outer battle states, effects, weather, HUD/stage integration, and exact shaping of implemented roots |
| Spell cards | Shared data/parser/runtime dependencies mapped | Complete PAT/parser source, resource lifetime, HUD integration, and roster spell fan-out |
| Engine/scenes | Main loop and selected scene hooks | Full scene registry, transitions, loading, local/server/client/watch flows |
| Render/animation | Selected sprite/effect constructors | D3D device, render queues, textures, fonts, design/PAT/animation runtime |
| Assets/filesystem | Selected readers and loaders | Package/archive, caching, text/CSV, texture and resource ownership |
| UI/profile | Scenario/select/result/profile/title slices | Menu/design tree, HUD, deck/stage/weather screens, shared layout ABI |
| Input/replay | Logical input and selected synchronized paths | Device lifecycle, mappings, recording/playback, serialization and battle sync |
| Network | One exact session leaf and a root | Winsock lifecycle, protocol packets, lobby, client/server/watch state machines |
| Audio | DirectSound and Ogg wrapper slice | High-level BGM/SFX managers and scene/resource integration |
| Script/story | RTTI seeds | Command factory, interpreter, story and ending flow |
| Platform/bootstrap | `WinMain` now located | Window loop, timing, global services, startup/shutdown and static initialization |

Game-owned framework code remains authored work.  Only compiler-generated,
VC8 runtime, import, and proven third-party implementations are excluded.

## Giant-byte frontier

Before provenance classification, 38 unclassified candidate game rows larger
than 10 KiB accounted for 1,574,018 bytes.  Thirty are repeated character
pillars.  The fifteen primary-vtable `+0x28` roots alone occupy 918,209 ledger
bytes; the likely per-character owned-object/action roots occupy another
565,438 bytes.  This is why function progress can improve quickly while byte
progress remains low.

`config/character-vslot28-roots.csv` is the first structured manifest for that
frontier.  It records accepted ledger spans, IDA boundary conflicts, numeric
action-table blocks, and shared/distinctive callees without inventing per-case
gameplay names or placeholder bodies.

Six roots now also have complete slice manifests. Three use successful IDA
Hex-Rays output; Marisa and Udonge use exact-target compressed-table decoding
after Hex-Rays failure; Patchouli additionally guards the non-contiguous IDA
boundary case. This backend-neutral evidence model preserves breadth without
lowering the semantic gate or pretending that disassembly is pseudocode.

## Next provenance work

1. Split the mixed Boost/project island `0x00690310..0x006A3DCF` by RTTI,
   call-graph isolation, object signatures, and wrapper ownership.
2. Mine interspersed VC8 STL specializations, deleting destructors, thunks,
   and EH adapters in the game address region.  Promote only exact or
   provenance-supported bodies.
3. Assign a subsystem to every remaining review row using RTTI/vtable
   ownership, strings, callers, globals, and address clusters.  Address
   adjacency alone is never sufficient.
4. Regenerate the census and progress after each audited batch.

## Commands

```bash
python3 scripts/function-origins.py --check
python3 scripts/function-origins.py --write
python3 scripts/function-origins.py --apply-ledger
python3 scripts/validate-tracking.py
python3 scripts/progress.py --check
```

Only the coordinator uses `--apply-ledger`.  Evidence workers return bounded
row lists and selectors; they do not write shared manifests or statuses.
