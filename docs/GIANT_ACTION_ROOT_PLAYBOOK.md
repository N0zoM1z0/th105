# Giant Fighter Action-State Root Playbook

Practical workflow for reconstructing TH105 v1.06a Fighter vtable `+0x28`
(`*_dispatch_action_state_vslot28`, 37–82 KiB) and similar multi-table switch
roots to 100% canonical byte equality under VC8 SP1 (`/O2 /GS- /GR /EHsc /MT`).

Proven exact on:
- `Reimu_dispatch_action_state_vslot28` (`0x00478FA0`, 81,550 callable / 82,924 envelope, 11 switch tables)
- `Iku_dispatch_action_state_vslot28` (`0x00620920`, 59,038 callable / 60,194 envelope, 3 switch tables)
- `Aya_dispatch_action_state_vslot28` (`0x00602250`, 65,601 callable / 66,704 envelope, 7 switch tables)
- `Youmu_dispatch_action_state_vslot28` (`0x00530200`, 37,692 callable / 38,816 envelope, 4 switch tables)
- `Marisa_dispatch_action_state_vslot28` (`0x004A3710`, 66,695 callable / 67,936 envelope, 6 switch tables)
- `Sakuya_dispatch_action_state_vslot28` (`0x004CADB0`, 74,937 owned / 75,042 physical code / 76,336 envelope, 14 switch tables)

Update this playbook and [scripts/giant-root-iterate.py](../scripts/giant-root-iterate.py)
whenever a new root reveals a reusable pattern or compiler rule.

## 1. Fast Iteration Tooling

Use [scripts/giant-root-iterate.py](../scripts/giant-root-iterate.py) for tight
compile-audit-diff loops against any root registered in
[config/giant-action-switches.toml](../config/giant-action-switches.toml) and
[config/match-units.toml](../config/match-units.toml):

```bash
# Compile a scratch copy and print summary + non-exact owners + direct-call deltas
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/giant-root-iterate.py \
  --root aya-vslot28 --unit exact-first-aya-action-state \
  --compile build/aya-root-work/aya_v1.cpp --obj build/aya-root-work/aya_v1.obj

# Diff specific owners (target '-' vs candidate '+')
scripts/repo-python scripts/giant-root-iterate.py \
  --root aya-vslot28 --unit exact-first-aya-action-state \
  --obj build/aya-root-work/aya_v1.obj --diff low:214 mid:404

# Dump raw target disassembly of one or more owners
scripts/repo-python scripts/giant-root-iterate.py \
  --root aya-vslot28 --unit exact-first-aya-action-state \
  --target high:740
```

If an early draft has extra or missing `rel32` / `dir32` symbols (for example,
after changing a parameter width to `signed char` or `unsigned char`), pass
`--rel32 Symbol=0xAddress` or `--dir32 Symbol=Target` on the command line until
you promote the final source into `config/match-units.toml`.

This script is strictly diagnostic. Canonical acceptance is always:

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit <unit> --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit <unit> <root> <object>
```

## 2. Five-Step Opening Pass (Apply Before Micro-Tuning)

Most early drafts carry structural artifacts that distort global register
allocation, tail merging, and branch sizing across all 100+ cases. Fix these
five items **first**, before looking at individual small diffs:

1. **Replace `byte_at` / `float_at` / `raw + offset` casts with typed struct members.**
   Char-pointer casts create aliasing barriers that block VC8 scheduling and
   hoisting. Define a character-scoped typed receiver (`*ActionStateView`) and
   peer struct (`*PeerView`) with compile-time `offsetof` assertions.
2. **Fix byte-width ABI signatures on shared fighter calls.**
   - `emit_fighter_effect(..., unsigned char direction, int trailing)` (`0x00435240`)
   - `spawn_owned_object_via_manager(..., signed char direction, int layer, const void *payload, int count)` (`0x00465190`)
   - Passing `int` instead of `unsigned char`/`signed char` adds sign/zero
     extension noise and blocks `push ebx` (`-1`) reuse.
3. **Flatten `goto` labels and early-`return` `__forceinline` helpers.**
   - Delete artificial shared `goto` labels (`landed`, `idle_drift`, etc.) and
     write each case's natural statements inline; VC8 `TailMerge` creates the
     real shared tails automatically.
   - Inline any `__forceinline` helper that contains early `return;` statements
     (such as `try_dispatch_verified_action`, `try_dispatch_verified_glide_action`,
     or multi-case fans) directly into the `switch`. Early returns inside
     inlined helpers reorder the `L_ret` predecessor list in `c2.dll:0x10B307E0`,
     reversing tail-merge winners across unrelated cases.
   - Place `advance_frame_and_dispatch();` immediately after the `switch` and
     exit bare-advance cases (`0, 2, 4, 5, 9`, and any trailing `break` owner
     such as Iku `781`) with `break;`.
4. **Lock global register allocation (`ebp`, `edi`, `ebx`) and direct-call counts first.**
   - Align `case 214` (flight/glide, ~2.2 KiB; structurally shared across
     roster characters — start from Reimu/Iku's exact `case 214` shape) and
     eliminate every direct-call count delta (`865/865`, etc.) before touching
     small cases.
   - A single wrong register choice (e.g. `ebx = 1` instead of `edi = 1`) causes
     dozens of false diffs across the entire function.
   - For projectile rings with `payload[0] >= 0.0f && payload[0] <= 180.0f ? 1 : -1`,
     write `if (...) spawn(..., 1, ...); else spawn(..., -1, ...);` — VC8
     tail-merges the `call 0x465190` and matches target call counts.
5. **Ignore 16-byte loop-alignment padding and `disp = 115..126` 6-byte `0F 85` diffs until all real code diffs are zero.**
   - See Section 4 (`WidenBranches` `0x10C56F50`). Both are pure downstream
     consequences of upstream size deltas of even 1–2 bytes and snap
     automatically once real code diffs reach zero.

## 3. Shared Fighter Receiver Offsets (v1.06a)

Verified identical across Reimu (`0x00478FA0`) and Iku (`0x00620920`). Check
each character's accesses and pin every used field with compile-time `offsetof`
assertions:

| Offset | Type | Meaning |
| --- | --- | --- |
| `0x000` | vtable | Virtual slots (`+0x08 set_action_and_finalize`, `+0x0C select_sequence`, `+0x10 set_sequence_frame`, `+0x14 next_sequence_block`) |
| `0x004` | subobject | Action scratch / motion helper base (`reset_fighter_action_scratch`, `set_oriented_components`) |
| `0x0EC` | `float` | `x_ec` |
| `0x0F0` | `float` | `y_f0` |
| `0x0F4` | `float` | `velocity_x_f4` |
| `0x0F8` | `float` | `velocity_y_f8` |
| `0x100` | `float` | `acceleration_y_100` |
| `0x104` | `signed char` | `facing_104` (`1` or `-1`) |
| `0x110..0x112` | `unsigned char` | RGB tint bytes (`byte_110`, `byte_111`, `byte_112`) |
| `0x130` | subobject | Event pair view (`set_global_pair`) |
| `0x13C` | `short` | `action_id_13c` |
| `0x13E` | `short` | `sequence_index_13e` |
| `0x140` | `short` | `frame_index_140` |
| `0x142` | `short` | `frame_timer_142` |
| `0x144` | `int` | `time_counter_144` |
| `0x168` | pointer | Secondary fighter/emitter view (character-specific) |
| `0x170` | pointer | `related_170` (opponent peer view: `x_ec`, `y_f0`, `facing_104`, `word_174`, `word_48c`) |
| `0x174` | `short` | `word_174` (active combo/guard word) |
| `0x180` | `int` | `state_180` |
| `0x186` | `short` | `word_186` (hitstop/freeze guard) |
| `0x47E` | `unsigned char` | `byte_47e` (air/ground slide flag) |
| `0x482` | `short` | `word_482` (spirit / guard meter) |
| `0x48A` | `short` | `word_48a` (spell freeze / flash timer) |
| `0x4A8`, `0x4AC` | `short` | Invulnerability / graze counters |
| `0x4B8` | `int` | `field_4b8` (weather / spirit modifier) |
| `0x606` | `unsigned char` | `byte_606` (card/skill level) |
| `0x655` | `unsigned char` | `byte_655` (portrait/cutin flag) |
| `0x6B4..0x6C8` | `int` | Directional & button inputs (`6b4` X, `6b8` Y, `6bc..6c8` buttons) |
| `0x72C` | `unsigned char` | `byte_72c` (mode/round flag) |
| `0x730..0x738` | `short` | Per-action work counters (`word_730..word_738`) |
| `0x73C`, `0x740` | `float` | Per-action work floats (`field_73c`, `field_740`) |
| `0x750`, `0x751` | `unsigned char` | Charge / guard-effect flags |
| `0x764..0x76C` | `short` | Story/spell counters |
| `0x78C` | `short` | `word_78c` |
| `0x7A0`, `0x7A2` | `short` | Per-frame reset words (`0`, character constant) |
| `0x7B0..0x7B4` | `short`/`float` | Character-specific state words/floats |

## 4. Key VC8 SP1 `c2.dll` Mechanics Reference

Detailed proofs live in [VC8_SOURCE_SHAPE_PATTERNS.md](VC8_SOURCE_SHAPE_PATTERNS.md):

- **Post-switch `advance_frame_and_dispatch()` (`0x10B281E0` before x87 `0x10C28970`)**:
  Places the shared `fstp st(0); mov ecx, esi; call advance; ret` tail on the
  designated `break;` owner (usually `case 9`; `case 781` in Iku) and prevents
  premature `mov ecx, esi` hoisting.
- **Tail-merge `saved_bytes` & `CanFoldBranch` (`0x10B307E0`, `0x10B30B97`, `0x10B30D90`)**:
  Under `/O2`, short merges (`<= 20B`) require either `CanFoldBranch` (branch
  right before the matched suffix) or an earlier `> 20B` merge that raised
  `[branch + 0x1c]` (`saved_bytes`, capped at 20). When two candidates both
  pass `CanFoldBranch`, the earlier predecessor on the target label's list stays
  inline. Avoid artificial labels and early-`return` helpers so the natural
  predecessor order matches.
- **Branch widening & phantom alignment slack (`0x10B24EE0`, `0x10C56F50`)**:
  VC8 starts all branches 2-byte short (`0x1c6`/`0x1c8`) and widens to 6-byte
  near (`0xf`/`0x10`) in a fixpoint loop. On forward branches to unvisited
  labels, `0x10C56F75` adds the pass's cumulative widening delta (`[esp+0x1c]`)
  to the previous-pass label offset while 16-byte loop alignment (`0x10B25058`)
  shifts `current_offset` without adjusting `[esp+0x1c]`. Thus a forward jump
  of `116..127` bytes can legitimately stay 6-byte `0F 85` in standalone COFF
  builds whenever upstream alignment savings push its pass estimate above `127`.
- **LIFO weight-sorted stack-slot packing (`esp+0x10` vs `esp+0x20`, proven via `/FA`)**:
  `c2.dll` sorts non-address-taken stack temps and spilled scalars by descending
  use count and assigns them to a LIFO list of 8-byte-aligned slots (`-984` =
  `esp+0x20` first, `-1000` = `esp+0x10` created at the list head upon the first
  interference). Every subsequent lower-weight symbol hits the newly prepended
  head slot (`esp+0x10`). In Aya `720`/`721`, hoisting `float base;` before
  `switch (g_aya_action_match)` (13 uses -> placed in `esp+0x20`) and using
  per-loop `for (float counter = 0.0f; ...)` (5 uses -> interferes with `base`,
  prepending `esp+0x10` right between use-count 6 and 4) simultaneously fixed
  all 168 `esp+0x10` vs `esp+0x20` diffs across 14 unrelated cases (`201`,
  `224`, `307`, `418`, `505..508`, `530`, `532`, `560`, `561`, `720`, `721`).

## 5. High-Frequency VC8 Source-Shape Idioms

| Target assembly signature | Natural C++ source shape |
| --- | --- |
| `fiadd dword ptr [esp+disp]` without float spill | `expr + static_cast<float>(word_x + 100)` |
| `cmp eax, 0x32; setb al; mov ecx, 1; add al, al; sub cl, al` | `static_cast<signed char>(1 - 2 * (static_cast<unsigned>(random(100)) < 50))` |
| `fld [esi+A]; fadd [esi+B]` when `B` appeared earlier in function | `double t = A; B = static_cast<float>(t + B);` |
| Right-to-left RNG arg evaluation inside `spawn(...)` | Call `static_cast<unsigned>(random(...))` directly in args, not via `__forceinline` wrapper |
| `movsx edx, [esi+0x104]; fmul ...; movzx ecx, [esi+0x104]` (no `mov al` CSE) | Inline `aya_cosine(...) * radius * facing_104 + x_ec` directly inside `spawn(...)` args instead of `double baseX`/`baseY` locals |
| `cmp dword ptr [esi+0x6bc], ebp; ja/jbe` on button hold counters | Declare `field_6bc`, `field_6c0`, `field_6c4` as `unsigned int` and test `> 0` |
| Uninitialized `count` with `>= 4`, `<= 3`, `<= 1` + synthesized `sub [esp+0x10], 0x14` | `int count; if (lv >= 4) count = 4; if (lv <= 3) count = 3; if (lv <= 1) count = 2; for (int i = 0; i < count; ++i) { packet[0] = i * -20 + 20.0; ... }` |
| Reverse-ordered `sub eax, 1; je` chain or descending direct table for `g_match_identifier` | `switch (g_match_identifier) { case 3: ... case 2: ... case 1: ... case 0: ... }` |
| `fld [esp+packet2]; fadd [esi+0xf0]` instead of `fld [esi+0xf0]; fadd [esp+packet2]` | Preserve `float dx = ...; aya_atan(related_170->y_f0 - y_f0, dx);` (natural `dx` local, inline `dy`) so `y_f0` and `packet` keep their target CSE/VN order |
| Head-merged `packet[0..2]` init before `if (!(word % 2))` | Write `packet[0..2]` assignments inside *both* `if` and `else` branches so VC8 head-merges them above `jne` |
| `mov ebx, 5` hoisted before `jne` on `frame_timer_142` | `if (sequence_index_13e == 0) { if (frame_timer_142 == 0 && frame_index_140 == 3) ... }` |
| `[esp+0x10]` vs `[esp+0x14]` float rounding temp | Assign directly to member instead of `float adjusted = ...; member = adjusted;` |
| `push 1` instead of `push edi` before a loop that clobbers `edi` | Check nested `if (frame_timer_142 == 0) { if (frame_index_140 == N) ... }` after loop |
| `fstp` / `call 0x465190` tail-merged across `1` / `-1` layer | `if (cond) spawn(..., 1, ...); else spawn(..., -1, ...);` |

## 6. Promotion & Verification Checklist

1. Promote clean source (no dead helpers, CRLF per `.gitattributes`, no
   trailing whitespace) into `src/characters/`.
2. Update `config/match-units.toml` (`rel32_targets`, `dir32_targets`, and full
   `switch_payload` with `load_offset` / `jump_offset` at instruction starts,
   not immediate displacement offsets).
3. Run strict verification:
   ```bash
   WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit <unit> --compare --json
   scripts/repo-python scripts/audit-giant-action-owners.py --unit <unit> <root> <object>
   ```
4. Update `config/functions.csv` (`matching,100.00`), `config/implemented.csv`
   (if absent), `config/matches.csv`, and `config/reccmp-relocations.csv` (if
   any new literals were needed).
5. Run ledger, literal, progress, and CI checks:
   ```bash
   scripts/repo-python scripts/verify-target.py
   scripts/repo-python scripts/validate-tracking.py --require-target
   scripts/repo-python scripts/check-match-literals.py --require-target
   scripts/repo-python scripts/progress.py
   scripts/repo-python scripts/report-reconstruction-status.py --summary
   python3 scripts/ci.py
   ```
6. Delete scratch directories under `build/<char>-root-work/`, update
   [RE_HANDOFF.md](RE_HANDOFF.md) and this playbook with any new findings, and
   commit cleanly.

## Youmu source-shape findings

`Youmu_dispatch_action_state_vslot28` at `0x00530200` now matches all
37,692 callable bytes and its complete 38,816-byte envelope under VC8 SP1
`/O2 /GS- /GR /EHsc /MT`, in unit `gpt-web-youmu-vslot28-full-root`.
[The source](../src/characters/YoumuActionState.cpp) and its
[manifest contract](../config/match-units.toml) reproduce four switches,
707 index bytes, 1,126 relocations and 98/98 instruction/edge-identical owners.
Callable SHA-256 is
`19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`;
full-envelope SHA-256 is
`07283bd567ce8a199d6d14db90f27218521b465e4a7a2954c231ae9b259b16b3`.
Use the same build/audit commands as Section 6 with this unit and `youmu-vslot28`.

The target observations and successful source controls support these additions
to the opening pass:

- **Keep float member updates direct.** Decompiler-created float copies such as
  `float next = velocity_x - amount; velocity_x = next; if (next < 0) ...`
  allocated competing stack slots across this root. Updating and testing the
  typed member directly recovered the target's shared rounding slots. Preserve
  explicit float rounding when removing a carrier that was subsequently widened
  to double; merely deleting that rounding changes the expression.
- **Read the opponent through the member at each operation.** Removing cached
  opponent pointers in actions525/526 recovered the target's pointer reloads,
  virtual-call registers and complete physical owners. A same-layout receiver
  or inheritance-only rewrite did not resolve those cached lifetimes.
- **Retain independent early exits.** In actions302 and603, write
  `if (advance()) { set_action(0); return; }` followed by
  `if (sequence_entry(1)) { set_action(0); return; }`. Combining these into one
  `if (advance() || sequence_entry(1))` retained the instruction count but selected
  the wrong physical action-zero tail in302 and a different volatile-register
  cycle in603. Splitting them resolved the final differences. Copying the
  opponent X into a local, moving/initializing the payload array, adding an
  inlined emitter wrapper and changing the action parameter from short to int
  did not fix that register cycle.
- **Structure the whole action before adjusting local registers.** Removing
  action603's shared `goto` labels and writing its sequence0/2/3/4 blocks
  naturally recovered late constant lifetimes and downstream alignment together.
  An early local rewrite could reduce the owner count while correcting real
  arithmetic or argument scheduling; revisit global stack placement afterward.
- **Preserve signed byte reads separately from unsigned snapshots.** Youmu's
  `byte_184` comparisons are signed, two `byte_47e` tests read it as signed char,
  and the direction snapshots used by actions600/730 are zero-extended before
  their signed arithmetic. Collapsing these distinctions lost otherwise equal
  owners. The exact local spawn view uses signed char for both direction and
  the control byte forwarded to factory `+0x33c`; the effect direction is
  unsigned char. Original declarations are not uniquely determined by the
  compatible caller view.

Action720 also exposes a verifier scheduling case at `0x00538C5D`: after
`cmp eax, 3`, VC8 emits `mov edx, 10; lea ecx, [edx+10]` before `ja` and the
four-entry direct jump table. These instructions preserve EFLAGS and EAX.
The verifier accepts these specific register forms only when neither replaces
the selector, and still rejects branches into the protected setup. Positive,
selector-clobber, flag-clobber and bypass cases are in
[the focused tests](../tests/test_coff_switch_payload.py).


## Marisa source-shape findings

`exact-first-marisa-action-state` reproduces the complete 66,695-byte callable
and 67,936-byte envelope under VC8 SP1 `/O2 /GS- /GR /EHsc /MT`, with 125/125
owners. [The root note](MARISA_ACTION_STATE_2026_10_28.md) gives the hashes,
commands, relocation census and private result paths.

For actions 570–573, expand the volley into its actual branch arms and give
its positive and negative loops separate counter lifetimes. This shape removes
the extra eight-byte frame area and recovers the native `0x4C0` frame and
scalar slots. Keep the conditional packet level initialization as one store
per path. Merely shrinking the two partially initialized 307/308 arrays from
three floats to two also produced the right frame size, but moved their homes
and other payloads incorrectly. That trial was rejected; exact source retains
the three-float arrays and their unwritten third elements.

In 565–568, Y is computed as a double before the packet branch and narrowed to
float separately at each spawn call. A cached float Y emits one narrowing
before the branch; the target emits one in each call arm. Moving the float
cast changes precision and lifetime, so inspect the whole call site. Negative
integer offsets also use explicit float conversion where the target emits
`fisub`; widening the integer directly to double instead emits `fild/fsubp`.

Independent frame guards matter in 307/308/547: put the sequence test outside,
then test timer/frame separately for each arm. Combining the timer into the
outer guard caches the frame index and removes two native instructions.
Likewise, flatten the two frame guards in 615 while retaining the sequence
reread after its spawn calls; an extra outer sequence guard delayed the
shared constant-40 load. Separate the two action choices in 310 with an early
return to recover the physical set-action-2 tail and its consumers.

Use the target's physical action order: 658, 611, then 610. Reordering these
blocks recovered the remainder register in 658, its shared landing tail and
612's volatile vcall registers. In 525, the observed thresholds are explicitly
`>=4`, `<=3`, and `<=1`; equivalent bounds change reuse of the live constant 3.
These are local observations, not a rule to normalize bounds across a root.

The full comparison corrected actions 730/732's destinations to 731/733 and
retained both repeated flight-release gates. It also fixes the association in
720's horizontal velocity to `(destination - x) * rate * facing`, allowing the
rate to remain live for vertical velocity. Arithmetic association, callback
rereads and unwritten packet fields need target evidence even when a retained
candidate has the right action labels and direct-call counts.

## Sakuya source-shape findings

`exact-first-sakuya-action-state` reproduces the complete 76,336-byte envelope
at `0x004CADB0`, including ten remote code chunks, fourteen tables and all
2,805 relocations. The [root note](SAKUYA_ACTION_STATE_2026_10_28.md) preserves
its main boundary, owned-byte accounting and commands.

- **Keep independent guards independent.** Separate `ENTRY(1)` / `ENTRY(2)`
  tests in 404–406, 414–415 and 565–566 preserve the native time-counter
  lifetime. A shared outer time test caches the timer instead. In 520/521 and
  525/526, keep only sequence zero as the outer guard and repeat the timer
  test in each frame arm. The observed frame/timer order varies by action.
- **Let VC8 extract repeated arithmetic.** In 400/402, repeating `word_732 % 3`
  in the two sequence branches recovers the common leading division and native
  volatile registers. An explicit cached remainder changes those registers and
  breaks shared virtual-call tails. In 304, read the sequence member directly;
  a cached short introduces two extra jumps around the landing alternatives.
- **Use direct arguments and their observed precision.** In 605, cached facing,
  X and Y carriers prevent the native flash tail from merging with 607. In
  565/566, inline facing and trig expressions in the spawn arguments. For
  411/415/416, `30.0 - absolute(2.0 - i) * 2.0` preserves the double subtraction;
  a float temporary added to itself introduces narrowing and changes packet
  weights. Action 416 uses `30.0 + y_f0 + i * 6.0`; the second level-two arcs in
  546/548 use `i * 40.0 + y_f0 + 40.0`.
- **Recover each scalar lifetime.** In 720, declare the random float angle
  before the difficulty switch and keep each loop counter local to its arm;
  this also restores scalar slots in unrelated movement cases. In 721's
  hardest arm, a live double `offset = i * 15.0` before the payload assignment
  preserves multiply-before-member-load order. Action 603 similarly needs a
  float angle product before adding 15 degrees. In 730's easy arm, separate
  double row lifetimes recover both volleys; the first Y expression is
  `URAND(20) + (y_f0 + 10.0 + row) - 10.0`.
- **Retain the difficulty structure.** Story arms appear in source order
  3, 2, 1, 0. In 740, write the identical assignments in their separate cases
  and let the compiler merge them. The second volley uses a nested switch
  with cases 2 and 3 sharing a body. An equality disjunction emits two compares;
  a hand-written unsigned range changes volatile-register choices across the
  root. Preserve the uninitialized default reads.

The 95 payload homes include twelve four-float arrays passed with count three.
Initialize only the three target-written elements. Shrinking their storage loses
48 frame bytes; using a three-item aggregate initializer for a four-element array
adds unwanted fourth-element stores. The complete match supports this recovered
allocation; the original declarations remain unknown. Finally, action 10's
zero-input branch precedes its nonzero branch in the natural source.


## Alice source-shape findings

Alice's complete 44,072-byte code/switch payload is exact under
`exact-first-alice-fighter-update`; the [root note](ALICE_FIGHTER_UPDATE_2026_10_25.md)
records its scope and commands.

A single `if (word_186 != 0 || related_170->word_48c != 0) return;` recovers native
tail sharing. Two separate early returns produce the same entry instructions
but different common tails across the root: combining them raised the owner
diagnostic from 35/104 to 96/104 and closed every direct-call-count difference.
The final independent entry guards in 404/406 recover their time-counter
lifetime; the sequence-eight action-nine call continues into threshold checks.

Callback snapshots can distort global allocation as well as behavior. In
308/309, reload facing inside every request-loop iteration. Negate the float
index before multiplying by double 60. Direct velocity-member updates in 310
also recover the native temporary, while a separate float carrier changes it.

Packet declarations need a whole-home census. Alice570/571 reserve three floats,
pass count four and leave the fourth transmitted word unwritten. Four-float
storage gives the wrong frame and moves other packet homes. The final complete
match supports the twelve-byte allocation; preserve the target overread.
