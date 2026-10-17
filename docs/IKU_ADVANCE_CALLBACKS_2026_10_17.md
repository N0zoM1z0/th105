# Iku real animation completion and advance-call sharing

The whole-root native fixture now executes the original animation callbacks
and observes both advancement results for actions310/409. The selected C++
source is unchanged. This closes a runtime-evidence gap; it does not resolve
the separate compiler call-sharing difference or add exact authored credit.

Target remains original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Iku `[620920,62EFBE)` is59038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
Wrong-image IDA was rejected. Observations use the attested PE and direct,
read-only Ghidra; no factory adapter or IDA semantic information was used.

## Observed control and return contracts

Target310 calls4351C0 at624612;409 calls it at625893. Both test **AL** and
select action9 on a nonzero result, otherwise returning through the common
epilogue. The selected declaration already returns unsigned char. Target409
sets ECX before its landing Jcc and enters the CALL directly; this is not
evidence that the predicate preserves ECX. The candidate retains a shared
call6245ED with incoming set{310,409}, accounting for107 target advancement
sites versus106 candidate sites.

A private409 source control replaces the inline `advance_or_action(9)` with
an explicit failed-advance return, followed by the real action9 callback.
Its entire59478-byte canonical section is identical to the selected section,
SHA-256018be2dcd2b8361057022937b0d35c8ce4fbe2aa6933a0b625a523da11023bd3.
It retains the shared call and is unselected. This narrows a source-shape
hypothesis; it proves neither original source spelling nor an LTCG barrier.

The actual62-byte4351C0 increments DWORD144 and WORD142. At the signed
frame-limit comparison it may call original vslot20/45C1A0. A nonzero AL
then tail-calls original vslot14/45C220. The ordinary fixture initializes
frame limit14C to32767, so its usual small timer inputs do not establish this
successful callback path.

45C1A0 advances the signed frame index modulo the positive frame count,
applies the frame through45C110 and computes AL from frame-index zero and
block byte14. 45C220 follows block link1C when present, updates the frame
count and calls original vslot1C/45C180. It computes its own AL from block
field18, resetting sequence/time on the zero branch. These results now come
from actual target instructions, not replacement callback results.

## Real callback fixture

`scripts/iku_animation_callbacks.py` pins all13 dependency byte ranges and
checks the three original Iku vtable words at6C652C. The original vtable and
all executable bytes remain untouched. Only bounded input objects are built:

- Actor frame pointers/count/limit, with1..3 frames of stride88hex.
- Frame duration08, texture index0A, signed rectangle fields0C..12 and
  formats0/1. Format0 executes both genuine origin-scale methods.
- Two bounded blocks with observed fields04/08/14/18/1C and four combinations
  of link conditions. These are data-domain diagnostics, not a claim that
  every combination is encountered during play.
- A valid nonempty checked DWORD span at actor130, containing texture handle0.
  The genuine lookup40C100 and Sprite texture routines execute the supported
  zero-handle path, followed by the real reset/commit operations.

Actual frame application follows45C110's tail to436760. That code reads the
frame rectangle and texture slot, invokes407160/407230 and the Sprite
transform routines. The fixture checks actor ECX, Sprite ECX=this+4, lookup
ECX=the supplied span, and the compiler-private407230 receiver in **EAX**.
No external C++ EAX declaration, return shim, device mock or code patch is
introduced. The existing write and x87-stack/control-word checks remain.

436760 and40C100 remain unclassified ledger entries. Their pinned execution
ranges do not promote callable boundaries, authored/library origin, source
selection or exactness. Nonzero texture resources, invalid spans, frame
format2, unmasked exceptions and final action-callback continuation remain
outside this fixture's evidence.

## Native results

The new whole-entry `--advance-callbacks` profile passes **0/1992 mismatches**.
It varies before/at-duration timing and signed WORD timer wrap, durations1/3,
frame counts1/2/3, first/last frame, block mode/link conditions, frame formats
and x87 PC53/64. Additional310 sequence1/2 cases retain its genuine double
counter increment and threshold/wrap behavior.

| Action | Actual successful advance, action9 entry | Normal root RET |
| --- | ---: | ---: |
| 310 | 120 | 912 |
| 409 | 48 | 912 |

Per side, the actual callbacks include712 next-frame and264 next-block
entries. There are168 final action9 entries and1824 RETs;121 target-root
instructions and324 distinct instructions across the13 pinned dependencies
are visited. Every case must reach exactly one actual4351C0, and each selected
action must cover both outcomes. Successful cases execute frame callbacks
before reaching the final action9 backend; that final callback itself remains
the stop boundary.

`--control advance-action` changes only409's successful fallback action9 to10.
It detects **48/960 differences**, exactly its48 successful advancement cases;
the other912 cases return normally. This calibration would not establish the
successful path in the ordinary high-frame-limit fixture.

| Profile | Input SHA-256 | Target-output SHA-256 |
| --- | --- | --- |
| Positive1992 | dc8041a11b3df036d2544edaa8f47135e95fd118a394e429bdbede7ed3b05c55 | 4fe424334c92b8dbbf919813707874d44876579fdde4f2219ca6fd3f7f1c1c47 |
| Wrong-action960 | 8408a38350172c666a36985634e9b35a08a796b54ff6afea91915afa38e8850f | bea36b384dd45138392b99c13179a220663fe4e723eaa437e6b4e016024252c0 |

Configured/native complete59478-byte sections agree. C++ source remains
CRLF SHA-256d6a5f1276ad22ba8739d7d3cefb2a09e57da92b92e3efb2ca8b6f505744a2c12;
canonical section remains018be2dcd2b8361057022937b0d35c8ce4fbe2aa6933a0b625a523da11023bd3.
Strict whole59038 still first differs at+64hex/620984. Initial constant1,
other shared tails, original compiler/TU/source and full-root behavior remain
unresolved. Other native matrices and accepted units were not replayed.

## Reproduction and analysis lifecycle

```sh
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json
python3 scripts/probe-iku-upper-actions.py --advance-callbacks --output build/iku-advance-sharing/IkuAdvanceCallbacksNative.obj
python3 scripts/probe-iku-upper-actions.py --advance-callbacks --control advance-action
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/iku-advance-sharing/IkuAdvanceCallbacksNative.obj
python3 scripts/ci.py
git diff --check
```

Comparison and the intentional control exit1. Reports are under
`build/iku-advance-sharing/`; private source/Ghidra recipes are under
`.analysis/iku-advance-sharing-20261017/`. Direct Ghidra independently attests
import/file identity, entry, full mapped .text, root, all13 dependency spans,
the three vtable words and the decisive AL/callback instructions. Bounded
disassembly changes were discarded in one read-only768MiB/two-CPU clone;
all nine primary files are hash-unchanged. The clone and temporary path alias
were removed. Superseded controls/objects/caches are disposable. No C++/shared
header/layout/profile/relocation, exact ledger or aggregate replay changed.
