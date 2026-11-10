# Connect menu normal destructor: complete315-byte exact match

Original Japanese TH105 v1.06a executable SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

CMenuConnect normal destructor443C30 is now canonical315/315. Native and source
whole-function SHA-256:
0c109ea165c105dfe9c01a4768c4fa6c5a6f07d4880cc415107d849ce60225d2.
The body ends with RET0 at443D6A. Existing zero-offset CMenuConnect RTTI and its
scalar wrapper444470 independently identify this normal destructor.

## Recovered application cleanup

The source shuts down the existing profile-name list6FD2C8 through43A0A0,
releases texture handles60 and2FC, and invokes design00C's actual virtual cleanup.
Ordinary C++ member destruction then handles the eight guides atC4C, endpoint
string42C, deque3A4, tiles/sprites, embedded number108 and design00C, followed
by the real Menu base setting scene mode22.

The0x118C owner layout comes from the existing complete constructor view.
The lifetime source keeps actual typed members and uses std::string for the
endpoint. It does not invent an extra owning object or constructor result.

## Actual polymorphic lifetimes

The independently exact-backed CNumberLifetime.cpp supplies its real four-byte
IColor interface, embedded tile lifetime and number owner. The two singleton
sprites have ordinary virtual destructors derived from that same interface.
Tile members reuse CNumberTileLifetime. Their storage extents remain94/A4 and
the number remainsCC with its owned value at24 and tile at28.

This makes the compiler emit all observed vtable transitions and number-value
release in the correct order naturally. No hand-written vptr assignment,
assembly, fake temporary, forced inlining, custom register ABI or modified STL
is introduced. Existing broad UI layout headers and their accepted consumers
are not rewritten for this focused destructor.

The GuideOverlay array still invokes its actual out-of-line destructor through
the original VC8 vector-destructor iterator. Neither that callback nor another
helper receives new exact credit from this root.

## Contract and verification scope

Public unit: exact-first-connect-menu-lifetime. Public source:
src/ui/MenuConnectLifetime.cpp.

All native calls and absolute references are replayed, including the actual
profile global, title manager, four vtable identities, GuideOverlay callback,
cookie and the real handler entry6B94DD. The new handler address binding pins
its complete native entry through the terminal jump. This is the established
complete COFF-function contract; no additional exact claim is made for remote
EH metadata outside the315-byte authored body.

No old source file changed; the number and menu lifetimes are included as
existing providers. Only the new unit needs a native replay. CI and whitespace
checks follow ledger promotion.

The ledger gains one authored function and315 bytes:1563 exact /445390 bytes.
Source1760, authored1780, mapped1787, excluded1658, review589, units753.
The scalar-deleting wrapper444470 remains compiler-excluded.
