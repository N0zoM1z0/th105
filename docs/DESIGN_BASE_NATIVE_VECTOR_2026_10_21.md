# CDesignBase native vector and binary loader

Target: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This checkpoint corrects a member-ownership hypothesis and positively identifies
the complete `CDesignBase_load @ 0040B000`. It adds no source-present function
or exact match.

## Observed target facts

The complete `0040B000..0040BA69` callable contains 2666 bytes and 860 decoded
instructions, span SHA256
`756f150004243d88a9dd987bcf9aec662b7a4c7caf808a789a72749adf2b16e2`.
All 860 instructions are reachable when the guarded switch is resolved:
`CMP EAX,6 @ 40B427`, dispatch `40B430`, seven DWORDs at `40BA6C`, and four
distinct destinations `40B437/40B5B8/40B66D/40B7ED`. The single normal RET4
ends at `40BA69`. The `MOV EDI,EDI` alignment at `40BA6A`, switch table through
`40BA87`, and following CC bytes are excluded from the callable extent.

RTTI name `.?AVCDesignBase@@`, COL `6D7594`, and vtable `6C08AC` identify the
owner; slot +10 at `6C08BC` points to `40B000`. The previously accepted
`initialize_profile_ui @ 43FCA0` calls it at `43FD98/43FDA7/43FDEB/43FE55`.
A fresh build of `cross-v106a-profile-ui-init` preserves all 666 exact bytes.
ECX is the design owner and the path is the one stack argument. The caller
ignores the result; these observations do not establish a C++ return type.

The loader uses `FileReaderOwner::open @ 40CF40`, split-path processing,
virtual reads, texture resources, and four distinct design factory arms.
Its number factory at `40B7ED` allocates E4 bytes and publishes CDesignNumber
vptr `6D6AC0`, with CNumber member +18 and tile member +40. The normal loop
reaches `CALL 40C6D0 @ 40B9DC`; this resolves the previously unverified raw
E8 candidate in the scene-lifecycle audit. It does not settle the generic
helper's source boundary or provide new compiler/library credit.

## Corrected ownership and focused exact controls

The loader passes `this+4` to native vector operations. The pinned VC8
`<vector>` places `_Alval` before its three pointer members. Consequently a
native `std::vector<unsigned int>` occupies 10h bytes at +4, with its pointers
at owner +8/+C/+10. The old eight-byte primary interface and homemade
three-pointer owner produced the same lifetime instructions but assigned
the first vector word to an unsupported base-class field.

`DesignBaseLifetime.hpp` now uses the four-byte primary interface and the
native vector. The list remains +14, map +20, and checked iterator +2C;
compile-time size/offset checks preserve the full 34h layout. This correction
retains the complete canonical lifetime results:

| Function | Bytes | Canonical SHA256 |
| --- | ---: | --- |
| ctor `4217F0` | 153 | `d4aab242f4bb7480f5dd4be64e5c9e758983cb484a034497af5e659c4eda8b54` |
| normal dtor `421890` | 154 | `6e049b6b301522e2ab32a3c72e6ebdc6c6c7047bf0c26759e196aeac01ff31c9` |
| scalar deleting dtor `421930` | 30 | `544eb06ac72099d36c8f16ad444a8df5f16f1d38e88288605aab53cf792c0f13` |

The semantic include closure selects 13 existing units. All 43 affected
accepted functions were rebuilt serially and remain completely exact.
`build/design-loader-20261021/header-consumers.json` lists the closure;
`affected-replays.json` records every comparison. Private native-container
controls agree with the public lifetime replay. No flags, relocation bindings,
or accepted extents changed. All work ran on CPU0 at nice10.

## Evidence, records and remaining work

Raw instruction/edge/vtable facts are in
`build/design-loader-20261021/target-facts.json` and `target.asm`.
IDA preflight rejects the attached wrong-target session. A single direct
Ghidra process independently attested the canonical imported hash, x86 Windows
specification, image base/entry, all four file-backed PE sections, and the
entire callable span. The corrected read-only run temporarily created the
bounded entry, verified its extent, decompiled it, explicitly removed the new
entry, and read back its absence. All nine primary database file hashes are
unchanged. Earlier failed attempts and their receipts remain private.

The decompilation is a hypothesis: missing private-callee prototypes cause
stack drift and poor inferred types. It is not a source implementation.
Private scripts and receipts are under `.analysis/design-loader-20261021/`
and `build/design-loader-20261021/`. The 197 prior origin-rule selections are
unchanged and disjoint from the newly identified loader; only the new rule's
body, caller and table witnesses needed evidence replay.

`functions.csv`, `reccmp-functions.csv`, and the positive authored origin rule
now record the loader identity. `implemented.csv` and `matches.csv` are
unchanged. The loader still needs a full natural C++ implementation, a resolved
return contract, and evidence for original helper visibility/TU context.
Existing lifetime-header `int load` remains unqualified by this audit. Future
texture work must recover real compiler-private helper ownership; the inherited
naked assembly in `TitleResourceLoad.cpp` is not a permitted source model for
this reconstruction.
