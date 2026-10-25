# Scenario command interpreter00458440

## Observed target and boundary

Only Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. `scripts/repo-python scripts/audit-scenario-command-update-target.py`
closes the complete interpreter from the raw PE:

- Callable `[00458440,00459C29)`:6121 bytes, SHA-256
  `7062af4006e7ea7f92d8401280bfe123715b729eb1c1bf991e15b6f892de915f`.
- 1693 decoded instructions,1690 conservatively reached; no escaping or
  noninstruction edges. The three unreached instructions are exact internal
  alignment at45879A,4596D8 and4596DF.
- One indirect dispatch at458C7F owns all23 destinations in table459C2C.
  Three alignment bytes and92 table bytes extend the full payload through
 459C88:6216 bytes, SHA-256
  `0a37b616b4d17a6d3cf2d42fa2f9f9b38540cca3005659591f0c44cc856384aa`.
- Following eight INT3 bytes through459C90 remain separately observed;
  their object/linker ownership is unknown. They are not silently credited
  to the source function or waived from a future acceptance decision.
- Scenario vtable006C2998 points to this root at slot08. The receiver is ECX,
  explicit aligned stack allocation is288, and the sole physical RET is RET0.
  The body has216 direct and14 indirect calls, including three IAT calls.
- Return exits set **AL** to00/01/FF. Upper EAX is not established. The old
  `CScenarioData::update` int declaration does not establish this ABI.

The interpreter's game text, character, input, effect, audio and result policies
establish authored ownership independently of its surrounding compiler/STL
helpers. The new origin rule pins the complete body and actual calls to the
accepted fade/color helpers. This is an ownership classification, not exact
credit. The old provisional callable size happens to agree with the closed CFG.

## Complete source and first comparison

`src/battle/ScenarioCommandUpdate.cpp/.hpp` now contain an independently written
complete hypothesis: all23 command IDs/default and the preceding list/text,
character setup, synchronized/local input, result, wait and termination gates.
The new pointer-only member view uses a signed byte return hypothesis and the
existing physical Scenario/container/resource layouts; it is never constructed
or embedded. No accepted shared header or compiler profile changed. The old
nominal return declaration remains unmodified pending caller/type evidence.

Source is **identified/unselected**, absent from `implemented.csv` and
`matches.csv`. Semantic coverage still needs instruction review, and no
behavioral equivalence claim follows from the compiling source.

The first complete source was immediately compiled and submitted to the
strict comparator before changing its shape. Its emitted section was5352
bytes. After binding the observed native EH entry, real virtual thunk and
actual declared providers, strict replay stopped at the newly emitted local
`scenario_peek_inline` helper. Native has the corresponding front/pop logic
inside this root; no target address was invented for the new helper.

One bounded inlining control made the two genuine queue operations explicit
inline helpers. This emitted5640 bytes but exposed the retained declaration-only
ShortDeque8 front operation. A real `std::deque<short>` storage view of the same
20-byte container then retained the same raw root section. Its emitted front
operation independently compares **71/71** against actual provider4321B0,
including the resolved invalid-parameter call. This confirms a provider/storage
identity; it does not accept the caller or add another exact function.

A full4024-candidate helper scan found nine exact symbol-to-entry bindings
(including the shared iterator inequality body). Only positive complete
canonical matches with matching ledger sizes were added to this probe's local
call aliases. No generated helper origin ledger or exact total was changed.
Eight new string literal rows plus private EH/thunk rows are used only by this
probe; existing relocation bindings are unchanged.

Current unit:

```bash
taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py \
  --unit exact-first-scenario-command-update --compare --json
```

Expected exit1 is **blocked**, currently at the local37-byte string copy
constructor. A separate search of all `.text` byte offsets finds no identical
complete constructor after real REL32 replay; it is not merely absent from
the candidate ledger. Native case2 instead constructs the two by-value strings
in the caller. This does not identify the original TU, compiler inlining
context or precise source spelling. No absent constructor binding is supplied.
Other generated providers also remain unqualified.

The current raw section is5640 bytes, SHA-256
`85deb994e1f5deaca5d017846517b717d4df2390384f959286f1dfc054379efe`;
source SHA-256 is
`01a25dc140f47d766ccc137b79b357a62d24814644b8ae3fcc203b19cb573e95`.
These are **unreplayed input hashes**, not canonical payload hashes. No full
canonical difference count, first mismatching offset or percentage exists yet.
Do not report the relocation failure as an ordinary unequal-byte result.

## Multibyte character search correction

The first draft used byte-oriented `strrchr`. Independent review of the actual
native calls458DCF/458DEC instead identifies the19-byte wrapper68B4EE,
which passes locale0 to68B42E. The latter tests a multibyte lead-byte table,
consumes paired bytes together and delegates to byte `strrchr` only in its
non-multibyte branch. The current source uses `_mbsrchr` at both sites and
binds the actual68B4EE provider. The root's unreplayed section remains5640
bytes; unchanged raw bytes do not imply unchanged resolved call destinations.

Publisher-toolchain corroboration uses the pinned SP1 libcmt member
`build/intel/mt_obj/cpp_obj/mbsrchr.obj`,10363 bytes, SHA-256
`10ad698c12ab76969807438bf8e593bdfdcbef4d18f98af4e9ddb57aa5a22990`.
Its `__mbsrchr`19-byte wrapper agrees completely with target68B4EE after
resolving `__mbsrchr_l` to68B42E. This is provider identification within the
new interpreter probe, not a new accepted runtime unit or authored exact credit.
Reproduction:

```bash
scripts/repo-python scripts/extract-msvc-library-object.py --library libcmt \
  --object mbsrchr.obj --output build/exact-first-scenario-update-20261025/mbsrchr.obj
scripts/repo-python scripts/compare-function.py 0x0068B4EE \
  build/exact-first-scenario-update-20261025/mbsrchr.obj --symbol-base __mbsrchr \
  --rel32-target '__mbsrchr_l=0x0068B42E' --json
```

The active runtime codepage is not established here. No locale behavior matrix
or whole-interpreter runtime equivalence is claimed. Receipts use the
`mbsrchr-*` prefix, including the corrected complete build/comparison.

## Evidence limits and continuation

Raw instructions and the public target audit outrank decompiler types. A single
read-only384MiB Ghidra process independently checked executable identity, entry,
language/compiler specification and all mapped PE section bytes. Its temporary
function and ABI view were read back and rolled back. All nine primary DB file
hashes remained unchanged. The saved decompiler output has unreachable-block
warnings and remains a hypothesis; it was not mechanically pasted as source.
IDA preflight again rejected the different GUI target, so no IDA semantics were
used.

Next work is the concrete source/provider visibility question at case2 and
remaining generated operations, followed by an unmasked complete replay. Do
not skip unbound calls, allocate arbitrary replacement addresses, force register
lifetimes, or infer standalone/LTCG impossibility from this first failure.
No broad behavior matrix was added. A scoped runtime witness is appropriate
only when instruction review reveals a specific ambiguous branch or interface.

Receipts: `build/exact-first-scenario-update-20261025/` contains target-audit,
first-compare/formal-first, queue-inline, native-deque, current-admission,
native-deque-front, generated-helper-scan, copy-constructor-all-text,
current-inputs and Ghidra attestation/hash receipts. Private source snapshots,
scan recipes and read-only decompiler driver are in the matching `.analysis/`
scope. Generated files, target, analysis DB and compiler remain outside Git.
