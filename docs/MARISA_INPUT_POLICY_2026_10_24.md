# Marisa input policy: complete source checkpoint, nonexact

## Current result

Marisa Fighter primary slot `+0x50 @ 0x004B9FA0` has a complete reviewed source
body covering **7,664 callable bytes** and both adjacent switch tables. The
selected source emits the complete target-sized **7,768-byte payload**, replays
all **180 relocations**, and remains **nonexact**. Canonical first difference:
`+0x1AF5 / 0x004BBA95`, target76 / source3B. No `matches.csv` row is added.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-marisa-input-policy --compare --json
python3 scripts/audit-marisa-input-policy.py
```

Both comparison commands currently return1 with the recorded mismatch. The
full audit requires exact section-tail length and uses the same strict COFF
owner/relocation/literal checks; it does not mask the residual. Local CI must
still pass before commit/push. Source-present and exact remain separate states.

Selected complete canonical SHA256:
`53acd36513eee03fe5ea95775c31ff5827e4ec01d903fb2abef9bbc71983fd1c`.
Target complete SHA256:
`934f930a181ddaa5c5cc5963c057678acb39d28b5a4a46bf19ad1b415b691d82`.
There are104 differing callable bytes between `0x4BBA95..0x4BBB37`; all104
adjacent metadata bytes match. The equal lengths, physical call counts and
matching metadata are diagnostic evidence, never exact credit.

The source in `src/characters/MarisaInputPolicy.cpp` uses numeric commands,
actual field widths, a pointer-only polymorphic view and declaration-only
callees. Never construct or embed the views. Original names, full layouts,
ignored-return declarations and original TU/compiler context remain unknown.
No assembly, target arrays, artificial padding, inert locals, fake returns,
ABI/register forcing or compiler-profile search were introduced.

## Observed target facts

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The frozen roster RTTI anchor binds cell `0x006C45D4` to Marisa primary
slot `+0x50`; a raw aligned-pointer scan independently reads the same address.
Existing authored ownership/evidence is unchanged.

Raw traversal closes all **2,151 instructions**, **36 RETs**, **15 external
tails**, every direct/internal edge, and both actual indirect tables. The
callable ends exclusively at `0x4BBD90` after the tail JMP at `0x4BBD8B`.
There is no alignment gap before the20-entry table at `0x4BBD90..0x4BBDDF`.
The six-entry table immediately follows at `0x4BBDE0..0x4BBDF7`; subsequent
INT3 padding is excluded. Ground record203 shares its603 finalizer with the
air table, and air205/207 share the ground605/607 finalizers. Tables cannot
be inferred from the peer's eight-entry layout.

The frame reserves eight bytes and saves EBX/EBP/ESI/EDI. There are168 physical
calls:136 direct and32 virtual action-slot+08 calls. Direct calls comprise five
stage predicates, six deque subscripts, two front predicates,21 finalizers,
62 command-window queries,31 packed-input initializations and nine other gates.
External tails go once to45DDA0, once to464200 and13 times to4633A0.
The object has151 REL32 fields and29 DIR32 fields: one float reference, two
table bases and26 destination pointers. The existing float90.0 binding at
`0x006C3D8C` is independently read; no global relocation mappings change.

## Reviewed complete behavior

[Sakuya's accepted source](SAKUYA_INPUT_POLICY_2026_10_24.md) supplies a hypothesis;
complete raw byte/edge/argument review and attested Ghidra views independently
check each changed path. Decompiler expressions are not pasted as source.

| Surface | Native behavior retained |
| --- | --- |
| Queued commands | Ground200..219 finalize600..619; air203/205/207 finalize603/605/607, air208 finalizes658. |
| Special dispatch cleanup | Writes float+12C=0 after action selection on every special-command path. |
| Ground masks400/200 | +60D531/530, +609526/525, then521/520 through flag+755. |
| Ground masks4/2 | +60F571/570, +60B566/565, then561/560 through flag+757. |
| Ground masks40/20 | +60C510, +608506/505, then500 through flag+754; preserve actual common successes. |
| Ground high-bit masks | +60E551/550, +60A545, then541/540 through flag+756. |
| Air masks4/2 | +60F573/572, +60B568/567, then563/562 through flag+757. |
| Air masks40/20 | +60C512, +608506/505, then500 through flag+754. |
| Air high-bit masks | Both +60A/+60E must be zero; each independently queries542 through flag+756. |
| First normal group | Retains Sakuya305 transition,321-to322 shortcut, float90.0 and independent air308 attempts. |
| Group+6F8 | Performs the normal402/401/400 or406/404 action first, then reads signed word+7A6 and may perform421/420/422, then resets input.408 has no such extra action. |
| Group+6FC ground | Queries412 twice independently; either success reaches the mode gate selecting431 or412. Neutral411/fallback410 select430 when mode is positive.418 bypasses the mode replacement. |
| Group+6FC air | Actual415/416/414 gates retain their order/repeated eligibility and select432 instead when the mode word is positive. |

The mode read in group+6F8 is after the first virtual action; it must not be
hoisted or replaced by an action-number ternary. The group+6FC mode read is
before its selected action. Declaration-only helpers receive no new credit.

## Evidence-backed trials and stop condition

The first complete build (probe00) emits7,780 bytes. I initially misread the
second412 success edge as bypassing the mode test. Full comparison exposes
that missing behavior: raw `0x4BBB36` is `JLE 0x4BBAD1`, entering the same real
mode gate as the first query. Probe01 corrects the behavior and emits7,788 bytes,
but duplicates the complex success body's mode/vptr work.

Probe02 combines the two independently evaluated success guards with ordinary
short-circuit OR around their single common body. This preserves query order,
repeated field reads and the real mode gate, recovers the7,768-byte extent and
all table bytes, and leaves one physical placement difference: target puts the
mode/action block before the second query and branches backward into it; the
source puts both queries before the common block. Instruction-sequence alignment
only diagnoses this movement; strict comparison remains failed.

Probe03 expresses an explicit label at the real common success body and branches
the second query to it. The entire canonical payload is byte-identical to
probe02. Retain probe02's ordinary condition; do not repeat OR/label controls
unchanged. Following the user's stop rule, park this physical-placement residual
and continue another complete peer. No LTCG impossibility or original-source
spelling is established. A new independent lifetime/TU fact could reopen it.

## Validation and retained evidence

IDA's required preflight rejects the other executable still open there; no
semantics or writes from that session are used. One read-only Ghidra process
independently attests file/program identity, Windows x86 language/compiler,
image base, entry `0x68B9D2`, every raw-backed mapped section and this root hash.
Temporary metadata is read back and rolled back; pinned primary database files
are unchanged. CPU0/nice10 and384 MiB heap bound analysis; builds are serial.

Private recipes and four source snapshots remain under
`.analysis/exact-first-marisa-slot50-20261024/`. The corresponding `build/`
directory retains raw facts/disassembly, whole-CFG and both table edges,
attestation/logs/database pins, all trial objects/canonical payloads, complete
comparison diagnostics, the neutral-control receipt and residual summary.
Previous five exact input-policy source/header pairs remain unchanged. No broad
runtime matrix, new callee credit or aggregate cold replay is claimed.
