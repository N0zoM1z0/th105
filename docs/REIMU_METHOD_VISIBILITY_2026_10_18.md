# Reimu: method IR visibility and facade aliases

A real provider compiled with `/GL` does not by itself establish that its
implementation is visible through a facade alias. This experiment supplies
a positive direct-call control and checks the entire Reimu caller payload.
The selected root remains nonexact; no game source or default profile changes.

## Target and controlled source

Target is original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The bounded root is `478FA0..48CE2E`,81550 callable bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The IDA metadata preflight rejects the other executable; no IDA semantics,
Ghidra process, factory adapter or target instruction write is used.

The [existing real root link](REIMU_REAL_LINK_2026_10_18.md) deliberately uses
ordinary opaque providers. Its root-facing method names are connected to
real provider methods by `/alternatename`. To investigate method visibility,
the probe adds only `/GL` to the complete, unchanged
`src/battle/FighterLandingTransition.cpp` recipe. Before that change, a fresh
ordinary build matches all four methods against the canonical target:

| Method | Target | Ordinary exact bytes |
| --- | --- | ---: |
|resolve_stage_surface_landing_transition|473DD0|442|
|has_crossed_stage_surface_while_descending|5F9310|64|
|publish_battle_layout_scalar|4359D0|21|
|dispatch_indexed_event_member|4359F0|14|

All other objects, libraries, compiler flags and the real root IR remain
pinned. These are actual source implementations and CRT dependencies.
No replacement helper, register constraint or forced-inline directive is used.

## Alias/direct pair and positive control

Three private links use that same real provider IR:

1. **Alias:** the ordinary root-facing facade calls and existing linker aliases.
2. **Direct:** only the root's event-member receivers change to
   `reinterpret_cast<FighterLandingTransitionView *>(this)`. The private
   declaration preserves the actual provider's full class declaration and
   offset checks, so the caller and provider use the same class definition.
   A private relocation binding names the already proved4359F0 method.
3. **Witness:** the alias root plus two short, truthful C++ forwarding callers,
   one through the facade method and one through the real method declaration.
   The callers are diagnostic exports, not reconstructed target functions.

Before linking the direct root IR, its ordinary COFF compilation independently
replays to the **same complete82916-byte canonical payload** as the selected
root. Thus the receiver spelling changes no caller instruction, parameter,
branch, local table or canonical relocation value in the ordinary anchor.
Only the linker-facing method identity differs.

The two short callers establish a real difference in this tested VC8 context:

| Short caller | Bytes | Observed real call |
| --- | ---: | --- |
|Facade alias|15|4359F0 member wrapper remains; actor is loaded into ECX|
|Direct method|12|member wrapper is inlined; calls the global indexed-event dispatcher|

The direct caller no longer loads the actor into ECX and uses a caller stack
cleanup after the global call. Both sources simply forward their actual
arguments. Their complete decoded bodies close through RET and their one E8
destination is checked against the named real MAP provider. No witness is
executed. This is a positive visibility/inlining control, with the alias
caller as the counterexample to treating all linked IR as caller-visible.

## Complete giant-root result

The giant root itself retains **55 event-member calls** in all three links,
including the link using direct method symbols. All1178 direct calls remain.
Calls to the other three provider methods remain95,75 and5 respectively.
The small caller's inlining therefore does not predict the giant root's result.

Each private root is checked against the ordinary producer over every one of
its82916 payload bytes. The existing field replay checks all2466 fields:
1178 E8 calls,1104 numeric operands,14 metadata pointers,163 code pointers and
seven absolute game-data addresses. Literal bits, widths and original target
anchors are independently checked; the exact1281 HIGHLOW inventory and the
separate12-byte INT3 linker gap are required. Nothing is masked. All three
canonical payloads have SHA-256
`826889ee7ec055e44def5cc1602de2fae75f58403e2332194ec3b20cd55dc0d3`.

Consequently prefix81544/frame570h, all11 switches, the existing physical
sharing differences and strict first mismatch **+17/478FB1** persist. In this
tested context, genuinely naming the event method directly still does not
explain or repair the root's zero-register/sharing differences.

The normal producer's rejection of provider IR without separate ABI proof
is unchanged. These replays prove the complete **caller payload** corresponds
to the ordinary root; they do not canonically qualify the four IR-generated
callee bodies or admit the private DLLs to native execution. Original TU
ownership, original visibility and the cause of the giant caller's different
inlining behavior remain unknown. A compiler size/inlining budget is a
hypothesis, not a measured threshold or a target fact.

An earlier bounded source probe also saved an unsigned facing byte before
each520..523 object815 request and reused its signed low byte for X. It
compiled to exactly the same82916-byte canonical payload, so no such source
change is selected. Repeating this spelling with unchanged evidence cannot
address the observed815 tail merge.

## Reproduction and next step

```bash
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-method-visibility.py
```

The probe first reattests the genuine base, rebuilds the four ordinary anchors,
then performs the provider/root/caller builds and three links serially. It
requires the direct ordinary root anchor, complete linked root correspondences
and both opposite short-caller results. `--help` performs no build. The receipt
under `build/reimu-method-visibility/` records commands, source/class/tool hashes,
object/image/MAP hashes, unchanged base inputs and decoded witness bodies.
Large private sources, duplicated inputs and binaries are cleaned after
verification; compact receipts and maps remain reproducible from the script.

The completed run uses CPU0/nice10 and peaks at approximately301MiB child RSS.
All9 primary analysis database files hash unchanged by streamed reads. No
native historical matrix or aggregate cold replay is needed for this tool-only
experiment. The selected ordinary object remains SHA-256
`41bf3b15ff2dbf6cf7c25e0c0191ab18d963782e0e7fab5d3b9af82c0ab245fd`.
There is no new root source-present, exact or partial-byte credit.

Future method-IR investigations need a real direct-symbol positive witness
before drawing conclusions about visibility through aliases. The earlier
atan2 probe already calls its global function directly. Continue recovering
target-backed argument/field lifetimes and the300/320,215/310/797,522/523
sharing context; this experiment does not justify arbitrary ABI, flag or
duplicate-condition changes.
