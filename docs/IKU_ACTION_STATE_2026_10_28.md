
## Action 781 random X argument (2026-11-05)

At `0x62EA72..0x62EAB5`, the native action chooses its direction, places the remaining spawn arguments including Y = -200, calls the 640-range selector, performs unsigned-to-float correction, and writes X directly to the outgoing call slot. The previous source assigned X to a separate float local before preparing the spawn, producing an additional store/reload. Passing the selector conversion directly to the X argument recovers this local call and x87 lifetime in the candidate (`0xDFE8..0xE033`); the direction arithmetic and other scheduling still differ. This does not establish a whole-function match or a normal-gameplay numeric difference.

## Action 302 independent braking paths (2026-11-05)

Target `0x623984..0x623A00` tests sequence 0 and sequence 1 independently. Each checks horizontal velocity, subtracts its own constant (`0.5` or `1.0`) and clamps a negative result to zero while retaining the target's x87 zero across both checks. The prior combined condition and ternary reproduced the ordinary selection but merged the two arithmetic paths. Expressing the two observed checks separately restores their physical instruction structure in candidate `0x2F7E..0x2FFB`, including separate literal subtractions and clamp comparisons. Some registers and surrounding layout still differ, and the complete fighter root remains nonexact. This observation does not claim a difference on normal inputs between the two source forms.

## Actions 740 and 781 phase dispatch (2026-11-06)

At `0x62E341` the native action 740 groups phases 1–3 through a signed switch-style range dispatch; at `0x62E928` action 781 dispatches phases 0 and 1 through a signed two-arm subtraction chain. Expressing these existing source conditions as ordinary switches restores those local instruction shapes in the focused VC8 output while retaining the same phase and default behavior. Register choices and the full function still differ. The candidate section tail is 59430 bytes, with first mismatch +100; no exact credit is claimed.

### Timer threshold

The original gate at `0x624442` branches while the timer is below 15. The equivalent `>= 15` source form recovers that local comparison and branch. Integer behavior is unchanged; the 59,430-byte candidate remains non-exact.

Five further original integer gates at `0x6210C3`, `0x621202`, `0x627323`, `0x627497`, and `0x62BF61` use timer 40 and frame 11 thresholds. Equivalent source forms recover the local signed comparisons and branches without changing integer behavior. The 59,430-byte candidate remains non-exact.

Two repeated signed skill-level gates at `0x6284F3` and `0x62880F` now use the equivalent `>= 4` bound, recovering the local signed comparison and branch. The complete candidate remains non-exact.
