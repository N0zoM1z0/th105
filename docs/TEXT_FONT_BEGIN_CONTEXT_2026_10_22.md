# Font begin: actual CIL context and remaining publication window

Begin4119A0 now selects the real owner/render CIL body. It naturally reproduces
the target64-byte frame, full EDI save scope and83-instruction boundary. It
remains nonexact291 bytes/+59: ten bytes reorder font-handle publication,
HWND reading and the outgoing argument store. Every other byte agrees.
No exact count changes, source-body edits or compiler-option changes follow.

All target observations use original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA again rejects its unrelated image. Target facts use the attested PE;
source facts use actual native/linked compiler output.

## Selection and full-body evidence

The genuine `TextFontLinked.cpp` includes owner and render definitions. The
actual unexported static begin is reached once from the exported renderer;
target call412706 and the complete source/target caller CFG establish that
path. The existing `private_static_leaf` contract attests reviewed included
source, the unique static map entry and lack of aliases/exports before the
unchanged full byte/CFG/relocation comparison runs.

Ordinary native begin is291 bytes/84 instructions,728a7bf3, nonexact+7. It
reserves56 bytes and conditionally saves EDI. Selected CIL is291/83, with the
target64-byte frame, unconditional EDI scope and fall-through loop alignment.
This selection follows actual frame/ABI and provider context, not a partial
exact claim. The native alternative remains emitted in its unchanged COFF.

| Body | Complete canonical SHA256 |
| --- | --- |
| Target291 | `1c9a673b94a0d9a20e34859f3dc3ef0841720700f1a13cb1e318b3314358cf00` |
| Selected CIL291 | `f9651374cfe6f91372993ca2c753dcf40a74599968de96411268c2710376168a` |

Only4119DB..4119E5, exclusive end, differs:

| Target | Selected CIL |
| --- | --- |
| MOV [ESI+4],EAX | MOV ECX,[702A1C] |
| MOV ECX,[702A1C] | PUSH ECX |
| PUSH ECX | MOV [ESI+4],EAX |

The next instruction is the real GetDC call in both bodies. The first
publication occurs after CreateFontA has actually returned on a normal path;
the isolated proof below does not execute or invent that return.

## Conditional endpoint proof and native checks

`scripts/prove-text-font-begin-window.py` first repeats full linked build
provenance, actual caller-path and canonical comparison checks. It rejects
any difference outside the ten-byte window. It then symbolically executes
the three actual MOV/PUSH instructions over arbitrary32-bit entry registers
and byte-addressed data memory, with immutable instructions and valid accesses.

An endpoint mismatch is UNSAT when the four font-handle bytes at ESI+4 are
disjoint from both the HWND cell702A1C and the outgoing stack word at ESP-4.
All eight final general registers, final data memory and pending HWND argument
agree; MOV/PUSH leave arithmetic flags unchanged. The proof needs neither
alignment restrictions nor disjointness between HWND and the outgoing word.

Ordered writes remain different: target writes font then argument; CIL writes
argument then font. Intermediate/read traces, faults and asynchronous
observers are outside this endpoint theorem. It is not canonical acceptance.

Two overlap controls are SAT with new-font11111111 and old-HWND22222222:

| Isolated overlap | Target pending HWND | CIL pending HWND |
| --- | --- | --- |
| Font handle occupies HWND cell |11111111|22222222|
| Font handle occupies outgoing word |22222222|11111111|

These are machine-window counterexamples, not demonstrated valid full C++
owner lifetimes. They prevent an arbitrary-alias equivalence claim.
An independent Unicorn check runs512 disjoint boundary/pattern cases and the
two overlap cases. All514 native GPR/memory/write-order results agree with the
symbolic model; arithmetic flags stay unchanged. Digest:
`fffde10dee5de10ab5a3539b84e0d44e50b01106ddb152eb446b1cd394404262`.

Fresh full-function execution separately passes4,320 cases with the selected
CIL bytes and actual target/list instructions. It checks all14 font arguments,
handle propagation/reloads, full-byte outline coordinates, flag/base-color
publication before list releases, list rewiring, final bytes and normal
RET/ESP/callee-saved ABI. CRT/GDI remain explicit observers; even metrics
failure writes all56 metric bytes. Valid separate objects/lists and bounded
nonoverflowing coordinates are required. No real GDI, unwritten-error-metric,
malformed-list, arbitrary-alias, fault, unwind or whole-runtime claim follows.
The expected trace digest is
`731489fff4e09990ffdcf46c1f87d2cfaddd79f0b3ca0532d59e3ed7011df909`.

## Source/compiler controls and unresolved ownership

Each private control retains the same four canonical leaf payloads:
begin291/f9651374, color352/268b8440, end168/68b02c0e and reset162/8b90f385.

| Private control | What was actually varied |
| --- | --- |
| Opaque window handle | Three compatible pointer declarations and the explicit data-symbol role; no whole-project NO_STRICT assertion |
| RTM CIL | Actual .42 cl/C1XX/C2/link, with fixed pinned SP1 CRT/SDK inputs |
| Explicit inlining | SP1 CIL with /Ob1 in the genuine owner/render context |
| Ordinary member begin | Real nonvirtual declaration/definition/call in the same194h owner; no layout change |
| /EHs and /EHa | Separate genuine exception-model compiler controls |

The pinned SDK's WinDef.h/WinNT.h corroborate opaque HWND under NO_STRICT.
That does not identify the original macro/type; the isolated pointer view is
not selected. Member ownership similarly cannot be inferred from neutral code.
None of these controls changes the ten-byte residual or authorizes a new flag.

The /Ob1 image restores the actual surface helper call that default CIL
inlines. Its parser is1554 bytes versus default1572; both remain nonexact
against1744. EH inspection adds an independent lifetime discriminator:
target FuncInfo6E49EC has four states and ninth DWORD1. Default, /Ob1, /EHs
and /EHa CIL each have three states; their ninth DWORDs are1,1,1,0 respectively.
Begin has no own EH handler in those maps, so this parent metadata does not
identify begin's original option or prove a common original TU. No handler,
cleanup-map or parser acceptance is inferred from normal caller witnesses.

RTM linking initially failed LNK1296 because its compiler-only tree lacked
msobj80.dll. The same-release57,856-byte companion was extracted from the
hash-attested official payload; no installer ran or existing tool binary was
replaced. See [RTM provenance](VC8_RTM_PROBE.md). The137,878,428-byte temporary
media/extraction tree was removed after per-file hashes and version readback.

## Reproduction and checkpoint

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-text-font-color-linked --compare --json
python3 scripts/compare-linked-unit.py gpt-web-text-font-color-linked --address 0x004119A0 --json
python3 -m pip install -r scripts/requirements-smt.txt
taskset -c 0 nice -n 10 python3 scripts/prove-text-font-begin-window.py > build/font-begin-proof.json
```

Both comparisons intentionally exit1 for the unaccepted begin/renderer.
The proof reports `canonical_result=mismatch` alongside its conditional
endpoint result. Z3 is optional and separate from CI's dependency set.

The descriptor moves from native to the existing linked unit, keeping one
selection per address. Seven native comparisons and five linked comparisons
remain. Public CPP stays76e86737, headers/default profile and matching rules
stay fixed. Scoped serial cold replay of both affected units preserves all
six accepted functions, including linked color/end/reset352/168/162.

Private recipes are in `.analysis/font-begin-handles-20261022/`; reports under
the matching `build/` directory include `selected-linked-build.json`,
`selected-window-proof.json`, `native-window-check.json`,
`selected-full-semantics.json`, the control JSONs, `inline-membership.json`,
`eh-context.json`, `rtm-msobj-install.json` and `scoped-replay.json`.
Completed private PE/COFF controls are in `completed-context-controls.tar.gz`;
`retention.json` records every member hash read back before loose removal.
Restore that archive in the build directory before rerunning private readers.
Configured public inputs and `SelectedBegin.bin` remain available.
Control recipes retain their source epochs; original macro/type/TU/toolchain
and exception-runtime behavior remain unknown.

Next reconcile the target's fourth cleanup state with actual CIL/native
construction and cleanup ownership before changing markup lifetimes or stack
storage. Begin remains nonexact; strict totals stay1,381/234,914 bytes (10.99%).
No fresh all-unit cold replay or extra authored/library credit is claimed.
