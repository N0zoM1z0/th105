# AyaObject action 826 owner-Y lifetime, October 23, 2026

The selected root at `0x0061A290` now captures the owner's Y value as a used
double before the alpha decrement. This restores the target's X/alpha/Y write
order and the live Y value at the alpha store. The whole root remains nonexact;
no authored exact credit is added.

## Observed target and selected code

All observations use Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target/status/tracking checks pass. IDA preflight still rejects the open
database's different identity, so no IDA semantics or writes were used.

Action 826 sequence 1 begins its position update with this target interval:

| Target address | Instruction |
| --- | --- |
| `0x61C2BA` | `fld dword ptr [eax + 0xEC]` |
| `0x61C2C0` | `fstp dword ptr [esi + 0xEC]` |
| `0x61C2C6` | `fld dword ptr [eax + 0xF0]` |
| `0x61C2CC` | `add byte ptr [esi + 0x113], 0xF6` |
| `0x61C2D3` | `fadd qword ptr [0x6CD190]` |
| `0x61C2D9` | `fstp dword ptr [esi + 0xF0]` |

The 37 bytes end exclusively at `0x61C2DF`, SHA256
`18ab975df59599b49e600171fa256c87e7753c1e1b75c16ef67b7b2ad3973c53`.
X is committed before alpha, and the owner's Y is already live in x87 when
alpha changes. The prior source expression lets VC8 move the alpha memory ADD
before X's FSTP. A used `double const owner_y = owner->y_f0` before the alpha
update recovers all six target instructions, once, without extra operations.
This supports the value lifetime; original source spelling remains unknown.

Complete canonical payload stays 20,132 bytes, metadata starts at 19,664.
Only 13 bytes change inside `[+0x20AF, +0x20C2)`, a 19-byte interval; every
byte outside it, including switch metadata, is identical to the predecessor.
The previously recovered action 807 26-byte interval still occurs once.
Strict outside-826 graph comparison preserves 4,438 paired nodes without
carrier, floating-operand or flag allowances.

Full canonical SHA256:

- Predecessor: `17585ff8bc4fadd5f63619d3d52d470440955256a820ac76ca97daa7ee31f88f`.
- Selected: `a5dc22f5c6f0e93a3fc81592510327c5708c8c4d41938f2bd96eaf7947523ede`.

The configured 19,522-byte comparator still differs at `+0x22`, address
`0x61A2B2`, target `0F` / source `9B`. A local exact interval is not a whole
function match and is not entered in `matches.csv`.

## Actual-code execution

`audit-aya-object-scale-adds.py --actions 826 --position-lifetimes` runs 2,584
actual root returns with original frame helpers. The matrix includes scale and
growth raw bits, signed zero, subnormal, finite extremes, infinities, quiet and
signaling NaNs, eight masked precision/rounding control words, alpha boundaries
and phases 0/1/6. Its extra 512 owner-Y cases vary 16 raw values, four alphas
and eight control words. Owner X remains finite; animation resources are a
bounded fixture below callback thresholds.

Selected code has zero recorded differences in actor/parameter bytes, ordered
writes, calls, final x87 status/tag, scale-store live x87 state and X/alpha/Y
store snapshots. The predecessor differs in ordered writes and position-store
snapshots in all 2,584 cases. Its final values alone had concealed this issue.
The selected-only strict run passes the same matrix and 37-byte interval guard.
Alpha-read epochs, arbitrary resources/owners, callbacks and unmasked exception
delivery remain outside this proof.

The earlier 6,216-case 820/826 impact matrix had exposed the ordering issue:
820 sequences 2/3 agree in all 4,144 cases for both old801-control objects;
826 sequence 1 differs only in write order in 2,072 cases for both. The new
actions selector preserves the original default 853/861 matrix. Its replay
retains the known 861 write-order deficit; this change does not fix 861.

## Bounded 801 investigation and remaining constraints

Before the 826 correction, a fresh 801 cached-sequence control eliminates all
3,012 predecessor sequence-read differences in 3,840 actual-code cases. Its
852 replay also agrees in 6,528 returns and 6,400 owner-product snapshots.
These are scoped execution results, not acceptance of that root control.

New `audit-aya-object-fade-sharing.py` checks the real action entries and common
root prologue/dispatch. It pairs 154 states for 817, proving its AL20 compare
moves only across 11 identical floating instructions with no AL/EFLAGS write,
integer instruction, call or branch in between. It pairs 202 states for 822,
with two checked JB/JAE edge inversions. Both source graphs retain identical
other instruction labels and ordered edges. The two inverted branches belong
to 822's reuse of the old 817 fade tails, correcting earlier physical-owner
attribution. An identity control needs neither allowance. These proofs assume
normal identical callee behavior; asynchronous observers and unmasked faults
can observe moved flags and are excluded. The strict graph checker is unchanged.

The full outside-801 diagnostic is still incomplete. It now reaches action
807, where the cached candidate inserts facing capture/scratch stores inside
the recovered 26-byte interval. The unchanged 807 audit rejects it at that
exact-window guard; no successful 807 receipt is claimed. Natural else-if and
switch forms also lose this interval, despite their different code generation:

| Pre-826 control | Full bytes | Canonical SHA256 | 807 interval count |
| --- | ---: | --- | ---: |
| Cached sequence | 20268 | `110214dac416470c33335da85cb164e74b46277e4d0e43bf703a80dd946b6309` | 0 |
| Else-if | 20268 | `907d3ab224c3dc2c664d063c5ef928b66e69fe1264b5821321c9ee6a3c22aebf` | 0 |
| Switch | 20224 | `f5084462e99092e63743cc852eb74bf7c410333d17aa9bbfc52adb376f87eee8` | 0 |

The new target-backed 826 lifetime justified one further cached-sequence retry.
It produces 20,268 bytes / SHA256
`86daa69db8e36681bfcb5c5640421630afd2bf68504e206435018b5f698c599b`;
826's 37 bytes survive, but 807's 26 bytes still disappear. It is unselected;
no execution equivalence is claimed for the else-if/switch/combined controls.
Current 801 source therefore retains its known 3,012 read differences. Revisit
it only with a supported context that addresses the 807 scheduling interaction,
alongside remaining x87 input order, scratch, frame-tail and TU questions.
Failed source controls do not establish an LTCG impossibility.

## Reproduce

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-scale-adds.py --actions 826 --position-lifetimes --output build/aya-801-impact-20261023/resume826.json
python3 scripts/audit-aya-object-fade-sharing.py build/aya-801-impact-20261023/previous.obj build/aya-801-impact-20261023/snapshot.obj --output build/aya-801-impact-20261023/resume-sharing.json
python3 scripts/validate-tracking.py --require-target
```

The root comparison intentionally exits nonzero. Private scope
`build/aya-801-impact-20261023/` retains frozen CPP/object epochs, formal
comparisons, `826-canonical.json`, `826-outside.json`, strict/native receipts
and control hashes. The exploratory full-flow script under `.analysis/` is
diagnostic only. Frozen 801 and older owner-context inputs predate this 826
selection; do not replace current source wholesale with them. No ABI/header,
compiler flag, object partition or accepted relocation contract changes.
