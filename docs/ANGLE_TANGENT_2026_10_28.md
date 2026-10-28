# Exact float-angle tangent 0x00406430

Japanese TH1051.06a target SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Complete exact result

src/engine/AngleTangent.cpp reproduces all69 bytes,406430..406475 exclusive.
Target and canonical relocated object share SHA-256:
10156df6311fa6629b4a580867db0ad2875a7800f688544e66fc48ce7387722b.

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-angle-tangent --compare --json

Receipt: build/frontier-406430-20261028/formal-build.json. The source uses one
real cosine temporary, an ordered-zero guard and a quotient. No assembly,
copied instructions, padding, artificial storage, volatile locals, self-assignment
or register forcing is present.

## Native evidence and configuration

The69-byte body is fully decoded with one RET and no external code tail.
The first call406439 targets cosine4063D0; ST0 is materialized as m32. Native
FUCOMP returns positive zero on ordered equality, while unordered values proceed
to sine406360 at406461 and division by the stored cosine. The quotient is
materialized as m32 before returning in ST0.

Default precise-FP emits63 bytes and differs at+22. Plain strict FP produces the
quiet comparison but70 bytes and exception-sensitive argument scheduling.
Strict FP with exception-sensitive scheduling disabled matches69/69.
Command-line /fp:strict /fp:except- and the retained balanced
float_control(except, off, push)/pop source independently reproduce the body.
This is the already established integer-angle ratio configuration, not a new
global profile or proof of the unique original compiler flags. No build tool,
shared header or global compiler default changed.

The pinned raw PE was the oracle. Unavailable IDA routes from the enclosing
Udonge investigation were skipped; no IDA metadata was written for acceptance.

## Ownership and limits

Udonge5BFD50 makes20 decoded direct calls to this helper. For example5CA391
passes its cone angle; after the call the caller loads peer X, computes the
cone boundary and compares with previously captured QWORD Y. The game-owned
sine/cosine lookups and those callers support authored engine ownership.

The float(float) tangent declaration is a coherent complete-byte reconstruction,
not proof of unique original spelling. Sine/cosine retain the repository's
double(float) declaration view; those callees remain nonexact and ST0 alone
does not uniquely prove their original return spelling. No credit transfers
to either dependency or any caller.

The origin census update uses its existing canonical-exact baseline for this
previously unclassified row. An attempted full origin regeneration timed out
without writing it; the affected row alone was regenerated with baseline().
All other origin rows and rule definitions are unchanged.

Only the tangent unit was built for acceptance. No accepted consumer source
changed and no cold full-corpus replay was run. This adds one exact function
and69 exact bytes; Udonge remains nonexact.
