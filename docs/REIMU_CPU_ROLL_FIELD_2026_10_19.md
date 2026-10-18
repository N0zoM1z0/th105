# Reimu CPU signed selection field, 2026-10-19

The selected15999-byte root at48D390 now reads the signed76A field directly
instead of a scalar snapshot. Ordinary VC8 forwards its producer into ECX
without a single field reload, while eliminating all44 non-target unsigned
range branches in the reachable policy0 CFG. Twenty-one manual range gates
are restored to ordinary field range predicates. The root remains nonexact:
first mismatch+12E/48D4BE is the displacement of JLE48D4BC. No exact credit
is added.

## Target and source interpretation

Only original Japanese1.06a is used, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable `[48D390,49120F)` SHA256 is
`3bd363994e140603ae0ec249ffd3a36b1ae0448e72a389e417c4cc7a6d113e2d`.
Authored vslot+58 identity, void ECX ABI, complete4126-instruction closure,
52 balanced RETs and four adjacent metadata tables remain unchanged.

**Observed target:** selector result EAX is copied into ECX at48FC28; CX is
stored at76A at48FC2D. Later signed16-bit predicates consume CX. No target
instruction reloads76A. Reachable policy0 has1488 instructions,37 selectors,
50 RETs,110 JL,61 JG and no JA/JBE branches.

**Prior inference, now superseded:** no reload was taken to favor an explicit
local cache so strongly that direct field reads were discouraged. That was
not established by the machine code. A real memory read in C++ can disappear
after optimization. The preceding int-cache source correctly reproduced
MOV ECX,EAX but still generated38 JA and six JBE policy0 branches.

**Fresh compilation:** store the real selector result into signed member76A
and use that member in each decision. The compiler emits MOV ECX,EAX, stores
CX, and eliminates every76A reload. All44 unsigned range branches disappear,
including before any range-source cleanup. Thus absence of a machine reload
does not identify a unique original C++ cache declaration. The precise
optimizer pass responsible is unknown; no volatile qualifier, fake use,
helper, ABI change or assembly is introduced.

The selected source also replaces21 paired rejecting gates with their
ordinary inclusive field range conditions, removing the unused labels. It
keeps condition bounds, side-effect ordering, genuine helper calls and early
returns. Using the already-declared signed766/768 members instead of retained
raw WORD/short casts is independently canonical-payload-identical; deleting
the policy-roll macro is also byte-identical. Shared field layouts are
unchanged. This is a supported source hypothesis, not proof of original source.

Direct read-only Ghidra independently re-attests imported identity, entry,
mapped text, root bytes and typed method metadata. Nine primary DB file hashes
remain unchanged; alias removed. The384MiB/CPU0 recipe is under
`.analysis/reimu-cpu-roll-field-20261019/`. Required IDA preflight still rejects
the wrong open file; no IDA semantics, factory adapter or target patch is used.

## Whole-root and reachable policy0 diagnostics

| Variant | Root prefix/payload | Policy0 instructions | Selectors | RETs | JL/JG/JLE | JA/JBE |
| --- | --- | --- | --- | --- | --- | --- |
| Target | 15999 / metadata separate | 1488 | 37 | 50 | 110/61/50 | 0/0 |
| Previous explicit int cache | 15860/16401 | 1359 | 33 | 49 | 67/3/63 | 38/6 |
| Direct76A, old manual gates | 15944/16485 | 1379 | 34 | 46 | 111/41/69 | 0/0 |
| Selected natural field predicates | 15916/16457 | 1385 | 34 | 46 | 111/56/54 | 0/0 |

These counts come from closed reachable policy0 CFGs, not physical suffix
disassembly. They exclude unreachable other policy arms and carry no partial
exact credit. All reviewed CFGs have no unresolved transfers and only the
real selector dependency. Whole-root counts change117->118 selector sites
and50->48 RETs; target has121/52. Size or a later first mismatch is not an
acceptance criterion.

Coupled native selection traces preserve all18 previously correct one-to-one
observed CALL components, including the initial draw and policy selection
producer. The remaining bad component splits/merges change; the net deficit
of three selectors is not three independently missing operations. All source
policy0 instructions are not thereby proven correct.

Observed one-to-one RET and ordered-publication groups remain25 and33,
respectively, but their memberships change. Target RETs48FD23 and48FE44 lose
one-to-one correspondence;48FD04 and490640 gain it. Do not describe this as
uniform terminal-sharing improvement. The selected policy3 publication now
has the same66 live-value observations as target, but other source publications
still carry non-target live FP values. All selector entries/genuine returns
remain empty/TOP0 and preserve their x87 state on the selection matrix.

Two additional controls remain unselected:

- Repeating the real terminal-body expansion after this independent field
  change gives125 root selectors/57 RETs and policy0 counts1546/41/56.
  Its16757-byte payload exceeds the reviewed next-function boundary when
  replayed at48D390; it is not executed. The source change alone does not
  recover the target's mixed shared/copied terminal structure.
- A private `/O2 /Os` build on the new source has a13912-byte section tail,
  fails the existing action-table shape contract and first differs at+50/
  48D3E0 in timer decrement encoding. No shape gate is weakened and the
  selected/O2 unit flags are unchanged. This is phase-scoped negative evidence,
  not a proof that every possible size/LTCG context is impossible.

## Selected artifacts and execution

| Artifact | SHA256 |
| --- | --- |
| Source | `77234302d395e30a71dbded324b0696e142c0f53ff56cb0c2a34d590a03d7864` |
| Fresh selected ordinary object | `159333751ab7993f04ef5b433769f41cabbbc43102677c1af46b703015f7a1eb` |
| Canonical16457-byte payload | `d3b9a02340e6c4611a46007991b816c5675310b7e1d2cd28221f9a08f2d6ed54` |

The preceding selected payload was
`70905d5a0663e6c41cbdc5dfd94a9ee56b8ed3a197011432c5270e87b2990ae4`.
The direct-field intermediate payload is
`281b44f375fa97323b766b8c96b82eabb1dd7f46f952827610d58c8d077f344c`.
All four candidate metadata tables still close under the existing manifest.
Canonical root producer/store widths match; no76A loads are emitted.

Fresh intermediate and selected-shape selection runs each pass0/16160 cases,
confirm real rolls0..100 and visit all1488 target policy0 instructions. The
selected source's entire payload, including metadata, is identical to the
natural-range object used for that run; typed-member and macro cleanup require
no repeated identical-code execution. The current selection report contains63
coupled terminal records,50/46 observed RETs and46420 paired selector calls.
This is actual-helper execution from explicit empty masked-PC53 input, with
full actor/RNG/call/ftol2/stack/control comparisons, not substituted outcomes.

Fresh selected-object execution passes0/5000 general,0/45714 action-edge and
0/368 height/NaN cases. Together with the16160 selected-shape selection cases,
this is0/67242 on the current canonical code. General and action-edge suites
execute all five original helpers on both sides. These reports are retained
under `build/reimu-cpu-roll-field/`, together with strict comparisons, closed
CFG profiles and unselected controls. Reproduction:

```bash
python3 scripts/build.py --unit gpt-web-reimu-cpu-action-policy --compare --json
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu \
  --selection-cases --selection-x87 --selection-terminals
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --cases 5000
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --reimu-edge-cases
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --height-cases
python3 scripts/validate-tracking.py --require-target
python3 scripts/ci.py
git diff --check
```

Original source/TU visibility, constant2/400 register lifetimes, remaining
CALL/publication/RET memberships, FP scheduling and complete numerical/gameplay
equivalence remain unknown. Keep direct signed764/76A reads; do not restore a
scalar snapshot merely because the generated machine code has no field reload.
No shared header/flag/relocation change, unrelated accepted-unit replay or
aggregate cold exact claim is made.
