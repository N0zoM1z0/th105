# Original matcher recursion stopper and tail dispatch

Two additional complete original checked-string matcher bodies are now proved:
6A2830/19 unwind_recursion_stopper(bool), and 6B25B0/5
match_dot_repeat_dispatch(). Only 24 third-party bytes are newly classified.
No authored exact, source-present or unit-count increase is claimed.

Both come from the unchanged original release instances.cpp unit, using the
same verified original headers and pinned probe as the preceding matcher
leaves. The release unit now has 14 complete exact comparisons. The previous
leaf gate's ownership checks are replayed unchanged as a regression.

## Recursion stopper

The complete 19-byte method advances m_backup_state by one four-byte saved
state, clears pstate and returns false with the actual bool stack argument
cleanup. Its full relocation-free bytes and candidate-inventory uniqueness
are checked; it is not classified merely because it returns false.

The actual source unwind table has declared extent 72 bytes: 16 named members
followed by two null slots. Complete symbolic relocation order and the null
slots are checked. The full original unwind dispatcher 6B1AC0/58 canonically
references native table 6D6068 at its sole DIR32 field +34. Independent whole
unwind_alt 6A28B0/46 and unwind_repeater_counter 6A4160/34 establish two more
selected roles; native slot 2 identifies the recursion stopper. No other
method or entire-table canonical credit follows from pointer order alone.

## Dot-repeat dispatcher

The original matcher table's slot 22 identifies the exact checked-string
match_dot_repeat_dispatch specialization. The full five-byte tail JMP names
match_dot_repeat_fast at 6B1930, not an arbitrary address inferred only from
relative displacement. Its complete 397-byte implementation is replayed.

All eight provider REL32 fields have independent named source identities and
already-excluded ownership. The two early direct tail exits at offsets 17/47
both target the original slow-repeat implementation 6AF2D0; closed CFG checks
allow exactly these explicit exits. Other calls retain their checked-iterator,
invalid-parameter and saved-repeat semantics. The dispatcher remains unique
across the complete same-sized candidate inventory after relocation.

## Validation and scope

Eight tests protect the typed pair, exact extents, no masks, source/header
context, actual tail provider and the preceding leaf contracts. All 47 real
byte-corruption controls fail: every new root byte, selected/null table slots,
provider call/tail fields and supporting body boundaries. The narrow origin
rule passes before changing only the two review rows.

Evidence is retained in build/origin-anchors/boost-matcher-stack.json and
build/frontier-matcher-stack-20261101/. Private scripts are under
.analysis/frontier-matcher-stack-20261101/. Generic minimum coverage/byte
thresholds remain unchanged. Universal false-return stubs and previous
nonexact public-search CIL results remain unaccepted.
