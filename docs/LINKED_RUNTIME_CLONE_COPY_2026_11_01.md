# Original runtime_error clone copy

Native6A8370 is the complete46-byte copy constructor for
boost::exception_detail::clone_impl<error_info_injector<std::runtime_error>>.
The unchanged original Boost/VC8 CIL graph reproduces every byte after typed
named relocation. SHA-256:
f467d41117e8c58e4d0e8ac830fc40022e49a3d7d5ab74eacc5f245c4a7283dc.

This is one new third-party exclusion, not authored exact progress.
Excluded2003/review369; authored exact1431/443916 bytes,
source1635/authored1655/mapped1820/units776 remain unchanged.

## Complete support, not just a shape

The actual source clone calls its original injector copy. That entire147-byte
body matches native6A5E40, including the conditional shared payload-reference
virtual call and every publication. The runtime_error destructor6A4B30/50
also matches completely, including named delete and exception-destruction
calls. Both were already excluded; neither receives duplicate accounting credit.

The injector's complete handler6BD458/27, cleanup action6BD450/8, FuncInfo
6E3834/36 and unwind map6E382C/8 all match. Its one state transitions to-1
through the fully compared runtime_error destructor. Every scalar and typed
metadata pointer is checked, with exact source HIGHLOW coverage. The source
and target security-cookie initialization also agree.

Eight actual source/native RTTI identities are checked. They include the
runtime_error and boost::exception bases, clone_base, the injector's primary
and offset40 subobjects, and the clone's primary/offset40/offset60 subobjects.
Thus invalid_argument6A95D0 and logic_error6B5060 cannot be accepted merely
because their46-byte shapes resemble this runtime_error specialization.

Each of the three compared bodies is full canonical-inventory unique. The
clone has one E8 field9 and four vptr fields16/22/29/36. The original strict
canonicalizer verifies all instruction and typed data roles, whole closed
boundaries, exact HIGHLOW coverage and unchanged nonrelocation bytes.
No source rewriting, fake ABI, copied instructions or mask is used.

## Explicit nonacceptances

The lower std::runtime_error copy at6A59A0 is independently identified by its
original named source symbol, previously accepted native ownership, actual
runtime_error RTTI and existing source proofs. In THIS full CIL context its
113-byte emission reorders the EH-state store relative to other constructor
operations. The complete current diagnostic remains nonexact, and its hashes,
first difference and unequal-byte count are recorded. It is a named typed
callee, not silently promoted as an exact support body.

The public original basic_regex root112/native111 remains nonexact. The
regex_error injector154 also has an EH-state scheduling difference, so its
neighboring clone46 lead is not included in this stricter support closure.
Current whole-body successes do not authorize changes to those residuals.

## Replay and negative controls

- scripts/repo-python scripts/linked_clone_copy_origins.py
- Narrow function-origins.validate_rule_evidence replay.
- Eight synthetic tests cover one-root selection, no duplicate support credit,
  nominal-class/secondary-offset/source-owner checks and complete EH metadata.
- Seven private actual-code/data mutations, covering clone, injector,
  destructor, handler, cleanup action, FuncInfo and unwind state, all fail.
- scripts/repo-python scripts/ci.py and git diff --check pass.

Contract: config/linked-clone-copy-origin-anchors.toml. Fresh proof:
build/origin-anchors/linked-clone-copy/proof.json.

All source packages, compiler/library pins and the original seven-TU graph
are verified afresh. The only export remains the genuine public constructor.
Raw PE observations use the pinned Japanese1.06a target; no new IDA semantic
dependency, generated executable run or whole-corpus cold rebuild is introduced.
