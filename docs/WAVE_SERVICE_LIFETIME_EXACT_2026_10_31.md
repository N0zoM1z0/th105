# Complete global wave-service lifetimes

Target: original Japanese TH105 v1.06a, SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

Two normal game-owner functions now compare completely exact:

- Constructor401880,143 bytes:
  688f0a4fa278fcee5f7eb320de948db86b5cc479761a046bacfb9fcd82b6f56e.
- Destructor401910,128 bytes:
  373508e62e6093c78e125a6995103adca928d39ed3a9c1d4a96eb53688a898a5.

Both also pass every byte of the shared native three-state cleanup: handler
6BD83B/27, funclets8/11/24, FuncInfo6E3E04/36 and unwind map24, total130 bytes
outside each authored main body. These extra regions receive no authored credit.

## Concrete application ownership

Raw constructor and destructor calls independently place two64-byte resource
managers at offsets0/64,32 base DirectSound buffers of0C bytes atC8, and32
spatial buffers of10 bytes at248. The existing buffer initialization/release
methods independently establish counters448/44C and gains450/454. The complete
service occupies458 bytes at702288. The source leaves those final primitive
fields uninitialized in construction, as observed; initial zero storage is a
loader property, not an invented constructor statement.

WaveServiceLifetime.cpp expresses that real game-specific composition with
ordinary C++ construction/destruction. Existing actual resource-provider source
is reused. The member-manager declaration moves to a shared header and its
ordinary constructor initializes the observed generation counter44 to zero.
No hand-written cleanup loops, vptr stores, padding, assembly or custom register
ABI are used. Original class/member spelling remains an interpretation.

## Real global proof

The existing strict global-lifecycle contract verifies:

- The sole native COFF BSS object has the actual458-byte extent/alignment.
- Source and target mapped storage are writable, nonexecutable and initially zero.
- The full17-byte initializer6BE6F0 calls401880 and registers6BEDC0 with the
  positively identified CRT atexit68AF1E.
- Its unique real CRT C++ initializer-table slot is6C035C.
- The complete five-byte exit callback6BEDC0 jumps to401910.

The source functions naturally specialize to the global object without a
receiver parameter. Their ordinary C++ signatures are unchanged. A new scoped
storage alias records only actual member references; old opaque aliases are
not widened. No synthetic initializer or callback stub is linked.

## Strict array callback proof

The new linked_wave_callbacks module handles only the four existing wave-buffer
constructor/destructor entries used by this verified global service:

- Base constructor418280/17.
- Spatial constructor4180B0/20.
- Base destructor4182E0/33.
- Spatial destructor4180F0/139, including its complete cleanup/EH.

All209 callback main bytes must freshly compare exactly in the current image
against their fixed native hashes and existing exact source records before any
code-pointer reference is returned. CIL ownership, full extents, exact HIGHLOW
coverage, real vtables and all required exception cleanup remain mandatory.
The actual reviewed DirectSound provider CPP must be in the source dependencies.

References permit only immediate PUSH operands, not arbitrary code addresses,
memory reads/writes, different symbols/targets/sizes, prefix matches or unproved
callbacks. The flag requires this concrete458-byte global and its real
constructor/destructor pair. Eight new tests exercise negative and positive
contract boundaries. No existing byte or relocation comparison is relaxed.

The four callback functions were already accepted and earn no new credit.
The two member constructors emitted193/145-byte bodies, but remain unselected;
length alone is not acceptance.

## Focused verification and accounting

The public wave-service pair passes with complete global and EH proofs.
After the shared manager-header change, all three old98-byte manager destructors
and their30-byte scalar wrappers freshly remain exact. Both old package-store
global lifetimes also pass, exercising the unchanged generic global path.
The normal tool test suite is run after final ledger updates; no cold whole
repository replay is claimed.

Unit: exact-first-wave-service-lifetime.
Receipts: build/frontier-wave-service-lifetime-20261031/, including the public
wave-service, resource-manager and package-store reports.

The two concrete application-owner bodies add271 authored bytes:
1567 exact /446694 bytes. Source1763, authored1783, mapped1790,
excluded1658, review586, units754. Compiler array iterators, static wrappers,
exit callbacks, already-matched resource callbacks and unselected members add
no authored credit.
