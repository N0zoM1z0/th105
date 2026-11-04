# Timeline loader uses the real script owner

The exact timeline loader `0x004540F0` now calls `CScript::load` and
`CScript::next_command` on its actual `script_18` member instead of a separate
partial receiver view. The emitted call symbols match the definitions in
`ScriptFileLoading.cpp` and `ScriptNextCommand.cpp`; this is source-level
identity, not a claim that the complete game links. The next-command provider
itself remains nonexact and its private dereference ABI remains unresolved.

The main loader remains 1,584/1,584 exact. Both the configured build and an
independent cold build also reproduce all 1,676 bytes of its callable plus
alignment and switch-table payload, SHA-256
`b6bb1b77c0258c4c24bf3ff0eeec71ea11409e7f1af88d4d91e0dc13fe1af973`.
No function or authored byte is added again. The associated standard-library
helper remains separately compiler-excluded.

Both affected generated-origin rules (8 and 2 helpers) and the distinct
unsigned-deque pop-back proof were fully revalidated. The latter's source pin
was updated to the new CRLF-stable source after reviewing the exact payload;
the native body, caller, named roles and uniqueness checks were not weakened.
Target-independent line-ending pin checks pass. Receipts are under
`build/frontier-timeline-real-script-20261104/`.
All 1,030 target-independent CI tests, including source-pin and generated
progress checks, passed.
