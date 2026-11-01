# Original cache-list sentinel allocation

Native6A3BD0/26 is now whole canonical from the original VC8 std::list
specialization used by Boost's narrow Windows-regex object cache. It allocates
20 bytes with the named original operator new, preserves both null/field checks
and initializes the two self-linked list-node prefix pointers. No payload
construction, invented sentinel data or game-authored algorithm is supplied.

The unchanged original seven-TU graph yields the actual mangled specialization
and its original CIL owner. Every byte compares after the sole E8 field3 is
resolved to original operator new689DCB. There are no HIGHLOW/data references,
all closed CFG paths participate, no non-call byte changes and the complete
canonical26-byte body is unique across the entire candidate inventory.

## Independent owner evidence

Original object_cache<unsigned long,w32_regex_traits_implementation<char>>::data
construction calls this exact emitted list helper once, then publishes EAX as
head at+4 and zeroes count+8. Independently classified native cache-data
constructor6B0310/125 does the same at actual call6B0339. Its whole reviewed
native hash and existing Boost origin rule are required. Both full caller CFGs
are decoded, the direct call and immediate two header publications are checked,
and different owner registers are permitted only as observed compiler output.

The source constructor117/native125 is NOT declared byte-exact or the same
private ABI. The source/native larger do_get callers1139/1187 were also observed,
but neither is promoted. The accepted leaf is the data-independent20-byte
allocation/link prefix, not a new claim about application payload nominal types.
This is stronger than transferring a masked helper shape across unknown callers.

Only6A3BD0 moves from review to compiler-generated exclusion. Excluded2004/
review368; authored exact1431/443916 bytes, source1635/authored1655/mapped1820/
units776 remain unchanged. No generic minimum-byte/coverage gate is lowered.

## Reproduction and validation

- scripts/repo-python scripts/linked_list_node_origins.py
- Narrow function-origins.validate_rule_evidence replay.
- Eight synthetic tests cover exact specialization, complete selection, wrong
  call/site, returned head/count values, offsets and common owner identity.
- Five private real-byte mutations of allocation size, link and caller
  publications are all rejected.
- scripts/repo-python scripts/ci.py and git diff --check pass.

Contract: config/linked-list-node-origin-anchors.toml.
Proof: build/origin-anchors/linked-list-node/proof.json.
Private discovery: .analysis/frontier-linked-list-node-20261101/.

Target is the pinned original Japanese1.06a PE. No new IDA semantic dependency,
generated executable execution, copied implementation, fake caller or ABI
declaration is introduced. Existing parents, original public Boost root and
payload-dependent tree leads remain outside this exact leaf acceptance.
