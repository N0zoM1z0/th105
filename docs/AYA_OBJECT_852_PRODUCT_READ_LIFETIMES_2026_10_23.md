# AyaObject 852 product operand lifetimes

The selected update source now promotes the nested signed facing byte once
and uses float arithmetic in its two product arms. This restores the target's
live x87 facing value when speed is read. The predecessor passes output and
product-store checks but fails this observation in 1,920 cases. Root `0x61A290`
remains nonexact; branch-local conversion placement is still unresolved.

## Observed target and source correction

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking checks pass. IDA rejects its open database's
different executable; observations use the hash-attested PE and serial CPU0/
nice10 VC8 SP1 builds. No target bytes or analysis metadata are changed.

The target product window `0x61C98C..0x61C9CA` has 62 bytes / 14 instructions:
one early `MOVSX EDX` from the nested byte, then branch-local conversions.
The negative arm performs `FILD`, reads speed with `FLD` at `0x61C9AA`, negates
it and multiplies. The positive arm reads speed with `FMUL` at `0x61C9BE`.
Both reads therefore find the converted facing already live in x87.

The predecessor captures a signed-char local. Its negative arm reads speed
before converting facing. Earlier [store-only checks](AYA_OBJECT_852_NATIVE_CONTROL_2026_10_23.md)
did not observe that moment. The new `--product-read-lifetimes` mode in
`scripts/audit-aya-object-852-native.py` identifies a closed guard/store region,
then records actual nested-byte and speed reads: value, preceding write count,
x87 status/tag and every live register. Each product execution must contain
exactly one read of each operand. Existing default checks remain available.

Selected [source](../src/characters/AyaObjectActionState.cpp) SHA256:
`d4f4d37c9dcc348bab7e3448e5600f2c863d224463a05259003081d7c4ebcb8f`.
Only the used local type and its two arithmetic casts change. The one-byte
memory access, object layout and calling conventions stay unchanged.
The fresh public object has full canonical payload 20,120 bytes, metadata at
19,652, SHA256
`9ef08a09283471e6cdebb8a71900e6e0c68aa6a02d2761385e0e0df8b93ad565`.
Configured comparison of the unchanged 19,522-byte callable ledger remains
nonexact at `+0x22`, target `0F` / source `8E`. No exact credit is added.

## Execution and complete source impact

The expanded matrix has 9,728 cases, each running original target and both
source objects through actual RET. The 9,600 healthy sequence-0 cases cover
sixteen speed bit patterns, signed facing boundaries, timers 239/241 and twelve
masked x87 control words, including PC24. The other 128 cases cover sequences
0–3 and nonpositive health using two control words. Current source has no
recorded difference. The predecessor differs only at the speed-read snapshot
in 1,920 negative-facing cases; final effects and product stores still agree.
The command with that negative control intentionally exits 1.

The strict outside-action graph preserves 4,267 nodes. A narrower complete-root
traversal checks 4,558 node pairs while excluding only the closed product
window, including the remaining 852 spawn/RNG guards and paths. It finds one
two-instruction tail carrier, `MOVSX EDX/EAX; MOV [ESP+0x18],EDX/EAX`. The
unchanged public carrier checker proves both full registers dead afterward
under its reviewed normal-return `0x4351C0` contract. No generic register masks
or whole-action exclusions hide that difference. Private logs retain the
initial strict failure. The receipt records the qualified carrier, all switch
indices/ordered edges and absence of external entries into the window's interior.

These are scoped execution and source-to-source graph observations. They do
not establish arbitrary resources, random/spawn execution, callbacks, unmasked
exception delivery or whole-root equivalence. A local escaping-branch mutation
is rejected. A fault injected at the real target speed read `0x61C9AA` stops
execution and is surfaced by the existing ValueError callback wrapper.

## Source-expression and genuine CIL controls

| Control | Full payload bytes | Observation |
| --- | --- | --- |
| Predecessor byte local | 20132 | 67-byte window; late branch-local sign extension; negative speed-read lifetime fails. |
| Conditional speed operand, byte/int local | 20120 / 20116 | Adds a float spill/reload; fails the target split-window shape. |
| Int local, float arithmetic (selected) | 20120 | 54-byte window; early MOVSX and one common FILD; target arithmetic and speed-read state recovered. |
| Same float arithmetic, explicit if/else | 20120 | Complete payload identical to selected. |
| Int local, negate a double speed | 20108 | Common multiply before conditional FCHS; not the target arithmetic placement. |
| Direct nested-byte reads in both arms | 20132 | Target branch-local arithmetic, but two separate MOVSX reads instead of one early capture. Float/double cast variants are byte-identical. Unselected. |

Both selected and direct-read controls are compiled in the previously closed
update/init owner model as genuine `/GL` inputs and linked with the same twelve
hash-verified native source providers and pinned static CRT/SDK libraries.
Complete replay closes seven switches, 362 HIGHLOW fields and 123 direct calls.
Both emitted caller payloads equal their native counterparts at the canonical
address and `0x800000`. Selected envelope is 20,128 bytes including eight trailing
INT3 bytes, SHA256 `f00d6e70a97eec0e12775ccd3c92ed966b3b1e875ef5e5592b11f6e16b09e1b4`.
Three math providers remain nonexact; nominal aliases retain their prior limits.
This is not DLL-provider execution or proof of original class/TU ownership.

The selected 54-byte window still hoists one `FILD` before the branch; target
has two branch-local copies. Its tail now uses target EAX, but the scratch slot
is still `ESP+0x18` rather than target `+0x14`. These explicit differences remain
the next compiler/lifetime questions. Failed controls limit their tested
contexts, not every possible source or LTCG partition.

## Reproduce

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-852-facing-lifetimes.py
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-852-native.py --product-read-lifetimes
```

The root comparison intentionally remains nonzero; the selected-only runtime
audit is expected to pass. Private scope: `build/aya-852-expression-20261023/`;
recipes: `.analysis/aya-852-expression-20261023/`. Frozen `selected.cpp/obj`
means the **pre-change** baseline in this scope. `final-formal.json`,
`final-read-lifetimes.json`, `outside-product.json`, `guard-checks.json` and
`cil-selected/replay.json` retain the fresh evidence. `final-identities.json`
pins complete canonical and mapped identity between the audited and rebuilt
public objects. No shared game ABI,
header, compiler profile, partition, binding or accepted-unit change; no new
aggregate cold replay claim. Earlier 852/CIL records retain their source epochs.
