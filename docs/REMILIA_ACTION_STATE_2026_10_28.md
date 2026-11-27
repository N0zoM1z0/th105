# Remilia action-state root (`0x00545090`), JP 1.06a

## Canonical exact result

`exact-first-remilia-action-state` matches the original Japanese TH10.5 v1.06a
Remilia Fighter `+0x28` root (`0x00545090`) with zero byte differences under
VC8 SP1 `/O2 /GS- /GR /EHsc /MT` from the character-scoped
[source](../src/characters/RemiliaActionState.cpp) and checked typed receiver
[header](../src/characters/RemiliaActionState.hpp).

- Callable code: **61,962 physical bytes** (`[0x00545090, 0x0055429A)`),
  SHA-256 `cffbd3c34e8a10be85f5236a16afad7e035227df15bf420b9eb30599fce0092b`.
  Raw CFG reaches **15,972 of 15,973** decoded instructions (**61,959 authored
  bytes**); one unreachable 3-byte VC8 loop-alignment `lea ecx, [ecx]` at
  `0x00551DAD..0x00551DAF` is compared and excluded from authored progress in
  `config/function-byte-exclusions.toml`.
- Complete switch payload: **63,316 bytes** (`[0x00545090, 0x005547E4)`),
  SHA-256 `1c631b6ff3b591e2f96c1ad5de0957213a71855231e79d3768726acd1752c5a3`,
  covering all **16 switch tables** (3 sparse action tables `low`/`mid`/`high`,
  4 five-entry skill tables, 9 four-entry difficulty tables: **160 destination
  words**, **709 index bytes**, **5 alignment bytes**).
- Relocations: **2,127** total (**967 REL32** calls across 31 targets, **1,160
  DIR32** fields), all verified.
- Owner audit: **103/103** `instruction_edge_identical_owners`.

Reproduce:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-remilia-action-state --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-remilia-action-state remilia-vslot28 build/match-units/ExactFirst_RemiliaActionState.obj --json
```

### Key findings that closed exactness

- **Checked typed receiver & calling conventions**: replaced `at<T>` pointer
  casts with `offsetof`-checked fields in `RemiliaActionStateView`, fixed
  `word_76a`/`word_76c` as two `short` fields (2-byte aligned, matching
  `word [esi+0x76c] = 0; word [esi+0x76a] = 1`), corrected `remilia_sine`/
  `remilia_cosine` return types to `float`, typed `spawn`'s direction and layer
  parameters as `signed char` and `effect`'s direction as `unsigned char`
  (eliminating `movzx` register shuffles in `500`/`501`), and dispatched
  `0x00435160` (`oriented_components`) through the `+0x04` `RemiliaActionScratch`
  subobject (`lea ecx, [esi+4]` in `560` and `721`).
- **Receiver correction in `607` and `710`**: the wave handle call `16`
  dispatches through `owner_168->dispatch_character_wave_handle(16)` (`mov ecx,
  [esi+0x168]`), not `this`.
- **Switch & CFG structure**: post-switch `advance()` with `break;` in cases
  `0, 2, 4, 5, 9` and separate inline `208..212, 220..222` cases with
  `if (!entry(1)) return;` restored all 32 `low` destinations (preventing
  `209` and `212/221` from merging). Separate `if (entry(k))` guards in `505`,
  split `charged` vs uncharged loops in `fan817` (`530`/`531`), `static_cast<double>(n) < field_740`
  in `ring815` (`520`/`521`), `p[0] >= 0.0f && p[0] <= 180.0f` in `565`/`566`/`720`,
  `byte_113 >= 10` / `crossed()` branch polarities in `730`/`731`, `word_732 >= N`
  in `741`, inlined `400` float-loop / `414`/`415` air-801 paths (eliminating
  spurious `npad` alignment cascades and restoring `0x546382` tail merging), and
  `double step = field_73c * 90.0;` in `710` mode 1 matched the exact x87
  instruction schedule and native `sub esp, 0x4f0` frame.
- **Verifier support**: `scripts/coff_switch_payload.py` now accepts VC8's
  flag-preserving `mov edi, 60` scheduled between `cmp eax, 3` and `ja` in
  `action720` (`diff_2`), covered by positive/negative tests in
  `tests/test_coff_switch_payload.py`.
- **Preserved native packet extents**: action `408` (one written float passed
  with count 3) and actions `530`/`531` (three written floats passed with count
  4) remain faithfully unpadded as in the target binary. Full `Fighter` class
  layout and TU boundaries remain outside this character-scoped unit.

## Historical development notes (2026-10-28 – 2026-11-06)

## Target and boundary evidence

The hash-attested original Japanese 1.06a executable is
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
Factory-native IDA metadata, entry, function inventory, and five mapped-byte
probes were independently checked at 03:27–03:28 UTC on October 28.
Factory discovery reattested its metadata at 04:04 UTC. The local legacy
check-ida-mcp.py cannot load mcp==1.26.0; this is not a successful legacy
preflight and is not evidence that Factory IDA is disconnected. No dependency
installation was used. Decompiler output is only a semantic hypothesis.

Raw target CFG closure covers 0x545090..0x55429A:
- 61,962-byte callable span; 15,973 decoded instructions.
- 15,972 reachable instructions / 61,959 reachable instruction bytes.
- Only three unreachable alignment bytes at 0x551DAD..0x551DB0.
- 146 RET instructions and 967 direct call sites to 31 targets.
- No unresolved indirect exit after closing all sixteen tables.
- Three sparse action tables: low 32, mid 42, high 30 destinations.
- Four five-entry skill tables and nine four-entry difficulty tables.
- Direct action 300 and shared 560/561 are outside those sparse tables.
- Complete payload ends at 0x5547E4, size 63,316.

Callable SHA-256:
cffbd3c34e8a10be85f5236a16afad7e035227df15bf420b9eb30599fce0092b

Full payload SHA-256:
1c631b6ff3b591e2f96c1ad5de0957213a71855231e79d3768726acd1752c5a3

## Recovered source and ABI

The pointer-only view is not a complete recovered Fighter layout. It keeps
VC8 field widths and virtual sequence slots. initialize_fighter_phase_631e0
uses the previously established fastcall ABI; oriented motion uses the
established two-float thiscall at 0x435160.

All 63 native crossed-surface consumers test AL, including two that first
load a vtable pointer. The generic immediate-consumer diagnostic reports
false for those two; raw instructions establish the actual width. The
candidate has 62 physical crossed calls because native low owners 209 and
212/221 merge. This is not a reason to reinterpret the result as full EAX.

The 101 native and 101 candidate spawn-payload homes resolve without unknown
payload pointers. This proves pointer provenance, not initialization or
dynamic equivalence. Two unusual native extents are intentionally exposed:
- Action 408 passes count three with only one written scalar. Its next
  native payload home is four bytes later.
- Four action 530/531 packets pass count four, while only three scalar cells
  belong to each recovered packet extent and are initialized.

The extra values are **not recovered**. The candidate does not invent zero
initializers or reserve inert cells to repair this mismatch. These paths
need callee/use and original allocation ownership review before source
selection; this is not a portable runtime-safety claim.

Other independently reviewed details include:
- Flight 214 is a burst with entry/frame-specific angle processing, not
  another character's continuous flight loop.
- 525/526 timeout compares signed time with signed-char skill level.
- 565/566 and 720 retain the native unsigned direction in the second
  mirrored X coordinate; do not silently normalize it to signed facing.
- 730/731 difficulty one falls through to difficulty zero's second emission.
- Floating-point arithmetic operation counts agree for every mapped action
  after correcting negative flash offsets and avoiding X+0 in charge effects.

Physical call-site diagnostics differ for action 710 (native/candidate
spawn sites 8/5 and virtual sites 2/3). Shared tails are not dynamic call
counts; trace the exact call arguments and incoming edges before changing
behavior. Native/candidate stack frames both equal 1264 bytes, return sites
146/145, virtual call sites 179/181. Stack coloring and physical ownership
remain open, not solved by the count agreement.

## Focused replay

Only the new unit was compiled; no shared accepted source was changed and
no cold full-corpus run was performed.

taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-remilia-action-state --compare --json
    scripts/repo-python scripts/ci.py
    git diff --check

Both comparator commands correctly report mismatch. The full-payload audit
rechecks target hash, all table destinations, complete reachability, exact
unmasked bytes and payload length.

Final candidate SHA-256:
629b1dfc49d0a7a2afcec1090b6715cbb892bbe76bb74cca44e8b20a3955e70b

Full positional differences including absent trailing bytes: 59,877.
That count is diagnostic, not a semantic similarity or completion metric.

The checked-in source is authoritative. Existing exact receipts remain incremental.

### Physical-owner refinement

The native low sequence places action 214 before 215. Restoring that source
order brings its physical owner span from 1010 to 810 bytes (native 811),
without changing action semantics or adding a padding/return workaround.
The native prelude captures unsigned direction once and then sign-extends
that captured byte for X. The candidate now expresses that flow explicitly.
Neither of those two changes solved the then-first +8 mismatch; no exact credit was awarded.

### Native-size frame from circular request preparation

The 730/731 circular 902 requests prepare count, pointer, layer and direction
before calling sine (for example 0x551DF2..0x551E22), then put the rounded Y
value on the outgoing stack before cosine. The former source instead named
both Y and X before preparing the request.

Only ring 902 now expresses X/Y directly in the ordinary call arguments. It
preserves the same casts, packet writes, float loop, lookup order and field
loads. This restores the native call-preparation lifetime and reduces frame
0x4F8 to 0x4F0. The first strict mismatch advances from +8 to +18, at the
choice of EBX versus EBP for zero, not a newly accepted function.

All 101 payload homes still resolve; their native/candidate sorted offset
sets now coincide, including the unusual adjacent extents noted above.
Fresh mapped-action arithmetic counts still agree, and the same action 710
physical-call residual remains. Final full payload is 62,912 versus 63,316.
This is an independent native instruction witness, not an automatic transfer
of Komachi's different scalar-angle cause. No packet padding, dummy locals,
register forcing, or compiler-flag change is used.

## Diving ring angle grouping, 2026-11-04

The native 565 and 566 loops at `0x0054DA16..0x0054DA32` and
`0x0054DF13..0x0054DF2F`, and action 720 at
`0x00550E95..0x00550EB1`, form the loop-angle product plus 30.0 before
adding the converted random value. The two corresponding source expressions
now preserve this grouping, and the fresh VC8 object emits the same x87
multiply/add/add-stack sequence. The bounded integer loop and random values
are exactly representable, so this is a source-structure correction rather
than a claimed gameplay change.

The complete `0x00545090` callable remains nonexact, first mismatch +18;
the candidate section tail is 62,912 bytes against the 61,962-byte callable.
It remains unselected and adds no exact credit.

## Spell spawn-height grouping, 2026-11-04

The native 730/731 ring sites, including `0x00551E22..0x00551E3F` and
`0x00552B83..0x00552B8F`, add 100.0 to the fighter height before combining
it with the sine offset. The native 741 site `0x00553796..0x005537AB`
similarly adds 230.0 to the height before the sine offset. The two source
expressions now preserve those groupings. A fresh object emits corresponding
x87 height-load/add/add-stack sequences. Since floating-point addition is not
generally associative, this corrects a meaningful precision distinction; it
does not establish gameplay equivalence.

The whole 61,962-byte callable remains nonexact from +18; the 62,912-byte
candidate section tail is not a full-function match. No source selection or
exact-byte credit is added.

### Fan and orbit direction reads (2026-11-05)

The pinned target's fan-817, ring-902 and object-903 paths capture unsigned direction before sine and reload signed facing after cosine, for example `0x54C4BA..0x54C538`, `0x551E08..0x551E9C` and `0x553784..0x5537F4`. The earlier candidate used an early cached signed value. The source now makes the two reads explicit while retaining the angle and radius reloads and original coordinate associations. Rebuilt dispatch code shows the later signed read at four fan-817 sites, eight ring-902 sites and the object-903 site. Trig helpers do not ordinarily mutate the receiver; no normal-play effect is claimed from this ordering correction.

Strict callable-boundary comparison remains nonmatching: target 61,962 bytes, candidate section tail 63,100 bytes, first difference +47. The separate 63,316-byte original full payload includes tables; neither size comparison establishes exactness or adds match credit.

## Reverse-object signed X offsets, 2026-11-05

The native object 826 reverse-facing requests at `0x54DB75..0x54DBBE` and `0x54E072..0x54E0BB`, and the object 901 request at `0x550FA1..0x550FE8`, sign-extend the freshly read facing byte before multiplying by 50 for X. They separately negate its low byte for the facing argument. The earlier source used the unsigned byte in the X calculation for the second request. With facing `0xFF` this gave X+12750 rather than the native X-50. Both source sites now use the signed value; the 826 helper expands into the two native paths. Focused VC8 compilation shows the corresponding sign extension and multiply in all three generated paths. The full root remains nonexact, and this correction adds no exact credit.

## Action 606 signed sequence gate, 2026-11-05

At `0x54F50D..0x54F530`, the original compares the 16-bit sequence against 3 with signed `jg`, then tests the frame when equal. The earlier source explicitly converted the signed field to unsigned before `> 3`, incorrectly taking the texture branch for a negative sequence. Removing that conversion restores the target comparison. Reachability of negative sequence values during ordinary play is not established. Focused VC8 compilation remains nonexact for the whole root; no exact credit is added.

## Action 741 signed counter threshold, 2026-11-05

The target at `0x553675..0x553695` compares the 16-bit counter at `0x732` with 60 using signed `jl`; a negative value is incremented rather than triggering the reset. The prior source read the counter as unsigned, which treated negative values as above threshold. The field is now read as signed for this comparison. Focused VC8 compilation emits a signed conditional jump; ordinary-play reachability of negative counter values is not established. The whole root remains nonexact and receives no exact credit.

## Action 741 later signed counter thresholds, 2026-11-05

The same `0x732` counter is compared as signed against 90 at `0x553B0C..0x553B2C` and against 30 at `0x553FA5..0x553FC5`, both using `jl`. Four difficulty-source branches share the former native comparison. The earlier unsigned reads incorrectly took the reset path for negative counters; the five source comparisons now preserve signed behavior. Focused VC8 emits signed `jge` gates for both thresholds. Negative-value reachability in ordinary play remains unproved, and the full root remains nonexact without exact credit.

## Unsigned random conversion constants, 2026-11-05

The native action root uses the float `2^32` correction for unsigned random results, for example at `0x548746..0x548762`. Eleven source expressions converted those results directly to double and produced 35 expanded double-correction sites. Expressing the float conversion before promotion restores the observed correction type: native and focused candidate each contain 92 float corrections and no double corrections, versus 57 float and 35 double in the previous candidate. The aggregate categories of the next x87 operation remain the same, with no added early float-store category. The count is a diagnostic rather than a per-site or full-function match proof. The calls use bounded, small integer ranges, so no ordinary-play numeric difference is established. The complete 61,962-byte root remains nonexact at +47 with a 63,052-byte candidate section tail; no exact credit is claimed.

## Object 800 fan-angle association, 2026-11-05

Nine native fan paths, including `0x5485A9..0x5485C6` and
`0x54875C..0x548779`, retain the unsigned random conversion in x87, load the
angle field, subtract the 10 or 15 degree bias from that field, then add the
random value. The shared source previously grouped the addition before the
subtraction. Parenthesizing the field-minus-bias expression restores the
native operation order for both integer and float loop variants. The unsigned
conversion still uses the native float 2^32 correction. The ordinary action
angle and bounded RNG ranges do not establish a gameplay difference; the
change follows the observed arithmetic association.

The complete target remains 61962 bytes and nonexact at +47; the candidate
section tail is 63068. Matching an operation order does not grant exact-function
or byte credit.

## Action 710 mode-1 angle association, 2026-11-05

For the first object-900 request in mode 1, native `0x550605..0x550629`
combines `state_73c * 90` with `(state_744 - 45)`. The prior source grouped
the multiplication and `state_744` first, then subtracted 45. Parentheses now
preserve the native association; VC8 emits the field subtraction before the
final addition, though it schedules the independent multiplication later
than the target. No normal-play numeric difference is established. The root
remains 61962 bytes, nonexact at +47, with candidate section tail 63068; no
exact credit is claimed.

## Surface-height spawn arguments (2026-11-05)

Three calls in actions 600 and 603 use the surface provider's return directly as spawn Y in the target, including `0x54E62D..0x54E654` and the two separately called 603 paths beginning at `0x54EE7B`. Direct arguments reproduce these local provider-to-outgoing-slot lifetimes. Action 711's native `0x550A18..0x550A3F` also passes the return directly, but making its source identical to action 600 caused VC8 to merge two physical target call sites into one. Its previous float local is therefore retained while that code-sharing difference remains unresolved. The selected candidate keeps both 850 call sites; the 711 local still introduces an extra store/reload. Direction remains captured before each provider call; no whole-root exactness or normal-gameplay numerical difference is asserted.

## Action 711 surface argument and direction width (2026-11-06)

The earlier action 711 float local preserved the two physical object-850
spawn sites but introduced an extra store and reload of the surface return.
Keeping the captured direction as its observed unsigned-byte value and passing
the surface call directly to the spawn is a natural alternative. It preserves
both physical 850 pushes while removing the extra surface-result spill. The
candidate at `0xB815..0xB840` captures the direction before the provider call,
stores the provider's result directly into outgoing Y, and then loads X, as in
native `0x550A18..0x550A3F`. The exact instruction schedule still differs:
the candidate loads the byte and zero-extends it separately. No claim of a
normal-play numerical difference is made.

The selected root remains nonexact, with 63,036-byte section tail and compared
SHA-256 `d066c11f0aa3334b9ff2391104fbc454875386b39054c23b04f87517f340ec57`.
This supersedes the retained-local limitation in the preceding section; the
complete function earns no exact-byte credit.
