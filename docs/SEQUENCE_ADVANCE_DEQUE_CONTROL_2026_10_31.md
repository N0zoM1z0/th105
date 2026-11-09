# Sequence advance: genuine deque control

The new fully matching rotation and implicit sprite copy motivated a bounded
check of the existing source-present advance at 45D040. The canonical native
body remains 198 bytes, SHA-256
b2d9f98e42afffc206e502e400b6112aac95632fbec533c2ef1f191226958a28.
Raw target was hash-attested; no new IDA semantics were used.

Replacing the handwritten checked-pop block with the actual typed card deque's
pop_front emits only 163 bytes. Its generated destructor is correctly bound to
the IColor vtable, but pop_front does not supply the target's checked iterator
construction/dereference checks. Calling real erase(begin()) instead emits 168
bytes with an out-of-line erase call and iterator stack lifetime absent from
the native body. Neither control is accepted. Do not insert an unused front()
call, a dummy iterator or a manual register barrier to recreate checks.

The directly affected front-ready peer stays exact118 in both controls; consume
stays346/nonexact at+204. Source and temporary manifest binding are fully
restored. The earlier truthful-destructor/zero-propagation result remains a
separate known boundary; these controls do not resolve it. No ledger or progress
changes. Receipts are build/frontier-sequence-advance-deque-20261031/formal.json,
bound.json and erase.json; bound.json explicitly compares the existing object
without claiming fresh build provenance after the temporary manifest binding.

## Real sequence subscript control, 2026-11-09

After proving the actual sequence record's push-back provider, a separate
bounded control replaced every `entry_at_checked` call in `SpellRuntime.cpp`
with the real `std::deque<FighterSequenceSlot>::operator[]`. The emitted
94-byte provider matches `0x4399C0` in full, including all invalid-parameter
calls. This is the existing 0x98-byte record, not a short-element deque.

Readiness remains exact118. Advance remains198/native198, first difference
+46, and consume remains346/native346, first difference+204. Their complete
canonical candidate hashes are unchanged from the current source. Actual
subscript visibility therefore does not resolve either known residual. The
control stays private rather than publishing another declaration-only rename;
no source, ledger or acceptance status changes. Reports are
`build/frontier-sequence-read-provider-20261109/probe.json` and `provider.json`.
