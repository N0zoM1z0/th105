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
headers. Its complete `0x462AB0` body still compares exactly. The destructor also represents those two members as native deques.

A direct `deque::erase` and `push_front` spelling for the shuffle was also
tried after the native queue migration. VC8 emitted 237 bytes against the
196-byte target, differing from +18; the existing out-of-line mutation view
remains selected. This does not change the shuffle's nonexact status.

Character construction and destruction now share `CharacterSpellResources`,
including the real resource core, both deques and selected-value array. The
nullable side-payload initializer is a member of this owner, eliminating a
receiver cast. The complete Character constructor, the 101-byte spell-resource
destructor and both side-input methods remain exact; the destructor's 117 bytes
of generated EH code and data also match. The enclosing Character destructor
retains its earlier nonexact hash. The general `SpellDataOwner` receiver remains
a separate view used by other callers.
