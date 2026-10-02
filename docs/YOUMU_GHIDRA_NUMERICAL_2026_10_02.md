# Youmu Ghidra cross-check and ordered facing guard, 2026-10-02

## Current result

`Youmu_dispatch_action_state_vslot28 @ 0x00530200` remains **nonexact** over
37,692 target bytes. Action 214's final non-1-facing branch now preserves the
raw target's unordered comparison behavior: it reverses facing/velocity and
selects sequence 5 only when opponent X is **ordered greater** than self X.
Less, equal and unordered positions preserve facing/velocity and select 6.
The preceding source's `opponent_x <= self_x` guard incorrectly sent unordered
positions to the reversal path.

The fresh retained build changes exactly one byte in the complete raw COFF
text: candidate `+0x1C7B`, `7A` (JP) to `74` (JE). Text extent and relocation
records are unchanged. This is an ordinary C++ predicate correction, not an
assembly patch. The target's branch has opposite edge polarity; no claim that
this candidate opcode is byte-identical to the target branch is made.

Whole-function canonical comparison still first differs at **+0xCA**, target
`64`, candidate `D9`. Metadata remains **+0x92B4**, versus target **+0x933C**.
Candidate has 97 physical switch destinations, including 33 low entries.
Fresh strict instruction/edge auditing remains **24/98** diagnostic owners;
no exact ledger receives credit.

## Observed x87 guard

After the sequence-3/4 and facing-not-1 gates, target reads opponent X and
compares it with the already loaded self X:

```text
531F01 MOV EDX,[ESI+170]
531F07 FLD DWORD PTR [EDX+EC]
531F0D FCOMPP
531F0F FNSTSW AX
531F11 TEST AH,41
531F14 JNE 531F3F
531F16 NEG CL             ; ordered-greater reversal path
...
531F31 PUSH 5             ; reversal sequence argument
...
531F3F MOV EAX,[ESI]      ; unchanged direction/velocity path
531F44 PUSH 6
```

`TEST AH,0x41` examines C0 and C3. The JNE arm includes unordered comparisons;
only ordered greater falls through to reversal. The retained condition is
`!(opponent_x > self_x)` before the unchanged path. It does not introduce a
new field, temporary, call or floating operation.

| Opponent X relative to self X | C0/C2/C3 in AH | Target path | Old candidate | Corrected candidate |
| --- | --- | --- | --- | --- |
| less | `01` | preserve; select 6 | same | same |
| equal | `40` | preserve; select 6 | same | same |
| greater | `00` | reverse; select 5 | same | same |
| unordered | `45` | preserve; select 6 | reverse; select 5 | same |

The old candidate also used `TEST AH,0x41`, but its JP reversal edge selected
both greater (`00`, even parity) and unordered (`41`, even parity after the
mask). The corrected JE reversal edge selects only the zero masked result.
The private fact packet asserts the actual target instructions, both sequence
arguments, complete root hash, one-byte COFF delta, equal relocation records
and all four comparison states. Report:
`build/youmu-facing-contract-20261002.json`.

**Unknown:** reachability of NaN positions during normal gameplay and original
source spelling. The correction preserves target behavior for all four
comparison classes; it does not assert that a NaN state occurs in a match.
The other three facing branches in this action retain their existing ordered
less/greater predicates and were checked against their raw AH tests.

## Independent Ghidra attestation

A direct Ghidra 12.1 headless import independently checks the local PE identity,
import metadata, image base, x86 language, Windows compiler specification,
external entry point and all mapped virtual `.text` bytes before disassembly
or decompilation. No IDA analysis, factory adapter or target patch is used.

- Executable SHA-256:
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
- Entry: `0x0068B9D2`; first 32 bytes:
  `e8ca9f0000e916feffffcccccccc8d42ff5bc38da424000000008d64240033c0`.
- Complete virtual `.text` SHA-256:
  `f5cb09ff0a54362356d8c4cce853cbcb14552499cce12cf7390d0868db9ebe97`.
- Root body SHA-256:
  `19f2d4fba4f6ea626b69a28f4717d0fcfae06ea97e95ddb24e656e0ea518ed74`.
- Explicit function body: `0x530200..0x53953B`, 37,692 bytes.

All three primary destination tables and the action-720 auxiliary table are
checked and their destinations disassembled within the reviewed callable span.
Normal direct helper call views mirror the current source/unit bindings;
28 helper signatures, calling conventions and purge sizes are read back.
The initial incomplete call-view output is discarded. The corrected run uses
spawn helper `0x465190`, void texture publication and the sequence-finalization
helper. Root output reads back `void __thiscall ... (void *this)`.
These metadata views do not establish new original declarations or callee
ownership. The custom x87 conversion helper and indirect virtual signatures
remain limitations of this decompilation.

Private corrected output:
`.analysis/youmu-tail-placement-20261002/ghidra-typed-hypothesis.c`;
attestation/readback log: `build/youmu-ghidra-typed-20261002.log`.
Imports run one at a time in transient projects below `build/` with
`-deleteProject`; no analysis database is committed.

## Decompiler limits and numerical order

Ghidra warns that it cannot fully track the stack spacebase, and removes
several unsigned-remainder conversion arms as unreachable. Its output remains
a hypothesis, not proof of complete source or byte closure. Raw traversal
still reaches all **9,912 instructions / 37,692 bytes**, with no unresolved
indirect jumps; no removed decompiler block is removed from source merely
because of that simplification.

For action 214's effect Y argument, the decompiler displays a reassociated
sum equivalent over real arithmetic to `100 + Y + sin*100`. Actual x87 order
at `0x531D49..0x531D59` is:

1. Load double 100 while the sine result remains on the x87 stack.
2. Multiply that sine result by 100 with `FMUL ST(1),ST(0)`.
3. Load actor Y, then `FADDP ST(2)` adds Y to the product.
4. `FADDP ST(1)` adds the preserved 100.
5. Store/reload the final single-precision effect argument.

Thus target association is **`(sin*100 + Y) + 100`**, already preserved by
source. No reassociation is retained. The printed cast of a returned cosine
or sine value to float likewise does not prove an extra pre-product target
rounding: raw code multiplies the live return before its field store.

## Closed layout probes

On this checkpoint's baseline, sharing the two real horizontal-step variables
in actions 0/2 and spelling their final clamp as ordinary nested conditions
are both byte-neutral over the complete canonical window. Neither changes
the +0x20 candidate scratch slot to target +0x10 or recovers the frame-advance
tail. No probe is retained.

Putting action 210 lexically before 209 merely swaps their physical entry
order, retaining metadata +0x92B4 and 24/98 diagnostic owners. It does not
reproduce target ownership of the shared tail and is not retained. This rules
out that particular predecessor-order remedy, not all TU/context hypotheses.

## Reproduction and remaining work

```bash
taskset -c 0 python3 scripts/build.py \
  --unit gpt-web-youmu-vslot28-full-root --compare --json \
  > build/youmu-ordered-facing-20261002.json
python3 scripts/audit-giant-action-owners.py youmu-vslot28 \
  build/match-units/GptWeb_YoumuActionState.obj \
  --unit gpt-web-youmu-vslot28-full-root --json \
  > build/youmu-ordered-facing-owners-20261002.json
```

Formal comparison exits 1 for an ordinary mismatch, without a relocation
failure. Owner audit succeeds with the diagnostic count above. Candidate
37,692-byte comparison-window SHA-256 is
`510a89eaf4be97fe6c8e1e2faf2b3de4c53b88402e9e8fa0f47c83dc778c8373`;
it includes metadata after +0x92B4 and is not a candidate body hash. Source file
SHA-256 is `587ead3f9940d8d2f19227801fd4d6ce0cfd7ca4a0bcffae2a63b9803369f1eb`.

Shared-tail placement, real temporary lifetimes, other ordered numerical
contracts and original TU/compiler context remain unresolved. The Ghidra
warning prevents treating its flattened source as full semantic closure.
No assembly or LTCG requirement is inferred. No shared header, compiler
profile, relocation mapping or object partition changes. Only this unit is
rebuilt; aggregate exact totals remain unchanged ledger totals.
