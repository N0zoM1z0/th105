# Original exception member identities

Four complete original-source bodies,78 bytes, now have positive typed library
ownership:
- 4016E0/14: std::logic_error::what().
- 6A4B70/14: std::runtime_error::what().
- 401780/25: std::out_of_range copy constructor.
- 402570/25: std::length_error copy constructor.

No authored credit is added. Excluded1998/review374; authored exact1431/
443916 bytes, source1635/authored1655/mapped1820/units776 unchanged.

## Identity, including two equal byte strings

All bodies come from the unchanged original seven-TU Boost/VC8 CIL graph,
with its sole genuine public basic_regex constructor export. Class RTTI and
source/map ownership are checked independently of the opcode match.

Both what() bodies are the same14-byte string-buffer selector. Complete
inventory replay finds exactly two native occurrences,4016E0 and6A4B70.
They are NOT globally byte-unique and are not classified by a threshold waiver.
Actual named source class vtables and native RTTI-backed slot+4 distinguish
the functions: logic_error6C05D0 points to4016E0, runtime_error6D5E48 points to
6A4B70. Derived out_of_range6C05DC and length_error6C0888 also inherit4016E0.
Their source slots point to the actual original named what implementation.

Both25-byte copies are whole-canonical inventory-unique after their actual
named base call and own class vptr are resolved. They call the previously
proved logic_error copy4017A0. Each validation freshly reproduces both complete
logic_error base constructors107/113 AND their full EH support before accepting
the derived members. 401780 is therefore positively out_of_range, not the
earlier rejected bad_alloc-shaped guess. The real bad_alloc copy remains402680.

Every opcode and operand byte participates. what() has no relocation or external
call; both RET paths are decoded. Each copy has one E8 field9 and one typed
vptr HIGHLOW field15, plus RET4. The whole source/native CFGs, exact source
relocation coverage, byte hashes and unmodified nonrelocation bytes pass.
No partial body, copied implementation, fake ABI, manual vptr or source wrapper
was introduced. Existing generic origin and whole-function gates are unchanged.

## Evidence and replay

The target is the original Japanese1.06a pinned SHA-256. Raw PE class/slot/code
evidence is used; no new IDA semantics are required.

- scripts/repo-python scripts/linked_exception_members.py
- Narrow function-origins.validate_rule_evidence replay.
- Nine synthetic tests cover typed selection, wrong bad_alloc identity,
  partial/masked rejection, explicit two-body what equality, copy uniqueness,
  actual RTTI/source ownership and wrong-slot rejection.
- Four private actual-code corruption controls all fail.
- scripts/repo-python scripts/ci.py and git diff --check pass.

Contracts: config/linked-exception-members-origin-anchors.toml. Fresh full proof:
build/origin-anchors/linked-exception-members/proof.json.

The ordinary library root112/native111 and payload-dependent tree leads remain
nonexact/unaccepted. These short bodies do not improve the authored numerator.
