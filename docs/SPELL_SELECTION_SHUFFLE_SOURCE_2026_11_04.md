# Spell selection shuffle: complete local match

As of November 9, `SpellDataOwner::shuffle_selection` at `0x432420` compares
exactly across all 196 bytes under the pinned VC8 SP1 compiler. The change is
small: call the owning `std::deque<short>::push_front` directly instead of the
declaration-only mutation view. Its real definition naturally restores the
saved-value and stack-reservation schedule that previously differed at seven
byte positions. No compiler flags, loop spelling, storage layout, or forced
inlining changed.

## Behavior and complete boundary

The function takes the selection count once and, if nonzero, repeats 100 times:
choose an index with the existing random selector, read the checked iterator,
erase that entry, and prepend its saved short value. The original caller is the
sequence-mode setter at `0x432520`, whose call at `0x432538` remains verified.

The complete root has 69 reachable instructions, six calls, and one RET through
`0x4324E3`. Its section is exactly 196 bytes, with no alignment tail, switch
payload, or owned EH section. All relocations compare against the original
Japanese v1.06a target. Canonical SHA-256:
`540ef3b2fd1fd978957bf2df18d4d2272af85f78ec0ad79cfd09f1b904a8dbe0`.

The public object also emits the real push-front provider at `0x42A4B0`
(122/122) and its grow-map helper at `0x42A350` (344/344). Their complete bodies
and relocations match. The unchanged direct mode setter and its source-unit
sibling remain exact at 33 and 35 bytes.

## Preserve the actual erase boundary

The original root calls the single-element erase wrapper at `0x4323B0`.
A separate natural-VC8 probe reproduces that whole 108-byte provider, including
both invalid-parameter calls and its range-erase call to `0x429690`. The source
retains the existing out-of-line erase declaration with the genuine checked
iterator return/argument contract.

Replacing both mutation calls with visible standard-library definitions is
not the same reconstruction: VC8 inlines the single-element erase wrapper,
adds its check to the root and calls range-erase directly. That complete
candidate is 237 bytes, not 196. The unchanged public profile and the original
out-of-line edge are retained rather than forcing the inliner. This is a useful
counterexample to replacing every facade in one sweep.

## Evidence and status

Run `scripts/repo-python scripts/build.py --unit
exact-first-spell-selection-shuffle --compare --json`.

The local authored ledger gains one function and 196 bytes. The prior separate
authored-origin rule is superseded by the canonical-match baseline; its target
hash and direct-call evidence were rechecked before that transition. Generated
helpers remain excluded. This local result is not a Factory-authoritative
accepted claim; the existing invocation-plan/toolchain freshness issue remains
unresolved and no validator or input SHA pin was changed.
