# Original short-deque pop_back

428680 is the complete23-byte VC8 std::deque<short>::pop_back emitted by the
unchanged official-header instantiation scripts/probes/deque_short.cpp.
It has no relocation, no hidden tail, and a complete closed CFG. All23 bytes
match exactly. The method conditionally decrements the size at+10 and resets
the offset at+0C only when the deque becomes empty; it does not invent element
cleanup for trivial shorts.

Byte equality alone is not unique:413DF0 has the same23 bytes and stays in
review. The actual original _Insert_n member provides the independent identity:
its source relocation1094 names this pop_back, and native call463D05 targets
428680. The whole native1404-byte insertion body is pinned. The existing
insertion provenance gate freshly recompiles its original source and retains
its full-inventory uniqueness,0.70/24-byte/non-tail criteria unchanged. The new
leaf uses its own complete-body and caller proof, not a relaxed generic threshold.
No exclusive original specialization spelling or linker ICF choice is claimed.

Compiler, instantiation source and original deque/xmemory/xutility headers are
pinned. The public formal unit compares exactly23/23. Ten tests and1450 actual
byte mutations cover both23-byte identities and the full1404-byte owner; all
are rejected. This adds only23 compiler-library bytes to exclusions, with no
new insertion/EH/provider or authored credit.

Excluded2065, review306, units808; authored exact1432/443941 bytes,
source-present1637 and authored1656 remain unchanged. The older SHORT_DEQUE_INSERT
note that428680 remains review is superseded only for this now separately proved
callee. Other incoming calls and413DF0 remain independent work; no inferred blanket
deque exclusion is made.

Nov2:413DF0 is separately qualified through its actual unsigned-deque range
insertion caller; see UNSIGNED_DEQUE_POP_BACK_2026_11_02.md. The short-deque
proof above still selects only428680 and its byte-identity limits are unchanged.
