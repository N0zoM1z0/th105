# AyaObject entry sequence-word ABI, 2026-10-19

Current code shares `AyaObjectActionView.hpp` between both AyaObject methods.
Initializer source is now fa06d792; the complete canonical payload remains
6f70b6f3. Earlier 5ca0fb42 receipts describe the preceding source epoch.

The4531-byte initializer at61F0B0 now differs from target in only two bytes.
Its local vslot+0C sequence parameter is `short`: this recovers all19 virtual
call preparations. The root remains nonexact and earns no exact credit.
A separate natural short-parameter witness reproduces the already-accepted
45C390 callee's entire202 bytes without changing the shared header.

## Target observations

The original Japanese1.06a executable SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable `[61F0B0,620263)` SHA256 is
`31c7399e608cfc6eb2a663ca53a99e6d8eaf12df221cbe1d0440cbed4ba919bd`.
All1195 instructions/4531 bytes are reachable through the32-destination
action switch; there are no unledgered direct targets or unresolved exits.
The one NOP and tables after RET620262 are outside callable credit.

AyaObject primary vtable6C624C, proved through COL6DB6FC, places45C390 at
slot+0C and this initializer at+3C. Its eight-entry RTTI hierarchy has AyaObject,
CharacterObjectEx<Aya,AyaObject>, CharacterObject, AttackObject and
AnimationObject at primary offset0, AnimationObjectBase at+4, Environment
at+130 and CObjectBase at+330.
The current method-prefix view does not reconstruct that full hierarchy.

At45C3E8 the sequence callee loads a full four-byte stack slot into EAX.
Every relevant use consumes its low word: TEST AX at45C3EC/45C40E, the
word publication at45C3EF, and modulo-low-word decrement/termination. EAX
is overwritten at45C419 before the next unrelated computation. RET4 at
45C457 confirms four-byte stack cleanup. The initial DWORD load alone does
not establish an original `int` parameter.

The old int-facing implementation explicitly casts the argument to short
both for publication and every loop test. Its accepted202-byte equality
therefore did not distinguish a wider source facade from a native narrow
parameter. Target observations establish low16-bit consumption; the coupled
caller experiment below supports the signed short source interpretation.

## Coupled caller and callee evidence

[The older scheduling note](AYA_ENTRY_VSLOT0C_SCHEDULING_2026_10_02.md)
identified11 CALL EDX sites. Complete current owner comparison finds another
eight CALL EAX sites in the same sequence-operation class. Each obtains its
method from vtable+0C. The old candidate delays MOV ECX,ESI until after
argument preparation; every target site prepares ECX earlier.

Changing only the local Aya view's sequence parameter from int to short
recovers all19 complete preparation sequences. No argument bits are patched,
instruction order is not forced, and the existing casts/decision bodies are
retained. Vtable order, receiver, four-byte argument slot, fields and root
void-return convention are unchanged.

The manual probe
`scripts/probes/animation-sequence-word-abi.cpp` uses a real short parameter
and ordinary `while (sequence != 0) { --sequence; ... }`. It inherits the
existing data prefix and calls the real tree lookup and virtual frame setter.
It needs no repeated cast in its loop and reproduces the complete202-byte
callee, including its ordinary receiver and RET4. This is an alternative
witness at an already-matched address, not a new function/byte claim.

Reproduce it using the existing unit's boundary and relocation contract:

```bash
scripts/compile-unit.sh scripts/probes/animation-sequence-word-abi.cpp \
  build/aya-entry-word-abi.obj
python3 scripts/compare-unit-object.py cross-v106a-animation-sequence-virtuals \
  build/aya-entry-word-abi.obj --address 0x0045C390 --json
```

This is a fresh manual compile followed by an existing-object comparison;
the latter does not attest build provenance or replace the default unit's
producer receipt. The comparator reports202/202, target/candidate SHA256
`dd6808825102feaf752f50030bba523485d6c03828599435509c2e09359abcd4`.
The shared int facade, its accepted implementation and all other callers
remain unchanged in this bounded checkpoint. No ABI rule is inferred for
another vtable implementation merely because it uses the same slot number.

## Complete selected root result

Selected source SHA256 is
`5ca0fb4209861320d3e69564de51cc53f0ced9ff062e30990c537f1b5b0bb104`.
The canonical4859-byte COFF payload SHA256 is
`6f70b6f354fdff459a628bdfbf0a7a3c12fe854a65f95f6cf33731b5d606b066`.
Code-prefix/table start remains4532; actual RET remains at4530. Comparison
of the **entire payload**, including every relocation and all metadata,
finds only these differences:

| Address / offset | Target | Candidate |
| --- | --- | --- |
| 61FCA7 /+BF7 | MOV ECX,[ESI+340] ModRM8E | MOV EAX,[ESI+340] ModRM86 |
| 61FCAF /+BFF | FLD dword [ECX+8] ModRM41 | FLD dword [EAX+8] ModRM40 |

Both instructions are in action856 before the real conversion helper. All
later bytes, branch displacements, helper identities and switch metadata
agree exactly. No opcode is normalized away for this finding. The owner
diagnostic rises13/33->31/33; action856 and the post-RET alignment owner
remain different. Counts or matching individual bytes do not confer partial
exact credit. Original action856 source lifetime/register choice is unknown.

```bash
python3 scripts/build.py --unit gpt-web-aya-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-action-entry \
  build/match-units/GptWeb_AyaObjectActionEntry.obj \
  --unit gpt-web-aya-object-action-entry --json
python3 scripts/ci.py
git diff --check
```

The first command intentionally remains nonzero at+BF7. Since the ordinary
machine changes are the19 commuting call preparations, the complete dataflow
comparison is more direct than a sampled replacement-helper execution.
No new native gameplay or exception-equivalence claim is made.

## Direct angle writeback and a closed native context

The selected source now writes800/810's angle fields directly before their
common selector tail. It removes the double `shared_angle` temporary, whose
only role was to copy an already loaded float. This source spelling remains
an inference. Its observed ordinary4859-byte payload is fully identical to
the preceding8f036434 source: the same two callable bytes differ, and no
metadata or helper/branch byte changes. No new exact credit is claimed.

This also changes the genuine `/GL`+`/LTCG` experiment. The selected5ca0fb42
source now has the target10h local frame,4532 metadata start, and full4859
byte envelope in a real diagnostic DLL. It closes through seven ordinary
source-provider units and CRT startup, with no invented caller, code stub,
ABS code binding or execution. The quantized lookup definitions are genuinely
compiled with the same private float return declarations as their consumers;
there is no float/double symbol alias. Fresh paired compilation verifies that
the float/double variants' complete94/88-byte raw sections and symbol/addend
relocation inventories agree. This source-to-source correspondence does not
accept either helper against target; their known nonexact status remains.
The sole same-target function alias joins the two receiver-only names for
596370. Shared sources, compiler profiles and accepted helpers are unchanged.

Independent linked replay checks all188 owned relocation fields:60 REL32
edges (59 CALLs and the qualified596370 tail),94 numeric literals, two table
addresses and32 internal code pointers. All128 PE HIGHLOWs match the DIR32
inventory. Every direct edge reaches its named real provider; literal bits,
widths and read-only storage and local pointer roles agree before replay.
All other instruction/data bytes agree with the ordinary object. The envelope
comes from the qualified ordinary COFF extent and reconciled CFG, rather than
an assumed next-MAP-symbol function boundary. Callable credit remains4531
bytes; the one NOP and327 metadata bytes remain outside it.

The resulting payload is again6f70b6f3 with only the two ModRM differences.
This closes the previous frame/envelope obstacle for this diagnostic context;
it does not explain the remaining register choice or prove an original TU.
The source CIL owns the exported entry10001000. Producer and replay receipts
are under `build/aya-entry-registers/link/`; link receipt SHA256 is
`aa06891c8b520ccd0bf129233aacc61c4810095cf5cf1592bbc9ae8bcca82e20`.
The private diagnostic reproduction is
`python3 -B build/aya-entry-registers/link-context.py` followed by
`python3 -B build/aya-entry-registers/audit-link.py`; this is not an accepted
linked-unit command.

Fresh unselected source controls on8f036434 are also recorded there. Explicit
856 active-branch joins, expanding its target pointer reads, and the two852
chained scale assignments each retain the full6f70b6f3 payload. A real two-float
direction value instead changes the frame10h->18h and85 callable bytes.
Combining852 chains with the already rejected float copy gives4540/4867
prefix/payload. A signed64-bit sequence conversion introduces `_ftol2`;
canonicalization rejects that unbound REL32 in both856-only and all-call
forms, including explicit final narrowing. Target68A1A0 instead has an SSE2
CVTTSD2SI EAX path and a fallback branch. No `_ftol2` binding is invented.

A fresh direct read-only Ghidra pass independently checks file/imported
identity, entry, the complete mapped text and this4531-byte root before
semantics. Temporary thiscall/void/body metadata is read back, and bounded
800/810/856 pcode and decompiler output remain hypotheses. All nine primary
DB hashes remain unchanged and the project alias is removed. The384MiB,
CPU0/nice10 script/output are under `.analysis/aya-entry-registers-20261019/`
and `build/aya-entry-registers/`. No IDA semantics, factory adapter or target
patch is used.

A final getter control on the selected5ca0fb42 source replaces only856's
selector input with a real forced-inline member returning, respectively,
float value, const float reference, or const float pointer. Each compiles
and preserves the complete6f70b6f3 payload, all19 conversion calls and the
same two differences. None is selected and no original getter API is inferred.
Fresh baseline, sources, commands and full packets are under
`build/aya-entry-getter/`. Further unchanged source-API tuning is deferred
pending new ownership/TU evidence.

## Exact-first refresh, 2026-10-23

A fresh configured build on selected source SHA256
`5ca0fb4209861320d3e69564de51cc53f0ced9ff062e30990c537f1b5b0bb104`
still produces the complete4859-byte payload6f70b6f3 above. Only+BF7/+BFF
differ; callable4531, all19 conversion preparations and metadata are unchanged.
IDA preflight again rejects its open database; no IDA semantics are used.

Thirty complete native source controls were compiled serially on this epoch.
Twenty-five valid controls are fully payload-identical: typed payload records,
real conversion/getter APIs, used reset-zero values, short/implicit856 arguments,
local903 scalar lifetime, full856 member/free-function inlining, and typed
pointer/sequence reference accessors. Each helper uses its real inputs; no
out-of-line code binding, dummy local or target-register prescription is added.
Three controls are worse: split800/810 heading ownership differs at four bytes,
an unsigned sequence field at six, and a pointer-value accessor at94. None fixes
the two original bytes. These are tested source forms, not impossibility proofs.

The remaining two controls require different qualifications. Pragmas placed
inside856 emit **C4177** (global/namespace scope required): their byte-neutral
result does not test local floating-environment constraints. A correctly placed
namespace-scope pragma around the complete root emits4863 bytes and a new
unmapped `__real@43020000` relocation. Formal replay stops there; no binding or
full canonical hash is invented for that object.

The earlier `/Zi` failure is now resolved in a private tooling context. Matching
SP1 compiler/PDB components (14.0/8.0.50727.762) use the task-specific native
PDB endpoint `th105_entry_vc8_20261023` in this repository's Wine prefix. Wine's
missing NTLM helper was supplied by locally extracting verified Ubuntu packages,
without a system install or daemon. The helper is Samba4.19.5; package versions
and digests are in `.tools/pdb-ntlm/{receipt,dependency-receipt}.json`.
With the same native profile plus `/Zi`, compilation exits0 and creates a real
object and PDB. The full payload is again6f70b6f3 with only+BF7/+BFF different.
This is an actual negative `/Zi` result; the old C1902 failure was not one.
No other repository's PDB server was stopped or reused.

Recipes: `.analysis/aya-entry-payload-view-20261023/`. Frozen controls and
receipts: `build/aya-entry-payload-view-20261023/`, starting with `controls.json`,
`scalar-views.json`, `lifetimes.json`, `field-views.json` and `zi-isolated.json`.
The latter pins all six compiler/PDB inputs, the command, source, object and PDB;
receipt SHA256 is
`011e80269fdd775a9c6747473e765aa1ba057db69cc441bcaad971b4b95cee8f`.
Completed source/object payloads are compressed with a verified retention list.
Public source, unit, compiler profile and match ledgers remain unchanged.
No new exact credit, native execution or aggregate replay is claimed. Further
progress needs a different target-backed source/TU lead, rather than repeating
these byte-neutral forms or importing TH075's VC7.1 `/Od` profile.

## Full hierarchy and compiler controls, 2026-10-24

Fresh configured compilation retains source 5ca0fb42 and the complete 4859-byte
payload 6f70b6f3. The 4531 callable bytes still decode to 1195 instructions/32 RETs;
the single NOP and all 327 metadata bytes agree. Only +BF7/+BFF differ. No new
exact result, runtime matrix or aggregate replay is claimed.

Raw COL `0x6DB6FC` points to CHD `0x6DB710`, whose base array contains eight entries.
All PMD vbptr displacements are -1. In array order, the observed member offsets
are 0,0,0,0x330,0,0,4,0x130: AyaObject, CharacterObjectEx<Aya,AyaObject>,
CharacterObject, CObjectBase, AttackObject, AnimationObject,
AnimationObjectBase and Environment. The earlier prose summarized six entries;
it was not the complete base array. The last two data bases matter when
testing a physical class view rather than a virtual-prefix-only inheritance.

A private C++ view now represents these data-bearing bases, preserves the
selected field types/operations and checks the observed sprite, environment
and non-primary-base offsets at compile time. Its Animation/Attack/Character
prefix sizes are158h/330h/348h; these are view constraints, not proof of a
complete Aya allocation. No instance, constructor or replacement vtable is
created. The entire 4859-byte result still equals 6f70b6f3. This tested physical
hierarchy does not explain the two register bytes or recover original fields.

Two documented compiler controls on the unchanged selected source, `/Oi-`
and `/Ob1`, each retain the same complete payload after a manual default-profile
parity build. Neither emits an ignored/overridden-option warning. A negated
active-state exit in 856 is also byte-identical; a switch-based gate instead
produces 4851 bytes, first differs at +7F and retains the original register
differences. It is rejected. No public source or compiler profile changes.

Compiler-release uncertainty remains distinct from these results. The installed
cl/c1xx/c2 components are 14.00.50727.762. Microsoft separately documents C2
[14.0.50727.3080](https://support.microsoft.com/en-gb/topic/fix-when-you-run-an-application-that-is-built-by-using-the-ot-compiler-option-in-microsoft-visual-studio-2005-service-pack-1-sp1-some-if-statements-may-run-incorrectly-270601b8-04f6-f517-0c20-38e6de2740d7),
[14.0.50727.4025](https://support.microsoft.com/en-us/servicing/visual-studio/hotfix/2017/01/fix-error-message-when-you-build-a-project-that-has-a-very-large-function-in-visual-studio-2005-serv)
and [14.0.50727.5587](https://support.microsoft.com/nb-no/servicing/visual-studio/hotfix/2017/01/fix-errors-occur-after-an-exception-is-thrown-or-a-declspec-noreturn-function-is-executed-when-you-r).
This corroborates later releases, not their use by TH105 or applicability to
these register choices. No later backend binary was recovered or compiled here.
The target PE timestamp 2011-10-24 is metadata, not a compiler-version proof.
The tested archive inventories and failed mirror requests are retained; they
do not establish that no authentic package is obtainable elsewhere.

Recipes: `.analysis/aya-entry-hierarchy-20261024/`. Artifacts:
`build/aya-entry-hierarchy-20261024/`; start with `rtti.json`,
`baseline-build.json`, `baseline-packet.json`, `physical-hierarchy.json`,
`profiles.json`, `gates.json` and `compiler-provenance.json`. Raw observations,
source hypotheses, actual compiler negatives and untested release candidates
are kept separate. The function note now supersedes its old `/Zi`-failure text.
Completed control sources/objects/payloads are compressed after full member-hash
verification; `retention.json` lists the archive and exact restore command.

### Source order, TU and floating profiles

Fourteen new source/TU controls and three explicit floating profiles were
compiled serially from selected source 5ca0fb42. Ten retain the complete 6f70b6f3
payload: numeric case-group order, signed/unsigned normalized switch indices,
four uses of existing heading/scalar temporaries, both adjacent Aya member-source
TU orders, and `/fp:precise`. An unsigned-WORD index adds a third difference at
+0xA: target MOVSX versus candidate MOVZX. None is selected.

Moving 856 first in the switch changes which branch gets the ECX operand.
Its 406-byte/106-instruction owner becomes instruction/edge-identical, including
the ECX pointer, while 803 acquires two register-operand differences. Whole
payload comparison still differs at 3154 bytes. Three other placements are also
worse. The owner diagnostic is not byte-exact acceptance or a compiler barrier.

Compiling the complete initializer and adjacent event bridge together, in either
source order, retains the two root differences; the existing event witness
`0x6203B0` remains 1177/1177 exact in both objects. The common-receiver test below supersedes this earlier two-source context.

`/fp:fast` compiles a 4771-byte section with an unbound `__real@43020000`;
`/fp:except` compiles 4623 bytes and introduces `_ftol2_sse_excpt`, whereas the
target calls `_ftol2_sse`. Full replay correctly stops at those dependencies;
no canonical hash or replacement binding is invented for either object.

Compiler discovery recovered the [archived Connect page DownloadID32789](https://web.archive.org/web/20101225182105/http://connect.microsoft.com/VisualStudio/Downloads/DownloadDetails.aspx?DownloadID=32789) and the
actual Visual Studio 2005 mirror forum44; the old blog linked forum43 (2008).
Listed hotfix topics do not supply recovered binaries. The [official KB932232
Vista package](https://www.catalog.update.microsoft.com/Search.aspx?q=932232) was
hash-verified and its 55 CAB members inspected; no C2 payload was recovered.
It was never executed and its temporary payloads were removed.
No later C2 version was compiled. Empty unvalidated wildcard searches and failed
requests do not establish package absence.

Recipes: `.analysis/aya-entry-backend-20261024/`. Start with `packet.json`,
`family-contexts.json`, `floating-profiles.json` and `vista-package.json` under
`build/aya-entry-backend-20261024/`. Completed proofs and archived web pages are
compressed with verified member hashes and the restore command in `retention.json`.
Public source, compiler profiles, accepted units and exact ledgers are unchanged.

## Shared receiver and handoff cleanup, 2026-10-24

One partial `AyaObjectActionView` now replaces the two duplicate class prefixes.
It binds the update definition to virtual slot+28, keeps initializer slot+3C,
and consistently declares short at+0C. Fifteen observed offsets and the388h
represented prefix are checked at compilation. No view is constructed or embedded.
Aya's constructor publishes primary vtable6C62D4 at61861C; both it and AyaObject
6C624C bind+0C to45C390. The two casts through fighter_owner retain that common
slot ABI. Original complete class layout and TU identity remain unknown.

Six complete source/ABI controls precede the selection: the short update alone,
both separate views together, unified int, two unified short source orders,
and a nonvirtual-update calibration. Every short form retains both payloads;
the int initializer regresses to b4f36926/83 differences. The selected shared
header and member qualifications retain both complete old payloads: initializer
4859/6f70b6f3 and update20000/5f2966cb. Update source is now15a6f13a; shared-header
SHA256 is2ed12ce9. Runtime matrices were not rerun.

A private TU also defines the real frame/phase member bodies under that receiver.
Both definition orders reproduce4351C0 (62 bytes) and64CD00 (73 bytes) exactly.
Its update has11 direct frame calls rather than12, but grows to20032 bytes,
canonical23925cd4, and still differs at+22. The initializer retains its two
register bytes. This candidate is unselected and earns no new exact credit.
Comparing that removed frame-call site with the target is a retained lead.

The new header is consumed only by the two nonexact Aya units. No global
relocation, compiler profile, accepted source or match ledger changed.
Recipes and frozen pre-cleanup inputs: `.analysis/aya-joint-owner-20261024/`
and `build/aya-joint-owner-20261024/`. Start with `summary.json`; completed
controls are compressed after member-hash verification, with restoration in
`retention.json`. Current selection and continuation steps are in `RE_HANDOFF.md`.

## Whole-payload refresh and release search,2026-10-25

A fresh serial SP1 build of the unchanged selected source reproduces the
complete **4859-byte** payload:4531 callable bytes, one alignment byte and327
metadata bytes. Canonical SHA-256 is
`6f70b6f354fdff459a628bdfbf0a7a3c12fe854a65f95f6cf33731b5d606b066`;
target payload SHA-256 is
`e7667d2ccbd8681049553b243f9aac7405419fa4a732136f953ed86549b2ef76`.
The full replay has only two unequal bytes:61FCA7 native8E/candidate86 and
61FCAF native41/candidate40. These select ECX versus EAX for the action856
heading pointer. The alignment byte and all327 metadata bytes agree.
There are no masks, relocation omissions or new exact claims.

Reproduce the focused build with
`scripts/repo-python scripts/build.py --unit gpt-web-aya-object-action-entry --compare --json`
(expected exit1). Private full-section replay and hash-pinned input receipt:
`.analysis/aya-entry-backend-20261025/baseline.py` and
`build/aya-entry-backend-20261025/baseline-packet.json`. Selected source/header
hashes remain fa06d792/2ed12ce9. No source, header, unit, compiler profile or
relocation ledger changed during this refresh.

Microsoft's retained release tables independently document later C2 versions
[14.0.50727.3080](https://support.microsoft.com/en-gb/topic/fix-when-you-run-an-application-that-is-built-by-using-the-ot-compiler-option-in-microsoft-visual-studio-2005-service-pack-1-sp1-some-if-statements-may-run-incorrectly-270601b8-04f6-f517-0c20-38e6de2740d7),
[14.0.50727.4025](https://support.microsoft.com/en-us/servicing/visual-studio/hotfix/2017/01/fix-error-message-when-you-build-a-project-that-has-a-very-large-function-in-visual-studio-2005-serv)
and [14.0.50727.5587](https://support.microsoft.com/en-us/servicing/visual-studio/hotfix/2017/01/fix-errors-occur-after-an-exception-is-thrown-or-a-declspec-noreturn-function-is-executed-when-you-r).
Their release existence does not establish which backend built TH105, or that
the documented defects explain this register choice. No executable compiler
package was recovered or executed. The final metadata-only Internet Archive
item searches returned only ordinary SP1/Express items, not a later backend;
their limited scope is recorded in `build/aya-entry-backend-20261025/archive-items.json`.
Earlier KB932232 payload inspection already established that package has no
C2 member; it was not repeated. Archived support/download pages alone do not
attest a compiler binary. Keep this release question parked until an authentic
package can be recovered; do not repeat the closed source/flag controls.

## Rejected controls and analysis limits

The saved pre-change baseline is sourcec9d1abb5, canonical payloadb4f36926.
Pinned RTM, embedded debug information/Z7,19 explicit int argument carriers,
an inherited virtual-prefix view, a discarded-return declaration and an
action856 heading-pointer local are fully payload-identical on that input.
That earlier /Zi attempt failed C1902 in its PDB manager and was not a codegen
result. The successful current-epoch /Zi refresh above supersedes that blocker.

After the short fix, direct/explicit short conversions, inherited virtual
prefix, local/shared heading carriers and real shared scalar carriers leave
the same two bytes. An unsigned-short parameter changes the frame and removes
the19 conversion-helper calls, so it is not selected. Narrowing the real
float-copy-only shared_angle alias to float adds eight bytes and is rejected.
Do not repeat these unchanged controls as if the source context were new.

The earlier action856 pass started from source8f036434 and retained the
same6f70b6f3 payload/two differences. A double Y-offset literal, direct
angle-argument expression, EHa exception model, generic copied-word storage
with real float reads, and a layout-checked multiple-inheritance model are
each fully byte-neutral. The latter preserves a330-byte primary prefix,
an8-byte secondary base at+330, and the observed338/340/348 fields; it is
a source-layout control, not proof of the original complete class definition.
A genuine repeated conversion/virtual operation fails the normal comparator
when emitted out of line; no invented binding is supplied. Its inlined
control is also fully payload-identical.

A real sequence-word snapshot changes prefix/payload to4524/4851 and no
longer has the target comparison structure. Explicitly widening the returned
angle before negation adds the non-target materialization,4540/4867.
Combining an unsigned formal with explicit signed conversion still produces
the previously rejected5052/5379 payload without the19 conversion calls.
None of these controls is selected. No register-normalized acceptance,
source change, native claim or exact credit follows. Receipts are under
`build/aya-entry-action856/`; the new bounded read-only Ghidra pass under
`.analysis/aya-entry-action856-20261019/` leaves all nine DB hashes unchanged
and removes its alias.

The earlier /GL diagnostic used seven actual source-provider objects, real
static CRT/SDK libraries and real DLL startup. The old baseline and preserved-type
short sources both acquired an aligned EBP frame, unlike target. The short
source fixes the call preparations even there. A float-copy variant restores
the entry frame but retains the wrong4540-byte metadata boundary. Linked
images are neither executed nor accepted; preliminary table/CFG inspection
does not claim full linked relocation or tail qualification.

The link has no placeholder functions, unresolved overrides, fabricated
callers or absolute code bindings. Its only function alias joins the two
source names for the real596370 receiver-only operation. Six direct engine
providers compare exact;596370 and the two quantized lookup providers retain
their known nonexact status. For a coherent private float lookup declaration,
changing only the two return declarations preserves their full94/88-byte
COFF sections and relocation inventories. This does not accept those helpers
or modify their public sources.

Private reports, pinned input receipts, RTTI, complete byte/slot comparison
and genuine-link recipes are under `build/aya-entry-context/`. Direct Ghidra
independently verifies imported identity, entry and all mapped text bytes.
Its primary project initially has no Aya function; bounded read-only decoding
of the1195 attested instruction starts and a4531-byte temporary function
supports a decompiler hypothesis, whose unreachable-block warnings do not
override the raw CFG. All nine DB files remain unchanged and the temporary
project alias is removed. CPU0/384MiB recipes are under
`.analysis/aya-entry-context-20261019/`. Required IDA preflight rejects its
wrong target; no IDA semantics or factory adapter is used.
