# Canonical comparison after VC8 LTCG

`kind = "linked_candidate"`, profile `vc8-sp1-ltcg-o2`, compiles real C++ with
`/O2 /GL /GR /EHsc /MT` and the unit's explicit GS setting, then performs a
resolved `/DLL /NOENTRY /LTCG /NODEFAULTLIB /OPT:NOICF` link. It supplements the
existing COFF path when link-time code generation owns the observed boundary.
It does not change COFF comparison or authorize partial-function matches.

The first accepted example is scene retirement `408870`,281/281, in
`cross-v106a-application-scene-lifecycle`. Its ordinary COFF candidate is278
bytes; LTCG naturally emits the target's eight-byte-aligned dual-EBP frame.
The same source's scene-handoff producer remains189/148 nonexact.

## Build and reference identity

`config/tools.lock.toml` pins cl/c1xx/c2/link, both complete header trees and
the actual VC8 `msvcrt.lib`/`msvcprt.lib` import libraries. These libraries
resolve runtime function identities with normal linker-produced import thunks;
their bodies are outside the selected authored comparison. No synthetic
callee implementation, assembly, source byte array or forced return is used.
The compiler still uses the stated MT source profile. The import libraries
serve as link resolvers for external runtime calls, whose original static-game
destinations are separately attested and replayed by name.

Unit `link_data_targets` explicitly binds only existing game data and named
Win32 IAT cells. A generated COFF file contains an absolute external symbol
table with **zero sections and no code/data payload**. Every declared field
addend must have its exact ledger bytes in the hash-attested original PE;
IAT names must independently match its import directory. Executable addresses
are forbidden as absolute data bindings. No existing allowlist is widened.

The link must resolve every symbol without `/FORCE`, linker errors or linker
warnings. Compiler/linker environment overrides are cleared. Output is a
function-comparison image referring to the original game's data context;
it is never executed or presented as a standalone reconstructed application.

## Independent boundary and byte checks

`scripts/linked_pe.py` verifies x86 PE32/DLL/NOENTRY identity and source-owned
export/map agreement. The next linker function bounds the available span;
only trailing linker INT3 padding outside a closed RET is removed. Full
instruction decoding and CFG traversal must own every remaining byte, with no
escaped branches, indirect jumps, traps, unaccounted tails or remote chunks.
The target ledger size is used only for the final comparison, never to crop
the linked function. Equal prefixes of differently sized functions cannot pass.

Every external E8 field resolves through a named linker function or a named
MSVCR80/MSVCP80 import thunk and an explicit target-callee mapping. Only its
REL32 displacement is replayed, without masking bytes. Internal CFG encodings
remain untouched. Every absolute memory reference and game-address immediate
must use an attested data binding/addend; reads/writes cannot exceed its attested
width. Internal image addresses, base relocations, floating-literal pointers
and other unsupported surfaces fail closed until a specific typed contract
exists. The current path does not support EH chunks or indirect jump tables.

The sidecar records source/input digest, CIL object, binding object, map and
image hashes, all tool/header/library pins and parser versions. Modified or
stale artifacts are rejected before decoding. Both supported Capstone versions
(CI4.0.2 and development5.0.6) pass the rejection tests and independently rebuild
the same281-byte example. A build and comparison must use the same recorded
parser version. pefile is pinned to2024.8.26.

```bash
python3 scripts/build.py --unit cross-v106a-application-scene-lifecycle --json
python3 scripts/compare-linked-unit.py cross-v106a-application-scene-lifecycle --address 0x00408870 --json
```

The normal `build.py --compare`, existing-artifact comparison and accepted-unit
replay dispatch to this path only for linked candidates. Mixed units still
compare every configured function when requested, while the accepted-function
replay selects only matching rows. The two-function example intentionally fails
its full comparison because the producer remains nonexact. These PE units use
the canonical CLI rather than a COFF-only object viewer.

`tests/test_linked_pe.py` exercises named call replay, data width/identity,
escaped/indirect CFGs, unreachable/truncated tails, unowned internal literals,
runtime DLL/ordinal/name mismatches, ambiguous map aliases, symbol-only binding
objects and modified build artifacts. The mandatory local CI gate includes
these tests; actual compiler/linker comparisons remain target-dependent.
