# Animation virtual interface evidence, 2026-11-08

The missing animation virtual declarations cannot safely be filled by appending
placeholder methods. The target distinguishes abstract base interfaces,
derived overrides and two different roster construction/destruction hierarchies.
The current layout/lifetime declarations reproduce important code and RTTI, but
do not yet reproduce their full virtual interfaces.

## Native tables and current source

The pinned Japanese 1.06a PE provides these complete primary tables:

| Class | Target table | Target slots | Current COFF slots |
| --- | --- | ---: | ---: |
| AnimationObject | 0x6C0914 | 15 | 4 |
| AttackObject | 0x6C2B3C | 17 | 4 |
| CharacterObject | 0x6C400C | 17 | 5 |
| CSelectObject | 0x6C0954 | 16 | 5 |
| InfoEffectObject | 0x6C37EC | 16 | 5 |

For these five classes, the complete source RTTI graphs compare equal after
symbolic pointer relocation: TypeDescriptors, COLs, hierarchy descriptors, base
arrays and all base descriptors, including PMDs and attributes. This validates
their recovered inheritance/layout, not the omitted vtable entries.

AnimationObject has pure-call entries at +0x0C through +0x28, followed by four
render callbacks through +0x38. AttackObject supplies the seven sequence-method
entries at +0x0C through +0x24, keeps update +0x28 pure, and adds a pure callback
at +0x3C and a no-op at +0x40. CharacterObject retains those entries. The target
therefore does not support making either base concrete just to compile a pool.

The effect branch uses a different sequence-method family. CSelectObject uses
update `0x422180`, transform `0x41FAD0` and a no-op at +0x3C. InfoEffectObject
instead overrides those slots with `0x65CB40`, `0x660730` and `0x660780`.
It does not inherit the CSelect update implementation merely because both
constructors currently use the same incomplete shared header.

## Signature evidence has limits

Known callback bodies and callers identify sequence/frame arguments, byte-valued
advance signals, rendering and state-update roles. A residual EAX value alone
is not evidence for an integer return contract.

A bounded control demonstrates this at the two AttackObject action/finalization
wrappers: both the selected `int` declarations and a consistent `void` version
produce the same complete canonical bodies, 26 bytes at `0x45BFE0` and 33 bytes
at `0x45C000`. The control changes only the action-wrapper/finalizer returns in
a private copy of the existing TU/header; all calls are resolved and no bytes
are masked. Thus the current return-bearing view cannot establish the original
base/override signature. No source-wide return-type change is justified by this
comparison alone.

## Roster boundary and next step

The target ReimuObject RTTI includes `CharacterObjectEx<Reimu, ReimuObject>`.
The current allocation TU instead uses a separate `RosterObjectTail` base; its
complete RTTI comparison fails. The destructor TU already models the real
intermediate class and documents a constructor-visibility/codegen boundary.
That existing split must not be hidden by adding concrete virtual declarations
to the allocation view.

The present AttackObject-header closure is 44 configured units and 189 function
entries. A declaration change must first resolve the abstract overrides and
source-provider identities, then check the affected bodies, call sites and
complete emitted RTTI/vtables. This audit changes no shared header or source
ABI. Four representative source units were freshly built: all 24 selected roots
remain exact. The two finalization roots were also freshly replayed.

Private evidence is in `build/frontier-animation-vtable-contract-20261108/`:
`audit.json` retains full native/source tables and whole RTTI records;
`int-return.json` and `void-return.json` retain the return-type control. The
bounded drivers and private source copies are in the corresponding `.analysis/`
directory. The existing checked-list and effect release sources remain unchanged.
