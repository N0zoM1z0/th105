# Original linked logic_error constructors

The pinned original Japanese v1.06a target is unchanged. Hash-attested raw PE
observations and fresh original-source VC8 compilation are the evidence in this
scope; no new IDA semantics are required.

## Whole-body result

- 401670: original std::logic_error(const std::string&),107 bytes,
  SHA-256 11df2a916174a00a5ce4e984ed5c3f2ed7aca35a695e83ec9fc92fb9f8c05068.
- 4017A0: original std::logic_error(const logic_error&),113 bytes,
  SHA-256 355d02b61e1891ee592bed3645994c314923e9e9e0f050f9168869487c61eb7b.

Both bodies are independently closed and fully canonical, with zero unequal or
masked bytes and unique whole-body hits in the complete candidate inventory.
Both MAP owners are the original instance CIL object. Actual logic_error RTTI
at native6C05D0, not a runtime_error-shaped body, establishes the nominal class.
The source vtable comes from the pinned libcpmt:string.obj archive member.
The cookie comes from libcmt:gs_cookie.obj and agrees with native6F7A88.

The seven unchanged original Boost TUs, original headers and static CRT/SDK
are verified and linked by original_boost_link.py. The only export is the
genuine basic_regex(const char*,flags) public root. That root remains112/native111
and is not accepted. No fabricated caller, private export, ABI declaration,
manual vptr, copied native bytes, assembly or special code-shaping source exists.

## Complete exception handling

For401670, handler6BD958/27, action6BD950/8, FuncInfo6E3FB8/36 and unwind
map6E3FB0/8 all compare completely. For4017A0, corresponding support is
6BD928/27,6BD920/8,6E3F8C/36 and6E3F84/8. This is not a prefix-only EH check.

Both FuncInfo records have magic19930522, one unwind state, no try/catch or IP
map and EH flags1. Each unwind entry transitions to state-1 and invokes the
actual original CIL action, which loads the saved exception base and tail-jumps
to the original exception destructor. Both handlers check the security cookie,
load their exact FuncInfo and tail-jump to CxxFrameHandler3. Every instruction,
metadata scalar and mapped pointer is checked; source HIGHLOW coverage is exact
for roots, handlers, actions, FuncInfo and unwind tables.

All six external callee identities are named original source/archive symbols,
with independently accepted native ownership rules retained: exception normal/
copy constructors and destructor, string assignment4020D0, security check689D25
and frame handler6899E7. No arbitrary native address is supplied as an untyped
matching escape. The existing core canonicalizer and ordinary origin gates
are unchanged.

## Accounting and replay

Only the two constructors move from review to compiler-generated exclusion.
The70 bytes of handler/action code and88 bytes of EH metadata are support only,
not extra candidate or authored credit. Excluded1989/review383; authored
exact1431/443916 bytes, source1635/authored1655/mapped1820/units776 unchanged.

Fresh serial CPU0/nice10 replay:
- scripts/repo-python scripts/linked_logic_error_origins.py
- Narrow rule validation through function-origins.validate_rule_evidence.
- Existing vector back40DBF0/67 and its four actual receiver sites remain exact
  against this fresh original-library graph.
- Twelve synthetic tests cover typed selection, complete metadata, wrong
  runtime_error RTTI, missing callee proofs, source owners, export/cookie
  restrictions and forbidden partial/masked contracts.
- scripts/repo-python scripts/ci.py and git diff --check.

Reproducible contract: config/linked-logic-error-origin-anchors.toml.
Current build/proof: build/origin-anchors/linked-logic-error/proof.json.
Private discovery: .analysis/frontier-linked-logic-error-20261101/prove.py.

Allocator85 and payload-dependent tree erase/Tidy observations remain
unaccepted. Their masked shape alone is not a proof, and existing strict
noreturn boundaries and payload ownership requirements have not been relaxed.
