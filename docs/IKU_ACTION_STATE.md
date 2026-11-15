# Iku action state 0x620920

`Iku_dispatch_action_state_vslot28` spans [0x620920, 0x62EFBE), 59,038 bytes:
15,132 instructions, 131 returns and three indirect switches, with all 110
nondefault actions plus the shared default. It is a `void` thiscall method with
no stack arguments. The complete source is `src/characters/IkuActionState.cpp`,
compared by unit `gpt-web-iku-action-state`. It is nonexact; the last recorded
first difference was at +100, with the candidate section at 59,426 bytes.

## Source shapes recovered from target bytes

Each of these restores the local instruction shape; the whole root still
differs.
- **Integer gates use the target's literals.** The timer gate at 0x624442 is
  `>= 15`; five gates at 0x6210C3, 0x621202, 0x627323, 0x627497 and 0x62BF61
  use timer 40 and frame 11 thresholds; the skill gates at 0x6284F3 and
  0x62880F use `>= 4`. (See the integer-literal rule in the
  [patterns note](VC8_SOURCE_SHAPE_PATTERNS.md).)
- **Action 224** (0x623126..0x623134) subtracts 0.5 from the vertical velocity
  with a compound assignment; an explicit float cast added a store and reload.
- **Action 302** (0x623984..0x623A00) tests sequences 0 and 1 separately, each
  with its own subtraction (0.5 or 1.0) and clamp to zero. A combined
  condition merged the two paths.
- **Action 730's ring** (around 0x62DF75) multiplies the loop value by 30
  without adding a zero offset in the three zero-offset copies; the other copies
  add 10 or 20.
- **Action 740** (0x62E341) dispatches phases 1–3 through a switch, and
  **action 781** (0x62E928) phases 0 and 1 through a two-case switch.
- **Action 781's spawn** (0x62EA72..0x62EAB5) passes the selector's converted
  value straight to the X argument instead of through a float local.

## Still differing

Register choice and the surrounding layout around these sites, and action
781's direction arithmetic.

The October checkpoint notes for this root were removed in the commit that
added this note; Git history keeps them.
