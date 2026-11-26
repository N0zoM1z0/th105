# Alice Fighter action-state root: canonical exact

Target: original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `0x004E9F50` is Alice's primary vtable slot `+0x28` at `0x006C4C04`.
The standalone [typed source](../src/characters/AliceFighterActionState.cpp)
matches under VC8 SP1 `/O2 /GS- /GR /EHsc /MT`.

## Canonical exact result

`exact-first-alice-fighter-update` verifies all 42,721 physical code bytes and
the complete 44,072-byte code/switch payload `[0x004E9F50,0x004F4B78)` with zero
differences. All 1,380 relocations agree: 674 REL32 calls across 27 targets and
706 DIR32 fields. The owner audit is 104/104, including entry.

- Code SHA-256:
  `588194779ec2bba363702ac150979a064ce8bf77553bfa727b34951fc8788a89`.
- Payload SHA-256:
  `202e532a593f9c712518519e0c782ce177696ddb3ab401aaec86ec5a113c0f89`.
- Raw CFG reaches 11,169 instructions and 42,718 authored bytes. The three-byte
  `lea ecx,[ecx]` at `0x004F28ED` is unreachable loop alignment, compared in the
  payload and excluded from authored progress.
- Entry aligns ESP to eight bytes and reserves `0x410`; the code has 128 RETs,
  674 direct calls and 163 register-indirect calls.

The sixteen switch tables contain 165 destination words and 685 byte indices.
The three primary maps are:

| Actions | Destinations / words | Indices / bytes |
| --- | --- | --- |
| 0–226 | `0x004F4634` / 31 | `0x004F46B0` / 227 |
| 301–508 | `0x004F4794` / 34 | `0x004F481C` / 208 |
| 521–770 | `0x004F4914` / 40 | `0x004F49B4` / 250 |

Thirteen nested tables are recorded in `config/giant-action-switches.toml`:
eight five-word difficulty tables and five four-word story tables. Two occupy
`[0x004F48EC,0x004F4914)`, between the mid index map and high primary table.
The six metadata-alignment bytes, every destination and every index are part
of the strict comparison.

Earlier probes used a 44,080-byte region ending at the next function,
`0x004F4B80`. Its last eight `INT3` bytes align that independent CPU-policy
function. They follow the final table at `0x004F4B78` and are outside Alice's
owned code/switch payload. The first three bytes after the callable are
`8D4900`, matching the source's table alignment; they are not `INT3` padding.
The callable inventory boundary remains `[0x004E9F50,0x004F4631)`.

## Source shapes that recover the target

The entry skip tests use one short-circuit guard:

```cpp
if (word_186 != 0 || related_170->word_48c != 0)
    return;
```

Two separate early returns emitted the same entry tests but selected different
shared tails throughout the function. Combining them recovered native tail
sharing, moved the physical-owner diagnostic from 35/104 to 96/104 and closed
all direct-call-count differences. This is a VC8 source-shape finding for this
root. Action 10's zero-input arm must also precede its nonzero arm.

Keep 404/406's sequence-four and sequence-eight entry tests independent. The
first action-nine call returns; the second continues into fresh sequence and
time-threshold checks. Combining the outer time guard caches the frame timer
instead of the native time-counter value. Similar independent timer/frame
checks matter in 412, 507/508 and 414–416. Separate terminal entry tests in
414–416 and 543 preserve their native cached values; a cached sequence local
in 547/548 removes a native comparison.

Actions 308/309 read facing inside every iteration of their six object-849
requests. Calls `0x004ECC7B` and `0x004ECDF1` loop through `0x004ECBFA` and
`0x004ECD6A`, respectively, before reloading byte `+0x104`. The old snapshot
across callbacks was incorrect. Negate the converted float index before
multiplying by double 60 to retain `fild; fchs; fmul`.

Action 321 passes zero to `0x00478EE0`, subtracts double 1.0 (`0x006CD160`)
and initializes horizontal velocity to float 10.0 (`0x006D6EEC`). Action 402's
three stores form `{0,0,7}`. The earlier gate one, damping 0.5, velocity 7.5
and `{0,7,0}` packet were incorrect.

Several other recovered lifetimes affect the whole root:

- Dust computes double `x + 50` before RNG calls. Paired dash effects and 695's
  effects reload facing between callbacks. 197–199 use live peer/member reads.
- 525/526 repeat the double `n * 2.0` calculations for both packet fields.
  A cached float adds narrowing; a cached double changes load placement.
- 721's hard/normal arcs form a double offset before adding the base angle.
  730 constructs its direction with signed-byte arithmetic.
- Updating 310's velocity member before widening it for predictive landing
  recovers its native float temporary; an extra float carrier changes its home.
- Native comparison spellings include time `>=39` in 600/601/603/604,
  unsigned RNG `<=50` in 545–548, word `+0x7A4 >=3`, and time `>33` in 566.

## Request storage and publication

The source reserves three floats for each 570/571 request buffer while passing
count four, matching the native twelve-byte homes at post-prologue ESP `+0x78`
and `+0x6C`. Only three words are written; the manager really copies sixteen
bytes. Preserve the unwritten fourth transmitted word. Four-float storage
instead produces frame `0x418` and moves many unrelated packet homes. The
complete exact result supports the recovered allocation, but does not uniquely
identify the original declarations or the incoming fourth-word value.

Select 570/571's angle with `if (index > 0) ... else 0`, and write packet element
two once per conditional arm. Initializing before the branch adds stores that
the target lacks. Preserve the post-spawn publication order:

| Actions | Order after spawn |
| --- | --- |
| 410 | wave, adjust, scale, field `+0x180 = 1` |
| 411/412/415/416 | wave, field `+0x180 = 1`, adjust, scale |
| 414 | wave, adjust, field `+0x180 = 1`, scale |

The typed receiver checks every accessed member offset at compile time.
Several field meanings and the concrete complete class layout remain unknown.
No shared gameplay layout or callee implementation changed.

## Reproduction and retained evidence

```bash
WINEDEBUG=-all DISPLAY= WAYLAND_DISPLAY= scripts/repo-python scripts/build.py --unit exact-first-alice-fighter-update --compare --json
scripts/repo-python scripts/audit-giant-action-owners.py --unit exact-first-alice-fighter-update alice-vslot28 build/match-units/ExactFirst_AliceFighterActionState.obj --json
```

Current private reports are `build/alice-root-work-codex/canonical.json` and
`owners.json`. The full switch contract is in `config/match-units.toml`; the
main alignment exclusion is in `config/function-byte-exclusions.toml`.

Alice exposed two bounded comparator omissions: its physical code ends with
an unconditional jump into an earlier shared exit, and its first difficulty
bound is derived by `mov ebp,8; lea ebx,[ebp-4]`. The verifier now accepts that
internal jump while retaining guard/CFG checks, and propagates nonvolatile
constants through plain register copies and unindexed LEA. Twenty-eight focused
positive/negative tests pass, including fallthrough, metadata-entry,
partial-register and bypassed-definition failures. Fresh complete Alice,
Marisa and Sakuya comparisons pass.

Width/profile sweeps, adding lexical braces, swapping jump cases and expanding
shared action labels did not recover the target. Ordinary SP1 compilation with
live callback fields and the recovered guard/storage lifetimes does.
