# Iku action 730 ring angles

The 1.06a action 730 sequence-5 ring emits object 920 in six loop copies.
For the three zero-offset rings, native code multiplies the float loop value
by 30 and stores the result without adding zero (for example 0x0062DF75-
0x0062DF86). The other three copies add 10 or 20 after the multiplication.
The shared source helper formerly added its offset even when it was zero,
creating three extra x87 additions. The zero-offset expression is now separate;
the nonzero rings retain their additions. The float loop values run from 0 to
11, so no ordinary numeric difference is claimed.

The candidate now has zero zero-offset additions, two additions of 10, and one
of 20, consistent with these six native loop copies. The complete dispatcher
remains nonexact: target size 59038, candidate section tail 59426, first
mismatch +100. These observations do not grant exact-function or byte credit.
