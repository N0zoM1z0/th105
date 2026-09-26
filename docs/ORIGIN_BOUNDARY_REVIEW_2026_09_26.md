# Origin and boundary review: shared game helpers

## Evidence scope

All addresses and bytes below are from the hash-verified original Japanese
TH10.5 v1.06a PE, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The attached IDA session has a different executable hash and was not queried.
Retained source and old notes supplied hypotheses only. The new direct-edge
witnesses in `config/function-origin-rules.toml` replay the actual E8/E9
instruction and signed displacement inside independently exact callers.

## Queue-wide boundary triage

`scripts/audit-candidate-boundaries.py` recursively decodes raw PE control
flow from each candidate entry. Before the first origin promotion, it audited
all **1,239** review rows: **935** had all provisional span bytes reachable,
at least one RET, and no visible indirect or outgoing jump; **159** had
unreached bytes, **62** had indirect jumps, and **137** had outgoing direct
edges. These categories overlap. No row had a failed or overlapping decode.
This is a priority map, not 935 accepted function boundaries: jump tables,
remote chunks, exception paths, incoming interior edges, and compiler metadata
still need review at each address. The report is reproducible and generated
privately below `build/`:

```bash
python3 scripts/audit-candidate-boundaries.py --review --json > build/all-review-boundaries.json
```

## Four bounded authored candidates

Each candidate below has a complete raw reachable main span, no visible
indirect or outgoing jump, RET termination, and nearby `INT3` separation.
Their origins are supported by target behavior plus independent exact game
callers; this does not establish exact source code or original TU partition.

| Candidate | Main span / returns | Raw callable SHA-256 | Origin evidence |
| --- | --- | --- | --- |
| `0x00407AD0` sprite render finalizer | 219/219; RET `0x00407BAA` | `5b4ed5412715bbb05c9c311f9c72fcc9548ab93fb1c5aad0dcb039a43002b698` | Exact AnimationObject color render tail `0x0043555D` and exact SpriteRenderEffect call `0x0066550F` land here. The body reads sprite fields, calls texture-stage binder `0x00404DF0`, and performs D3D9 draw dispatch. |
| `0x004099F0` UI tile renderer | 756/756; RET `0x00409CE1` | `c521a6318217f285e593bff562969f8b7b7ef4687b7e26884df446cb476416eb` | Exact ScenarioResultResource render call `0x00454939` lands here. Target code uses game orientation helpers `0x00406360/0x004063D0`, handle lookup `0x00417800`, and a draw virtual. |
| `0x00420B90` UI design-object binder | 118/118; RETs `0x00420BDE/0x00420C03` | `663afb38180408beed34f80e9d9c0ddb44feec986aac016287f387669af51541` | Exact profile UI initializer call `0x0043FDB8` lands here; 43 exact game call sites exist. The body searches the receiver's `+0x20` tree through generated lower-bound helper `0x0040CDA0`, then writes the selected object or null through the output pointer. |
| `0x00462AB0` Character base constructor | 557/557; RET 4 `0x00462CDA` | `6843409d8f8d40e4f3ebf4d1bd9615a666c72f0abda652943492913297aaa5a5` | Fourteen exact roster-derived constructors call it, including Reimu `0x00493A6D` and Alice `0x004FAC6D`. It constructs AttackObject and game-specific fighter/spell members before derived vptr publication. |

Focused reproduction:

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x00407AD0 0x004099F0 0x00420B90 0x00462AB0 --json
python3 scripts/function-origins.py --check
python3 scripts/validate-tracking.py --require-target
```

`functions.csv` now records these reviewed main spans as identified; the
generated origin census classifies the four as authored game functions. The
names for the two UI methods are working semantic labels, without a separate
RTTI class-name proof. `0x00404DF0` remains under origin review. Existing
standalone source probes for the sprite finalizer and Character constructor
remain nonexact, and neither the UI renderer nor binder receives source-present
or canonical exact credit from this origin decision.

## Ten five-byte tail aliases

The second bounded batch found ten review candidates whose entire provisional
span is one reachable `E9 rel32` instruction. The preceding code terminates
at a return, another jump, or `INT3`, so there is no visible fallthrough into
the alias. The origin rules independently replay the signed jump displacement,
require a five-byte candidate, and require an excluded destination origin.

| Alias | Destination | Destination evidence |
| --- | --- | --- |
| `0x004021B0` | `0x004023E0` | VC8-generated `std::list<void*>::_Tidy` anchor |
| `0x00413770` | `0x00413A90` | VC8-generated fixed-slot container anchor |
| `0x00420B80` | `0x00420AF0` | VC8-generated CFileList container anchor |
| `0x00436470` | `0x00436420` | VC8-generated SpriteEx vector anchor |
| `0x0045FD50` | `0x0045FC30` | VC8-generated PatRecord vector anchor |
| `0x0046B1F0` | `0x00435EB0` | VC8-generated `std::list<void*>::_Tidy` anchor |
| `0x00665B8A` | `0x00689DCB` | VC8 SP1 archive-defined operator new |
| `0x006898EA` | `0x0068C686` | VC8 SP1 archive-defined `free` |
| `0x0068AA26` | `0x006898EA` | The preceding excluded `free` alias |
| `0x0068B1B7` | `0x0068B1A6` | VC8 SP1 archive-defined `atol` |

These are compiler/linker aliases, classified `compiler_generated/exclude`:
they contain no independent authored or runtime function body. The destination
rules supply positive provenance; name prefixes by themselves were not used
to classify them. This establishes the five-byte entry boundary and jump
target, without claiming the linker mechanism or original TU placement.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x004021B0 0x00413770 0x00420B80 0x00436470 0x0045FD50 \
  0x0046B1F0 0x00665B8A 0x006898EA 0x0068AA26 0x0068B1B7 --json
python3 scripts/function-origins.py --check
```
