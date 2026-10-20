# ReimuObject animation ownership and remaining selector merge

## Current source hypothesis

The authored root496540 now has the target's physical memberships for all25
direct callees across42 outer action destinations. Animation4351C0 improves
from13 to22 sites. Nine action tails are local:801/810/811/815/817/822/852/906/908.
800/821,860/861 and905/907 retain their respective target-shared animation sites.
811/815 retain their four bounds checks before animation.852/906 use an explicit
retirement exit after their final counter/timer/frame/sequence3 test.852 writes
scaleX then scaleY, following the observed target store order.

Target801's final animation retirement and811's parent-sequence2 retirement
join496C0C/RET496C1D. The source now expresses that actual decrement/return
join as `retire_801_811`; its native RET8014C5 has exactly801/811 membership.
The final811 World request has a different target return and is not a member
of this join. No opaque call is made to return in the runtime fixtures.

**Observed regression:** source indirect sites decrease29 to28.801's
select-sequence2 site496AC1 and852's49B02A become one source site8048E1.
The checkpoint advances direct-call and one RET partition while retaining this
physical merge as a known blocker to exactness. The new strong audit remains
**`rejected`**, with exit status1. No matching/remote_exact row or authored-byte
credit is added. Baseline003b6f7 remains the reproducible earlier source state.

ECX/RET0 and the known4937D0 caller's ignored EAX are observations. The source
uses void; that caller alone does not prove the original C++ return type.
The39853-byte main-span candidate and three owned instruction ranges remain
provisional and unchanged. Strict comparison covers all46138 physical bytes
through4A197A:46128 owned instruction bytes plus10 alignment bytes. Metadata,
shared tails and remote chunks are not skipped to obtain a match.

## Target evidence

The raw complete root still has10670 reachable instructions,22 switches,
404 direct CALLs to25 targets,29 indirect CALLs and68 RETs. All22 animation
sites and their conditional post-call continuations were inspected. Their
union contains404 instructions, including one858 continuation to another call.
This is a bounded tail packet, not a new compiler/function boundary.

|Target CALL|Selected native CALL|Action membership|
|---|---|---|
|496844|80366F|800/821|
|496BC8|8005BF|801|
|49702C|800A0F|804|
|497193|80AD07|ordinary completion (18 actions)|
|49778E|80112B|810|
|497D6F|8016F4|811|
|4982D1|801C65|812|
|49864F|801FDA|815|
|498C75|8025CE|816|
|4993AB|803160|817|
|49A483|803DD1|822|
|49A5DD|803F21|825|
|49A7EA|804118|848|
|49AFC5|804871|852|
|49BD7B|805655|858|
|49BF37|80589A|860/861|
|49D7B8|80705F|901|
|49F230|80991D|905/907|
|49FB2C|809255|906|
|4A0FB8|80AAE7|908|
|4A18B9|80AE83|999|
|4A195B|80AEE8|default|

The ordinary-completion shared site covers807/808/850/851/853/854/855/856/859/
866/869/900/902/903/904/951/980/998. Membership means conditional normal-return
CFG closure. It does not establish branch predicates or returning opaque effects.

852's physical interval `[49ADF7,49B037)` has576 bytes/124 instructions, SHA256
`fe06cfc53d97b9f00203bec61e1f52fc83991eaa412e366cd776447b35e6b894`.
Its actual49AE71 `CMP CX,CX` followed by JNE is redundant. The original
source/compiler explanation remains unknown; no corresponding source predicate
has been inferred. The observed load width of a literal also does not prove its
original C++ spelling: explicit1380.0f and the existing1380.0 produce identical
default-profile code in the tested tail context.

## Runtime and structural audit

`scripts/audit-reimu-object-animation-sites.py` reuses the target attestation,
guarded source switches, complete42-action census and existing World proofs.
It checks every animation CALL's E8 encoding and actual callee, observes its
real return address/ECX, and records sequence13E, frame140, timer142, counter144
and state330 before/after the original helper plus returned AL. Full existing
object/owner/parameter/helper/ABI/x87/frontier output comparisons remain active.

The3360 inputs have SHA256
`35c726a1577208baf6c50e35bde1c5082d26aa7b9b2a8031379c214a1bee8b2c`.
All22 target and22 selected-source animation sites execute. Results are3078
real RETs,172 secondary-setup,94 World,8 wave and8 owned-spawn frontiers, with
zero prefix or animation-event differences. Source/target PC identities are
compared through physical memberships, not by requiring relocated PCs equal.
The original helpers run; opaque entries stop and do not receive invented returns.

The earlier13-site source also passes these executed outputs and covers all13
of its sites, but fails the direct-site partition. Conversely the selected
22-site source passes all25 direct-callee partitions and World constraints,
but fails the indirect membership comparison. Neither is accepted by the
strong conjunction. A green execution matrix is not a canonical result.

Two additional actual prefixes isolate the remaining merge:

|Input|Target CALL|Source CALL|Actual callee/receiver/argument|
|---|---|---|---|
|801,sequence1,phase1,index0,counter1,mode0|496AC1|8048E1|45C390 / actor /2|
|852,sequence0,owner action608,counter1|49B02A|8048E1|45C390 / actor /2|

Both execute the original selector and return with equal admitted outputs.
These observations identify the callee under the original input vtable; they
do not establish all indirect identities or arbitrary-vtable behavior.

## Compiler controls and qualifications

All controls compile serially, preserve real packet lifetimes and compare the
entire root extent. The selected profile remains `vc8-sp1-probe-o2`, GS off,
default FP, compiler SHA25671c93ca5… . No public profile, shared layout/header,
object partition or typed relocation key changes.

|Control|Canonical bytes / SHA prefix|Animation sites|Indirect sites|Result|
|---|---|---|---|---|
|003b6f7 baseline|44872 /fdf7c248|13|29|direct partition differs|
|five low tails only|45320 /3828bea1|17|29|other direct partitions differ|
|817 tail only|44980 /5264f8b4|14|29|other direct partitions differ|
|all nine local tails|45520 /ec5d26b5|20|28|825/852 and905/906/907 still merge|
|explicit852/906 retirement exits|45660 /4789efc5|22|28|direct partitions agree; selector merge remains|
|separate852 scale stores|45660 /7557a159|22|28|store order changes, selector remains|
|selected801/811 retirement join|45660 /14809ce3|22|28|one additional target RET membership agrees|
|RTM baseline|44892 /34ada750|13|not census-qualified here|nonexact|
|RTM inline-tail control|45664 /ffbfe4cd|22|28|selector merge remains|

Early-return and private-label spellings can emit identical complete code.
Changing declaration order of the same14 real arrays, including target-slot
ascending/descending order, also emits identical7557a159 code. These are
phase-scoped negative controls, not an impossibility theorem. Typed owner-pointer
and positive-guard controls likewise do not remove the801/852 merge.

Strict/exception and global-optimization controls stop at unreviewed double1380
or local fabs relocations under the unchanged contract. They do not yield a
qualified canonical result; no speculative bindings are added to pass them.
RTM14.0.50727.42 and SP1 .762 are independently file-version/hash inspected.
Rich-header build50727 alone does not identify the patch level or this root's
original compilation mode.

A separate private fixed-base `/GL`+`/LTCG` hosted-fragment diagnostic preserves
the25 known original helper addresses with a code-free, zero-section symbol
provider. Function REL32 imports use the linker's fixed-image RVA convention;
g_match_identifier remains the real host data address. Its unreferenced
`__fltused` link marker is metadata, not a replacement runtime function or a
claimed target data mapping. No helper body, return or target byte is fabricated.

That linked image is not a recovered original TU or a standalone game. Its
guarded22-switch closure has404 direct/28 indirect CALLs, all25 direct partitions
and the same selector merge. Its prologue adds EBP and dynamic8-byte alignment,
unlike the target. Actual execution of the same3360 inputs visits all22 sites,
with zero prefix/event differences. This one link context does not solve the
residual or prove that another honest source/caller/helper context cannot.

## Buffer and checkpoint pins

Actual first-World pointer observations retain12/14 target-relative buffer
slots in both the baseline and selected source. The two differences are822
healthF+190 versus sourceF+1A0 and900 completed sequence0 F+164 versus sourceF+104.
The other distinct slots are903 burst2C,901 exhaustion48/health54,822 phase180,
869 sequence2C4/owner384,900 dead sequence0 2DC/dead sequence1 3E4,903 health30C,
908 sequence6 378/sequence7 390 and902 retirement39C. Frame base is the actual
root stack below saved registers, recovered at the seven-argument World entry.
These are first-frontier slot observations, not full lifetime/opaque-return proof.

|Selected artifact|SHA256|
|---|---|
|Public CPP|`93ff75956a1e27258a4d8336d517972d9a6b204fb0adbbf050ea8cf95adc9bb1`|
|Unchanged header|`348794fa1087721b1444eacdc1d421355b6b8f76f656bd216b41261221876adc`|
|Canonical45660 at496540|`14809ce3a68dca9d74804d08455ca0243d031c63da3b3987a30b9213f14b59d6`|
|Native45660 at800000|`678a7468f20de821b40070e656ce12e9951ae602e9ea543751d7417fa0d2cf41`|
|Frozen tested COFF|`8198ee564d178b5f20c2338deb1de246fcd47d3fd60287c936c9aa7ca640d3b0`|
|Final rebuilt COFF|`b8a7b50b3bdfb2e0d5c8c998e3d1d43868864dbcb17e0b65e5001153b84eeefd`|

The final rebuild differs from the frozen tested object only in the COFF
timestamp field at offsets4..7. Every other object byte is identical; the
complete canonical code/metadata hash remains14809ce3. Execution reports pin
the frozen8198ee56 object, not the later timestamped container.

Source code prefix44792 plus868 metadata bytes, decoded10368/reachable10365,
404 direct+28 indirect CALLs and60 RETs. The natural438h frame and first31
target bytes remain. Complete46138-byte comparison still first differs at
49655F/+31; owner diagnostics remain0/43. No aggregate exact percentage is claimed.

Frozen full-input execution passes0/133192, unchanged SHA256
`f46a849ff57f64bb16e77fd0e28f7f51eee7238501c04049add99e7f77fc3b8b`.
Target/source visit9215/8945 instructions, with119356 real RETs and unchanged
opaque/CRT endpoint counts. Final source/COFF/native pins agree. World540+180,
900v2,9010/8/joint23,8040/3144,8120/2438/joint15,selector0/16,808/812 caller,
orientation400,alpha1170 andterrain288 regressions pass. Terrain retains240
finite equal and48 hardware-unqualified nonfinite contexts. The shared seven-
action World CALL/RET moves to80AA36/80AA4C; its18-byte post-call tail still agrees.

## Attestation and reproduction

Only original Japanese1.06a SHA25656350024… is used. IDA reports another image
and contributes no semantics. One direct Ghidra read-only/no-analysis run
re-attests file/import identity, entry, mapped text, full root and vtable,
then exports the reviewed404-instruction tail union. CPU0/nice10/128MiB heap,
one process, all nine primary DB hashes and temporary-alias cleanup are verified.
No target bytes or analysis database are patched.

Generated reports/controls remain below `build/reimu-object-animation-20261020`;
private recipes below `.analysis/reimu-object-animation-20261020`. Object-only
audits keep `build_provenance_verified=false`; compiler/source/COFF receipts
are separate. The former812 page records the superseded source checkpoint.

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/report-reconstruction-status.py --summary
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-state --compare --json
# Expected nonexact comparison at+31 over all46138 physical bytes.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-animation-sites.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-animation-20261020/animation.json
# Expected exit1/rejected: zero runtime differences, all25 direct partitions,
# all22 animation sites observed, but801/852 indirect membership differs.
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-world-sharing.py build/match-units/GptWeb_ReimuObjectActionState.obj --output build/reimu-object-animation-20261020/world.json
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-scalar-actions.py build/match-units/GptWeb_ReimuObjectActionState.obj --final-actions --output-dir build/reimu-object-animation-20261020/positive
python3 scripts/check-match-literals.py --require-target
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next recover the remaining selector-site/RET sharing, two buffer slots and
instruction/register/source/type/TU context. Returning opaque graphs, arbitrary
aliases/resources/vtables, nonnull rendering and unmasked exceptions remain
outside execution scope. Preserve Fighter478FA0 and initializer4A1CE0. No shared
change requires unrelated accepted-unit replay, and no LTCG impossibility or
root exactness is claimed.
