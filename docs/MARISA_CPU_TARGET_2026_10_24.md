## Canonical exact resolution (2026-11-28)

`exact-first-marisa-cpu-policy` now matches `Marisa_update_cpu_action_policy`
(`0x004B4070`) with **zero byte differences** under standalone VC8 SP1
`/O2 /GS- /GR /EHsc /MT` (no `__forceinline` or `/LTCG` required):

- Callable code `[0x004B4070, 0x004B7FD5)`: 16,229 bytes, 46 `RET 0` exits,
  161 direct calls (121 `selector_random_roll`, 27 checked `deque::operator[]`,
  7 `__ftol2_sse`, 5 `atan2_degrees`, 1 `mt19937_next_u32`), SHA-256
  `20a78101afe95044c22b4f8cefde19f80b5138576d2b998efd7ecf9f9f331edf`.
- Complete eight-table switch payload `[0x004B4070, 0x004B827B)`: 16,907 bytes
  (82 destination words, 344 remap bytes, 6 alignment bytes `8d4900` + `8d4900`),
  SHA-256 `390ace272a1567150c1332831c28fb1c252073f80879975b86c6d1e9a30d0e90`.
- Relocations: 405 verified (161 REL32 + 244 DIR32).

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-marisa-cpu-policy --compare --json
```

Four natural C++ fixes closed the function:
1. Replace `if (S(0x766) == 0) { ... goto policy_dispatch; }` and `goto approach_policy;`
   with `switch (S(0x766)) { case 0: ... break; }` and inline approach bodies —
   restoring first-site hosting for both the four `approach` arms and the shared
   `I(0x6B4)=C(0x104); I(0x6B8)=0;` tail without `__forceinline`.
2. Remove `goto expire_policy` / `wait60` / `check214` / `horizontal214` /
   `rising214` and use per-case `break;` in `switch (S(0x766))` cases `1..102` —
   keeping `DURATION(17/16/18, 20, 5)` separate and hosting the shared expire
   tail in `case 11..18`.
3. Use `(C(0x104) == -1) ? 1 : 2` in `case 10`.
4. Remove the spurious `&& I(0x180) == 1` check on `FRONT == 207` in `case 414`
   and `case 416` (`0x004B56E6` jumps to `0x004B474F`, bypassing `0x004B4748`).

---

# Marisa CPU policy: earlier analysis record (superseded by exact match above)

## Current source checkpoint: nonexact

`0x004B4070` is the RTTI-owned Marisa Fighter primary slot+58 CPU action-policy
root, separate from the parked input-policy root `0x4B9FA0`. Complete source is
selected in `src/characters/MarisaCpuPolicy.cpp/.hpp`, with numeric states, typed
offset accesses, pointer-only views and declaration-only helpers. Never construct
or embed either view. No complete nominal layout or original TU is claimed.

The selected full payload is **16867 bytes versus 16907 target bytes**. Strict
canonical comparison remains nonexact at `+0x12E / 0x004B419E`, target 2C/source06,
in the inactive-opponent return branch displacement. Its first 302 bytes match.
This size difference is not an unreconstructed-byte count. Canonical full SHA256:
`b7872facbcbe0e9019026385d84694d52beb3e0d8eeecda5459b3411fda23127`.
The formal manifest build reproduces this payload. **Source-present only; no
matches.csv row or exact-byte credit is added.**

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-marisa-cpu-policy --compare --json
```

The first two commands currently return 1 with the recorded canonical mismatch.
The full audit replays every section-tail relocation, checks the target payload
hash and requires full length/byte equality; no callable/table mismatch is masked.
The third is a scoped execution diagnostic and returns 0. No shared headers,
compiler flags, accepted objects or global relocation bindings are changed.

## Target-backed source revisions

The initial full source (`probe00`) emits 16403 bytes, canonical SHA256
`d2d1f087416a5a0ac1cf7752f5cabea9a5c3d3429fcb82b582831b247f747579`.
Separating four grouped sequence-case labels into independent ordinary case
bodies (`probe01`) restores all eight destination tables with native counts
20/7/7/7/12/3/3/23 and all four remap arrays. Its 16419-byte payload SHA256 is
`ca76b8bb83a1d6ae36d8075693a998c2461d95a05b1416a7df6af803e5045a76`.
The shared-exit control below was neutral in that source phase.

**Observed:** target probability windows use paired signed WORD comparisons;
for example 4B69C2 compares CX to zero then 4B69C9 compares CX to 9. The initial
source's private local-cache predicates compile to unsigned range checks and
LEA/subtract range folding. Replace only the probability-window reads with the
already published WORD76A (`probe03`), retaining the full selector producer and
WORD store. The compiler now retains the native signed comparisons, emits
119 selector sites instead of 110, and restores the target's initial EDI 2,
EBP 32, EDX 600 register allocation. Payload 16839 SHA256:
`c6f8a72a7a382d07d2f067edb57c8b71f0b4f476f87053d69d27481a12a23fff`.
This is direct field-access evidence, not proof of unique original declarations.

**Observed:** sequence 205 in actions 400/401 and 410/411 targets 4B5162. Raw code
compares h with double 500; for the lower path it loads v, writes DWORD6D0=2,
compares v with double100 and reads x87 status before joining 5362. The first
source omitted the v predicate because decompiler output discarded its result.
The earlier `probe04` retains the natural `h<500.0 && v<100.0` predicate before
the real shared sequence fallback. It reproduces those target instructions,
without an artificial volatile read, unused temporary or synthetic padding.
Both branches still publish the native input value. Original high-level reason
for the apparently redundant final predicate remains unknown.

## What the complete comparison resolved

Decoded CFG phase traversal stops at common attack/policy joins. Selector counts
are target 24/source24 for actions and 57/57 for attacks. Other helper counts also
agree: actions five conversion/one MT/eight deque/three atan2; attacks two
conversion/19 deque/two atan2. Final movement policy is now 40 native versus 38
source, superseding the previous 40/29 result. The two missing physical copies
are the duration tails for policy 17/16, merged with policy 18's20-bound/+5 tail.
The selected source now has 45 RETs versus 46 target. Counts and token alignments
are diagnostic only. No overall similarity percentage or partial exact credit
is inferred.

## Native control flow and operand follow-up

Source `probe05..probe22` makes each change against a specific raw discrepancy:

| Trial | Question and observed result |
| --- | --- |
|05|Use the target's coordinate-comparison operand order. Scalar load/flag forms change; no fresh ABI or gameplay names. |
|06|Use the observed integer angle thresholds >=30/50/20 instead of equivalent >29/49/19. Native CMP/SETGE forms return. |
|07|Keep the genuine conversion result in an int and consume its signed low WORD. Two extra MOVZX instructions disappear. |
|08|Use real early exits in the first action switch. All 1291 reachable first-stage instruction forms align, retaining target common join 5362. External epilogue/table references still differ; this is not a canonical match. |
|09|Retain actual unsigned probability/resource endpoints and peer-state <=95/>=140 guards. Native comparison immediates/branches return. |
|10|Rejected: a mistaken shared-tail ownership inference changed descending input 1 to 0. Real MT execution and CFG ownership disprove it; public source never selected it. |
|11|Put the grounded-opponent air branch first, following 604F/6052. Both posture bodies and their distinct vertical outputs remain. |
|12/14|Recover ordered rising/falling/velocity predicates from x87 flags, then the actual height-operand order. Native zero lifetimes and branch forms return. |
|13|Express the ordered >=300 distance guards. Native TEST AH,1 forms return at all four gaps. |
|15|Retain the actual repeated peer-height check at 7401/7412 and its native return edge. This is a target-observed reread, not an inserted volatile dependency. |
|16|Retain the actual near-air height operand order. The extra reversed comparison disappears. |
|17|Express shared horizontal/upward policy 214 output tails as ordinary labels. Native output-store sharing returns. |
|18|Move approach assignment into the first passing window with later gotos. Entire canonical output is neutral against 17; keep its receipt. |
|19|Use the native early timer/unsigned RNG guards in policies 1/2. Two separate epilogues disappear; no threshold/behavior change. |
|20|Put h before the computed angle-request threshold. Native x87 load/flag order returns in both posture bodies. |
|21|Fix a real equality error: ground resource attack gate is h>=180, not h>180. |
|22|Retain the ordered >320 vertical guard from 77E2..77F1. Selected complete output is 16867 bytes; still nonexact. |
|23|Unselected repeated approach-assignment control changes a few branch/layout bytes but still leaves its block out of line and two policy-duration calls merged. Not an acceptance or reason for further spelling search. |
|24|Unselected independent posture-guard arrangement emits 16815 bytes/116 selector sites; it loses three more native physical copies and does not reproduce the repeated-guard structure. Retain selected 22 and the alternative receipt. |

The full comparator still differs at+12E. Residual instruction forms are now
limited to approach 100 block placement, one shared facing-output tail, two
merged policy 17/16 duration-call tails and minor store/scheduler order. Source
first-stage1291 and attack 1254 instruction counts agree with the target; final
movement 1605 versus 1619 differs. Counts do not establish full edge equality.
The selected common policy join is 6943 versus target 6941. Original TU/compiler
phase remains unknown; no standalone-object impossibility or LTCG-only claim
is proved. Keep the source and receipts, park unchanged text/visibility/profile
controls, and switch to another complete representative unless independent
source/lifetime evidence reopens this residual.

## Scoped execution and a real boundary regression

The earlier selected sources passed 1056 diagnostic inputs. The current public
auditor runs **1134**: the same 460 action windows/84 sequence edges/64 attack
inputs/404 policy 0 inputs/44 terminal policies, plus four h180 boundary inputs,
two positive posture-tail inputs and 72 ordered-velocity inputs. Policy 0 still
uses all 101 real selection rolls in four posture/distance bands. Native target
execution confirms every seed/roll, both descending-tail button/vertical outputs and visits to
the exact 64A3/692F instruction sites before comparing the candidate. No helper result is substituted.

At h180, raw 5BD3 loads float 180 and compares it against h. TEST AH,41/JP
rejects h<180 or unordered, retaining equality. The previous >180 source skipped
real RNG/control paths. All four new boundary inputs reject pre-fix `probe20`,
while selected 22 passes 1134/1134. This is a real behavior regression, not a
codegen score. Its full actor fields, RNG state, call trace, stack cleanup and
x87 stack checks agree. New vector SHA256:
`7444616d3d2f7df51d9151b06d0ac4e76e78b8e41e35bd3b12fb5c5a28645de1`.

The descending-input false lead is resolved by an explicit positive control:
real seed 54, h250 and selfY300/peerY0 reaches 64A3/64A9 and publishes vertical 1;
selfY400/peerY100 reaches 692F/6935 and publishes 0. The attempted zero-output
change was rejected, not a public correction. Private seed search receipts are
bounded diagnostics; the two durable positive inputs remove any need to repeat
the search. Velocity inputs target the specific ordered comparison question,
including quiet NaN and signed finite velocities. Sampled execution remains
separate from canonical equality and exhaustive behavior.

## Bounded follow-up receipts

The native target has 46 RETs; the initial selected source had 38. A single follow-up replaces
early returns in the final movement-policy section with a shared ordinary exit
label (`probe02`). The complete canonical output remains byte-for-byte identical
to the earlier 16419-byte payload above, with 110 selector calls and 38 RETs.
This rejects the simple return-versus-shared-exit spelling explanation for the
remaining duration-call copies. The historical source was retained; do not repeat this
neutral control without new target/compiler evidence. No second execution matrix
is needed for an identical canonical payload.

The public native-path auditor also rejects a generated-COFF negative control:
changing the source's real `mov edx,2` output constant at+144 to 3 produces 145
mismatches among the same 1056 inputs and returns 1. This is a private generated
object only; the target PE and public source are unchanged. The negative payload
SHA256 is `e11c16b382f87bce26cf32aee0091f85262788ce51c181e783e5af6901cc064b`.
`probe02.diagnostic.json`, the generated negative object and `negative-paths.json`
are retained below the same build scope. Local CI and whitespace gates pass
before saving each stable checkpoint.

## Observed target and ownership

Only original Japanese 1.06a SHA256
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
active-opponent path. The entry reserves 12 bytes. A void `__thiscall` is the
existing source call-view, not a proof of original nominal C++ declarations.

Callable SHA256:
`20a78101afe95044c22b4f8cefde19f80b5138576d2b998efd7ecf9f9f331edf`.

The complete target payload is **16,907 bytes** through exclusive `0x4B827B`.
It includes 328 destination bytes,344 index bytes and six actual alignment bytes.
It is structural evidence, not a source object or authored-byte extension.
Target payload SHA256:
`390ace272a1567150c1332831c28fb1c252073f80879975b86c6d1e9a30d0e90`.

| Metadata address | Complete observed surface |
| --- | --- |
|4B7FD5..4B7FD7 |Three-byte LEA alignment after the last RET. |
|4B7FD8 |20 destinations for the first action switch. |
|4B8028 |217 index bytes for actions 200..416; unsigned guard 216. |
|4B8101..4B8103 |Three-byte LEA alignment between index/table data. |
|4B8104,4B8120,4B813C |Three independent seven-destination sequence switches,205..211. |
|4B8158 |Twelve destinations for sequence 200..211. |
|4B8188 /4B8194 |Three destinations plus twelve index bytes. |
|4B81A0 /4B81AC |Three destinations plus twelve index bytes. |
|4B81B8 /4B8214 |23 movement-policy destinations plus 103 index bytes for policies 0..102. |

All 82 destination entries and 344 index entries are read from the attested PE.
The first action switch has 23 actual selector values sharing 19 action bodies
plus the default. The final switch includes 0..18 and 100/101/102, with the real
default for gaps. No table is sized by copying a peer's candidate or assuming
that a following function begins immediately after it.

There are **161 physical direct calls**:121 selector calls at 4067D0,27 checked
deque accesses at 4399C0, five atan2 calls at 406540, seven float-to-int conversion
calls at 68A1A0 and one MT draw at 4066B0. Their target spans/hashes, call sites and
existing ledger states are retained. RNG/atan2 have prior accepted units;
deque/runtime dependencies remain excluded. None receives fresh credit.

Temporary ABI readbacks confirm cdecl RNG/selector, cdecl float atan2 returning
ST0, checked-deque ECX receiver/RET4, and the root's ECX/RET0 view. Existing
conversion metadata reads float 10 ST0 input and EAX 32 output. Source must use
normal cast expressions rather than inventing an ordinary conversion-helper
declaration. The excluded conversion island's ledger boundary stays provisional.

## Source-shape evidence and limits

Raw entry clears DWORDs724/728, derives the two integer-absolute distances from
opponent 170 coordinates via native conversion, decrements WORD768, and clears
six control DWORDs6BC..6D0. Signed WORD13C and policy/counter WORDs764..76E
drive the switches. Literal observations retain every actual F32/F64 width;
constants include float 80/90/150/300/320/350/520/600/700 and double 50/60/100/
120/200/210/220/240/250/400/500. No equivalent-looking float/double spelling is
selected without compilation evidence.

**Observed:** final policies 100/101/102 each publish facing input and clear
button controls. While the timer is positive, state 200 can request different
buttons at the actual distance thresholds 220/320/320 respectively. All retain
the timer-expiry RNG path. These two additional policies are absent from the
current Reimu representative. Other differences include the first action
switch, sequence choices, resource gates, probability windows and policy 0
distance partitions. Complete source covers these paths; original gameplay
names remain provisional.

**Diagnostic only:** an instruction-token alignment of the two native final
policy regions pairs 1444 instructions from Reimu 1637 and Marisa 1614. It keeps
ordinary operand spellings but suppresses direct branch destinations solely
to locate differences. Its 456-line difference record is not a CFG equivalence,
byte score, acceptance, or permission to reuse all unmatched semantics. Shared
regions still require edge/width/side-effect review in the complete source.
Original source variables, full owner layout, TU and compiler phase are unknown.

## Attestation and retention

IDA preflight rejects the different executable still open there; no semantics
or writes from that session are used. One CPU 0/nice10 read-only Ghidra process,
with 384 MiB heap, independently attests executable/program hash, Windows x86
language/compiler, image base, entry 68B9D2, every raw-backed section and the root
hash. Root min/max/count matches the raw extent. Temporary function/type changes
are read back and rolled back; pinned primary DB files remain unchanged.
Decompiler output is a hypothesis and has not been pasted into source.

`probe10` is rejected; `probe18` is neutral;
`probe23`/`probe24` are unselected. `formal-refined-paths-pinned.json` adds
per-input instruction-site attestation for the two posture witnesses. The initial
target-only receipt is historical; the public source/unit and current comparison
above supersede its source-selected flag. No target bytes are patched. Earlier CPU
and input sources, compiler flags, layouts, object units and relocation ledgers
remain unchanged.
