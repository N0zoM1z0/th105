# Alice CPU policy: bounded target and whole-source comparison

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
No source-present or exact credit is claimed at this boundary checkpoint.

**Unknown:** original local names, full nominal owner layout, original TU,
compiler phase and explanation for retained redundant probability checks.
Compiler standalone/LTCG ownership is not established by this comparison.
