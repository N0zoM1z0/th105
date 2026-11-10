# Info record: natural sprite-member lifetime

The implicit constructor at46EA40 is now reproduced in full:28 bytes, SHA256
c2c0d1bf762c4ec2cada7bbef9f79c0685c511dd3b66b7ba19363ed1fe4eed29.
It is compiler-generated provenance, not28 authored exact bytes. The unchanged
full-inventory uniqueness gate accepts24 nonrelocation bytes and one4-byte
vtable relocation, with minimum0.70 coverage/24 bytes/no alignment tail.

## Independent ownership and source evidence

Canonical-exact CInfoManagerBase constructor46F5D0 pushes destructor46E950
at46F658 and constructor46EA40 at46F65D, count2 and stride154, before the real
VC8 array-constructor call46F675. The corresponding owner destructor46F6A0
uses the same record destructor. Existing InfoLongRecord154Runtime separately
establishes the actual sprite members at04/98, followed by timer12C, fade bytes,
position/velocity/scale, active14C and lifetime150. The record resource at00
and remaining scalar state are not initialized by this callback.

The current constructor decodes completely through its RET at46EA5B, followed
by INT3 alignment. It clears each sprite texture handle and installs the real
CSprite vptr6C0668. The paired destructor46E950 publishes IColor6C0624 to the
two sprites in reverse order. These are observations, not manual source stores.
Factory-native IDA identifies the CSprite vptr; the prior same-session mapped
byte preflight passed, and pinned raw PE plus exact owner provide the proof.

The source uses a local ordinary polymorphic sprite view. The four-byte color
interface and texture ownership follow the already exact implicit sprite copy
455160; the zero-initializing DesignTextureHandle is an existing four-byte
value independently used by the exact Character constructor and design resource
lifetimes. No shared class layout is edited. No handwritten vptr, explicit
record constructor/destructor, padding local, fake ABI or exception annotation
is used. Ordinary C++ generates both array callbacks from the actual members.

## Bounded source controls and complete comparisons

The initial existing ProfileCSpriteLifetime view gives28 bytes but loads the
vtable constant before the first zero store, unlike the target. Moving to the
independently supported four-byte color base while leaving texture scalar is
byte-neutral. Giving texture04 the existing initializing handle lifetime moves
the first zero store before that load naturally and reproduces all28 bytes.
These are member-ownership controls, not register/spelling forcing.

All three accepted owner lifetime functions remain canonical:195-byte
constructor46F5D0,185-byte destructor46F6A0 and30-byte deleting destructor46F760.
The generated record destructor46E950 also compares fully,15 bytes/SHA256
13c246d3bcc6065db09caa3462cda670cb28700f35ea08b13ad1be865e9506e7.
That support result does not reclassify the15-byte record; it stays review,
and no short-function origin threshold is waived. Original nominal type/TU
spelling is not uniquely established by these matches.

The existing cross-v106a-info-manager-base-lifetime unit now also compares the
28-byte constructor. Source and origin anchor both use the actual owner TU. The one
new compiler-origin rule passes full4027-candidate uniqueness, not just a
selected-address comparison. No target bytes or public validator change.

Totals: exact1582/449309 authored bytes, source1782, authored1802, mapped1809,
units765 unchanged; compiler exclusions1792, review433. No push.
