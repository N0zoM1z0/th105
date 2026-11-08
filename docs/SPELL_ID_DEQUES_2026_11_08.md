# Spell ID queues

`SpellDataOwner` keeps the loaded spell IDs in a short deque at `+0x20` and
the current selection in another at `+0x34`. Side-payload setup copies into
both; sequence-mode setup copies loaded IDs to the selection and may shuffle
it. `0x432310` returns the front ID and removes it, or returns -1 when empty.
The filtered CSV loader reads the loaded IDs to select records.

These receiver fields and the filter argument now use `std::deque<short>`
instead of a five-word layout facade. The selector is expressed naturally as
`empty`, `front`, and `pop_front`; its full 78-byte target comparison remains
exact. The two assignment functions, load selector, CSV wrappers, character
constructor, lookup, and directly affected exact resource functions also
remained exact. The shuffle, filtered parser, fighter reset, and sequence
preparation retain their earlier nonexact candidate hashes.

This unifies the receiver's accessed storage, not the entire owning lifetime:
the Character constructor still uses its separately represented resource
owner, whose deque construction and destruction need their own reconciliation.
Scope is Japanese TH10.5 1.06a with the pinned VC8 profile.

The Character constructor's separately represented spell resource owner now
constructs the same two native short deques rather than initializing two raw
headers. Its complete `0x462AB0` body still compares exactly. The destructor
already represents those two members as native deques, but the constructor and
destructor owner types and their cleanup/EH linkage remain separate views.
