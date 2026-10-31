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
