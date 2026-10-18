# Reimu: height-definition visibility and the 300/320 shared prefix

The current root source is retained. Making the real height getter visible
changes field-read timing and loses the target's eight-byte Y snapshot without
recovering the remaining physical call sharing. Two exit-shape controls also
leave 300/320 merged. These are new constraints on the reconstruction, with no
new root source-present or exact credit.

## Identity and scope

Target is original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The root is `[478FA0,48CE2E)`, 81,550 bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Its ledgers remain authored/unclassified/declaration-only. No shared source,
ABI, compiler profile, relocation ledger or accepted match unit changes here.

The source baseline is commit `c39c49b`, whose genuine ordinary object is
`4f2dada4ea46b61e53cadd2b991d9250d307a616d17e9f23df19396ec8c71cfb`.
Its complete 82,904-byte canonical ordinary/linked payload is
`c927ac8906a31ee59f3427681c573ad25136d94199a653650ef8c6d881e635cf`.
The baseline still differs from the target at +541, the JNE displacement at
4791BD. Equality between two source payloads below is not target equality.

## Observed 300/320 prefixes

The target has two separate 95-byte, 26-instruction prefixes:

| Action | Prefix, including advancement | Advancement call |
| --- | --- | --- |
| 300 | `[47CBBD,47CC1C)` | 47CC17 |
| 320 | `[47D96A,47D9C9)` | 47D9C4 |

Their instruction/register/edge shapes agree after accounting for relative
encodings. They call landing473DD0, gate478EE0 with zero, test AL, apply the
47E-gated friction, then advance4351C0. This is instruction-shape evidence;
their relative fields are not identical canonical bytes. The following action0
virtual calls use different registers: 300 calls EDX at47CC29, whereas 320
calls EAX at47D9DA. Both reach the actual shared timer/frame3 event27 tail at
47CC2B. The candidate merges both complete entries at47CC10.

Two private controls preserve the operations but change outer-switch exits:

| Control | Result |
| --- | --- |
| Only 320's final return becomes break | 300/320 still merge; differing direct partitions increase 6 to 7, adding4359F0 |
| Middle region's flat cases use breaks | 74 exits in30 arms change; nested loop/switch cases stay intact; 300/320 still merge; differing direct partitions increase to8 |

The middle-only control also loses the complete owned-request243/243 and
wave77/77 partitions, producing243/241 and77/75. Both controls fit the reviewed
size limits, but neither is selected or executed. The missing separate
advancement site is a physical sharing question: per-action direct-call
cardinalities already agree. A smaller generated body is not sufficient.

An additional effect62 control captures facing as one unsigned byte, consuming
its signed-byte interpretation for X and its unsigned interpretation for the
direction argument in410/414/416. All82,904 canonical bytes remain identical to
the baseline. It does not recover the two missing virtual-next memberships.

## Real height-body visibility

The accepted `StageGeometry.cpp` getter body is adapted only to the existing
root helper name and offset-proved actor pointer view. The float return and
fastcall ECX/no-stack-argument interface remain unchanged. All89 canonical
helper bytes agree with435D60, SHA-256
`4896deab933804203efe263ac8d771c5a471cc54e11b56fa25a6ed2134550895`.
This reuses an existing accepted anchor; it adds no exact credit.

Three definition-visibility controls isolate the change:

| Definition available to compilation | Complete root result |
| --- | --- |
| Same body under an unreferenced control name; called getter stays opaque | All82,904 baseline bytes unchanged |
| Called getter defined before the root in the ordinary TU | Prefix81,436 / payload82,808 / frame568h |
| Original opaque root `/GL` object plus separate true getter `/GL` object | All82,808 bytes agree with the ordinary visible-body control |

The visible-body canonical payload is
`00cc908bce1885fe532c3cf47e5f302ca302984399f4d3e13de09354c9a8503c`.
Its first target difference is now +8=478FA8, frame568h versus570h. All58 height
calls remain, and the root has no new stage-array references. The observed
change therefore does not require inlining the height body into the root.
A separate24-byte small caller also retains the call; it is not evidence of
small-caller inlining.

The decisive read-order example is616's current-Y comparison:

| Image | Observed order |
| --- | --- |
| Target | FLD Y489DFA; FSTP m64 `[ESP+18]`489E02; CALL height489E06; FCOMP snapshot489E11 |
| Current opaque candidate | FLD Y489DDC; FSTP m64 `[ESP+18]`489DE4; CALL height489DE8; FCOMP snapshot489DF3 |
| Visible-body candidate | CALL height489D88; FADD300; FLD Y489D93; FCOMPP489D99 |

The same C++ `const double current_y` no longer forces the observed snapshot
when the callee's true definition is available. Other next-Y expressions also
move actor reads after the query. This is a compiler-context observation, not
proof that a const local guarantees a spill or that the original TU was opaque.
The representative action10 landing's ECX reload is unchanged; these controls
do not establish a new ECX-clobber explanation.

Complete source partitions for all32 direct callees, and aggregate indirect
memberships with physical multiplicity, remain identical to the baseline.
Owned243/243 and wave77/77 still agree. Advancement stays121/120, with300/320
at47CC10; six direct partitions still differ. Aggregate indirect counts remain
220/221, with per-action deficits only410(4/3) and416(5/4). Visibility does not
repair the remaining sharing problem in this source phase.

## Qualification, reproduction and limits

The public opaque-provider audit correctly rejects a defined helper as an
unqualified external call. That guard is unchanged. A private closed-unit
diagnostic first qualifies the unique helper's full89 bytes and its own COFF
section/value, then permits only that proved provider. It replays all2,475 root
fields:1,187 calls,1,104 numeric literals,14 metadata addresses,163 code pointers
and7 globals. All11 switches and15 request/preparation contracts still pass.
This is a separate diagnostic contract, not root admission.

The linked control reuses the original root IR and pinned genuine providers,
removes only the height weak alias, adds the separate real height IR and exports
that helper. MAP ownership places the root at10001000 and getter at10015380.
All89 helper bytes, its five typed fields and four HIGHLOW fields qualify.
The root then agrees with all82,808 ordinary visible-body bytes, all1,281
HIGHLOWs and the separate eight-byte INT3 alignment gap. The linked image SHA is
`1e3c60d6aa82c8f7b80df838c0d7b624c22ccdd72b8b8b49ce61146f166548b3`.
Neither visible-body image is executed; no behavior or target-root equality
claim follows from this source-to-source correspondence.

Private recipes, receipts and readbacks remain under `build/reimu-300-320/`:
`terminal-break.py`, `middle-breaks.py`, `effect-direction.py`,
`height-visible.py`, `height-control.py`, `height-proof.py`,
`separate-height-ltcg.py` and `separate-height-proof.py`. They pin the unchanged
`build/reimu-ltcg/` source/object/provider cache and compiler commands. The closed
provider/census recipes and complete partition comparison remain alongside
their reports. Large generated source/object/link products were discarded;
regenerate them before reusing an inspection command. The initial visible-body
wrapper failed while saving receipt metadata after both compilations; COFF and
input hashes were read back to recover the receipt without recompiling.

Focused public commands run in this checkpoint include:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py \
  build/reimu-300-320/middle-breaks/candidate.obj --diagnostic-oversize
nice -n 10 taskset -c 0 python3 -B scripts/build.py \
  --unit cross-v106a-stage-geometry --compare --json
```

All four existing geometry comparisons pass:435910/59,435950/120,435D60/89
and434EE0/69. This supports the getter anchor, not a new leaf-work checkpoint.
No unchanged native matrix or aggregate exact-unit replay is repeated.

Direct bounded Ghidra instruction readback independently attests the imported
image identity, entry/language/compiler, complete mapped `.text` and root hash
before inspecting the two prefixes and three effect62 windows. No full-root
decompilation or saved metadata write occurs; all9 primary DB hashes remain
unchanged. The temporary project alias is removed. Heavy work is serial with
CPU0/nice10; the bounded Ghidra run takes10.36s and peaks326,572KiB (319MiB).
Cleanup removes29 obsolete files/3.57MiB and verifies all164 files in the current
genuine cache remain unchanged. Recipes, receipts and small real-body witnesses
remain available.

Next investigate independently observed control flow and live values at the
remaining effect/height/zero/landing/action-gate and410/416 exits, preserving the
complete owned/wave and landing groups. Do not repeat these exit or visibility
controls without a material source-phase change. Getter equality alone does
not identify the original TU, and the precise original visibility remains open.
