# ReimuObject action869 parameter prefix, 2026-10-22

The target loads parameter0 before adding angular velocity. Public source
reproduces that order; both private complete-owner variants reverse the two
operands. Reading the parameter pointer from the real inherited340 storage,
alongside the typed self-float access, restores the target window and3,072
prefix observations. The whole root remains nonexact+31 and unselected.

## Raw target and source observations

Use only original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh IDA preflight again rejects its unrelated `10350095...` image; all target
facts here come from the attested PE. The reviewed primary table selects869
at49C32D. The next higher primary entry is49C9F5; that physical interval is
only a search bound, not accepted action or compiler byte ownership.

For sequence0 with fighter action669, the target subtracts0.5 from this+37C,
rounds/stores the float and clamps it to at least-15. At49C39B..49C3B7
(exclusive end), this28-byte window follows:

```text
FSTP float[this+37C]
MOV EAX,[this+340]
FLD float[EAX]
FADD float[this+37C]
FSTP float[EAX]
FLD float[this+370]
```

The selected public root has all28 bytes equal at805B46. The private complete
owner and the [typed self-float control](REIMU_OBJECT_804_LIFETIMES_2026_10_22.md)
instead use `FLD float[this+37C]; FADD float[EAX]`. Their stored results agree
in the matrix, but the live value before FADD differs. Equal output and equal
instruction lengths therefore do not recover the target operand order.

## Real parameter-storage control

The retained real CharacterObject layout has `unsigned *copied_words_340`.
In the private typed-self owner root, replace the190 uses of the existing
overlay parameter pointer with `reinterpret_cast<float *>(copied_words_340)`.
This changes access to the same actual pointer/storage; it does not add a
field, change layout, force volatile reads, invent a value or alter a call
contract. Target float accesses support this bounded storage interpretation,
not the original nominal pointer declaration. Other overlays remain in place.

The ordinary VC8 control now restores the28-byte window. Its complete source
payload remains45,696 bytes but has canonical SHA256
`4d0ac180cace3180285c26ccfb94a48d3f05d70037761cdbd4f1d7f07c947a50`,
still nonexact at49655F/+31. The real counter4963A0 remains66/66. Relative to
public source, a coarse branch-normalized instruction delta now has12 regions,
in902/904/907. The previous869/908 scheduling differences disappear. This
diagnostic does not prove those other actions equivalent or accept the root.

## Bounded execution evidence

`scripts/audit-reimu-object-869-prefix.py` executes the actual root prefix and
stops at the original406360 sine entry, before that helper's first instruction.
There is no fabricated lookup result or returning opaque callback. This scope
does not claim a full-root RET ABI check or original lookup execution.

The fixed3,072-case matrix crosses12 parameter bit patterns,16 angular-velocity
patterns, PC53/64, all four x87 rounding modes and two parameter locations:
the ordinary external buffer, or aliasing this+370 amplitude. Each location
has1,536 cases. Raw inputs include signed zero, subnormals, infinities,
signed quiet/signalling NaNs and neighbours of the0.5 and-14.5 input thresholds.
Exceptions are masked. Sequence0, phase0, fighter action669, counter1 and
timer0 select the actual add prefix. Raw fixture bits/pointer are installed
at root entry; target and candidate instructions remain immutable.

Compare fixture outputs as raw bytes, ordered owner/parameter writes,
logical x87 snapshots immediately before/after FADD and at sine entry,
the actual pending float argument and final FPSW. Every case crosses each
observer once and reaches the same real helper entry.

| Real compiled source | Outputs / writes / pending argument / FPSW | x87 snapshots |
| --- | --- | --- |
| Selected public root | Equal in3,072 | Equal in3,072 |
| Complete owner with overlay access | Equal in3,072 | Different in3,008 |
| Typed self floats, overlay parameter pointer | Equal in3,072 | Different in3,008 |
| Typed self floats and actual parameter pointer | Equal in3,072 | Equal in3,072 |

The latest pointer control also passes all5,120 cases of the804 audit with
its real animation helper and full RET checks. This supports those two bounded
paths only; the other changed parameter sites remain unqualified. Results are
x86 emulation observations, not hardware validation, arbitrary aliases or
unmasked exception coverage. Existing public selection remains unchanged.

## Reproduction and next lead

```sh
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-869-prefix.py \
  build/match-units/GptWeb_ReimuObjectActionState.obj
```

Use `--contrast-object` and `--contrast-symbol` for a compiled negative control,
or `--symbol` for a real owner as primary input. Primary snapshot differences
fail the command; contrast differences are informational. Reports pin target,
COFF, source, data/manifest ledgers, imported audit scripts and engine versions
before/after execution. Source-to-object build provenance is explicitly not
attested by the execution command; retain its separate actual build receipt.

Private recipes are under `.analysis/reimu-object-869-lifetimes-20261022/`:
`facts.py`, `params_build.py`, `params_delta.py`, `probe.py`. Receipts under
`build/reimu-object-869-lifetimes-20261022/` include `facts.json`,
`params-comparison.json`, `params-source-delta.json`, `probe.json`,
`public-audit.json`, `params-audit.json` and `params-804-audit.json`.
The pointer control uses the actual int/void selector hierarchy and the
unchanged ordinary profile from the804 typed-self experiment. Its emitted
source SHA256 is `e6489df19cad7082bf1b4bbbcdd93ba9793c6a4ac3790c5e1515d7a1ccf9e86f`.
Private source, objects and reports remain uncommitted.

No public reconstruction source/header/profile, selection, byte-ownership or
match row changes. Ledgers remain1,379 exact/234,584 bytes; no new aggregate
cold replay is claimed. Next inspect902's pointer reload/float round trips,
then the904/907 sharing changes before adopting a complete-owner source model.
