# Aya Fighter action state 00602250

Complete manual source now covers all 114 actions and the default. The selected
whole canonical replay remains **nonexact**. Source presence, matching call
counts and switch topology do not earn exact-byte credit.

## Canonical target and ownership

Japanese 1.06a SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The existing authored primary-vtable anchor is rechecked directly: primary
vtable 6C62D4, slot 28 cell 6C62FC ->602250, COL 6DB828, TD6E8E30 `.?AVAya@@`.
The adjacent CPU policy 6126E0 and all accepted shared dependencies are unchanged.

Callable [602250,612291) is 65601 bytes, SHA256
`04c7620574e00d6f05bb615a095188ee2c60e94cc9d94dbad2eed56b92ab7fd5`.
16858 instructions decode;16856 instructions/65593 bytes are reachable.
Only [6100E8,6100F0) is alignment, an eight-byte JMP/LEA sequence.
There are 146 RET 0s,199 virtual sites and 1011 direct sites to 33 targets.
Native ESP alignment is 8 and frame allocation is 3E8.

Complete payload [602250,6126E0) is 66704 bytes, SHA256
`42401b4701e475fbaab7d19a542aec6edbe503082a2a0dc2a2e22407e71903a3`.
Three-byte LEA alignment precedes the metadata. Seven table dimensions are
33/27/48/4/4/4/8; the three remaps contain 227/118/239 bytes. Their domains are
0..226,301..418 and 502..740, with the final direct table 791..798. Sparse maps
cover 111 action labels; direct 300/500/770 complete the 114. All table targets,
remap ranges and intervening alignment are covered by the raw audit.

## Analysis and source evidence

Local IDA preflight lacked its pinned MCP runtime, so that session was not used.
The separately target-attested Factory-native session worked for metadata,
entry, mapped bytes and inventory, but Aya decompilation failed. Work continued
through Factory repository Bash with the already installed Ghidra 12.1 toolchain.
A fresh isolated project checked executable SHA, imported SHA, image base,
x86 language, Windows compiler specification, entry 68B9D2, every mapped virtual
.text byte and the complete bounded body before analysis. The old Iku project
was not changed. No target bytes or IDA database metadata were changed.

The full Ghidra navigation export completed. Thirty-two existing ordinary
callee contracts and actual sequence virtual slots were separately applied to
that isolated analysis and read back; the compiler conversion intrinsic was not
given a fabricated ABI. Ghidra still warns about 17 removed blocks and stack
spacebase tracking. Raw CFG reaches those blocks; decompiler output is therefore
not authority for deleting them or copying its source mechanically. Unsigned RNG
conversions, omitted ST0 consumers, literal widths and unordered predicates were
reconstructed against instructions. First compilation waited for the full root.

The pointer-only receiver inherits the established AnimationSequenceObjectView.
All scalar offsets, callback-sensitive reloads and actual packet arrays remain
explicit. Motion uses this+4;740's periodic wave uses owner 168. Crossed-surface
and on-surface callers inspect AL while retaining the established int-returning
callee contracts. Direction arithmetic is signed-byte; effect/spawn carriers
retain the observed unsigned-byte value. No allocation extent is claimed.

Several raw corrections are material: jump 6..8 has no 144 time gate;307/418's
minimum-speed path writes 74C rather than 73C;502's Y offset is 76, not 100;
508's fan advances +20 with +30 origin, unlike 506's negative fan.565/567 capture
Y as QWORD before surface(), and their flag includes unordered comparisons.
662 also uses a QWORD Y capture.740 keeps QWORD coordinate captures across RNG
and the native addition associations. Distinct action/sequence/height/zero-motion
landing orders are retained rather than collapsed into one generic policy.

529 retains an uninitialized packet when its selector is outside the observed
-2..2 branches.530/532 initialize only the first two words of a three-word
request. These are bounded source hypotheses, not proof of the original type,
initialization domain or exception behavior; no fallback values are invented.

## Whole replay and controls

Unit: `exact-first-aya-action-state`.
Command: `scripts/repo-python scripts/build.py --unit exact-first-aya-action-state --compare --json`.
Audit: `scripts/repo-python scripts/audit-aya-action-state.py`.

The first complete candidate was 65752 bytes. Explicit branch-owned virtual calls
for 10/200 and separate entry guards for 414/416 restore their native per-action
virtual-site counts.540's separated guards remain physically merged; an actual
shared ground continuation for 528 changes layout but does not close its residual.
No further label spelling or register coercion is justified by these controls.
The raw 508 fan correction is retained independently of its comparison result.

The initial checkpoint full candidate was 65784 bytes, SHA256
`4cf50d1d4991f3505b861e23b3081f2e0bc8a1e948b102e62c57239930a075d6`.
First difference+8 /602258 is frame 3F0 versus 3E8.63316 unmasked positions differ,
including missing/extra bytes. Candidate 147 RETs,195 virtual sites and 1003 direct
sites reflect different physical sharing. Low table 31 versus native 33 merges
additional owners; the other six dimensions agree. Remap lengths all agree;
only the 118/239-byte mid/high remaps are byte-identical.

A private complete-CFG traversal from each action entry finds identical direct
callee counts for all 114 actions. Virtual counts differ only 528 (7/8) and 540
(8/7). Floating-operation counts differ only 214,510 and 740; for 510, raw opposite
layer paths duplicate the X-coordinate addition while the candidate shares it.
These are omission diagnostics, not opcode, operand, semantic or byte acceptance.
Remaining frame bytes, control sharing, scalar lifetimes and FP scheduling remain
unresolved. The original TU/LTCG context and complete nominal layout are unknown.

The
formal public build reproduces the selected private payload exactly.145 isolated
aliases are appended; existing aliases, shared ABI, compiler profile and accepted
sources remain unchanged. Only the affected unit is built. matches.csv is unchanged;
no new whole-corpus replay or exact percentage is claimed.

## Two-word request homes and shared continuation

The subsequent whole-root caller-stack audit resolves 85 request homes on both
sides, without unknown pointers. Native 530/532 use homes 636/628; neighbouring
612/662 requests occupy 620/612, and another request begins 644. Each 530/532
setup writes exactly two words but still forwards count 3. The first draft's
three-element arrays added eight bytes beyond these observed stack-home intervals.

A two-word representation restores frame 3E8 without padding, inert locals or
ABI changes. The forwarded count remains 3. This preserves an apparent caller/
callee size mismatch, not a recovered nominal C++ type: the third word's meaning,
original aggregate boundaries and initialization domain remain unknown. No third
value is synthesized. The native path converges at 60AAC6 through one actual 817
request continuation. Two genuinely live function-scope records and a typed
pointer now express that continuation without a pointer escaping a block lifetime.
This reduces the complete candidate by 64 bytes. It is source/dataflow evidence,
not a claim that all physical call sharing is recovered.

Current selected full payload is 65720 bytes, SHA256
`032d6be21c2ba353607229f9b9a9b838ce017fd00e00ff817761fbda6accdcc9`.
Frame 3E8 now agrees; first mismatch+18 /602262 is native EBP versus candidate
EBX zero-carrier allocation.63396 positional differences remain. The old 63316
count is not an improvement score: changed register allocation shifts widespread
bytes. Candidate 147 RETs/196 virtual sites/1003 direct sites remain nonexact.
All 114 per-action direct-call censuses still agree; virtual/FP residuals and low
owner merges remain as described above.

The updated payload audit still resolves 85 homes and every normal stack join;
530/532/612/662 now have the same 636/628/620/612 homes as native. First payload
home 44 also agrees. Some other home ordering remains different. Candidate
60A1A2 was explicitly qualified as slot 0C via EDI=[ESI]+0C preserved across
435DC0, then EAX=[EDI], ECX=ESI; it was not assigned a purge by guess. Native
609565's surface result is tested in AL after an intervening FLDZ, so the older
immediate-next-instruction diagnostic reports false without an ABI mismatch.

The formal source reproduces the private payload; no exact ledger changes.

## 2026-10-29: scalar and call-argument lifetimes

New full candidate 65692/native66704, canonical payload SHA-256
73065d6a8c782cc22eff170bc8efcfd48ba32376edc6d288fbe3c1cb30bed129.
Frame 3E8 remains native; first difference moves to+48/602280, a register
operand in the initial action comparisons.63495 whole-payload positions differ,
including length. This is still nonexact, with no byte credit. The normal
build report compares the 65601-byte ledger callable; formal-audit.json also
compares the entire 66704-byte native code/alignment/switch payload and every
relocation. Their compared hashes have different extents and are not substitutes.

Three independently observed source lifetimes replace earlier merged forms:

- Action 214: native 603D66..603D7A tests selector 4B8==0 first, then performs
  separate +2/+1 additions. The negative branch 603D89..603DAF similarly selects
  -2/-1 arithmetic. Ordinary explicit branches now preserve that operation
  graph instead of choosing a right-hand ternary constant before one addition.
- Action 740: thirteen native 903 spawn preparations put count 3, request pointer,
  layer and facing on the outgoing argument stack before the first of the two
  coordinate-jitter RNG calls. All thirteen cosine-to-RNG prefixes are recorded
  in orbit-call-facts.json, from 610961/61099C to 611AE0/611B21. Keep the real
  captured double baseY/baseX and facing, but express the final Y/X random
  offsets as actual spawn arguments, not separate float locals. The native
  Y-RNG then X-RNG order, request homes and counts are retained.
- Action 510: native 608DA0..608DDD and 608DE1..608E1A independently prepare the
  positive/negative layer arguments and X sum before joining the common spawn
  at 608E28. An ordinary if/else around the two spawn expressions preserves
  these separate preparations rather than choosing only the layer inside one
  argument list. Both branches still converge naturally in compiled code.

The bounded per-action floating-operation census now includes FIADD/FISUB/
FIMUL/FIDIV in their matching arithmetic families. All 114 actions agree in
both direct callee counts and arithmetic-family counts. These are omission
checks, not equality or semantic proof. Five physical virtual-site count
residuals remain:414 (5/4),416 (5/4),525 (6/4),529 (11/12),540 (8/7).
Unrelated actions can acquire different physical tail sharing after whole-root
compilation; do not force duplicates solely to match those counts. Low primary
table 31/native33 remains; other table dimensions and both larger remaps agree.

A full incoming-action-partitioned payload audit retains 85 known request homes
and zero unknown spawn pointers on each side. The native two-word530/532
storage and forwarded count 3 are unchanged. Candidate 139 epilogues/191 virtual
sites differ from native 146/199. One candidate cached vslot 0C across on_surface
is independently proved from EDI=[ESI], EDI+=0C, preserved EDI across 435DC0,
then EDX=[EDI] and CALL EDX at 60A09E. Its boolean result uses NEG AL/SBB, so a
simple next-instruction-only TEST-AL diagnostic is not a valid rejection.
No public comparator exception or source ABI change was introduced.

The previously pending action 529 positive-vertical-speed guard is also closed:
60A434 FLDZ / FCOMP [F8], FNSTSW, TEST AH,5 / JP skips multiplication for
negative, zero or unordered values. Existing F8>0 source is correct and remains
unchanged. No NaN policy is invented from decompiler output.

Do not rerun the old Oct28 assembly/writer scripts over this source: they predate
these changes.

## November 1: complete manager-backed spawn-width controls

Fresh raw PE review closes the real 465190/66 forwarding wrapper and actual
Aya manager 618470/237, selected by vtable 6C62A4 slot 4. COL 6DB7A8 points to
TD6E8DF4, `CharacterObjectManager<Aya,AyaObject>`. Wrapper SHA256 remains
80aab8cb379377dc179c3e1311599ab890885fa92ffd5ecf075ff6c3df15a7fc;
manager SHA256 remains
e29f767ab7c746db971de525ba7b1f694668b8e3b20e5bba09bc2c35e046e45b.
The wrapper copies the complete direction/variant argument words. Manager
618512/618516 reads their low bytes, then 618530/618548 stores them at 104/33C.
The complete manager contains no other reads of those two argument slots.

Two ordinary source controls change both forwarding-wrapper declarations
consistently: unsigned-byte direction only, and unsigned-byte direction plus
variant. Both independently reproduce all 66 canonical wrapper bytes, including
RET 28. The original int-view wrapper also freshly passes. Thus neither narrower
view proves the original source declaration; none is an alternate register ABI.
The accepted roster-spawn unit freshly passes, including Aya 237.

For the complete Aya action root, direction-only yields 65536 bytes, SHA256
8e28536cde5296baf84df6ec6157ac5bdef0d59b53fe6a018d3af8760e821090.
Both bytes also yield 65536, SHA256
63d36eb03ef1153ea8f7b0c1cb5fb0a272fb07c2d032054d5cc04bab3645c5ba.
Both remain nonexact at+48 against the entire native 66704-byte payload; the
complete source baseline is freshly reproduced 65692, first+48. Neither width
control closes the first register allocation difference or the low-table31/33
owner difference. Both retain all 114 per-action direct-call and FP-operation
censuses. Virtual physical-count residuals are 414(5/4),416(5/4),525(6/5),
529(11/12). Fewer residuals are not proof of semantic or canonical equivalence.
No public source/header/manifest change is selected, and no exact credit added.
Do not repeat these width controls or force byte carriers/registers in the root.

The manager also independently confirms a real count-sized copy:6184C7 reads
count,6184CF..6184E2 allocates four times that count, and 6184F8..618502 passes
four times count to memcpy when the pointer is non-null. Consequently the
530/532 count 3 cannot be dismissed as a harmless ignored argument. The earlier
observed two-word homes remain an unresolved original extent/lifetime issue;
this scope does not synthesize a third word or enlarge the arrays to hide it.

All native work was serial.

## Actions 560 and 561 spawn height, 2026-11-05

At `0x60CC72..0x60CCA2` and `0x60CE28..0x60CE58`, the native 825
spawn retains the unsigned RNG(300) conversion in x87 while computing
`actor Y + 300`, adds the two, and only then stores the float argument. The
prior source stored the random value to a float local first. A double local
initialized through the existing float conversion retains the original float
2^32 correction while allowing VC8 to keep the value in x87; the focused
candidate now performs the additions before its first float store at both sites.
The RNG's ordinary 0..300 integer range is exactly representable as float, so
no normal gameplay numeric change is claimed.

The complete 65601-byte root remains nonexact at +48; the new section tail is
65700 bytes. This local observation does not add exact-function or byte credit.

### Integer gate thresholds

Four original gates at `0x60A2D0`, `0x60B745`, `0x60DF0A`, and `0x60E548` compare signed values against 2, 4, 60, and 300. The equivalent threshold forms recover their local comparisons and branches with no integer behavior change. The complete candidate remains non-exact, with a 65,700-byte section.

Repeated frame and signed-level gates at `0x60A2E2`, `0x60A468`, `0x60A94E`, `0x60ABA2`, `0x60BB3E`, and `0x60BF6A` now use the equivalent original thresholds. The frame comparisons and all six branch conditions follow the native forms; the candidate uses a register for the two level thresholds and still differs in layout. Integer behavior is unchanged, and the 65,672-byte candidate remains non-exact.

The 20-frame gates including `0x609BDC` and `0x60E220` now use the equivalent native bound. Focused compilation recovers the local signed comparison and branch while differently merging repeated follow-up code. Integer behavior is unchanged; the 65,648-byte candidate remains non-exact.
