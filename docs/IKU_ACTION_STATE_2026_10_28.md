
## Action 781 random X argument (2026-11-05)

At `0x62EA72..0x62EAB5`, the native action chooses its direction, places the remaining spawn arguments including Y = -200, calls the 640-range selector, performs unsigned-to-float correction, and writes X directly to the outgoing call slot. The previous source assigned X to a separate float local before preparing the spawn, producing an additional store/reload. Passing the selector conversion directly to the X argument recovers this local call and x87 lifetime in the candidate (`0xDFE8..0xE033`); the direction arithmetic and other scheduling still differ. This does not establish a whole-function match or a normal-gameplay numeric difference.
