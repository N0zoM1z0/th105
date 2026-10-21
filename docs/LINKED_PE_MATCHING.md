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

The third accepted example is shared handle-token release `405200`,167/167,
in `cross-v106a-network-winsock-send-client`. Its genuine private EAX entry is
generated from an ordinary member definition and its actual sender caller.
The real senders and native thread callback are exported; a typed caller contract independently attests
the private entry. See [the full shared-release evidence](HANDLE_MANAGER_RELEASE_2026_10_16.md).

`CDesignBase::render @ 40BC80` is also complete135/135. The same native
member-iterator source is124 bytes under ordinary COFF; GL/LTCG naturally
retains the target eight-byte frame and loop alignment. Its explicit empty
`link_data_targets = []` is accepted because no absolute game data is used;
missing declarations and unbound absolute references still fail. See
[the complete render evidence](DESIGN_BASE_RENDER_2026_10_21.md).

Texture dimension query `404E60` is complete148/148 with the genuine handle
lookup definition visible and its ordinary thiscall export preserved. The
ordinary COFF query is147 bytes. Already attested Kernel32 IAT data cells
resolve the real VC8 GS-report helper; no static-lifecycle guard changes or
ABS code providers are used. The lookup's independent probe remains nonexact.
See [the source and complete comparison](TEXTURE_SIZE_QUERY_2026_10_22.md).

## Build and reference identity

`CDesignBase::virtual_cleanup @40BB40` extends the closed-CFG contract to one
typed vector range-error exit,310/310 exact. `error_tails` must name the actual
unexported CIL `_Xran` helper and exact target E9 site. Independent pinned
target error/throw/record anchors, source CRT throw thunk/IAT, native message,
actual ThrowInfo argument and exception layouts establish the terminating
error role. Both complete caller CFGs then close and the named E9 REL32 field
is replayed normally. This authorizes no general escaped branch, helper/EH
exactness, origin exclusion or literal allowance.

Optional `preserve_public_members` keeps genuine normal public thiscall member
ABIs exported without registering duplicate target functions. Unique source
CIL ownership, actual export identity and native implementations are required;
these roots add no match credit and cannot replace the comparison root.
See [cleanup acceptance and rejection tests](DESIGN_BASE_CLEANUP_EXACT_2026_10_21.md).

`config/tools.lock.toml` pins cl/c1xx/c2/link, both complete header trees and
the actual VC8 `msvcrt.lib`/`msvcprt.lib` and Platform SDK `WS2_32.Lib` import libraries. The runtime libraries
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

Optional `link_import_targets = ["_sendto@24=0x006898CC"]` links the actual
pinned SDK archive. This narrow registry supports only the independently
hashed i386 code/ordinal20 short import member, with exact `_sendto@24` symbol
and WS2_32 DLL identity. The target must be an excluded, executable six-byte
candidate containing `FF25` to the independently attested ordinal20 IAT slot;
its literal bytes and zero addend are checked. Comparison requires the source
PE's actual ordinal import, matching linker symbol/library ownership and the
function's explicit callee mapping to agree with that contract. pefile's
convenience name for an ordinal import never replaces the ordinal identity.
Named or different-ordinal SDK calls, arbitrary libraries and executable
absolute bindings remain rejected. The source calls the ordinary stdcall API;
the real library/linker supplies its thunk. See [the send-worker evidence](NETWORK_UDP_SEND_WORKER_2026_10_16.md).

The link must resolve every symbol without `/FORCE`, linker errors or linker
warnings. Compiler/linker environment overrides are cleared. Output is a
function-comparison image referring to the original game's data context;
it is never executed or presented as a standalone reconstructed application.

## Independent boundary and byte checks

`scripts/linked_pe.py` verifies x86 PE32/DLL/NOENTRY identity and source-owned
export/map agreement. A function may instead declare
`private_from = { caller = "0x00416990", site = "0x00416B01" }` when its real
caller is another configured exported function in the same source TU. The
private symbol must have exactly one CIL-owned map entry, without any function
alias or export, including ordinal-only export aliases. Private chains,
self-witnesses and simultaneous export declarations are rejected.

Its caller must have reviewed implemented/matching source in that TU. Source
and target caller bodies must both close through complete CFGs. Each must have
exactly one ordinary E8 call to the respective private entry, and the target
instruction must be the declared site. The caller's named callee mapping must
agree. Internal base relocations in this first private-caller contract are
unsupported. Caller source/target hashes and actual E8 sites join the result.
The caller is an ownership witness, not an exact claim; selecting only the
private function still repeats every caller check. No synthetic caller,
resolver code or forced register declaration is added.

The next linker function bounds each available span;
only trailing linker INT3 padding outside a closed RET is removed. Full
instruction decoding and CFG traversal must own every remaining byte, with no
escaped branches, indirect jumps, traps, unaccounted tails or remote chunks.
The target ledger size is used only for the final comparison, never to crop
the linked function. Equal prefixes of differently sized functions cannot pass.

Every external E8 field resolves through a named linker function, a named
MSVCR80/MSVCP80 import thunk, or the typed SDK contract above, with an explicit target-callee mapping. Only its
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

A configured scalar destructor may set `vtable_entry` to its exact
`link_vtables` symbol. Its native table then witnesses the entry without
exporting that compiler wrapper. Source/target RTTI and the actual source entry
pointer are revalidated, and only the same-class scalar/vector compiler alias
is allowed. This selector cannot combine with export/private/global entry
witnesses or act as an exported caller. The unit retains a real source export
or CRT lifecycle root. Packet wrapper4138B0 remains30/30 through this path,
while normal destruction413820 stays98/98. Numbered linker warnings and errors
now fail even with exit status zero; no LNK4102/LNK4210 exception is granted.
See [the guard correction and focused replay](LINKED_WARNING_GUARD_2026_10_21.md).

The sidecar records source/input digest, CIL object, binding object, map and
image hashes, additional COFF inputs, typed vtable and SDK import contracts, all
tool/header/library pins and parser versions. Modified or
stale artifacts are rejected before decoding. Both supported Capstone versions
(CI4.0.2 and development5.0.6) pass the rejection tests and independently rebuild
the same281-byte scene,98-byte pool and167-byte private release examples. A
build and comparison must use the same recorded parser version. pefile is
pinned to2024.8.26.

```bash
python3 scripts/build.py --unit cross-v106a-application-scene-lifecycle --json
python3 scripts/compare-linked-unit.py cross-v106a-application-scene-lifecycle --address 0x00408870 --json
python3 scripts/build.py --unit cross-v106a-network-udp-packet-pool --json
python3 scripts/compare-linked-unit.py cross-v106a-network-udp-packet-pool --address 0x00413820 --json
python3 scripts/build.py --unit cross-v106a-network-winsock-send-client --json
python3 scripts/compare-linked-unit.py cross-v106a-network-winsock-send-client --address 0x00405200 --json
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
rejected vtable binding bypasses and extra COFF artifact tampering. Private
caller tests also reject missing/ambiguous/unreachable E8 edges, wrong source
ownership, unreviewed parents, exported aliases and internal relocations.
SDK tests independently reject archive/member ABI changes, wrong thunk/IAT,
ordinal/name confusion, unpinned symbols, map owners and nonexcluded targets.
Actual compiler/linker comparisons remain target-dependent.
