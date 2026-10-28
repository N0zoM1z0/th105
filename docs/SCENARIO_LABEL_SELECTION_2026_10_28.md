# Scenario label selection455490

Complete276-byte native label-search root now has a275-byte unselected
candidate. First mismatch+36 is the persistent owner/subobject receiver
allocation. No exact/source-selection credit.
Receipt: build/frontier-455490-20261028/formal-build.json.
Target SHA:58a5ad2f28ad4f111408771ec435f7b34c3b1bf0bc77deb3185b7ce2f0498190.

The exact Scenario owned-string wrapper and phase-five caller establish the
by-value std::string ABI and RET1C ownership. The routine resets the script
cursor, advances through the real next-command405AC0 interface, considers only
command id0, and compares the TCommand1<std::string> payload with the requested
label. Success/failure both destroy the owned string naturally. No manual SSO
cleanup or guessed stack return is used.

The three old opaque script cells28/2C/30 are independently consistent with
the actual12-byte VC8 checked deque iterator. Its owning pointer deque is at14,
and the CScenarioData script is at35C. The local runtime view uses actual
std::deque<CCommandBase*> and iterator types; it is not constructed and does
not change the shared CScript registry header's historical element-type view.
405AC0's dereference helper uses a private internal register ABI, so it remains
out-of-line and unimplemented here rather than receiving a fabricated prototype.

A named long-lived script receiver produced251 bytes by eliminating the
second native iterator range check and changing return cleanup placement.
That control is private; the simpler member-access275-byte source is retained.
No redundant arithmetic/check, fake liveness, forced register or manual vtable
operation was introduced to retain an optimizer-eliminated check.

The full target CFG closes all decoded instructions and the final RET:
build/frontier-455490-20261028/boundary.json. The added EH address witness
6BA908 is read from the canonical prologue and mapped prefix; no generated
cleanup exactness is claimed. Only this new unit was built.
