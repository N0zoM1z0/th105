# Iku action 224 vertical deceleration

The Japanese 1.06a fighter action dispatcher subtracts 0.5 from the vertical
velocity in sequences 1 and 2. At 0x00623126-0x00623134 it loads the field,
subtracts the double constant, and stores directly to the float field before
calling the surface-crossing check. The former explicit float cast caused VC8
to store and reload an additional float temporary before storing the field.
The natural compound assignment emits the target's direct field store at the
corresponding candidate site. Both versions round to float before the check;
no normal gameplay difference is claimed.

The focused `gpt-web-iku-action-state` comparison remains nonexact: the
59038-byte native body first differs at +100, and the candidate section tail
is 59446 bytes, down from 59462. This local instruction improvement is not
an exact-function or exact-byte credit.
