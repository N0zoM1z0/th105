# Three concrete resource-manager lifetimes

Target: original Japanese TH105 v1.06a, SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Complete canonical results

Three normal application-owner destructors now match98/98 bytes each:

- 401F10, CHandleManager<CWaveBuffer*>; vtable6D6994.
- 402020, CHandleManager<CDSBuffer*>; vtable6D699C.
- 404FD0, CHandleManager<IDirect3DTexture9*>; vtable6D69AC.

Their real scalar-deleting wrappers402090,4020B0 and405040 also compare30/30
each, but remain compiler-excluded and earn no authored credit. All six
physical functions have complete fresh public receipts in
build/frontier-resource-manager-lifetime-20261031/formal.json.

Raw decoding closes all34 instructions of each98-byte normal destructor,
with conditional frees, one RET0 and no escaping branches. Previously pinned
zero-offset COL/type-descriptor/scalar-wrapper evidence identifies each real
resource specialization; the linked replay independently reads back that RTTI
and its actual vtable entry. The canonical receipt records each full body hash.

## Genuine ownership source

ResourceHandleManagerLifetime.cpp expresses the recovered0x64-byte manager:
primary virtual pointer; deque<T> at04; vector<T*> at18; generation vector28;
unsigned free-slot list38; generation DWORD44; and the genuine existing
critical-section member48. T is an opaque resource pointer in each concrete
specialization. Only pointer storage is accessed, so no invented resource-object
layout is required. Compile-time size and member-offset checks pin the shape.

An ordinary virtual destructor with an empty body naturally destroys these
real members in reverse order. There are no hand-written STL free loops,
vptr stores, dummy locals, barriers, custom register calling conventions or
copied target instructions. The normal game-owner lifetimes are distinguished
from their compiler-generated deleting wrappers, as in the independently
accepted UDP packet manager with this same physical ownership prefix.

The existing, unmodified unsigned-list and unsigned-vector COFF instantiations
are linked with the real CIL source. This established source/library boundary
naturally preserves the public ECX list cleanup and private ESI deque cleanup.
The target413E10 helper is not declared as an invented ESI C++ ABI. Its emitted
native calls are resolved from actual source symbols.

This reconstructs destruction of container storage, not a claim that the
manager destructor releases every external pointed-to resource. It does not
replace the existing method-focused acquisition/lookup/release views.

## Narrow symbolic contract addition

The linked validator previously accepted only non-template class vtable names.
It now additionally accepts the observed VC8 name shape for a namespace-qualified
class template with one ordinary pointer-to-named-class/struct argument.
References, integral/value arguments, nested templates, multiple arguments and
unrecognized suffixes remain rejected.

All existing requirements stay intact: the scalar entry must have exactly the
same owner spelling, the real source vtable/RTTI and native type descriptor must
validate, pointer relocations must be present, an actual exported source root
must exist, and every compared byte must match. No body or relocation check was
relaxed. Three new tests cover the supported shape, wrong-owner rejection and
unsupported argument shapes, while preserving ordinary named-class behavior.

The public six-function replay passed after that validator change. Fresh
regression of the old normal-class UDP manager includes destructor98, scalar
wrapper30 and constructor145 with its complete three-state cleanup EH; all
remain exact. This is focused validation, not a cold replay of all units.

## Accounting

Three normal physical owner functions add294 authored exact bytes:
1561 functions /444796 bytes. Source1758, authored1778, mapped1785,
excluded1658, review591, units752. The three30-byte wrappers remain in their
existing compiler-origin rule. No helper inflation.


## Selected texture context update

The already accepted texture normal destructor404FD0/98 and scalar405040/30
now select exact-first-texture-service-lifetime, which freshly proves the real
global aggregate and new private constructor404F00/193. They are not recounted.
The old resource-manager unit retains the wave/sound pairs. See
TEXTURE_SERVICE_LIFETIME_EXACT_2026_10_31.md for the complete startup/exit gate.
