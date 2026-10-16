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

The second accepted example is packet-handle manager destruction `413820`,
98/98, in `cross-v106a-network-udp-packet-pool`. Its ordinary COFF form is97
bytes. A genuine ordinary COFF `std::list<unsigned int>` instantiation linked
before the CIL input preserves the shared list helper ABI while LTCG retains
the packet deque's private ESI helper. The source constructor remains nonexact;
its linked EH surface is unsupported. See [the complete evidence](NETWORK_UDP_PACKET_POOL_2026_10_16.md).

## Build and reference identity

`config/tools.lock.toml` pins cl/c1xx/c2/link, both complete header trees and
the actual VC8 `msvcrt.lib`/`msvcprt.lib` import libraries. These libraries
resolve runtime function identities with normal linker-produced import thunks;
their bodies are outside the selected authored comparison. No synthetic
callee implementation, assembly, source byte array or forced return is used.
The compiler still uses the stated MT source profile. The import libraries
serve as link resolvers for external runtime calls, whose original static-game
destinations are separately attested and replayed by name.

Optional `linked_coff_sources` accepts only distinct existing C++ files below
`src/library/`. They compile serially with the same flags except `/GL`, and
link before the source CIL object. The input digest, source/object hashes and
commands are recorded in provenance. They supply real compiler-library
instantiations, without authored credit or a claim about original TU partition.

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
width. One narrow internal-address contract supports native primary vtables:
`link_vtables` fixes source symbol, target allowlist key, source scalar deleting
destructor/target entry and original RTTI type name. The source table and entry
must be uniquely owned by the CIL object, with read-only table/COL data,
matching class RTTI, an executable entry and no extra executable function slot.
The original PE independently attests its exact four-byte allowlist prefix,
zero addend, primary VC8 COL, RTTI spelling and executable candidate entry.

Only `MOV dword ptr [base+disp], imm32` of that source-owned vtable is replayed,
replacing the entire immediate with the attested target address. The source
instruction must have exactly one matching HIGHLOW relocation; all other,
overlapping or duplicate base relocations fail. Pushes, register loads,
indexed stores and hardcoded game-vtable addresses fail. Flat absolute data
bindings cannot impersonate a native vtable. This contract currently supports
plain source classes with a single scalar deleting destructor slot, not
general vtables or source class templates. Other internal image addresses,
floating-literal pointers, EH chunks and indirect jump tables remain unsupported.

The sidecar records source/input digest, CIL object, binding object, map and
image hashes, additional COFF inputs, typed vtable contracts, all
tool/header/library pins and parser versions. Modified or
stale artifacts are rejected before decoding. Both supported Capstone versions
(CI4.0.2 and development5.0.6) pass the rejection tests and independently rebuild
the same281-byte scene and98-byte pool examples. A build and comparison must use the same recorded
parser version. pefile is pinned to2024.8.26.

```bash
python3 scripts/build.py --unit cross-v106a-application-scene-lifecycle --json
python3 scripts/compare-linked-unit.py cross-v106a-application-scene-lifecycle --address 0x00408870 --json
python3 scripts/build.py --unit cross-v106a-network-udp-packet-pool --json
python3 scripts/compare-linked-unit.py cross-v106a-network-udp-packet-pool --address 0x00413820 --json
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
these tests, including typed vptr/RTTI identity, exact HIGHLOW coverage,
rejected vtable binding bypasses and extra COFF artifact tampering. Actual
compiler/linker comparisons remain target-dependent.
