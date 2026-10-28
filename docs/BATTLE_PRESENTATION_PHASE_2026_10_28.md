# Battle presentation phase and Story reset wrapper

Complete canonical exact bodies: 46B160..46B1C9 exclusive,105 bytes;
471580..47158E exclusive,14 bytes. Both are game policy, not compiler helpers.
Origin rules select neither for exclusion. The shared phase has one final RET
and all instructions are reachable; the Story wrapper stores a signed-short
zero then tail-jumps to that phase. Its pointer is Story vtable6C1374 slot3C,
at6C13B0. These raw observations refer only to the SHA-pinned Japanese1.06a PE.

The presentation phase tests both fighter texture-duration words at6A0 using
short-circuit evaluation. Either nonzero value sets the shared background
effect deltaFC to -10. It reads game mode separately for exclusions4 and5,
then invokes input update428260 when neither exclusion holds. Effect sink
vslot14 and background update466F40 follow, then the shared pair tick increments.
The source does not cache a mode call or change callback/global reload order.

Existing target-backed global bindings and shared interfaces are reused.
The input callee's nominal original method name/return spelling is unknown;
the caller view consumes no result and preserves ECX and cleanup. Neither
the local owner-view names nor the unselected input callee receive additional
identity or exactness claims. The Story wrapper clears the observed short
mode value6FA88C and uses the normal member-call ABI.

Fresh focused comparison receipts:
- build/frontier-46b160-20261028/formal-build.json:105/105,
  SHA b1723b43395f50c1664937aaac71e58ddd0b15371dc14cebb84b91fe76a6afdb.
- build/frontier-46b160-20261028/story-caller.json:14/14 and all five
  previously accepted Story phase peers203/157/309/59/88 unchanged exact.

Only these two units were built. No global compiler options, relocation
ledger, shared data layout or defensive behavior changed. No assembly,
padding, register forcing or artificial liveness is used.
New authored exact increment:119 bytes.
