# One observed frame construction model across PAT and effects

The actual eight-WORD/byte/pointer FrameData model now supplies both the PAT
base and the effect loader's28-byte frame values. The duplicated EffectFrameData
class is removed; the loader uses FrameData and its real lifetime definition.

## Context-sensitive zeroing, not a forced store sequence

The earlier FrameData model wrote a20-byte memset beginning at+04, then tag14
and pointer18. That reproduced the native derived PAT constructor, but did not
uniquely establish the original source expression. The independently recovered
effect temporary instead clears all28 bytes, including its just-published
virtual pointer, before publishing tag14 and pointer18.

A coherent ordinary constructor uses memset(this,0,sizeof(*this)), followed by
those same two publications. In the real derived PatRecord88 context, VC8
naturally removes overwritten base/virtual-pointer stores and emits the exact
same300-byte constructor. No inline directive, barrier, manual vtable address,
padding or register annotation is used. The destructive whole-object clear
was already independently observed in the effect temporary.

This is a source model consistent with the two observed construction contexts,
not a claim of a separately discovered standalone default-constructor entry
or proof of unique original spelling. It does not invent a generally portable
polymorphic-object initialization policy.

## Public source and exact scope

PatRecordLifetime.cpp now provides the whole-object FrameData construction.
EffectResourceLoading.cpp includes that actual definition and uses the shared
FrameData type. Its reads address the corresponding raw WORD members; sign and
field terminology remain deliberately unspecified where only width is proved.
The existing vector/helper bindings are renamed to their actual shared type,
without changing native destinations or widening data contracts.

Five affected PAT/base lifetime roots remain canonical exact:
460F90/300,45FFD0/515,4601E0/30,421A70/21,421A90/47.

The complete effect loader remains nonexact2528/2528 with exactly its prior
canonical source hash:
94b3933b2f738df5bc2b78da6ea254f3bec748027eba57fcefc6dccfca1ab49b.
Its first residual remains+1269/4383B5. Neither the unchanged size nor shared
type model earns exact credit or reopens register/branch-spelling experiments.

Actual dependency discovery finds only these two changed-source consumers.
Private coherent controls and public full receipts are retained in
build/frontier-frame-construction-20261031/. Counts are unchanged.
