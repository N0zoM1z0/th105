# Youmu caller widths and shared-tail controls, 2026-10-19

This bounded follow-up examines the complete Object initializer at543670
(5159 bytes), then the complete Fighter state root at530200 (37692 bytes).
Neither root gains exact credit. Their selected sources, shared headers,
compiler profiles and relocation bindings remain unchanged. The significant
new target observation is that the same object-control byte is passed as
both `FFFFFFFF` and `000000FF` at different call sites; a uniform signed
argument replacement is not justified by the former alone.

## Target identity and baseline scope

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Both mandatory IDA preflights reject the wrong open executable; no IDA
semantics are used. Fresh raw owner audits close both target CFGs:

| Root | Target callable SHA256 | Reachable instructions / bytes |
| --- | --- | --- |
|543670|`d680c9d1386e6c3f8cc5e755dffccbbd431864dee308f760cf48fe00274ed245`|1294 /5159|
|530200|`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`|9912 /37692|

The Object baseline remains23/30 owner diagnostics, code/metadata prefix5156,
complete section payload5488 and canonical payload4b9bf0a4. It has20 rather
than21 conversion sites and22 rather than23 RETs. The Fighter baseline remains
31/98, prefix37648 and payload38772. Its complete canonical payload SHA256 is
`e81b3c5fc7709907fe0f9f4c86678a55cb7441ebb359d17a1cc246cc7b458ecf`.
Its strict37692-byte window includes adjacent candidate metadata and is not
a candidate callable-body hash. First mismatches remain+80 and+CA respectively.

## Object initializer source controls

These tests use the current short-selector source, rather than assuming the
older int-selector experiments determine its behavior. Every result compares
the entire candidate section and runs the unchanged public owner audit.

| Private source control | Prefix / payload | Observation |
| --- | ---: | --- |
| Independently write820's real angle/selector tail |5176 /5508|21 conversions/23 RETs, but still23/30; wrong physical sharing remains |
| Factor the real angle/selector operation into an inline member |5176 /5508|Same complete payload as the independent-tail control |
| Define the shared tail in820 and enter it from850 |5156 /5488|Complete baseline payload unchanged |
| Void discarded selector result, with/without return expressions |5156 /5488|Complete baseline payload unchanged |
| Chain850's scales and/or823's two random-scale pairs |5156 /5488|Complete baseline payload unchanged |
| Float851 value instead of its retained double |5164 /5496|Still23/30; does not recover the target load timing |
| Int851 value captured before the state store |5156 /5488|18/30, loses five earlier equal owners |
| Short851 value captured before the state store |5156 /5488|19/30, gains the last owner but loses the same five |
| Reference851 value, directly or through a real inline selector helper |5116 /5444|851/854 merge; public owner gate rejects the candidate |

No control is selected. In particular, retaining the baseline does not
validate851's early value capture: target851 captures the pointer/vptr,
stores state344, then reads the value. A replacement must reconcile that
ordering and the target-distinct owners. Owner preservation alone is not
semantic acceptance or a proof of the source's alias assumptions.

Sources/producer are under `.analysis/youmu-entry-sharing-20261019/`;
packets and logs are under `build/youmu-entry-sharing-20261019/`.

## Fighter selector and spawn-interface controls

Canonical primary cells6C516C and6C5150 independently identify530200 at+28
and45C390 at+C. A private four-slot call view tests all38 source selector
expressions. The int-view control reproduces the complete baseline payload;
the short view produces exactly the same38772 bytes. No shared interface
is changed, and the result does not transfer the action980 recovery into
this root as an optimization rule.

The local spawn interface is then tested against the already observed control
argument difference. Changed source signatures use explicit private REL32
spellings for the same verified465190 receiver/stack ABI. No unsupported
callee address or artificial implementation is supplied. The private auditor
adds only that symbol binding and retains all public boundary/owner checks;
its receipt records the override and public auditor hash.

| Private control | Prefix / payload | Owner diagnostics |
| --- | ---: | ---: |
| Signed char or plain char control argument |37792 /38916|4/98, no gains |
| Int or unsigned int control argument |37804 /38928|3/98, no gains |
| Int control plus an unsigned-byte606 local |37804 /38928|Same complete payload as int control |
| Int control plus a signed-byte710 local, with/without the606 local |37804 /38928|3/98, no gains |
| Int control plus branch-local710 calls and actual X argument rounding |37820 /38944|3/98, no gains |
| Baseline control type plus the same710 call-expression rewrite |37672 /38796|12/98, loses19 earlier equal owners |

The interface controls first differ at+12 and change the initial constant
register assignment. These are whole-root regressions, not acceptable fixes
of an isolated argument window. `/O2 /Os` also compiles but loses the expected
low switch topology; both structural checkers fail closed. No canonical result
is claimed for that profile control. All controls remain unselected.

Sources/producer are under `.analysis/youmu-state-word-20261019/`; complete
packets, sources' compiler commands/pins and owner reports are under
`build/youmu-state-word-20261019/`. Private copies adjust only the two include
paths for their new location; the baseline control proves this byte-neutral.

## Two observed control words, one consumed byte

The bounded stack calculator
`.analysis/youmu-state-word-20261019/prove-control-words.py` independently
pins the full target root and the exact instruction windows below. It tracks
the actual outgoing stack positions, byte arithmetic, explicit stack writes
and the established cdecl RNG's net stack effect. At each465190 call it
requires seven outgoing slots and reads argument5 at callerESP+10h.

| Path | Defining operations | Helper call | Argument5 word |
| --- | --- | --- | --- |
|601 outside|536E44 PUSH3, payload address, 536E4B PUSH-1|536E7E|`FFFFFFFF`|
|606 false|538035 XOR EAX,EAX;53803E ADD AL,AL;538040 SUB AL,1;538049 PUSH EAX|538086|`000000FF`|

Both low bytes areFF. The second word is255, not minus one: AL subtraction
preserves the already zero upper24 bits. The later RNG result changes EAX
after the control was pushed; it does not change that outgoing slot. The
calculator fails on an unmodeled ESP write and asserts both complete words,
rather than assuming a signed extension from the consumed byte.

The raw66-byte465190 wrapper forwards whole argument words, adds two leading
factory arguments, and returns with RET1C. Root argument5 at entryESP+14h
therefore becomes factory argument7 at entryESP+1Ch. Youmu's237-byte factory
53B1C0 reads that byte at53B266 and stores it to object+33C at53B298; its nine
stack slots are cleaned by RET24. Fresh complete decoding covers25 and67
instructions respectively. The proof receipt is
`build/youmu-state-word-20261019/control-words-proof.json`.

These observations separate word transfer, byte consumption and original
source declarations. Neither differing upper bits nor a low-byte consumer
alone uniquely proves a signed-char, unsigned-char or int formal. The result
does not establish an original TU or a general compiler scheduling barrier.

## Independent Ghidra check and limits

One direct read-only Ghidra process re-attests the imported target, entry,
Windows x86 analysis target, full mapped text, both roots and the two callees.
It corroborates manager vslot4 at6C5118 and temporarily supplies the observed
physical interfaces: ECX receiver, seven/factory-nine stack slots, RET1C/24,
wrapper control Stack[14h]:4 and factory control Stack[1Ch]:1. The factory
view uses `undefined1` for the copied bytes so it does not invent signedness.
Metadata is read back before bounded decompilation; output remains a hypothesis.

All nine saved primary DB pins are unchanged afterward, and the project alias
is removed. This is not a saved metadata promotion or a native gameplay test.
The current primary pin file remains the action980 checkpoint's file. No cold
aggregate replay, new exact byte credit or accepted-source ABI change is claimed.
