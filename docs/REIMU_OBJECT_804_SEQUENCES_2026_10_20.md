# ReimuObject804 independent sequence bodies

The selected source and flow audit have since advanced in the
[901 checkpoint](REIMU_OBJECT_901_FLOW_2026_10_20.md).
The pins and results below describe the preceding804 checkpoint.

This advances the [selector-family checkpoint](REIMU_OBJECT_SELECTOR_FAMILIES_2026_10_20.md)
for authored root496540. The target remains original Japanese TH10.5 v1.06a,
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The root owns46128 instruction bytes inside the46138-byte physical envelope
ending exclusively at4A197A. The provisional39853-byte main span, ownership
manifest, void/ECX/RET0 ABI and vslot28 are unchanged. No exact credit is added.

## Observed804 control flow

The physical interval496C1E..497086 contains272 instructions/1128 bytes, SHA256
`b20e9210f5ff5ef488373ea247facfda4025a01cb73508b21db06385d00aaf72`.
It is an action interval within the complete root, not a standalone function.
Its entry first checks phase5 and the signed sequence<2 owner-effect gate.
The sequence comparisons then occur independently at496C4B (zero),496DB0
(one) and496F26 (two). The zero body falls through to the one comparison;
both bodies can reach the fresh two comparison. A snapshot switch or an
else-if sequence2 test does not express this observed control flow.

| Operation | Sequence0 call sites | Sequence1 call sites |
| --- | --- | --- |
|Secondary setup993,4.0f,30,1,2|496C91|496DF0|
|Orientation at speed35|496CC4|496E23|
|State-six limit10|496CCD|496E2C|
|Conditional orientation at speed2|496CFB|496E5F|
|Select sequence2 through vslot0C|496D3C indirect|496EAD indirect|
|Secondary release|496D47|496EB8|
|MT next for horizontal speed|496D4C|496EBD|
|MT next for vertical speed|496D7E|496EEF|

**Observed:** setup requires all three counter/frame-timer/frame fields zero,
then clears the16-bit state364. Each body copies the parameter heading and
calls orientation at35. Sequence0's speed2 condition admits phase1/9;
sequence1 also admits phase2. Its16-bit state increment wraps and the subsequent
comparison is signed; values>3 reset state364 and phase180 to zero. Collapse
admits phase2/4; sequence1 additionally requires signed byte184<=0. It calls
the actual select-sequence virtual, clears byte184, releases the secondary,
then draws two MT values for the%20/%25 velocity expressions.

After either body, the root rechecks sequence2. A transition can therefore
apply gravity0.25, the vertical bounce, heading+40 and alpha-5 in the same
invocation. The later signed sequence<2 movement gate uses the updated value.
Bounds retain1380/-100/1000/-120 and a direct animation call at49702C. Animation
completion and a fresh all-zero sequence2 frame gate can each decrement330.
The two sequence families share this animation site, while their fourteen
other direct sites are distinct. The shared owner-effect site and two indirect
virtuals are separate from those fourteen sites.

**Source inference:** retain two independent if bodies followed by the existing
sequence2/movement tests. Duplicate only their actual supported behavior,
with no invented locals or branch predicates. Give804 its own natural bounds/
animation/sequence2-retirement tail, matching its observed local call site.
The rest of the source and all shared headers remain unchanged.

## Controlled compilation

All shapes use the same VC8 SP1 O2/GS profile, typed bindings and complete
46138-byte canonical comparison. No compiler flag, ABI, ownership range or
relocation key changes. Each keeps the natural438h frame and first31 target
bytes. First difference remains49655F/+31 in the default-branch displacement;
later register lifetimes, return/call sharing and body bytes also differ.

| Shape | Section bytes | Metadata start | Direct CALL /RET | Canonical SHA256 |
| --- | --- | --- | --- | --- |
|Starting selector source|44604|43720|393 /60|29f2de2f…|
|Independent804 bodies|44920|44036|400 /60|4ebe5489…|
|Local804 tail only|44776|43892|394 /61|85c33f58…|
|Selected: independent bodies and local tail|45100|44216|401 /61|3416b950…|

The independent bodies restore exactly two orientation sites, two MT sites,
one setup, one state-six and one release site. The local tail restores one
animation site and one physical RET. All23 non-animation/non-World callee
multiplicities now agree across the root: MT6/6, orientation47/47, state-six27/27,
setup11/11 and release9/9. Remaining counts are animation22 target/11 source
and World99/107. Their net three-site difference does not mean three missing
behaviors. Target/source RET counts remain68/61 and all43 owner diagnostics
remain nonidentical. Equal call counts or source size would not prove exactness.

The selected source decodes10285 instructions before metadata. Its final RET
ends44214, two alignment bytes precede44216, and884 metadata bytes follow.
The canonical comparator still checks all46138 physical bytes, including10
nonowned alignment bytes and remote chunks. No instruction or relocation mask
is added. The unchanged raw full-root closure retains10670 instructions,
22 switches and404 actual direct CALLs to25 targets. E8 inside49C35A's FLD1
remains a mapper false positive rather than a4C611D call.

An unselected follow-up expands only fifteen actual World-adjacent retirement
statements. It keeps438h but produces44872 bytes/391 CALLs/51 RETs and World97
against target99, so it is not selected. The target has eight direct jumps to
499DF6's shared receiver setup/World/retirement tail. A separate static walk
of unconditional normal-return continuations finds three target World sites
that reach RET without another call/conditional branch, twelve in the selected
source and two in the follow-up. These are structural classes, not execution
of World or proof of effect equivalence. The target classes include497A8B's
plain return,499DF8's immediate decrement330 and49D0C0's EBX decrement330.

901 initializes EBX=-1 at49CEC9 and preserves it through the latter World call.
Its direction stores at49CF27/49CF30 use immediate byte FF/1, not BL; the
decrement-register lifetime must therefore be investigated independently.
Two further private controls use -1 rather than255 for the equivalent stored
direction byte, separately and with local World retirements. They change code
but leave those401/391 CALL,61/51 RET and107/97 World totals respectively, with
zero identical owners. They remain unselected; no header signedness claim is
made. Recover901's local animation/retirement tails, actual constant lifetimes
and per-site sharing before adopting
these shapes. The preceding aligned-frame control does not prove their result
in this newer compiler phase, and a smaller number is not acceptance.

## Actual prefixes and physical-site checks

The new `scripts/audit-reimu-object-804-sequences.py` reuses the unchanged native
executor. It compares3144 actual target/source inputs covering sequence0/1
phase gates, signed byte127/128/255, short state-32768/-1/32767, state-six9/10,
both tested x87 control words, two actual MT seeds, initialization frame/timer
gates, sequence2 gravity/bounce/alpha and signed sequence-width defaults.
It observes original direct-call entries by their real root return PCs and
requires each sequence's expected seven private direct sites, disjoint between
the two families, plus one shared animation site. Target coverage must satisfy
the reviewed partition before source acceptance is possible. Indirect virtuals
are executed and remain covered by the underlying prefix/state/ABI checks;
they are not miscounted as direct sites.

The private selected shape passes0/3144, input SHA256
`192d412a7718d04b6ef04857ea6aa273b00c166ba2948b7c725400340d312dee`:
3132 actual RETs and12 secondary-setup entry stops. The fresh starting object
also has zero actual-prefix differences on these inputs, then fails the
physical setup-site partition because both sequences use the same source site.
That failure does not establish a runtime error in the merged baseline.

A separately compiled control changes only the final independent sequence2
test to else-if. It has the same45100-byte size,401 direct CALLs and61 RETs
as the selected shape. Actual input1920 rejects it: sequence1,phase2,index0,
state-32768,state-six9,seed0,counter1,CW027F. This control skips same-invocation
sequence2 processing after the transition. No target instruction or opaque
helper return is patched. The negative-control source SHA256 is
`c01cf68041bacbd82628c90eae92dd6428b6ff1242d8d5f0f1097ce6e83a3e6d`.

The auditor checks only admitted actual prefixes and observed site coverage.
Setup remains an entry frontier; it does not prove returning opaque graphs,
arbitrary aliases/resources, original source/TU spelling or exact bytes.
Object-only reports retain `build_provenance_verified=false` with source/tool
pins; the formal build's compiler/input/object provenance is separate evidence.

The fresh public build independently passes the same3144-input audit and the
previous16-input selector audit. Both808/812 caller proofs, orientation0/400,
alpha0/1170 and terrain288 pass with the selected45100-byte replay. A focused
original4937D0 manager-wrapper integration also passes0/3969, input SHA256
`a68f382d03a6e26297c7fcfe19f2efffb1cf39c5b93919e7ca8dd7c68f9dcdf8`:
3819 real wrapper RETs,54 secondary-setup,75 owned-spawn and21 first-World
entry stops;771 target/752 source instructions visited. It uses an input vtable
clone with cell28 selecting the actual target/source update, zero freeze/hold
words and null secondary. Original wrapper/root bytes and helper returns are
unchanged. This matrix selects projectile state/collapse/frame cohorts rather
than reusing the preceding checkpoint's unrelated manager input hash.

The frozen public source passes **0/133192** full existing inputs, unchanged
SHA256 `f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
It visits9215 target/8825 source instructions. Endpoints remain119356 actual
RETs,10422 first World entries,915 setup,1151 owned-spawn,26 effect,114 wave,
472 parented-spawn,112 CRT errno and624 CRT qNaN entries. Object/owner/parameter
bytes, helper arguments/traces, RET/stack, saved registers and x87 state keep
their existing checks. Opaque entry stops remain outside returning-graph proof.

## Ghidra corroboration and precision limits

Fresh preflight verifies the hash-attested PE and ledgers. IDA metadata still
identifies a different image and supplies no semantics. One direct read-only/
no-analysis Ghidra run independently checks imported/file identity, entry,
mapped text, root and primary vtable before decompilation. It uses CPU0,
nice10 and a128MiB heap cap; all nine primary DB hashes remain unchanged and
the temporary alias is removed.

**Decompiler hypothesis:** the two independent bodies and the subsequent
sequence2 check corroborate the raw edges. Its casts and predicates are not
source evidence. Target arithmetic uses FILD and64-bit operands, including
the exact double conversion of0.1f at6CD1E0; the source preserves that width
and association. The decompiler's positive ordered bounds conjunction also
needs raw flag review: the source retains the observed retirement predicates
and tests the matrix's NaN bounce/bounds inputs rather than copying that
conjunction. This does not close unmasked exceptions or the separately measured
Unicorn SSE conversion gap in the terrain audit.

## Selected pins and reproduction

| Artifact | SHA256 |
| --- | --- |
|CRLF CPP|`4d203e02b1c37cb7a992c9d1fe640a9495fae8558389784efe2fa261f83cd42b`|
|Unchanged header|`348794fa1087721b1444eacdc1d421355b6b8f76f656bd216b41221876adc`|
|Canonical45100-byte replay at496540|`3416b95016c143e4529daf5280745a6a8cf77febd67bc60755024f2fd5b61002`|
|Native45100-byte replay at800000|`3352e26225e0a5f9c1dc462eb87062bf25dd2bd54e96e7be4cbb9bf83fcc271f`|
|Public build object|`d5be3e981b034954c536773bed5c4e79b7da4379150408c51d1f9cce56a37d61`|
|804 auditor|`2f6f42ed6c6928146a053757eb7f148b9408e85ecda2fec83ec4e5fba47c1209`|

Reports, controls and fresh build receipts stay below
`build/reimu-object-sequence-804-20261020`; private raw/Ghidra/shape recipes
stay below `.analysis/reimu-object-sequence-804-20261020`. No generated report,
executable, object, database or compiler install is committed.

```bash
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-update-target.py --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected mismatch across the complete46138-byte physical envelope.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-804-sequences.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-sequence-804-20261020/804-selected.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-selector-families.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-sequence-804-20261020/selector-sites.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/match-units/GptWeb_ReimuObjectActionState.obj --final-actions --output-dir build/reimu-object-sequence-804-20261020/positive
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next investigate the remaining shared animation and excess World sites,
physical RET sharing, constant-register/stack lifetimes and honest TU/LTCG
context. Frame agreement and this case partition do not establish a standalone
compiler boundary or an LTCG impossibility. Terrain's48 hardware-unqualified
nonfinite contexts, returning world/setup/event/wave/CRT graphs, arbitrary
aliases/resources, nonnull rendering and unmasked exceptions remain open.
Preserve Fighter478FA0 and initializer4A1CE0 checkpoints. No cold aggregate,
percentage, root exact row or authored-byte credit is asserted.
