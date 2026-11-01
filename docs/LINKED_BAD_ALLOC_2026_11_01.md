# Original bad_alloc and allocator overflow paths

## Result and ownership

The unchanged original seven-TU Boost/VC8 CIL graph reproduces five complete
native bodies,242 bytes total:
- 401630/11: bad_alloc normal destructor.
- 401640/36: bad_alloc scalar deleting destructor (folded vector alias once).
- 402680/25: bad_alloc copy constructor.
- 402590/85: one-byte allocator allocation/overflow.
- 410130/85: four-byte allocator allocation/overflow.

All have zero unequal bytes, zero masks, complete control-flow boundaries and
unique full canonical hits across the function inventory. They are generated/
library ownership, not authored-game exact credit. Long is the original
four-byte family witness, not a guessed nominal game payload type.

Actual bad_alloc RTTI at6C05A0, original source/archive symbol ownership and
typed metadata establish identity. A preliminary25-byte shape at401780 is
NOT bad_alloc: it calls logic_error4017A0 and writes a different class vptr.
The real bad_alloc copy is402680, proved by native ThrowInfo and complete code.
401780 remains review; no shape-only nominal classification is accepted.

Only five rows change to exclusion: excluded1994/review378. Authored
exact1431/443916 bytes, source1635/authored1655/mapped1820/units776 stay.

## Overflow and noreturn proof

The allocator bodies each have an ordinary return path and a terminal CALL
to the original C++ throw implementation. The generic linked_pe closed-body
gate still rejects a terminal CALL; it was not loosened. A new narrow allocator
contract independently decodes all85 bytes, walks every CFG edge, rejects
unreachable bytes/interior branches/indirect calls and verifies the sole
return and final named throw call.

Both complete source and target CRT throw bodies are74 bytes. Canonicalizing
only the record and RaiseException IAT pointers makes every byte agree.
The original32-byte exception-record initializer also agrees completely;
its flags are EXCEPTION_NONCONTINUABLE=1. Source and target PE imports prove
kernel32!RaiseException. This, not just a symbol name, justifies the terminal
call boundary. The full throw and record hashes retain the already-reviewed
linked_noreturn anchors; they receive no new credit.

The allocator's three calls are actual operator new, exception(char const*&)
and CxxThrowException. Independent native ownership rules are required. The
only two data pointers are the actual pushed ThrowInfo and stack-object
bad_alloc vptr. Their instruction/argument roles and source HIGHLOW coverage
are checked, with no nonrelocation-byte changes.

## Complete typed support

ThrowInfo6E3C18/16 has the actual normal destructor401630, no forward compat
and the two-entry CatchableTypeArray6E3C0C/12. The two complete28-byte records
prove bad_alloc and exception with size12, zero adjustment and pdisp=-1.
Copy entries are402680 and689F82 respectively. The84 record bytes compare
completely after typed pointer rebasing; both complete TypeDescriptors,
including their type_info vptr, zero spare and terminated names, are checked.

The three associated bad_alloc lifetime bodies are accepted independently,
with whole code, original RTTI and named exception/delete calls. The existing
strict core canonicalizer handles their normal RET/E9 boundaries unchanged.
All source pointer fields in code and metadata have exact HIGHLOW coverage.

## Reproducibility and checks

- scripts/linked_bad_alloc_origins.py rebuilds the original graph serially.
- config/linked-bad-alloc-origin-anchors.toml pins all five whole native hashes.
- Narrow function-origins.validate_rule_evidence replay passes.
- Both previously accepted logic_error roots and complete EH graph freshly
  pass using this same final original-library image.
- Eleven synthetic tests protect whole typed selection, both CFG paths,
  terminal target, interior branches, unreachable bytes, extra calls,
  pointer/argument roles and exact five-field canonicalization. A regression
  test confirms that the ordinary core still rejects terminal CALL.
- Eleven private real-byte mutations of roots, throw code, noncontinuable
  flags, metadata and type names are all rejected.
- scripts/repo-python scripts/ci.py and git diff --check pass.

Receipts: build/origin-anchors/linked-bad-alloc/proof.json,
logic-error-regression.json and negative-mutations.json.
Private discovery: .analysis/frontier-linked-bad-alloc-20261101/.
Target identity remains the pinned original Japanese1.06a SHA-256; this scope
uses raw PE evidence, not new IDA semantics. No executable is run or committed.
The public Boost constructor112/native111 and payload-dependent tree helpers
remain unaccepted. No native code copying, private export or fake ABI was used.
