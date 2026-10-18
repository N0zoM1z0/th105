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

## Current strict result and open questions

Selected source SHA256:
`7f12f5c1cd9755235546ce4bfda9f30eb7ca3fa698f04673f7e1b807e7b63386`.
The complete canonical5440-byte section payload SHA256 is
`14a90e9d621c28bd65132ef1a66362fb114ad66cf179a8d5ae4c9c6e543a04e0`.
Both source and target primary metadata start at+4892, but the candidate's
last RET ends at4A2FF9: its three-byte compiler LEA alignment8D4900 occupies
the rest of that prefix. Target callable bytes extend through4A2FFB.
The candidate prefix therefore is not a4892-byte callable-body hash.

Strict full-callable comparison remains nonexact at+80/4A1D60, target90 /
source8D, in the default-exit branch displacement. No partial byte credit
is assigned. The remaining diagnostics are:

| Owner | Unclosed physical difference |
| --- | --- |
|822|Source shares a floating scale/return tail; target owns its copy|
|903|Source owns a longer scale/return copy where target shares the904 tail|
|904|Phase-byte store, x87 temporary and epilogue scheduling|
|906|Virtual-call and heading-pointer register allocation|
|908|Phase-byte store and epilogue scheduling in the shared angle paths|
|999|Heading-pointer and selector-call register allocation|
|default/802|Candidate's post-RET alignment is included in the diagnostic span|

A private whole-function `fenv_access(on)` control regresses36/43 to9/43,
with no newly equal owner and prefix/payload4948/5496. It is not selected.
Original sharing, exception delivery, value lifetimes and TU/LTCG context
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
