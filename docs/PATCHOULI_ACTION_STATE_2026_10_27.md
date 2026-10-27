# Patchouli action-state 0x0050F200

Complete unselected C++ candidate for109 native action labels. All three
sparse regions plus direct300/560 are present. Compilation and a full strict
comparison are available; no implementation or exact ledger credit is added.

## Exact-target observations

The JP1.06a target and Factory native IDA metadata, entry, mapped entry bytes
and inventory were attested at16:40UTC on October27. Direct IDA still lacks
mcp1.26.0/uv. Full decompilation was read as a provisional guide, not copied
into source or trusted over raw instructions.

Native callable50F200..51C6B4 exclusive is54452 bytes, SHA-256:
41430c00c554e7dc169692c56b41fd43f5ef1204700cb092bab6420f327ed944.
All14068 instructions decode;14067 are reachable. The sole unreachable
instruction is seven-byte compiler alignment at50F8A9..50F8B0.
There are133 RETs,807 direct call sites and29 direct targets. All four
indirect jumps resolve: a pre-dispatch difficulty switch plus three sparse
action tables with32/43/32 physical destinations. No indirect exit is unresolved.

Full code/table payload55610 bytes ends51CB3A, SHA-256:
d4d73f175e4f8b37667f04472df8c5db8cbec0ca20414d4107df08a007779043.
Alignment after that endpoint is not included.

## Source decisions and evidence limits

- Uses the accepted virtual slot order and a pointer-only receiver extension,
  not a recovered complete allocation or an instantiated Fighter.
- Buff7A4 reads owner168 and peer170 health, not self health. Skill606 is
  signed-byte arithmetic. Action710 emits its orbit before the hitstop guard.
- All40 native5F9310 call sites test AL; the accepted int callee declaration is
  retained and caller values explicitly narrow. All47 unsigned-conversion
  bias operands are float2^32; candidate count/width agrees.
- Effects carry unsigned direction bytes while coordinate multiplication is
  signed. Ring820's layer carries the low byte of word730, including255 for-1;
  it is not silently replaced by an int-1 argument.
- Trig and square helpers consume actual ST0 results, not decompiler aliases.
  Action599 sign-extends DX at519FE6 before subtracting from-20. The RNG has
  no phantom decompiler arguments.
- Action214's alleged extra v571 virtual argument is absent in raw code.
  Release frame restoration uses the real slot1C and preserves frame730.
- Ground/air fan emissions keep distinct low/high payloads. Air fan seq0 and
  seq1 checks are independent across callbacks. Landing action/select/surface/
  zero-motion order is retained for each family rather than normalized.
- Action603 request853 adds20 in world X, unlike its direction-scaled effect.
  Its request precedes sequence-window/resource calls. Action602 has positive
  sine and negative cosine arguments. Actions797/798 retain different landing
  event order and advance to0 versus700.
- Native561 and798 unordered comparisons were checked directly; unordered
  values skip emission/landing. Skill581 has no defined cap for levels>4,
  unlike580's default4. That domain is still unproved; no fallback is invented.

Every action label has a complete candidate path, but this does not establish
all values, callback aliasing, NaN/overflow behavior or original TU ownership.
The source remains unselected while these semantics and physical ownership
are reviewed. No assembly, target arrays, fake returns, padding locals or
volatile register controls are used.

## First complete comparison

Candidate full54342 versus native55610; first mismatch+8 is frame468 versus460.
Full candidate SHA-256:
f21ffde47c144cf7fac7a4dc1e82d5ca06b63d37bae65bcfea7d767a69a4c783.
The full comparison has52767 unequal/missing/extra positional bytes. This
number is not a semantic-completion percentage.

Candidate sparse groups31/43/32 fold target-distinct210/222; no native group
splits. The diagnostic31 allowance never relaxes target32 or exact acceptance.
Native209/212/221 and585/586 genuinely share their respective target entries.

Per-action reachable-call counts differ at214/409/500/501/502/503, where
source compilation folds virtual or request sites. Arithmetic-operation counts
differ at214/500/501/502/503. These diagnostics identify remaining questions,
not proof that the other actions are equivalent. Global helper-count changes
also reflect common tails and the low-owner merge.

## Focused reproduction

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-patchouli-action-state --compare --json
    scripts/repo-python scripts/audit-patchouli-action-state.py
    scripts/repo-python scripts/map-giant-action-switches.py patchouli-vslot28 --json
    scripts/repo-python scripts/compare-giant-action-switches.py patchouli-vslot28 build/match-units/ExactFirst_PatchouliActionState.obj --json

The full audit replays every COFF relocation with the canonical comparator and
rechecks native CFG closure. Expected mismatch exits must not become acceptance.
Seventeen new literal bindings are supported by native operand addresses and
COFF values; all prior bindings and accepted consumer sources are unchanged.
Artifacts: build/frontier-50f200-20261027/. Only the new unit is compiled.

## Branch and payload refinement

The next focused replay restores separate entry transitions for actions 409,
502 and 503. Native 5157AF/512FE7, 517151/51348B and 5174A1/512FE7
are distinct physical call sites, not one combined condition. Action 214 now
retains the shared turn-and-restore path at 5114CE and the four independently
returning sequence-8 restore paths at 5116A6, 5116C6, 511713 and 511735.
Its reachable virtual-call count is now 27, matching the native diagnostic;
its FCHS count also agrees. Neither count establishes byte equivalence.

Surface rings in actions 540/541/797/798 now spill the complete sine-derived
vertical offset (sine * 75 * 0.25) as a double before querying the surface,
not the unscaled sine result. Native 5180B2..5180D8 establishes this rounding
boundary. The emission argument order captures layer/direction before the
surface query and consumes the cosine afterward. The ground-810 initializer
ordering trial was byte-neutral and was not retained.

Current full candidate: 54466 bytes versus 55610 target bytes, first mismatch
still +8 (frame 0x468 versus 0x460). SHA-256:
87055307b1883af792f0bc7cec13481185554ce128ec4728b05ae7f66844d921.
The strict full comparison reports 52911 unequal/missing/extra positional
bytes. Source remains unselected and no exact credit is added.

The private payload trace resolves all spawn pointers and finds 91 distinct
payload homes in both native and candidate code. Their spacing agrees,
including the one 16-byte step, but all candidate homes are displaced by
8 bytes (first home 44 versus 36). This isolates the residual frame question
to scratch/lifetime allocation rather than a missing payload. Native/candidate
physical virtual-call counts are 172/164 and epilogues 133/126; per-action
reachable-call differences now remain only at 500/501 (three native spawn
sites versus two compiled sites). Arithmetic census also differs at 502/503.
These are diagnostics, not acceptance or a proof of complete semantics.

Latest focused receipts use the surface-ring prefix under the artifact
folder. No compiler flag, dependency ABI, existing relocation or accepted
consumer changed. Broader rebuilding is not warranted by this source edit.
