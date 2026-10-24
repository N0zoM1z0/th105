# Alice CPU policy: complete source checkpoint, nonexact

## Observed target identity and complete boundary

This work selects the remaining Alice primary slot+58 CPU root `0x004F4B80`,
not the already exact slot+5C control root `0x004F8E00`. The original Japanese
1.06a executable SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The RTTI-owned primary-vtable cell `0x006C4C34` contains `0x004F4B80`.
The separate origin ledger already classifies this root as authored game code.

Raw target traversal closes all **4174 instructions**, **48 RET0 exits**,
**147 direct calls**, and every internal edge. There are no indirect calls
or external tail transfers. The final RET is `0x004F8B61`; callable extent
is **16354 bytes**, exclusive end `0x004F8B62`, SHA256
`8dde0aa257347356612ded23c26cf4a4dfcec593244ad0ed36778c5b812e33da`.

| Target metadata | Entries / bytes |
| --- | --- |
|4F8B64 action destinations|18 DWORDs|
|4F8BAC actions200..416 remap|217 BYTEs|
|4F8C88 /4F8CA0 /4F8CB4 sequence destinations|6 /5 /5 DWORDs|
|4F8CC8 /4F8CE4 /4F8D00 /4F8D1C sequence destinations|7 /7 /7 /7 DWORDs|
|4F8D38 final-policy destinations|21 DWORDs|
|4F8D8C policies0..100 remap|101 BYTEs|

All 83 destination entries land at reviewed instruction boundaries. The
alignment bytes are `8bff` at4F8B62 and `8d4900` at4F8C85. Complete target
payload is **17009 bytes**, exclusive end `0x004F8DF1`, SHA256
`44c74a61697409bc3628dbd5c2e48788f4c0e5ce02a439bcce5331d19812431d`. Fifteen following INT3 bytes separate the next root.

## Observed phases and helper ABI

| Reachable phase (stopped at its common join) | Instructions | Selector | Deque | Atan2 | FTOL2 | MT |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
|Entry/action dispatch to4F63C0|1418|24|7|2|4|1|
|Common attack proposals to4F75A5|1182|57|13|1|1|0|
|Final movement policy to real returns|1579|37|0|0|0|0|

Phase traversals may share tail instructions; the phase sum is not a unique
instruction count. Selector4067D0 is cdecl int(int); MT4066B0 is unsigned
cdecl(void); atan2_degrees406540 is float cdecl(float,float). Checked
sequence4399C0 takes ECX receiver+55C and one stack index0, returns a pointer
to a signed WORD, and pops4. The root receives ECX, returns with RET0,
conditionally saves EBP after the opponent-life gate, and has no EH or virtual
call sites. Partial pointer-only receiver views do not establish a nominal
owner layout and must never be constructed or embedded.

## Analysis provenance and early comparisons

The IDA preflight failed: GUI SHA256
`10350095bcf95edb59e03bee9849a2dc8a7714b4927ad5909c569c550fce6822`
is not this target. No semantic query or metadata write used that IDA session.
One read-only Ghidra run independently attested original path/hash, x86 Windows
language/compiler, image base, entry68B9D2, every mapped raw-backed section and
this root. All nine primary database file pins were unchanged. Its 2357-line
call-view decompilation remains a hypothesis; source choices require raw
operands and edges. Ghidra used a384MiB cap, CPU0/nice10, and completed normally.

A complete Marisa family-control body was compiled early as a private diagnostic
input. It emits16867 bytes versus17009 target; first mismatch+12E is a return
branch displacement. It is deliberately **not selected Alice source**. Independent
Alice action-stage reconstruction subsequently recovers the native18/6/5/5/7/7/7/7
destination counts and all action helper counts. Attack and policy stages are
being independently checked, including ordered float guards, sequence IDs,
independent RNG draws and repeated timer/probability observations.

Private bounded work is under
`.analysis/exact-first-alice-slot58-20261024/`; generated receipts are under
`build/exact-first-alice-slot58-20261024/`. `raw.py`, `setup.py`, `phases.py`
and `diagnose.py` reproduce target closure and complete-object diagnostics.
These inputs and receipts are local working state, not committed artifacts.
The first boundary-only checkpoint did not claim source or exact credit.
The subsequent complete source selection below supersedes that phase.

**Unknown:** original local names, full nominal owner layout, original TU,
compiler phase and explanation for retained redundant probability checks.
Compiler standalone/LTCG ownership is not established by this comparison.

## Complete selected source: nonexact

`src/characters/AliceCpuPolicy.cpp/.hpp` now supplies the complete numeric/offset
candidate. It contains the real first-stage action dispatch, common attack
proposals, all four posture pairs, policy0 probability bands, policies1..18,
100 and default, native timer/command widths, inactive-opponent return and actual
RNG/deque/angle declarations. There are no assembly bodies, copied bytes,
padding, fake returns, invented helper behavior or full owner-layout claims.

The formal manifest build and independent cold object both emit **16869 bytes
versus17009 target**. Full canonical SHA256 is
`8a05cfa0020973f731bc9950527ff7fdb4d1fa909f4246f4cd45a376439cdfde`.
First mismatch is **+0x35 / 0x004F4BB5**, target10/source14: the first genuine
integer-to-float temporary uses `[esp+10]` versus `[esp+14]`. Both frames are12
bytes; no artificial local or ABI change is used to force reuse. This is not a
missing-byte count or an exact match. `matches.csv` remains unchanged.

Selected source retains all nine destination tables with counts
18/6/5/5/7/7/7/7/21 and both217/101-byte remaps. Action helper counts match
24 selector/7 deque/2 atan2/4 FTOL/1 MT; common attacks match57/13/1/1/0.
The final policy emits30 physical selector sites versus37 native, and the whole
body42 RETs versus48. Several equivalent duration/return tails merge. Counts
are diagnostics, not semantic or canonical acceptance. Full comparison replays
all callable and metadata relocations and requires complete length equality.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-alice-cpu-policy --compare --json
python3 scripts/audit-alice-cpu-policy.py
taskset -c 0 nice -n 10 python3 scripts/audit-alice-cpu-policy-paths.py
```

The first two return1 with the recorded mismatch; the path diagnostic returns0.
A cold object can be independently checked with `--object` on both audits.

## Bounded source decisions and retained experiment receipts

Every row compares a complete emitted candidate. None receives partial exact
credit. Private frozen sources and generated canonical/report hashes remain
under the paths recorded above.

| Candidate | Evidence-backed question / result |
| --- | --- |
|family-control|Complete Marisa-shaped control16867; first+12E. Alice behavior is not inferred from this family control.|
|actions-candidate|Independently restore Alice action windows, WORD timers, command724/728 distinction and sequence200..206 switches. All action helper/table counts return; caller is still a private mixed-family control.|
|complete-v2|All three Alice phases are present. Two genuine air entries retain distinct proposal draws and merge the angle call. Emits16873, first+2 frame16 versus12. The44 bounded controls expose3 actual counterexamples.|
|complete-v3|Correct the ground attack interval to h>=250 AND h<=400. Raw4F6934..6950 selects the <=400 path. The three real RNG streams now retain all17 draws, including the draw missed by v2. All44 controls pass; full16873 remains nonexact.|
|complete-v4, unselected|Move the whole common angle expression into one source label. Frame12 returns, but one real physical proposal copy merges: attacks56 selectors versus57. Full16857, first+12E. Do not select it as a codegen improvement.|
|probe05|Use the observed unsigned `<15/40/50/30/10/2/3` endpoints where native CMP/JAE retains them. Full16869; frame16 remains.|
|probe06, unselected|Explicit first-stage exits test the same control-flow approach used for Marisa. Full16905, first+2; no helper-copy recovery. Preserve the receipt rather than assuming family codegen transfers.|
|probe07, selected|Keep the live horizontal angle capture and evaluate the real vertical argument at the common call. The extra vertical temporary dies; frame12 returns. Full16869, first+35. All44 scoped controls pass.|

**Observed source-specific details:** action301/304/308 producers use R200,
other action producers R100; timer actions400/401/404..406 also produce R30 and
increment signed WORD76C before checking76A. Action308 writes DWORD724 in its
last two command windows. Action404..406 retains the target's repeated25..30
window without deleting it. Sequence204 gates h<540f and206 h>320f. All final
policy overlaps preserve the earlier passing branch; final modes101/102 are
absent from this root. Common attack sequence accesses remain independent;
falling/rising predicates retain their actual field read and FP ordering.

The diagnostic executes44 inputs chosen for those ambiguities:13 action,
19 policy-overlap and12 attack-order inputs. The original native MT, selector,
checked deque, atan2 and FTOL2 all execute; no helper return is injected.
Actor bytes, control/command words, RNG state, full helper argument/return trace,
x87 control and real RET cleanup agree. Each selection seed is independently
confirmed by the target. Native ground h400 streams must make17 selector calls
before any source comparison. The old complete-v2 object fails3 of the same44
inputs and is retained as a negative control. Vector SHA256:
`0ab1c2e1a74fa3590066f0bd009f3b5ab741e4aad0a796ee7cb183799eee6fdf`.
These scoped inputs do not establish complete gameplay equivalence.

Four newly witnessed float bindings540/720/580/380 are added without changing
existing bindings. Earlier sources, headers, flags, objects, accepted exact units
and authored-origin denominator are unchanged. All15 roster CPU owners now have
complete selected source through five roots (the shared root covers11 owners);
this is source coverage, not exact coverage. No aggregate cold-exact claim is
made. Preserve this local-stack/shared-tail residual and select another complete
representative unless new target or compiler evidence justifies reopening it.
