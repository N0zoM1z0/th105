# Reimu root: bounded integer operands and x87 state

## Target observations and selected source

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The authored root `Reimu_dispatch_action_state_vslot28 @478FA0` remains
`[478FA0,48CE2E)`, 81550 bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
Its ledger status/source selection remain unclassified/declaration-only.
No implementation, match-unit, exact-byte or aggregate-progress credit changes.

Raw target instructions contain seven FIMUL sites. The preceding selected
source emits FILD plus FMULP at each corresponding operation. The signed
integer stores, arithmetic order and subsequent float stores already agree.
These are operation/type observations, not seven independent functions.

| Action | Target FIMUL | Current source FIMUL | Target/source preparation starts | Equal bytes |
| --- | --- | --- | --- | ---: |
| 89 | 47A471 | 47A490 | 47A445 / 47A464 | 54 |
| 545, extra ray | 486DCF | 486D3E | 486DBF / 486D2E | 37 |
| 545, regular ray | 486E80 | 486DEF | 486E70 / 486DDF | 37 |
| 546, extra ray | 48730A | 487279 | 4872FA / 487269 | 37 |
| 546, regular ray | 4873BB | 48732A | 4873AB / 48731A | 37 |
| 550/551, Y | 4875D5 | 487545 | 4875C3 / 487533 | 45 |
| 550/551, X | 487619 | 487589 | 487600 / 487570 | 58 |

Each complete no-CALL interval in the table now has identical bytes, including
integer preparation, multiplication and outgoing/result stores. Intervals
exclude the preceding trig CALL; its relative displacement depends on site
placement. These internal diagnostics confer no partial matching credit.

The selected source hypothesis explicitly converts the real integer operand
to float before the existing double calculation:

- `ReimuActionStateMovementAttackCases.hpp`: negated signed WORD732 for VY.
- `ReimuActionStateMid540Cases.hpp`: signed facing times 50 in both ray paths.
- `ReimuActionStateMid550Cases.hpp`: signed animation timer times 20 for X/Y.

The respective ranges are [-32767,32768], [-6400,6350] and
[-655360,655340]. Every integer in those ranges is exactly representable in
the target's binary32 float. Negation still occurs after sign extension to
int; -32768 remains supported. No calculation is commuted, callback read
moved, ABI changed or extra rounding store emitted. Under the same pinned
VC8 SP1/default-FP configuration, these conversions recover all seven FIMULs.
Original spelling and original TU/profile provenance remain unknown.

Private same-source /Os, /fp:fast and RTM controls each emit zero FIMULs.
They are unselected, unexecuted diagnostics; this is not a general exclusion
of other compiler/TU contexts. Their recipes and receipts are below
`build/reimu-x87-state/`; obsolete products have been removed.

## Complete source qualification

Current ordinary object SHA256:
`1962c4202fdab172c3a6d95ee4dd563957f1653334d66a0d07cff07b001086b5`.
Generated source SHA256:
`72df0da474154f8203df746ae8c5484fe41d697b65e7ccb34e2c411d92b4b307`.
The private source-type control and selected ordinary object have identical
canonical payloads. The genuine linked payload also agrees in all 82808 bytes,
SHA256 `967ab8fdda07897afedf43e034bd85e0d5d756afdc915b05394f9a6977ede6c5`.

Frame 570h, code prefix 81436, all 11 switches and all 15 request-buffer
contracts remain qualified. All 2471 fields replay: 1183 REL32 calls, 1104
numeric fields, 14 metadata addresses, 163 code pointers and seven globals.
There are 1281 HIGHLOW fields; eight linker INT3 alignment bytes are separate
from the 82808-byte payload. Genuine linking is not target byte equality.

The complete source physical partitions are unchanged for all 32 direct
callees, indirect calls, candidate virtual-slot domains and RET sites,
including complete action membership and multiplicity. Thus the recovered
owned-object/wave and action10 landing memberships are preserved. The same
six direct callee partitions still differ from target: 4351C0, 435240,
435D60, 45AF40, 473DD0 and 478EE0. Indirect physical counts remain 220/219,
with action-count deficits at 410 and 416. Strict comparison still first
differs at +541 / 4791BD, the conditional branch operand at 4791BB.

## Conditional x87 dataflow and execution

A private depth/last-producer worklist covers every qualified CFG edge:
20243/20243 target and 20251/20251 current source instructions. It gives
one depth per instruction, maxima 3/4, no underflow/overflow or conflicting
depth, and depth zero at all 153 RETs on each side. This is conditional
consistency evidence, not numeric equivalence or a recovered ABI declaration.

The model assumes empty contiguous entry tags and ordinary successful paths.
406360, 4063D0, 406540, 435D60 and 478DD0 push one floating result;
68A1A0 consumes one value. Other 26 direct callees and virtual slots 8/C/14
have zero net effect. Unmasked exceptions, arbitrary entry tags, environment
restoration and all internal callee paths are not proved. Generic push/pop
semantics are corroborated by the official
[Intel software developer manual](https://www.intel.com/content/dam/support/us/en/documents/processors/pentium4/sb/25366521.pdf).

At target 47973A, ST0 has one live zero from six possible FLDZ producers:
47920C, 47927C, 4793C0, 4798EC, 4799B3 and 47A5BC. The FSTP consumes it;
47973C/47973E enter setup/advance with an empty stack. Source
4792D2/4792D4/4792D6 has the corresponding states; its producers are
47920C, 47927C, 4793C9, 47990B, 4799D2 and 47A5DB. No missing cleanup
distinguishes these entries under the stated effects. This alone does not
explain the remaining physical sharing differences.

Fresh selected-source execution passes **0/4628 differences**: action89 320,
545/546 1366 each and 550/551 788 each. It includes 32 signed-WORD extrema
cases and PC53/64 fixtures. Stops are 3516 real RETs, 24 effect-entry requests
and 1088 owned-object-entry requests. All seven target/source FIMUL sites
actually execute, with matching occurrence counts 54/60/123/60/123/616/616.
From explicitly supplied empty entry tags/TOP0, every multiplication has one
occupied tag and TOP7. Later world callbacks, subsequent fan/ring iterations,
arbitrary FP environments and complete runtime behavior remain unproved.

An initial diagnostic assertion incorrectly assumed the inherited Unicorn
fixture already had empty entry tags. That run is not an accepted result.
The explicit entry fixture passed a focused 38-case calibration and then the
full 4628-case run above. No target instruction or helper result was patched.
Affected partial movement and integrated-low rebuilds pass 0/99 and 0/59.

## Reproduction and retained working state

Run commands serially with CPU affinity and low priority. The public producer
reconstructs/qualifies the current ordinary and genuine linked payloads:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --action 545 --action 546 --action 550 --action 551 --require-contracts
```

Current private adapters/reports remain under `build/reimu-x87-state/`:
`operand-windows.py`, `graphs.py`, `trace.py`, `native-affected.py`,
`float-operand-windows.json`, `selected-state-report.json`,
`float-qualification.json`, `native-float-operands.json`, partial smoke
reports and cleanup/resource receipts. The native adapter runs with
`python3 -B build/reimu-x87-state/native-affected.py build/reimu-ltcg/ordinary.obj`;
input SHA256 is
`56ff32069b186d73f428ec5d10a9cb63da019b06724c0324a28bf83cec3577ae`.
Private files are ignored working evidence, not committed acceptance units.

No IDA semantics, Ghidra process or database write was used for this unit.
All nine primary database hashes remain unchanged. Serial CPU0/nice10 peaks
313 MiB for genuine production, 291 MiB for static state qualification and
151 MiB for affected execution. No aggregate exact-unit replay was run.
Cleanup removes 26 obsolete products/listings, 8215783 bytes, preserving all
164 current genuine-cache files and the nine database pins. CI-created
bytecode is separately disposable. See the current [handoff](RE_HANDOFF.md)
for the remaining boss constraints and mandatory final gate.
