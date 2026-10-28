# Aya Fighter action state 00602250

Complete manual source now covers all114 actions and the default. The selected
whole canonical replay remains **nonexact**. Source presence, matching call
counts and switch topology do not earn exact-byte credit.

## Canonical target and ownership

Japanese1.06a SHA256:
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The existing authored primary-vtable anchor is rechecked directly: primary
vtable6C62D4, slot28 cell6C62FC ->602250, COL6DB828, TD6E8E30 `.?AVAya@@`.
The adjacent CPU policy6126E0 and all accepted shared dependencies are unchanged.

Callable [602250,612291) is65601 bytes, SHA256
`04c7620574e00d6f05bb615a095188ee2c60e94cc9d94dbad2eed56b92ab7fd5`.
16858 instructions decode;16856 instructions/65593 bytes are reachable.
Only [6100E8,6100F0) is alignment, an eight-byte JMP/LEA sequence.
There are146 RET0s,199 virtual sites and1011 direct sites to33 targets.
Native ESP alignment is8 and frame allocation is3E8.

Complete payload [602250,6126E0) is66704 bytes, SHA256
`42401b4701e475fbaab7d19a542aec6edbe503082a2a0dc2a2e22407e71903a3`.
Three-byte LEA alignment precedes the metadata. Seven table dimensions are
33/27/48/4/4/4/8; the three remaps contain227/118/239 bytes. Their domains are
0..226,301..418 and502..740, with the final direct table791..798. Sparse maps
cover111 action labels; direct300/500/770 complete the114. All table targets,
remap ranges and intervening alignment are covered by the raw audit.

## Analysis and source evidence

Local IDA preflight lacked its pinned MCP runtime, so that session was not used.
The separately target-attested Factory-native session worked for metadata,
entry, mapped bytes and inventory, but Aya decompilation failed. Work continued
through Factory repository Bash with the already installed Ghidra12.1 toolchain.
A fresh isolated project checked executable SHA, imported SHA, image base,
x86 language, Windows compiler specification, entry68B9D2, every mapped virtual
.text byte and the complete bounded body before analysis. The old Iku project
was not changed. No target bytes or IDA database metadata were changed.

The full Ghidra navigation export completed. Thirty-two existing ordinary
callee contracts and actual sequence virtual slots were separately applied to
that isolated analysis and read back; the compiler conversion intrinsic was not
given a fabricated ABI. Ghidra still warns about17 removed blocks and stack
spacebase tracking. Raw CFG reaches those blocks; decompiler output is therefore
not authority for deleting them or copying its source mechanically. Unsigned RNG
conversions, omitted ST0 consumers, literal widths and unordered predicates were
reconstructed against instructions. First compilation waited for the full root.

The pointer-only receiver inherits the established AnimationSequenceObjectView.
All scalar offsets, callback-sensitive reloads and actual packet arrays remain
explicit. Motion uses this+4;740's periodic wave uses owner168. Crossed-surface
and on-surface callers inspect AL while retaining the established int-returning
callee contracts. Direction arithmetic is signed-byte; effect/spawn carriers
retain the observed unsigned-byte value. No allocation extent is claimed.

Several raw corrections are material: jump6..8 has no144 time gate;307/418's
minimum-speed path writes74C rather than73C;502's Y offset is76, not100;
508's fan advances +20 with +30 origin, unlike506's negative fan.565/567 capture
Y as QWORD before surface(), and their flag includes unordered comparisons.
662 also uses a QWORD Y capture.740 keeps QWORD coordinate captures across RNG
and the native addition associations. Distinct action/sequence/height/zero-motion
landing orders are retained rather than collapsed into one generic policy.

529 retains an uninitialized packet when its selector is outside the observed
-2..2 branches.530/532 initialize only the first two words of a three-word
request. These are bounded source hypotheses, not proof of the original type,
initialization domain or exception behavior; no fallback values are invented.

## Whole replay and controls

Unit: `exact-first-aya-action-state`.
Command: `scripts/repo-python scripts/build.py --unit exact-first-aya-action-state --compare --json`.
Audit: `scripts/repo-python scripts/audit-aya-action-state.py`.

The first complete candidate was65752 bytes. Explicit branch-owned virtual calls
for10/200 and separate entry guards for414/416 restore their native per-action
virtual-site counts.540's separated guards remain physically merged; an actual
shared ground continuation for528 changes layout but does not close its residual.
No further label spelling or register coercion is justified by these controls.
The raw508 fan correction is retained independently of its comparison result.

Selected full candidate is65784 bytes, SHA256
`4cf50d1d4991f3505b861e23b3081f2e0bc8a1e948b102e62c57239930a075d6`.
First difference+8 /602258 is frame3F0 versus3E8.63316 unmasked positions differ,
including missing/extra bytes. Candidate147 RETs,195 virtual sites and1003 direct
sites reflect different physical sharing. Low table31 versus native33 merges
additional owners; the other six dimensions agree. Remap lengths all agree;
only the118/239-byte mid/high remaps are byte-identical.

A private complete-CFG traversal from each action entry finds identical direct
callee counts for all114 actions. Virtual counts differ only528 (7/8) and540
(8/7). Floating-operation counts differ only214,510 and740; for510, raw opposite
layer paths duplicate the X-coordinate addition while the candidate shares it.
These are omission diagnostics, not opcode, operand, semantic or byte acceptance.
Remaining frame bytes, control sharing, scalar lifetimes and FP scheduling remain
unresolved. The original TU/LTCG context and complete nominal layout are unknown.

Receipts: build/frontier-602250-20261028/{formal-build,full-audit,target-audit}.json.
Private source preparation and diagnostics: .analysis/frontier-602250-20261028/.
The formal public build reproduces the selected private payload exactly.145
isolated aliases are appended; existing aliases, shared ABI, compiler profile and
accepted sources remain unchanged. Only the affected unit is built. matches.csv
is unchanged; no new whole-corpus replay or exact percentage is claimed.
