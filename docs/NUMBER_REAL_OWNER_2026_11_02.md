# Shared CNumber runtime and lifetime owner, 2026-11-02

Pinned original Japanese v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Source unification

CNumberRuntime.hpp now contains CNumber's ordinary inline destructor: release
number_value_24 directly when nonzero, then let actual CTile and IColor destruct
normally. This is the existing independently exact cleanup, transferred without
adding virtual deletion or other behavior. The member remains INumberValue *;
its address is passed directly to operator delete as in the target.
CNumberLifetime.cpp defines the three actual CNumber color forwarding methods.
CNumberLifetime.hpp is now only a compatibility header with aliases to actual
CNumber and IColor, eliminating its duplicate owner declaration and constructor.

Offset checks for value +0x24 and tile +0x28 are private compile-time typedefs
inside the existing constructor. They add no runtime object or instruction.
Total size stays 0xCC. Compiler flags, preservation settings and runtime choices
are unchanged. Manifest and the scalar origin anchor use actual method symbols;
record cleanup source pins include the reviewed runtime header.

## Results

Fresh before/after controls preserve normal destructor 40, three color methods
11 each, scalar 60, DesignNumber scalar 61, integer renderer 312, Connect ctor
728 and destructor 315. The actual runtime-containing constructor unit now also
emits the whole canonical 60-byte CNumber scalar wrapper, SHA-256
778cb8774685a6977529384329fe9092b6778a76ccfaa59999f0c5d619e007dd.
This resolves the previous separate runtime/lifetime scalar-body limitation,
without counting compiler-generated wrapper bytes as authored progress.

The actual include closure is 13 units. All 28 accepted roots in 11 units are
freshly exact; 13 other roots in eight units retain fresh HEAD hashes.
CNumber initialize stays 102 versus native 104 bytes, with unchanged SHA-256
fcd06b657b11f935b2f8b7a8a9b275a5a1ccbc41c768c732468f633ec0e32f61.
Its scratch-word lane is not reopened or artificially shaped.

The full Connect constructor EH at 0x6B9590 is 168 bytes with handler 0x6B961D;
its full FuncInfo/unwind table is 116 bytes. The destructor retains its complete
168+116-byte proof. Combined support comparison is 568 exact bytes. String
and deque cleanup providers are independently checked in full; the constructor's
MenuString28 declaration refers to the same native string cleanup at 0x401E00.
The original two sprite facade declarations in Connect construction are not
claimed unified by this change. Actual CTile RTTI 247 bytes, its four-slot table,
CNumber's zero-offset IColor base and four method roles pass. Namespace-specific
outer RTTI and full-program linkage are not asserted identical.

Scoped scalar origins (2 / 121 bytes) and record cleanup origins (2 / 23 bytes)
pass. No origin disposition or count changes. Final CI passed all 962 tests (97.791
seconds), tracking, generated progress and whitespace checks. Both diff checks
passed. No private evidence or target binary is committed.

Totals: 1427 exact / 443604 bytes, 1637 source-present, 1656 authored,
1826 mapped, 2074 excluded, 297 review and 813 units, all unchanged.
