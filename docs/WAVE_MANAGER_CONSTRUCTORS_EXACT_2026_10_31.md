# Wave-service member constructors: complete private-entry proofs

Original Japanese TH105 v1.06a executable SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

Both concrete manager constructors are now independently canonical exact:

- Wave-buffer manager401E40:193/193, SHA-256
  5d6088c6ca4be2548300991e6d0441e7b76e948d9a2ae176a817186090e7bca9.
- DirectSound manager401F80:145/145, SHA-256
  07c0f7eb1cc137608c34fa8e2bd43eb5a0617d449af0a9476dd44c356c5e9e26.

Each additionally passes all120 cleanup/EH bytes: handler27, three11-byte
funclets, FuncInfo36 and unwind map24. The wave member uses handler6BE461 and
info6E4C94; the sound member uses6BDFF1 and6E4680. Extra EH bytes receive no
authored credit.

## Actual source and entry

The existing ResourceHandleManagerLifetime.hpp source is unchanged in this
follow-up. Genuine C++ member construction initializes the actual containers
and critical section, then the application generation counter44 is zeroed.
Native RTTI associates the two concrete pointer-resource specializations with
CHandleManager<CWaveBuffer*> and CHandleManager<CDSBuffer*>.

The first constructor naturally specializes to the fixed global member and
takes no receiver argument. The second naturally consumes its receiver from
the stack and returns with RET4. Neither private ABI is declared in source.

Their real direct callers are4018A9 and4018BB in the already-exact WaveService
constructor401880. That143-byte parent, all130 parent cleanup/EH bytes, complete
458-byte storage,17-byte initializer, real CRT table slot and5-byte exit tail
are freshly replayed before accepting either child.

## Narrow global-parent extension

linked_global_caller.py extends the existing exact-parent mechanism only to a
direct, single-site, ordinary default constructor of an actually attested
polymorphic class. The parent must be a verified global constructor, not a
destructor, source-only caller, callback, arbitrary function or deeper chain.

Both parent and child require complete cleanup/EH. The child class must have
its real typed vtable contract; named classes and the already-supported ordinary
one-pointer-argument template form are accepted. Global storage/startup evidence
must equal the current image's freshly generated witness. The complete parent
source/target body hashes and exact relocations still pass the old verifier.
The native/source E8 edge and the actual named constructor binding must agree.

The child receipt retains the parent global witness and every parent EH region.
No export is added to control the constructor ABI, and no receiver instructions,
code bytes or field accesses are waived. Existing source-only and private-parent
paths keep their earlier requirements. Six new tests cover the bounded extension
and reject missing/stale/mismatching global/EH evidence and unsupported entry roles.

## Focused regressions and accounting

The public wave-service unit passes all four lifetimes: parent143/128 and
members193/145. Old BGM private stream220 and nested reader15 still pass their
exact-parent chain. Old UDP packet constructor145, normal destructor98 and
scalar wrapper30 remain exact, including the source-only constructor path.
Four existing wave-buffer callback proofs are still mandatory and gain no
additional credit.

Only two whole member constructors add338 authored bytes:
1569 exact /447032 bytes; source1765, authored1785, mapped1792,
excluded1658, review584, units754.

Receipts: build/frontier-wave-manager-constructors-20261031/, with the public
wave-service, BGM and UDP reports. No cold whole-repository replay is claimed.
