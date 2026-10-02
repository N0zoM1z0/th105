# AyaObject 903 distinct sequence branches, 2026-10-02

## Bounded result

This continues [the remaining selector checkpoint](AYA_OBJECT_REMAINING_SELECTOR_CONVERSIONS_2026_10_02.md)
on `AyaObject_update_action_state_vslot28 @ 0x0061A290`. The callable
`[61A290,61EED2)` has19,522 bytes and SHA-256
`18c813a20cea427b2c3577e2612e3f2e949a191ee2496dc9204331758bebb895`
in original Japanese1.06a PE
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

**Observed:** target903's auxiliary jump table at61F080 has ten distinct
entries. Index4 enters61E926 and index5 enters61E9A5. The previous
candidate pointed both entries to61E9DF, testing the sequence after a shared
owner/position prefix. The retained source gives each case its own body,
with its actual +1/-1 float displacement.

Within each body the target checks owner action740 before reading owner
sequence WORD+13E. The old eager local read the sequence first, including
when the action test failed. Source now reads the sequence after that test.
Both target paths then accept sequence1 or2, copy owner X/Y, and add/subtract
1 to reset+12C. A real alpha snapshot before the reset store restores
`MOV AL` between the x87 add/subtract and FSTP. The source writes the
saturating alpha as `<=245` plus10, otherwise255, recovering target JA and
the ordinary ADD AL/MOV BYTE path. These are target-backed read, value and
branch boundaries. Whether owner can be invalid or mutated on a rejected
action path is not established.

Target case4 occupies `[61E926,61E9A5)` (127 bytes); case5 occupies
`[61E9A5,61EA00)` (91 bytes). Retained candidate equivalents occupy
`[61E9DC,61EA5B)` and `[61EA5B,61EAB6)`. Across218 bytes/40 instructions,
all nonbranch encodings and operands agree, internal branches translate by
182 bytes, and external branches reach the same61A359 death or61A41D frame
exit. Their REL32 displacement bytes differ with placement. The candidate
auxiliary table is61F098 with distinct case entries61E9DC/61EA5B. A strict
hash-bound proof replays the unit's current relocation bindings, checks both
entire tables for ten distinct entries, and verifies every instruction/edge
in these two regions. This is **placement-translated diagnostic evidence, not
canonical byte equality or function acceptance**.

The configured whole-root comparison remains **nonexact at+0x22**, target0F/
candidate27. Retained source SHA-256 is
`f415056268756beb05581187e56c0c27d1a2b1ccad268156c2ef8f297ca418f2`.
Comparison-window SHA-256 is
`a5c8323ca9adf5556fa513776b20cd3d8820af8783030591e8cf0f025a363dce`.
Candidate metadata starts19,548,24 bytes beyond target metadata19,524;
its section tail is20,016. The19,522-byte comparator window ends26 bytes
before candidate metadata. This prefix hash does not establish candidate
body equality or accepted byte progress. No exact-ledger credit is added.

## Controls and other owners

| Sequential control |Metadata|903 span/instructions|Raw diagnostics|
| --- | ---: | ---: | ---: |
| Fresh previous source |19476|1655/363|3/34|
| Distinct 4/5 branches |19580|1760/380|4/34|
| Owner sequence after action guard |19580|1760/380|4/34|
| Saturating alpha `>245` branch |19548|1726/372|3/34|
| Addition-first `<=245` branch |19548|1726/372|3/34|
| Prior alpha snapshot, retained |19548|1726/372|3/34|

The temporary4/34 diagnostic includes802 alignment and is not retained as
acceptance. Final raw diagnostics remain entry/800/980,3/34, with33 main
switch destinations and zero splits. Target903 physical span is1697 bytes/
364 instructions, compared with candidate1726/372; differences elsewhere
in903 and its tail placement remain. The main target traversal still covers
all4,630 instructions/all19,522 bytes through seven switches.

Final-object regressions were checked:124/124 floating guards with the known
853 role mapping and902 path lead; all18 selector unsigned conversion forms;
826's140 mocked postspawn paths and131-byte translated interval;861 owner
read/payload interval and range; two641-value unsignedY cases;450 mocked
emission-prefix cases; RTTI-bound byte call widths;852's446-byte translated
emission pattern (27 bytes later) and194-byte rate/sequence pattern (32 bytes
later). These scoped models are not whole-game or global x87 control proofs.
No shared ABI/header/helper/compiler/object-partition or accepted-unit
relocation contract changed.

## Verification and remaining work

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

Final configured reports share prefix `build/aya-903-branches-final-`.
Private controls and the complete table/region checker are under
`.analysis/aya-903-branches-20261002/`; their objects and source/object/
window-hashed `controls-summary.json` are under
`build/aya-903-branches-20261002/`. Existing-object controls lack configured
build provenance; the retained source is rebuilt through the configured unit.
IDA still fails target identity and was not used. No Ghidra import or
aggregate cold replay is claimed. Run the mandatory local CI/whitespace gate
before commit.

Remaining issues include903's other auxiliary cases, register and physical
tail ownership,852's FILD/facing/scratch homes,826/861 physical sharing, and
original TU/LTCG context. Original alpha source spelling is not uniquely
proven by the decoded result. This interval emits naturally from VC8 C++;
no assembly requirement follows.
