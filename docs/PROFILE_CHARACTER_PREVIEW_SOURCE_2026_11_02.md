# Profile character preview source publication

The previously private preview recovery is now ordinary source in
ProfileCharacterSelectPreview.cpp, implementing the shared owner's existing
refresh_character_preview method. No local owner or manual vtable view is used.
The new exact-first-profile-character-preview unit compares the complete body.

## Native ownership

Whole178-byte native4484F0 has55 reachable instructions, one RET0, four direct
helper calls and three indirect calls. Exact constructor4487E0/571 calls it at
4489FE; exact update4485B0/372 calls it at4486EB. Both source parents freshly
replay unchanged. Its game policy releases the prior texture, clears handle4,
skips character -1, formats the pooled data/stand/%s.bmp path, loads without
width/height outputs and, after a nonzero result, configures sprite8 to512x480
and colorFF808080. This application policy and its exact owner edges establish
authored ownership, not a standard-library template or compiler lifetime.

Native SHA256:
1afe0ad43b693c126df82a1725c72af49dd16db7f1a08ec8be9695bdf712a4a9.
Source SHA256:
f2ab3f95d836d320881274f4cf976331e44fee62714ee38a7bcd864043b6dab2.

Both are178 bytes, but12 byte positions differ starting at+37. The compiler
loads/tests the character before the independent clear-store; native clears
first. The established closed scheduling lane is not reopened. No volatile
field, fake dependency, register constraint, padding or copied implementation
is introduced, and no exact bytes are added.

## Bounded observations

The audit compares complete native/source CFGs and runs six isolated fixtures:
absent selection, load failure and load success, including zero prior handles
and a high-only nonzero returned handle. It checks actual virtual slot5 texture
and slot1 color arguments, call ordering, full32-bit handle writes, no other
owner writes, RET0, saved nonvolatile registers and the GS cookie boundary.
Helpers deliberately clobber volatile registers and flags. A wrong clear-field
control is rejected through guarded callbacks rather than a swallowed callback
exception. Four lightweight audit-contract tests are included in default CI.

The fixtures model helper returns, including a synthetic character-name string.
They do not execute the real name lookup, formatting API, resource loading,
sprite methods or OS, and establish neither full gameplay/concurrency behavior
nor universal equivalence. The native character-name helper is not assumed to
be a trivial pointer table. Complete differing bytes still fail exactness.

## Accounting and reproduction

A scoped rule pins the whole native hash and both exact caller edges. Only this
one review row moves to authored/source-present. Source1637, authored1656,
mapped1826, review297 and units813; excluded2074 and exact1427/443604 bytes remain
unchanged. No generic origin gate or whole-byte comparison is relaxed.

    scripts/repo-python scripts/build.py --unit exact-first-profile-character-preview --compare --json
    scripts/repo-python scripts/audit-profile-character-preview.py

The comparison intentionally reports mismatch; the diagnostic audit succeeds
only when all bounded checks pass. Receipts are under
build/frontier-profile-character-preview-20261102/, with the scoped origin
validation and private source publication controls in its .analysis counterpart.
Default CI and both diff checks gate the local checkpoint.
