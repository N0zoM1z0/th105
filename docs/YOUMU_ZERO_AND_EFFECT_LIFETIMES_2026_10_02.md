# Youmu zero and effect lifetimes, 2026-10-02

## Retained result

`Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains **nonexact** over
37,692 target bytes. Action214 now expresses all five velocity predicates
with velocity on the left and a literal zero on the right. Natural VC8 code
keeps zero on the x87 stack through the target memory comparisons, discards
it before conditional virtual calls and reloads it afterward. Three extra
velocity FLDs disappear. The repeatedly assigned zero local is unnecessary
in the recovered source and is removed.

Effect125 now computes X/Y inside its actual call arguments. The generated
schedule prepares trailing arguments before sine-Y and cosine-X, preserving
the target's Y association `(sine*100+selfY)+100`. Four unused floating local
hypotheses are removed in total. The existing direction snapshot remains.

Fresh configured comparison first differs at `+0xCA / 0x005302CA`, target
`64`, candidate `0C`. Candidate metadata starts at `+0x92E4`, versus target
`+0x933C`; its callable is 88 bytes shorter. Section tail is38,728 bytes.
All97 physical switch destinations and33 low entries remain distinct.
Strict instruction/edge diagnostics stay **27/98**, with no gains or losses
from the typed-call checkpoint. There is **zero new canonical exact credit**.

Target callable SHA-256:
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
Retained CRLF source SHA-256:
`eae0bdd5c36c3e0dd10b670651d44b38559f1e276d59e293c9dc96c00e395d92`.
Canonical compared candidate-window SHA-256:
`6434ac9c95ef94dd5bebee3add2ed08723b5451766fbaa729c46b33c26ed1419`.
That compared window includes candidate metadata and is not a body hash.

## Target and candidate evidence

**Observed:** original Japanese1.06a PE SHA-256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
entry point `0x0068B9D2`. Fresh IDA preflight fails with the different
`10350095...` executable; that session is not used. All new observations
come from the hash-attested PE and canonical candidate relocation replay.
No new Ghidra process, database write or target patch is involved.

Target starts the zero lifetime at `531C6C FLDZ`. The retained candidate
has the following corresponding memory comparisons. Both operand bindings
are zero in ST0 and the current velocity dword at self`+0xF4`.

| Target | Candidate | Instruction | Mask / following branch |
| --- | --- | --- | --- |
| `531C6E` | `531BE0` | `FCOM [self+F4]` | `41 / JNE` |
| `531C8D` | `531BFF` | `FCOM [self+F4]` | `41 / JNE` |
| `531CB2` | `531C24` | `FCOM [self+F4]` | `41 / JP` |
| `531CD7` | `531C49` | `FCOM [self+F4]` | `41 / JNE` |
| `531CFD` | `531C6F` | `FCOMP [self+F4]` | `41 / JP` |

The first guard selects the rotation correction. The remaining four guard
sequence changes3/1/4/2. Zero is retained on paths that skip a virtual call;
call paths discard it with `FSTP ST0` before the invocation and reload it
afterward. The final FCOMP consumes zero. The velocity itself is not cached
across calls: each comparison rereads the field. The target reloads zero at
`531CB0`, `531CD5` and `531CFB` after the first three sequence calls.

The preceding source mixed `velocity<0` with `zero<=velocity` and
`zero>velocity`. Its generated code popped zero too soon and reloaded velocity
for three later comparisons against a qword zero literal. Merely changing
the zero local's type had been byte-neutral. A fresh all-right source probe
instead recovers the observed memory-comparison/lifetime shape. Replacing
its known-zero local and redundant assignments with literals is byte-neutral.

**Inferred source:** `velocity<0` and `velocity>=0` preserve the old predicates,
including both signed zeros, infinities and unordered results. Less-than and
greater-or-equal are both false for unordered values. The complete raw guard
packet confirms the target/candidate operand bindings and mask/branch shapes
above; it does not establish unique original source spelling or full floating
environment/exception equivalence.

**Observed effect schedule:** direction is read at `531D31`, phase at
`531D38`, and trailing1/direction arguments are prepared at `531D3E/531D3F`.
Sine helper is called at `531D44`; Y is rounded at `531D5B`, reloaded and
stored in the outgoing slot at `531D63`. Cosine helper is called at
`531D70`; signed facing multiplication and self-X addition precede the X
dword home at `531D94` and outgoing store at `531D9C`. Effect call is
`531DA1 CALL 435240`.

The retained candidate prepares trailing arguments at `531CB0/531CB1`,
calls sine at `531CB6`, rounds/stores Y at `531CCD/531CD5`, calls cosine at
`531CE2`, rounds/stores X at `531D06/531D0E`, then invokes the effect at
`531D13`. Its multiply/add/pop order, literal widths and dword homes reproduce
this target schedule; registers and absolute placement still differ.

**Inferred source:** nested coordinate arguments explain this order without
changing helper contracts or arithmetic association. Final X/Y arguments
remain floats; helper results and scaling arithmetic remain double. Earlier
Y snapshot locals are unnecessary in this generated schedule. The existing
integer direction snapshot is still read before either helper. There is no
claim that this is the only possible original source expression.

## Controls and phase-scoped negative evidence

| Serial VC8 probe | Observation | Disposition |
| --- | --- | --- |
| Put zero on the left of all five predicates | 27/98; metadata `+0x9314`; five extra velocity FLDs instead of the baseline three. | Not retained. |
| Put velocity on the left throughout | 27/98; metadata `+0x9304`; action214 load/store lead disappears. | Retained property. |
| Remove known-zero local/assignments from all-right probe | Same compared window as the preceding row. | Retained cleanup. |
| Add nested effect125 arguments after recovered zero lifetime | 27/98; metadata `+0x92E4`; no owner gains/losses. | Retained. |
| Remove four now-unused floating local declarations | Same compared window as the preceding row. | Retained cleanup. |
| Action606 random-X expression inside spawn argument, alone | 25/98; metadata `+0x92E8`; loses low11/mid304. | Private source hypothesis. |
| Random-X606 plus recovered zero lifetime | 25/98; metadata `+0x92E4`; same losses. | Not retained. |
| Spell606 frame range as `>6 && <11` in preceding probe | Byte-neutral. | Not retained; no original range spelling proved. |
| Both214/606 argument schedules plus zero lifetime | 25/98; metadata `+0x92D8`; same losses. | Not retained. |

The earlier effect-argument probe lost low11 when combined with typed calls.
The independently observed zero-lifetime recovery changes that result:
the same local effect schedule now preserves all27 prior owners. Thus the
negative conclusion in
[the typed-call checkpoint](YOUMU_TYPED_VIRTUAL_CALLS_2026_10_02.md)
is superseded for this combination. This is a bounded retry justified by new
target-backed lifetime evidence, not an arbitrary declaration/flag search.

**Observed606 lead:** target rounds Y at `538014`, keeps the reloaded value
through `538028 FCOMP ST1`, prepares arguments7..4 and stores outgoing Y
at `53804C`, before the random100 call at `538051`. Baseline instead pops
both values at its comparison and keeps several values live across the
random call, then reloads Y for the outgoing argument.

Moving only the real random-X expression into the call argument recovers
that local FCOMP/Y carry/trailing-prefix schedule and removes606's load/store
multiset lead. It also changes shared virtual-site placement: candidate slotC
sites decrease31->30 and slot8 sites106->105. Those are physical counts,
not proof of missing behavior. Full graph/register allocation remains
nonmatching, including the low11/mid304 regressions. Original606 expression
and shared-tail placement remain open; the probe is recorded for a later
independently supported compiler/lifetime phase change.

## Whole-root validation and remaining scope

Fresh explicit-object scans cover all138 target/candidate masked floating
guards, with zero unequal owner counts or unordered-only leads under ordinal
hypotheses. All49 spawn payloads resolve without conflicting modeled ESP
merges. The same six normalized payload-address owners differ. Arithmetic
counts remain349/348 with three multiset leads in601/696/710. Load/store
multiset leads decrease13->12, removing action214. These scans do not close
all operands, dependency orders, precision or exception behavior.

Virtual physical-site counts remain107/106,31/31,12/13,2/2 at slots8/C/14/1C.
Raw target traversal still reaches9,912 instructions/all37,692 bytes without
unresolved indirect jumps. No shared header, helper, compiler flag, relocation
map or TU partition is changed. No aggregate cold-replay claim is added.

```bash
python3 scripts/build.py --unit gpt-web-youmu-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json
python3 scripts/ci.py
git diff --check
```

Fresh reports use `build/youmu-zero-effect-final-20261002.json` and
`build/youmu-zero-effect-final-owners-20261002.json`. Explicit-object call,
guard, stack, arithmetic and load/store packets use that prefix and date.
Private controls are below `.analysis/youmu-flow-lifetimes-20261002/` and
`build/youmu-flow-lifetimes-20261002/`; their reports contain their actual
object hashes. The load/store census checks object/audit hash agreement.

Original local types, other argument schedules, physical tail placement and
TU/compiler context remain unknown. The recovered zero lifetime is evidence
that this x87 difference can arise from ordinary source shape; it is not a
rule for every x87 function or the out-of-root trigonometric helpers. Whole-
root zero-difference replay is still required for exact acceptance.
