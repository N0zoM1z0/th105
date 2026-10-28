# Battle effect bootstrap6654A0 /6654C0

Canonical exact21/10 in exact-first-battle-effect-bootstrap; receipt
build/frontier-6654a0-20261028/formal-build.json.
Initialization is called by scene resource bootstrap at43F0CB, and shutdown
by scene teardown at43D6E8. They are application resource policies, not compiler
static-initialization or atexit thunks.

The first passes the canonical embedded program6C69C0, length0xAC8, to global
BattleBaseEffect owner6FD394 through initialize417FF0. The second forwards to
its exact shutdown418040, which removes the reset listener and releases the
owned effect. Existing source defines the underlying class lifetime; this
new TU uses declaration-only normal member boundaries and ordinary cdecl entry.
The caller ignores the initialization result, so the wrapper is void.

The program is referenced as an external symbol; its data is neither copied
into source nor counted as authored function bytes. Canonical owner/program
prefixes attest relocations, with full code comparison unmasked. Boundary
receipt includes the explicit shutdown tail. No shared source/header changes.

Hashes:
- cd1a00756e8df0b437aeb50aad95cb3f5f5739df4f44d68c34b8edeea32efc00
- 728012bfe8b049333ef43f197075aa1fec795e6ea6acf3cbba753870b3a23439
