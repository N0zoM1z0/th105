# Youmu shared returns and x87 controls, 2026-10-02

## Retained result

**Observed:** the source for `Youmu_dispatch_action_state_vslot28 @ 0x00530200`
is unchanged from the [copied-input/action601 checkpoint](YOUMU_COPIED_INPUT_AND_ACTION601_2026_10_02.md).
The configured full-root comparison remains nonexact over all 37,692 callable
bytes: first difference `+0xCA`, target `64` / candidate `38`; candidate
metadata `+0x9310` versus target `+0x933C`, 44 bytes earlier. Strict owner
diagnostics remain 31/98, with 97 distinct physical destinations / 33 low
entries. These diagnostics add no exact function or byte credit.

Target executable SHA-256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target callable SHA-256:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Retained CRLF source SHA-256:
`784e5356d0f80f09e6621213d73529aeb71f1602ba23a8f03a3cabc0f7141f7a`.
Canonical candidate-window SHA-256:
`cb91ae38d3c8fce149a8a0de8002dfc5a6ade8e4c196c9270b08bed2e68bad0d`.
The compared window includes candidate-adjacent metadata; it is not a callable
body hash. Raw target traversal still reaches 9,912 instructions / all 37,692
bytes without unresolved indirect jumps.

## Complete incoming group for the action-zero return

**Observed:** the target tail at `0x0053058E` belongs to physical owner `low:3`:
load vptr into EAX, slot8 into EDX, push EBX, move ESI into ECX, call EDX,
then return through the saved-register epilogue. Thirteen explicit incoming
jumps reach this exact tail, in addition to low3's local fallthrough:

| Physical owner | Exact incoming branch addresses | Baseline candidate incoming count |
| --- | --- | --- |
| mid304 | `533042 JNE`, `533069 JE` | 2 |
| mid401 | `533D8B JE` | 1 |
| mid402 | `533EBA JE` | 1 |
| mid526 | `535695 JNE`, `5356BE JE`, `5356E6 JE` | 1 |
| mid540 | `535E2B JE`, `535E4E JE`, `535E72 JE` | 3 |
| mid545 | `536359 JE` | 1 |
| high696 | `538588 JNE`, `5385AF JE` | 0 |

The baseline's equivalent low3 tail is `53058A`, with nine incoming jumps.
This counts physical sharing, not runtime call coverage. Other physical
zero-return tails remain present.

**Observed:** EBP is initially 1, but target526 changes it to 2 at `5356C6`
before its second idle-state comparison. Target540 sets EDI to 2 at `535DB7`.
Its three zero-return checks are for sequence 1/2/5, not 1/4/5. Register names
alone do not identify constant values across an owner. In 401/540/545, the
advance-result action call continues into subsequent checks; those paths
must not be redirected into a return merely because their call argument is 0.

**Inferred and tested:** a real shared source label before low3's existing
call can express these return paths without assembly or fake state. The
696-only probe recovers its two destination edges, but redirects the four
previously correct 304/401/402 edges to another zero-return tail at `531FC1`.
Low3 also changes EAX/EDX allocation. Its same 207-byte / 63-instruction size
is not instruction equality.

A second control explicitly redirects only the corresponding return paths
in all seven owners. It leaves the advance-and-continue calls intact. This
still does not recover physical placement: low3 loses its local call and
branches to `539446`, annotated as high797. That tail uses EDX for the vptr,
EAX for slot8 and an immediate zero. Twenty-three incoming jumps from a wider
owner group now reach it. Target-distinct zero-return tails are overmerged;
31/98 diagnostics regress to 27/98. No version of this explicit label is
retained. This is concrete backend/TU-phase evidence, not proof of the
original source layout or an LTCG cause.

## Shared floating decrement placement

**Observed:** target696 compares signed frame +140 against 5 at `538605`, then
jumps at `53860C` to the conditional `JL` at `533966` inside action311.
The common body loads velocity, subtracts 2, rounds through a dword at
`533978`, reloads at `53397C`, and jumps to the existing sign-check path at
`532C70`. The branch carries the preceding CMP flags.

**Inferred and tested:** sharing the real decrement expression and float
carrier in C++ preserves the value operation but does not recover this
placement. VC8 puts the common JL/decrement in 696 instead: action311 jumps
from `53392A` to `53859B`; the latter has the conditional JL, followed by
FLD/FSUB/FSTP32/FLD. Combining it with the 696 zero-return label retains the
same wrong placement. These controls are not retained. A target-sized-looking
combination or equal arithmetic multiset cannot establish these edges.

## Return-width and TH08 x87 reference

**Observed:** full raw decoding of lookup helpers `406360` (100 bytes) and
`4063D0` (94 bytes) reaches their respective normal returns. Their returned
ST(0) value originates from `FLD dword [EDX*4+6FE8B0]`, at `4063B9` and
`406423`. Body hashes are respectively
`b03e5be2d5e7b36fd141594a76773e2ba1481ecc299f92b7178d41c7a7d2f9e5` and
`85296bac92963c839b2258ecbc61b460a8244f84097f18ea18877f6d6c8e68fe`.
This establishes float-table value origin, not a unique float/double return
prototype. Both types can return that value through ST(0).

A caller-only float-return declaration control, with probe-only relocated
symbol aliases at these same helper addresses, produces the exact same
compared candidate window and 31/98 diagnostics as the baseline. Production
return declarations and relocation mappings remain unchanged. This closes
that declaration change as an explanation for the current caller residuals
under this compiler profile; it does not accept either helper as exact. See
[the earlier helper evidence](ANGLE_RATIO_EVIDENCE_2026_09_12.md).

**External source evidence:** local TH08 checkout
`d2a00f4acb4a13916e07a00bd13f714961714628` uses inline FSINCOS in
`src/ZunMath.hpp:38/:57/:145` and four FRNDINT operations followed by shared
coordinate stores in `src/AnmManager.cpp:1146`. Those are specific instruction
islands; ordinary sinf/cosf/nearbyintf expressions in its modern-port branches
do not establish legacy byte equality. No TH08 build or exact claim is made.

**Observed:** this Youmu callable and both decoded lookup helpers contain
none of FSINCOS, FRNDINT, FSIN, FCOS, FPTAN or FPATAN. That does not cover every
transitive callee or other TH105 roots. TH08's examples do not establish an
assembly requirement for this bounded scope. The target-proven natural C++
x87 environment control in
[the exact sprite-rotation unit](SPRITE_PIVOT_ROTATION_2026_10_02.md) is a
separate positive example, not a universal recipe.

## Phase-scoped controls

All controls start from the retained source above, use the configured VC8
SP1 probe flags, compile serially, and remain private. Existing-object formal
comparisons do not have configured build provenance.

| Control | Owner diagnostics | Candidate metadata start | Disposition |
| --- | --- | --- | --- |
| 710 branch calls, explicit float X and real unsigned direction snapshot | 12/98; 19 prior owners lost, no gains | `+9324` | Not retained; restores an arithmetic multiset but changes global allocation. |
| Caller-only float lookup returns | 31/98; byte-identical compared window | `+9310` | Not retained; original prototype is not uniquely proved. |
| Shared action-zero return from 696 | 27/98; loses low3/mid304/401/402 | `+9320` | Not retained; two recovered edges displace four correct ones. |
| Shared 311/696 floating decrement | 29/98; loses low11/mid311 | `+92FC` | Not retained; common body placed in 696 instead of 311. |
| Both preceding 696 controls | 26/98; loses low3/mid304/mid311/mid401/mid402 | `+9310` | Not retained; matching baseline size does not recover its bytes. |
| Full action-zero incoming group | 27/98; loses low3/mid304/401/402 | `+9320` | Not retained; common call moved into high797 and wider tails merged. |

Probe sources are in `.analysis/youmu-710-direction-20261002/`; reports,
source/object hashes, gains/losses and window hashes are in
`build/youmu-710-direction-20261002/controls-summary.json`. Exact branch
packets are `target-zero-tail-incoming.json`,
`candidate-zero-tail-incoming.json` and `all-incoming-zero-tail-placement.json`
in that build directory. Private reports are disposable working evidence.

## Focused reproduction and remaining work

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
```

Fresh finished-worktree reports are
`build/youmu-shared-zero-final-20261002.json` and
`build/youmu-shared-zero-final-owners-20261002.json`.
The whole-root comparison remains required for exact acceptance. No source,
shared ABI, compiler flag, object partition, global map or exact ledger changes.
The IDA preflight fails because the attached image SHA begins `10350095`;
this work uses the hash-attested PE, with no new IDA/Ghidra database output.

**Unknown:** original declarations and register/stack lifetimes, remaining
argument schedules, actual shared-tail ownership, compiler/TU/LTCG context,
and full numerical/exception closure. Preserve the current root source;
revisit only with independent lifetime or compilation-context evidence.
The next bounded giant candidate is `YoumuObject_initialize_action_entry @
0x00543670`, whose 5,159-byte source-present callable still requires a fresh
focused comparison and raw boundary/control-flow check.
