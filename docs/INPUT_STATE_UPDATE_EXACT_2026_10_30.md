# Input-state table update: complete266 exact

InputStateTableStorage::update_input_state_table at40A550 now compares266/266
from genuine VC8 CIL with its byte-vector add-key sibling and pinned CRT.
The current DirectInputBackend.raw_keyboard_state field supplies702A48.
The old unselected retained source incorrectly used6ECFF0; it never had exact
credit. No explicit alignment, artificial local, register directive or altered
calling convention is used. Incremental total:1544 functions /437755 bytes.

## Target and source evidence

Fresh Factory native IDA metadata, entry and five mapped samples were compared
with the hash-pinned raw PE at20:44-20:45 UTC; fresh input inventory,
disassembly, decompilation and callers/callees were captured20:49. Target identity
is original Japanese1.06a SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
Raw caller43B4A0 calls update at43B4A8 and discards its incidental EAX.
The ordinary void thiscall declaration is retained.

The real checked vector iterates tracked byte keys and increments held-key
counters, otherwise clears them. Shift2A/36, Alt38/B8 and Control1D/9D pairs
publish three byte flags at410/411/412. Native nonzero high-bit semantics are
preserved without additional guards. The input state owner layout and its
ordinary vector<char-sized unsigned key> implementation remain unchanged.

The real public add_tracked_key sibling is retained in the same source TU and
exported through its ordinary declared thiscall ABI. It is not a fabricated
caller or a forced-inlining barrier. Its complete CIL body is269/native202;
the target preserves a private vector insert boundary not recovered here.
No exact credit is assigned to this sibling. Its known scene bootstrap calls
at43EE3B and the subsequent twelve key registrations establish real usage.
A single-update-only context folded the error string into a specialized helper;
that context was not accepted by the existing direct-message witness.

## Complete comparison and bounded tooling

The root has two RET0 paths and one internal noreturn error jump at40A5DE.
The helper40A8A0 is a distinct117-byte VC8 byte-vector range-error specialization,
not the existing123-byte40C350 design-vector helper. Both are individually
hash-pinned. The new contract requires the exact unsigned-char vector symbol,
native helper/throw/exception-record anchors, genuine source MSVCR80 throw
import, one literal message, actual second throw argument, and all three
catchable type names/layouts. It proves only the error role, not helper/EH
exactness or library-origin credit. The original design contract is unchanged.

Native40A56D contains an unreachable3-byte neutral LEA before the16-byte-aligned
loop at40A570. The compiler emits the identical bytes at the identical relative
offset. The explicit alignment contract admits only a declared unreachable
three-byte LEA reg,[same-reg+0], immediately preceding a reached aligned entry.
Both target and source CFGs must account for every instruction. These bytes
remain in the canonical byte stream; they are neither normalized nor masked.
Synthetic tests reject live/moved/undeclared sites, changed operands/displacement,
non-LEA padding and missing alignment, and prove that two neutral register
spellings still compare differently.

The canonical266-byte SHA is
00674c9ab1f5221b57043d7a070536f62564db1da5a32ea3dbae8961a9a9c92a.
All four REL32 operands and current runtime data addresses are replayed.
The indexed keyboard address also stays in the full compared instruction.

## Validation

Reproduce:
scripts/repo-python scripts/build.py --unit exact-first-input-state-update --compare --json

The two affected ordinary InputCluster units retain all four prior exact
functions. The existing design-cleanup linked unit retains its310-byte exact
root and original range-error witness. Focused linked/error tests pass.
No full-corpus rebuild was performed; unrelated receipts are preserved.

Receipts and raw boundaries: build/frontier-input-state-cil-20261030.
Mapped sample evidence: build/frontier-pixel-upload-20261030/ida-preflight.json.
Private sibling/static-CRT controls are under the matching .analysis directory.
