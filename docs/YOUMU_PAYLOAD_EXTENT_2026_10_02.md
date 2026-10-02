# Youmu object-853 payload extent and stack facts, 2026-10-02

Follow-up: [float X carriers and extended x87 guard coverage](YOUMU_FLOAT_CARRIERS_2026_10_02.md)
now report 26/98 diagnostic owners, metadata `+0x92B0` and first mismatch
`+0xCA`, target64/candidateD8. Measurements below describe the preceding
payload-extent checkpoint; its three-float correction remains retained.

## Retained result

**Observed:** the three object-853 requests in action 603 of
`Youmu_dispatch_action_state_vslot28 @ 0x00530200` consume one contiguous
three-float payload. The old source split it into `int v444[2]` and an
independent float `v445`; VC8 removed every write to the independent scalar.
The retained source uses `float payload_444[3]` and writes its third element
before each request. This restores actual target data, not a padding local.

The complete 37,692-byte callable remains **nonexact**. Fresh configured
comparison first differs at `+0xCA / 0x005302CA`, target `64`, candidate `F5`.
Candidate metadata is now `+0x92D0`, versus target `+0x933C`; it grew 28 bytes
from the previous `+0x92B4` checkpoint. Strict owner auditing remains
**24/98 diagnostic owners**, with no gained or lost identical owner.
Candidate still has 97 physical destinations / 33 low entries.
No exact function or byte credit is added.

Target callable hash:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Retained CRLF source hash:
`818478d3ebb8ee203323b72e7666e3eab53c69b41d1bb7f4d0034b2788acbf0c`.
Canonical compared candidate-window hash:
`cd41f1a2580dc0e1ac47bca14946ebc8e702c1516cd99de2adfc47ca60abf243`.
The candidate window includes its earlier metadata; it is not a body hash.

## Observed contiguous extent and consumer

Stack slots below are relative to ESP after the root's saved-register pushes,
with each outgoing argument push/subtraction and callee purge accounted for.
Both target and candidate have the same aligned `0x230` local frame.

| Request | Target call | Payload base | Third-element target store | Value |
| --- | --- | --- | --- | --- |
| First object 853 | `5375DA` | `+0x28` | `53759B FSTP [ESP+38]`, normalized `+0x30` | 2.0 |
| Second object 853 | `5377A3` | `+0x28` | `5375E1 FSTP [ESP+30]`, normalized `+0x30` | 1.0 |
| Third object 853 | `537853` | `+0x28` | `5377AE FSTP [ESP+30]`, normalized `+0x30` | 3.0 |

Each request passes a count of three. The first two elements occupy `+0x28`
and `+0x2C`, so the third at `+0x30` belongs to the same 12-byte request.
The flat forwarding helper at `0x465190` has `RET 1C`. Its Youmu manager
consumer at `0x53B1C0` independently establishes the counted-copy contract:
`53B217` reads the count, `53B248 LEA EDX,[EDI*4]` computes the byte length,
and `53B252` calls memcpy with the supplied source pointer. Thus a count of
three copies 12 bytes, not only the two separately declared array elements.
These are fresh raw target observations; the matching helper/manager source
views corroborate them without establishing unique original declarations.

The old candidate payload base was `+0x2C`, and all standalone `v445` stores
were absent. C++ declarations of an array and a separate scalar provide no
contiguity contract. The new three-element array has the target's `+0x28`
base and retains all three dword third-element stores. Their candidate
addresses are `5374F3`, `537539` and `537715`, before calls `537532`, `53770A`
and `5377BD` respectively. Remaining instruction scheduling and floating
lifetimes in action 603 are not claimed exact.

## Raw stack-pointer packets

A private analysis walks the root CFG after the saved-register pushes and
stops at frame teardown. Direct-call purges come from raw helper RET
instructions; indirect calls use the observed sequence slots and their
existing ABI contracts. All four switch tables are checked as in-root code
destinations. There are no conflicting modeled ESP merges.
Reverse instruction def-use tracing resolves the sixth argument of all
**49 physical spawn sites** in both target and candidate, including shared
sites reached from different actions. It reports stack addresses, explicit
push definitions and any unresolved values rather than borrowing source
array names. The retained third-element stores are checked against the
resolved payload base and dword width.

The baseline packet found differing payload-address sequences in seven
physical owners; the extent correction closes the action-603 discrepancy,
leaving six: mid 500/505 and high 601/604/605/710. This is a scoped address
fact, not a complete ownership or numerical audit. Reconstruct their real
argument schedules and lifetimes rather than assigning padding or arbitrary
stack addresses. The root frame size itself was already identical.

Private script: `.analysis/youmu-payload-lifetimes-20261002/stack-packets.py`.
Final packet: `build/youmu-payload-lifetimes-20261002/final-stack-packets.json`.
The preceding angle guards remain: the 136-guard ordinal scan has zero
residual unordered-only leads after this correction. It remains a diagnostic,
not full numerical or exception-environment closure.

## Isolated probes and byte-width discrimination

| Probe | Observation | Disposition |
| --- | --- | --- |
| Three-float extent only | Metadata `+0x92D0`, 24/98; restores base and third-element writes. | Retained through a fresh configured build. |
| Other int payload arrays/scalar changed to float | Same canonical compared window as the previous baseline, metadata `+0x92B4`, 24/98. | Byte-neutral; broader type edits not retained. |
| Extent plus those type changes | Same canonical compared window as extent only, 24/98. | Broader edits not retained. |
| Action 601 spawn moved into both range branches | Metadata `+0x92E4`, 12/98; loses twelve previously identical owners. | Rejected as a whole-root shape hypothesis. |
| Forwarding helper's fifth parameter spelled int in this local caller view | First mismatch `+0x12`; metadata `+0x9380`, 3/98. | Not retained; full-width forwarding loads do not establish downstream consumption width. |

The last probe motivated inspection of the actual consumer. The forwarding
helper copies stack words unchanged, but `53B266 MOV DL,[ESP+24]` reads only
the fifth user argument's low byte, and `53B298` stores DL to object `+0x33C`.
The existing unsigned-char caller view is compatible with this consumer.
An exact int-carrier forwarding view does not require int declarations at
all callers. No accepted helper, shared header, ABI contract, compiler flag,
relocation target, or object partition changed.

## Reproduction and remaining unknowns

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
```

Fresh reports: `build/youmu-payload-final-20261002.json`,
`build/youmu-payload-final-owners-20261002.json` and
`build/youmu-payload-final-guards-20261002.json`.
Raw traversal still reaches 9,912 instructions / all 37,692 callable bytes,
with no unresolved indirect jumps. No new Ghidra output is used.
Actual source/TU ownership, remaining temporary and argument schedules,
physical shared-tail placement and full floating semantic closure remain
unknown. Whole-root canonical zero-difference replay is still required.
