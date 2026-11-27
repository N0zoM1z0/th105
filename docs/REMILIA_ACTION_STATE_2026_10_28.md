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

Private reports: `build/remilia-root-work/{canonical,owners}.json`.

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
- **Verifier support**: `scripts/coff_switch_payload.py` accepts VC8's
  flag-preserving `mov edi, 60` scheduled between `cmp eax, 3` and `ja` in
  `action720` (`diff_2`), covered by positive/negative tests in
  `tests/test_coff_switch_payload.py`.

## Preserved target semantics

- Partial checked receiver (`RemiliaActionStateView`) is pointer-only; full
  `Fighter` class layout, TU boundaries and several field meanings remain open.
- **Unpadded native packet extents**: action `408` writes 1 float and passes
  count `3`; four action `530`/`531` packets write 3 floats and pass count `4`.
  The source preserves these target-observed extents without inventing zero
  padding.
- Flight `214` is a burst with entry/frame-specific angle processing rather
  than a continuous peer flight loop; `525`/`526` compare signed time with
  signed-char skill level; `606` and `741` (`0x732` vs `60`/`90`/`30`) use
  signed comparisons; `730`/`731` difficulty `1` falls through to difficulty
  `0`'s second emission.
- Fan-817, ring-902 and object-903 paths capture unsigned direction before sine
  and reload signed facing after cosine; reverse-facing `826`/`901` spawns
  negate the low direction byte while sign-extending facing for `facing * 50`;
  all 92 unsigned random conversions use the float `2^32` correction.
