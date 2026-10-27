# CProfileDeckEdit update, 0x0044A410

The complete virtual update now matches **1339/1339 bytes** with unchanged
VC8 SP1 O2/GS. Only the new `exact-first-profile-deck-update` unit is built;
no existing source/header/compiler profile is changed or cold corpus replayed.

## Observed target evidence

Canonical Japanese1.06a SHA256 is
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
All401 instructions are reachable inside the1339-byte span. Seven RET0 exits
are44A466,44A499,44A4C5,44A4EE,44A6B8,44A7DF and44A94A. Five following INT3
bytes separate the next body. There are no indirect branches or remote chunks.
The complete function SHA256 is
65539fc215a4dc89c300c3266eb32fe3d5094f701d0703b0b94cef9429dfba70.

The pointer at6C2234 is slot+8 in the vtable starting6C222C. Its COL at6D8610
names the TypeDescriptor6E6DDC `.?AVCProfileDeckEdit@@`. The table agrees with
existing destructor/menu/update/render virtual order. The function uses ECX as
its owner, returns AL booleans, and preserves all seven native exits. Twenty
invalid-parameter calls are natural VC8 checked-container operations.

The direct IDA launcher remains blocked by its missing mcp/uv environment.
Factory-native IDA metadata, entry68B9D2, entry bytes e8ca9f0000e916feffff and
inventory401000/52 were independently checked against the canonical PE before
semantic use. Supported name/prototype metadata was updated and read back;
no target bytes were patched. IDA decompilation remains provisional; raw PE
and strict whole-function relocation replay establish acceptance.

## Complete source behavior

`src/ui/ProfileDeckUpdate.cpp` uses the existing CProfileDeckEdit owner layout,
real VC8 map iterators, four GuideOverlay members and both MenuCursorState
members. No new public/shared layout is introduced.

- Update and hide each guide, then give message/confirmation modes priority.
- Preserve response codes2/3/4; save/export only when total deck count is20.
  The original insufficient-size message branch precedes the successful save.
- Resolve the selected spell key through the checked iterator deque. Toggle
  count-edit mode when owned/available; preserve cancel and exit prompt order.
- Increment only below both available count and4. Decrement positive counts.
  Maintain the original byte-sized total without adding saturation or a20 cap.
- Outside count-edit mode, key59 zeroes mapped counts without erasing nodes;
  cursor changes update/hide the original eight UI objects and dispatch events.
- Filter selection passes its low byte, then sign-extends the stored category
  back into the cursor. Do not replace this with a new range check.

The target explicitly loads ECX with this before both zero-stack-argument
message calls43F870/43F6E0. Their bodies do not read ECX; existing standalone
facades model them as cdecl. This caller preserves its observed member-compatible
entry via declaration-only views, without asserting original static/member
identity or changing the separately accepted helper. No extra argument, wrapper,
fake return or new provider credit is introduced. The player slot helper keeps
its established unsigned-short deque return; the existing export interface
accesses the same two-byte deck storage through its signed-key deque view.
These partial call receivers are never instantiated or allocated.

The two Japanese messages are source string literals with their complete native
Shift-JIS/NUL bytes, independently pinned to PUSH immediates6C220C/6C21DC and
checked against emitted COFF data. These are data, not copied instruction arrays.

## Trial and verification receipts

The first full compile already had the target1339-byte length. After binding
its two literal data symbols,72 differing positions remained, entirely in the
save-case branch ordering. Reversing the natural size guard to match the observed
failure-first flow made the complete function exact. Reconciling the player
slot's unsigned deque declaration was byte-neutral and remained exact.

`build/frontier-44a410-20261027/` retains first/literal/branch-order/typed-slot
objects and previews, full target disassembly/CFG facts, formal-first.json,
formal-second.log and final gate logs. The failed undefined external-string
preview is retained as a diagnostic, not a successful comparison.

```
scripts/repo-python scripts/build.py --unit exact-first-profile-deck-update --compare --json
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/check-match-literals.py --require-target
scripts/repo-python scripts/ci.py
```

Final CI is pending at writing; its terminal log/exit is the gate receipt.
No new runtime matrix is added. Actual UI, file writes and library execution
are not exercised by the byte comparison. Original nominal TU and helper source
identities remain unknown; canonical bytes and observed ABI are preserved.
