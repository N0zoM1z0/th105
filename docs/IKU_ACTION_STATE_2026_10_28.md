
## Action 781 random X argument (2026-11-05)

At `0x62EA72..0x62EAB5`, the native action chooses its direction, places the remaining spawn arguments including Y = -200, calls the 640-range selector, performs unsigned-to-float correction, and writes X directly to the outgoing call slot. The previous source assigned X to a separate float local before preparing the spawn, producing an additional store/reload. Passing the selector conversion directly to the X argument recovers this local call and x87 lifetime in the candidate (`0xDFE8..0xE033`); the direction arithmetic and other scheduling still differ. This does not establish a whole-function match or a normal-gameplay numeric difference.

## Action 302 independent braking paths (2026-11-05)

Target `0x623984..0x623A00` tests sequence 0 and sequence 1 independently. Each checks horizontal velocity, subtracts its own constant (`0.5` or `1.0`) and clamps a negative result to zero while retaining the target's x87 zero across both checks. The prior combined condition and ternary reproduced the ordinary selection but merged the two arithmetic paths. Expressing the two observed checks separately restores their physical instruction structure in candidate `0x2F7E..0x2FFB`, including separate literal subtractions and clamp comparisons. Some registers and surrounding layout still differ, and the complete fighter root remains nonexact. This observation does not claim a difference on normal inputs between the two source forms.
