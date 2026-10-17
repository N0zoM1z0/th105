# Iku compiler visibility and current complete link

The selected Iku source is unchanged. This investigation isolates a concrete
compiler-context constraint, adds a reproducible entry-witness mode, and
refreshes the complete ordinary-provider link for that selected source.
No exact credit or aggregate replay result is claimed.

Target is original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root620920 `[620920,62EFBE)` is59038 bytes, SHA256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.

## Controlled compiler-context observation

Under the same pinned VC8/SP1 flags, genuine sources, SDK/CRT libraries and
explicit retention of real game-function definitions, compiling all41 game
providers with `/GL` changes the root's first instruction. The generated root
starts with `SUB ESP,3FC` instead of the target's EBP setup and eight-byte stack
alignment. Its first101 bytes have no HIGHLOW field or CALL requiring replay.
An ordinary-provider control with the same retention directives still agrees
through the first100 bytes and differs at+0x64.

Eight successive subset links isolate one sufficient provider unit:
`cross-v106a-mt19937-next`. These are compiler-context trials, not source
expression searching. All408 compile-input checks across those eight trials
reused their already compiled objects; no compiler ran during the isolation.

| Providers visible as LTCG | First differing entry byte |
| --- | ---: |
| none; all game providers ordinary | +0x64 |
| all41 game providers | +0x00 |
| only `cross-v106a-mt19937-next` | +0x00 |

This unit contains the real `Mt19937.cpp` state, seed routine and next-value
routine. The result is **TU-level**, not proof that one function alone, a
specific optimizer pass, or inlining alone causes the change. It does not
prove the original MT unit's flags or original source/TU ownership. Within
this reconstruction/context, making that entire provider visible is
incompatible with the observed Iku entry. Keep the ordinary-provider baseline;
do not add invented source attributes or weaken matching to accept the trial.

A private attempt to inspect the full MT-visible root stopped at the strict
low-region switch recognizer (`expected one candidate COFF switch table,
found0`). This is a recognizer rejection, not proof that the low switch is
absent. The all-visible trial also exposes CIL-module MAP alias ownership
which the ordinary same-object rule does not certify. Neither trial supports
a full canonical or execution claim.

## Public reproduction and guards

```sh
python3 scripts/probe-iku-action-ltcg.py --reuse --provider-visibility none
python3 scripts/probe-iku-action-ltcg.py --reuse --provider-visibility cross-v106a-mt19937-next
python3 scripts/probe-iku-action-ltcg.py --reuse --provider-visibility all
```

`--provider-visibility` accepts `none`, `all`, or comma-separated selected
game-provider unit names. It is explicitly **entry-only** and rejects use
with `--ordinary-object`. Only named game providers gain `/GL`; the SDK deque,
provisional fabs adapter and static CRT/SDK remain separate. All retained
functions have real definitions. No code/import/CRT-storage stubs or executable
ABS bindings are introduced. Ordinary prelink dependency comparisons remain
separate from the experiment's linked objects.

The mode uses source/command/full-unit-input/tool/object-attested reuse,
retains the real game definitions with `/INCLUDE`, and records linked input
hashes, compiler-cache hashes, commands, data bindings, image/MAP hashes and
raw alias/actual MAP locations. A same-address inventory entry does not certify
cross-object alias ABI. No MAP ownership is rewritten and the existing full
replay's alias checks remain unchanged. Neither a same entry nor a successful
link means the full function matches. The mode returns a diagnostic receipt,
not an accepted comparison result.

Entry inspection rejects absent/duplicate Iku exports, HIGHLOW fields and
CALLs in the101-byte window. It decodes through the end of the window so a
CALL starting at byte100 is also rejected. Five new tests cover provider
selection, missing/split MAP aliases, pointer relocation, a CALL crossing the
window boundary and absent/duplicate exports. The full default link path is
unchanged and was separately run after adding this mode.

Public none/MT reports are `build/iku-visibility-public-{none,mt}.json` and
context receipts live below `build/iku-action-ltcg/provider-visibility/`.
They reuse44/44 and45/45 objects, respectively. The public all-provider run
also reproduces+0x00 and reuses85/85 objects. The MT trial's44 aliases have
unique same-address definitions in its inventory, which remains weaker than
the full replay's ownership/ABI qualification. No linked image was executed.

## Current selected-source complete replay

```sh
python3 scripts/probe-iku-action-ltcg.py --reuse --ordinary-object build/match-units/GptWeb_IkuActionState.obj
```

This separate default run reuses44/44 objects and closes the actual root with
41 ordinary game providers, pinned SDK/CRT,44 checked same-target aliases and
18 attested non-code data bindings. Fresh ordinary dependency comparisons
remain47/52 exact;406360/4063D0/417800/42CF70/4740C0 are nonexact. The406330
fabs adapter remains provisional/nonexact/unclassified. Both SDK deque
witnesses4399C0/42D1B0 remain94/100 exact before and after linking.

The complete59504-byte linked envelope replays all898 HIGHLOW fields:
782 literal reads, six switch-table address fields and110 destinations.
All863 ordinary CALLs and two absolute game-data reads close. Callable/padding
ends at58348; metadata ends59502; the remaining two bytes are explicit INT3.
Against all59502 ordinary section bytes, exactly22 scheduling bytes differ
in action730 at offsets `[53205,53219)` and `[53220,53228)`. No bytes or
alignment are hidden. Strict target59038 remains **nonexact+0x64 /620984**.

| Current bytes | SHA256 |
| --- | --- |
| source on disk, CRLF | `69c43bf58dcfbeee08866a93b007fa266718a37c7850b79609056b3920fa864b` |
| complete ordinary59502 | `dac7642939ffc375a5fc6095057722c35a47ebc7112faf978e9bdfcfd3b3f751` |
| linked shared59502 | `a9647e9a6a401eaab8c24f128d9fea99d0571c24df277abf7aa08d4f8746fbc4` |
| linked envelope59504 | `0ce3d92b61d3b860050e57f1d736a149babe2f3735068f1bc6faeea004d2f26e` |
| linked strict target-sized59038 | `f3983570b71d51aa1e5272f7b8ecca15442de2284621c6c77e92cea7db291de6` |

Report: `build/iku-state-flow-current-linked.json`; the default cache receipt
is `build/iku-action-ltcg/receipt.json`. This supersedes the earlier link's
source/size/hash claims while preserving its separate historical scope.

## Other bounded observations

A single read-only Ghidra clone was run with768MiB/two CPUs. Imported/PE
identity, entry, full mapped `.text`, complete root bytes/15132 instructions,
58 layout fields,177 virtual-call records and the ST0/EAX32 ftol ABI were
re-attested/read back. All nine primary database files are hash-unchanged.
Fresh decompiler output remains a hypothesis. The wrong-image IDA session
was not used for semantic analysis.

Moving all eight object818 phase payload declarations into their actual caller
blocks, while passing the arrays to the existing inline helper, is completely
byte-neutral across the59502-byte section. Frame400hex/84 homes and57 identity
correlations are unchanged. That source control is unselected. Exploratory
call-order/constant-argument projections did not establish a source defect;
mixed virtual-call labels, unknown scalar values and ordinal pairing still
limit those projections, so they are not promoted as equivalence proofs.

Current native results remain the same-source0/1584 effect and0/1728 sequence
exit checkpoints. Unrelated/broad native matrices and accepted units were not
replayed. No game source, shared header/layout, canonical profile, relocation
ledger, object partition or exact ledger changed. Retain the small default
cache and MT visibility object; remove other experiment objects, cloned
projects and duplicate linked images. Original C++/TU/inheritance/compiler
phase, post-backend behavior and exceptional timing remain unknown. These
observations reject particular contexts; they do not establish a general
standalone or LTCG barrier.
