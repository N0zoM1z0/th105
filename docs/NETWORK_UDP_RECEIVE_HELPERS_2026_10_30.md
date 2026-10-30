# UDP rejection and endpoint-list source recovery

Two previously unclassified helpers now have explicit authored/source entries:
415B90 (122 bytes) and 415C10 (315 bytes). They were already present as private
C++ definitions in the real receive-loop TU, but lacked individual ownership
and comparison records. Neither receives exact credit. Existing 1530 exact
functions / 434133 bytes remain unchanged.

## Observed behavior and boundaries

The canonical Japanese 1.06a receive loop calls rejection at 41DAEA after its
opcode 7, four-byte payload and state 3 gates. The helper uses ESI for the UDP
owner and one stack packet pointer, returning with RET4. It locks callback
member +84, invokes virtual slot +4 with packet DWORD +0 if callback +80 is
nonnull, sets state +144 to 9, then unlocks. All 35 instructions / 122 bytes
are reachable. Complete body SHA256:
`ae62a5f7d4885b130e65630893135dd3df77835c188955e3f3c1c52bea30e9ca`.

Opcode 8 instead requires a 68-byte payload and calls 415C10 at 41DB02.
This helper uses EDI owner and one stack packet pointer. Under endpoint lock
+E0, signed count is clamped only above four. A current address/port repeated
in those entries returns early. Otherwise it copies the old endpoint to +4C,
selects packet entry zero even when count is nonpositive, sets marker +148 to
FFFFFFFF, erases the endpoint vector's complete iterator range, appends count
entries, then sets state +144 to 2. Do not add a nonnegative-count guard.

The native range erase at 415D06 retains begin/end iterator checks. The old
source's clear() omitted these operations; it now uses erase(begin(), end()).
The full 315-byte extent includes the three-byte alignment LEA at 415C6D and
an early-return cleanup branch after the main RET4. No padding is waived.
Complete body SHA256:
`232bf915cc0c440bbc53b8d9f606e3fc93456875053a427e324062edec2e2e6d`.

Both helpers have native one-state cleanup EH. Rejection selects handler
6BD688 / FuncInfo 6E3C5C; endpoint-list selects 6BE128 / 6E4860. The complete
27-byte handlers are recorded as symbol-owned address bindings for ordinary
COFF comparison. This binding alone does not prove compiled EH equality.

## Fresh source results

Ordinary COFF rejection is 122/122 with 12 differing bytes caused by EH-state
store scheduling. Genuine mixed COFF/LTCG receive/peer/accept/thread context
naturally recovers its ESI receiver and full 122-byte instruction sequence.
A main-only diagnostic replays its two typed prologue addresses and is equal;
full source EH and the switch-bearing private caller are not yet admitted by
the canonical linked contract. It remains nonexact in the accepted ledger.

Endpoint-list is 400/315 in ordinary COFF and 515/315 in the genuine linked
context. The remaining differences include vector helper boundaries, receiver
allocation and inlining. No private ABI facade, added storage or helper copy
was used. The new source operation is justified by the native iterator checks,
not by a claim that a smaller source extent is exact.

The sole affected unit is cross-v106a-network-winsock-receive-thread. Its
previously accepted 14-byte entry remains exact. The old 148-byte key and
33-byte checked-access diagnostic controls also remain exact but retain their
prior origin-review/no-credit status. All nine ordinary function comparisons
resolve their relocations; only previously accepted roots remain credited.

Private evidence: .analysis/frontier-udp-endpoint-list-20261030 and
build/frontier-udp-endpoint-list-20261030, including boundaries.json,
formal.json and rejection-main-diagnostic.json. Reproduce the ordinary unit:

`scripts/repo-python scripts/build.py --unit cross-v106a-network-winsock-receive-thread --compare --json`

## Adjacent negative controls

The UDP owner's actual peer/send contexts and ordinary CIL tree
instantiations still emit a 341-byte destructor versus native 333. The packet
pool destructor remains 98-byte exact. A fresh known-packet shutdown control
still emits 150 versus 149 and lacks the target's aligned EBP frame; the
native minimum opcode source remains selected. These are bounded negatives,
not exclusions from future target-backed reconstruction.
