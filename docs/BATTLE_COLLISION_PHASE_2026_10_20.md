# Battle collision phase 46DFF0: native containers and complete source

## Target and extent

Only original Japanese TH10.5 v1.06a is used, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The bounded target is `[46DFF0,46E59C)`,1452 bytes, SHA256
`ca24d275c213508fd8a634e8712736c20297637739051f98147bebbd8f8bca53`.
It decodes 449 instructions; raw CFG reaches 1434 bytes and one RET 0 at 46E59B.
The remaining 18 bytes are exact branch-skipped alignment at 46E07D/3,
46E3E8/8 and 46E4A9/7. There are no indirect exits, switch data or remote
owned chunks. The body has 46 direct calls to nine destinations and two
zero-stack-argument virtual calls through manager slot 24h.

Five exact BattleManager/Story pipelines call the entry at 471643,4716FC,
471771,472E54 and 472ED1. Each supplies the context in ECX; together with
RET 0 and context field accesses this supports ordinary member calling.
The durable mapping is `BattleCollisionPhase_run`; `CollisionPhase` is a
runtime prefix view, not a recovered original declaring class or complete TU.
The pre-existing authored rule retains its body/padding/caller witnesses and
also pins all three exact 45C500 calls. Adjacent traversal 46DD40 is now
independently 686/686 exact; its remaining 542-byte pair resolver retains a
separate rule using matching traversal callers. No authored/exclusion census
change is inferred from the parent source.

## Observed policy and physical interfaces

The context exposes fighters at 0C, three pairs of 12-byte lists at 2C/44/5C,
and two pairs of dword deferred values at 74/7C. The function clears all six
lists and deferred values, prepares each fighter, copies byte 4E9 to 4EA, then
iterates each manager's owned objects. It derives signed player 334 from the
object's owner 16C, obtains the two native vector sizes from frame 158, adds
extension 194, and uses flags 01000000 plus result 180/signed byte 184 to choose
which of the three families receive the object. It next appends eligible
fighters, calls both collision dispatches, traverses attacks against the other
fighter and conditionally the same fighter, then publishes deferred counters.
The family names are observed grouping labels, not new gameplay terminology.

All 21 invalid-parameter sites are genuine checked iterator operations. Target
seven Buynode calls pass a list receiver in ECX and three stack slots; seven
Incsize calls use ECX and a single amount slot. Owned-object pointers convert
to void-pointer family values through real temporary arguments. The native
standard library explains these instructions without hand-written checks.
The separate 51-byte Buynode and 160-byte Incsize already have positive compiler
origin evidence; their classification is reused, without new exclusion credit.

The actual manager getter at 4B9DA0 is `8d4158c3`: return receiver+58h. All fifteen
roster manager vtables contain it at slot 24h. The execution fixture uses the
canonical Reimu manager vtable 6C40FC, whose COL/type descriptor identifies
`CharacterObjectManager<Reimu,ReimuObject>`. Both virtual calls therefore run
the real four-byte getter, rather than a supplied callback result.

`CollisionPhase.cpp` now uses real `std::list<void*>`, typed owned-object
iterators and native `std::vector<Box16>` size operations. Compile-time checks
pin context prefix 84h, list/deferred offsets, fighter manager 658/player334/
state 4E9, object owner 16C/extension194 and prepared frame 1A4. These views are
not allocated as complete original game classes. No shared header changes.

## Source selection and comparison

The retained file was unselected and unverified. It manually repeated sentinel
assertions, called a member node operation through a free stdcall facade,
and used a volatile store to retain a schedule. Those constructs are removed.

| Fresh control | Complete function result |
| --- | --- |
| Retained unselected hypothesis |1398 bytes, first+5 |
| Native checked containers and direct field expressions |1444 bytes/frame2Ch; all 21/7/7 check/create/increment call sites recovered |
| Fighter pointer local before the final guard |1447 bytes, first+558; prior 1368 bytes equal |
| Fighter local inside the successful guard |1449 bytes, first+559; prior 1369 bytes equal |
| Value-first cap comparison | Same 1449-byte extent; target cap branch polarity, still nonexact |
| Ordinary short local, sum operand order, ternary cap, unsigned dword storage | No closure of the selected tail |
| Native std::min<int> expression |1466 bytes; temporary-reference addresses, unselected |
| Natural inline narrow policy/guard variants |1449/1447 bytes, unselected |
| RTM in the selected source context | Complete payload identical to SP1 |

The selected ordinary VC8 SP1 `/O2 /GS- /GR /EHsc /MT` body is 1449 bytes,
canonical SHA256
`ea3990e6e90f79437c9c5c42a8b87102dc2fc63c5c10a63dfd22ee1a252edf5d`.
The strict configured unit `gpt-web-battle-collision-phase` returns 1/nonexact,
first mismatch+559/46E549, a changed branch displacement. Structurally, the
remaining difference is the final dword guard/low-word signed conversion,
register carriers and consequent length/relocation changes. Target loads the
low word with MOVZX, later sign-extends the carrier and adds the signed actor
word. The candidate combines that conversion with its memory load. Both
retain the signed full-int sum and signed maximum before the final word store.
No padding, inert local, register constraint, assembly or byte edit is used.

The full 1369-byte canonical prefix includes both same-side call preparation
and all container/classification/dispatch logic. It remains diagnostic prefix
equality, not whole-function acceptance. Original source spelling, the final
narrow lifetime/compiler phase and original TU are unknown. These observations
do not establish an LTCG requirement. No matches row or exact-byte credit.

### Subsequent real-member closure

The complete native family1 member 46DD40 is subsequently 686/686 exact. A
private genuine same-TU definition before this caller preserves that entire
callee and the caller's1449-byte ea3990e6 payload. Narrow/word-storage views,
pre-guard locals and external visibility also retain the caller difference.
Repeated cap evaluation reaches 1452 bytes with a28h frame; a by-value
three-short policy reaches 1452 bytes but still differs 31 bytes. None is
selected. These source-context witnesses do not establish an LTCG barrier;

## Native execution and its limits

The v2 `audit-battle-collision-phase.py` (since removed) superseded the earlier 114-full/
396-tail execution receipt. Inspection found that the old seed left
`candidate->source_168` zero. The real provider reads its source's byte 4EA;
the emulator's mapped SEH page accidentally supplied a zero byte at 4EA. The
old finite comparison is therefore not valid-owner/game-startup evidence.
This fixture correction does not change source or canonical comparisons.

The new binding is pinned independently to target stores: Character constructor
462AB0 stores self at 16C/168 at 462BC4/462BCA; the exact Reimu object spawner
loads its owner from manager 64 at 4938DE and stores it at object 168 at 4938E7.
Fighters now bind 168 to self, and objects bind 168 to their side's fighter.
The zero page permits only the four-byte x86 SEH cell; all other native reads
and writes there are rejected. A missing-owner data control now stops at the
actual 46DA1C read of 4EA rather than silently accepting a zero source state.
This is a bounded runtime view, not a claim that the original constructors or
full startup execute in the fixture.

The auditor executes original and COFF entries at separate addresses. Actual
geometry, classification, collision providers, list helpers and real manager
getter run. Only the 12-byte native Buynode allocation and validated old-node
frees are environment callbacks, with permitted EAX/ECX/EDX clobbers. Code and
resource pages are read-only; writes are restricted to context/actors/nodes,
stack and the SEH cell. No gameplay/geometry/predicate result is supplied by
Python. Callback failures stop execution explicitly.

The final source passes **198 full entries and 396 explicit tail entries**, with
zero mismatches in each lane. Target coverage is 424/449 decoded instructions;
all normal reachable instructions execute. The remaining 25 are exactly 21
invalid-parameter calls and four skipped alignment instructions. Source visits
423 instructions because its remaining narrow conversion uses one fewer
instruction. Coverage is asserted against those exact excluded sets on a full
run, not inferred from a percentage.

The 198 full entries contain:

- 114 earlier topology/frame/classification cases, now with the corrected owner
  bindings: empty/mixed geometry, eight frame flag patterns, plain/oriented
  extensions, zero/one/two objects, result/status gates and old-list cleanup;
- 72 separated owned-object same-side cases over four shape-count pairs, three
  extension forms, source states 0/1/2 and one/two objects, enabling the frame 50
  same-side flag only on the owned objects;
- 12 actual same-side hit cases covering all four frame-flag pair outcomes,
  with zero/one/two owned objects. Fighters retain self bindings and source
  state zero. Real geometry/extent routines find the self overlap, and the
  actual 143-byte46C8A0 provider writes result 3 and returns true. No general-hit
  renderer/manager callback is substituted.

The target and candidate each execute 228 same-side provider entries and 390
opposing entries. The original frame-flag routine returns true 24 times on each
side. Each of the 12 hit fixtures independently requires both target fighter
results to be 3; the entire candidate arena must then agree. These observations
come from actual stack arguments, native AL returns and resulting state.

Every full entry compares all 128KiB of arena state, ordered allocation/free and
direct-call traces, actual RET/ESP/nonvolatile registers, restored SEH/x87
state and MXCSR. A data-only cosine table/SSE2 flag is an input rather than
startup evidence. The audit implementation/object hashes must remain stable
during the run; reconstruction-source producer verification remains separate
from existing-object execution. The refreshed audit SHA256 is
`029b16a1d4958b8e9b9d6c335d63ef16dcf82d7beebe76fd8c1f3c2f054ab595`.

Full entries reset deferred values to zero, including the supported frame-flag
hit exits. The 396-case tail lane remains necessary: it explicitly supplies the
attested 46E53B entry state,2Ch local frame/four saved registers, pending pointer
at ESP+30h and actual return address. It is not 396 additional whole-root calls.
Signed current/maximum boundaries, dword deltas with zero/nonzero low words and
positive/negative558 deltas execute target arithmetic and real 45D510. A full
nonzero dword with zero low word still enters the update. No low-word guard
replaces the observed dword guard.

Two fresh source negative controls retain the original source path and restore
its SHA before execution. Inverting the cap passes all 36 smoke full entries
but fails 10/24 tail entries. Changing only the same-side flag mask from 100000h
to 200000h fails 19/36 smoke full entries, including all 12 hit outcome checks,
while its 24 tail entries still agree. The negative report preserves differing
call counts and returns 1 for mismatches; equal-result runs still require
identical aggregate helper counts. Smoke and full matrices reuse inputs and
are not additive coverage.

Both child auditors import this environment. After the binding/read-guard
change, the exact traversal's226-record audit and the source-present pair's
2638-record audit replay with zero mismatches and retain their disclosed
instruction/return coverage. Their existing canonical exact/nonexact statuses
are unchanged.

General-hit/effect/callback graphs remain outside the fixture. The previously
failing unrestricted self-hit reaches 46A8A0 through the real general-hit path;
its absent InfoManager pointer 6FBCA8 produces the guarded write at 180 in
46A8A2. Correct source binding does not manufacture that separate manager
object or bypass the failure. The new supported hits return earlier through
the target's real frame-flag rule. Invalid containers, throwing allocation,
legacy x87 ceil, complete startup and arbitrary game states are also unproven.

### Further narrow-lifetime controls

Fourteen additional whole-root source hypotheses remain unselected. A narrow
member defined after its caller, both-field/reference-maximum policies, a
shared amount or fighter local, signed interpretation over unsigned-word
storage and a narrow accessor all preserve the complete ea3990e6 payload.
Reference-current, by-value minimum with sum first and unsigned-delta argument
policies reproduce the earlier 7f675ed2 payload. A separate final-loop index
produces c5fb9198, while cap-first by-value minimum produces 345df742. Every
candidate is 1449 bytes and first differs at+559; none explains the extra
MOVZX/register-sign-extension instruction. This is negative source/context
evidence, not a demonstrated LTCG barrier. No source, compiler flag, shared
layout or accepted relocation is changed.

## Reproduction

```bash
python3 scripts/build.py --unit gpt-web-battle-collision-phase --compare --json
python3 scripts/validate-tracking.py --require-target
python3 scripts/check-match-literals.py --require-target
python3 scripts/ci.py
git diff --check
```

The build command currently returns 1/nonexact, not an infrastructure failure. The
native audit returns 0 for the supported full/tail fixtures; `--smoke` selects 36 full
and 24 tail cases.

The direct 128MiB/CPU0 read-only Ghidra pass independently verifies executable
identity, entry, full mapped text, root bytes and all five inbound E8s. The
refreshed pass also attests fighter self-binding/object owner-binding stores,
reads back the disposable ECX/void signatures and discards changes. Nine primary DB
hashes remain unchanged. Decompiler text remains a hypothesis; IDA preflight
rejects the wrong open image and no IDA semantics or factory adapter is used.
This checkpoint adds source/ABI/execution evidence only. Exact totals are
unchanged, with no cold aggregate replay claim.
