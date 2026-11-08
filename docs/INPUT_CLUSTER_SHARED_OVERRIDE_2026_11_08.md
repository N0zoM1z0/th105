# Share the combined-input override

`CInputManagerCluster` now has one shared definition and implements the base
update override. Its former `merge_menu_input_sources` definition was a
nonvirtual method, while the independent selection-menu definitions declared
an override with no matching implementation. The original table proves these
are the same function, not two separate operations.

## Original contract

The complete callable table at `0x6C0874` has two entries: scalar deletion at
`0x420C30` and the 1003-byte input merge at `0x40A0F0`. The following pointer
is the next class's COL, not a third method. The cluster COL at `0x6D74B8`
points to the global `CInputManagerCluster` descriptor at `0x6E62E8` and the
two-class hierarchy at `0x6D74CC`. Its base descriptor is the same physical
`CInputManager` record at `0x6DCA4C` used by the extended input class.

Fresh comparison of the independent global input-base lifetime also validates
its complete RTTI graph, normal7 and scalar31 bodies. Thus the original global
class identities and inheritance are established; the shared namespace-based
source identity is still a separate migration.

The actual selection constructor emits the cluster's normal19 and scalar40
bodies. Both now have complete local byte equality and closed control flow at
`0x420C10` and `0x420C30`. The weak deleting symbol resolves to that scalar
body. Both complete callable slots, their relocation roles and the entire
1003-byte update body also compare equal.

## Shared source

`InputCluster.hpp` declares `update_player_input_counters_from_raw` as the
virtual override. `InputMerge.cpp` defines it, and the frame updater calls it.
`SelectConstructor.hpp` and `SelectLifetime.hpp` include this shared header
instead of separately defining both input classes. Four selection source files
use the existing typed `counters` array and `sources` deque rather than their
former duplicate-layout field names. Field widths, offsets and lifetime
operations are unchanged.

The complete include closure for this change is 20 units. All 26 before/after
comparison results are unchanged: 17 equal results, including 12 distinct
accepted roots, and nine existing nonexact results. All non-debug COFF section
bytes, symbols and relocation roles remain equal after the method rename.
SafeSEH membership is unchanged; two constructor profiles reorder entries.
The linked input-update witness also preserves code, data, relocation and
read-only content apart from its PE export timestamp.

Four affected origin proofs pass: design-base lifetime, sprite default
construction, input-byte allocation and the generated checked-deque accessor.
Only the changed existing source pins were renewed. No exact ledger or
compiler-origin classification changed.

Evidence is in `build/frontier-input-cluster-owner-20261108/`, including
`sections.json`, `interface.json`, the preserved objects and four origin
results. Private drivers are in `.analysis/frontier-input-cluster-owner-20261108/`.
This uses the unchanged pinned Japanese 1.06a target and existing VC8 profiles.

## Next identity step

The shared types still emit namespaced struct RTTI, whereas the original uses
global classes. A global migration must update the input, cursor and scenario
forward declarations and their decorated parameter types together. The wider
header union reaches 219 units; use actual symbol consumers to narrow that
migration rather than rerunning every indirect include. The conflicting
selection definitions no longer obstruct it.
