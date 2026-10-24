# Iku control mode: complete exact representative

## Accepted result

Iku Fighter primary slot `+0x5C @ 0x0062F450` accepts **2,609 callable bytes**
and the complete **2,916-byte emitted payload**, including all switch tables
and alignment. Formal and independent cold builds replay **98 relocations**
(26 REL32 /72 DIR32) with zero differences. Only callable bytes earn authored
credit. The pinned VC8 SP1 `/O2` profile remains unchanged.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-iku-control-mode --compare --json
python3 scripts/audit-iku-control-mode.py
```

Run both commands. The full audit checks every returned section-tail byte and
its exact length, replaying relocations beyond the callable boundary too. The
formal object/provenance is retained; only this unit's active object/sidecar
were removed before the independent cold compile. A negative changes the first
emitted destination's addend in a separate generated object; full audit rejects
it at `+0xA34 /0x0062FE84`, target38/source39. The target is never modified.

Callable SHA256:
`10915c08cd2ddd00b1967811cbaa6f932bf3f03f777df21b2657b25ce4c20df7`.
Complete canonical SHA256:
`fc3ed17f652b11d6aa7f5b053fb32a87ed72f4665e5455820c41afe50682b135`.

Source is `src/characters/IkuControlMode.cpp` and its pointer-only declaration
header. Never instantiate or embed these views. It retains numeric actions,
field offsets and real consumed locals; full class recovery is deferred.
Declaration-only callees receive no new source/exact credit. No assembly,
byte array, inert local, fake return, padding, ABI lie or compiler-profile
search is used. Earlier accepted source/header pairs are unchanged.

## Observed target evidence

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is inspected. Existing RTTI origin ownership classifies the root as authored.
Raw primary vtable cell `0x006C6588` binds slot5C to62F450. The same table's
slot08/0C cells point to45BFE0/45C390; their accepted call views are int(short)
and int(int). Slot58 points to the shared5F1F80 policy; the present root invokes
it through the vtable and does not implement or newly credit that callee.

Complete raw traversal closes **710 instructions**, **11 RET0s**, all internal
direct edges and all13 destination entries. There is no external tail or
unresolved register jump. Callable end is exclusive `0x0062FE81`, followed by
three-byte LEA alignment. Four destination tables start at62FE84,62FE94,
62FF94,62FFA4; the two byte-index tables start at62FE8C and62FEA0 and contain
8 and244 bytes. Full payload ends exclusively at62FFB4. Native padding before
the root and after the payload is independently checked.

There are **26 direct calls**: checked deque4399C0 once, facing478E60 twice,
selector4067D0 sixteen times, wave dispatch45C030 once, spawn465190 four times,
and orientation cosine4063D0 twice. Another **11 virtual calls** comprise ten
action calls and one slot58 CPU call. The CPU transfer is a CALL followed by
frame teardown, not the tail jump found in some peers.

The prologue aligns ESP to eight bytes, reserves38h and saves EBX/EBP/ESI/EDI;
it establishes a genuine zero-valued EBP lifetime after saving the frame
pointer. Real three-float spawn packets, the floating loop variables and the
double angular expressions account for the native frame without shaping data.
Existing accepted spawn ABI supplies id/float x/float y/direction/variant/
packet/count; its seven argument words and native cleanup are checked.

## Complete-source comparison and focused corrections

The first complete source already emits2916 bytes with the correct table start
at+0xA34 and all helper-call counts. Private probe00..04 retain every trial.
No runtime matrix was needed because raw operands and whole-object comparison
resolved each concrete discrepancy.

| Trial | Evidence-backed source change | Complete comparison result |
| --- | --- | --- |
|00|Complete independent body; no partial stub comparison.|2916 bytes; first mismatch+0xAC from downstream size, one extra doubling instruction plus switch/comparison differences.|
|01|Write real velocity doubling as `vy*2` instead of `vy+vy`, matching native FADD ST0,ST0.|First mismatch+0x64E; all callable instruction counts now agree.|
|02|Order both identifier switches3,2,1,0 as their native physical blocks.|First mismatch+0x652; branch/table order now agrees.|
|03|Assign count, burst period, then period, matching each native block's consumed local stores.|First mismatch+0xA06; only final floating comparison remains.|
|04|Compare float(counter-1)>limit with counter first, preserving ordered x87 operands and TEST AH,5/JP.|Full2916 bytes exact.|

The ordinary expressions retain the native floating widths:640.0f, .25f,
10.0f/-10.0f and count/limit values are float, while8.0,2.0,4.0,100.0,
360.0,180.0 and the loop increment are double at their observed consumers.
Direction multiplication uses a signed facing byte; spawned direction reads
use MOVZX. A random selector result is consumed as unsigned. In particular,
`unsigned(selector_random_roll(6)-3)` deliberately preserves the native SUB,
signed-test and 2^32 correction, rather than inventing a signed range.

Records0..3 and the second motion branch retain the target's ordered x<=640
condition, including its unordered branch. Do not copy Marisa's separately
proved x>640 facing semantics. Records8..11 do not increment the control state
after action730. Records248..255 dispatch the actual virtual CPU call. Records
12..15 publish state1 before action740 and preserve the separate two-word
fallback stores. Post-call reads, distinct RNG calls and right-to-left spawn
argument evaluation remain explicit.

The global remains `g_match_identifier @0x006FA894`; no gameplay name is
invented. Both native identifier switches cover0..3 and omit initialization on
the default path. The first default even reads an uninitialized stack slot for
both periods. Source preserves the same absence of initialization; adding a
zero/default gameplay value would change target behavior and code generation.
Valid-domain assumptions and original invalid-input behavior remain unknown.

## Inferences and remaining unknowns

The retained cosine source suggests a double return, while raw x87 ST0 alone
does not prove its original nominal return type. The pointer call view uses
that declaration; complete caller comparison verifies emitted call/consumer
behavior, not original source spelling. This callee remains source-present
and nonexact. Original full owner identity/layout, untouched virtual signatures,
translation-unit partition and source declarations are not claimed recovered.
No LTCG impossibility is inferred: ordinary standalone VC8 compilation is exact
for this bounded unit.

IDA preflight fails against the different executable currently open there; no
semantics or metadata writes from that session are used. One read-only Ghidra
process independently checks imported file identity, entry68B9D2, x86 Windows
language/compiler and all raw-backed sections against the hash-attested PE.
Its temporary call-view types and bounded function are hypotheses; raw control
flow, ABI and operand widths govern the source. Changes are rolled back, and
all nine pinned primary DB hashes are unchanged. Heap is384MiB and maximum CPU
count1. Compilation is serial under CPU0/nice10; available memory is monitored.

Private recipes, frozen first source and four focused trials remain under
`.analysis/exact-first-iku-slot5c-20261024/`. The corresponding `build/` scope
retains complete raw CFG/tables/literals, attested decompile views and DB pins,
formal/cold comparisons, original formal object/provenance and table negative.
Public ledgers record1396 exact functions/324774 callable bytes after this
acceptance; these are ledger totals, without a new aggregate cold replay.
Continue independently reviewed same-slot peers. Marisa's complete source and
its neutral receiver-schedule controls remain parked.

The full origin-census replay also catches stale expected counts in the
`skip_matching` Fighter-vtable rule: its64-root/1124191-byte subset still
included the fourteen accepted input peers. With Iku included, the current
nonmatching subset is49 roots/1034331 provisional bytes. The immutable73-root
RTTI pointer witness is unchanged. The fourteen prior peers already have
`canonical-exact-authored` labels; regeneration moves only Iku's evidence label
to that baseline. Authored/excluded/review dispositions and byte denominators
stay unchanged. This maintenance assigns no additional exact
credit and does not substitute for aggregate cold replay.
The existing origin-rule test now also compares this selector's actual row
count and byte sum to its configured expectations, so future exact promotions
cannot leave stale subset counts hidden behind a constant-only assertion.
