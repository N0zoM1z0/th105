# ReimuObject selector families and natural frame recovery

> Historical experiment record. Its pins, selected source and next steps apply
> to that checkpoint. Use [the current handoff](RE_HANDOFF.md) and
> [evidence index](REIMU_OBJECT_EVIDENCE.md) for current state and ABI limits.

The selected source has since advanced in the
[804 sequence checkpoint](REIMU_OBJECT_804_SEQUENCES_2026_10_20.md).
The pins and results below describe the preceding selector-family checkpoint.

This advances the [void-root checkpoint](REIMU_OBJECT_VOID_ROOT_2026_10_20.md)
for authored update496540. The target remains original Japanese TH10.5 v1.06a,
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Its complete physical comparison is46138 bytes through4A197A exclusively:
46128 owned instruction bytes and10 alignment bytes. The39853-byte main-span
candidate remains provisional. There is no new exact acceptance.

## Observed selector partition

Fresh raw decoding retains10670 instructions,22 switches,404 actual direct
CALLs to25 targets and68 RETs. The raw E8 mapper still counts the E8 inside
49C35A's FLD1; that byte is not a call to4C611D. The four selector dispatches
load the32-bit global6FA894 once, compare against3, take unsigned JA for the
default, then jump through a four-entry table.

| Action | Dispatch /table | Destinations for modes0,1,2,3 |
| --- | --- | --- |
|905|49ED75 /4A1C24|49EF46,49EEC1,49EE3C,49ED7C|
|906|49F44A /4A1C4C|49F76D,49F665,49F55D,49F451|
|907|49FD3F /4A1C74|4A0072,49FF68,49FE4E,49FD46|
|908|4A0840 /4A1CAC|4A0DC5,4A0C03,4A0A40,4A0847|

**Observed:** normal-return CFG closure from each selector destination gives
the following physical call-site partition. These are static continuations
conditional on normal ABI returns, not execution of opaque calls.

| Action | Private calls per mode0,1,2,3 | Calls shared by all four modes |
| --- | --- | --- |
|905|1,1,1,1|World49EE25, wave49EE32, animation49F230|
|906|3,3,3,3|animation49FB2C|
|907|2,2,2,2|wave4A016E, animation49F230|
|908|8,9,9,10|animation4A0FB8|

905 has four separate first-spawn sites and stack packets; each mode mutates
its packet before a shared second spawn/wave tail. 906 owns a loop spawn,
final spawn and wave in every family. 907 owns an atan2 call and spawn in
every family; mode1 still calls atan2 and discards its result. 908's counter
updates precede the selector load. Its type4/type5 request offsets, selector1
reset240, selector2/3 reset150 and selector3's two60-word writes before RNG
are preserved. Calls cannot cause a second selector-global read in the source.

**Source inference:** select separate natural C++ case bodies and actual local
parameter arrays for all four families. The previous merged period/sector
implementation preserved tested entry prefixes but did not preserve this
physical partition. This does not prove that its runtime behavior was wrong.
VC8 is allowed to share the tails again; the source has no assembly, byte
arrays, inert locals, padding, fabricated returns or register directives.

## Controlled source experiments

All experiments use the same VC8 SP1 O2/GS profile, header, typed bindings and
complete46138-byte strict comparison. No accepted boundary or relocation is
changed. Sizes include switch metadata; CALL/RET counts are decoded physical
instructions, not behavior counts. The starting void source hash is81038174.

| Private shape | Section bytes | Metadata start | CALL /RET | First difference |
| --- | --- | --- | --- | --- |
|Baseline|41480|40612|347 /61|+0|
|Separate905 only|41856|40988|350 /61|+0|
|Separate906 only|42172|41304|356 /61|+0|
|Separate907 only|42080|41212|352 /61|+0|
|Separate908 selector only|42620|41736|373 /60|+0|
|All four selector families|44424|43540|390 /60|+2|
|All four plus separate908 sequences4/5|44464|43580|391 /60|+2|
|All four plus separate908 sequences6/7|44564|43680|392 /60|+31|
|Selected: all four plus separate908 sequences4/5/6/7|44604|43720|393 /60|+31|

Two additional alignment controls limit the inference. Separate905+908 still
uses the aligned frame (42996 bytes); separate906+907 removes it but allocates
3C0h (42952 bytes). Merely replacing the two named double sector-step locals
with inline expressions retains the aligned frame (41460 bytes). The result
does not support a claim that named double declarations alone caused alignment.

**Observed:** the target's908 sequences4 and5 independently call orientation
at4A10D1/4A11F4, then share state-six(limit10) at4A10EC. Sequences6 and7 call
orientation at4A124F/4A132B and state-six(limit3) at4A126A/4A1346. Both increment
parameter speed before orientation, then change heading by opposite2-degree
steps. Signed phase-index<=0 and the owner-health gate set state1. Their
type8/type9 packets occupy separate target stack locations378h/390h before
sharing argument preparation at4A12BA and the remote World tail at499DF6.
Sequences4/5 retain their own-health thresholds-800/-1200 and fade behavior.

**Source inference:** separate those four sequence bodies rather than testing
the sequence again inside grouped cases. Splitting6/7 gives a real additional
three-float packet scope and increases the selected frame by12 bytes,42Ch to
438h. Splitting4/5 adds a distinct orientation site while VC8 naturally shares
the state-six tail. Splitting6/7 adds another orientation and state-six site;
the World site remains shared. This explains the measured frame change without
claiming that every target local/stack slot or original source spelling is known.

The selected source begins with the same31 bytes as the target: SUBESP438h,
saved EBX/EBP/ESI, receiver setup, sign-extended action load, normalization,
range comparison and saved EDI. The first strict difference is49655F/+31,
the range-default branch displacement. Later differences include lifted EBP=0
and EBX=1 constants before the source's primary jump table, metadata addresses,
return sharing and body scheduling. Matching this prefix grants no partial
authored-byte credit.

| Callee | Target sites | Selected source sites |
| --- | --- | --- |
|4066B0 MT|6|4|
|435160 orientation|47|45|
|4351C0 animation|22|10|
|4963A0 state-six|27|26|
|4963F0 release|9|8|
|496420 setup|11|10|
|64CCB0 World|99|107|

Other callee counts agree. The net11-CALL/eight-RET difference is a partition
diagnostic: the source also has eight excess World sites. It is not eleven
missing behaviors. All43 physical owner diagnostics still report nonidentity.

## Scoped selector audit and counterexamples

The new `scripts/audit-reimu-object-selector-families.py` executes sixteen
actual target/source inputs, one per action/mode. It identifies the dispatch
reached by each input, compares the complete prefix to the first World entry
and requires four physically distinct first-World calls per action. Actual
helper/RNG instructions run; World is never replaced with a fabricated return.

The script validates the exact observed global-load/CMP3/JA/indexed-JMP
protocol. It fully decodes the source prefix ending at its first reviewed
forward absolute jump table and bounds selector tables within that metadata.
It compares private/shared call multiplicities and labeled call-graph
bijections after projecting intervening instructions onto actual calls/RET.
Duplicate callees may be renamed, while loop edges, order and shared/private
ownership must survive. Physical RET sites are collapsed into one terminal;
branch predicates, instruction equivalence and termination are not proved.
The report explicitly retains `build_provenance_verified=false` and pins its
support files; formal build provenance is separate evidence.

The selected source passes all16 prefixes and partitions, input hash
`0b04b4aa99b98c2af1ac707ba98eb104c629449961c6c0ca9761a33f6e504b43`.
The fresh baseline object is rejected for action905's merged physical sites.
A separately compiled private906 control moves the wave before the final
spawn while preserving the first-spawn prefix and call counts. The call-graph
comparison rejects it at906/mode0. Four focused unit tests cover renamed
duplicate callees, an early wave, a removed iteration and changed site ownership.
Neither this audit nor its counterexamples proves returning-World semantics.

## Build, runtime and provenance

The selected CRLF CPP is
`1e08994cea9c3185726927a66df0707e2151491f4ae242b1973ee4fc730e5dd9`.
The header remains
`348794fa1087721b1444eacdc1d421355b6b8f76f656bd216b41261221876adc`;
the native auditor remains
`6d3dfbdf984db55dd29bae2648c383df071bdd1f29efced1f3d790fd368b8d70`.
Canonical replay at496540 is44604 bytes,
`29f2de2f348bcc98014c458834ff30bf3661a74a4fbf343432ae88390b5948c7`.
Native replay at800000 is44604 bytes,
`fccfd70aaaed5df3b8c0533f591c1f915301ce0dff8777353d6055003cad77bf`.
Source final RET ends43718, two alignment bytes precede43720 and884 metadata
bytes follow. The full comparison remains **mismatch** at+31, without masks or
unresolved bindings. Decoded source counts are10163 instructions,393 direct
CALLs to25 targets and60 RETs. Owned-extent and literal ledgers are unchanged.
The closing public rebuild has object SHA256
`a5e6f749f6d023054feb139eabae38b2c139207763d7d5a587034c56cbfc24af`,
with fresh final ledger/manifest provenance. Its entire44604-byte native replay
is byte-identical to the separately pinned82b30abc runtime object; COFF file
identity is not substituted for replay identity.

The first four-family stage passed0/4032 selector-focused inputs and the
unchanged0/133192 full matrix. The private movement shape passed0/984 gate,
state-six and floating-boundary inputs (768 real RETs,216 first World entries),
input hash `3de8f168a9a9fcf15b6ad436e429c1a3460fffd6dbaad6ecaa7c30aa322ed75e`.
These stage objects remain separately pinned rather than being attributed to
the final public build.

The frozen selected public source passes **0/133192** unchanged full inputs,
hash `f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
It visits9215 target/8709 source instructions with119356 real RETs,10422
first World entries,915 secondary-setup entries,1151 owned-spawn entries,
26 effect entries,114 wave entries,472 parented-spawn entries,112 CRT errno
entries and624 CRT qNaN entries. Object bytes, owner/parameter bytes, helper
arguments/traces, stack/RET, saved registers and x87 state retain their prior
checks. The endpoints are entry stops rather than simulated opaque returns.

The selected public object82b30abc passes the original76-byte4937D0 wrapper
entry check0/4200, unchanged input hash
`fff4c44d1164561a14ae08befbaea5c268bef7c4e8d41b62c8c491c636ab6d7b`:
4156 real wrapper RETs and44 first World entries,1226 target/1211 source
instructions visited. It uses an input vtable clone with the actual update
at+28, zero freeze/hold words and null secondary. Both808/812 caller proofs,
orientation0/400, alpha0/1170 and terrain288 pass for the selected object.
The18 already accepted geometry/animation/runtime/atan2 members replay exact;
their shared headers, flags and bindings are unchanged by either source shape.

Fresh preflight verifies the target, ledgers and shared-callee inventory. IDA
metadata still identifies another executable; no IDA semantics are used.
One direct read-only/no-analysis Ghidra process independently attests file and
import identity, entry, mapped text, root and primary vtable with a128MiB heap
cap, CPU0 and nice10. Its decompilation corroborates family structure only as
a hypothesis. All nine primary database hashes remain unchanged; the alias is
removed. No target bytes, databases or original vtables are patched.

Build reports, raw packets, shape controls and runtime reports stay below
`build/reimu-object-selector-families-20261020`; private recipes/Ghidra scripts
stay below `.analysis/reimu-object-selector-families-20261020`. No generated
object, report, executable or database is committed.

```bash
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-update-target.py --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected mismatch over the complete46138-byte envelope.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-selector-families.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-selector-families-20261020/selector-sites.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/match-units/GptWeb_ReimuObjectActionState.obj --final-actions --output-dir build/reimu-object-selector-families-20261020/positive
python3 -m unittest discover -s tests -p test_reimu_selector_call_graph.py -v
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next recover the remaining physical animation/case/RET sharing and constant
register lifetimes against the full raw CFG. Matching the natural438h frame
does not close stack-local ownership, TU/LTCG context or root exactness.
As a bounded next lead, physical intervals between the reviewed primary
entries localize all remaining MT/orientation/state-six/setup/release count
differences to804's496C1E..497086 interval: respectively4/2,4/2,2/1,2/1,2/1
target/source sites. Raw instructions distinguish sequence0 at496C4B and
sequence1 at496DB0; the selected source still groups them. These interval
counts do not establish semantic action ownership of shared tails. No804
source change is included here. Excess World sites and shared animation tails
require separate analysis.
Returning World/setup/event/wave/CRT graphs, arbitrary aliases/resources,
nonnull rendering and unmasked exceptions remain unknown. Terrain still has
240 finite equal prefixes and48 hardware-unqualified nonfinite contexts;
the measured Unicorn SSE conversion gap and runtime6FA894 adjacent-word load
remain unchanged. Preserve Fighter478FA0 and initializer4A1CE0 checkpoints.
No cold aggregate, percentage, root exact row or authored-byte credit is added.
