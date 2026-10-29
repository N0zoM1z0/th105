# Scenario window-text replacement, JP1.06a

456760 is canonical exact563/563, SHA256:
3260da30146bd2e7c80b112769dd6ffa449fb71b322e915fd249d20dbb6b8819.
The complete body through456990 RET4 is selected, not a matched prefix.

## Recovered policy and ownership

The method belongs to CScenarioData's text-window path. It receives a pointer
to the actual std::string, uses the nonpolymorphic font at068, manipulates the
9C-entry list350, and reads the current signed fade step from520.

It first pops old entries until at most one remains. Pop-front releases each
entry's title resource, naturally invokes sprite/color destruction and frees
the node. It then appends a newly constructed entry with alpha0, delta5 and
resource handle0. A real sprite member constructs its four-byte texture value
and publishes its vtable through ordinary C++. The local entry is destroyed
after the checked-list push.

The last entry receives a1024x128 text texture rendered from text->c_str()
using font068. Its sprite's actual slot10 configures handle, x/y0, size640x80,
origin-32 and option0. Slot04 sets transparent-white color00FFFFFF. Finally,
the signed low byte of field520 replaces the entry's delta099.

The new typed9C entry has only two semantic bytes after its94-byte sprite:
unsigned alpha098 and signed delta099. The final two bytes are alignment
padding, not additional copied fields. Native node creation455BE0 copies just
those two bytes after the real sprite copy constructor455160. The emitted
100-byte node helper matches completely; no hand-written node manipulation or
copying of target instructions is used. The source-emitted85-byte entry
destructor also matches the independently accepted434C60 body. Neither
provider is counted again as authored exact credit.

## First comparison and bounded correction

The first complete source immediately compiled to563 bytes. Full canonical
comparison found18 unequal positions around local entry initialization.
Native initializes alpha/delta before the resource-handle store. Reordering
those genuine constructor-body stores to their observed order closes all563
bytes. No artificial local, register annotation, forced inlining, padding,
manual vptr or ABI override was introduced.

The existing DesignTextureHandle supplies actual four-byte initializing value
semantics inside the polymorphic color base. Sprite copy is a nonthrowing
out-of-line member provider, consistent with its scalar physical copy and the
native node helper's absence of EH. The524-byte containing view is pointer-only;
unaccessed fields stay opaque, and it is never constructed or allocated.

## Reproduction and limits

scripts/repo-python scripts/build.py --unit exact-first-scenario-text-rebuild --compare --json

Source:src/battle/ScenarioTextRebuild.cpp.
Receipt:build/frontier-scenario-text-rebuild-20261029/formal.json.
Provider checks:providers.json in the same scope. Three new data mappings bind
the actual IColor/CSprite vtables and complete native EH handler. Shared headers
and accepted caller sources are unchanged; no cold-corpus build is needed.
Default CI validates the final ledgers, source selection and tooling.

IDA preflight for this scope was unavailable because its MCP Python runtime
was missing. Analysis used only the hash-attested canonical PE and ordinary
fresh VC8 compilation; no unverified IDA session or database write was used.
