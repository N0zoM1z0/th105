# Original CRT bad_exception lifetimes, not bad_alloc

Three complete routines from the actual pinned libcmt:frame.obj now match the
canonical target and are inventory-unique:
-68EF88/11: std::bad_exception destructor.
-68EF93/34: scalar/vector deleting destructor aliases, counted once.
-68FB16/24: std::bad_exception copy constructor.

This class is bad_exception, independently established by its complete RTTI
graph and vtable6CD9B8. The earlier bad_alloc lookalike at68EF88 was correctly
not accepted under that wrong class identity. These69 bytes are vc8_runtime
exclusions, not authored code or guessed new source mappings.

## Source and full body checks

The unchanged genuine original seven-TU library build naturally pulls the
original CRT frame object. It introduces no private helper export, new C++
wrapper, ABI facade, compiler switch or COFF barrier. All three MAP functions
must have their actual original frame.obj ownership; only the scalar/vector
pair may share an entry. The real public library constructor remains the only
export and receives no new exactness claim. Pinned CRT archive/build hashes
are retained in the fresh proof.

Each body is decoded completely through RET4 or its actual tail jump. Named
base exception destructor689FDA, copy689F82 and operator delete6898EA resolve
through original CRT owners and independent accepted origin evidence. The
normal destructor fields are REL32+7 and vptr+2; scalar fields are calls+10/+23
and vptr+5; copy fields are call+8 and vptr+14. All source HIGHLOW entries are
accounted for. Only those proved pointer/call fields are canonicalized; every
other byte is unchanged. Whole inventory uniqueness applies to each routine,
not a prefix, masked pattern or short-code heuristic.

## Complete RTTI graph

The source and native primary vtables contain exactly the checked scalar
entry and inherited exception::what at689FF0. The latter retains its prior
runtime ownership, with no extra credit. The vtable prefix, whole20-byte
complete-object locator, both TypeDescriptors including entire names, both
28-byte base descriptors, both hierarchy descriptors and their complete base
arrays are canonical.

Primary offsets/signatures must be zero. The bad_exception hierarchy has two
bases, itself and exception; exception has one. Each base's contained count,
PMD adjustment and0x40 attribute are fixed. Own-class hierarchy references
must close locally, shared source metadata must retain consistent target
identity, and cycles/aliases are checked rather than ignored. All data
relocations are exact and accounted for. This establishes the real class and
its base relationship; no ThrowInfo or other unused metadata is claimed by
this scope.

## Verification and limits

Fourteen focused tests reject wrong type, partial extent/mask, missing member,
extra alias, unknown callee, wrong vtable, nonprimary/base-layout changes,
changed complete names and inconsistent RTTI cycles/pointer identities.
Twenty actual code and RTTI graph byte mutations are rejected. The existing
canonical comparator and generic origin thresholds are unchanged.

No gameplay source, match unit or old exact receipt changes. Excluded2015/review357;
authored exact1431/443916 bytes, authored1655, source1635, mapped1820 and units777
stay unchanged.
