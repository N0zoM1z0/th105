# ReimuObject908 arithmetic and rebuilt owner context, 2026-10-22

The target's29-byte post-wave arithmetic loads angle before converting the
short counter. The selected public root instead has a27-byte integer-first
form. A real owner context with typed float/parameter/facing storage and the
902 correction reproduces all29 bytes, while preserving the earlier804/869/902
execution results. Both rebuilt48-object images retain that window. Neither
whole root is exact; the owner context remains private and unselected.

## Target observations

All target facts use original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA again fails preflight for its unrelated `10350095...` image. Raw attested
PE instructions supply the observations, independently of decompiler prose.

The primary908 dispatch starts at4A051D. It reads sequence13E and unconditionally
sets EBP to-1 at4A0524 before its checked secondary dispatch. At4A0765 a direct
CALL reaches the real35-byte wave dispatcher45C030. The29-byte window
`4A076A..4A0787` (exclusive end) is:

```text
FLD float[this+374]
MOVSX EAX,word[this+366]
MOV [ESP+20],EAX
FILD dword[ESP+20]
FADDP ST(1)
FSTP float[this+374]
```

The selected public source first converts the integer and then uses FADD
with the float in memory. Immediately before addition, the target has two
live x87 values and public source one. Final float outputs need not reveal
that difference. The next target instruction, outside this window, adds BP
to the word counter. The physical prefix from4A051D through the wave CALL
has no other EBP/BP-writing instruction. Under normal ABI-preserving returns,
this is a decrement. This is static register context, not a returned-wave test.

There is an earlier spawn call on this path. Existing actual-root probes stop
at its opaque entry. No returning spawn/wave result is supplied in this work.

## Explicit arithmetic-window preconditions

`scripts/audit-reimu-object-908-window.py` starts directly at the arithmetic
window and stops before the counter update. Its preconditions are ESI=owner,
writable stack at ESP+20, empty x87, and a specified masked control word.
It does not jump past an executing callback, inject a RET, or claim that the
original callback returned. Code remains immutable. This is an independent
straight-line instruction experiment, not a whole-root execution audit.

The2,240 cases cross20 raw angle bit patterns,14 signed-short counter values,
PC53/64 and all four rounding modes. Values include signed zero, rounding
boundaries around1 and2^24, largest finite floats, subnormals, infinities,
signed quiet/signalling NaNs, and counters-32768 through32767. Observe raw
float output, ordered integer-temporary/angle writes, logical x87 values/tags
before/after addition and final FPSW. Verify unchanged counter/ESP/control
word, exact window traversal and empty final x87.

| Compiled input | Float output / writes / FPSW | x87 snapshots | Window |
| --- | --- | --- | --- |
| Selected SP1 source77fe73a4 | Equal in2,240 | Different in2,240 | 27 bytes, nonexact |
| Expanded used-double local | Equal in2,240 | Different in2,240 | Unchanged27 bytes |
| Corrected real owner | Equal in2,240 | Equal in2,240 | 29/29 |
| Current public source with RTM | Equal in2,240 | Different in2,240 | Nonexact |

These are scoped emulation results. They do not cover arbitrary incoming
floating stacks, unmasked exceptions, callback return behavior or root RET ABI.
The public SP1/RTM inputs intentionally fail this audit when used as primary
input; contrast mismatches are informational.

## Corrected owner and preserved earlier paths

The private owner keeps the real17-slot hierarchy and existing size388 fields.
It uses the prior typed self-float storage, actual inherited340 pointer, and
actual effect-sprite signed facing field; apply the five selected902
directional intermediates to this source. No extra value, padding, fake
callee or assembly is introduced. An ordinary native build gives45,696 bytes,
canonical SHA256
`4b565d714737cf5ddfdaf8ae5d9944369071899fccb70223f86f572b55a65bf2`,
still nonexact49655F/+31. Counter4963A0 remains66/66.

Fresh original-target execution audits of that real owner pass804's5,120,
869's3,072 and902's1,792 cases under their separately documented scopes.
Those include real helpers/full RET paths where previously admitted; they do
not turn the908 window fixture into a returning-callback test. A normal graph
comparison preserves9,344 semantic nodes from the other199 action entries
plus default, contracting only direct JMP and register LEA/NOP. The remaining
coarse native-source delta is the908 value-loading/addition order.

The public source remains selected: SHA256
`77fe73a458421c55ceb7f2d9151a369aa19095f2de194404b8e8033f109fc349`,
canonical45,696-byte `4d0ac180...` payload, nonexact+31. Simply expanding its
used angle intermediate to double is byte-neutral. The new context is useful
evidence for owner storage/access recovery, not justification to replace
global class interfaces or claim original nominal member/return types.

## Rebuilt genuine provider contexts

Copy the typed owner headers into one private tree and rebuild Root, Pool and
Lifetime with their existing flags, plus Finalize, Sequence and Idle native
providers. The native Root's original header copies are byte-identical to
this tree. Ten sequence bodies remain fully canonical22/27/111/20/67/35/
138/112/202/154; finalize overrides remain26/33. The accepted counter is66
in both final images. These are replays of existing bodies, not new credit.

Substitute these inputs into the prior real-provider closure. Each image has
48 actual objects,29 physical-ABI aliases, nine attested data-only bindings
and the pinned static CRT/SDK. Export only the real pool and counter; the
root is retained through its actual vtable. All17 entries resolve and +28
points to the root. All eight target RTTI base names/PMD offsets agree.
Native providers still include separate ABI views; this is not recovery of
the original complete program's nominal declarations/TU graph.

| Linked observation | Native root | Root CIL |
| --- | ---: | ---: |
| Root VA | `806140` | `801070` |
| Available symbol span | 45,696 | 45,600 |
| Metadata offset | 44,828 | 44,720 |
| Reachable instructions | 10,387 | 10,482 |
| Reachable instruction bytes | 44,805 | 44,715 |
| Reviewed switches | 22 | 22 |
| Calls / returns | 428 /63 | 432 /63 |
| First target difference | +31 | +0 |
| Post-wave arithmetic | 29/29 | 29/29 |

The CIL entry still aligns ESP down to8 through an EBP frame, unlike target.
Both linked angle windows are statically byte-equal to the target. Their image
SHA256 values are
`aee3e20c52bd735ca74c35b432e782963cce89b195e567604124a59e54a3539d`
and `b0b14d84ec45be18da492802ac41c039edc5ddf3d2df2e2b79abfeffdbaab443`.
Symbol spans include metadata/alignment; they are not authored-byte ownership.

## Compiler revision and reproduction

A fresh current-source RTM control verifies all three installed compiler
payload hashes from [the RTM record](VC8_RTM_PROBE.md). Its45,716-byte payload,
canonical SHA256
`468308aa11e29ed7101cb666cdbebbd62be36b90c01c2a12ae6c8467bd630b6a`,
still differs+31 and retains counter66/66. It does not restore this source's
908 window. This discriminates this source/profile only, not all RTM or other
original compilation contexts. The public compiler profile is unchanged.

```sh
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-908-window.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj
```

The selected public input has an expected snapshot mismatch. Use `--symbol`
for the real owner and `--contrast-object` / `--contrast-symbol` for the compiled
negative. Reports pin target/COFF, public source/ledgers, script dependencies
and engine versions before/after execution. Source-to-object provenance is
explicitly a separate actual build receipt. No execution report is matching
acceptance.

Private recipes are under `.analysis/reimu-object-908-lifetimes-20261022/`;
receipts under `build/reimu-object-908-lifetimes-20261022/` include `facts.json`,
`bp-prefix.json`, `comparison.json`, `corrected-owner-comparison.json`,
`probe.json`, `owner-window-audit.json`, the804/869/902 owner audit reports,
`unchanged-graphs.json`, `rtm-comparison.json` and `rtm-window-audit.json`.
The `owner/` subdirectory retains six-TU build receipts, both links/inspections
and `linked-angle-windows.json`. Generated sources/objects/images remain
private and uncommitted.

No public reconstruction source/header/ABI/profile/relocation/ownership or
match-row change; ledgers stay1,379 exact/234,584 bytes without a new aggregate
cold replay. Next recover the remaining actual self/parent storage accesses
in the private owner using offset/width facts, rather than promoting the
remaining staging overlay or assuming original global interfaces.
