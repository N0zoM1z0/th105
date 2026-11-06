# Yuyuko Object update, JP1.06a 0x0056F700

The complete 28-action/default manual source is selected in
`src/characters/YuyukoObjectUpdate.cpp/.hpp`. The reproducible unit is
`exact-first-yuyuko-object-update`. It is **source-present, not exact**.
The first complete compile and full-payload comparison preceded source controls.
Current selected full34928 SHAc97edd07 remains nonexact32764/+31; see the
bounded815 and exit follow-up below.
Numeric actions, typed offsets and declaration-only providers remain deliberate;
original names, complete owner layout and translation-unit ownership are unknown.

## Observed target boundary

All observations use the original Japanese 1.06a executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
base `0x400000`, entry `0x68B9D2`. The GUI IDA SHA mismatches and was not used.
The roster raw shared-callee census was refreshed before this root's analysis
(`build/exact-first-yuyuko-object-update-20261025/roster-shared-callees.json`).

The primary Object slot+0x28 cell `0x6C55EC` points to `0x56F700`.
The candidate's main `[0x56F700,0x577CE6)` is 34,278 bytes, SHA-256
`5c6d0bac072dda180fac2f0d65b1f444381257ec8940d330e781cbd906052e8d`.
Raw decoding finds 8,047 instructions; complete CFG traversal reaches 8,032
instructions/34,210 bytes. The remaining 15 instructions/68 bytes are exact
internal alignment spans, individually checked by the public audit. All 62
reachable exits are RET0; no branch escapes the reviewed main span. Eight
preceding INT3 bytes and twelve following INT3 bytes isolate the complete payload.

The full `[0x56F700,0x577FF4)` is 35,060 bytes, SHA-256
`606cd3d61fb4798f134297a76237c045d28ee45f215f9be95bfdb1984b24d7de`.
It owns 16 destination tables/121 DWORDs and seven bounded byte remaps/291 bytes.
The remaps start at `0x577D5C/577E38/577E7C/577EC4/577F14/577F40/577FA0`,
with lengths `199/20/15/17/12/12/16`. The primary dispatch covers actions
800..998; **999 is not its last remap byte**. The remaining seven bytes are
reviewed compiler alignment: `577CE6:8bff`, `577E23:90`, `577E8B:90`,
`577ED5:8d4900`. Nested remap extents come from their own CMP/JA guards and
MOVZX-to-destination-table dataflow, not from the primary action range.

The same-owner initializer `0x578000`, slot+0x3C cell `0x6C5600`, remains a
separate source-present/nonexact function and was used only as family context.
Its bytes and the separating INT3 bytes are outside this unit.
Default `0x577CD6` calls `0x4351C0` once and ignores AL, restores four registers
and ESP, then RET0. It does not decrement lifetime.

## ABI and source evidence

The root is thiscall/RET0, with `SUB ESP,0x238`, saved EBX/EBP/ESI/EDI,
primary `this` in ESI and no ESP realignment. Its 329 direct calls cover 24
entries. All 15 virtual calls use the primary receiver, slots 0x0C/0x14/0x1C.
The source header is a pointer-only call view: never instantiate or embed it.

| Direct entry | Physical calls | Supported local call contract |
| --- | ---: | --- |
| 5575C0 | 19 | thiscall byte result, three int arguments, RET12 |
| 435160 | 29 | this+4 motion receiver, two float arguments, RET8 |
| 4067D0 | 80 | cdecl int random result; unsigned conversion when observed |
| 64CCB0 | 52 | thiscall unparented request, seven arguments, RET28 |
| 406360 / 4063D0 | 41 / 15 | cdecl float argument, local float/ST0 result view |
| 4351C0 | 7 | thiscall byte frame result, RET0 |
| 496420 / 4963A0 | 3 / 20 | secondary replacement RET20 / advancement RET4 |
| 4E0BF0 / 45C030 | 1 / 7 | heading RET12 / owner event RET4 |
| 406540 / 435D60 | 5 / 1 | cdecl float atan2 / thiscall surface height |
| 68A1A0 | 14 | compiler conversion helper, physical ST0 input and EAX output |
| 4FC710 | 3 | bounds, four int and three short argument slots, RET28 |
| 406580 / 478DD0 | 2 / 1 | cdecl float square / square root |
| 435240 | 4 | thiscall fighter effect request, RET20 |
| 64CD00 / 4064B0 | 5 / 2 | thiscall phase RET4 / cdecl int-angle cosine |
| 496370 / 4FCA60 | 1 / 4 | secondary alpha RET4 / parented request RET28 |
| 5B0400 / 53CBC0 | 12 / 1 | relative position RET8 / shared ping-pong update RET0 |

Provider contracts use complete raw bodies and independently supported forwarding
witnesses where available; they do not grant new callee implementation credit.
The quantized sine/cosine providers terminate in an m32 table FLD/ST0/RET0.
The audit rechecks their complete hashes and return tails. A local float carrier
is supported without claiming the original nominal prototype or changing any
shared provider source, header, accepted unit or compiler profile. Compiler
conversion calls come from ordinary casts; no fake custom ABI helper is declared.

One direct readonly/noanalysis Ghidra process, limited to 384 MiB, independently
attested import identity, entry and all mapped bytes. Temporary root/callee/
physical-ST0 call views were read back and rolled back; all nine primary DB
hashes were unchanged. `ghidra-receipt.json` records the successful sentinel
`YUYUKO_OBJECT_UPDATE_READONLY_ATTESTED`. Decompiler text remains a hypothesis,
not a source-generation recipe. Manual source was written and reviewed separately.

Raw stack-depth propagation and backward tracing from the actual request
argument slot establish 46 consumed three-word packet bases (-12 through -552).
Shared request `576974` has distinct -180/-156 predecessors; `5770BD` has
-492/-108 predecessors. Tracking register definitions, overlapping writes,
caller-saved clobbers and callee argument spans leaves no unresolved packet
pointer definitions under those contracts. This is not general alias or
path-feasibility proof. The source uses every packet; none is inert frame padding.
Ten qword stack accesses are scalar expression spills, not an excuse to force
alignment with dummy doubles.

A decompiler artifact in action816 prints a write to pool address `0x6C3CE8`.
Native `571C17/571CB3/571D65/571E01/571E91/571F2D` only FLD-read its float16
and write the stack packet. Manual source writes packet[2]=16, with no absolute
pool write. Undefined4 labels likewise do not authorize integer bit copies:
position/velocity/heading transfers were checked against native floating accesses.
Actions851/854 retain integer counter*3 before conversion and a wide sine product
across the second lookup, supported by the target's qword spills. Actions852/855
really decay X scale and then overwrite X from Y; raw FLD/FSTP instructions
support this unusual order and it is retained.

## First whole comparison and bounded controls

Receipts are below `build/exact-first-yuyuko-object-update-20261025/`.
Every candidate replays its complete COFF section and all relocations against
all 35,060 target bytes; no instruction or metadata masking is used.

| Source/control | Complete size / SHA prefix | Differing bytes / first offset | Evidence and disposition |
| --- | --- | --- | --- |
| first-complete | 34772 / 3b558e64 | 32958 / +31 | First full body before controls; natural frame238; retained |
| request-epochs | 34844 / cd286e4c | 32886 / +2 | Correct815 loop bound12; independent900 RNG pairs with shared final request; extra live coordinate locals produce frame23C; retained, unselected |
| full-requests | 34908 / 06a43850 | 32830 / +31 | Prior selected complete ordinary argument expressions restore frame238; independently retain both900 coordinate computations, but compiler leaves two request calls versus native one |

Native815's `571536 FLD [6C12B0]`/back edge at571545 establishes loop bound12,
correcting the first body's accidental2. Native900's two paths each have two
random calls; only the final spawn site576974 is shared. The first source
incorrectly shared coordinate computation too. The two controls above address
that concrete lifetime/physical-sharing question; neither proves exactness.

First-checkpoint selected full payload SHA-256:
`06a438502d5e2ffbe0464d12e3e6db69a1d6b6a329f9603f4e858e18d9a5b381`.
Its natural frame0x238 agrees, and all 16 table dimensions/seven remap contents
agree. Nevertheless it has 68 RETs, 27 motion calls, four frame calls, 53
unparented calls and 12 virtual calls versus native62/29/7/52/15. Static per-action
reachable call inventories agree for all 28 nondefault actions except815's
one versus two virtual calls and900's two versus one request calls. These are
coverage diagnostics, **not execution-equivalence or path-feasibility proof**.
The full comparison remains nonexact at32,830 unmasked differences, first56F71F.

At that checkpoint the next investigation was native argument/return epochs and physical sharing:
independent810/856 and811/855 motion sites, separate815 virtual exits, native
820/858 shared next-block exit, and the native four frame-owner groups. Do not
force stack slots or open a compiler-flag/spelling grid. Preserve the first full
receipt and switch if bounded controls repeat without new evidence.

## Bounded815 expressions and exit-owner follow-up

The raw815 effect-X calculation at5714EE..57150B multiplies the float loop value
by double130, then cosine, then the separately converted signed facing. Source
now keeps `facing * (n * 130.0 * cosine)` rather than left-associating facing
into the first product. Native571726..57172D consumes the sine return directly
with `FADD ST0,ST0`; source now doubles the call expression directly instead
of assigning a named float and rounding it again. These changes follow actual
operand order and return-provider bytes; they are not an original-source claim.

The native815 integer guards use comparisons against1,16,15,10 and20. Keeping
those inclusive boundaries (`own frame <=1`, parent frame `>=1 && <=16`,
parent invalid frame `>=15`, active own frame `>=1`, counter `>=10/20`, and
alpha `<=15`) admits the actual separate virtual exits. Candidate57155C and
5716B9 now correspond to native571634 and571790; both still take argument2
and reset counter144. No synthetic variable, padding or forced register is used.

Fresh complete controls are retained below `build/yuyuko-update-exits-20261025/`:

| Control | Full bytes / SHA prefix | Unmasked differences | Physical observations |
| --- | --- | ---: | --- |
| 815-expressions | 34908 / e592725c | 32745 | Raw product association and direct sine doubling; still one815 virtual exit |
| 815-guards | 34928 / c97edd07 | 32764 | Selected; two815 virtual exits;13 virtuals overall, frame238,69 RETs |
| native-joins | 34300 / 2e70a26c | 33058 | Unselected broader native continuation spelling: ordinary movement,852/858 frame and820/858 next-block joins; over-factors motion24 versus29;75 RETs |
| phase-frame-joins | 34988 / 6c6e55be | 32626 | Unselected narrower852/858 frame and820/858 next-block joins;27 motion/70 RETs and same wrong frame-owner partition |

All controls keep all16 table dimensions and all seven remap byte sequences,
frame0x238, and the ten qword stack accesses at the native relative offsets,
widths and operation order. These are diagnostics, not exact or execution proof.
Selected full SHA-256:
`c97edd078c3d744786f30337106b1938004d1e6f51bb8e951dc1aebd00354da6`.
Full strict comparison remains32764 unmasked differences, first56F71F/+31.
The smaller difference count or size of an unselected control does not establish
fidelity; the selected815 changes have independent raw expression/guard evidence.

The public audit now emits static per-action call counts **and physical call
owner groups** for target and candidate. Three synthetic controls distinguish
one shared site from two independent sites with identical per-action counts,
and count a loop's physical site only once. This does not count dynamic calls or
prove path feasibility. All28 per-action inventories now agree except900's
extra unparented call; nominal side effects/alias contracts remain separately
unknown. Target frame sites partition as follows:

| Native frame site | Reachable action owners |
| --- | --- |
| 56FBAF | 800,801,812,815,816,820,821,850,851,853,854,857,900,902,920,922,980,998 |
| 5706B9 | 810,826,856,901 |
| 570FA7 | 811,855 |
| 573237 | 825 |
| 573822 | 848 |
| 57452A | 852,858 |
| 577CD6 | default; ignores AL |

Both join controls and the selected source instead coalesce all four ordinary
movement/frame families into one26-action frame site, plus825/848/default: four total
versus seven. The two controls have different full hashes and are **not**
byte-neutral. They repeat the same unresolved owner partition. Close this scoped
join question without a compiler-option/spelling grid or an LTCG-impossibility
claim. The target also retains independent810/856 and811/855 motion sites;
the broad movement join removes three further physical sites and is rejected.

A private raw x87-depth propagation, under the independently recorded call
return/purge contracts, closes every reached RET at depth0 with consistent
join depths for target and all candidates. All900 unparented calls have depth0;
its two source calls versus one native site are not explained by a different
entry x87 stack depth. Native both coordinate paths retain the m32 rounding
at576962/576B7A before their common final request. There is no evidence to
replace a float coordinate with a double simply to tune the frame. Keep the
previous explicit-coordinate frame23C control unselected and avoid repeated
carrier/flag trials without new independent facts.

The selected candidate still has27 motion/4 frame/53 unparented/13 virtual
calls and69 RETs versus29/7/52/15 and62. No exact credit or new aggregate cold
claim is made. Park56F700 after these bounded questions. The next independently
reviewed candidate is TenshiObject64CD50: provisional41001 bytes, primary
Object slot28 cell6C6734, source missing. Its same-owner657150 initializer is
source-present/nonexact context only; no boundary or semantic reuse is assumed.
Refresh all four preflights and the raw shared-callee census before analyzing it.

## Reproduction and acceptance limits

```bash
scripts/repo-python scripts/audit-yuyuko-object-update.py --target-only
scripts/repo-python -m unittest discover -s tests -p test_yuyuko_object_update_audit.py
scripts/repo-python scripts/build.py --unit exact-first-yuyuko-object-update --compare --json
scripts/repo-python scripts/audit-yuyuko-object-update.py
scripts/compile-unit.sh src/characters/YuyukoObjectUpdate.cpp build/yuyuko-update-exits-20261025/cold.obj
scripts/repo-python scripts/audit-yuyuko-object-update.py --object build/yuyuko-update-exits-20261025/cold.obj
scripts/repo-python scripts/check-match-literals.py --require-target
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ci.py
git diff --check
```

Compile/compare/audit commands return nonzero for the recorded nonexact result;
the compiler itself succeeds. Target-only audit and all17 synthetic controls pass.
Controls reject last-action overrun, nested remap overrun or changed guard,
metadata destinations/table cuts/truncated remaps/unowned tails, unreviewed
internal padding, escaping CFG edges, and a default that consumes AL or retires.
Candidate inventory failures are diagnostic and do not suppress the full strict
canonical comparison. Formal and independent cold artifacts must agree before
checkpoint acceptance. Ninety-five new literal aliases and three mutable-bound
aliases are exclusive to this new probe; the existing match identifier mapping
is reused. No shared ABI/profile/object partition or accepted binding is altered.
No exact claim, new accepted unit or new aggregate cold-replay claim is made.
Original nominal prototypes, invalid/nonfinite input domains, TU/LTCG context
and the remaining complete instruction differences are unknown.

First-checkpoint validation: formal and independent cold complete-payload audits are
identical at the selected SHA above, with every section relocation replayed.
The local `scripts/repo-python scripts/ci.py` gate passes601 tests; tracking
and all1,870 target literal references pass. Accepted exact progress is unchanged;
the last aggregate cold receipt remains the prior Remilia-action checkpoint.

Follow-up checkpoint: formal and independent cold complete-payload receipts
agree at34928 SHAc97edd07 with1,059 relocations replayed. All17 target-free
audit controls and the mandatory local CI gate (604 tests) pass; all1,870
literal target checks and tracking pass. No accepted source/header/profile or
relocation binding changes, no exact increment and no new aggregate cold claim.

## Action 821 vertical pursuit, 2026-11-04

Native `0x00572C7B..0x00572CB7` accelerates upward only when the height
difference is ordered and negative (`AH & 5`, parity branch skips otherwise),
then clamps speed only when it is ordered and above the limit (`AH & 0x41`
skips otherwise). The two previous negated comparisons admitted unordered
values. They now use `< 0.0` and `> 6.0f`; fresh VC8 reproduces the local
status masks and branches at `0x3895..0x38CB`. This does not assert whole-root
or unmasked-exception equivalence.

The 34,278-byte callable remains nonexact from +31; the candidate section
tail is 34,928 bytes. No exact credit is added.

## Action 800 scale branches, 2026-11-05

The target compares `1.0` against the existing X scale at `0x56F78B..0x56F798`: unordered values take the same branch as scale greater than or equal to one. The subsequent updated-scale clamp at `0x56F7AE..0x56F7BB` clamps only an ordered value greater than one. Expressing these two conditions accordingly fixes their unordered behavior. The focused VC8 build shows the corresponding `test ah, 0x41` branches at candidate offsets `0x8B..0x98` and `0xC4..0xD1`. The full 34278-byte root remains non-exact (candidate section tail 34928, first mismatch +31); no exact credit is claimed.

## Action 801 vertical chase, 2026-11-05

The target at `0x56FCC6..0x56FCDF` takes the upward-acceleration branch for unordered height comparisons as well as for Y at or below the target height. The prior `<=` selected the opposite branch for unordered inputs. The source now expresses the observed condition, and the focused candidate uses the corresponding `test ah, 0x05; jnp` inverse branch at `0x56C..0x585`. The full 34278-byte root remains non-exact (candidate section tail 34928, first mismatch +31); no exact credit is claimed.

## Action 811 fade gate, 2026-11-05

At `0x570A99..0x570AAA` the target skips the fade when the decayed scale is greater than 0.3 or unordered. The previous negated `>` included unordered values in the fade. The source now uses ordered `<=`; focused compilation emits the same `test ah, 1; jne` continuation at `0x12E6..0x12F7`. The full 34278-byte root remains non-exact (candidate section tail 34928, first mismatch +31); no exact credit is claimed.

## Actions 851 and 854 packet speed rounding, 2026-11-05

Native `0x573C92..0x573CB3` and `0x574BBD..0x574BD9` round the RNG(40) and RNG(120) products with double-promoted `0.1f` to float before adding 2 and 10 respectively. The previous expressions added before the float conversion. The source now preserves the intermediate float; focused VC8 compilation emits the corresponding store/reload/add sequences at `0x468D..0x46A1` and `0x5424..0x5433`. Valid RNG values can change the final speed: action 851 with RNG 13 yields about 3.30000019 instead of 3.29999995, and action 854 with RNG 42 yields about 14.20000076 instead of 14.19999981. The 34278-byte root remains non-exact (candidate section tail 34948, first mismatch +31); no exact credit is claimed.

## Action 848 direction argument, 2026-11-05

For sequence 10's periodic object 848 spawn, native `0x5735E7..0x5735F3` reads the facing byte with `movzx` and passes the resulting full 32-bit value before either RNG call. The previous byte-sized local compiled into a byte store followed by a full-word reload, leaving the argument's upper bytes dependent on the stack. An unsigned integer snapshot preserves the observed zero-extension and timing; focused VC8 compilation now emits `movzx` and the full-word push at candidate `0x3E2D..0x3E36`. The wrapper forwards the argument word, but no gameplay consequence of its formerly unspecified upper bytes is established. The full 34278-byte root remains non-exact, first mismatch +31; no exact credit is claimed.

The same full-word facing snapshot is observed in the native periodic spawns for objects 801, 810, 811, 820, 854, 856, 858, 900, and 901. Representative zero-extended reads are at `0x56FEEA`, `0x5704FA`, `0x570D3F`, `0x5724A6`, `0x572857`, `0x574BE9`, `0x575B37`, `0x5764D5`, `0x576905`, and `0x576DE1`; the native 900 branches share one emitted call path. Eleven corresponding byte-sized local snapshots now use an unsigned integer, and focused compilation produces zero-extended full-word arguments for each source site. This does not establish a gameplay difference or whole-root exactness.

## Timer angle conversion order (2026-11-05)

Native 0x56F99F, 0x56FC64, 0x56FDEA, 0x5700ED, 0x570388, 0x571C6A, 0x571DB8, 0x571E4C, 0x571EE4 and 0x5730C6 loads the signed timer directly into x87, multiplies by the double angle constant, and rounds to float only after any angle offset. The source now preserves that order instead of first casting the timer to float. The pinned VC8 build already elided the earlier conversion: the compared function bytes remain unchanged (SHA-256 `4b4b7bf867d87df277fff9d5a0778bcdebcdfbba3a20085693172797f83dad1a`). The function remains nonexact; no claim is made that a timer large enough to expose strict floating-point rounding is reachable in normal play.

## Action 857 sequence 14 scale threshold (2026-11-05)

At `0x5762CA..0x576301` the native code rounds the updated scale at `+0x120`
to float, compares `1.0` against that value and enters the clamp for values
greater than or **equal to** 1.0. The earlier source used `> 1.0` and could
miss the state transition when the rounded value was exactly 1.0 and the timer
was at least 20. The source now uses `>= 1.0` and spells the timer guard as
`>= 20`; unordered comparisons still bypass the clamp. For example, a float
near 0.9 plus the stored float 0.1 rounds to 1.0. No claim is made about how
often that state occurs during play.

The focused pinned-VC8 build now emits `test ah,0x41; jp` and `cmp ...,0x14;
jl` at object offsets `0x6AD3..0x6AE5`, matching the native local comparison
and timer-guard structure. The complete selected root remains nonexact, with
34,868-byte section tail and compared SHA-256
`0d3aac7b14ea022c60f4710238f171255c952a7eb235c5f8bf024b09c6f89eb8`;
no whole-function or exact-byte credit is claimed.

## Action 826 out-of-bounds comparisons (2026-11-06)

Native `0x573361..0x5733B7` checks each of the four out-of-bounds predicates
separately. An unordered coordinate does not by itself trigger retirement.
The earlier source expressed the complementary ordered in-bounds range, so an
unordered coordinate caused retirement instead. Four direct guards now preserve
native ordered comparison behavior for the same bounds. Finite in-range and
out-of-range inputs retain their prior decisions; normal-play occurrence of an
unordered coordinate is unknown.

The selected candidate at `0x3BA3..0x3BFA` keeps a distinct four-comparison
sequence, including `test ah,0x5` at the upper bounds. VC8 emits local return
copies where the native branches use shared return tails, so physical ownership
is not yet correct. A single combined OUTSIDE expression was also tried but
merged this whole comparison sequence into another action; it was not selected.
The full root remains nonexact, section tail 34,884 bytes, compared SHA-256
`6a4bc69f0cb99eb0283671e7a11084fa13ba70617be09a417ecc1c4fb463fab4`.
No whole-function or exact-byte credit is claimed.

## Timer comparison precision (2026-11-06)

At `0x57528B`, native loads the signed timer with `fild` and directly compares it with parameter 1. Source now converts the timer to double rather than float before that comparison, avoiding premature rounding of large integers. The pinned VC8 candidate remains unchanged at SHA-256 `6a4bc69f0cb99eb0283671e7a11084fa13ba70617be09a417ecc1c4fb463fab4`. Normal-play reachability of such values is unknown; the function remains nonexact.

## Four phase dispatches (2026-11-06)

Native actions 821, 825, 851 and 920 use signed phase dispatches at `0x572965`, `0x573183`, `0x573B43` and `0x5775CD`. The equivalent source conditions now use ordinary switches, restoring the four local signed phase loads and switch branch families in the focused VC8 output while retaining case/default behavior. The complete candidate remains nonexact (34944-byte section tail, first mismatch +31); no exact credit is claimed.

Action 826 at `0x57329E` likewise uses a signed phase switch, with phase 0 separate and phases 1–4 sharing a branch. Replacing the equivalent unsigned range check with those switch cases restores the signed load and local range-dispatch family; all other phase values retain the default path. The focused section tail is 34924 bytes, first mismatch +31, and the complete function remains nonexact.

### Integer gate thresholds

Six original integer gates at `0x56F77E`, `0x56FA01`, `0x57212A`, `0x5743C9`, `0x5754D5`, and `0x577784` compare against 120, 60, 10, 300, 360, and 120. The equivalent source threshold forms recover these local compare and signed-branch instructions without changing integer behavior. The complete function remains non-exact; the candidate section is 34,924 bytes.
