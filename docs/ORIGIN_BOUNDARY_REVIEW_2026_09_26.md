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

## VC8 security-cookie check at `0x00689D25`

The hash-attested raw PE candidate spans 15 bytes. Its reachable code compares
ECX against `[0x006F7A88]`, returns on equality, and tail-jumps to
`0x0068FCFC` on failure. SHA-pinned VC8 SP1 `libcmt.lib`, member
`build/intel/mt_obj/secchk.obj`, defines the 15-byte
`@__security_check_cookie@4` function. All seven non-relocation bytes agree;
the complete 4,023-candidate fingerprint hit set is only `0x00689D25`.
The member's DIR32 `___security_cookie` field resolves to `0x006F7A88`,
and its REL32 `___report_gsfailure` field resolves to `0x0068FCFC` in the
target. The short-anchor rule checks the archive hash, COFF function extent,
full hit set, relocation types/symbols, and both resolved addresses.

This is `vc8_runtime/exclude`, with a complete 15-byte boundary and no game
source or canonical exact credit. The narrow short-anchor threshold applies
only with explicit relocation destinations; the established broader runtime
anchor threshold remains unchanged.

## Eighteen global static destructor callbacks

A separate batch reviewed 18 complete ten-byte candidates. Each contains only
`MOV ECX, <.data object>` followed by `E9` to a cleanup target or container
teardown. Raw target code pushes each callback address and calls `_atexit @
0x0068AF1E`, whose VC8 runtime origin is already independently established.
Three registrations perform only target-pinned global stores between the push
and `_atexit`; the other fifteen call immediately. The origin rule checks each
ten-byte body, object address in the PE `.data` virtual section, direct tail
target, callback PUSH, intervening bytes, and signed `_atexit` CALL. Raw CFG
review covers 10/10 bytes at every entry with no gap or indirect exit.

| Callback | Receiver global | Tail destination | Registration PUSH |
| --- | --- | --- | --- |
| `0x006BEDE0` | `0x00702798` | `0x00404FD0` | `0x006BE737` |
| `0x006BEF00` | `0x006FA6E0` | `0x004114C0` | `0x006BE93A` |
| `0x006BEF10` | `0x006FA6C8` | `0x00413A90` | `0x006BE8E0` |
| `0x006BEFA0` | `0x006FBDC8` | `0x004145F0` | `0x006BE9AA` |
| `0x006BEFB0` | `0x006FBD60` | `0x00409D50` | `0x006BEB4C` |
| `0x006BF090` | `0x006FCA2C` | `0x0043C280` | `0x006BEB70` |
| `0x006BF0E0` | `0x006FC598` | `0x0043DC70` | `0x006BEC1A` |
| `0x006BF170` | `0x006FCC98` | `0x0043DF10` | `0x006BEC3A` |
| `0x006BF180` | `0x006FBDD0` | `0x0043F260` | `0x006BE9FA` |
| `0x006BF1D0` | `0x006FD0B8` | `0x004114C0` | `0x006BEC5A` |
| `0x006BF220` | `0x006FD2C8` | `0x00439FC0` | `0x006BECAA` |
| `0x006BF230` | `0x006FD288` | `0x00435EB0` | `0x006BED5A` |
| `0x006BF240` | `0x006FD24C` | `0x00421890` | `0x006BECFA` |
| `0x006BF250` | `0x006FD048` | `0x00421890` | `0x006BED1A` |
| `0x006BF260` | `0x006FD294` | `0x00421890` | `0x006BED3A` |
| `0x006BF270` | `0x006FD07C` | `0x00421890` | `0x006BECDA` |
| `0x006BF280` | `0x006FD394` | `0x00417FC0` | `0x006BED8A` |
| `0x006BF300` | `0x006FDEC4` | `0x006B0390` | `0x006B3DF4` |

The uniform callback shape and actual `_atexit` registration support an
**inferred** compiler-generated global destruction-adapter origin. Several tail destinations
are authored game destructors, several are generated container teardowns, and
others still await origin review. Excluding the callbacks makes no assertion
about their destinations, source TUs, or exact game-code matches. Three similar
ten-byte candidates without a verified `_atexit` registration remain pending.

```bash
python3 scripts/function-origins.py --check
python3 scripts/audit-candidate-boundaries.py --review --json > build/current-review-boundaries.json
```

## Eight registered global container cleanup bodies

The next group has six 64-byte RET-terminated callbacks and two 46-byte
RET-terminated callbacks. Every provisional span is fully reachable with no
unreached byte or outgoing jump. The six larger bodies load a global container
range, call its element-destruction helper, free backing storage through the
already excluded `0x006898EA` alias, and clear the range pointers. The two
smaller bodies test a global `std::string` capacity against 16, free heap
storage when needed, then reset capacity, size, and the small-string first
byte. All eight callback addresses are pushed and passed to VC8 `_atexit @
0x0068AF1E` by target code. The rule pins the full body hash, free-call edge,
PUSH, intervening registration bytes, and `_atexit` CALL.

| Callback | Body | Registration PUSH | Free call |
| --- | ---: | --- | --- |
| `0x006BEF20` | 64 | `0x006BE91A` | `0x006BEF47` |
| `0x006BEF60` | 64 | `0x006BE98A` | `0x006BEF87` |
| `0x006BF0A0` | 64 | `0x006BEABA` | `0x006BF0C7` |
| `0x006BF0F0` | 64 | `0x006BEA7A` | `0x006BF117` |
| `0x006BF130` | 64 | `0x006BEAFA` | `0x006BF157` |
| `0x006BF190` | 64 | `0x006BEA3A` | `0x006BF1B7` |
| `0x006BF2A0` | 46 | `0x006B3B69` | `0x006BF2AF` |
| `0x006BF2D0` | 46 | `0x006A5115` | `0x006BF2DF` |

The repeated destructor shapes and registrations support an **inferred**
compiler-generated static cleanup origin. The exact source TU and semantic
type of each container value remain unknown. These exclusions make no
canonical exact-source claim.

## Ten small static lifetime callbacks

These ten remaining callbacks have a direct `PUSH <entry>; CALL _atexit`
registration with no instruction between the PUSH and CALL. Their complete
1–20 byte main spans are raw-CFG reachable. The full body SHA-256 and
registration instruction pair are replayed by the origin rule. Body behavior
is summarized below; an outgoing E9 is a boundary exit, not a RET.

| Callback | Bytes | Target body | Registration PUSH |
| --- | ---: | --- | --- |
| `0x006BEDB0` | 11 | global vptr store; RET | `0x006BE6E0` |
| `0x006BEE70` | 1 | RET only | `0x006BE7E4` |
| `0x006BEE90` | 1 | RET only | `0x006BE825` |
| `0x006BEEA0` | 1 | RET only | `0x006BE854` |
| `0x006BEEC0` | 5 | E9 to authored `shutdown_direct_sound` | `0x006BE890` |
| `0x006BF1E0` | 11 | global vptr store; RET | `0x006BEC70` |
| `0x006BF1F0` | 11 | global vptr store; RET | `0x006BEC80` |
| `0x006BF200` | 11 | global vptr store; RET | `0x006BEC90` |
| `0x006BF210` | 11 | global vptr store; RET | `0x006BECC0` |
| `0x006BF28A` | 20 | global vptr store; E9 to `0x00689FDA` (origin pending) | `0x00689E0B` |

The actual registrations and isolated callback bodies are **observed**.
Compiler-generated static lifetime origin is **inferred** from the repeated
forms and placement. In particular, excluding the callback alias at
`0x006BEEC0` does not exclude its authored DirectSound shutdown destination,
and the origin of `0x00689FDA` remains pending. No source TU or canonical
exact-match claim follows from these registrations.

A bounded 75-byte proximity screen found 38 initially pending candidate
addresses near raw calls to `_atexit`. The 36 callbacks above had a verified
PUSH-to-first-CALL path. The other two, `0x0043BF50/0x0043BF60`, are pushed
as destructor/constructor arguments to VC8 array-construction helper
`0x0068A30C` first; a later nearby `_atexit` call belongs to another
registration. They remain in origin review. This screen does not enumerate
registrations made through a different instruction form or beyond its window.

## Two KERNEL32 import thunks

`0x006B55C0` and `0x006B5ECA` each have a complete six-byte `FF 25` body:
an indirect jump through IAT slots `0x006C008C` and `0x006C0144`,
respectively. The hash-attested PE import descriptors map those slots to
`KERNEL32.dll!GetUserDefaultLCID` and `KERNEL32.dll!RtlUnwind`.
`function-origins.py` now replays the PE32 import table and checks the
instruction bytes, referenced slot, DLL, and imported name. Both boundaries
are one reachable jump instruction, with no body continuation. The first is
`INT3` separated; the second follows a return and precedes a new function.
Both are `import_thunk/exclude`, with no independent source or canonical
exact-game credit.

## Two VC8 SP1 runtime functions

`__free_lc_time @ 0x0069CCD9` has a complete 400/400-byte RET-terminated
target boundary. SHA-pinned VC8 SP1 `libcmt.lib` member
`build/intel/mt_obj/inittime.obj` defines `___free_lc_time` with the same
400-byte extent. Its 228 non-relocation bytes all agree, and the complete
candidate-inventory fingerprint hit set is only `0x0069CCD9`. All 43 COFF
relocations are `REL32` calls to `_free`; all 43 target calls resolve to the
already excluded CRT `free @ 0x0068C686`. The archive symbol has one more
leading underscore than the current candidate name, so the broad
name-based runtime selector did not claim it. The explicit archive anchor
replays the function body and every relocation symbol and destination.

`__allshl @ 0x006B6D00` has a complete 31/31-byte boundary with three RET
paths. SHA-pinned `libcmt.lib` member `build/intel/mt_obj/llshl.obj` defines
the same 31-byte `__allshl` body with no COFF relocations. The full byte
sequence is unique among current candidate spans. Its address lies outside
the broad name-based runtime rule's bounded island, so it receives its own
positive archive anchor.

Both are `vc8_runtime/exclude`. The archive matches prove runtime provenance
and candidate boundaries; they do not grant canonical authored source or
exact-game comparison credit.

## Match-mode setup at `0x0043B8F0`

Fresh raw-PE CFG traversal reaches all 286 candidate bytes, both returns at
`0x0043B9C7/0x0043BA0D`, and no visible indirect or outgoing jump. `INT3`
separates both sides of the main span. The full body SHA-256 is
`beaf3460ffa40456b209c220f737c4b74565b3ec45cb5b2a916540123ce18b59`.
Target instructions write mode `0x006FBD4C`, setup option `0x006FBD44`,
selected-input state around `0x006FBD38`, and scenario state `0x006FCA70`;
one branch writes the player-two input address `0x006FBDD0` to the object
loaded from session pointer `0x006FBD5C` at `+0x6B4`. The current global names
are ledger annotations, while those addresses and widths are raw observations.

Canonical-exact `CTitle::update @ 0x00425990` calls the body at nine E8 sites
covering different title choices. All nine belong to **one** exact caller;
the rule replays sites `0x004259D6` and `0x00425B29`. An additional call
comes from nonexact `0x004472A0`. These calls plus the game-specific state
transitions support `authored_game/battle`; they do not prove a canonical
function name or exact standalone source. The exact caller uses the local
alias `prepare_title_match_mode`, while historical notes use
`prepare_result_match`. Neither alias is promoted to a durable name here.

```bash
python3 scripts/audit-candidate-boundaries.py 0x0043B8F0 --json
python3 scripts/function-origins.py --check
```
