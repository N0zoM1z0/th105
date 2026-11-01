# Texture service aggregate and private manager construction

The October31 investigation completes its accepted replay on November1 UTC.
Texture manager constructor404F00 is canonical exact193/193, SHA-256
b13f70db5b62e14188345346b748e177e1221624fef30565be2e3b7536baf50b.
All120 cleanup/EH bytes also agree: handler6BE461/27, three11-byte funclets,
FuncInfo6E4C94/36 and the24-byte unwind map. Extra regions earn no authored credit.

## Actual composition and compiler behavior

The native resource object at702798 has a0x64-byte CHandleManager texture-pointer
member followed by eight cached handle cells at offsets0x64..0x80. The first size
and class identity are fixed by the existing typed manager lifetime and RTTI;
the cache is independently used by the texture binder and initialized by the
real CRT initializer. The source expresses this0x84-byte (132-byte) aggregate directly,
with the existing genuine manager template and an ordinary eight-element zero
initialization loop. Original nominal source/class spelling remains unknown.

The compiler naturally specializes the member constructor to the fixed global
instance. Its source signature remains a normal C++ default constructor, with
no custom register ABI, source absolute-address stores or synthetic caller.
The aggregate constructor itself is inlined into the genuine CRT initializer.
The source does not add or manufacture a separate authored wrapper entry.

## Separate strict aggregate startup contract

The pre-existing generic global contract intentionally permits only a natural
same-class constructor/destructor pair with a17-byte initializer and5-byte exit
tail. It is not widened or bypassed for this different shape.

The new linked_texture_lifecycle module accepts only this concrete texture
aggregate, three fixed entry contracts and two actual RTTI-owned member vtables.
Before admitting its private constructor, it requires:

- The sole native COFF0x84-byte BSS object, compiler alignment8, matching initially
  zero writable source/target storage and no mapped storage aliases.
- A scoped fixed field ledger for the manager and all eight cache cells. It
  cannot be widened or reused as an absolute external provider.
- Complete59-byte compiler initializer6BE730: call404F00, all eight cache-zero
  stores, the actual callback address, positively identified _atexit68AF1E,
  stack cleanup and RET. Every source HIGHLOW field and every target byte is
  checked, not just the first call or a prefix.
- The complete10-byte callback6BEDE0 loads the actual global into ECX and tails
  to the existing normal destructor404FD0. The receiver instruction is required.
- A unique source CRT C++ initializer entry between the real CRT sentinels,
  no additional nonzero C++ initializers, and exact native table slot6C0364.
- Fresh canonical equality of the existing normal destructor98 and scalar
  wrapper30 in the same image, including their calls and vtables.
- The constructor's complete193 bytes and all120 EH bytes under the unchanged
  canonical code, relocation, ownership and cleanup comparators.

The actual source, original unsigned-list/vector COFF providers, static CRT,
entry identities, EH metadata and vtables are mandatory. There is no general
private-global escape, optional receiver check, arbitrary initialization tail,
new blanket code-address alias or acceptance of a merely source-present parent.
The new module participates in build provenance and input hashing.

## Negative and regression evidence

Twelve new exact-acceptance tests reject altered source/runtime/provider scope,
missing/changed entry or EH contracts, alternative private/export paths,
incorrect RTTI/scalar identity, widened/missing field cells, every changed
initializer/callback byte, partial extents and missing/duplicate/extra CRT
initializers. An actual compiler negative changes only the cache loop bound
from8 to7. Fresh comparison rejects its incomplete source initializer; the
selected source is then restored and all three entries replay exact again.
No target bytes are edited.

The two existing wave/sound manager destructors and scalar wrappers freshly
pass in the old resource-manager unit. All four wave-service lifetime/member
constructor roots and both package-store globals also freshly pass, preserving
the unchanged generic global/cleanup paths. Default CI passes235 tests.

The already-counted texture destructor98 and compiler scalar30 move from
exact-first-resource-manager-lifetime to exact-first-texture-service-lifetime
without duplicate manifest addresses or recount. Existing source bodies are
unchanged; only their selected context changes.

Receipts under build/frontier-texture-global-20261031 include restored-final.json,
missing-cache-negative.json, the three existing-family replay JSONs and ci.log.
The earlier independent audit.json was explicitly diagnostic-only until the
public contract and negative tests were complete.

Only193 authored bytes/one function are added: exact1582/449309, source1781,
authored1801, mapped1808, excluded1783/review443, units764.
