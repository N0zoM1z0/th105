# Scenario label selection455490

Complete276-byte native label-search root now has a275-byte unselected candidate.
First mismatch+36 is the persistent owner/subobject receiver allocation. No
exact/source-selection credit. Target
SHA:58a5ad2f28ad4f111408771ec435f7b34c3b1bf0bc77deb3185b7ce2f0498190.

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

The added EH address witness 6BA908 is read from the canonical prologue and mapped
prefix; no generated cleanup exactness is claimed. Only this new unit was built.

## Actual owner and registry control, 2026-10-31

The current shared CScript now has the genuine pointer deque and checked
iterator, superseding the historical opaque/element-type limitation above.
A bounded control puts the same method on the actual complete CScenarioData
layout and accesses CScript.pending_14/current_28 directly, with an ordinary
next_command member declaration. It still emits275/native276, first+36.
The canonical compared body hash is identical to a fresh restored baseline:
3eea55109cff650d5f922a2d9fad6ebdd64592846bb7569b67f87bedd5b09790.

Thus the recovered full owner/registry layout does not resolve the receiver lifetime
residual. Both temporary nonvirtual declarations, source and manifest are fully
restored. No source/ledger/exact increment or ABI forcing is retained.
