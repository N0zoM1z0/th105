# Input-endpoint delay queue ownership

The 79-byte method at `0x44EA80` belongs to the composed input endpoint,
not the Client primary object. Both Client frame pacing and Server endpoint
maintenance pass the same owner +0xF8 and owner +0x174 receivers. Their 0x7C
stride agrees with the existing `NetworkInputEndpoint7C` layout.

## Native evidence

All observations use the hash-attested Japanese 1.06a PE
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
A scan of executable-section direct CALL operands, followed by instruction
boundary checks in each owning function, finds four calls:

- Client pacing `0x44EAD0`: `0x44EC6A` and `0x44EC75`.
- Server maintenance `0x44F8E0`: `0x44F906` and `0x44F911`.

The callee tests the deque count at endpoint +0x78, calls the checked front
helper for the deque at +0x68, copies its two-byte value into +0x60, then advances
head/count with block-capacity wrap and the original empty-queue resets.
The destination is the embedded `CInputManagerEx::injected_mask`, not a Client
primary field. The complete callee has 29 reachable instructions; its complete
Client pacing caller has 169. None of the three network primary tables
listed below contains this method.

## Shared implementation

`NetworkInputDelayQueue.hpp` holds the existing method's 0x7C field view and
asserts mask +0x60, deque +0x68 and total extent. The implementation remains in
`NetworkClientPrimaryProtocol.cpp`; its former Client-owner name and unused
primary declaration are removed. Client pacing's call-only alias and Server
maintenance's separate endpoint declaration now use this same implemented
view. Server's previous +0x78 `remaining` member is expressed as the real
queue count.

The canonical descriptive name is now
`NetworkInputEndpoint_advance_delay_queue`. Only the name/signature/ownership
notes changed in its existing ledger rows; its accepted address and 79-byte
extent are unchanged. The CInputManager classes and actual endpoint lifetime
header were not edited.

## Focused comparisons

Pinned VC8 builds preserve all eight accepted roots across the affected units:

- Client primary protocol: `0x44E730/30`, `0x44E750/100`, `0x44E9E0/79`,
  `0x44EA80/79`.
- Server continuation: `0x43CBD0/57`, `0x44F8E0/78`, `0x44FF90/69`,
  `0x44F390/324`.
- Client pacing remains 573 bytes and nonexact at +459, with the identical
  compared hash. The previously documented operand-order stop is unchanged.

All 318 original non-debug sections retain bytes and relocation roles after
three call-symbol renames. The shared checked-deque header adds 44 ordinary
four-byte STL constant sections to the Server object; it adds no code section
or linker-directive change. No origin proof consumes the changed translation
units, and no source pins were changed.

## Full network class boundary

The independent primary-table inventory establishes 17 slots for each of
`CNetworkBase` (`0x6C1684`), `CNetworkServer` (`0x6C16EC`) and `CNetworkClient`
(`0x6C1754`), with matching owner TypeDescriptor names and zero-offset COLs.
The Base table contains its destructor/reset followed by fifteen references
to the archive-proved VC8 `__purecall` at `0x689934`. A one-slot primary view
therefore cannot serve as the complete original abstract base interface.

A coherent primary/secondary implementation merge must also join the real
member lifetimes and callback definitions, rather than introducing another
nominal inheritance layer. That closure includes the still-pending input
identity work and its existing source-proof dependencies. This checkpoint
keeps that larger change separate and fixes the independently established
endpoint owner instead. The examined neighboring callback roots were already
exact; this work adds no new authored exact credit.
