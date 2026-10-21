# Native markup color reset and actual ESI caller

`TextFont_reset_markup_color @ 0x004118F0` has a complete162-byte,
47-instruction raw CFG with two RET paths. Real file-local typed C++ in the
actual markup TU naturally passes font in ESI with no stack argument.
Source161 bytes/46 instructions remains **nonexact at+7**:
`261fc985518daf149094489666948bd12b715aae1c7bef5b638036d1e7b72ae7`.
The entire native list cleanup loop is byte-identical; EDI save/restore scope
and the resulting tails differ. There is no new exact credit.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is analyzed. Required preflights pass for the target and ledgers. IDA rejects
its wrong open executable; facts use the attested raw PE. Full target hash:
`8b90f385b2069c2a33647ee19cf5d92e31a1cefcd5f28ebcd5acc8249afe2171`.
All162 bytes are reachable, including the compiler's loop alignment instruction.
There is no cropped tail, copied alignment or authored padding in the source.

## Target observations and selected source

The tracked candidate main-instruction census finds a direct edge at41260F
from reviewed markup411FA0. Font is ESI on entry, there are no stack arguments,
and EDI is the only register saved by the function. Original nominal spelling,
original TU and arbitrary indirect/remote callers remain unknown.

Reset retires the **whole** temporary color list, front to back. Each iteration
checks front, deletes its color array, checks pop-front, unlinks the node,
deletes the node, then decrements size. It does not pop a single nested color.
Only after the list becomes empty does it restore color state. Nonzero base158
is copied to active154. Zero base instead packs config-first R/G/B bytes
10C/10E/110 into fallback168. Active154 is untouched on that flat path, even
when it points to the array just deleted. Source does not add a pointer clear
or recover a previous temporary palette.

An ordinary `static void __stdcall` definition expresses this policy in the
actual caller TU. VC8 privately chooses ESI; no register facade or fake callee
prototype is used. Ordinary code generation saves EDI only while the list is
nonempty and restores it before color restoration. The target saves it across
the whole function and restores it separately in the two tails. The identical
loop does not make the remaining byte differentials exact. Linked context is
still needed to test this save-scope explanation; no synthetic register use or
inert local is added to force preservation.

## Execution, sensitivity and affected parent

All **240/240** bounded actual-reset instruction cases pass. Inputs cover
valid lists0/1/2/4/8, nullable payloads, four RGB triples, base absent/present,
and active null/distinct/former-front pointers. The independent final-state
specification and observations verify every array/unlink/node/count event,
complete retirement, config RGB packing, retained active on the flat path,
entire font/list snapshots, ESP and saved registers. CRT array/node deletion
uses explicit observers. No actual allocation, malformed-list, arbitrary-alias,
GDI or EH execution is claimed. A clear-active control fails120 cases.
A single-pop source experiment produces a separate out-of-line erase helper;
it is not used as a runtime or exact control without proving that extra boundary.

The real parent stops pushing/cleaning a stack font argument at its reset call.
Its complete body shrinks1652/447->1648/445, canonical
`4137c41131b2388b7c8f8cd34ee6aa4d4f70d37a5079c3dc465b0e4f02228213`.
It remains nonexact at+16 with frame788 versus target796 and the unresolved
ordinary member/private target entry. All **8,640/8,640** parent cases pass
again with actual byte-identical hex45 execution and an ESI reset observer.
Reset itself is tested separately above; other parent CRT/STL/font/color
providers remain abstract. Actual parent GDI/EH unwinding and allocation
failure remain untested, and its handler/metadata are still unqualified.

The other seven complete candidate bodies remain unchanged, including color332
and the five runtime roots; accepted hex remains45/45 exact on the focused
cold build. Only this accepted font unit is affected. No shared header, profile,
partition or existing data/relocation ledger changes; no unrelated or aggregate
exact replay is claimed. Authored/source-present classification increases by
one; matches.csv remains unchanged.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The nine-function focused comparison intentionally reports comparison_failed:
eight candidates are nonexact, while hex45 is exact. Selected evidence and
receipts remain in `build/font-reset-20261021/`; private reproduction recipes
are in `.analysis/font-reset-20261021/`. Next are genuine setter411760 and
blend4127C0 definitions, then larger font TU/link/EH recovery. Reimu496540 still
first differs at49655F/+31.
