# Shared CNumber in design rendering, 2026-11-02

Target SHA-256: 56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

DesignNumberRender.cpp now uses the shared CNumber class for its number member
and ordinary unexported helpers. NumberColorView / NumberRenderView are removed;
the design object's color base uses IColor. The same helper declarations are
friends of CNumber so they can read its existing private fields. This changes
access visibility only, not layout, runtime code or calling-protocol controls.
The independently observed digit-count fields still use their existing names
reserved_18 / reserved_1c. No original source spelling or access policy is claimed.

The integer-render definition is extracted verbatim from CNumberRuntime.cpp into
CNumberIntegerRender.cpp and included by both existing runtime and linked design
contexts. DesignNumberRenderProviders.cpp now includes real shared definitions
instead of duplicating the integer body on another class. The initial private
whole-runtime include introduced unrelated texture-initialization dependencies
and failed to link; it is not retained. No invented provider or absolute binding
was used to resolve that experiment. Sharing the actual integer definition keeps
the established provider graph and FP pragma context unchanged.

All four linked roots remain canonical: design render 55, offset render 63,
bound dispatcher 95 and floating renderer 581 bytes. The existing private
caller-edge proofs, naturally chosen EAX / ESI protocols and 64-byte floating
frame alignment remain intact. Existing public-member preservation only changes
its integer-render symbol to CNumber; no new preserve item, export barrier,
noinline annotation, dummy storage or ABI prescription is introduced.

Actual quoted-include closure: 10 units. All 25 accepted roots in nine units
pass final replays. Six other roots in five units retain their hashes, including
CNumber initialization's closed 102 / 104-byte residual. The existing implicit
cleanup gate passes 3 / 28 after renewing the conservative header source pin;
affected scalar gates pass 1 / 30 and 2 / 121. No origin/ledger counts change.

Final CI passed all 962 tests in 115.052 seconds. Both diff checks gate the local
checkpoint. Totals remain 1426 exact / 443399 bytes, source 1636, authored 1655,
mapped 1826, excluded 2076, review 296 and units 813.
