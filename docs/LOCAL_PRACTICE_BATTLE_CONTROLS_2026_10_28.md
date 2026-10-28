# Local practice battle controls 0x00428070

Complete482-byte canonical exact body, SHA:
2cbe83e0af6fd37a71102ee91feb50771b4fa455b0c8264aece90fdb5d9de157.
Receipt: build/frontier-428070-20261028/formal-build.json.
The existing method suffix427190 is historical; the current target is428070.

Network-session presence causes an immediate return. Modes2/3 accept inputs
65(reset mode),64(previous mode),63(next mode),59(toggle restoration).
Signed modulo14/2 is preserved, including negative input behavior; no unsigned
substitution or clamping is introduced. Modes2/3/8 additionally allow inputs
61/60 only when neither fighter is in the32..95 state range.

Input61 advances both card sequences five times and then resets both spell
selection modes with1. Input60 prepares both sequences five times. Fresh scene
and fighter pointers are read for each target call; they are not hoisted over
callbacks. All repeated mode queries and the native receiver ABI are retained.
The formerly pending pre-reset472230 and accepted round initializer470BC0
already call this exact decorated method, with unchanged contracts.

Raw recursive CFG reaches all code except the explicit8-byte loop-alignment
gap428228..428230, skipped by JMP at428226. The complete bounded comparison
includes those bytes and final RET at428251. No boundary truncation or partial
credit is used. Receipt: build/frontier-428070-20261028/boundary.json.

Only this new source/unit was built. Existing header declarations and global
bindings were reused unchanged; no other source was affected. Origin rules
contain no exclusion for this game input policy. New authored exact credit:
one function,482 bytes. The callee prepare45DC90 remains nonexact and is not
promoted by this caller.
