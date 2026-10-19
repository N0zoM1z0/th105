# Battle collision phase46DFF0: native containers and complete source

## Target and extent

Only original Japanese TH10.5 v1.06a is used, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The bounded target is `[46DFF0,46E59C)`,1452 bytes, SHA256
`ca24d275c213508fd8a634e8712736c20297637739051f98147bebbd8f8bca53`.
It decodes449 instructions; raw CFG reaches1434 bytes and one RET0 at46E59B.
The remaining18 bytes are exact branch-skipped alignment at46E07D/3,
46E3E8/8 and46E4A9/7. There are no indirect exits, switch data or remote
owned chunks. The body has46 direct calls to nine destinations and two
zero-stack-argument virtual calls through manager slot24h.

Five exact BattleManager/Story pipelines call the entry at471643,4716FC,
471771,472E54 and472ED1. Each supplies the context in ECX; together with
RET0 and context field accesses this supports ordinary member calling.
The durable mapping is `BattleCollisionPhase_run`; `CollisionPhase` is a
runtime prefix view, not a recovered original declaring class or complete TU.
The pre-existing authored rule retains its body/padding/caller witnesses and
now also pins all three newly exact45C500 calls. Its dependent family1 origin
rule follows the caller's implemented status; no origin classification changes.

## Observed policy and physical interfaces

The context exposes fighters at0C, three pairs of12-byte lists at2C/44/5C,
and two pairs of dword deferred values at74/7C. The function clears all six
lists and deferred values, prepares each fighter, copies byte4E9 to4EA, then
iterates each manager's owned objects. It derives signed player334 from the
object's owner16C, obtains the two native vector sizes from frame158, adds
extension194, and uses flags01000000 plus result180/signed byte184 to choose
which of the three families receive the object. It next appends eligible
fighters, calls both collision dispatches, traverses attacks against the other
fighter and conditionally the same fighter, then publishes deferred counters.
The family names are observed grouping labels, not new gameplay terminology.

All21 invalid-parameter sites are genuine checked iterator operations. Target
seven Buynode calls pass a list receiver in ECX and three stack slots; seven
Incsize calls use ECX and a single amount slot. Owned-object pointers convert
to void-pointer family values through real temporary arguments. The native
standard library explains these instructions without hand-written checks.
The separate51-byte Buynode and160-byte Incsize already have positive compiler
origin evidence; their classification is reused, without new exclusion credit.

The actual manager getter at4B9DA0 is `8d4158c3`: return receiver+58h. All fifteen
roster manager vtables contain it at slot24h. The execution fixture uses the
canonical Reimu manager vtable6C40FC, whose COL/type descriptor identifies
`CharacterObjectManager<Reimu,ReimuObject>`. Both virtual calls therefore run
the real four-byte getter, rather than a supplied callback result.

`CollisionPhase.cpp` now uses real `std::list<void*>`, typed owned-object
iterators and native `std::vector<Box16>` size operations. Compile-time checks
pin context prefix84h, list/deferred offsets, fighter manager658/player334/
state4E9, object owner16C/extension194 and prepared frame1A4. These views are
not allocated as complete original game classes. No shared header changes.

## Source selection and comparison

The retained file was unselected and unverified. It manually repeated sentinel
assertions, called a member node operation through a free stdcall facade,
and used a volatile store to retain a schedule. Those constructs are removed.

| Fresh control | Complete function result |
| --- | --- |
| Retained unselected hypothesis |1398 bytes, first+5 |
| Native checked containers and direct field expressions |1444 bytes/frame2Ch; all21/7/7 check/create/increment call sites recovered |
| Fighter pointer local before the final guard |1447 bytes, first+558; prior1368 bytes equal |
| Fighter local inside the successful guard |1449 bytes, first+559; prior1369 bytes equal |
| Value-first cap comparison | Same1449-byte extent; target cap branch polarity, still nonexact |
| Ordinary short local, sum operand order, ternary cap, unsigned dword storage | No closure of the selected tail |
| Native std::min<int> expression |1466 bytes; temporary-reference addresses, unselected |
| Natural inline narrow policy/guard variants |1449/1447 bytes, unselected |
| RTM in the selected source context | Complete payload identical to SP1 |

The selected ordinary VC8 SP1 `/O2 /GS- /GR /EHsc /MT` body is1449 bytes,
canonical SHA256
`ea3990e6e90f79437c9c5c42a8b87102dc2fc63c5c10a63dfd22ee1a252edf5d`.
The strict configured unit `gpt-web-battle-collision-phase` returns1/nonexact,
first mismatch+559/46E549, a changed branch displacement. Structurally, the
remaining difference is the final dword guard/low-word signed conversion,
register carriers and consequent length/relocation changes. Target loads the
low word with MOVZX, later sign-extends the carrier and adds the signed actor
word. The candidate combines that conversion with its memory load. Both
retain the signed full-int sum and signed maximum before the final word store.
No padding, inert local, register constraint, assembly or byte edit is used.

The full1369-byte canonical prefix includes both same-side call preparation
and all container/classification/dispatch logic. It remains diagnostic prefix
equality, not whole-function acceptance. Original source spelling, the final
narrow lifetime/compiler phase and original TU are unknown. These observations
do not establish an LTCG requirement. No matches row or exact-byte credit.

## Native execution and its limits

`scripts/audit-battle-collision-phase.py` executes the original entry and the
COFF candidate at separate addresses. All geometry, classification, collision
providers, list helpers and the real getter execute original PE instructions.
The environment supplies only the native12-byte Buynode allocator and original
node frees as deterministic heap callbacks. Callers/size/ownership are checked;
EAX/ECX/EDX are deliberately clobbered where permitted. No gameplay or geometry result is
supplied by callbacks. Code/resource pages stay read-only; writes are
restricted to the fixture context/actors/nodes, stack and the x86 SEH cell.
Callback errors explicitly stop execution; no ctypes callback exception can
silently pass the audit.

The final source passes all114 full-entry and396 tail-entry cases with zero
mismatches. The audit enforces416/449 visited target instructions: the33
absent instructions are exactly21 invalid-parameter calls, four skipped
alignment instructions and eight instructions preparing the unsupported
same-side hit call. Source visits415 instructions because its remaining
narrow conversion uses one fewer instruction. The canonical getter executes
456 times per side; native Buynode/Incsize execute482 times each, and all792
original-node frees agree.

There are114 full-entry cases: empty/mixed geometry, all eight frame flag
combinations, absent/plain/oriented extensions, zero/one/two owned objects,
negative/zero/positive status, result gates and old-list cleanup. Frame50
same-side-hit flag stays zero; actors on opposing sides are separated. The
actual foe collision helpers execute, including46DD40/46CA80/46BCA0,
46DB30/46C9E0/46C930,46DA10/45E390/46BB10 and geometry routines. These cases
compare every byte in the128KiB fixture arena, ordered allocations/frees,
ordered direct-call targets, real return/ESP/nonvolatile registers, restored
SEH state, x87 TOP/control word and MXCSR. A data-only cosine table and SSE2
flag are inputs, not original startup-table evidence.

The full-entry no-hit cases naturally reset deferred values to zero. A separate
396-case tail-entry lane supplies explicit preconditions for the common
46E53B entry:2Ch local frame plus four saved registers, pending pointer at
ESP+30h, and a real return address. It does not claim396 additional full-root
invocations. Current/maximum signed-word boundaries, dword deltas with zero or
nonzero low words, and positive/negative558 deltas exercise the actual target
arithmetic and real45D510 setter. Nonzero high dword bits must still enter the
word update even when the narrowed delta is zero. Low-word arithmetic is not
silently substituted for the dword guard.

An inverted-cap source control (`value >= maximum` to `value <= maximum`)
passes all15 smoke full entries but fails10/24 smoke tail entries. Full-entry
fixtures alone would therefore miss this real counter regression. The control
is compiled at the original source path to preserve anonymous namespace
identities, then the selected source is restored and its hash read back before
auditing. The negative recipe and reports remain private/build artifacts.

A same-side hit fixture reached the larger effect/callback environment and
stopped on an unreviewed write. It is excluded from the supported execution
domain, not replaced with a fabricated hit result. Its callsite remains in the
canonical prefix. Invalid containers, throwing allocation/length errors,
same-side hit effects, legacy x87 ceil and full game startup remain untested.
The auditor reports unvisited instruction offsets and existing-object build
provenance as unverified; the fresh formal producer supplies independent build
provenance. Sampled execution does not award exact bytes.

## Reproduction

```bash
python3 scripts/build.py --unit gpt-web-battle-collision-phase --compare --json
python3 scripts/audit-battle-collision-phase.py \
  build/match-units/GptWeb_BattleCollisionPhase.obj
python3 scripts/validate-tracking.py --require-target
python3 scripts/check-match-literals.py --require-target
python3 scripts/ci.py
git diff --check
```

The build command currently returns1/nonexact, not an infrastructure failure.
The native audit returns0 for the supported full/tail fixtures; `--smoke`
selects15 full and24 tail cases. Reports and raw byte evidence are under
`build/collision-phase-20261020/`; source trials, guarded negative recipes and
direct Ghidra scripts are under `.analysis/collision-phase-20261020/`.

The direct128MiB/CPU0 read-only Ghidra pass independently verifies executable
identity, entry, full mapped text, root bytes and all five inbound E8s. It reads
back the disposable ECX/void signatures and discards changes. Nine primary DB
hashes remain unchanged. Decompiler text remains a hypothesis; IDA preflight
rejects the wrong open image and no IDA semantics or factory adapter is used.
This checkpoint adds source/ABI/execution evidence only. Exact totals are
unchanged, with no cold aggregate replay claim.
