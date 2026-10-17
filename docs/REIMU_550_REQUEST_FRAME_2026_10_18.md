# Reimu550/551: request preparation and the remaining frame discrepancy

## Observed target and source facts

Target remains original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 has81550 callable bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Authored identity, unclassified/declaration-only selection and exact ledgers
are unchanged. No root source-present or exact credit.

The preceding candidate's frame is578h versus target570h. Its compiler
listing places550/551's float trajectory at frame-relative676, between
parameter arrays. Target4876B0 stores that m32 value at40, and4876C4 reloads
it for each inner request. Target and source730 both use an m64 temporary
at40; changing730's floating type would not explain this discrepancy.

Target550/551's two object822 call sites are48763F and48776B. Before each
sine lookup, the target has already pushed count4, the parameter pointer,
arg5=1 and direction. Sine precedes cosine, then the object request. The old
source calculates named y/x locals before preparing those request arguments.
The physical table-owner span also contains direct560; that is not550
behavior. Action-entry CFG traversal isolates the two822 sites.

## Source hypothesis and compiler result

Only `ReimuActionStateMid550Cases.hpp` changes. Both requests now express x
and y directly in the argument list, preserving the existing casts, arithmetic
association, payload stores, loop bounds and per-iteration angle rewrite.
The fragment is included only by the main staging dispatcher. No shared
class/layout, compiler flag, global mapping or accepted unit changes.

Under pinned VC8 SP1/default FP, this ordinary source recovers the observed
argument preparation. It also moves the trajectory to the ordinary m32 slot40:
current4875EC writes it and487604 reloads it. The separately allocated4-byte
slot in the array region disappears. The112 source parameter arrays now cover
48..1408 contiguously; the earlier layout also had an unused4-byte gap before
the array region. Source frame **578h->570h** now equals target allocation.
Other scalar homes still differ; this does not identify the original spelling
or prove a language-wide argument evaluation order.

The strict comparison first differs at **478FB1/+11h**, after the common
17-byte prefix. Target pushes EDI there; candidate first zeroes EBP and later
uses BP for zero stores. This is a remaining compiler/source-shape difference,
not canonical equality or proof that standalone compilation is impossible.
Current prefix/text are81364/82736, with1168 E8s versus target1188.
All2456 relocations qualify/replay. No masking, register forcing or assembly.

Current object SHA256 is
`7dd7e47dd689c6d3cc33a74832891cd1388fc6927b3111de7172dd4c214abc74`.
Its last reachable instruction ends at the first table48CD74, without the
preceding candidate's three trailing alignment bytes. Internal alignment is
retained; the source/compiler boundary is still diagnostic, not an accepted
match unit. The unchanged official mapper retains126 primary destinations
and all11 switches.

## Reproducible bounded checks

```bash
python3 scripts/probe-reimu-action-source-shape.py --void-root --output-dir build/reimu-scalar-frame/current
python3 scripts/audit-reimu-root-stack.py build/reimu-scalar-frame/current/ReimuActionStateDispatch.obj --action 550 --action 551 --require-contracts --native
python3 scripts/audit-reimu-root-stack.py build/reimu-scalar-frame/current/ReimuActionStateDispatch.obj --require-contracts
python3 scripts/audit-reimu-void-root.py build/reimu-scalar-frame/current/ReimuActionStateDispatch.obj
```

The stack audit now supports a selected action matrix. The old
`--require-partitions` spelling remains an alias of `--require-contracts`;
default nine-action behavior is unchanged.550/551 additionally require the
observed object ID/count/arg5, sine/cosine order, and collective dominance of
the four argument pushes over the sine call. Every reaching argument push and
register definition remains significant. The previous578h object retains
the right buffer partition but fails both request-preparation contracts.

Two analyzer corrections were necessary for this evidence:

- Source550's four-entry table directly precedes the high primary table.
  Reading an entire contiguous relocation run merged these owners and invented
  high-action edges. Destination tables now stop at the next independently
  referenced metadata owner. Each of the eight auxiliary lengths must also
  agree with its decoded unsigned guard; the register bound requires agreeing
  reaching constant definitions. Counts are4,7,4,4,4,4,4,4. The previous and
  current nine buffer-partition conclusions both pass the corrected traversal.
- Capstone can report x87 store operands as reads. FST/FSTP/FIST/FISTP/FISTTP
  now count explicitly as writes when rejecting overwritten stack arguments.
  A poisoned-pointer FSTP fixture and adjacent-table fixture detect both bugs;
  the focused analyzer suite now has9 tests.

These corrections strengthen probe evidence. They do not change target bytes,
canonical relocation replay, accepted units or aggregate exact totals.

## Native evidence and remaining unknowns

The focused550/551 matrix passes **0/1576**,788 inputs per action, with960
real RETs and616 actual object-request entry stops. Input SHA256 is
`6b81cd666b1475fb1e31634b66e34ee0e061f41f6b170ccfe0bcbb33f70723cb`.
It uses the original family branch assertions and the current void fixture
defaults. Actual helpers, MT state, actor state and first payload are compared;
no helper result or callback return is fabricated.

The frame-timer0 grid follows the eight earlier object requests. The native
oracle stops at the first real request, so it does not execute that grid or
prove all returned iterations. Its two static call-site preparation checks
remain separate evidence. This change retains every inner angle rewrite;
removing it merely to reduce the frame would contradict target instructions.

Fresh current void also passes0/1544 with unchanged input SHA256
`c61982a9ccc694e3b6667371b5a4882e896da92d11320dd4aa3784f464787b80`.
Fresh compact bool passes0/12 smoke and0/8 indeterminate740 boundaries. The
710/711/720 static loops,48 510 packets/12 reloads and all nine earlier buffer
partitions pass. No full historical or aggregate cold replay.

Receipts, scalar/listing facts, controls and comparison reports are below
build/reimu-scalar-frame/. The private listing build and public probe have
identical raw code and relocation records. All9 primary Ghidra hashes remain
unchanged under the prior attested identity; this unit uses raw PE facts,
without IDA semantics or a new Ghidra process/clone. Superseded sources,
listings, inaccurate exploratory packets, objects and caches are cleaned.
Next recover the remaining constant/register sharing and call-site structure,
then returning-world and full compiler/TU ownership before canonical acceptance.
