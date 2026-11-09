# Animation frame and action return contracts

The original frame-setting chain and the action-finalization chain are separate.
The evidence below supports retaining the existing source until their virtual
consumers are resolved, rather than changing every int declaration to void.
The two next-frame/block byte statuses are positively consumed by native code.

## Original target evidence

This pass used the hash-attested Japanese 1.06a PE, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Private scripts are in `.analysis/frontier-animation-return-contract-20261109/`;
results are in the corresponding `build/` directory.

- The fourteen frame/sequence virtual addresses occur in 53 primary tables with
  valid COL/type-descriptor records and offset zero. Their slots +0C through
  +24 form two patterns: 49 actor tables and four effect tables. There are no
  unowned aligned references to these addresses in the non-executable sections.
  This is a census of those method references, not a proof of the full hierarchy.
- `direct-proof.json` closes 23 original bodies, totaling 2,337 bytes. An
  independent executable-section E8/E9 byte scan agrees with all eleven decoded
  direct edges to the 21 audited method targets. Both terminal jumps from
  `0x436760` to `0x4073C0` are included. The otherwise unreachable six-byte
  `lea ebx,[ebx]` at `0x473BEA` is verified as native loop alignment.
- `wrap-reads.json` separately closes the 62-byte dispatcher at `0x4351C0`,
  including its indirect terminal jump. It tests AL from slot +20 at
  `0x4351EC`, then tail-dispatches slot +14 at `0x4351F8` on wrap. Thus the
  next-frame and next-block return signals must remain value-bearing.

## Three different return paths

Frame application `0x45C110` / `0x473950` tails to `0x436760`. Setting or
stepping backward through a frame reaches that same leaf; reset, select and
previous-block methods finish through virtual slot +1C. The sprite leaf itself
performs texture and transform work. Its final 24-byte commit operation at
`0x4073C0` does not write EAX. Register contents left by those operations are
not evidence of a separately defined status.

The other direct user, Youmu's `0x53CDF0`, overwrites AL immediately after its
call at `0x53CE24` and derives its own return from object state. The two
next-frame methods also calculate their own AL wrap status after applying the
frame. Neither observation proves that every other virtual caller discards EAX.

Action setters `0x45BFE0` and `0x45C000` first call `0x435200` / `0x435220`,
then invoke slot +3C. Their return register comes from that callback, not
straight from the frame leaf. The 53 tables contain 35 distinct +3C entries,
including the pure-call target. These overrides require their own return and
consumer evidence; a void declaration on `0x436760` cannot establish their type.

## Consumer search and decision

The bounded register-target search found 121 immediate EAX-read candidates at
slots +0C, +10, +18, +1C and +24. Accounting for partial-register writes and
zeroing idioms reduced these to 54 actual reads in the searched windows.
For example, `fnstsw ax; test ah,...` reads the new x87 status, not a value
returned by the preceding animation call.

Same slot numbers also occur on unrelated interfaces. The two reads at
`0x46E0E2` and `0x46E0FC`, for example, load the receiver from fighter +658 and
consume a collision-list pointer. They do not call the fighter's frame slot.
The other candidates are retained with their instruction context in
`read-review.json`; they have not become a universal receiver-type proof.

The search does not resolve memory-target calls, every reaching definition,
or return-value liveness across arbitrary control flow. That remaining gap
prevents a family-wide int/void change. No game source, ABI, parameter width,
source pin or exactness ledger changed, and no new exact credit is claimed.
A future pass should start from an unresolved concrete caller or override,
not repeat declaration comparisons or treat local byte equality as a type proof.
