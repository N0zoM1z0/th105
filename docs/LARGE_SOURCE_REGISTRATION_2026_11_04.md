# Three complete nonexact source registrations

Three existing target-backed complete source hypotheses are now tracked as
source-present. Their fresh pinned-VC8 builds and whole-target audit results
remain nonexact, so none contributes a matching function or byte:

- Filtered spell CSV parser `0x00433B30`: 1,987/1,987 bytes, two unequal
  deque-check operand bytes. Exact spell wrappers and the 1,646-byte resource
  parser were replayed.
- Fighter PAT/palette loader `0x00461B70`: 3,885/3,885 bytes, four unequal
  deque-check operand bytes. The exact 333-byte fighter initializer and its two
  same-unit peers were replayed.
- Scene resource bootstrap `0x0043E2E0`: 3,722/3,722 bytes, eleven unequal
  stack-displacement bytes. The exact 162-byte scene initializer and its three
  same-unit peers were replayed.

All target audits returned the expected candidate-nonexact status, not exact. Raw
CFG, owner, source and prior negative-control evidence remain in the respective
existing detailed documents. This checkpoint does not establish full exception-path
equivalence, application linkage, or runtime gameplay. The three scoped
authored-origin checks and all 1,024 target-independent CI tests passed, including
generated-progress and whitespace checks.
