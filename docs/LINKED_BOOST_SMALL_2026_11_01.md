# Complete original Boost small members

The unchanged original seven-TU Boost/VC8 CIL graph yields four whole canonical
bodies,47 bytes:
- 6A08B0/13: boost::detail::sp_counted_base::destroy.
- 6A4D30/11: boost::exception_detail::clone_base copy constructor.
- 6B55D0/12: boost::re_detail::free_module.
- 6B55E0/11: HINSTANCE custom-deleter sp_counted_impl_pd::dispose.

All four are full-inventory unique after typed canonical rebasing, with zero
unequal or masked bytes. Only these four review rows become third-party Boost
exclusions. Excluded2002/review370; authored exact1431/443916 bytes,
source1635/authored1655/mapped1820/units776 remain unchanged.

## Positive source and ownership

Every body is a unique original-source MAP symbol with its actual original TU
owner. The original package/header/compiler/library pins and sole genuine public
basic_regex constructor export are checked by the existing build recipe.
No game implementation or synthetic caller is supplied.

The original base type sp_counted_base matches native primary RTTI6D5DE0;
its destroy slot+8 points to6A08B0. The actual HINSTANCE/function-pointer-deleter
specialization matches native RTTI6D690C, with dispose slot+4 at6B55E0 and
inherited destroy slot+8 at6A08B0. Both original source slots resolve to those
same named source functions. This establishes the role of the two indirect-call
bodies rather than inferring it from their short instruction patterns.

clone_base has actual primary RTTI6D5DD0. Its implicit copy emits the complete
11-byte constructor, including the only vptr field at+4 and RET4.
The original free_module is a complete12-byte cdecl wrapper around the actual
source/native kernel32!FreeLibrary import. Only its IAT field at+7 is rebased.
Both pointer fields have exact source HIGHLOW coverage. destroy/dispose have
no address relocations at all. All four complete CFGs are decoded and all
nonrelocation bytes remain untouched.

No generic minimum-byte/coverage policy is lowered. This is a separate whole
original-source, typed-RTTI/import contract, not masked-short-body credit.
The shared_ptr allocator, other clone specializations and unrelated identical
instruction shapes remain independent evidence obligations.

## Reproduction and checks

- scripts/repo-python scripts/linked_boost_small_origins.py
- Narrow function-origins.validate_rule_evidence replay.
- Prior four exception-copy/what members freshly pass using this same image.
- Seven synthetic tests cover typed selection, whole extents, target/digests,
  original class identity and wrong/ambiguous source ownership.
- Four private actual-code mutations are all rejected.
- scripts/repo-python scripts/ci.py and git diff --check pass.

Contract: config/linked-boost-small-origin-anchors.toml.
Fresh proof: build/origin-anchors/linked-boost-small/proof.json.
Private source discovery: .analysis/frontier-linked-boost-small-20261101/.
Raw PE observations are against the pinned Japanese1.06a target; no new IDA
semantics or generated executable execution is involved.

The broader small-source discovery is not acceptance. Its bad_alloc-shaped
68EF88 is actually bad_exception and is not assigned the wrong type. Runtime-
error-shaped clone46 leads at6A95D0/6B5060 are actually invalid_argument/
logic_error specializations and remain unaccepted. The truthful runtime_error
6A8370 and regex_error6B5350 leads need their own whole base/callee/secondary-RTTI
proofs. Payload-dependent tree Tidy candidates remain unaccepted.

## Later typed CRT bad_exception proof

The initially rejected wrong-class68EF88 lead is now resolved through the
actual original libcmt:frame.obj bad_exception, not by relabeling bad_alloc.
Whole11/34/24 methods and complete primary/base RTTI graph pass; see
LINKED_BAD_EXCEPTION_2026_11_01.md. This is separate CRT ownership, no Boost
root/callee or authored credit.

## 2026-11-01 original clone_base destructor

The actual original seven-TU graph also emits clone_base::~clone_base at
6A0880/7, with unique i original-0.obj ownership. Its complete MOV-vptr/RET
body matches after the sole actual clone_base vtable DIR32 field+2 is replayed.
The source/native primary RTTI identity is the same real clone_base already
proved for copy11; no other class is substituted. All seven bytes, closed CFG,
source HIGHLOW inventory and whole-candidate uniqueness pass. No caller or
provider byte is inferred from this short body.

The existing typed small-body contract now contains five roots/54 bytes. Its
four previous members are freshly rebuilt and replayed unchanged. Two added
scope/type tests and all seven actual body-byte mutation controls pass.
No generic threshold, source, flags, exports or unit changes are made.
Evidence: build/origin-anchors/linked-boost-small/proof.json and
build/frontier-clone-base-dtor-20261101/mutations.json. Only7 new library bytes;
excluded2019/review353, all authored/source/unit totals unchanged.
