# Derived UDP callback slots and notification contracts

The Client and Server constructor/lifetime views now inherit the shared
six-slot `INetworkUDPEventProc` and declare the native override sets. This
replaces a four-slot constructor interface and a one-slot lifetime interface
that could reproduce vfptr stores without describing the stored tables.
The Server lifetime view also retains the known eight-byte tail, bringing its
modeled extent from 0x6E4 to the factory-proved 0x6EC; Client remains 0x6E4.

## Native ownership and complete slots

The hash-attested Japanese 1.06a target is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Server table `0x6C16CC` has COL `0x6D80A8`, type descriptor `0x6E6904` and
hierarchy `0x6D8050`. Client table `0x6C1734` has COL `0x6D810C`, type
descriptor `0x6E6924` and hierarchy `0x6D80D0`. Both hierarchies contain the
owner, `CNetworkBase` at +0, and `INetworkUDPEventProc` at +0x6DC, with no
virtual bases. Both secondary COLs independently report offset 0x6DC.

| Slot | Callback | Server | Client |
| --- | --- | --- | --- |
| 0 | Acceptance | inherited 0x43AA20 | 0x44E7E0 |
| 1 | Rejection | inherited 0x44E8E0 | 0x44E840 |
| 2 | Primary data | inherited 0x43AA10 | 0x44EE80 |
| 3 | Peer data | 0x44FB40 | 0x44EA30 |
| 4 | Route payload | 0x44F600 | 0x44E880 |
| 5 | Peer removal | inherited 0x44E8E0 | inherited 0x44E8E0 |

Thus Server overrides slots 3/4; Client overrides slots 0 through 4. There is
no secondary virtual destructor and no new slot appended by these overrides.
All seven distinct override bodies were already accepted authored functions,
so discovering their complete table membership adds no exact credit.

A bounded pinned-VC8 multiple-inheritance probe independently checks the
receiver convention. Defining `on_rejected(unsigned)` on a class with primary
base size 0x6DC and the real secondary interface naturally emits the original
13-byte store to `[ecx-0x330]`, with no adjustment thunk. ECX is the secondary
receiver for this override. No hand-written adjustment or forced ABI is needed.

## Remove unsupported return promises

The Client notification implementations had returned `this`, the stored option
value, or the incoming packet pointer. None is needed by the interface.
The native calls at `0x415B61`, `0x415BE4` and `0x41DD0E` do not read EAX before
the following call clobbers it. Their current shared interface uses void.

Removing those return expressions and using void reproduces the complete
91-byte acceptance, 13-byte rejection and 68-byte peer-data bodies unchanged.
The apparent EAX results are ordinary register leftovers, not evidence that
the source should promise a result. The dispatch view's matching declarations
now use void too. Route callbacks still return their actual status codes.

## Affected validation

Four real source units were rebuilt before and after the change:

- `gpt-web-network-derived-constructor`: 108/108/113/113.
- `gpt-web-network-derived-lifetime`: 109/30/110/30.
- `gpt-web-network-client-secondary-runtime`: 91/13/68.
- `gpt-web-network-client-secondary-dispatch-runtime`: 582.

All twelve complete function comparisons retain their hashes: ten accepted
authored roots and two compiler-generated scalar wrappers. The existing
folded lifetime EH35/metadata44 and factory EH38/metadata44 also replay exactly.
The Client dispatcher additionally matches its complete 624-byte section:
582 callable bytes, two alignment bytes and the ten-entry switch table.
All callable instructions are reachable from the entry/switch destinations.
Its three-state EH code70 at `0x6BA5A0`, metadata60 at `0x6DFFA0`, and complete
INPUT8, ACK_INFO19 and REPLAY8 cleanup bodies match the original.

For both constructor and lifetime objects, all six secondary entries and the
COL pointer are replayed for both derived owners, with exact whole-table
bytes. Their COLs and complete three-class inheritance geometry also match.
The shared interface's own full RTTI graph, original type name and six-slot
table compare equal. The remaining owner and primary-base declarations are
still named partial views, so their TypeDescriptor names and incomplete
primary vtables are not claimed as whole-class RTTI equality.

The whole-object check finds only the five expanded interface tables and two
replacement interface type descriptors changing. All code and EH sections
retain bytes and relocation roles; SafeSEH handler membership is unchanged.
No origin configuration consumes the four changed source files, and no origin
pins or exact ledgers were modified.

## Evidence and next boundary

Reports are in `build/frontier-derived-udp-callbacks-20261109/`: focused builds,
`tables.json`, `sections.json`, `lifetime-eh.json`, `client-dispatch-eh.json` and
the bounded receiver/void probes. Private replay scripts and the inherited
worktree snapshot are in `.analysis/frontier-derived-udp-callbacks-20261109/`.

The secondary interface declaration is now complete. Its concrete callback
implementations still live in separate owner views; joining them to the
constructor/lifetime classes also requires unifying the real primary base
and its full virtual interface. That is the next ownership boundary, rather
than adding another nominal class layer or treating these partial declarations
as a finished application link.
