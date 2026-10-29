# CScript destruction with complete CIL cleanup evidence, JP1.06a

405660 is canonical exact95/95, SHA256
1ed5c1a7fe28f8796a191563a9d5b6abcc2bdf7a1f047e570dd1c516b7a90e58.
The newly exact ScenarioData destructor calls it at438B3F. It invokes the
existing game-owned clear_commands policy, then destroys the pending-factory
deque+14 and command map+0. This is the actual34-byte CScript lifecycle, not a
new source wrapper around an unexplained private ABI.

## Genuine source context

The unchanged constructor, destructor and clear_commands definitions are
factored into ScriptLifecycle.cpp. ScriptCommandLifetime.cpp includes that
file and retains its character-command parser. The linked unit compiles this
real lifecycle core with VC8 /GL and LTCG, static CRT, and a preserved public
clear_commands boundary. The compiler itself chooses ESI for deque _Tidy and
EAX for map _Tidy, matching the native destructor call setup. No source-level
custom register convention, helper stub or fake global object is introduced.

The source clear_commands provider is still not exact: the selected CIL body
is309/native170, while its existing COFF comparison remains296/native170.
It gets no new credit. Constructor65 and character parser505 remain canonical
exact in the fresh original-TU replay after factoring the definitions.

## Full exceptional cleanup, not an address waiver

The95-byte normal body was initially only a private diagnostic because the
linked comparator admitted cleanup EH only with a source-owned global-object
witness. This destructor is a normal exported member, not such a global.
The contract now also admits unrenamed exported no-argument C++ lifetimes
with the real static CRT and its independently verified security-cookie
storage. Private entries, renamed exports, ordinary methods, import-runtime
images, missing cookies and incomplete/extra EH fields remain rejected.

The existing strict cleanup checker is unchanged. The actual parent must
install its unique compiler handler. Every handler/FuncInfo/unwind-map/funclet
record and HIGHLOW field is read from the built image and compared to the
canonical target. The formal receipt verifies:
- Handler6BE423:27 bytes, including cookie check and FrameHandler3 tail.
- Funclet6BE410:8 bytes, actual map destructor tail405650.
- Funclet6BE418:11 bytes, actual deque destructor tail413B00.
- FuncInfo6E4C58:36 bytes, two states and native cleanup-only flags.
- Unwind map6E4C48:16 bytes, both native transitions/actions.

The static image's CRT entry and four runtime-only C initializers are also
validated. No application initializer or synthetic object is substituted.
These compiler metadata/helper bytes are evidence only; only95 authored bytes
are added to progress.

## Focused verification

scripts/repo-python scripts/build.py --unit exact-first-script-lifecycle-linked --compare --json
scripts/repo-python scripts/build.py --unit cross-v106a-script-command-lifetime --compare --json
scripts/repo-python scripts/build.py --unit gpt-web-package-archive-store --compare --json

Receipts:build/frontier-script-lifetime-cil-20261029/formal.json,
coff-regression.json and global-regression.json. The old global-lifecycle
contract retains both163/228-byte exact roots after a fresh build. One small
admission-contract test is added; all13 lifecycle tests pass. No broad runtime
matrix or full native corpus replay is introduced.

## Subsequent pending-command order correction

Raw405770 proves that the command's scalar deleting destructor is invoked at
4057E1 before the queue count is reloaded/decremented at4057E3 onward. The
retained clear_commands source had popped first. ScriptLifecycle.cpp now
performs delete command before pending_14.pop_back(), preserving the native
callback-visible lifetime without adding a guard or changing the container.
This is a semantic restoration, not a claim that clear_commands is exact.

Fresh delete-before-pop-linked.json retains destructor95 and all five EH
witnesses unchanged. delete-before-pop-coff.json retains constructor65 and
parser505 exact; clear_commands remains296/native170, now with canonical
candidate3fe7ae6034cd441f1afca5a276db458d24f5cc4df2d77adae6ab634aca98150d.
The linked clear provider remains309/native170. formal.json is refreshed from
the actual latest linked replay, with the earlier receipt retained separately.
