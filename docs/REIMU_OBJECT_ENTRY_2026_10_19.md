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

## Current strict result and open questions

Selected source SHA256:
`4e165b8e1f963eff9fedb2d61dd5c650b5bf41d67e65b1f041f2d43a5d25fcbf`.
The complete canonical5440-byte section payload SHA256 is
`a72cf4f19db686c170b1b2216f0d660a6cb1e28a37831fbb738743ccd8f8ce25`.
Both callable bodies end at4A2FFC; both metadata starts are+4892. All65 direct
call sites,39 RETs and1325 instructions retain their target multiplicities.

Strict full-callable comparison remains nonexact at+1140/4A2E20, target57 /
sourceCE, in the selector-call preparation. There are30 differing callable
bytes, with no partial byte credit. All earlier36 equal owner diagnostics
remain equal;40/43 now agree. The remaining owners are:

| Owner | Unclosed physical difference |
| --- | --- |
|906|Virtual-call and heading-pointer registers; auxiliary entries2/3/5 use different shared angle-tail suffixes|
|908|Phase-byte store, heading-pointer load and epilogue scheduling in4/7's angle path|
|999|Heading-pointer and selector-call registers/preparation|

The548 metadata bytes differ in three byte positions, all in906's auxiliary
DWORDs. Its2/5 destinations are target4A2F15/source4A2F31; its3 destination
is target4A2F31/source4A2F4D. The primary destination/index tables and the
other six auxiliary tables are byte-identical after canonical replay.
Candidate4A2F4D is the pointer-load suffix after908's phase store. These
aliases and that store/load scheduling must be reconciled together; equal
sizes or an owner count do not establish complete metadata equality.

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
