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
registration. Later callback reviews below exclude destructor adjustor
`0x0043BF50` and its paired constructor `0x0043BF60`. This
screen does not enumerate registrations made through a different instruction
form or beyond its window.

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

## UI text-texture resource wrapper at `0x00404D00`

The exact PE main span is 111/111 reachable bytes with `RET 0x1C` at
`0x00404D5C/0x00404D6C`, no visible indirect or outgoing exit, and `INT3`
separation. Its body SHA-256 is
`fc2a1d60bc6b46699dfaace27231d5e7135b47105b7493cd04ce864ea9f8ee0c`.
Raw code keeps its receiver in EDI, obtains a resource handle through
`0x00405090`, calls `0x004097A0` to create a texture, invokes `0x00405200`
to release the handle on a negative HRESULT, and writes the resulting
four-byte handle through the hidden return pointer. `0x004097A0` itself
calls the PE import thunk `D3DXCreateTexture @ 0x0068989C`.

Six different canonical-exact UI/network functions call `0x00404D00`;
the rule replays E8 sites in exact `Menu_show_profile_result @ 0x0043F810`
and `NetworkSessionResultView_finalize_result_binding @ 0x0044DCB0`.
The wrapper's handle lifetime and game UI callers support
`authored_game/ui`. Retained source calls it
`TitleResourceManager::create_text_texture` and models a four-byte class
return; that class name is a working label. The target ABI and caller
behavior are the evidence here, without source-present or exact-match credit.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00404D00 --json
python3 scripts/function-origins.py --check
```

## Profile message update at `0x0043F6E0`

The hash-attested target CFG reaches 298/298 bytes from the candidate entry,
with five plain returns at `0x0043F72E`, `0x0043F75A`, `0x0043F7B2`,
`0x0043F7CD`, and `0x0043F809`. There are no unreachable candidate bytes,
indirect exits, or outgoing direct jumps; `INT3` follows the last return. The
body SHA-256 is
`7cd81ee125c1ed51f0c66aec0e25e1be8f8652d63af1e0f14f1c51d3395172ed`.

The body calls the game menu cursor update at `0x0041FA20`, dispatches UI
events `0x27`, `0x28`, and `0x29` through `0x0043B1A0`, and changes byte
`+0x14` on menu object pointers stored at five nearby globals
`0x006FD02C/34/38/3C/40`. Its return paths produce zero, two, three, or
four depending on cursor and message state. Seven separate canonical-exact
UI callers contain eight direct E8 calls. The origin rule replays sites
`0x00442844` in exact `CMenuConnect::update_state_one @ 0x00442790` and
`0x0044CD73` in exact `CProfileMenu::update_state_four @ 0x0044CC50`.
These target observations support `authored_game/ui` and the provisional
main-span boundary. `update_profile_message` is a retained working label;
its existing ordinary C++ probe is still 291 bytes versus target 298 and
does not gain source-present or exact credit from this review.

```bash
python3 scripts/audit-candidate-boundaries.py 0x0043F6E0 --json
python3 scripts/function-origins.py --check
```

## Twelve Boost exception RTTI adjustor thunks

Twelve eight-byte candidates in two exception-code clusters each consist of
`sub ecx, imm8; jmp rel32`. Every candidate byte is reachable; each outgoing
direct jump lands on a distinct inventoried callee entry. The exact PE
`.rdata` contains a function-pointer slot for each thunk. Immediately before
each slot's virtual-function group is a VC8 RTTI CompleteObjectLocator. Its
secondary-base `offset` equals that thunk's `sub ecx` immediate, and its type
descriptor names a `boost::exception_detail::error_info_injector` or
`boost::exception_detail::clone_impl` specialization.

| RTTI exception family | Adjustor entries (ECX subtraction) | Direct tail targets |
| --- | --- | --- |
| `std::invalid_argument` | `0x006A4D00` (`0x28`), `0x006A4D40` (`0x28`), `0x006A4D50` (`0x3C`) | `0x006A5360`, `0x006A5320`, `0x006A5320` |
| `std::runtime_error` | `0x006A4F40` (`0x28`), `0x006A4F70` (`0x28`), `0x006A4F80` (`0x3C`) | `0x006A5610`, `0x006A55D0`, `0x006A55D0` |
| `boost::regex_error` | `0x006B4C40` (`0x30`), `0x006B4C70` (`0x44`), `0x006B4C80` (`0x30`) | `0x006B4D80`, `0x006B4D40`, `0x006B4D40` |
| `std::logic_error` | `0x006B4CF0` (`0x28`), `0x006B4D20` (`0x3C`), `0x006B4D30` (`0x28`) | `0x006B4DE0`, `0x006B4DA0`, `0x006B4DA0` |

The origin rule replays each instruction, signed target, `.rdata` slot, RTTI
locator, offset, type descriptor, and Boost type name against the attested
target. This supports `compiler_generated/exclude`: the callable is a VC8
secondary-base `this` adjustment emitted for a Boost-owned virtual class. It
does not classify the twelve target callees or assign an upstream Boost
release. The source and exact-match ledgers receive no promotion.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x006A4D00 0x006A4D40 0x006A4D50 0x006A4F40 0x006A4F70 0x006A4F80 \
  0x006B4C40 0x006B4C70 0x006B4C80 0x006B4CF0 0x006B4D20 0x006B4D30 --json
python3 scripts/function-origins.py --check
```

## Eight Boost exception scalar deleting destructors

The same four Boost exception RTTI families each have two primary-vtable
deleting destructors: a 30-byte `error_info_injector` wrapper and a 57-byte
`clone_impl` wrapper. All eight provisional spans are fully reachable and end
in `RET 4`. Each preserves the `this` pointer, calls its class destructor,
tests the low bit of the deletion flag, conditionally calls the previously
excluded free alias `0x006898EA`, and returns `this`. The longer four publish
class vptrs before the destructor call.

| RTTI exception family | 30-byte / 57-byte wrappers | Underlying destructor |
| --- | --- | --- |
| `std::invalid_argument` | `0x006A5360` / `0x006A5320` | `0x006A4CA0` |
| `std::runtime_error` | `0x006A5610` / `0x006A55D0` | `0x006A4EE0` |
| `boost::regex_error` | `0x006B4D80` / `0x006B4D40` | `0x006B4BE0` |
| `std::logic_error` | `0x006B4DE0` / `0x006B4DA0` | `0x006B4C90` |

The origin rule pins each full target body hash, primary vtable pointer,
adjacent VC8 RTTI locator and Boost type descriptor, and both signed E8
destinations. This class-specific scalar deletion code is
`compiler_generated/exclude`. The eight underlying destructor candidates
are separate and remain under review; the RTTI association does not by
itself resolve their complete code ownership or original TU boundaries.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x006A5320 0x006A5360 0x006A55D0 0x006A5610 \
  0x006B4D40 0x006B4D80 0x006B4DA0 0x006B4DE0 --json
python3 scripts/function-origins.py --check
```

## Four Boost `clone_impl` throw virtuals

The four 55-byte candidates `0x006A84E0`, `0x006A96B0`, `0x006B5110`,
and `0x006B5400` are the second virtual-function slots in distinct Boost
`exception_detail::clone_impl` RTTI vtables. Each body reaches all 55 bytes,
copies a class-specific exception into a stack temporary through its own
helper, writes the vptrs belonging to that RTTI class, and ends in a direct
E8 to the independently identified VC8 `__CxxThrowException @ 0x0068A153`.
`INT3` follows each terminal call. There is no ordinary RET; the boundary
auditor conservatively reports an outgoing fallthrough because it does not
model the runtime call as no-return.

The origin rule pins full body hashes, both E8 destinations, vtable slots,
adjacent VC8 RTTI locators, Boost type descriptors, and the terminal throw
edge. These virtual throw/rethrow implementations belong to Boost template
code (`third_party/exclude`, inferred). Their helper callees remain separate
pending candidates. The four related 120-byte clone/allocate methods have EH
registration; their shared unwind path is reviewed in the next section. The
exact Boost release remains unknown. No source-present or canonical exact
credit changes.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x006A84E0 0x006A96B0 0x006B5110 0x006B5400 --json
python3 scripts/function-origins.py --check
```

## Four Boost `clone_impl` allocate virtuals and their EH cleanup

The four first-slot virtuals `0x006A8460`, `0x006A9630`, `0x006B5090`,
and `0x006B5380` belong to the same four `clone_impl` RTTI types. Each
120-byte main span is fully reachable and ends in a plain RET. Raw code calls
the separately excluded VC8 operator new `0x00689DCB`, invokes a
class-specific copy helper, then publishes vptrs for the corresponding
Boost class. All four register EH handler `0x006B6E2B` in their prologues.

The handler's complete 27-byte code checks the security cookie through
`0x00689D25`, loads VC8 FuncInfo `0x006DD140`, and tail-jumps to the
already excluded `__CxxFrameHandler3 @ 0x006899E7`. That 36-byte FuncInfo
has one unwind state and points at map `0x006DD138`; the map's action is
`0x006B6E20`. The action is an 11-byte cleanup that reads the allocated
pointer from `[ebp-0x10]` and calls excluded free alias `0x006898EA`.
This closes the observed exceptional allocation cleanup path without
folding the shared EH code into any of the four 120-byte main spans.

The origin rule checks all body hashes, virtual slots, RTTI locators, type
descriptors, both direct E8 sites per body, handler prologues, and the exact
shared handler/FuncInfo/unwind map/action bytes and references. The methods
are Boost template implementations (`third_party/exclude`, inferred). The
four called copy helpers have a later, separate origin and EH review below;
their original TU boundaries remain unknown.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x006A8460 0x006A9630 0x006B5090 0x006B5380 --json
python3 scripts/function-origins.py --check
```

## Network packet sender at `0x00416990` and deque provenance correction

The attested PE CFG reaches all 464 candidate bytes and ends with `RET
0x10` at `0x00416B5D`; there are no unreachable bytes, indirect exits, or
outgoing direct jumps. The body SHA-256 is
`5b83746b7004fc7e95b134b175b5b03d11feb738ac0e177d7d1b735506f48031`.
`INT3` precedes the entry, and the next candidate begins immediately after
the return. The receiver retains packet state at offsets `+0x17C` and
`+0x168`. The body writes packet tag `0x0E`, a WINMM `timeGetTime`
timestamp, and a copied payload under KERNEL32 critical sections; it can
search the second queue for a matching result, update an output handle, and
signals a KERNEL32 event before returning.

Nine separate canonical-exact `CNetworkClient` functions each make one
direct E8 call to `0x00416990`. The rule replays sites `0x0044D794` in
exact `CNetworkClient_send_simple_packet` and `0x0044E6C6` in exact
`CNetworkClient_send_packet_with_result`. The game-specific packet tag,
state coupling, Win32 synchronization, and independent exact callers support
`authored_game/network`. Retained callers use conflicting `send_client`
prototypes; their names and argument models are working hypotheses, with no
standalone source or exact credit for this callee.

The sender also calls `std::deque` pointer `push_back` body `0x00417240`.
That body and `0x00417500` were previously labeled `characters` because a
SHA-pinned VC8 rebuild of exact `RosterObjectSpawns.cpp` supplied equivalent
`ReimuObject*` template fingerprints. Their target placement and this network
call show that the fingerprint does not prove each target clone's template
argument or characters-only ownership. The generated STL origin remains
supported; the four clone records now use neutral `runtime` subsystem, and
the origin rule replays this network call. No source or exact ledger changes.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00416990 --json
python3 scripts/function-origins.py --check
```

## Profile slot defaults at `0x00432050`

The original PE entry has a complete 334/334-byte reachable main span,
one plain RET at `0x0043219D`, and `INT3` separation on both sides. Its
body SHA-256 is
`dec4a6bb8c88010804f180e336b81f779f689abbf9907a2a331a0e207157fcb1`.
The thiscall body initializes two profile strings at `+0x98/+0xB4`, zeros
two 0x34-byte key-setting blocks at `+0x140/+0x174`, writes fixed game key
codes `200,208,203,205,44,45,46,30,31,32,16` and `0..6`, sets profile
flags, initializes twenty deck slots of stride `0x14`, then calls
`0x00431E80` for fifteen character-specific default decks.

Four distinct canonical-exact profile setup/UI functions call this body at
seven E8 sites. The rule replays sites in exact
`initialize_default_player_profiles @ 0x0043AF30` and
`CProfileMenu_commit_state_one @ 0x0044C110`. The game key table and
profile/deck state updates support `authored_game/ui`. Retained source
`ProfileMenuBaseData::initialize_defaults` agrees with these observations,
but its class label, source selection, and standalone codegen are not
accepted as exact by this origin review. The separately reviewed deck loader
at `0x00431E80` has its own EH chain and unresolved calling convention.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00432050 --json
python3 scripts/function-origins.py --check
```

## Character deck CSV loader at `0x00431E80`

The hash-attested candidate has 463/463 reachable bytes, no indirect or
outgoing direct jump, and `RET 8` at `0x0043204C` before `INT3`. Its main
body SHA-256 is
`aaee5a80c6dfc0305066fd25e5118dcbe98df5337f067db310529fd0badf6697`.
The body obtains a character-specific name, joins target strings
`data/csv/` and `/deck.csv`, uses string/CSV helpers, and reads twenty
short deck values into a caller-supplied container. Exact
`prepare_match_runtime_by_mode @ 0x0043AC60` and exact arcade battle setup
`0x00473520` both call it; the reviewed profile defaults function calls it
for fifteen character slots.

This body registers VC8 EH handler `0x006B81C3`. The complete 46-byte
handler checks two security cookies and passes FuncInfo `0x006DE3C4` to
the excluded `__CxxFrameHandler3`. Its FuncInfo has six unwind states in
map `0x006DE3E8`. Three distinct remote actions at
`0x006B81A0/A8/B0` tail-jump to generated string cleanup
`0x00401E00`; the fourth at `0x006B81B8` tail-jumps to exact
`CsvReader_dtor @ 0x0042E980`. The rule replays the handler push, all
external body hashes, FuncInfo/map links, each state transition, and action
targets. Those shared EH actions remain separate from the 463-byte main
span.

The game-specific deck path and exact battle/profile callers support
`authored_game/config`. Retained sources use incompatible member/class
labels for this address. The callee does not read ECX, and `RET 8` alone
does not distinguish a two-argument member from a two-argument stdcall
function. Its durable name, calling convention, original TU, standalone
source, and exact codegen remain unresolved.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00431E80 --json
python3 scripts/function-origins.py --check
```

## Profile binary writer at `0x004317A0`

The original PE candidate reaches all 784 bytes from its entry. The normal
path returns with `RET 4` at `0x00431AA8`; a second path ends with a CALL
at `0x00431AAB` to generated helper `0x00431610`. That helper's entire
117-byte body is pinned and ends in a direct call to VC8
`__CxxThrowException @ 0x0068A153`, followed by `INT3`. The candidate's
next bytes are also `INT3`. The boundary auditor reports an outgoing
fallthrough to `0x00431AB0` because it assumes that terminal call returns;
the pinned no-return helper resolves that edge. The main body SHA-256 is
`2cce2b6f179d22fdbe4a2e6863501072dea6be3a4600680e2c93c7e6f46f5126`.

The receiver is carried from ECX in ESI, and the body uses target
`profile/` prefix, KERNEL32 `CreateFileA`, `WriteFile`, and `CloseHandle`
imports. It writes two `0x34`-byte profile blocks, two one-byte flags,
then twenty deck counts and their short entries. Five separate exact
profile setup/UI callers make eight direct E8 calls; the rule replays exact
`initialize_default_player_profiles @ 0x0043AF30` and
`CProfileMenu_commit_state_one @ 0x0044C110` sites.

The 40-byte EH handler `0x006B8108` points to FuncInfo `0x006DE338`
with three unwind states. Two actions at `0x006B80F0/F8` tail-call
generated string cleanup `0x00401E00`; the third at `0x006B8100`
tail-calls exact `CFileWriter_dtor @ 0x00407BF0`. The origin rule pins the
full handler, FuncInfo/map, all action bytes/targets, and the no-return
throw callee. This establishes `authored_game/ui` and the 784-byte main
span with separate EH actions. Retained
`ProfileMenuBaseData::save_to_profile` is a working class/source model, not
standalone exact evidence or an independently attested class name.

```bash
python3 scripts/audit-candidate-boundaries.py 0x004317A0 --json
python3 scripts/function-origins.py --check
```

## Nine game-class scalar deleting destructors

Nine pending candidates each have a fully reachable 30-byte body and one
`RET 4`. Their instructions preserve ECX as `this`, call a class
destructor, test the low deletion-flag bit, conditionally call excluded
free alias `0x006898EA`, and return the original pointer. Each address is
an exact primary vtable entry preceded by a zero-offset VC8 RTTI locator.
The rule pins full body hashes, vtable pointers, locators, type descriptors,
class-destructor E8 calls, and free E8 calls.

| Deleting wrapper | RTTI class family | Underlying destructor |
| --- | --- | --- |
| `0x00402090` | `CHandleManager<CWaveBuffer*>` | `0x00401F10` |
| `0x004020B0` | `CHandleManager<CDSBuffer*>` | `0x00402020` |
| `0x00404090` | `CHandleManagerEx<BgmBuffer>` | `0x00403F60` |
| `0x00405040` | `CHandleManager<IDirect3DTexture9*>` | `0x00404FD0` |
| `0x004138B0` | `CHandleManager<NET_PACKET_UDP_BUFFER>` | `0x00413820` |
| `0x0041E750` | `CSelectSV`, also shared by `CSelectCL`/`CSelect` | `0x00424260` |
| `0x004226F0` | `PatternData` | `0x00422660` |
| `0x0042CBC0` | `CInputManagerEx` | `0x00409D50` |
| `0x00444470` | `CMenuConnect` | `0x00443C30` |

The primary vtable slot for `0x0041E750` is `0x006C04AC`; the same function
pointer also appears at `0x006C0504` and `0x006C0BC4` in the other two
`CSelect` vtables. This reuse does not change the wrapper's compiler origin.
All nine are `compiler_generated/exclude` scalar deletion wrappers. The
class destructors are separate functions; eight remain under origin review,
while `0x00409D50` already has authored provenance. This batch does not
assign a source TU or exact-match credit to any wrapper.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x00402090 0x004020B0 0x00404090 0x00405040 0x004138B0 \
  0x0041E750 0x004226F0 0x0042CBC0 0x00444470 --json
python3 scripts/function-origins.py --check
```

## Five inline scalar deleting destructors

Five more pending candidates have complete 31/38-byte main spans, with one
`RET 4` each, no unreached bytes, indirect jumps, or outgoing edges. All test
bit 0 of the deletion flag, write a vptr to `this`, optionally call the
excluded free alias `0x006898EA`, and return the original `this`. Unlike the
earlier destructor wrappers, these do not call a separate class destructor.
`0x0040BA90` also writes its base `IColor` vptr at `this+0x18`.

| Address | RTTI type | Virtual slot / COL slot | Body SHA-256 |
| --- | --- | --- | --- |
| `0x0040BA90` | `CDesignSprite` | `0x006D6A80` / `0x006D6A7C` | `457b2df6c0d4b2611c1262b770d0d953fd228eb715790f9c7fea134fde87d7de` |
| `0x0041DD90` | `CNetworkWinsock` | `0x006D6EA4` / `0x006D6EA0` | `42b701daaa722641fb6fd7fe98ef3b24b3822471cd8f3b4e82a918446703741f` |
| `0x0041FAB0` | `IEffectManager` | `0x006C07F4` / `0x006C07F0` | `fc34b0887cb53ea433397cab8f64d1801d908e350ae467b4e6153e0680550d6b` |
| `0x006A0890` | Boost `clone_base` | `0x006D5DD8` / `0x006D5DCC` | `f651651ece36ed6704ae2e3440975a2305dbd06e72e7dd1ec836f4c689a130a6` |
| `0x006A08C0` | Boost `sp_counted_base` | `0x006D5DE0` / `0x006D5DDC` | `685fc30ee84f3d1ff2dc8d42c3d0cd637cf2e3f093a2386cd20c1d1f84eac4a9` |

The target PE vtable pointers, zero-offset VC8 RTTI locators, type
descriptors, stored vptr immediates, body hashes, and direct free-call edges
are all replayed by the origin rule. The Boost `clone_base` entry is the
third virtual slot: two preceding slots point to `__purecall`, so its COL
is twelve bytes before the wrapper slot. The `sp_counted_base` body pointer
also occurs in four other Boost vtables at `0x006D5E04`, `0x006D5E18`,
`0x006D5E2C`, and `0x006D690C`; that reuse does not make it the
`CEffectSprite` destructor despite a similar 31-byte shape.

These are compiler-generated wrapper entries. Their observed lifetime work
is vptr restoration and conditional free; the class implementation and any
source TU remain separate questions. There is no new exact-match credit.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x0040BA90 0x0041DD90 0x0041FAB0 0x006A0890 0x006A08C0 --json
python3 scripts/function-origins.py --check
```

## Four VC8 runtime global setters

Four pending 10-byte candidates each decode fully as `mov eax,[esp+4]`,
`mov [global],eax`, `ret`. Their raw target bytes match individually named
functions in the SHA-256-pinned VC8 SP1 `libcmt.lib` after replaying one
`IMAGE_REL_I386_DIR32` field at offset five. Each COFF member SHA, symbol,
relocation symbol, target body hash, and runtime consumer body is pinned in
`vc8-short-runtime-global-setters-106a`.

| Target setter | VC8 SP1 member / symbol | Relocated global | Target consumer |
| --- | --- | --- | --- |
| `0x0068A019` | `invarg.obj` / `__initp_misc_invarg` | `0x006FD3BC` | `__invalid_parameter @ 0x0068A11F` |
| `0x0068EF7E` | `inithelp.obj` / `__initp_misc_purevirt` | `0x006FD754` | `__purecall @ 0x00689934` |
| `0x0069095B` | `handler.obj` / `__initp_heap_handler` | `0x006FDA84` | `__callnewh @ 0x00690965` |
| `0x0069BC0F` | `initcrit.obj` / `__initp_misc_initcrit` | `0x006FDE14` | `___crtInitCritSecAndSpinCount @ 0x0069BC29` |

The adjacent setter `0x0069BC05` has the same six invariant bytes, but its
global at `0x006FDE10` has no separate consumer read in the tracked target
body inventory and no resolved VC8 object/symbol identity. Shape and
proximity are insufficient to assign it to a particular library member, so
it remains under origin review. The four supported setters are
`vc8_runtime/exclude`; no source or exact-match status changes.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x0068A019 0x0068EF7E 0x0069095B 0x0069BC0F --json
python3 scripts/function-origins.py --check
```

## Four Boost exception injector copy helpers

The four 147/153/147/154-byte candidates at `0x006A5E40`, `0x006A7310`,
`0x006B4E60`, and `0x006B4FC0` have fully reachable main spans with one
`RET 4` each. Every body registers a VC8 EH handler, calls a base-copy
helper, writes primary and secondary vptrs, copies the Boost exception
payload, and returns `this`. Two already-reviewed Boost `clone_impl`
virtuals, one allocate and one throw method, directly call each helper.

| Helper | Boost RTTI specialization | Primary / secondary vptr | EH handler / unwind action |
| --- | --- | --- | --- |
| `0x006A5E40` | `error_info_injector<std::runtime_error>` | `0x006D5E94` / `0x006D5E8C` | `0x006BD458` / `0x006BD450` |
| `0x006A7310` | `error_info_injector<std::invalid_argument>` | `0x006D5E5C` / `0x006D5E54` | `0x006BC9D8` / `0x006BC9D0` |
| `0x006B4E60` | `error_info_injector<std::logic_error>` | `0x006D687C` / `0x006D6874` | `0x006BD3F8` / `0x006BD3F0` |
| `0x006B4FC0` | `error_info_injector<boost::regex_error>` | `0x006D6844` / `0x006D683C` | `0x006BD458` / `0x006BD450` |

The corresponding VC8 RTTI COLs have zero primary offset and secondary
offset `0x28`, except `regex_error` at `0x30`. The rules replay all four
body hashes, eight caller E8 edges, the base-copy calls, both RTTI
locators and type descriptors per helper, and the three complete
handler/FuncInfo/unwind-map/action chains. Each FuncInfo has one unwind
state returning to `-1`. The remote actions tail-call `0x006A4B30`,
`0x00665AC7`, and `0x00401740` respectively. These action bytes are
separate from the four main candidate spans.

The target RTTI and clone virtual ownership support Boost template
provenance (`third_party/exclude`, inferred). The original source TU
boundaries remain unresolved. The base-copy callee `0x004017A0` remains
under its own origin review; the action target `0x00665AC7` has a later,
separate EH cleanup-tail review below. Other called cleanup/base helpers
were classified separately. No exact credit is assigned here.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x006A5E40 0x006A7310 0x006B4E60 0x006B4FC0 --json
python3 scripts/function-origins.py --check
```

## Three generated subobject cleanup tails

`0x0043BF50` and `0x0046EAF0` have complete eight-byte bodies:
`add ecx,8/0x20; jmp 0x00420A80`. Their destination is a separately
excluded 104-byte checked-container destructor. Canonical-exact
`CNetworkBase` and `CInfoManagerBase` constructors and destructors each
push their corresponding adjustor address as a callback to VC8's
`??_L` vector constructor or `??_M` vector destructor iterator. The
rule replays all four exact callback pushes, the iterator E8 calls, both
adjustor hashes, and the full destination hash. The boundary auditor's
outgoing E9 is the intended tail transfer.

`0x00665AC7` is a complete 11-byte EH cleanup thunk. It restores the
`std::invalid_argument` vptr `0x006C7548`, then tail-jumps to separately
excluded generated cleanup `0x00401740`. The vptr's zero-offset VC8
RTTI COL and type descriptor identify `std::invalid_argument`. The
one-state Boost injector copy-helper EH action at `0x006BC9D0` calls this
thunk by tail jump; both action and destination bodies are pinned. These
three thunks are `compiler_generated/exclude` with no exact credit.

The analogous `0x0043BE90` tail has no independently established callback
use and remains in origin review. The constructor callback `0x0043BF60`
has a separate review below.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x0043BF50 0x0046EAF0 0x00665AC7 --json
python3 scripts/function-origins.py --check
```

## Two array-record default constructors

The 17-byte candidates `0x0043BF60` and `0x0046EAD0` have complete
straight-line bodies and one `RET` each. Both return `this` after zeroing
four consecutive dwords: at `+0x0C..+0x18` and `+0x24..+0x30`. Their paired
eight-byte destructor callbacks adjust `this` by `+8` and `+0x20` before
tail-calling the same generated checked-container cleanup; the first
cleared dword is therefore at subobject `+4` in each case.

Canonical-exact `CNetworkBase` constructor `0x0044DB10` pushes both
`0x0043BF50` and `0x0043BF60` into VC8 `??_L @ 0x0068A30C` for a
two-element, `0x20`-byte record array. Canonical-exact
`CInfoManagerBase` constructor `0x0046F5D0` does likewise with
`0x0046EAF0` and `0x0046EAD0` for two `0x34`-byte records. The origin
rule replays both callback pairs, the iterator E8 calls and all four
target bodies.

As external codegen corroboration, the existing natural VC8
`GptWeb_NetworkBaseConstructorRuntime.obj` emits the implicit
`NetworkQueueSlot20` constructor as the same 17 target bytes at
`0x0043BF60`. This probe does not establish the original class name or
standalone exact credit. The analogous battle record class and original
TU remain unresolved. The target array lifetime and zero-field source
shape support `compiler_generated/exclude`, inferred, for these two
default-constructor callbacks.

```bash
python3 scripts/audit-candidate-boundaries.py 0x0043BF60 0x0046EAD0 --json
python3 scripts/function-origins.py --check
```

## Fighter body-collision phase at `0x0046CCA0`

The hash-attested target PE decodes all 1,862 candidate bytes from entry,
with no unreached bytes, indirect jumps, invalid overlap, or outgoing
direct branch exits. Its five `RET` sites are `0x0046D0DB`, `0x0046D285`,
`0x0046D3CF`, `0x0046D3DB`, and `0x0046D3E5`; eight `INT3` bytes follow
the last one. The complete body SHA-256 is
`c6ef9cab92b2106d93cd532e0074493d3ed0b3d53abaa3ae3ad16f06f0a10cd2`.

The entry loads two Fighter pointers from receiver `+0x0C/+0x10`, clears
each Fighter's `+0x6A4` body-overlap float, and gates the active path on
the two `frame_158 +0x54` body AABB pointers. It computes horizontal
motion, updates two byte-sized boundary-owner globals at
`0x006E7B6C/0x006E7B6D`, transforms both body boxes, tests overlap, and
adjusts fighter positions/overlap fields. These are direct target
instruction and data-access observations, independent of the retained
`BodyCollision.cpp` source hypothesis.

The rule pins ten outgoing E8 calls to five separately canonical-exact
game helpers: boundary classification `0x00435910` twice, world AABB
transform `0x0046B6E0` twice, overlap test `0x0046B740`, extent reset
`0x0046B6C0`, and stage-height proposal test `0x00435950` four times.
Nine distinct canonical-exact BattleManager/Story pipeline functions
call this candidate at `0x0047164A`, `0x00471703`, `0x00471778`,
`0x004718ED`, `0x00472D8A`, `0x00472DDA`, `0x00472E5B`, `0x00472ED8`,
and `0x00472F5F`. Their individual targets and exact statuses are
replayed, rather than inferred from a call count.

This establishes `authored_game/battle` origin and the reviewed 1,862-byte
main span. The original class name, source TU, and complete semantic
coverage of the retained file remain unresolved. The standalone source
still differs from target in x87/stack lifetime, so this review does not
select it in `implemented.csv` or add exact-match credit.

```bash
python3 scripts/audit-candidate-boundaries.py 0x0046CCA0 --json
python3 scripts/function-origins.py --check
```

## Render rectangle, line, and texture-slot chain

The hash-attested target PE reaches every byte of these three provisional
candidate spans with no indirect jump, outgoing direct branch, or invalid
decode:

| Entry | Bytes | Body SHA-256 | Return sites |
| --- | ---: | --- | --- |
| `0x00401180` | 148 | `8fab1b24e1ad32aa03203b28ed4c80a795f9d83f6f21e9890e154bb531b3f28d` | `0x00401211` (`RET 0x14`) |
| `0x004012A0` | 395 | `71aa186253ca2f14ce6ffc30ac72ef5a5ff29b01f2e2e85e3493c4f6d113b347` | `0x00401351`, `0x00401428` (both `RET 0x18`) |
| `0x00404DF0` | 107 | `c507bdb541478a700181ff1d1bfd3637cbc78261eed2de6390ec68fa1fb239fc` | `0x00404E22`, `0x00404E58` (both `RET 8`) |

At `0x00401180`, the target constructs **two** 20-byte color vertices,
passes zero texture handle and slot to `0x00404DF0`, then calls the D3D9
device's `SetFVF` and `DrawPrimitiveUP` slots (`+0x164`, `+0x14C`). The
draw call passes primitive type 2, count 1, and stride `0x14`: one line
segment. An earlier draft incorrectly described it as a textured quad.

`0x004012A0` has an outline path that calls this line helper four times
at `0x004012D5`, `0x004012FB`, `0x00401321`, and `0x00401347`. Its filled
path clears texture slot zero through `0x00404DF0`, constructs four
20-byte color vertices, and calls the same D3D9 slots with primitive type
5, count 2, and stride `0x14`: a triangle strip. Eight distinct
canonical-exact callers have pinned E8 sites, including
`RenderModeManager_draw_rect_int @ 0x00401260`. The retained class label
is supported by that caller but does not prove source/TU ownership.

`0x00404DF0` itself clears a D3D9 texture slot on zero handle, or resolves
a nonzero handle through source-present resource lookup `0x00417800`,
binds its texture through device vslot `+0x104`, and caches the handle in
its receiver's `+0x64` slot array. Canonical-exact
`RenderModeManager_submit_textured_primitive @ 0x00401130` calls it at
`0x0040113F`; the line and filled rectangle paths call it with zero
handle. Thus the zero-handle calls do not make either primitive textured.

The rule pins all three bodies, eight exact rectangle call sites, four
line-helper call sites, the texture-slot calls, and the lookup call.
These observations support `authored_game` origin and the reviewed main
spans. The original class names, TU boundaries, full semantics, and exact
source codegen remain open. No source-present or exact credit was added.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x00401180 0x004012A0 0x00404DF0 --json
python3 scripts/function-origins.py --check
```

## Shared visual effect owner lifetime and configuration

The exact target PE has three individually padding-isolated complete
candidate main spans. Raw reachability covers every byte, with no indirect
jump, outgoing direct branch, or invalid decode:

| Entry | Bytes | Body SHA-256 | Return |
| --- | ---: | --- | --- |
| `0x00411430` | 138 | `de916b659088e2537ea0915c832bd7df93a934638ac508840ae8260a018ef6ee` | `0x004114B9` (`RET`) |
| `0x004114C0` | 210 | `bca6292e5e37ba2aadd6231017c3dcc9e10d28807ba36ae84fec4e4af07aa2de` | `0x00411591` (`RET`) |
| `0x004115A0` | 439 | `956579b761782920fcbd5bace551efbd03e12c27f8ab1adeefb4dd0a4147e535` | `0x00411754` (`RET 4`) |

At `0x00411430`, the receiver gets effect defaults `+0x118 = 400` and
`+0x120 = 100000`, cleared flags at `+0x11C..+0x11E`, and zeroed owner
fields including `+0x154/+0x158/+0x164`. A helper call returns the
pointer stored at `+0x160`; the string-like member at `+0x174` gets
length zero and capacity 15. `0x004114C0` walks and frees the list-like
nodes under `+0x160/+0x164`, frees the optional `+0x158` color table and
long-string buffer, and tears down the member at `+0x15C`. Its calls to
`0x0068A143`, `0x0068AA26`, `0x006898EA`, and `0x00408A00` are observed
outgoing edges. The constructor's `0x004040B0` callee and the destructor's
`0x00408A00` callee remain in separate origin review.

`0x004115A0` copies 74 dwords (`0x128` bytes) from its argument into
receiver `+0x0C`. It compares three start/end color byte pairs at
`+0x10C..+0x111`. Equal pairs yield a packed RGB value at `+0x168`;
otherwise it frees the previous `+0x158` table, allocates four bytes per
step from count `+0x114`, and fills it with integer-interpolated colors.
Both paths then clear existing list payloads when `+0x164` is nonzero.
These are target instruction and field-access observations; the retained
`ScenarioEffectOwner194`, `ProfileSlotEffectOwner194`, and
`ResultEffectOwner194` names are source hypotheses.

Two distinct canonical-exact callers each construct and destruct this
owner: `PlayerSlotRecord_set_profile_color @ 0x00431440` and
`NetworkSessionResultView_finalize_result_binding @ 0x0044DCB0`.
Those two plus exact `ProfileDeckRefreshFacade_reload_common_resources`,
`initialize_profile_ui`, `CScenarioData_set_effect_color_bytes`, and
`CScenarioData_configure` call `0x004115A0`. The origin rule replays all
ten E8 sites and the three complete body hashes. The cross-subsystem
usage and game effect/color behavior support `authored_game/engine` for
these three spans. Original class and TU boundaries, source selection,
exact codegen, and the adjacent helper origins remain unresolved.

```bash
python3 scripts/audit-candidate-boundaries.py \
  0x00411430 0x004114C0 0x004115A0 --json
python3 scripts/function-origins.py --check
```

## Server type-0x0D network send path at `0x00416B60`

Raw target CFG reaches all 548 bytes through a single `RET 0x14` at
`0x00416D81`. There is no unreached range, indirect jump, outgoing direct
branch, or overlapping decode. Both sides are separated by `INT3` padding.
The full body SHA-256 is
`f9c4811900e4c22873f2176f36dd601d1e2fc4782308c183d1c9c863a7e8d3f9`.

The body indexes receiver `+0x10C` as 0x20-byte records and skips a slot
whose `+0x10` field is `-1`. It creates a queue item through
`0x00417660` for receiver `+0x17C`, writes packet type `0x0D` at item
`+0x1C`, stores a timestamp from the SHA-attested PE's WINMM
`timeGetTime` IAT `0x006C0258`, copies the selected record prefix and a
caller payload to item `+0x1D`, and serializes the payload length at
item `+0x18`. The target PE import table independently identifies
`0x006C0108/0x006C0104` as `EnterCriticalSection`/
`LeaveCriticalSection` and `0x006C0040` as `SetEvent`. An optional
result-pointer path searches the receiver deque at `+0x168` and updates
the caller's handle before the event signal.

Five distinct canonical-exact Server methods call this candidate at six
E8 sites: `CNetworkServer_send_packet @ 0x0044F50B`,
`sync_peer_state @ 0x0044F76C`, `send_request_info @ 0x0044F816`,
`send_state_or_terminate @ 0x0044F877/0x0044F8B9`, and
`send_ack_info_if_ready @ 0x0044FF3F`. The rule replays each site and
the full body hash. Protocol type, game queue fields, Win32 ordering,
and independent exact Server callers establish `authored_game/network`
for this main span. `0x00417240` is separately excluded generated
deque code; `0x00417660`, `0x004172C0`, and `0x00405200` still need
individual origin review. The original method signature, TU boundary,
and source/exact status remain open.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00416B60 --json
python3 scripts/function-origins.py --check
```

## Four-vertex three-axis pivot rotation at `0x00407680`

The SHA-attested target CFG covers all 1,095 bytes of the provisional
candidate. There are no unreachable bytes, indirect jumps, outgoing direct
branches, or overlapping decodes. Two exits at `0x00407ABB/0x00407AC4`
both use `RET 0x18`; `INT3` bytes follow the final exit. The complete
body SHA-256 is
`313f3bb25a5e3c835faf60c91a2196b0a2d22d3507c01bcac149fe3debb69dde`.

The six stack arguments are three angles followed by three pivot scalars.
The target tests the Z angle first, then Y, then X using x87 comparisons
against zero. Each active axis calls `0x004063D0` and `0x00406360`
(currently mapped as cosine/sine quantized lookups) and updates four xyz
working vertices in receiver `+0xB0..+0xDC`, with 12-byte vertex stride.
The three axis phases account for six individually replayed lookup E8
sites. The lookup bodies are source-present but nonexact; their retained
return signatures are not needed for this origin classification.

Five separate canonical-exact renderers call this body at six E8 sites:
`RenderTimelineEntry_render @ 0x00450F57`, `BG16_render_sprite @
0x00468764`, `BG16_slot_0c @ 0x00468819/0x004689C0`,
`BGCommon_render_sprite @ 0x00469594`, and
`SystemEffectObjectBase_render_effect @ 0x00473D80`.
Canonical-exact neighboring sprite reset/translate/scale methods use the
same four-vertex working layout. This supports `authored_game/render`
origin and the reviewed main span. The `CSpriteEx::rotate_xyz` source
label is plausible but remains a hypothesis; earlier 1089/1095 source
probe notes were not revalidated here. No source selection, original TU
claim, or exact credit was added.

```bash
python3 scripts/audit-candidate-boundaries.py 0x00407680 --json
python3 scripts/function-origins.py --check
```
