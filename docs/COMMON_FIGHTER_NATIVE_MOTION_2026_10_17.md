# Common Fighter motion execution, October 17

The active major root is again `Fighter_update_common_action_state @ 004740C0`,
10219 callable bytes used by all 15 roster action roots. This checkpoint adds a
bounded native execution oracle and names one related animation-context field.
The complete canonical comparison remains nonexact; no exact or partial byte
credit is added. The [previous receiver/domain evidence](COMMON_FIGHTER_ROOT_2026_10_16.md)
continues to apply.

## Target and source observations

Only original Japanese 1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The target body hash remains
`7def23cf4826d7511260e7d9ea8db18848c43a7b77939bb42724a29af117a0c6`.
Raw closure covers 2799 instructions and 10219 bytes; switch tables and the eight
qualified virtual tails retain their existing evidence and acceptance limits.

The already exact 62-byte `advance_frame_and_dispatch @ 004351C0` increments
DWORD+144 and WORD+142, then uses a signed comparison against WORD+14C before
its virtual animation calls. The JL is at 4351E3. The local CharacterEx view now
names signed-short `frame_limit_14c`, splitting the existing unknown span.
An offset assertion checks+14C; all subsequent offsets and the 7A4-byte prefix
size remain unchanged. This is related helper context, not a newly discovered
direct access by the common root or a complete original-class declaration.

Fresh configured compilation is byte-neutral: the canonical 10219-byte window
still hashes to
`99563500433bccf1f68e7c256b438595de9cdcf5b18aee4816f19e69e1cda835`.
It retains 53/66 identical diagnostic owners, metadata+2838 and 10801-byte COFF
section tail. The first mismatch remains+14 /4740D4, target 48 / candidate 95.
Source/TU, SUB lowering and physical clamp/sequence ownership remain open.

## Native motion controls

```bash
python3 scripts/build.py --unit gpt-web-fighter-common-action-state --compare --json
```

The first command still exits 1 for the nonexact function. The new command
executes original target instructions and the normally relocated COFF body
through their genuine RET. It executes all six dependencies from the original
PE; no helper result or instruction is replaced by a hook. It compares the
entire 7A4-byte actor prefix, helper calls, physical x87 conversion inputs,
caller stack displacement and control word. Every path must restore x87 TOP
and finish at the return marker with stack delta 4.

The **14208 controls have zero differences**. They cover 25 early/late motion
actions,48 velocity bit patterns, both values of the boundary-peer flag,
stage center/edges, and masked PC53/64. Patterns include signed zero,
subnormals, infinities, quiet/signaling NaNs and adjacent values around the
friction constants. Action 53 varies its direction-state word 0/1 at stage center.
Its wall-event branch is outside this actor-only fixture.

The actual input context is explicit: Y0; original zero-initialized1280-float
surface at 6FA898, asserted byte-for-byte; frame counter 7, frame timer 0 and frame
limit 32767. This keeps the real animation helper on its counter-update/return
path. The real CharacterEx vtable is present, but animation/resource dispatch
is not modeled. Writes outside the 7A4 actor prefix and stack fail the probe;
unreviewed direct or indirect calls fail before being treated as valid paths.

| Original dependency | Calls in each target/candidate set |
| --- | ---: |
| landing transition 473DD0 | 14208 |
| at/below surface 435DC0 | 14208 |
| surface height 435D60 | 14208 |
| X boundary 435910 | 11904 |
| frame advance 4351C0 | 14208 |
| conversion 68A1A0 | 14208 |

The matrix visits 403/2799 target instructions and 424 candidate instructions.
It does not establish complete branch, gameplay, numerical or exception
coverage. Report input SHA-256 is
`7ad4efb619ff804c8fd40ad1c955de07d41d18448e979921b2085cace223c791`;
reports also pin executable/body, object, Python, Unicorn and loaded-library
hashes. The oracle itself does not attest compiler provenance; the separate
fresh configured build receipt supplies that evidence.

## Verified negative controls

A real source control replaces action 159's two separately rounded float
increments by 0.6000000238418579 with a double-expression chain rounded only
once at the end. The 75-case smoke command reports **one mismatch** and exits 1:

| Input/action159 | Target velocity bits/value | Once-rounded control |
| --- | --- | --- |
| initial velocity-3, center, PC53 | BFE66667 / -1.8000000715255737 | BFE66666 / -1.7999999523162842 |

Thus algebraically combining those steps loses an observable rounding boundary.
The control is private and discarded. It is not a replacement reconstruction
or acceptance input. `--smoke` runs the 75 finite interior controls on a supplied
object; differences exit 1, input/target/execution failures exit 2.

An action 53 negative velocity at X40 reaches the wall-event publisher 4359D0.
The scope guard rejects it; no fabricated callback or animation state is supplied.
This is an incomplete input context, not a source mismatch or a passing test.

## Rejected code-generation controls and working state

The prior CPU root 5F1F80 remains at its committed checkpoint. An isolated signed
counter 320 plus shared-store jump preserves both signed comparisons and gives
a20-instruction/86-byte arm, but changes the upper branch and merges into a
different physical store owner. Explicit common-join edges fold the lower bound
again. These are not whole-function improvements; no CPU source is changed.

For the common root, explicit normalized switch indices leave its ADD-negative
encodings unchanged. Moving the sequence source arm changes real body order;
a reference-based clamp control merges target-distinct owners and has no valid
owner score. All are discarded. The next work remains recovering simultaneous
physical clamp/sequence ownership while preserving the demonstrated rounding,
not counting execution coverage as exactness or repeating equivalent shapes.

Direct Ghidra re-attests executable identity, entry, Windows/x86 target and mapped
text. It saves and reads back signed 16 field+14C and the native-helper context
comment, keeping all earlier ABI/domain facts and every target byte. The view now
has 52 named data fields plus its vptr; only 51 are direct root accesses. A fresh
read-only process verifies the update before the working project is copied back.
Temporary project copies and probe objects are removed after use. No shared header,
compiler profile, relocation contract or accepted unit changes; no aggregate cold
replay is claimed.
