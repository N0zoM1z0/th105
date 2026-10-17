# Iku call sharing and below-surface result consumers

Current checkpoint after [payload lifetime recovery](IKU_PAYLOAD_LIFETIMES_2026_10_17.md).
The target is the original Japanese TH10.5 v1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete Iku root remains `[620920,62EFBE)`,59038 bytes, SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
This is source/ABI/CFG evidence. Canonical whole-root comparison is still
**nonexact at+0x64 /620984**, after100 equal bytes. No exact count changes.

## Selected source and exact observations

The genuine `435DC0` below-surface predicate is42 bytes, SHA-256
`c2ee1b68bc5f44631a3cb5ec0538eae7a7280d08036bc4cf15ebaae9fd74fc12`.
It receives the fighter in ECX, has no stack argument/purge, and every normal
return sets the complete EAX to0 or1. Its two endings are MOV EAX,1/RET and
XOR EAX,EAX/RET. All10 physical Iku call sites immediately test **AL**.
The declaration remains `int __fastcall`; eleven source expressions now
explicitly narrow the result to `unsigned char`. Actions209/221 share one
physical entry. No callee ABI or canonical binding is changed.

Against checkpoint7170e75, the entire59586-byte normalized COFF section differs
at exactly10 bytes: each `85 C0` TEST EAX,EAX becomes `84 C0` TEST AL,AL after
a genuine435DC0 CALL. Instruction boundaries, edges, metadata, constants,
CALL relocations and all other bytes are unchanged. This is a narrow source
correction, not a new aggregate replay result. The public payload audit now
attests this callee hash and its10 low-byte consumers as well as the existing
41 surface-crossing consumers.

- Current source disk SHA-256 (CRLF):
  `5e7a21d0eb7a454a1d8c1133897246c6091466162e20c8eb5f96a8852a37cbfc`.
- Normalized whole-section SHA-256:
  `374c181347c08c54e414af063ff7eb7004fac6790196adf15b8fcf494f625356`.
- Callable span58430 bytes;15033 reachable instructions/58424 instruction bytes,
  six unreachable compiler alignment bytes,128 RETs. Metadata/alignment after
  the callable adds1156 bytes. Frame400hex and84 payload homes remain.
- Ordinary/register CALL sites867/166 versus target865/177; physical-owner
  diagnostics remain5/109, actions2/4/5/204/303. These are not partial credit.

## Where the excess effect calls come from

`scripts/audit-iku-call-sharing.py` propagates possible incoming action IDs
through the raw target and actual COFF CFG. Conditions are not evaluated;
ordinary CALLs retain their continuation. The report labels prelude-only
sites with an empty origin list and the default entry with-1. Virtual calls
retain the independently qualified receiver/slot set, including mixed8/C.
Three synthetic CFG tests cover shared loops/call continuation, RET isolation,
compressed-table edges and rejection of unknown edges.

Target effect435240 at **626C3B** has possible incoming actions
**416/417/565/566/567/568**. The call lies inside physical416; the latter four
heads join after preparing arguments. Candidate shares only416/417 there and
emits four separate sites for565–568. This accounts for its58 effect calls
versus54 in the target. The other shared effect site,621E48 with actions
208/209/210/211/212/220/221/222, already has the same origin set in the object.
These static unions locate sharing differences; they do not prove every path
feasible or establish missing behavior from a call-count difference.

Private controlled experiments remain unselected:

| Experiment | Observed result | Consequence |
| --- | --- | --- |
| Explicit shared FX62/next-sequence tail, with real X/Y locals | Effect calls54; span58151; register calls163. Shared call moves to62B3FE near568 instead of target626C3B. | Earlier IR sharing causes different physical ownership; matching the count alone is insufficient. |
| Forced-inline FX62/next-sequence helper at the six heads | Entire normalized section identical to selected source. | This refactor does not cause the target's later argument-tail sharing. |
| Local independent polymorphic field view, leaving shared headers untouched | Same span/call counts; only two callable bytes swap FLD/FADD operands73C/740. | Layout visibility does not explain this sharing difference; retain the conservative selected view. |
| Pinned VC8 RTM rather than selected SP1 | Span58439, same58 effect/166 register calls, first mismatch still+64. | No compiler-profile change; the Rich header alone does not select a revision. |

The typed-view experiment checked57 explicit fields plus the implicit vptr:
each literal entry-this offset/width against raw ESI-based operands, with
62092F MOV ESI,ECX the root's only non-POP ESI write. It preserved current
source signedness hypotheses and genuine external-call symbols. Independent
direct Ghidra readback first re-attested executable identity, entry, mapped
`.text`, all58 layout components,177 virtual-call records and custom ftol ABI.
The read-only768MiB/two-CPU clone was removed; all nine primary database files
retain their pre-run hashes. Wrong-image IDA remained rejected.

## Focused validation and reproduction

Fresh native whole-entry execution covers only actions
201/208/209/210/211/212/220/221/222/224/418: **0/812 mismatches**,386 RETs and
426 genuine first backend entries (42 effect,238 action,146 sequence).
It visits747 target-root instructions. Input SHA-256 is
`28580b305a2222ab76c636f031e1ff07664abd6c959292f73b0d4eb5b2a5bd2d`;
target-output SHA-256 is
`1b6bcbb0353862cabdbcf6f31447c276da40269da20f387a35dd35b682a3701a`.
The native-tested object and final configured unit replay to identical full
normalized section bytes. The earlier16285/26783 matrices and unrelated
accepted units are not rerun. Post-backend and exceptional behavior remain
unknown; no helper return value is injected.

```bash
python3 scripts/build.py --unit gpt-web-iku-action-state --compare --json > build/iku-sharing-final-compare.json
# Expected exit1: canonical first mismatch+0x64, not a build failure.
python3 scripts/audit-iku-call-sharing.py --object build/match-units/GptWeb_IkuActionState.obj > build/iku-sharing-final-origins.json
python3 scripts/audit-iku-payload-homes.py --object build/match-units/GptWeb_IkuActionState.obj > build/iku-sharing-final-homes.json
python3 scripts/audit-giant-action-owners.py iku-vslot28 build/match-units/GptWeb_IkuActionState.obj --unit gpt-web-iku-action-state --json > build/iku-sharing-final-owners.json
python3 scripts/probe-iku-upper-actions.py --source src/characters/IkuActionState.cpp --output build/IkuSharingFinalNative.obj --all-actions --smoke --whole --actions 201 208 209 210 211 212 220 221 222 224 418 > build/iku-sharing-final-native-report.json
python3 scripts/audit-iku-full-root.py --object build/match-units/GptWeb_IkuActionState.obj --native-object build/IkuSharingFinalNative.obj > build/iku-sharing-final-facts.json
python3 scripts/ci.py
git diff --check
```

Continue with joint argument packing, suffix ownership and live scalar/
constant lifetimes in this same root. Do not enforce the effect count with
fake calls, helper ABI changes or padding. Original C++ spelling, complete
inheritance/TU and LTCG's role remain unknown; none of these experiments proves
a standalone-match barrier.
