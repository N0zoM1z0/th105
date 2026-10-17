# Iku effect62 shared continuation

This is target-backed source/control-flow recovery for the complete Iku
`dispatch_action_state_vslot28 @ 00620920`, not canonical exact acceptance.
The executable remains original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `[620920,62EFBE)` is59038 bytes, SHA256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
The IDA preflight again rejected the wrong image. No database was used or
changed; observations use the hash-attested PE and freshly compiled VC8 COFF.

## Observed target and selected source

Actions416/417/565/566/567/568 share the physical effect call626C3B and the
following vslot14 sequence transition/RET. Each path pushes trailing1,
direction and rounded Y, leaves X in ST0, and reaches626C34:

```text
626C34  FSTP DWORD PTR [ESP]
626C37  PUSH 62
626C39  MOV ECX,ESI
626C3B  CALL 435240
626C40  MOV EDX,[ESI]
626C42  MOV EAX,[EDX+14]
626C45  MOV ECX,ESI
626C47  CALL EAX
626C49  ... RET
```

416 falls through;417 jumps from626FC3;565 from629DF8;566 from62A5CA;
567 from62AE2B;568 from62B6D3. The complete29-byte continuation
`[626C34,626C51)` hashes to
`7eb16fe79240428281e876491cb1f13b8c28065600e488f677d97c680d1e5f51`.
416/417 use rounded `Y+132` and rounded `X-facing*47`; the remaining four
use rounded `Y+150` and raw X. The latter must preserve negative zero.

The selected source assigns two live coordinate values and branches from
these six terminal paths to one `emit_sequence_effect` continuation. Both
values are assigned on every incoming edge. It emits effect62, calls the
actual sequence method once, then returns. This is an explicit representation
of the observed shared control flow, not a claim about original C++ variable
names or use of `goto`. There are no dummy initializers, padding, injected
results or new callable helpers. Ordinary public ABI and vtable remain intact.

The previous source had five physical effect sites for these six actions.
The selected source has one at62B4B6 with exactly the target incoming action
set. Whole-root effect sites fall58 ->54, matching target54. Ordinary CALLs
fall867 ->863; target has865, so this does not close other call-sharing
differences. Expanding ordinary sites by incoming action/callee leaves only
the known action730 facing helper mismatch: five candidate sites versus four
target sites. This static count relation does not prove feasible paths or
values. Total register sites are175 versus178 before/177 target; RETs129
versus133 before/131 target. Counts are diagnostics, not acceptance criteria.

An ordinary forced-inline effect/transition wrapper was byte-neutral and is
unselected. A private double X carrier kept X live longer but still required
an extra narrowing store/reload and grew the section59502 ->59518; it is
unselected. The retained float-coordinate continuation still stores/reloads
X at its join62B493, unlike the target's partial outgoing-argument join626C34.
That remaining lifetime and join placement are unresolved.

## Focused reproduction

```sh
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --sequence-effects --output build/IkuEffectFinalNative.obj
python3 scripts/probe-iku-upper-actions.py --sequence-effects --control effect-height
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuEffectFinalNative.obj
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj --partition-payloads
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json
```

The strict comparison and deliberately wrong control exit1. Current source
CRLF SHA256 is
`69c43bf58dcfbeee08866a93b007fa266718a37c7850b79609056b3920fa864b`.
The59502-byte canonical section SHA256 is
`dac7642939ffc375a5fc6095057722c35a47ebc7112faf978e9bdfcfd3b3f751`.
Configured/native sections normalize identically. Candidate has15002
reachable instructions/58344 instruction bytes in58347 callable span,
three internal alignment bytes/1155 following metadata/alignment bytes,
zero local CALLs. Compared with the preceding source, the section is288
bytes smaller. Strict whole59038 remains nonexact at+0x64/620984. Physical-
owner diagnostics are now6/109 (2/4/5/204/215/303), formerly7 including321;
neither result is function or partial credit.

The new1584-case whole-entry native profile passes with zero differences:
632 effect entries,528 action entries,24 object entries and400 RETs;588
target-root instructions. It uses genuine root/prelude/geometry/frame/math
helpers and stops at the first actual backend, without replacing returns.
The coordinate grid includes both facings, both PC53/PC64 x87 control words,
raw signed zeros/subnormal X, finite small/large Y, adjacent frame/timer
gates, sequence indices, effect enable bytes and resource/input gates.

| Action | Real effect62 entries | Raw negative-zero X entries |
| --- | ---: | ---: |
| 416 | 122 | 0 |
| 417 | 122 | 0 |
| 565 | 72 | 12 |
| 566 | 72 | 12 |
| 567 | 122 | 20 |
| 568 | 122 | 20 |

Input SHA256:
`71f49574e604d816f36c33be5ea027a74690923a6cedcb738ca8b91651c895ae`;
target output SHA256:
`ffaaf034ffa85cc3159188d3b84d85d4bbe3febfb9b0fc845b22bb6ef15df984`.
The wrong `effect-height` control adds1 to outgoing Y and detects536/1584
differences across all six actions (98/98/72/72/98/98). Binary32 rounding
absorbs that increment in the96 large-Y effect cases. The real effect's
return, following sequence callback, allocation/render work and exceptional
continuation are outside this native scope; the following call's receiver,
slot and cleanup are static ABI evidence.

Frame400hex/84 payload homes remain natural. The incoming-action/pointer audit
closes182 spawn sites/190 action-site records per image. Under conditional
action-group/physical-ordinal pairing all84 constraints remain singleton/
bijective with no issues;57 are identity, previously59. Candidate pre-epilogue
unique PCs14744/states16894; target14870/16959. Changed storage correlations
and owner counts are compiler diagnostics, not source-variable or payload-
value proof.

Reports are `build/iku-effect-final-{compare,native,control,facts,payloads,
owners}.json`. Previous native/link results retain their earlier source
hashes in [conditional exits](IKU_LANDING_ARGUMENT_OWNERSHIP_2026_10_17.md)
and [glide exits](IKU_GLIDE_EXIT_OWNERSHIP_2026_10_17.md); they were not broadly
replayed. No accepted shared header/layout/profile/relocation or exact ledger
changed. Original source/TU/inheritance/compiler-phase provenance and full
post-backend behavior remain unknown.
