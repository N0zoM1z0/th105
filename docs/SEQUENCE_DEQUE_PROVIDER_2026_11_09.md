# Fighter sequence insertion is a deque provider

`0x45DBA0` is the 114-byte VC8 `std::deque<FighterSequenceSlot>::push_back`,
not a separate authored enqueue algorithm. Instantiating the standard member
with the existing 0x98-byte record reproduces the complete original function.
The old hand-written implementation happened to duplicate that provider and
was incorrectly counted as authored. This checkpoint removes one function and
114 bytes from authored exact credit.

`SequenceEnqueue.cpp` now instantiates the real standard member instead of
reimplementing growth, allocation, wraparound and placement copy construction.
The preparation method calls that same member through its already established
deque view. Neither the shared record, the sprite layout, nor a compiler flag
changes.

## Original container and complete provider

The sequence record is the existing signed short ID, unsigned short value and
actual `CSprite` at +4. Native preparation constructs that 0x98-byte record on
the stack, passes its address, forms the deque receiver at Fighter +0x55C, and
calls `0x45DBA0` at `0x45DD6A`. It then reads the resulting live count at +0x56C.
The queue's indexing, copy and grow-map providers were independently recovered
in the earlier sequence work.

All 40 instructions and 114 bytes of the push provider close through RET 4.
There is no extra EH region, switch table or section tail. Its three calls are:

- +0x12: the existing generated grow-map provider at `0x45DA40`;
- +0x34: allocation at `0x689DCB`;
- +0x65: the real implicit `CSprite` copy constructor at `0x455160`.

The existing origin validator rebuilds the public source and checks its 102
non-relocation bytes together with all three call targets. Exactly `0x45DBA0`
matches across the complete 4,027-entry inventory. The rule also pins the
preparation call and the +0x55C receiver displacement. Canonical provider hash:
`b759b6250c6bb162efcd642a238df983041e175848d36e08ddcb8d37e7194d01`.

## Affected source and verification

The explicit provider and the actual preparation TU each emit the same exact
114-byte push member. The provider TU's implicit sprite copy also remains
exact across all 116 bytes.

Both affected SpellRuntime compiler profiles preserve all four authored root
bodies and their owned EH sections after accounting for the corrected call
symbol. Twelve complete sections retain their raw bytes and relocation roles.
The 118-byte readiness check remains exact; advance198, consume346 and
preparation257/native259 retain their previous nonexact hashes.

Preparation's complete 44-byte exception code, 44-byte metadata and eight-byte
record cleanup still compare exactly. Restoring the real push member does not
close its optional-texture load scheduling difference. Those authored methods
receive no new credit.

Public provider: `scripts/repo-python scripts/build.py --unit
cross-v106a-sequence-enqueue --compare --json`.

This is a local source and ownership correction. It does not establish a new
Factory-authoritative accepted claim or resolve the existing freshness failure.
Pending input migration files and their SHA pins are untouched.
