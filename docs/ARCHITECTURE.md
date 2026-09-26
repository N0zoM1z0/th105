# TH10.5 architecture baseline

This file records only the corrected 1.06a baseline and the repository shape
chosen for reconstruction. It does not carry forward addresses or exact-match
claims from the former 1.06 target.

## Verified executable facts

| Property | 1.06a value |
| --- | --- |
| Format | PE32 x86 Windows GUI, relocations stripped |
| File size | `3,129,344` bytes |
| Image base / image size | `0x00400000` / `0x00306000` |
| Entry point | `0x0068B9D2` |
| `.text` virtual range | `0x00401000..0x006BF33A` |
| `.text` raw size | `2,879,488` bytes |
| Linker | Microsoft 8.0 |
| Rich compiler build | `50727` |
| C++ / C / LTCG C++ records | `279` / `179` / `42` |
| PDB record | `c:\Nonotaro\works\東方緋想天\th105.pdb`, age 2 |
| Initial IDA candidate inventory | 4,001 functions (historical first pass) |

The section layout, hashes, timestamp, CodeView GUID, and complete provenance
are machine-readable in `config/target.toml`.

IDA candidates are not compiler-object boundaries. Tail chunks, EH funclets,
thunks, compiler helpers, statically linked libraries, and LTCG transformations
must be classified before authored progress has a meaningful denominator.

## Why TH08 cannot be copied mechanically

TH08 provides a mature workflow, not a compatible program architecture.

| Concern | TH08 | TH105 |
| --- | --- | --- |
| Product shape | scrolling shooter | networked fighting game |
| Dominant code organization | manager/global-heavy game loop | extensive polymorphic C++ scenes, fighters, objects, UI and networking |
| Toolchain family | VC7-era | VC8 build 50727 |
| Link optimization | no TH105-style evidence assumed | 42 C++ LTCG Rich records |
| Safe reusable material | ledgers, status separation, exact acceptance, handoff discipline | target-specific ABI, ownership, types, boundaries and source shape must be recovered anew |

Accordingly, this repository adopts TH08's control plane while retaining a
TH105-specific candidate/origin layer and multi-function VC8 match-unit format.

## Reconstruction modules

`config/modules.toml` is a proposed source taxonomy, not recovered original TU
ownership. The broad areas are platform/engine, input, rendering/assets/audio,
UI/script/network, battle, character families, and third-party/runtime code.
Move or split source only after 1.06a xrefs, RTTI/vtables, static initialization,
and comparison evidence establish ownership.

The original `src/` tree was a retained hypothesis corpus from the old target.
Selected 1.06a-reviewed symbols are now recorded in `config/implemented.csv`;
the rest of the retained tree still does not establish target semantics. Use
the current status report and ledgers for counts, not this baseline document.

## Current gates

1. Reconcile high-confidence IDA candidate boundaries against exact control
   flow and record exceptions without inferring adjacency-based sizes.
2. Separate authored code from compiler/runtime/third-party islands.
3. Expand the cold-replayable authored anchors while preserving current-target
   ABI/layout evidence and exact acceptance. The historical 553-anchor count
   is superseded; obtain the current count from the tracking report.
4. Maintain the reviewed authored/excluded denominator and recompute it from
   tracking ledgers before reporting aggregate function or byte percentages.
5. Treat standalone-object failure under LTCG as a classification result, not
   permission to weaken exact acceptance.
