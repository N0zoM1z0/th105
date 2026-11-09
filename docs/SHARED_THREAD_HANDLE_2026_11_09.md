# Shared native thread handle

The platform, audio scheduler and battle owner now include one declaration of
`BattleThreadHandle` from `src/platform/BattleThreadHandle.hpp`. The former
three definitions differed in access, field names and method inventory despite
using the same native methods and eight-byte storage. The network shutdown
view also uses this declaration and calls the real wait implementation instead
of an undefined `BattleThreadHandleShutdownView` method.

## Native evidence

The pinned Japanese v1.06a executable supplies the complete six-method family:
constructor `0x40CF10` (9 bytes), destructor `0x4145F0` (5), start `0x414600`
(49), wait `0x414640` (73), priority `0x414690` (17), and running query
`0x4146B0` (36). The constructor initializes only the handle at offset zero.
Start passes offset four to CreateThread as the thread-id output. The other
methods read the handle at zero; the destructor tail-calls wait. The shared
source preserves this nonvirtual layout and does not initialize the id early.

Actual owners establish where these same methods operate:

- Battle construction `0x4678F0` initializes and starts the two members at
  offsets `0x10` and `0x18`; destruction `0x466AF0` waits and destroys them.
- Audio finalization `0x419000` passes `0x703880`, scheduler base `0x703864`
  plus `0x1C`, to the same wait method.
- BGM initialization `0x403460` uses the handle/id pairs at offsets zero and
  eight and calls the same wait provider before its inlined starts.
- Network shutdown `0x412FD0` calls wait on offsets `0x13C`, `0x6C`, `0x5C`
  and `0x64`, in that order.

These call edges and field accesses support a common utility declaration;
they do not recover its original class name or access specifiers. Existing
BGM start/priority definitions keep their established visible-body compilation
context. A small compile-only translation unit now includes both audio and
battle headers together and checks the thread, scheduler and battle-owner
sizes as 8, `0x3C` and `0x118`.

## Complete affected comparison

The actual quoted-include closure contains 16 configured units and 40 roots.
Fresh before/after builds preserve all results: 34 exact, six previously
nonexact. The six remaining gaps are battle background update `0x466F40`,
UDP shutdown preparation `0x4130D0`, listener removal/wait `0x419400` and
`0x4194D0`, audio finalization `0x419000`, and scheduler thread `0x419100`.
No exact ledger or authored count changed.

All 711 non-debug COFF sections retain their layouts, stored bytes and
relocation roles after the single network wait-symbol substitution. There
are no compiler-local label substitutions. Both linked images retain all
eight section contents in total, apart from their export-directory build
timestamps. This also checks emitted support and exception data beyond the
individual root comparisons.

Moving the declaration changes the actual source closure of the endpoint
allocator, peer allocator and unsigned-list-growth origin proofs. Each now
pins the new header and changed implementation; all three full proofs pass
with their existing target extents, relocation, exception and ownership
checks. The initialization context builder now includes the shared production
header instead of extracting a class definition from the implementation.
Its 14 positive/negative tests pass, as do the 11 endpoint tests. The new
header uses LF checkout bytes consistently with its raw source pin.

Private evidence is under `.analysis/frontier-thread-handle-shared-20261109/`
and `build/frontier-thread-handle-shared-20261109/`: before/after unit reports,
`native-owners.json`, `sections.json`, the three origin results, context tests
and the shared-header compilation. Tracking validation, scoped CI and diff
checks pass. The pre-existing input migration and Alice audit edits remain
separate and unchanged.
