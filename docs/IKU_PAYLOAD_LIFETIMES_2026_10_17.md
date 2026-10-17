# Iku payload identities, stack frame and narrow result consumers

The complete `Iku_dispatch_action_state_vslot28 @ 620920` now naturally
reproduces the target's **0x400 stack frame** and **84 caller-stack payload
homes**, removing 14 extra arrays from the selected source. The first
canonical mismatch advances from +8 to **+0x64 / 620984**. All 41 surface
crossing consumers now test AL as the target does. The root remains nonexact;
there is no partial or exact authored credit.

## Observed stack and identity evidence

Target identity remains original Japanese TH10.5 v1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The root's 59,038 bytes retain SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
This batch uses hash-attested PE/COFF facts. The wrong-image IDA session is
rejected by metadata preflight; no database or target bytes are modified.

`scripts/audit-iku-payload-homes.py` traces stack depth and pointer provenance
from the aligned root entry through all reviewed branch edges. It follows
PUSH/POP, stack adjustments, LEA/MOV origins, supported stores, register kills
and joins, with explicit genuine callee cleanup contracts and independently
qualified receiver-domain virtual calls. Unknown pointer paths stay unknown.
The model assumes those established interfaces and ordinary callee saves; a
balanced stack alone does not prove a callee ABI or arbitrary callee behavior.

Both target and selected candidate have 84 distinct payload addresses at
`32 + 12*n`, n=0..83, relative to ESP after saving the four GPRs. The first
16 bytes there are the saved registers; the following 16 bytes are scalar
scratch; the remaining 84 three-float cells account for the frame:
`16 + 84*12 = 1024`. The prior object instead has 98 contiguous cells and
`16 + 98*12 = 1192`, exactly explaining its 0x4A8 frame. No padding or inert
locals are needed to obtain the target size.

The excess cells are localized to seven actions. Target call-site provenance
supports the following reuse, rather than unrelated arrays with equal values:

| Action | Target homes | Prior homes | Recovered identity |
| --- | ---: | ---: | --- |
| 412 | 1 | 2 | Initial object802 and following ring share their payload |
| 505 | 2 | 4 | Each sequence's initial object815 and ring share a buffer; the two sequence buffers remain distinct |
| 506 | 2 | 4 | Same two distinct sequence scopes, with their observed variant values |
| 520/521, each | 1 | 2 | Pre-advance ring and later object811 reuse the same payload |
| 720 | 1 | 2 | Object910 and its following six-ring reuse one payload |
| 730 | 1 | 7 | Both initial object920 calls and all six static ring sites use one buffer |

The ring helpers now accept caller-owned payloads where that identity is
observed. Existing wrappers keep local buffers for unaffected callers.
Every ring iteration still initializes all three values before publishing
the pointer. 520/521 explicitly overwrite all three fields after the ring,
preserving the target's ordering. These are genuine live buffers passed to
the original spawn interface. They are not original variable-name or lexical
scope claims. Physical sharing across calls is the observation; the C++ scope
expressing it is a source inference.

The analyzer checks every stack join and normal frame restore. Target has
131 such epilogues; current candidate has 128. The candidate also contains
two unreachable three-byte `lea ecx,[ecx]` alignment instructions, each after
a short jump to its following 16-byte boundary. Those six bytes are reported
separately, never silently removed from comparison. Any other unreachable
instruction fails the stack audit. Five tests cover distinct/reused buffers,
unknown pointer origins, wrong callee cleanup and unreviewed unreachable bytes.

## Narrow use and prelude condition

The exact-backed 64-byte predicate at 5F9310 has SHA-256
`8e948c42039b2fda3ef75fb7d40e120c8e128c44a2fd002412913911cf4d4dd6`.
Its two return paths fully set EAX to 0 or 1. All 41 calls in the original
Iku root immediately test `AL,AL`. Six source expressions already narrowed
the result; 35 more now explicitly cast to unsigned char. The callee's int
facade, source, canonical binding and ABI are unchanged. This expresses the
observed caller consumption without inventing a byte-return declaration.
The final actual root has 41 calls and every consumer tests AL.

The target prelude compares signed WORD+174 against zero with JLE. Changing
the equivalent source `<1` condition to `<=0` removes an early preserved
constant-1 dependency. Before this change, the recovered frame passes the
first 26 bytes and differs at +1A. Afterwards, the first **100 bytes** match;
target then loads EDI=1 before its action-range branch, while candidate branches
without that hoisted load. This is a source/optimizer phase observation,
not permission to insert a forced register variable or fake dependency.

A private direct-void-switch experiment before the final predicate change
replays to the same full-section bytes as the inlined status source. The
status abstraction therefore did not explain that phase's code difference;
the experiment is not selected and no historical probe interface is broken.

## Current code generation and limits

The final candidate contains 15,033 reachable instructions / 58,424 instruction
bytes in a 58,430-byte callable span, including six unreachable compiler
alignment bytes. Its 59,586-byte section adds 1,156 bytes of table/index
metadata and alignment after the callable. All three 33/42/35-entry tables
and 108 physical table destinations still agree; no local CALL relocation or
external tail remains. Five of 109 owner diagnostics remain instruction/edge
identical (2/4/5/204/303). These are diagnostic partitions, not partial exact
credit or independent original functions.

Ordinary CALL sites remain 867 versus target 865; register sites are now 166
versus target 177. Return/tail sharing, payload slot permutation in other
actions, scalar scratch placement and constant/register lifetimes still need
joint recovery. The target frame and matching prefix alone do not close the
whole root or establish an LTCG barrier. Complete class layout, original
source/TU spelling, exceptions and post-backend behavior remain unknown.

## Final native evidence and receipts

Fresh final-source whole-entry smoke passes **0/16,285** cases: 12,769 genuine
RETs and 3,516 first backend/runtime entry stops, visiting 10,195 target-root
instructions. Both roots execute their own prelude and genuine motion/frame,
landing, RNG, event/audio, counter and math helpers without result hooks.
The full actor, arguments/payloads, call/publication order, RNG/global effects,
conversion inputs, RET stack/callee saves, empty x87 and control word still
agree. The input and target-output digests match the earlier smoke fixture.
The old expanded 26,783 matrix is not replayed after these changes.

This retains the prior flat-stage/resource/zero-event fixture limits and stops
before object/effect/action/sequence/finalize/common backends. Nonfinite heading
and NaN X cases stop at the genuine cosine/abs entries. First-spawn payload
values alone cannot establish later buffer identity; the stack packet supplies
that independent call-site evidence. Complete backend/exceptional behavior is
not claimed.

- Final source SHA-256, CRLF on disk:
  `2a287193aa873fa369994f10968f03b2de45771356f8dac2ad4b87bd3243e663`;
- input SHA-256:
  `74b221b4ed574beb84cdfb324f2298645fd787ed48696486c05568598da3d1e6`;
- target-output SHA-256:
  `dd68c4cd32ae4a96d7cc2d0b5ffef5f9ce8dc1c58a43a91ef68416e1f1e7051e`;
- full canonical-replayed candidate section SHA-256:
  `e9bb12c69a4ba22621616c7ed19e5446bee7469e435c956956a709edf8e72814`.

The source/header/object hashes are checked around native execution. The
freshly built unit and final native object replay to identical full-section
bytes. The explicit old-object packet reports 98 homes, frame 0x4A8 and wider
consumers, demonstrating that the diagnostic does not force a candidate to
the target's allocation. These reports remain diagnostic, not acceptance.

The earlier flat-dispatch checkpoint is
[historical](IKU_FLAT_DISPATCH_2026_10_17.md). Canonical acceptance still compares
the complete fixed 59,038-byte target extent, with unchanged relocations,
headers, profile and unit partition. No unrelated accepted-unit replay or
fresh aggregate percentage is claimed.

Reproduce the focused evidence:

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json > build/iku-lifetimes-final-compare.json
python3 scripts/audit-iku-payload-homes.py --object build/match-units/GptWeb_IkuActionState.obj > build/iku-lifetimes-final-payload-homes.json
python3 scripts/probe-iku-upper-actions.py --all-actions --smoke --output build/IkuLifetimesFinalNative.obj > build/iku-lifetimes-final-native.json
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuLifetimesFinalNative.obj > build/iku-lifetimes-final-facts.json
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json > build/iku-lifetimes-final-owners.json
python3 scripts/validate-tracking.py --require-target
python3 scripts/ci.py
git diff --check
```

Canonical comparison intentionally exits nonzero. Objects/reports remain under
`build/`, private drafts under `.analysis/`. Re-attest a Ghidra import before
database use; this compiler/stack batch uses raw target evidence only.
