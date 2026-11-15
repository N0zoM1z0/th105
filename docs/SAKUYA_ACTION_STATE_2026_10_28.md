# Sakuya Fighter action-state reconstruction, 2026-10-28

Complete 113-action/default manual source is selected for 4CADB0. Whole native
comparison remains nonexact; source presence is not exactness or equivalence.

The canonical Japanese 1.06a target SHA256 is
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
The provisional 41511-byte entry span is not the full callable. Existing ownership
records independently hash ten remote chunks through 4DD2D2 exclusive. All prior
chunk hashes still agree. The complete contiguous callable extent is 75042 bytes,
SHA256 a7d5eb49423691b16358efbb5cb857867932c230a86798f84da233fe4207eb51.
Full callable plus metadata [4CADB0,4DD7E0) is 76336 bytes, SHA256
6ca4fc284871b25c320bfd93749f548b34b0b55122661caf137ab3efe6db138f.

Raw linear decoding closes 19016 instructions. Fourteen jump tables have 31/38/38
primary dimensions and eleven 4-entry secondary dimensions. Remaps cover 227/226/
230 labels starting 0/301/541. Direct 300/540/795/797/798 augment108 sparse action
labels. The CFG reaches 18993 instructions/74937 bytes, with 159 RET 0s and 190
virtual call sites. The native frame is 4D8 and aligned to 8. The formal comparison
must use the full owned extent, not only the provisional entry span.

## Alignment correction

Earlier ownership excluded seven-byte LEAs at 4D2839,4D2C79 and 4D2E19 but still
counted the preceding short jumps at 4D2C77 and 4D2E17. Both are unreachable
alignment instructions. Their immediate predecessors unconditionally branch to
4D2C8C and 4D2E2A. Complete traversal of all 14 tables and direct edges reaches
neither short jump; they skip their following LEA to the 16-byte boundaries
4D2C80/4D2E20. The two exclusion spans now include the short jumps and are hashed
as nine bytes each. Main excluded bytes are 25, not 21; owned bytes are 74937,
not 74941. All remote chunks and remote_exact=false remain unchanged.

This is correction of four compiler-alignment bytes in the denominator, not
new restoration progress. Full-payload byte comparison still includes every
alignment byte; no masking or altered acceptance boundary is introduced.

## Analysis route

Local IDA preflight still lacks its pinned MCP runtime; that session is unused.
The existing Factory-native IDA decompiler failure was not retried. A separate
Ghidra session through Factory repository Bash re-attested imported executable
identity, entry 68B9D2, x86/Windows specification and every mapped .text byte before
bounded analysis. Known ordinary helper ABIs, including exact 45E0E0, were read
back in the isolated project. Full navigation export completed 377265 bytes and
the project saved, verified after a client timeout before any repeat operation.

Decompiler removed-block/spacebase warnings remain hypotheses to review against raw
instructions. No target bytes or IDA metadata changed. The initial Iku project is
untouched.

## Complete source and replay

`src/characters/SakuyaActionState.cpp/.hpp` now provide all 113 primary action
labels and the shared default, including pre-dispatch time-control effects,
movement, normals, skill/projectile requests, spells and story patterns. The
view is pointer-only; no complete Sakuya allocation/layout is asserted. Shared
sequence slots and ordinary direct-call ABIs retain their existing contracts.
The separate exact 45E0E0 predicate uses its observed fastcall Boolean result.

Fresh raw RTTI readback: primary vtable 6C4914, slot 28 cell 6C493C ->4CADB0;
COL 6DA220 -> type descriptor 6E8158, name at 6E8160 `.?AVSakuya@@`.
All 138 new relocation aliases are isolated to this unit. Literal bindings use
actual operand widths/IEEE bytes. Match selector 6FA894 is freshly observed at
4DA8BC/4DAEA1/4DB4FB and later story sites; no global-layout claim is added.

The focused unit `exact-first-sakuya-action-state` uses VC8 SP1 O2/GS-off and
`owned_extent=true`, so formal comparison includes the main and ten remote
chunks, plus 105 alignment bytes. `scripts/audit-sakuya-action-state.py` also
replays every section relocation and compares the entire 76336-byte payload,
including 14 native tables and three remaps, without masks.

Selected full source output 77144 bytes, SHA256
410a41cea3c1b4150bfcab1264b176af6d88200da12bb8d1af004b5216110ad2.
First difference+8 /4CADB8 is frame 4A8 versus native 4D8; full payload has 73221
unequal positions including length difference. Source has 13 tables with primary
30/39/38 versus native 31/38/38,163 returns versus 159,184 virtual sites versus 190.
The remap lengths 227/226/230 agree, but contents and owner grouping differ.
No exact ledger entry or remote_exact promotion is made.

Bounded per-action traversal finds direct-call-site count differences only in
404/405 (counter helper 2 native versus 3 candidate) and 567 (spawn 3 versus 2).
Floating-operation count differences remain in 214 and 404/405/406. These counts
are navigation diagnostics, not proof of semantic or byte equivalence. Native
567 has two identical argument branches, which this compiler merges.

Private frame/payload dataflow closes all 113 action partitions with no unknown
payload pointers and 95 request homes in both target and candidate. Native
frame 1240 versus 1192 differs by 48 bytes; several native homes are 16 bytes apart
although only three words are visibly initialized/passed. Original declaration
extent, lifetime and compiler sharing remain unknown. No inert fourth word or
padding is inserted to force the frame. All 58 native and 57 candidate surface
consumers, and 8 native/7 candidate on-surface consumers, test AL. Physical
counts differ through shared tails and are not ABI changes.

Only this new unit was natively compiled; unchanged accepted receipts remain
incremental. The default repository gate is separate from native exact replay.

## Target-backed shared counter continuation

The native 404/405 sequence 1 tails join 406 at 4D0240 to publish 730 and call the
counter once. Expressing that actual shared continuation removes the extra
reachable counter sites in 404/405. The new selected full payload is 77064 bytes,
SHA256 6e219ddc90d401d5c83da2667d60b72f2d518b7d980a4ab1e1c4cba1dd52edb8,
with 73205 unequal positions, first+8 and frame 4A8 unchanged. Returns reduce to 161;
virtual sites 184, tables 13 and all 95 request homes remain unchanged. Only 567's
identical-branch spawn-site merge remains in the 113-action direct-call census.
The four floating-operation census residuals remain. No exact credit follows
from smaller output or matching per-action call counts.

Updated selected receipts are formal-tail-build.json, formal-tail-audit.json
and tail-payload-review.log in the same build scope. Initial receipts remain
historical and are not the selected source result.

## October 29: actual argument lifetimes and arithmetic branches

Raw 404 instructions 4CF2D9..4CF388 establish real call-argument evaluation:
count 3, request pointer, variant 1 and facing are placed before the sine and
cosine coordinate expressions. The previous KNIFE macro staged facing/y/x in
named locals, unnecessarily extending their lifetimes. The selected macro now
passes the actual expressions directly to spawn, preserving the same values
and observed right-to-left evaluation without invented storage or ABI changes.
The existing constant-zero x-offset branch remains a source-level constant.
This changes full output 77064 to 77000 bytes, without changing frame 4A8.

Action 214 also has two distinct arithmetic branches. Native 4CC6CB..4CC6E0
selects one of two ADD instructions after loading the current angle, while
4CC6F0..4CC717 keeps the zero-selector subtraction branch first. Explicit
ordinary if/else compound assignments now preserve that observed topology;
the previous ternary RHS merged the two addition sites. No redundant arithmetic,
forced register or additional request element is introduced.

The earlier 404/405/406 floating-operation census was misleading: it counted
FSUB-family instructions but omitted FISUB integer-memory forms. Including
FIADD/FISUB/FIMUL/FIDIV shows those three cases already agreed arithmetically.
After the 214 branch correction, all 113 per-action arithmetic-family counts
agree. These are diagnostic counts, not proof of full equivalence. The sole
direct-call count residual is still 567's identical branches merging three
physical native spawn sites into two. Whole source still has 13/native14 tables.

Current selected full payload is 77000 bytes, SHA256
`9ef2c49fca9a7b0d66604e9aabf236cbb98e4cd5b1a7f193c3de839ff86b07fe`,
with 73065 unmasked differing positions including length. First difference+8
and frame 1192/native1240 remain. Current private payload traversal finds 95 homes,
no unknown request pointers,160 returns and 183 virtual sites; source declaration
extents, frame allocation and tail sharing remain unresolved. The native has 159
returns and 190 virtual sites. This checkpoint earns **no exact credit**.

Focused public full-extent build and complete payload audit:
`build/frontier-sakuya-arguments-20261029/{formal-build,formal-audit}.json`. No
shared header, relocation binding, compiler profile or accepted consumer changed.

### Completed argument-lifetime pass

The same independent argument-stack review now covers 96 additional staged
spawn expressions:64 sine/cosine pairs across 19 primary actions, and 32 action 545/
546/547/548 sites using sine or ordered RNG coordinate expressions. Every reviewed
native site pushes its request count before the first coordinate helper. Ordinary
direct arguments reproduce that lifetime without named facing/y/x temporaries;
request declarations, element counts, value expressions and RNG order are
unchanged. Native proof packets are `trig-argument-facts.json` and
`817-argument-facts.json` in the current build scope. Primary action ownership
uses actual outer switch nesting, not the nearest nested case label.

This pass supersedes the 77000-byte selection above. Current full payload is
**76484/native76336, nonexact+8**, SHA256
`f9caf8283a24673e47ea3f9e4182861adc842edab8b90be22fd2f7193c22f885`.
There are 72568 unmasked differing positions including length,158 source returns
and 184 virtual sites. All 113 arithmetic-family censuses still agree, and only
567 retains the physical three-versus-two spawn-site difference. Raw 567 readback
again verifies identical argument values in the two native branches; register
spelling differs, which is not permission to invent a source-level distinction.

The payload audit still closes 95 homes with no unknown pointers, frame 1192 versus
native 1240 and unchanged AL-width predicates. This is a closer source expression
of the observed calls, **not byte-exact acceptance or a percentage inferred from
length**. The current focused receipts are `formal-allargs-build.json`,
`formal-allargs-audit.json` and `allargs-payload-review.log` in
`build/frontier-sakuya-arguments-20261029/`. All section bytes and metadata remain
unmasked; exact totals are unchanged.

## Action 730 height grouping, 2026-11-04

The native difficulty-0 first ring (`0x004DCB18..0x004DCB4F`) and difficulty-1
rings (`0x004DC922..0x004DC959` and `0x004DCA12..0x004DCA45`) add the
height offset (10.0 or 25.0) to fighter height before combining it with the
loop's 30.0 step and random jitter, then subtract 10.0. Three source
expressions previously combined the same terms in a different order; they
now preserve the observed grouping. Fresh VC8 code emits the corresponding
height-plus-offset x87 sequence. These paths can differ in floating-point
rounding; no full runtime equivalence is claimed.

The complete 75,042-byte target extent remains nonexact from +8. The candidate
section tail is 76,500 bytes; this selected source contributes no exact bytes.

## Actions 520 and 521 ordered shot gates, 2026-11-04

For the second shot phase, native `0x004D298F..0x004D29A0` and
`0x004D2DDA..0x004D2DEB` load the field at 0x73c, then the limit,
compare, and skip the shot path when `AH & 0x41` is nonzero. The path
therefore requires the field to be ordered and below the limit. The earlier
negated `limit <= field` also admitted NaN; both phase-two source conditions
now use `field < limit`. The fresh VC8 object has the corresponding operand
order, status mask and skip branches at offsets 0x7B8F and 0x7FDB.

The 75,042-byte owned extent remains nonexact from +8 (candidate section tail
76,500 bytes); this local observation adds no exact credit and does not assert
unmasked-exception equivalence.

## Action 707 ordered speed clamp, 2026-11-04

Native `0x004DA5FE..0x004DA623` subtracts from speed and clamps to zero
only when the resulting value is ordered and negative. The status test skips
on `AH & 0x41`, including unordered values. The previous negated `>= 0`
also clamped NaN. The source now uses ordered `< 0`; fresh VC8 emits the
corresponding local test and branch at `0xF89A..0xF8A9`. This does not
establish whole-root or unmasked-exception equivalence.

The 75,042-byte owned extent remains nonexact from +8; the candidate section
tail is 76,500 bytes. No exact credit is added.

## Action 730 vertical jitter, 2026-11-05

The eight object-920 shower loops keep RNG(20)'s unsigned conversion in x87
through the height calculation. For example, native `0x4DCB18..0x4DCB51`
combines the unspilled random value with the loop step and actor height before
the final float store; `0x4DC534..0x4DC56B` does the same for a negative
height offset. The old float jitter locals caused an intermediate float store.
Double locals initialized through the existing float conversion preserve the
native float 2^32 correction and let VC8 keep each jitter in x87. The 0..20 RNG
range is exactly representable in float, so no normal gameplay numeric change
is claimed.

The full owned extent remains nonexact: 75042 bytes of extent, 74937 owned,
first mismatch +8, and candidate section tail 76432. This local restoration
adds no exact-function or byte credit.

## Actions 545–548 skill-level signedness (2026-11-06)

At `0x4D4EEF`, `0x4D5601`, `0x4D5DFC` and `0x4D65BB`, the native dispatcher sign-extends the byte at `0x60A` before selecting cases 1 through 4. The fighter input policy independently reads that field as a signed byte. The four switch expressions now use the same signed view, and the focused candidate emits `movsx` at all four sites instead of `movzx`. Both views choose the same case for every byte value because all values outside 1–4 use the default path. The full focused candidate remains nonexact: section tail 76432 bytes, first mismatch +8. No exact credit is claimed.

### Action 302 timer thresholds

The original phase-1 and phase-3 timer gates at `0x4CD920` and `0x4CD985` use signed comparisons against 25 and 24, respectively, branching while the timer is below each threshold. Writing these as `>= 25` and `>= 24` preserves the previous integer behavior and restores both local comparison-and-branch sequences in the focused candidate. The complete action-state function remains non-exact; its candidate section is 76,432 bytes.

Five further integer gates at `0x4D15CC`, `0x4D1CEF`, `0x4DC451`, `0x4DC468`, and `0x4DCFE9` use thresholds 7, 20, 100, 75, and 8. Equivalent source comparisons recover their local compare-and-branch forms; behavior is unchanged and the 76,432-byte candidate remains non-exact.

Repeated action gates for timer thresholds 10, 35, 45, 60, and 36, plus signed skill level 4, now use the equivalent forms observed in the original. Focused compilation recovers the corresponding local comparison and branch families. Integer behavior is unchanged; the 76,432-byte complete candidate remains non-exact.

Additional timer gates, including `0x4D1F61`, `0x4D8C59`, and `0x4DB352`, now use the equivalent 30-, 60-, and 40-frame comparisons observed in the original. The local signed branch families are recovered; the complete candidate remains non-exact.
