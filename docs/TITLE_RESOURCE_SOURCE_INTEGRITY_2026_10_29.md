# Title resource source-integrity correction

The tracked Title texture load404C90 and release404D70 implementations were
naked inline-assembly transcriptions. Their99/115-byte equality did not meet
the repository's requirement for genuine source reconstruction. Both exact
rows are withdrawn. Authored ownership and source presence remain, now backed
by ordinary C++ rather than copied instruction streams.

Canonical Japanese1.06a SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Raw CFG traversal closes all99 and115 bytes. Native body hashes:
-404C90: `e1e7a44481f2af11e1217f3b250c9170f0855b87c9063a8b643f510ed5fe7917`.
-404D70: `84ceca2dfdde55fc4ff7e0e10ee9071de7ba4ac9aa34367baf0f090e1ba76e03`.
Exact CSelectScenario_apply_scenario4245D0 calls them at424641/4245F3,
independently anchoring game ownership after withdrawal of their own matches.

## Natural source

`TitleResourceLoad.cpp` initializes an actual token local, acquires a writable
resource cell, zeroes it and invokes the bitmap loader with observed height/path
ECX/EDX and cell/width stack arguments. Failure recycles the token and writes0
to the caller's result; success publishes the token. It returns that result
pointer. The manager acquire/release boundaries use ordinary member declarations,
not invented EDI/EAX source ABIs.

`TitleResourceRelease.cpp` preserves the zero-handle guard, eight cache entries,
real D3DDevice9 SetTexture(stage,0), checked manager lookup, IUnknown::Release,
cell clearing and token recycle. It uses established typed COM interfaces rather
than hand-written vtable offsets. The existing packet-manager release method
is used only as a pointer view of the independently proven shared generation,
free-list and lock prefix; it does not access a packet payload or send data.
No shared header or public caller interface changed.

Complete ordinary comparisons are93/native99 at+0 and119/native115 at+8,
canonical candidate hashes
`347763a55851d06f4142a5c2d4318db4dab4d088bd2590e2ef0e818ddbd15297` and
`e6db96163eb0ce3e203fc03c3268e5c3fcc74ae72b104768f7237f715cf9650d`.
A real same-CIL release/lookup/sender context also emits119/115, first+8.
A counter-first do/while control remains119; a positive-guard scope emits113,
still first+8. These unselected controls do not justify forcing prologue saves,
loop alignment or helper registers. The selected natural source remains nonexact.

## Preserve the independently genuine helper

405200's167-byte acceptance is separate and remains valid. Its actual ordinary
C++ source is NetworkUdpPacketHandleManager64::release in
`src/network/NetworkWinsockSendClient.cpp`, with the genuine sender witness and
standard unsigned-list COFF instantiation. A fresh focused build and private-entry
comparison reproduce167/167. The old Title assembly was not its source provider
or mandatory ownership witness.

The obsolete, unselected `src/assets/ResourceHandleManagerRelease.cpp` naked
assembly file contained old fixed-image IAT bytes and is removed from active
source. No selected unit referenced that file. The new Title bodies no longer
reference its fake register-specific externals. Historical source remains in
Git and private snapshots. A bounded tracked-src scan now finds no __asm,
__emit, naked declarations or explicitly aligned scratch constructs.

Accounting withdraws two exact functions and214 bytes, with no new library
exclusion or comparison-boundary change. Other callers' byte receipts remain
independent; complete source/ABI/layout recovery is required before restoration.
This correction supersedes historical99/115-byte acceptance claims.

Focused scope: `build/frontier-title-source-integrity-20261029/` contains
`load-build.json`, `release-build.json`, `boundary.json`, `withdrawn-matches.csv`,
`joint-compare.json`, `genuine-helper-build.json`, `genuine-helper-compare.json`
and `ci.log`. Private source/control snapshots are in the corresponding
`.analysis/` scope. No whole-corpus cold rebuild or runtime matrix was added.

A2026-10-30 control adds the actual ProfileMenuBaseData cleanup caller to the
real sender/resource-lookup/title-release CIL graph. Cleanup431390 remains
28/native29 at+3, with the same hoisted handle load. Callee visibility alone
does not close the memory-compare/reload difference. Source stays unchanged;
no volatile reload or exact credit is added. Evidence:
build/frontier-profile-cleanup-cil-20261030/compare.json.
