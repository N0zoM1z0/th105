# Application initialization with its real inline cleanup

`ApplicationState::ApplicationState` at `0x407CA0` now has a selected,
reproducible exact unit: `exact-first-application-initialization`. The complete
255-byte constructor matches, together with all 139 bytes of its cleanup EH,
the 17-byte initializer and the complete 73-byte generated exit callback.
The existing ordinary C++ source is unchanged. This resolves the selection
limit documented in `APPLICATION_INITIALIZATION_2026_11_09.md`.

## Target and ownership

The target is Japanese TH105 1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Pinned VC8 SP1 `/O2 /GL /GS` and static-CRT LTCG compile the actual singleton
in `ApplicationLifecycle.cpp`. Its native COFF allocation is exactly 184 bytes;
source and target loader storage are zero, aligned and unaliased. The original
object begins at `702820` and ends before the separate byte at `7028D8`.

The constructor initializes startup options, four thread handles, the retired
scene list and critical section before clearing the two scene pointers and
setting the running flag. Its closed body ends at `407D9E`. The four unwind
funclets occupy `6BD7C0..6BD7EB`, followed by handler `6BD7EC` (27 bytes),
FuncInfo `6E3DC8` (36 bytes) and unwind map `6E3DA8` (32 bytes).

The CRT slot at `6C036C` points to initializer `6BE780`, which calls the
constructor and registers `6BEDF0` with `_atexit` at `68AF1E`. The callback
releases the critical section, destroys the list and waits for the four threads
in reverse order. Its final instruction is the tail jump at `6BEE34`, ending
at `6BEE38`. There is no separate application destructor body to select.
The already-public `BattleThreadHandle::wait_for_exit` is retained through the
existing public-member mechanism and is not counted again.

Canonical constructor SHA-256:
`825f5380a7de1c4d91a268816ad59a06b8ebb5c0f1fce55b23279f6a245b910f`.
Canonical callback SHA-256:
`f79e168610935b8843deedfa7e6459bd3f37d7fe5bcfa2643fd7f7cb8733e642`.

## The bounded proof change

`linked_lifecycle.py` now accepts a declared complete generated callback extent
instead of a standalone destructor only when the real source-owned global,
same-class private constructor and complete constructor EH are witnessed.
The generated callback must be unique, unexported, compiler-owned and closed
at its native symbol boundary. Both source and target bodies are decoded;
segment-based EH and callee-pop returns are rejected. Every byte must match
through the ordinary symbol-backed call, import, vtable and data replay.
Every HIGHLOW field must be accounted for, including the terminal tail call.

The full compiler-proved BSS extent supplies byte-member references as well as
word references. Each operand must fit inside that object. This permits the
actual bool stores without modifying the relocation ledger or accepting an
outside or straddling access. Complete native C and C++ initializer tables are
checked: only pinned CRT callbacks and the fully witnessed source initializers
may appear, each exactly once, with all table relocations present.

The old separate-destructor/five-byte-tail route retains its previous checks.
The private-child global-caller route remains limited to that original form.
No target-specific allowlist, EH waiver, synthetic destructor, copied machine
code or weakened comparison was introduced.

## Reproduction and bounded regression

Run:

```
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-application-initialization --compare --json
scripts/repo-python -m unittest discover -s tests -p test_linked_lifecycle.py
scripts/repo-python -m unittest discover -s tests -p test_linked_pe.py
scripts/repo-python -m unittest discover -s tests -p test_linked_global_caller.py
scripts/repo-python -m unittest discover -s tests -p test_linked_texture_lifecycle.py
```

The four focused test files pass 106 tests, including malformed callback
contracts, byte/call mutations, missing/extra/duplicate/straddling relocations,
wrong or absent callee mappings, boundary and storage violations, aliases,
exported callbacks and extra or missing CRT entries. Fresh serial builds of
PackageArchiveStore, D3D backend, wave-service and BGM-service lifecycle units
retain all 11 previously exact roots. The existing unaccepted D3D destructor
at `414770` remains nonexact (source 103, target 169); this change does not
promote it.

Evidence is in `build/frontier-global-inline-cleanup-20261110/`: the formal
unit report is `formal-replay.json`, and the four named lifecycle reports retain
the regression results. These are local canonical comparisons. Factory receipt
acceptance is a separate result and must be checked for the current inputs.
Only the constructor adds authored exact coverage; generated lifetime support
does not add authored functions. The pending input-source pins and all earlier
uncommitted input/scenario edits remain unchanged.
