# ReimuObject entry initializer, 2026-10-19

## Target observations and boundary

The original Japanese TH10.5 v1.06a executable SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
ReimuObject primary vtable6C40A4 has complete-object locator6D9C8C and
type descriptor6E7E2C, whose name is `.?AVReimuObject@@`. Slot+3C points
to4A1CE0; slot+0C independently points to the reviewed selector45C390.
This supports the durable name `ReimuObject_initialize_action_entry` and
the local selector's short argument. The source view is not an original
symbol-name or complete inheritance claim.

The reviewed callable is `[004A1CE0,004A2FFC)`,4892 bytes, SHA256
`1cda9c10ed7d9ab2225800db60a62f45099c7cd3d7adec15621bfa3a49b8e6c1`.
All1325 instructions/4892 bytes are covered by raw CFG traversal. There
are39 RETs,65 direct CALL sites to ten helpers, and one independently
registered external tail: JMP596370 at4A2F8B. ECX retains the receiver on
that path; the function otherwise uses ordinary thiscall with no stack
arguments and a10h local frame. The last RET is4A2FFB. The next byte begins
switch data, not another instruction owned by this callable.

The primary dispatch4A1D6C indexes42 DWORD destinations at4A2FFC through
the200-byte action800..999 index table at4A30A4. Seven sequence dispatches
complete the raw CFG:

| Action | Dispatch | Table | Entries |
| --- | --- | --- | ---: |
|869|4A27EB|4A316C|6|
|903|4A2BC2|4A3184|6|
|904|4A2C99|4A319C|6|
|905|4A2D81|4A31B4|6|
|906|4A2E37|4A31CC|6|
|907|4A2E8C|4A31E4|5|
|908|4A2EF8|4A31F8|10|

The180 bytes in these auxiliary tables end at4A3220. All destinations and
dispatches are pinned in `config/giant-action-switches.toml`; the public
owner audit reaches all4892 bytes with no unreached range, unledgered direct
target or unresolved indirect exit. These548 adjacent metadata bytes are
structural evidence and receive no callable-byte credit. Origin remains the
existing observed authored ReimuObject vtable classification.

## Source reconstruction

`src/characters/ReimuObjectActionEntry.cpp` is a complete hand-written C++
candidate for all42 primary destinations, including the default. It uses
the current target-backed sprite/Object prefix and offset/size assertions,
ordinary virtual calls and the existing typed helper interfaces. It does
not paste the decompiler's casts or invent a callee for an intrinsic cast.
The unit is `gpt-web-reimu-object-action-entry`, kind `probe`; implemented
means source-present and the exact ledger remains unchanged.

Target checks distinguish positive-only heading[2] guards from nonzero
guards, the unconditional selector calls, and851/856's heading[0] selector
input. NaN/unordered branches are interpreted from FCOM/FNSTSW/TEST parity,
not from pseudocode alone. Other reviewed details include signed owner skill
bytes605/60E, the phase byte at184, the animation word174, byte113, and the
unsigned MT remainder. Action869 writes scale+120 twice, with a real RNG
call between stores at4A28CB/4A28F9. Both writes remain in source.

The source's direct CALL multiplicities agree with the raw target:

| Target | Role | Sites |
| --- | --- | ---: |
|68A1A0|VC8 x87-to-int conversion entry|26|
|4067D0|selector RNG|25|
|4FCA60|parented related-object request|3|
|64CCB0|unparented related-object request|2|
|435160|oriented motion components|4|
|496420|secondary animation replacement|1|
|4066B0|MT19937 next|1|
|4063D0/406360|quantized cosine/sine|1 each|
|406540|atan2 degrees|1|

The quantized lookup implementations remain nonexact, and their existing
double-return interfaces remain hypotheses. Call-count agreement does not
prove source semantics, original return precision, or complete exactness.
No new whole-root native/execution proof is claimed.

The initial candidate retained all65 calls and42 distinct owners, with25/43
instruction/edge diagnostics. Replacing the observed sequence snapshots in
866,901 and902 with ordinary switches and using the observed signed skill
comparison reaches29/43. The900 switch and further target-backed lifetimes
and rounding recover seven more, for36/43 with no previously equal owner lost:

- 801/810 share a real captured heading pointer across their common
  zero-scale/angle/positive-sequence tail. This restores their pointer-load
  timing and incoming edges.
- 822 rounds its random*0.1 product into a real float before adding2.0 to
  form vertical velocity. A local float for the complete sum was insufficient.
- 861 converts the unsigned MT remainder directly to float, adds40.0f, then
  stores the used float speed. A separate float-return helper introduced an
  extra rounding pair; double conversion changed the correction literal's
  width. The direct expression reproduces the full59-byte owner.

The newly required literal alias `__real@437f0000` pins float255.0 to6C4310
with bytes00007F43. Existing relocation keys are unchanged; no older unit
explicitly references this previously absent key. Shared headers, compiler
profiles and accepted helper sources are unchanged.

## Chained scale writeback and sequence-table order

**Observed:** the earlier36/43 source7f12f5c1/payload14a90e9d shares822's
last scale/return tail with901 while owning an extra903 copy. Five natural
x-then-y chained assignments replace the corresponding local float carriers:
one in822's5/6 path and four in903/904. They preserve the target field write
order, `y = x = expression`, and reproduce the target822/903/904 copying and
scheduling. This source form is an inference; the resulting target instruction
and edge agreement is observed. No original source spelling is claimed.

Changing903/904 alone gives prefix/payload4864/5412, canonical SHA256
`ad776ae9d6159bf0ab584c3b5406ae24e09cfc19472bb75119420d8d080c6ab6`.
Those two owners then differ only in their auxiliary table addresses;822
still lacks its28-byte copy. Adding822's corresponding chained writeback
restores prefix/payload4892/5440 and all1325 instructions/39 RETs, reaching
40/43 diagnostics with no previously equal owner lost. The four additional
owner diagnostics are822,903,904 and the final default/802 owner. Its callable
now ends at4A2FFC without candidate post-RET alignment inside the comparison.

The combined five-chain payload is12c13a63. Exporting the complete section
also exposes11 differing metadata bytes that the owner count does not include.
Listing908's4/7 group after its5/2/8 and6/3/9 groups follows the raw physical
tail order. This leaves every callable byte unchanged while correcting all
of908's auxiliary DWORDs. Only906's three auxiliary entries remain different.
Compiler metadata remains outside authored callable credit, but its edges
are retained as a separate reconstruction obligation.

## Explicit shared sequence edges

**Observed:** target906 sequence2/5 enters908's angle tail at4A2F15;
sequence3 enters its other angle tail at4A2F31. The preceding source leaves
these as duplicate statements, and VC8 chooses different suffixes. Explicit
`goto shared_sequence_angle_2` and `goto shared_sequence_angle_3` edges from
906 into the corresponding908 case bodies express these already observed
joins. No calculation, return value or field write is added.

This restores every one of the548 adjacent metadata bytes, including all
three previously differing906 entries. It also restores908's pointer-load,
phase-byte and epilogue schedule without a separate source change to4/7.
The callable remains4892 bytes/1325 instructions/39 RETs/65 direct CALLs;
its body differences fall30->14. Owner diagnostics rise40->41/43, with all
previously equal owners retained. The exact ledger receives no partial credit.

The selected source is3803a002; its complete canonical payload is65298d36.
On this joined source, capturing906/999's selector input pointers in the
already used shared parameter local, capturing906's angle pointer, using the
independently checked physical class hierarchy, and moving906's local4 case
first all reproduce the same complete65298d36 payload. They are unselected.

## Selector result and genuine link-context controls

**Observed, raw target:**45C390 reads the low-word sequence argument, updates
its sequence state, and forwards to vslot1C without constructing an integer
status. Slot1C is45C180, which writes the frame word and calls45C110;
45C460 is the separate reset-sequence function.45C110's successful frame
application tails to436760; the inspected final transform paths tail to the
already exact void24-byte4073C0 sprite commit. Residual EAX contents alone do
not uniquely establish an original integer return type for this chain.

A private natural `void select_sequence(short)` implementation, ending in
`void set_sequence_frame(short)`, compares202/202 at45C390, canonical SHA256
`dd6808825102feaf752f50030bba523485d6c03828599435509c2e09359abcd4`.
This is a manually compiled alternate ABI witness; the existing-object
comparator explicitly reports build provenance unverified. It is not a new
accepted unit, a unique return-type proof, or new exact credit. On the prior
30-byte-difference large root, changing its discarded selector result from
int to void leaves the completea72cf4f1 payload unchanged. Shared selector
headers and implementations remain unchanged.

Other controls on that preceding root are also bounded negatives: VC8 RTM
and SP1 give the same completea72cf4f1 payload; explicitly naming the two
velocity floats in a local sprite layout is byte-neutral. Reading908's angle
into a float before its phase store adds32 callable bytes, for4924/5472
prefix/payload, and loses the target tail sharing. It is not selected.

**Observed, genuine diagnostic link:** the selected3803a002 root compiles
with `/GL` and links with `/LTCG` into a DLL through real ordinary provider
objects and the default CRT DLL startup. There is no invented entry caller,
code stub, ABS code binding or execution of this diagnostic image. The ten
provider units plus a private full texture-size provider close the actual
code dependencies. The latter implements raw404E60 behavior: null-handle
256x256 fallback, D3D lock,417800 lookup, virtual surface acquisition and
description, width/height copy, Release and unlock. It remains unselected.
Only existing hash-attested nonexecutable globals use ABS data bindings.

The actual quantized lookup providers return double. For this diagnostic
partition only, the oriented-motion provider's two float lookup declarations
are refined to double to make source declarations agree with their definitions;
no float/double symbol alias is allowed. Its57-byte comparison then differs
at+26/435186. The lookup pair,596370 and417800 providers are also nonexact.
This context does not establish their exactness or original source partition.
The other same-target aliases change local view names without changing the
signature. No shared production declaration or accepted helper is edited.

The linked export is10001000 and MAP assigns it to the source CIL root.obj.
Its ordinary COFF extent, reconciled callable boundary and complete metadata
establish the5440-byte envelope; a next-MAP-symbol distance is not used as a
function boundary. All nonrelocation instruction/data bytes agree with the
ordinary object. Independent replay checks all247 owned fields:66 REL32
edges (65 CALLs and the already qualified596370 tail),85 immutable numeric
literals,9 metadata addresses and87 internal code pointers. The PE's181
HIGHLOW entries agree exactly with the DIR32 inventory. Every direct edge
reaches its named real provider; literal bytes/widths and local pointer roles
are checked before canonicalization.

The resulting canonical payload is again65298d36:14 differing callable
bytes, zero differing metadata bytes, and the same10h local frame. This
particular closed LTCG context therefore does not explain the remaining
register allocation. It neither proves an original TU nor excludes another
faithful context. The producer/auditor and receipts are under
`build/reimu-object-entry-abi/`; final link receipt SHA256 is
`4f3cb994c934308525fb80ae065700280a51bf6eac0c76e8e937bab4ae87c6a9`.
Reproduction of this diagnostic observation is
`python3 -B build/reimu-object-entry-abi/link-context.py` followed by
`python3 -B build/reimu-object-entry-abi/audit-link.py`. It is not an accepted
linked-unit command or whole-root execution proof.

## Independently observed inheritance and bounded controls

Raw COL6D9C8C and its descriptors establish eight RTTI entries, including
the complete object; every PMD uses pdisp=-1/vdisp=0. Direct read-only Ghidra independently corroborates the names
and offsets, checks each descriptor/name record against file-backed PE bytes,
and re-attests executable identity, entry, mapped text and this root:

| Type | Base descriptor | Offset from complete object |
| --- | --- | --- |
|ReimuObject|6D9CD4|0|
|CharacterObjectEx<Reimu, ReimuObject>|6D9C28|0|
|CharacterObject|6D9BAC|0|
|CObjectBase|6D9BC8|330h|
|AttackObject|6D94F8|0|
|AnimationObject|6D76DC|0|
|AnimationObjectBase|6D76F8|4|
|Environment|6D7748|130h|

A private C++ view reproduces this inheritance layout, including the real
AnimationObjectBase/CObjectBase members and assertions at4/130h/330h and
sizes158h/330h/348h/388h. On the36/43 source its complete canonical payload
is identical to14a90e9d. It is not selected; the minimal flat runtime view
remains adequate for the tested code generation. This does not recover the
original complete class declarations or every unused virtual slot.

All following controls remain unselected and phase-scoped:

- On the36/43 source, a real shared903/904 scale local and replacing all40
  outer-switch returns with breaks each retain the full14a90e9d payload.
- Local `float_control(except, on)` compiles but introduces
  `_ftol2_sse_excpt`, outside this unit's proved relocation contract. Both
  public comparison paths fail closed with an unknown REL32 target. No
  binding to68A1A0 or another entry is invented; this control has no accepted
  canonical result. It differs from the earlier fenv-access experiment.
- On the40/43 five-chain source, a908 pointer capture inside4/7, the906 byte
  access through the high byte of sprite color storage, direct short selector
  arguments in906/999, a real999 double value capture, and an ordinary
  inlined phase/angle setter each retain the full12c13a63 payload.
- Sharing one post-selector heading pointer across908's inner switch gives
  prefix/payload4904/5452 and32/43 diagnostics. It is not selected.
- Moving906's local4 case first changes auxiliary aliases but leaves the
  callable unchanged and three entries wrong. Direct returns from906's
  inner cases preserve the selected fulla72cf4f1 payload. Neither is selected.

The384MiB/CPU0 Ghidra hierarchy session leaves all nine primary DB file hashes
unchanged; its project alias is removed. It writes no durable metadata and
produces no new decompiler/native proof. Raw packets, complete trial sources,
comparison receipts and the checked hierarchy script remain under
`build/reimu-object-entry-lifetimes/` and
`.analysis/reimu-object-entry-lifetimes-20261019/`. No shared header, helper
implementation, compiler profile or relocation binding changes.

## Joined-source register and argument controls

The following fresh controls use the selected3803a002 source and pinned
VC8 SP1 compiler. Its public unit is rebuilt first; full-callable comparison
still starts at+1140/4A2E20. No control below is selected, and no shared
source/header/profile/binding changes.

- Expanding the used unsigned-RNG float conversion directly at its call sites
  preserves the entire65298d36 payload. Merely replacing force-inline with
  ordinary inline leaves a real local `unsigned_random_as_float` CALL;
  canonicalization rejects that unknown REL32 instead of inventing a target.
- Discarded selector result void, named short argument values in906/999,
  implicit float-to-bool guard spelling in906, a local typed BGRA color member
  for the observed byte113 stores, `/GS`, and `/O2 /Ob1` each preserve the
  complete65298d36 payload. The latter flag follows `/O2` in the tested command.
- Declaring the selector's argument int preserves prefix/payload4892/5440 and
  all metadata, but expands callable differences14->113, first+1B3/4A1E93.
  Unsigned short changes prefix/payload to6244/6792 and frame10h->14h; only one
  of the original26 ftol2_sse direct calls remains. These are caller codegen
  evidence supporting the retained signed-short view under the tested profile,
  not a unique original-prototype proof from a low-word consumer alone.
- Capturing906's float selector value before its guard gives4908/5456
  prefix/payload. Moving999 before906 in source gives4896/5444. Neither
  preserves the target layout.

Raw auxiliary entries independently show that905 and907 also enter the
4A2F15/4A2F31 angle tails. Making905's two angle joins explicit leaves all
metadata equal but increases body differences to16; doing so for907 alone
increases them to40 and changes three905 table entries. Both together give27
body differences with all metadata equal. Thus the successful906 source
recipe is not a general instruction to replace every duplicated angle store.

The shared state-one destination4A2EFF is observed in905..908's tables and
902's JLE at4A2B09. Explicit state-one joins from905..907, with or without902,
give4896/5444 prefix/payload; combining all these state/angle joins gives the
same27-byte-difference payload as the two extra angle joins alone. These
controls do not close the remaining906/999 allocation. Keep the selected
41/43 source and the original full-equality gate.

Sources, commands/tool pins, objects, canonical exports and failure logs remain
under `build/reimu-object-entry-registers/`. All VC8 builds run serially on
CPU0/nice10. Target PE identity and tracking pass; IDA preflight again reports
the wrong10350095 database and no IDA semantics are used. No new analysis
DB, native execution proof, exact credit or cold aggregate claim is produced.

## Current strict result and open questions

Selected source SHA256:
`3803a002807ee0a329e9721c4e814bc11159711e6dc515afbf2e88a5df7fd6dd`.
The complete canonical5440-byte section payload SHA256 is
`65298d3670c2c739162abc2d7172dc3db194835b05eedd407688a0b5e3be1347`.
Both callable bodies end at4A2FFC; both metadata starts are+4892. All65 direct
call sites,39 RETs and1325 instructions retain their target multiplicities.

Strict full-callable comparison remains nonexact at+1140/4A2E20, target57 /
sourceCE, in the selector-call preparation. There are14 differing callable
bytes, with no partial byte credit. All earlier40 equal owner diagnostics
remain equal;41/43 now agree. The remaining owners are:

| Owner | Unclosed physical difference |
| --- | --- |
|906|Virtual-call preparation and heading-pointer register in its4 angle path|
|999|Heading-pointer and selector-call registers/preparation|

All548 metadata bytes now agree:42 primary destinations, the200-byte index
and all seven auxiliary tables.906's2/5 destinations are4A2F15 and its3
destination is4A2F31 in both images.908's phase-store/pointer-load schedule
is now identical. Only the906/999 register/call preparation above remains
open; complete equality is still required before exact credit.

On the earlier36/43 source, a private whole-function `fenv_access(on)` control
regresses to9/43 with prefix/payload4948/5496 and is unselected. Original
remaining sharing, exception delivery, value lifetimes and TU/LTCG context
remain unknown. Preserve full callable acceptance and existing alias gates.

## Reproduction and analysis safety

```bash
python3 scripts/build.py --unit gpt-web-reimu-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py reimu-object-action-entry \
  build/match-units/GptWeb_ReimuObjectActionEntry.obj \
  --unit gpt-web-reimu-object-action-entry --json
python3 scripts/validate-tracking.py --require-target
python3 scripts/ci.py
git diff --check
```

The strict root comparison intentionally returns nonzero. Final packets,
the initial and corrected source snapshots, canonical exports and rejected
environment control are under `build/reimu-object-entry/`. The roster shared
callee ranking was rerun before this family analysis. Focused accepted-helper
replays are separate from this nonexact root and from any cold aggregate claim.
All23 accepted functions across seven focused helper units replay exact; the
receipt is `build/reimu-object-entry/accepted-helper-replays.json`. The
effect unit also contains the already nonaccepted5F9350 probe, which remains
nonexact. Its seven accepted members all pass; the entire mixed probe unit
is not reported as a passing exact unit.

Direct read-only Ghidra uses384MiB heap and CPU0/nice10. Before semantics it
independently verifies file/imported SHA256,400000 base,68B9D2 entry,
x86LE32/windows language/compiler, full mapped .text and root bytes. Its
temporary function metadata is read back and discarded; all nine primary
database file hashes agree afterward and its temporary project alias is
removed. The decompiler output in
`.analysis/reimu-object-entry-20261019/` remains a hypothesis. In particular,
it removes4A26F6's impossible negative unsigned-remainder branch and follows
the980 tail outside this root. Raw ownership retains the branch bytes and
models980 as a real helper transfer. Required IDA preflight rejects the wrong
open executable; no IDA semantics, factory adapter or target-byte patch is used.
