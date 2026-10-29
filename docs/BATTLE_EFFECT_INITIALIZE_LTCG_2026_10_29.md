# BattleBaseEffect initialize417FF0

Complete71/71 canonical exact in
`exact-first-battle-base-effect-initialize-linked`, SHA-256
`7fe4ec2b8b0277f2254e982992e410aec88638a495f64ddbaea1a4f1979d0887`.
Target is the pinned Japanese1.06a executable. Full28-instruction CFG includes
both RET8 exits and all71 bytes; nine following INT3 bytes are outside it.
Exact BattleObjectManager4678F0 calls at4679A5, and exact effect bootstrap6654A0
calls at6654AF. The first supplies member+40 and embedded effect blob6C2DB8;
the latter initializes the separately established global effect owner.

## Source and compiler context

The initializer body is unchanged: reject an already-owned effect, register
this reset listener, and invoke D3DXCreateEffect with device backend+20,
source pointer/length, null optional arguments and effect output member+4.
The ordinary class declaration moves to BattleBaseEffectLifetime.hpp; its
field/virtual order and nonvirtual destructor are unchanged. Lifetime methods
remain in the old TU. The initializer moves into its own TU and is included
with the real D3DBackendListenerRuntime.cpp and CriticalSectionWrapper.cpp.
This genuine one-CIL context naturally places the backend receiver in EAX.
There is no private calling-convention declaration or instruction transcription.

At this initial checkpoint only417FF0 was accepted. The real414CB0 provider was independently nonexact
(private focused comparison162/native157, first+6); it is not exported or
credited merely because its caller matches. The previous ordinary initializer
71/71 first+17 was a register-context mismatch, not a source-behavior gap.
Original whole-program TU boundaries remain unknown.

## Named external import

Target6898A2 is an excluded six-byte FF25 import thunk through IAT6C02B4,
whose PE import identity is d3dx9_33.dll!D3DXCreateEffect. The source uses the
ordinary stdcall nine-parameter declaration. A pinned VC8 LIB generates a
metadata-only import archive from that public DLL/name declaration. LIB's
stdcall DEF spelling defaults to IMPORT_NAME_NOPREFIX; the generated short
import record's standard name-policy field alone changes to
IMPORT_NAME_UNDECORATE. This keeps the decorated linker name while importing
the actual undecorated DLL name. No executable DLL, target function bytes,
handwritten thunk or replacement implementation is supplied.

linked_named_imports.py checks x86 headers, the sole short import's exact
symbol/DLL/policy, all three import-descriptor member inventories and rejects
executable sections. The final library must equal the generated original
except for that naming field. Definition, original/final archives, librarian
hash and command are recorded in the linked provenance. Comparison rechecks
them, the canonical target import/ledger/origin, and the actual linked PE's
DLL/name, thunk symbol, map archive owner and configured target. Existing
ordinal SDK import validation remains separate and unchanged. Whole callable
comparison and all relocation fields remain unmasked.

The GNU dlltool diagnostic did not produce a valid source PE import directory
with this linker and was rejected. It confers no evidence or credit.

## Reproduction and focused validation

- scripts/repo-python scripts/build.py --unit exact-first-battle-base-effect-initialize-linked --compare --json
- Same focused build for gpt-web-battle-base-effect-lifetime: five accepted
  constructor/destructor/shutdown/reset callbacks retain their exact bodies.
- cross-v106a-network-winsock-send-client exercises the unchanged ordinal SDK
  contract: accepted shared release helper405200 retains167/167. The selected
  send-client roots remain nonexact (561/464, 644/548, 16/18 and395/395),
  independently of this new named-import contract.
- Two small tooling tests reject incorrect names, DLLs, owners, naming policies
  and executable descriptor sections; existing linked tests remain green.
- Lightweight default CI and diff checks run after final edits.

Receipts: build/frontier-effect-listener-context-20261029/formal-build.json,
boundary.json, lifetime-build.json, sdk-import-replay.json and ci.log.
Only71 new exact authored bytes are added. Counts remain incremental; no cold
corpus build is needed for this isolated source/context/import extension.

Later same-day update: [D3D_LISTENER_FIND_LTCG_2026_10_29.md](D3D_LISTENER_FIND_LTCG_2026_10_29.md)
recovers standard find/result lifetime and accepts414CB0 independently157/157.
The initializer remains exact; source selection now records the linked wrapper
so the actual private caller is available to the existing witness contract.
