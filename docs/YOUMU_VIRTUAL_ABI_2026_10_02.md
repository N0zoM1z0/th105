# Youmu virtual ABI correction, 2026-10-02

## Current result and superseded assumption

`Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains **nonexact** over
37,692 target bytes. Its three retained `__stdcall` calls in actions
209/210/211 were incompatible with the target virtual method's ECX receiver.
Those calls are now ordinary member calls using the accepted animation/sequence
prefix. The historical decision to reject their ABI correction because it
collapsed the candidate switch is superseded: a diagnostic topology score
cannot justify an incorrect calling convention.

The fresh candidate has **95 physical switch destinations**, versus target
97, and metadata begins at `+0x9114`, versus target `+0x933C`. The strict
instruction/edge auditor rejects the candidate's merged target owners; no
current 24/98 owner score is claimed. That score belongs to the preceding
source checkpoint. Canonical first mismatch remains `+0xCA / 0x005302CA`,
now target `64`, candidate `39`. Exact ledgers receive zero new credit.

## Raw target ownership and call contracts

**Observed:** original Japanese 1.06a PE SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
with entry point `0x0068B9D2`. IDA still exposes the different `10350095...`
image and is not used. No Ghidra session, target patch or assembly is involved.

Youmu primary vtable `0x006C5144` points through its preceding DWORD to
RTTI locator `0x006DA8BC`, type descriptor `0x006E853C` (`.?AVYoumu@@`) and
hierarchy `0x006DA8D0`. Its seven base records place Youmu, CharacterEx,
Character, AttackObject and AnimationObject at displacement zero;
AnimationObjectBase and Environment appear at `+4` and `+0x130`.
Thus the animation/sequence primary prefix requires no receiver adjustment.

| Slot | Pointer DWORD | Raw callee | Accepted call view |
| --- | --- | --- | --- |
| `+8` | `0x006C514C` | `0x0045BFE0` | `int set_action_and_finalize(short)` |
| `+0x0C` | `0x006C5150` | `0x0045C390` | `int select_sequence(int)` |
| `+0x14` | `0x006C5158` | `0x0045C220` | `unsigned char next_sequence_block()` |

The `+8` wrapper receives the object in ECX, forwards its four-byte argument
slot to `0x00435200`, invokes virtual `+0x3C` on that object, and returns
with `RET 4`. The base setter consumes the low action word. The other two
callees corroborate the already accepted sequence view: the selector uses a
four-byte sequence slot and returns with `RET 4`; the advance method explicitly
returns 0/1 in AL. Return values are ignored at these Youmu call sites.
Compatible call views and accepted callee source do not prove unique original
class names, declarations or TU ownership.

**Source recovery:** the local Youmu view now derives from the existing
declaration-only `AnimationSequenceObjectView`. Its header is unchanged.
All 175 direct self calls through these three slots are expressed as named
member calls: 127 action calls, 33 sequence selections, 15 sequence advances.
Three cached sequence callees in action 214 retain their existing lifetime;
their return contract is updated to `int`. Opponent and other virtual slots
remain separate consumers. No shared header, accepted layout, compiler flags or
relocation targets are changed.

## ECX reload evidence

The target does not rely on the preceding predicate preserving ECX:

```text
action 209: 5315F2 CALL 5F9310; 5315F7 TEST AL,AL;
            5315F9 MOV ECX,ESI; 5315FB JNE 5314A3
action 210: 53172F CALL 5F9310; 531734 TEST AL,AL;
            531736 MOV ECX,ESI; 531738 JNE 5314A3
action 211: 53181D CALL 5F9310; 531822 TEST AL,AL;
            531824 MOV ECX,ESI; 531826 JNE 5314A3
```

At shared tail `0x5314A3`, target reads the object's vptr, loads slot `+8`,
pushes action 10 and calls it. Each source call must supply that object receiver.
The reload also prepares the false arm's geometry call.

**Observed negative evidence:** predicate `0x005F9310` calls height query
`0x00435D60`. The height query initially uses `PUSH ECX` as a four-byte
scratch slot, overwrites that slot with floating data and eventually uses
`POP ECX` to discard it. That pop is not restoration of the original receiver;
ECX receives the scratch bits. The predicate does not subsequently restore
ECX. Therefore a supposed register-preserving helper is not an explanation
for the target calls. An incidental receiver reload in a compiled false arm
would likewise not make a `__stdcall` source declaration truthful.

## Candidate folds and diagnostic handling

Correct calls cause VC8 to fold two sets of target-distinct low entries:

| Candidate cases sharing an entry | Candidate offset | Target groups |
| --- | --- | --- |
| `[209,212,221]` | `+0x13B0` | `[209]`, `[212,221]` |
| `[210,222]` | `+0x14CB` | `[210]`, `[222]` |

Candidate low table has 31 destinations, mid 44 and high 22. The existing
span mapper supports reviewed alternative candidate counts: config now records
low `[31,33]` and root `[95,97]`. Recognition still requires consecutive local
DIR32 relocations, complete in-range index coverage and one unique table per
region. Target PE counts and tables remain unchanged. These alternatives
permit diagnosis; they do not alter canonical comparison. The strict owner
auditor still exits 2 with `candidate merges distinct target physical owners`.
No normalized or partial exact score is substituted for that rejection.

The minimum three-call correction and the recovered ordinary call view produce
the same folds. Changing only ignored return types and narrowing the action
call view is byte-neutral. Using a local typed view versus the accepted inherited
prefix is also byte-neutral. Removing one-use constant-field temporaries from
209/210/211 does not change their corrected object. These probes close those
particular explanations; they do not prove LTCG or assembly is necessary.

## Reproduction and remaining work

```bash
taskset -c 0 python3 scripts/build.py \
  --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/map-giant-action-switches.py youmu-vslot28 --json
python3 scripts/compare-giant-action-switches.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
```

The formal comparison returns exit 1 for an ordinary mismatch, without a
relocation failure; the span mapper succeeds and the owner auditor rejects
merges as described above. A separate fresh raw traversal still reaches
**9,912 instructions / 37,692 bytes**, including the action-720 auxiliary
switch, with no unresolved indirect jumps. Callable target hash remains
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Canonical candidate-window hash is
`3464a7971c6adca7576add5a7ed77a010014c10e1e7ba7394abc4b4900fc7472`.
Because candidate metadata starts earlier, that 37,692-byte comparison window
includes candidate table bytes; it is not a candidate callable-body hash.

Remaining work is to recover the real source/context distinction between
209 and 212/221, and between 210 and 222, along with shared-tail ownership,
numerical contracts and real temporary lifetimes elsewhere. Preserve the
correct receiver ABI while investigating those distinctions. The preceding
action-720 and numerical source corrections remain. Only this unit is built;
exact totals are unchanged ledger totals, not a new aggregate cold replay.

The existing locality regression test now locates the named action call when
checking action 198's early return. Its obsolete prose-score assertions are
replaced by the actual full-root unit/ledger scope and absence from the exact
ledger. These checks protect acceptance scope; they do not establish exactness.
