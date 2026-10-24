# Marisa CPU policy: complete source checkpoint, nonexact

## Current source checkpoint: nonexact

`0x004B4070` is the RTTI-owned Marisa Fighter primary slot+58 CPU action-policy
root, separate from the parked input-policy root `0x4B9FA0`. Its complete source
is now selected in `src/characters/MarisaCpuPolicy.cpp/.hpp`, with numeric states,
typed offset accesses, pointer-only views and declaration-only helpers. Never
construct/embed either view. No complete nominal layout or original TU is claimed.

The first full source emits16403 bytes versus16907 target bytes. Canonical first
mismatch is `+0x12E / 0x004B419E`, a displacement in the inactive-opponent return
branch; the preceding302 bytes match. Full canonical SHA256 is
`d2d1f087416a5a0ac1cf7752f5cabea9a5c3d3429fcb82b582831b247f747579`.

One target-backed trial separates the four grouped sequence-case labels into
ordinary independent case bodies. The first source range-folded these tables;
the trial emits all eight destination tables with the native counts
20/7/7/7/12/3/3/23, retaining all four remap arrays. This source is selected for
its explicit switch structure, not a byte score. It emits16419 bytes, including
675 adjacent metadata/alignment bytes; target metadata/alignment is678. Its
first mismatch remains+12E, target2C / source47. Canonical full SHA256:
`ca76b8bb83a1d6ae36d8075693a998c2461d95a05b1416a7df6af803e5045a76`.
The formal manifest build reproduces that payload. **Source-present only; no
matches.csv row or exact-byte credit is added.**

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-marisa-cpu-policy --compare --json
python3 scripts/audit-marisa-cpu-policy.py
taskset -c 0 nice -n 10 python3 scripts/audit-marisa-cpu-policy-paths.py
```

The first two commands currently return1 with the recorded canonical mismatch.
The full audit replays every section-tail relocation, checks the target payload
hash and requires full length/byte equality; no callable/table mismatch is masked.
The third is a scoped execution diagnostic and returns0. No shared headers,
compiler flags, accepted objects or global relocation bindings are changed.

## What the complete comparison resolved

Decoded CFG phase traversal, stopping at the common attack/policy joins, finds
24 selector call sites in both action phases and57 in both attack phases. Their
other helper counts also agree: actions five conversion/one MT/eight deque/three
atan2; attacks two conversion/19 deque/two atan2. The physical selector deficit
is confined to final movement policy: target40 versus source29. Raw source and
output inspection therefore replace the initial undifferentiated110-versus121
call-count question with a concrete policy-tail/codegen question. Call counts
alone never prove semantic equivalence or a missing path.

A small native-helper diagnostic addresses action-window boundaries, sequence
switch edges, independent attack draws and policy0 duration-call merging. Both
full source versions pass the same1056 cases:460 action windows,84 sequence
edges,64 attack-call inputs,404 policy0 inputs and44 terminal-policy inputs.
Policy0 uses all101 real native selection rolls in four distinct posture/distance
bands. Native target execution confirms every seed/roll; RNG, deque, atan2 and
conversion calls all execute original PE code, without substituted results.
Complete actor fields, RNG state, helper-call trace, stack cleanup and x87 stack
checks agree. Vector SHA256:
`c1fb30f56362c0f32e2ef47c4af1e4a5c582490fa57f951de890513211c0f1ee`.
This sampled execution result is diagnostic only, not exhaustive behavior or
canonical equality. Policies101/102, all numeric windows and field widths are
reviewed independently rather than copied unchanged from Reimu.

Next investigate the final movement-policy return/shared-duration structure
against actual branch/call evidence. Register allocation diverges after the
matching prefix, and the selected payload is488 bytes shorter overall. Do not
repeat visibility/FP/profile controls from earlier CPU attempts or expand an
execution matrix without a specific ambiguity. Retain each trial and switch
candidates after neutral controls; no register forcing or padding.

## Bounded follow-up receipts

The native target has46 RETs; selected source has38. A single follow-up replaces
early returns in the final movement-policy section with a shared ordinary exit
label (`probe02`). The complete canonical output remains byte-for-byte identical
to the selected16419-byte payload above, with110 selector calls and38 RETs.
This rejects the simple return-versus-shared-exit spelling explanation for the
remaining duration-call copies. Keep the selected source and do not repeat this
neutral control without new target/compiler evidence. No second execution matrix
is needed for an identical canonical payload.

The public native-path auditor also rejects a generated-COFF negative control:
changing the source's real `mov edx,2` output constant at+144 to3 produces145
mismatches among the same1056 inputs and returns1. This is a private generated
object only; the target PE and public source are unchanged. The negative payload
SHA256 is `e11c16b382f87bce26cf32aee0091f85262788ce51c181e783e5af6901cc064b`.
`probe02.diagnostic.json`, the generated negative object and `negative-paths.json`
are retained below the same build scope. Local CI and whitespace gates pass
before saving each stable checkpoint.

## Observed target and ownership

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The existing roster Fighter RTTI anchor binds primary slot+58 cell
`0x006C45DC` to `0x004B4070`; a raw read independently confirms that pointer.
Authored origin and its existing evidence rule remain unchanged.

The callable closes **16,229 bytes**, **4,159 instructions**, **46 RETs** and
every direct/indirect edge. Start is `0x4B4070`, inclusive last byte `0x4B7FD4`,
exclusive end `0x4B7FD5`. Every decoded instruction is reachable from the entry
under the complete destination tables. There are no external tail jumps or
indirect calls. All returns have no stack-argument purge. The observed receiver
is ECX, retained in ESI; EBX/ESI/EDI are saved at entry and EBP is saved on the
active-opponent path. The entry reserves12 bytes. A void `__thiscall` is the
existing source call-view, not a proof of original nominal C++ declarations.

Callable SHA256:
`20a78101afe95044c22b4f8cefde19f80b5138576d2b998efd7ecf9f9f331edf`.

The complete target payload is **16,907 bytes** through exclusive `0x4B827B`.
It includes328 destination bytes,344 index bytes and six actual alignment bytes.
It is structural evidence, not a source object or authored-byte extension.
Target payload SHA256:
`390ace272a1567150c1332831c28fb1c252073f80879975b86c6d1e9a30d0e90`.

| Metadata address | Complete observed surface |
| --- | --- |
|4B7FD5..4B7FD7 |Three-byte LEA alignment after the last RET. |
|4B7FD8 |20 destinations for the first action switch. |
|4B8028 |217 index bytes for actions200..416; unsigned guard216. |
|4B8101..4B8103 |Three-byte LEA alignment between index/table data. |
|4B8104,4B8120,4B813C |Three independent seven-destination sequence switches,205..211. |
|4B8158 |Twelve destinations for sequence200..211. |
|4B8188 /4B8194 |Three destinations plus twelve index bytes. |
|4B81A0 /4B81AC |Three destinations plus twelve index bytes. |
|4B81B8 /4B8214 |23 movement-policy destinations plus103 index bytes for policies0..102. |

All82 destination entries and344 index entries are read from the attested PE.
The first action switch has23 actual selector values sharing19 action bodies
plus the default. The final switch includes0..18 and100/101/102, with the real
default for gaps. No table is sized by copying a peer's candidate or assuming
that a following function begins immediately after it.

There are **161 physical direct calls**:121 selector calls at4067D0,27 checked
deque accesses at4399C0, five atan2 calls at406540, seven float-to-int conversion
calls at68A1A0 and one MT draw at4066B0. Their target spans/hashes, call sites and
existing ledger states are retained. RNG/atan2 have prior accepted units;
deque/runtime dependencies remain excluded. None receives fresh credit.

Temporary ABI readbacks confirm cdecl RNG/selector, cdecl float atan2 returning
ST0, checked-deque ECX receiver/RET4, and the root's ECX/RET0 view. Existing
conversion metadata reads float10 ST0 input and EAX32 output. Source must use
normal cast expressions rather than inventing an ordinary conversion-helper
declaration. The excluded conversion island's ledger boundary stays provisional.

## Source-shape evidence and limits

Raw entry clears DWORDs724/728, derives the two integer-absolute distances from
opponent170 coordinates via native conversion, decrements WORD768, and clears
six control DWORDs6BC..6D0. Signed WORD13C and policy/counter WORDs764..76E
drive the switches. Literal observations retain every actual F32/F64 width;
constants include float80/90/150/300/320/350/520/600/700 and double50/60/100/
120/200/210/220/240/250/400/500. No equivalent-looking float/double spelling is
selected without compilation evidence.

**Observed:** final policies100/101/102 each publish facing input and clear
button controls. While the timer is positive, state200 can request different
buttons at the actual distance thresholds220/320/320 respectively. All retain
the timer-expiry RNG path. These two additional policies are absent from the
current Reimu representative. Other differences include the first action
switch, sequence choices, resource gates, probability windows and policy0
distance partitions. Complete source covers these paths; original gameplay
names remain provisional.

**Diagnostic only:** an instruction-token alignment of the two native final
policy regions pairs1444 instructions from Reimu1637 and Marisa1614. It keeps
ordinary operand spellings but suppresses direct branch destinations solely
to locate differences. Its456-line difference record is not a CFG equivalence,
byte score, acceptance, or permission to reuse all unmatched semantics. Shared
regions still require edge/width/side-effect review in the complete source.
Original source variables, full owner layout, TU and compiler phase are unknown.

## Attestation and retention

IDA preflight rejects the different executable still open there; no semantics
or writes from that session are used. One CPU0/nice10 read-only Ghidra process,
with384 MiB heap, independently attests executable/program hash, Windows x86
language/compiler, image base, entry68B9D2, every raw-backed section and the root
hash. Root min/max/count matches the raw extent. Temporary function/type changes
are read back and rolled back; pinned primary DB files remain unchanged.
Decompiler output is a hypothesis and has not been pasted into source.

Private replay recipes are under `.analysis/exact-first-marisa-cpu-20261024/`:
`raw.py`, `setup.py`, `facts.py`, the Java script and read-only launcher, plus
first-source `probe00`, independent-case `probe01`, full normalization/difference,
phase traversal and native execution recipes. Generated
evidence is under the corresponding `build/` directory: raw disassembly/facts,
full CFG and12 tables, callee/literal observations, attested call-view and logs,
DB hashes, initial scope summary, retained-input hashes, native-tail diagnostic,
probe00/probe01 payloads/reports, phase call-site partitions and formal-build/
formal-paths receipts. The initial target-only receipt is historical; the public
source/unit and current comparison above supersede its source-selected flag.
No target bytes are patched. Earlier CPU and input sources, compiler flags,
layouts, object units and relocation ledgers remain unchanged.
