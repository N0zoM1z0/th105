# Fighter sequence rotation and implicit sprite copy

The complete authored rotation at 0x0045DDA0 is now canonical exact, 265 bytes.
Its SHA-256 is 922b385d72683135389e7bb1ed41f554ca2b2c9e66b8a8035f81ebc330bc3708.
The genuine implicit sprite copy at 0x00455160 is also canonical exact, 116 bytes,
SHA-256 5622aa17ac7b57fda6dc5016472a9c6913110430a96389172331f8cd3b377319.
That copy was already a compiler-generated exclusion. Its evidence is strengthened;
it is not a new exclusion or authored match.

## Observations and source recovery

The pinned Japanese v1.06a target remains the oracle. Its sprite copy publishes
CSpriteBase vtable 6C0654 before copying texture04, the 112-byte vertex array and
two dimensions; it then publishes CSprite vtable 6C0668 and copies five floats.
There is no initial IColor vptr publication. Raw RTTI identifies those classes.
The existing CNumberColorLifetime already models the four-byte color interface.
A local sprite-base view gives texture04 to the sprite base, rather than to the
older eight-byte IColor view. This leaves EffectSprite.hpp and all shared layouts
unchanged. Ordinary implicit C++ copy generation now reproduces the whole body;
there are no explicit copy assignments, manual vptr stores or copied code bytes.
The local declarations are evidence-backed layout views, not a claim that the
original nominal class declarations or translation-unit spelling are unique.

Making the implicit copy visible with the older base layout first eliminated
11 of the parent's 12 differing bytes, but emitted a 122-byte copy with an extra
IColor publication. Correct texture ownership gives the native 116-byte copy.
The last parent difference was a full-width versus byte-width final count load.
The initial nonempty test remains unsigned. After real deque front/pop_front/
push_back, a fresh unsigned-byte value is published to state55A and returned.
This is the actual observed AL value on both paths, not an inert scratch local.
The existing unsigned-char ABI is unchanged; its original nominal return type
is still unknown. The operation rotates the front entry to the back, not removal.

## Whole-function and support gates

Pinned VC8 SP1 /O2 /GS emits both complete canonical bodies. Every relocation is
bound, including independently attested sprite and color vtables. The record
destructor at 45CF50 (8 bytes), unwind funclet/handler at 6BAD60 (44 bytes), and
unwind table/FuncInfo at 6E0858 (44 bytes) also compare in full. These 96 support
bytes confer no extra authored credit. The directly related existing enqueue
45DBA0 freshly passes all 114 bytes. No shared header or compiler flag changed.

The old compiler-origin rule now has a genuine source anchor with unchanged
minimum non-relocation coverage 0.70, minimum 24 bytes and no alignment tail.
Full candidate-inventory uniqueness validation passes for the 116-byte copy.
No target bytes, acceptance gates or global origin census were rewritten.

Replay commands:

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-fighter-sequence-rotate --compare --json
    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit cross-v106a-sequence-enqueue --compare --json

Private receipts are under build/frontier-sequence-sprite-copy-20261031:
final.json, final-auxiliary.json, enqueue.json and origin.json. Earlier controls
are retained separately. The auxiliary audit is retained under the matching
.analysis directory. The earlier 2026-10-28 report records historical nonexact
controls, superseded by this whole-body replay.

Only 265 authored bytes and one authored function are added. Totals are 1,577
exact functions / 448,878 bytes, 1,774 source-present, 1,794 authored and 1,801
mapped; exclusions stay 1,714, review becomes 519 and units stay 759.
