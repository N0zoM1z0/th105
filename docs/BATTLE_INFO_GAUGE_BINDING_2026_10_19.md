# Exact fighter gauge binding, 2026-10-19

## Target and result

`BattleInfoRecordF8_bind_fighter @0x0046FA90` is now canonical **648/648** in
`gpt-web-battle-info-gauge-runtime`. Its existing int*/short* value virtuals
remain20/20 and27/27. This adds one authored function /648 exact bytes, without
changing the authored denominator. No cold aggregate replay is claimed.

Only original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The complete callable is `[46FA90,46FD18)`, with186 reachable decoded
instructions, two bounded loop backedges, no indirect jumps or direct branch
exits, and RET4 at46FD15. Target and selected canonical source SHA256 both equal
`e44f2c92e653701f1356ce5eb1cdb9a524d60e42e4cd381965b50bda800f985d`.

Fresh Ghidra input/base/entry/language/compiler/full mapped-text attestation
precedes decompilation. The ECX record/stack fighter parameter storage and
648-byte body were read back; decompiled text was checked against raw code.
All nine primary database file hashes remain unchanged and temporary read-only
aliases are removed. IDA failed target preflight and supplied no semantics.

## Observed ownership and accesses

The root is game policy: it connects Fighter state to seventeen owned16-byte
gauges, releases five owned-effect references and disables three tail objects.
Two primary gauges use int* accessors into record+0C/+10. Three groups of five
use short* accessors at Fighter+482/+488/+558. The independently exact one-slot
value methods and vtables6C3890/6C3898 establish those accessor layouts.

The retained implementation and bindings had several independent errors:

| Observation | Correction |
| --- | --- |
| All five static allocation CALLs target scalar new689DCB, with size16 | Remove the old scalar-new-to665B8A alias |
| All five old-gauge release CALLs target operator delete6898EA | Replace CRT free with the actual raw C++ deallocation operation |
| Release occurs before each allocation | Separate release from the new-expression argument to the old replacement helper |
| Fighter+47C is consumed through MOVSX word, then stored to record+10 | Use a signed16-bit input view, rather than reading four bytes |
| Pointer/span inputs are captured at particular stages; later stages reload record->fighter | Preserve those actual lifetimes around allocator calls |
| The live UI receiver becomes object+18 and survives release/allocation; its gauge slot is at receiver+A0 | Represent that observed binding subobject in a bounded layout view |
| Group24 starts from a double `i * 200.0` and separately rounds float endpoints | Preserve the double and float stages before constructor subtraction |

The old replacement helper evaluated the new gauge before entering the helper
that freed the old one. That changes the allocation/deallocation order and
exception side effects. A nonzero upper halfword at Fighter+47C also changes
the old four-byte read's result; the target consumes the sign-extended low word.
These were semantic errors, not merely register-allocation residuals.

For primary and secondary bindings, the float span is captured before releasing
the old gauge. The second span is reread through record->fighter after the first
gauge is published. Group input pointers and binding receivers are similarly
captured before their allocation stage. A released slot is not cleared before
allocation; target null-allocation publication and call-boundary exception
state are preserved, without added recovery or rollback.

The source view has an opaque prefix to the observed+18 binding receiver and
an opaque prefix to its+A0 pointer. Those offsets explain all five receiver
adjustments retained across calls. Original UI class identity, inheritance and
unaccessed fields remain unknown; this does not assign a global CTile layout.
The Fighter input view likewise describes this root's access widths, without
changing the shared Fighter declaration.

## Source and comparison evidence

`src/battle/BattleInfoGaugeRuntime.cpp` uses normal C++ scalar new and
`::operator delete`, the existing TGageValue templates, meaningful pointer/span
locals and compile-time offset guards. Compiler profile remains ordinary pinned
VC8 SP1 O2, GS off. No assembly, custom entry convention, forced register,
stack padding, copied target payload or inert local is used.

Correcting width/ownership/lifetimes with the old flat UI view first produced
a647-byte candidate and the correct0Ch frame. Recovering the observed live
binding receiver produces the complete648-byte/186-instruction equality.
Both existing value virtuals remain exact in the same fresh object.

All23 relocation fields are replayed: ten REL32 calls (five scalar new and five
scalar delete), five vptr stores and eight floating-literal DIR32 references.
The vtable-owned callbacks are compared in the same unit; literal widths and
bits pass the target-pinned floating relocation audit. No address field is
masked to obtain equality. The formal object extent is exactly648 bytes.

Selected source SHA256 is
`ae51535f321c3af6c6d203e7028b1cd040abcde7187b511aa0f542b3c54754bf`.
Reproduce the fresh comparison with:

```bash
python3 scripts/build.py --unit gpt-web-battle-info-gauge-runtime --compare --json
```

`matches.csv` and `functions.csv` are updated together only after this formal
zero-difference result. Prior authored-origin evidence is retained as an
accepted witness; canonical matching now owns its census disposition.

## Remaining array-declaration audit

The same bounded batch reviews six other old scalar-new bindings. Their source
already used byte/word/dword array expressions, but lacked real VC8 `<new>`
declarations. The eight raw allocation sites all call665B8A. Four TUs now include
`<new>` and bind the emitted array-new symbol; source expressions and lifetimes
are unchanged:

| Entry | Source candidate / target after correction |
| --- | --- |
|FileBuffer plain419860|224 /234|
|Palette BMP419A60|1007 /1047|
|Palette raw419E80|247 /243|
|CV3 wave419590|250 /247|
|RIFF wave419690|439 /459|
|Encoded FileBuffer419950|275 /267|

Every complete canonical comparison payload is identical to its fresh pre-edit
control. These six functions remain nonexact. The former seven-entry alias list
therefore resolves to six genuine array-declaration fixes plus the incorrectly
bound scalar gauge allocator, rather than seven identical allocation cases.
There is no new runtime-origin or exclusion claim from the forwarding entry.

Receipts are under `build/array-declarations-20261019/`: target-cfgs.json,
primary-db before/after pins, baseline/updated/final focused reports,
array-payload-control.json, gauge-relocations.json and the647/648-byte private
controls. Analysis scripts and read-only Ghidra hypothesis are under
`.analysis/array-declarations-20261019/`. Continue archive-loader41BA70/context
recovery and the unresolved reader/BMP lifetimes after this checkpoint.
