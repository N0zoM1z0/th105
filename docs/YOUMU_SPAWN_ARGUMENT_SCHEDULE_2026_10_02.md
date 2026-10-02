# Youmu spawn argument schedules, 2026-10-02

## Retained result

**Observed:** `Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains
nonexact over all 37,692 callable bytes. Action 603's two offset object-853
spawns now compute their coordinates within the actual call arguments. The
generated VC8 schedule prepares arguments 7..4 before the remaining sine-Y
and cosine-X calls, as the target does. Ten unused scalar hypotheses are
removed; the real double base-coordinate carriers remain.

Fresh whole-root comparison first differs at `+0xCA / 0x005302CA`, target
`64`, candidate `CC`. Candidate metadata begins at `+0x92A4`, target
`+0x933C`; the candidate section tail is 38,664 bytes. Diagnostic owner
identity stays **26/98**, without gains or losses. All 97 physical switch
destinations / 33 low entries remain distinct. No exact credit is added.

Target callable SHA-256:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Retained CRLF source SHA-256:
`c54ed6e8c95630e4063a75fe2a0b5259209cd1e78072e0a162867ee5cfebb35f`.
Canonical compared candidate-window SHA-256:
`8d2ac3cfcb3e87224a6f73f010ba90419fa2fb34a16aaafbd8c9d2b466dacc08`.
The compared window includes candidate metadata; it is not a body hash.

## Target call/value evidence

**Observed:** action 603 first prepares two double base coordinates. The
sine-based Y value is stored as a qword at `5376FB`; the cosine-times-200
value is stored as a qword at `53772F`. These two real carriers stay.

For the following offset spawn, `537729 PUSH 3`, `537737 PUSH payload`,
`537738 PUSH 1`, and `53773C PUSH direction` prepare the trailing arguments.
Then `537741 CALL 406360` computes the remaining sine term for Y. The Y
difference is rounded to dword at `537750`, reloaded and placed in the
outgoing argument at `537758`. `537765 CALL 4063D0` computes the remaining
cosine term for X; subtraction, signed facing multiplication and peer-X
addition precede its dword store/reload and outgoing store at `53779B`.
The object-853 call is `5377A3 CALL 465190`.

The old candidate computed both coordinates in separate statements before
preparing these trailing arguments. It also stored/reloaded the two negated
float phases through named locals before copying them into helper arguments.
The target's negative phases instead use FLD, FCHS and a direct argument
store, without those two extra local copies.

**Inferred source:** the retained first call places the remaining coordinate
expressions directly in X and Y arguments, using the existing double bases.
Fresh generated code pushes arguments 7..4, calls sine-Y and rounds/pushes
the result, then calls cosine-X and rounds/pushes X. Its two negative phases
now use the target's direct argument-store shape. This removes two additional
dword frame stores/reloads. Argument home offsets and register choices still
differ. This is not a unique recovery of original source spelling.

**Observed:** the next spawn likewise prepares its trailing arguments before
`5377D9 CALL 406360` and `537819 CALL 4063D0`. Y retains
`sine*250 + (peerY+100)`, rounded at `5377F8`. X retains cosine scaling,
signed facing multiplication and peer-X addition, rounded at `537843`.
The object-853 call is `537853 CALL 465190`.

**Inferred source:** both helpers now appear inside this second spawn's
coordinate arguments. Fresh VC8 reproduces the observed trailing-argument,
sine-Y, cosine-X, spawn ordering. The float phase conversions, double base
values, final float arguments, payload extent and layer/direction contracts
are preserved. No shared helper, ABI, compiler flag or relocation target
changes. No numerical gameplay-value change or full exception closure is
claimed; only the observed local order and widths are recovered.

## Whole-root diagnostics and closed probes

The retained root still has 138 target/candidate masked floating guards,
zero differing owner guard counts and zero unordered-only leads under ordinal
pairing and finite-equivalence hypotheses. Target comparison instruction
coverage remains complete, as established in
[the preceding value-order audit](YOUMU_FPU_VALUE_ORDER_2026_10_02.md).
This is not operand, precision or exception closure.

All 49 physical spawn payloads resolve without conflicting modeled ESP
merges. The same six normalized address-sequence owners differ:
mid500/505 and high601/604/605/710. Target raw traversal still reaches
9,912 instructions / all 37,692 bytes without unresolved indirect jumps.
Arithmetic multisets remain 349/348 with leads in 601/696/710. The new
load/store multiset census removes action603's lead; other stack identities,
dependency orders and shared-owner placements remain unresolved.

Baseline direct physical calls number 598/591. The seven-site difference is
limited to two zero-motion calls, two surface-height calls, two frame-advance
calls and one effect call. Owner relocation/sharing requires separate path
reconciliation; these counts do not establish missing runtime behavior.
Virtual site counts remain 107/105 at slot8, 31/31 at slotC, 12/13 at slot14
and 2/2 at slot1C.

| Probe | Observation | Disposition |
| --- | --- | --- |
| Explicit return at shared sequence label; move label to action529 | Both byte-neutral against the preceding `347ac4b` checkpoint. | Not retained. |
| Move label plus explicit local action740 call | 25/98, loses low11, metadata `+0x92B8`. | Not retained. |
| Float zero carrier; three real payload declaration-order variants | All byte-neutral against the preceding checkpoint. | Not retained; no original type/order claim. |
| Nested first action603 spawn only | 26/98, metadata `+0x92A4`; observed argument prefix restored. | Independently tested property retained in combination. |
| Nested second action603 spawn only | 26/98, metadata `+0x92B4`; argument prefix/order restored. | Independently tested property retained in combination. |
| Both nested action603 spawns | 26/98, metadata `+0x92A4`, no gains/losses. | Retained through configured rebuild. |
| Direct action545 Y field, or move its float snapshot after payload initialization | Identical windows; 26/98, metadata `+0x9244`; 545 has 114 instructions as target, but physical spawn sites drop from49 to48. | Not retained as physical-path recovery. |
| Double action545 snapshot | 26/98, metadata `+0x92A4`; 545 still has116 instructions versus target114. | Not retained; no original snapshot type established. |

**Observed, action 545:** target initializes the payload at
`53643C..53645F`, then reads Y at `536466`, before spawning at `53648B`.
The old snapshot source reads Y earlier; a declaration does not uniquely
determine optimized machine scheduling. The direct/late-snapshot probes
merge the 545/546 spawn and subsequent half-velocity tail. Their one shared
physical spawn resolves both original payload addresses, while target has
separate calls `53648B` and `53667E`. Thus a matching local instruction count
does not establish the target's physical graph. The snapshot timing/type and
remaining value lifetime are unknown; no snapshot change is retained.

## Reproduction and remaining work

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
```

Fresh reports: `build/youmu-spawn-argument-final-20261002.json` and
`build/youmu-spawn-argument-final-owners-20261002.json`. Explicit-object
guard, stack, arithmetic and load/store reports use the same prefix with
`-guards`, `-stack`, `-arithmetic` and `-load-store` before the date.
Private probes are below `.analysis/youmu-shared-sequence-20261002/` and
`build/youmu-shared-sequence-20261002/`. The load/store census takes explicit
OBJECT, OWNER_AUDIT and OUTPUT arguments and verifies their object hash.
It normalizes stack identities and establishes no semantic equivalence.

No new analysis database output is used. The wrong-target IDA preflight
again fails; all new observations use the hash-attested PE and canonical
candidate relocation replay. Actual shared-tail placement, other argument
schedules, float lifetimes and original TU/compiler context remain unknown.
The next source audit should reconcile those lifetimes and argument schedules
before revisiting the closed label, declaration-order or snapshot probes.
Whole-root zero-difference replay remains required; this focused checkpoint
adds no aggregate cold-replay claim.
