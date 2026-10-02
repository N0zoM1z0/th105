# AyaObject owner reloads and floating payloads, 2026-10-02

## Bounded result

**Observed:** this continues [the spawn-argument checkpoint](AYA_OBJECT_SPAWN_ARGUMENTS_AND_BYTE_CONTRACT_2026_10_02.md) on
`AyaObject_update_action_state_vslot28 @ 0x0061A290`. The callable remains
`[0x0061A290,0x0061EED2)`,19,522 bytes, SHA-256
`18c813a20cea427b2c3577e2612e3f2e949a191ee2496dc9204331758bebb895`,
in original Japanese1.06a PE
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

861 now reloads `fighter_owner_348` after each stage-height call, and its two
random payloads convert unsigned selector results before floating subtraction50.
These follow raw target read and conversion boundaries. No assembly, artificial
storage, register forcing or shared ABI/compiler/relocation change is used.

The configured whole-root comparison remains **nonexact at+0x22**, target0F/
candidate7E. Candidate metadata starts19,380 versus target19,524: gap184->144.
Section tail19,848 supplies the19,522-byte window, including142 bytes after
candidate metadata. Its SHA-256
`8c88302ed91d0293e73316e63976ffcf46674fd7771cd766cefdc3ac5e229dd2`
is a comparison-window hash, not a body hash. Retained LF source SHA-256:
`da7e076be4bdb2ef39196d30584d04e42d9671d30d73a537c8a48bbce74c4b30`.
No exact-ledger credit is added.

## Owner read boundaries

**Observed:** target first reads owner+348 at61D5F8, owner Y at61D622, and
snapshots that Y into a QWORD before stage-height call435D60 at61D62E.
It reads owner+348 again at61D653, snapshots that owner's Y at61D659, and
calls435D60 at61D665. After the second call and heading guard it reads
owner+348 again at61D68A and copies that owner's X/Y at61D690/61D69E.
The old source retained the initial owner across both calls.

| Read | Target | Retained candidate | Previous candidate |
| --- | --- | --- | --- |
| First comparison Y |Initial owner|Initial owner|Initial owner|
| Second comparison Y |Owner after first call|Owner after first call|Initial owner|
| Position X/Y |Owner after second call|Owner after second call|Initial owner|

A hash-bound decoded read-epoch check verifies three owner-pointer loads in
target/current versus one in the previous candidate, and the four coordinate
reads above. It follows the lexical nonreturn path; it is not game execution.
**Unknown:** whether435D60 actually changes this owner pointer. The target
reload boundary is established without asserting such a mutation occurs.

The candidate's first guard still uses TESTBL,AH versus target TESTAH,1.
The existing raw435D60/68A1A0 preservation check establishes EBX=1 across
this call chain. All124 floating guards remain covered; the established
853 role mapping and902 path reconciliation are unchanged.

## Payload conversion and translated interval

**Observed:** target calls selector100 at61D6B0 and61D6D3. Each result is
FILD32-converted with an unsigned correction by2^32 at6D6EF8 when required,
then FSUB QWORD50 at6C3C08, then stored to its real payload slot. Previous
source performed signed integer subtraction50 before float conversion.
The retained unsigned cast followed by floating subtraction restores the
conversion order. The shared selector prototype/body is unchanged.

Target `[61D68A,61D70D)` and candidate `[61D65A,61D6DD)` have the same32
instruction forms across131 bytes: all noncall encodings/operands agree,
internal edges translate by48 bytes, and both CALLs target4067D0. CALL
REL32 bytes differ with placement. This is a translated instruction/edge
diagnostic, **not canonical byte equality or function acceptance**.

For every actual selector100 result0..100 inclusive, both old and restored
expressions produce the same stored binary32 value under nearest-even
FSTP32. Both independent payloads therefore cover10,201 possible pairs.
This is conversion-order recovery, not a demonstrated ordinary-value bug.
The rare inclusive upper100 is included. Global x87 control/exception
behavior and whole-root numerical closure remain unproven.

The owner action guard also remains source-equivalent: all65,536 short-bit
patterns agree between target's signed50..149 comparisons and candidate's
16-bit subtract50/unsigned<=99 fold. Nesting the source conditions changes
no comparison-window bytes; that control is not retained.

## Physical tail ownership and controls

**Observed:** target861's initial nonzero-sequence edge reaches61C2A7, and
its post-payload/call edges reach61C27E. These tails are physically assigned
to826 by the decoded owner audit. The candidate carries a phase-counter
block and part of the sequence-one X/Y/alpha/scale tail in861. Thus the
preceding427-byte candidate861 span versus358 target did not establish an
extra69 bytes of arithmetic or spills: physical sharing differs.

| Sequential control |Metadata|861 bytes/instructions|Raw diagnostics|
| --- | ---: | ---: | ---: |
| Fresh previous source |19340|427/100|3/34|
| Unsigned floating payloads |19364|453/106|3/34|
| Plus current owner reads, retained |19380|467/109|3/34|
| Nested owner range, byte-neutral |19380|467/109|3/34|

Restoring the two real read boundaries and conversion order increases861's
physical span40 bytes; smaller root metadata gap is not an exactness metric.
826 remains627 bytes/146 instructions versus target660/155.852 remains
1206/312 versus1201/310,855337/82 versus332/78,9001729/412 versus1773/412.
Raw diagnostics remain entry/800/980,3/34;33 destinations/zero splits persist.
No diagnostic owner is newly accepted.

## Verification and remaining work

```bash
python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-giant-action-owners.py aya-object-vslot28 \
  build/match-units/GptWeb_AyaObjectActionState.obj \
  --unit gpt-web-aya-object-vslot28-full-root --json
```

Final configured reports share prefix `build/aya-owner-reads-final-`.
Private controls/read-epoch checker are under
`.analysis/aya-owner-reads-20261002/`; objects and source/object/window-hashed
`controls-summary.json` are under `build/aya-owner-reads-20261002/`.
Private existing-object comparisons lack configured build provenance; the
retained source is independently rebuilt through the configured unit.

Fresh raw traversal again closes4,630 instructions/all19,522 target bytes
through seven switches.124/124 guard checks, two641-value unsignedY checks,
853 select7 immediate-return/current-owner/twelve-role checks,450 mocked
emission-prefix cases, and the RTTI/byte-contract/446-byte translated interval
checks pass against the final object. Mocked calls and nearest-even FSTP32
are scoped diagnostics, not full game/control-word proofs. The mandatory
local CI and whitespace gate must pass before committing. No aggregate cold
replay is claimed. IDA fails target identity and is not used; no new Ghidra
process is required for these bounded raw PE facts.

Remaining work includes861/826 tail placement,852 facing/FILD/FLD/scratch
homes, other action values/lifetimes, and original TU/LTCG context. Nested
range spelling is byte-neutral; do not repeat it as a matching strategy.
Follow independent target dataflow/type or compiler-context evidence. TH08's
special x87 instruction examples do not justify assembly for this interval,
whose recovered FILD/FSUB pattern is already naturally emitted by VC8 C++.
