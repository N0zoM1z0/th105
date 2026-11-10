# Scenario texture publication follows the loader result

The Stand, foreground and background commands now consume the token through
`TitleResourceManager::load_texture`'s returned pointer. The two list commands
also select their destination entry before calling the loader, preserving the
native destination across that call instead of looking up the list tail afterward.

## Native evidence

All addresses refer to the pinned Japanese 1.06a executable.

- Stand: call `0x459201` returns a pointer; `0x459206` reads `[EAX]`, and
  `0x45920E` stores that value into the selected text entry. The same value
  reaches the sprite texture-options call at `0x459231`.
- Foreground: `0x45960F..0x459623` selects and checks the list tail before
  the loader call at `0x459640`. The returned token is read at `0x459645` and
  stored through the saved node at `0x459647`. Only afterward does the code
  reload the list tail for the sprite operations.
- Background: `0x45988C..0x4598AD` similarly selects the destination before
  the loader call at `0x4598CE`. `0x4598D3..0x4598D5` reads the returned token
  and stores it through that saved node before the later list lookup.

The existing loader source returns its output pointer on both paths, so this
review does not establish a different gameplay result for that provider. It
corrects the interpreter's explicit call/data-flow reconstruction without
inventing a callback, failure guard, null check or resource lifetime.

## Fresh compilation and limits

The three fresh loader sites at object offsets `+0xB0C`, `+0xE4A` and `+0xFF6`
are followed by reads through EAX. For the list commands, the compiler selects
`back()` before the call and retains its destination until the token store.
It then separately looks up the sprite entry, as in the target. These are
instruction-level observations, not partial exact credit.

The complete 6,121-byte interpreter comparison was attempted before and after
the change. Both stop at the same unresolved local `?$basic_string_ctor` REL32
provider; no canonical mismatch offset or byte-equality result is available.
The target audit still closes the full callable, its 23-way table and 6,216-byte
payload. No new source-present or exact ledger entry was made.

Only `exact-first-scenario-command-update` selects this source. No shared type,
provider, compiler profile, relocation mapping or accepted consumer changed.
The focused CI and whitespace checks pass. Evidence is retained under
`build/frontier-scenario-texture-publication-20261110/`: before/after build
reports and objects, fresh object disassembly, the pinned native publication
ranges, and the complete target CFG audit.
