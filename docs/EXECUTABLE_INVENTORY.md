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

The current ledger contains 4,840 functions (the audit recovered two missing
internal boundaries):

| Status | Functions | Function bytes |
| --- | ---: | ---: |
| `unclassified` | 2,261 | 1,164,331 |
| `identified` | 126 | 19,743 |
| `decompiled` | 199 | 1,208,529 |
| `implemented` | 140 | 52,378 |
| `compiles` | 3 | 428 |
| `matching` | 214 | 28,717 |
| `library` | 1,897 | 169,825 |

The old progress denominator treated every non-`library` row as authored.
That included import jump stubs, statically linked VC8 CRT, C++ exception
funclets, zlib, and Xiph codec code.  It therefore reported 209/4,789 even
though most of those support rows should never be reconstructed by hand.

The current evidence-backed provenance pass excludes 1,897 rows and leaves
2,943 authored-or-review rows. It reports three separate populations rather than
pretending the unresolved population is authored:

- confirmed authored: 667 rows;
- confirmed non-authored: 1,897 rows;
- origin review: 2,276 rows.

The confirmed-authored population is a lower bound, not a new final
denominator.  Review rows remain outside that metric until evidence decides
their origin.  `docs/PROGRESS.md` retains the legacy non-library metric so the
transition is visible.

## Audited non-authored islands

### Static third-party libraries

| Selector | Rows | Bytes | Evidence and limit |
| --- | ---: | ---: | --- |
| `0x00664FA0..0x0066AC2D` | 44 | 21,553 | Target has the zlib 1.2.3 version string and `inflateReset`, `inflateInit2`, `inflate`, and `inflate_fast` fingerprints. |
| `0x0066BFD0..0x0067AFCF` | 151 | 52,055 | Static libvorbis/libvorbisfile cluster anchored by `ov_clear`, `ov_open_callbacks`, `ov_info`, `ov_time_seek`, `ov_time_tell`, and `ov_read`. One hundred fifty unique functions/52,001 bytes are strict exact against the official Win32 SDK 1.0.1 objects. Only `res0_free_look` (54 bytes) remains non-exact. |
| `0x006A2FB0..0x006A3DD7` | 33 | 3,343 | Separated libogg `framing.c`/`bitwise.c` graph proven by page-header semantics, `_packetout`, `oggpack_*`, and direct calls from the `ov_*` cluster. All 33 functions/3,343 bytes are strict exact against the official Win32 SDK 1.0.1 objects. |

The first audit hypothesis incorrectly treated `0x00662F80..0x0067AFCF` as
one codec island.  Read-only IDA call graphs disproved it: the prefix contains
character behavior, renderer helpers, and `WinMain` at `0x00664C20`.  Those
game rows remain authored/review work.  Library classification must use the
audited row set, not address adjacency.

A second pass found the inverse layout trap: libogg was not contiguous with
libvorbis. Its 33 selected framing/bitwise functions were linked at
`0x006A2FB0..0x006A3DD7` inside a larger mixed-origin address neighborhood.
Target semantics and direct `ov_*` call edges, rather than neighborhood
ownership, establish that separate third-party island.

The zlib provenance is additionally supported by the official
[zlib 1.2.3 source tag](https://github.com/madler/zlib/tree/v1.2.3). Xiph API
and cluster provenance is supported by the official
[libogg](https://github.com/xiph/ogg) and
[libvorbis](https://github.com/xiph/vorbis) repositories; external source is
supporting provenance, never target-instruction authority.

The repository now vendors the unmodified core zlib v1.2.3 translation units
at `third_party/zlib-1.2.3/`. VC8 SP1 canonical match units strictly reproduce
all 44 island functions and all 21,553 function bytes. Every row remains
`status=library`, so the external-source result is visible in library,
third-party, and combined reconstruction metrics without inflating authored-game
matching. Reproduce the accepted evidence with:

```bash
python3 scripts/build.py --unit zlib-inflate-anchors --compare --json
python3 scripts/build.py --unit zlib-deflate-anchors --compare --json
python3 scripts/build.py --unit zlib-crc32-anchor --compare --json
python3 scripts/build.py --unit zlib-zutil-anchors --compare --json
python3 scripts/build.py --unit zlib-inffast-anchor --compare --json
python3 scripts/build.py --unit zlib-inftrees-gs-anchor --compare --json
python3 scripts/build.py --unit zlib-adler32-anchor --compare --json
python3 scripts/build.py --unit zlib-tree-anchors --compare --json
```

The Xiph release matrix identified official libvorbis v1.0.1: target
`ov_time_seek` retains its old reverse link scan and the target
`vorbis_info_init` allocates a `0xE80`-byte codec setup, while v1.1.0 through
v1.2.3 use `0xE50`. An archived official Windows SDK then proved the missing
code-generation profile: its prebuilt COFF objects match nontrivial target
bodies exactly. The two libogg commands now cover the complete linked
framing/bitwise island, including verified REL32 and DIR32 replay. Reproduce
the accepted wave with:

```bash
python3 scripts/build.py --unit xiph-vorbis-info-anchors --compare --json
python3 scripts/build.py --unit xiph-vorbisfile-host-endian-anchor --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-block --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-synthesis --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-codebook --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-floor1 --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-res0 --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-mapping0 --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-psy --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-sharedbook --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-bitrate --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-envelope --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-smallft-forward --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-mdct-butterflies --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-window --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-floor0 --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-lsp --compare --json
python3 scripts/build.py --unit xiph-sdk-vorbis-lookup --compare --json
python3 scripts/build.py --unit xiph-sdk-ogg-framing-relocation-free --compare --json
python3 scripts/build.py --unit xiph-sdk-ogg-bitwise-relocation-free --compare --json
```

These units strictly reproduce 150 unique libvorbis/vorbisfile functions and
52,001 function bytes. Together with the complete 33-function libogg island,
the Xiph work leaves only `res0_free_look` (54 bytes) unresolved. Its official
SDK body has a real two-byte non-relocation difference, so it remains visible
as third-party work rather than being inferred exact from its neighbours.

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

The SHA-pinned VC8 SP1 archive replay now strictly reproduces 114 runtime
functions and 20,299 bytes. The initial breadth wave contributes 74 functions
and 6,862 bytes across 58 canonical `libcmt.lib` object units; the next
dependency pass contributes six small-block-heap/floating-exception functions
and 2,767 bytes; a low-level I/O/decimal-format pass contributes another five
functions and 4,137 bytes; the floating-point control/SEH chain contributes
four functions and 994 bytes; a disambiguated I/O/conversion pass adds seven
functions and 3,324 bytes; audited near-Jcc support closes `log10` and `floor`
for another 545 bytes. Ambiguous identical-body symbols are excluded. Reproduction
and ABI caveats are recorded in `docs/VC8_RUNTIME_RECOVERY.md`.

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

All fifteen roots now have complete slice manifests. Nine use successful IDA
Hex-Rays output; Marisa, Reimu, Sakuya, Suika, and Udonge use exact-target
compressed-table decoding after Hex-Rays failure, and Aya uses the strict
headless Ghidra fallback. The family includes
contiguous, small body/span difference, large chunk-conflict, four-table, and
43-callee outlier regressions. This backend-neutral evidence model preserves
breadth without lowering the semantic gate or pretending that disassembly is
pseudocode.

## Next provenance work

1. Continue splitting the mixed Boost/project island `0x00690310..0x006A3DCF`;
   the separated 33-function libogg sub-island is now removed from review.
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
