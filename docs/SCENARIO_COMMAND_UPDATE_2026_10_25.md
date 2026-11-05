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
  `CScenarioData::update` int declaration did not establish this ABI. It and the
  separate advance-loop ownership are corrected to a signed-byte contract in
  SCENARIO_FONT_OWNER_CORRECTION_2026_10_29.md.

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
or embedded. The initial whole-source comparison changed no accepted shared
header or compiler profile; the later entry-ownership correction is recorded
below. The old nominal return declaration was later corrected with the actual
story/ending caller evidence; see SCENARIO_FONT_OWNER_CORRECTION_2026_10_29.md.

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
call aliases. At that first checkpoint no generated-helper origin or exact
total changed; the subsequent strict front-accessor correction is recorded below.
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

## Entry ownership and real-provider control,2026-10-25

The actual case2 provider456EB0 closes598 code bytes through457106, with
RET80. Its stack owns two28-byte string objects plus six four-byte argument
slots; the original formal parameter grouping is still a hypothesis. The
body constructs a real0xDC text entry, copies the text, records the signed slot,
mirrors positive-side X about640, publishes480+Y and color bytes, inserts the
entry and finally destroys its temporary at457085 via435F00.

That last call exposed a real gap in the retained shared type:
`ScenarioTextEntryDC` had an implicit destructor, which omitted the native
release of resource_handle_000. `src/battle/ScenarioData.hpp` now declares the
owned destructor and `src/battle/ScenarioTextEntryRelease.cpp` supplies its
ordinary C++ body. The implicit string and UiSprite94 member cleanup then
naturally follows the explicit title-resource release, including the IColor
vptr restoration. The existing0xDC layout and constructor remain unchanged.

The new `gpt-web-scenario-text-entry-release` unit replays the **entire133-byte**
COFF section at435F00, with zero unequal bytes and all relocations resolved:
SHA-256 `ccaa3c72da0fb768a6c18c281d06cd340474d9e2292b7574c195576a4105ed3e`.
Both the private first build and public focused build agree. No padding,
assembly, masks or exception-state overrides are involved. This authored
resource ownership operation is separately selected/accepted; it does not
accept the interpreter.

```bash
scripts/repo-python scripts/build.py --unit gpt-web-scenario-text-entry-release --compare --json
```

The source dependency graph identifies eight previously accepted units that
include ScenarioData.hpp, plus the nonaccepted interpreter. All affected
accepted functions pass the completed full cold replay:524/524 units and all1412
authored functions, including this new133-byte entry. All eight affected old
units/19 functions remain exact. The receipt is
`build/exact-first-scenario-update-20261025/cold-all.log`.

One genuine456EB0 provider hypothesis was also compiled before joining it to
the complete caller. Pinned VC8 utility shows that make_pair takes its operands
by value, whereas native uses a two-reference pair constructor followed by a
const-key pair conversion and two pair destructors. An explicit ordinary
`std::pair<std::string,ScenarioTextEntryDC>(name,entry)` therefore replaces that
first private make_pair spelling. The complete provider emits599 versus598
native bytes, SHA c1b161af,326 unequal positions when its full emission is
replayed against the PE; first difference+58 is EH-state scheduling. The extra
byte is not waived. It remains private/unselected, with original formal
parameter grouping and EH/TU context unknown.
A separate read-only EH-header packet finds matching non-address words for
native/emitted entry, provider and caller: magic19930522, state counts2/5/9,
and final word1. This supplies no evidence for an exception-model flag trial.
The packet is `eh-root-provider-summary.json`; action ordering is still a
separate question from header equality.

A combined real-provider/caller object retains the caller's entire raw5640-byte
section SHA85deb994 and still fails strict replay at the local37-byte string
copy constructor. No missing helper receives an invented target address.
This finite same-TU control is closed; it proves neither all possible source
contexts nor LTCG impossibility. The interpreter remains unselected and has no
canonical difference count. Retain these receipts and switch to a fresh root
unless independent ownership/compiler evidence changes the question.

Private recipes and complete first/pair/joint sources:
`.analysis/exact-first-scenario-update-20261025/provider/`. Receipts use the
`install-character-*`, `provider-joint-*`, `joint-section-*` and
`entry-release-*` prefixes. `shared-header-affected.json` lists dependencies.

## Withdrawn authored credit: deque front4321B0

The helper provenance audit found that the formerly authored `front_checked`
entry is the complete VC8 `std::deque<short>::front()` operation. The other
seven distinct positively matched iterator/string helper entries were already
compiler exclusions;4321B0 was the accounting exception.

`scripts/probes/DequeShortFrontOrigin.cpp` now retains the real standard member
address. It provides no game facade or custom guards. The pinned SP1 compiler
and unmodified deque header regenerate **all71 bytes**, including both actual
invalid-parameter call destinations, SHA-256
`0f5106f69182629b19ef308697523efdc90bed3a805f9199138b918c3a5c8b89`.
The full4024-candidate scan has exactly one hit. The new origin anchor repeats
that uniqueness check and pins the full native body hash, so the origin proof
also fixes both REL32 destinations. The dedicated unit uses full canonical
replay without masks.

Compiler/header hashes are retained in `deque-front-provenance.json`:
cl.exe71c93ca5, c2.dll497d1ffe, deque header2970afda. These are the existing
SP1 toolchain, not a newly substituted compiler. The compatibility address
alias `front_checked` remains available to existing callers, now categorized
as library code. The old handwritten `src/battle/ShortDequeAccess.cpp` facade
is removed; the probe source remains separate from authored source.

```bash
scripts/repo-python scripts/build.py --unit cross-v106a-short-deque-front --compare --json
scripts/repo-python scripts/function-origins.py --check
```

`implemented.csv` and authored `matches.csv` no longer count4321B0. The new
entry destructor adds133 authored exact bytes, while this correction removes71:
net **+62 authored exact bytes**, with no net exact-function/source-present
count increase. The compiler exclusion adds no reconstruction credit. An
in-progress cold run against the former census was deliberately stopped at
242/525 units and retained as `cold-before-front-origin.log`; it is not an
aggregate result. The corrected `cold-all.log` subsequently passes all524 units/
1412 functions, verifying381170 authored exact bytes. No compiler operation is
restored to authored credit by that replay.

## Evidence limits and continuation

Raw instructions and the public target audit outrank decompiler types. A single
read-only384MiB Ghidra process independently checked executable identity, entry,
language/compiler specification and all mapped PE section bytes. Its temporary
function and ABI view were read back and rolled back. All nine primary DB file
hashes remained unchanged. The saved decompiler output has unreachable-block
warnings and remains a hypothesis; it was not mechanically pasted as source.
IDA preflight again rejected the different GUI target, so no IDA semantics were
used.

The real-provider control above is closed. Resume the case2 ownership question
only with independent new facts, then require an unmasked complete replay. Do
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

## Real checked-map iteration, 2026-11-04

The seven text-map advances in the still-unselected interpreter hypothesis now
use the actual `std::map` iterator's `++it` rather than a declaration-only
iterator facade. In a fresh ordinary VC8 build, its emitted checked-tree
`_Inc` specialization compares exact 126/126 with the independently
classified compiler-generated helper at `0x00435C00`, including the pinned
invalid-parameter call. The probe binds that real specialization, not the old
facade, to the existing target helper; it earns no authored-byte credit.

The interpreter's fresh root section is 5,368 bytes. Strict comparison still
stops on an unresolved locally emitted string constructor, so the section
size is not an accepted body comparison and there is no new exact or
source-present credit. The target CFG audit continues to pass. No general
behavioral equivalence or full executable link is claimed.

## Real text-map lookup, 2026-11-04

Four further map lookups now use the actual `std::map::find` operation instead
of a declaration-only facade. A fresh VC8 object emits its `find` specialization
exactly matching the already excluded native compiler helper `0x00455A00`,
122/122 bytes. Its lower-bound callee is independently emitted from the actual
Scenario text-map type and matches the native `0x00455270` body, 153/153,
including its real `char_traits::compare` call. A fresh pinned-compiler origin
witness checks the full 153-byte fingerprint against the entire current
candidate inventory and identifies a unique hit. That helper is therefore
classified as compiler-generated, not authored; it adds no authored exact bytes.

The interpreter remains an unselected source hypothesis: the fresh 5,368-byte
root section still blocks at an unresolved string constructor, and no full-body
comparison or general behavioral equivalence is asserted.

## Shared text-entry owner, 2026-11-04

The existing exact `render_dynamic` and `update_dynamic_state` functions now
belong to the real shared `ScenarioTextEntryDC` type rather than a duplicate
layout view. The unselected interpreter calls that same update member on its
actual map value, removing another declaration-only facade. Fresh builds and
comparisons preserve 22 accepted functions across the directly affected source
units, including both exact text-entry functions. The new map lower-bound
origin witness also revalidates against the revised header.

The interpreter itself still blocks at the same local string constructor and
its 5,368-byte root section is not an exact comparison. This source-owner
cleanup adds no authored exact bytes and does not establish full-program linkage.

## Shared scenario owner, 2026-11-04

The still-unselected command-update hypothesis now implements the existing
`CScenarioData::update` virtual member directly rather than a separate
pointer-only receiver view. It uses the shared scenario fields and the
same signed-byte return hypothesis, and its EH symbol binding follows the
actual member name. The unused view header was removed. The ordinary VC8
root section remains 5,368 bytes and strict comparison continues to stop at
the unresolved local string constructor; this is not a full-body result.
Target CFG audit and affected accepted scenario provider units pass. No source
selection, authored exact credit, general behavior proof or whole-game link
is claimed.

## Character-installation ownership, 2026-11-04

The complete 598-byte `0x00456EB0` body is now classified as authored game
code: it creates and inserts a Scenario text entry, publishes side-dependent
position and colors, and configures the Scenario font. Its body hash, three
incoming sites (including two in the freshly revalidated 991-byte exact battle
transition), and exact entry constructor, font configuration and destructor
calls are pinned. The provisional source remains unselected and nonexact:
the independently rebuilt actual-type control is 599/598 with unresolved
argument grouping and EH/TU differences. This classification adds no source
or exact credit and is not a full EH or behavior-equivalence claim.

## Character-installation source, 2026-11-04

A subsequent actual-type source candidate is selected for `0x00456EB0` and
implements `CScenarioData::install_character`, using the real shared text-entry,
sprite, map and font-configuration fields. The command-interpreter hypothesis
calls this member directly. Formal argument grouping remains a source
hypothesis, not a recovered original declaration. The selected ordinary VC8
body is 599 bytes versus the native 598, with first mismatch at +58 and full
candidate SHA-256 `c1b161af501134996ddaed612b60662ac16876d9729af8d76600e2a7c4ef589a`.
Only the native EH handler's initial 16 bytes are pinned for relocation;
complete EH metadata and general runtime equivalence are not established.

Fresh scoped comparisons preserve 27 previously accepted related roots,
including the 991-byte phase-five caller. The command interpreter remains
blocked at its own local string constructor. The 598-byte install function is
now source-present but contributes no exact bytes. This section supersedes the
older statements above that its source candidate is private and unselected.

## Exact phase-five call graph, 2026-11-04

The actual phase-five caller pushes the signed player index as an integer, while
`0x00456EB0` reads its low byte as a signed side. Modeling the source interface
as an integer and converting to a signed byte inside the callee preserves that
observed behavior and lets the exact phase-five source call real
`CScenarioData` methods for configuration, page loading, installation and label
selection. The native original nominal signature is still not uniquely proven.

A fresh comparison keeps phase five exact at 991/991; the install candidate
remains nonexact at 599/598, first mismatch +58, with canonical SHA-256
`9fd51ab6ff74d87751a825e7b301317f17b3b4f060cc03573061c5d09438a761`.
The command interpreter still blocks on its local string constructor. These
results do not establish full-program linkage or full EH equivalence.

## Updated joint-source control, 2026-11-04

After connecting the real Scenario owner and the scalar text-entry layout, a
single ordinary VC8 translation unit containing the actual character-install
and command-update sources was compiled as a bounded diagnostic. The command
root's raw 5,368-byte section is unchanged from its separate-source build
(SHA-256 `0a8a11f6a14e32e94f09beff1352050ba8485d592ed1921eaa50459b1637c8fd`),
and strict comparison still blocks at the same unresolved local string
constructor. The combined object is not an accepted full-game link and earns
no source or exact credit for the interpreter.

## Character command signed slot transport (2026-11-05)

The character command's original call sequence at `0x458FF3..0x45900E` loads byte `+0x2C` with `MOVSX` before passing the full four-byte slot argument to `install_character`. The command parser's storage remains an unsigned byte, but the unselected source previously promoted it unsigned, so values `0x80..0xFF` reached the call with different upper bits. Casting the stored byte to `signed char` at the call reproduces signed widening; the current candidate uses `MOVSX` at section offset `0x92F`. The known callee consumes the slot's low byte as a signed side, so this alone does not establish a gameplay-output difference. The complete command interpreter is still unselected and its whole comparison remains blocked by the separately unbound string-copy helper; no exact credit is claimed.
