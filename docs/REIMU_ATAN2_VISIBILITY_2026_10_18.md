# Reimu: real atan2 linker visibility

This bounded experiment concerns `Reimu_dispatch_action_state_vslot28`
at `478FA0` and its real `atan2_degrees` callee at `406540`. The target is
the original Japanese 1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The IDA preflight still rejects the different attached executable. Target
observations use the hash-attested PE; no database or target bytes changed.

## Question and controlled input

After the [argument-lifetime change](REIMU_AIM_ARGUMENT_LIFETIMES_2026_10_18.md),
nine complete 73-byte preparations equal raw target bytes. The first aiming
preparations for 400/401/404 differ in two register encodings: candidate ECX
versus target EDX. The next question was whether exposing the actual math
implementation to the root's LTCG optimizer explains this difference.

The probe uses the existing genuine root/provider link, with its real CRT and
SDK libraries. Only `src/engine/AngleAtan2.cpp` gains `/GL` in a private build;
its source, strict-FP recipe, includes and other flags remain unchanged. The
real `/GL` root and all other providers retain their verified inputs. There
are no substitute helpers, altered declarations or register constraints.

Before this experiment, the ordinary math unit was freshly rebuilt and
compared: **63/63 exact**, target and canonical object SHA-256
`c6e3d63c7180373f7cdda0c68622c1fedbdcb700e55db0571986eb47834946b0`.
The base producer audit also revalidated the complete selected root payload:
`826889ee7ec055e44def5cc1602de2fae75f58403e2332194ec3b20cd55dc0d3`.
All 51 original object/library inputs and four base receipt/object/image/MAP
files remained hash-identical across the private link.

## Observed result

| Observation | Private real-math `/GL` link |
| --- | --- |
| Root entry / frame | `10001000` / `570h`, unchanged |
| First root difference from target | `+17`, XOR EBX before target's PUSH EDI |
| Direct root calls / calls to math wrapper | 1178 / 36 |
| Lowest of 11 indexed switch tables | `10014E94`, offset 81556 |
| Next root MAP owner | Math wrapper at `100153F0`, envelope 82928 bytes |
| Actual math body through RET | 65 bytes, versus target 63 |
| Math tail to next MAP owner | 15 INT3 bytes, next owner aligned to 16 |

The math wrapper remains a separate stack-argument function. Its first
instruction is now `PUSH ECX`, followed by `FLD [ESP+0Ch]`; the target starts
with `FLD [ESP+8]`. The private wrapper ends in `POP ECX; RET`. Corresponding
ESP displacements change too. This is an observed instruction pair, not proof
that ECX preservation caused the allocator's choice or that the target math
could never have been built with `/GL` in another original context.

The root still has all 36 calls to this wrapper. Its final decoded jump ends
at `10014E91`, followed by a three-byte LEA before the lowest table. These are
layout observations, **not a qualified callable boundary**. The private image
was never executed or admitted to the root's native oracle. No relocation or
boundary guard was loosened. In particular, the normal producer auditor's
rejection of linker-visible provider IR without separate ABI proof remains.

This tested pair does not recover the target math body or root entry. The
ordinary exact math producer and selected root source remain unchanged.
There is no new root implementation, exact credit or aggregate replay.

## Caller ECX evidence and limits

A separate raw-target read-before-definition traversal starts immediately
after the three target signed-facing loads, at `47DEC7`, `47E40E`, `47EB90`.
It follows the reviewed root CFG until a full ECX definition, a return, or a
possible read. The search treats ordinary register/address reads and other
calls conservatively; only the independently reviewed stack-argument atan2
and ST0 `_ftol2` contracts are treated as having no ECX input.

Across 80, 78 and 92 visited instructions respectively, no path reads that
incoming ECX value before a full definition or return. First definitions
include `47DF60`, `47E49E` and `47EC2C`; return paths end at `489D71`.
This provides no evidence for forcing a preserved ECX value in the caller.
It does not identify the original TU, compiler profile or register allocator
context. The private packet is `build/reimu-register-context/ecx-liveness.json`.

## Reproduction and next step

The probe audits the base first, rebuilds the ordinary 63-byte anchor, compiles
the actual math source with `/GL`, clones the other object inputs, and links
once. Its receipt includes source/tool/input hashes, commands, unchanged-base
checks and decoded layout. `--help` performs no build. Generated files stay
under `build/`; stale products can be regenerated. Run serially on one CPU:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-atan2-visibility.py
```

The completed reproduction used output directory
`build/reimu-register-context/reproduced/`. Keep investigating the root's
physical sharing for 300/320, 215/310/797 and 522/523, and the duplicated target
resource gate in 214. These need source/visibility evidence; the math result
does not justify arbitrary ABI or source constraints.
