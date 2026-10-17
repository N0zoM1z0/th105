# Iku action root: unsigned random conversion and spawn rounding

The current work targets the complete59038-byte Iku action root at620920,
with15132 raw instructions and110 nondefault action IDs. This batch recovers
conversion/receiver facts across the root and verifies action602's periodic
object852 arguments in original target execution. The root remains identified,
without complete C++ source, a comparison unit or exact credit.

## Observed bytes and arithmetic proofs

The only target is Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The callable `[620920,62EFBE)` has SHA-256
`abc831c6ccd95986bed811694f532ad8c8b92cb49702a7f6ce4de100b8a73dea`.
Iku's RTTI-backed primary vtable is6C652C; its+28 entry6C6554 names620920.

`scripts/audit-iku-random-float-tails.py` rechecks the complete raw CFG and all
three switch tables, then discovers every root `FADD DWORD[6D6EF8]`. That
literal is the float4294967296. Each of the46 sites follows a signed `FILD`
of a stored32-bit integer and `TEST; ...; JGE` around the correction. The
script proves the producer range and preserves alternate-entry checks, stack
argument writes, signedness, flag definitions and the exact correction bytes.

| Producer | Sites | Derived normal-execution range |
| --- | ---: | --- |
| Original MT result modulo200 | 8 | 0..199 |
| Original MT result modulo100 | 8 | 0..99 |
| Original MT result modulo360 | 1 | 0..359 |
| Original selector, no subtraction | 28 | 0..limit, inclusive; listed limits2/8/30/360/500/640 |
| Original selector400, then unsigned subtraction200 | 1 | 0..200 or4294967096..4294967295 |

The selector's complete27-byte target body is checked before using its
unsigned two-division formula:
`raw / (0xffffffffU / limit)`. These limits can return the endpoint; replacing
the result with a conventional0..limit-1 model is incorrect.

For the first45 sites, the converted bit31 is clear, so `TEST` sets SF=OF=0
and `JGE` always skips the correction. `MOV` and `FILD` preserve EFLAGS.
The raw CFG still reaches these branches syntactically; arithmetic feasibility
is a separate property. The old Ghidra hypothesis's17 removed-block warnings
are exactly the17 bounded-remainder corrections. They do not identify missing
action statements. None of these bytes is removed from the callable, excluded
as a separate library island, or credited as partially exact. A faithful
compiler reconstruction must still regenerate the shipped machine code.

At62C5C3, action602 instead subtracts200 from selector400 before conversion.
For results below200, the unsigned subtraction wraps. The `FADD2^32` at
62C5D4 is feasible and required. The target then adds actor X in x87 and only
afterwards stores to float32. A signed centered offset or an extra float32
rounding before adding X changes the argument sent to object852. This is an
argument-boundary fact; the object's later treatment of that coordinate is
not established here.

## Original-code execution

`scripts/audit-iku-action602-spawn.py` starts at the real root entry, executes
the original seed function and discarded warm draw, both MT draws/selectors,
texture publication, checked texture deque, landing/frame/stage helpers and
the original x87 conversion runtime. No helper returns or RNG state values
are fabricated. Cached initial RNG states are read from actual seed/warm
execution. Every executed instruction must be an attested instruction boundary;
emulated writes are confined to the declared actor/manager/stack/RNG fixture.

The probe stops on entry to465190, before its first instruction. It checks
the real caller return62C5F7, ECX receiver, seven DWORD argument slots,
three-float payload `[0,0,5]`, a stack delta of-1080 from the aligned root entry,
texture-manager stores, frame counters, empty x87 stack and unchanged control
word. It does not execute the object backend or claim a native root RET.

The full2016-case matrix has **zero differences** from the unsigned,
late-storage arithmetic model:

- 36 genuine seeds, including exact selector400 outcomes0/199/200/201/400;
- X values0/1/128/320/640/1000/1279 and facing bytes1/FF;
- initial counters5/35, producing periodic counters6/36 in sequence1;
- grounded Y0 on the original zero stage, unexpired frame limit32767;
- masked round-to-nearest x87 control words027F/037F, PC53/64.

All99 sampled root instructions are visited. The feasible correction executes
in672 cases. A signed-offset model differs in all672; a separately rounded
float offset differs in80. These controls concern the emitted numeric value,
not source spelling. Input SHA-256:
`ad672128ec98a07474d088d02544079ec00867a38e602d9b58b54a784992b990`;
output/model SHA-256:
`3df50dff2e27aa9a8310411ebd2f84ac2a6095791c11b6ecede3a9ae2ebab6d9`.
The21-case smoke is a smaller PC53/counter6/positive-facing matrix, not a
repeat of every full-matrix axis.

Examples at X640:

| Seed | selector500 | selector400 | Spawn X |
| ---: | ---: | ---: | ---: |
| 145 | 72 | 0 | 4294967808 |
| 119 | 83 | 199 | 4294967808 |
| 9 | 182 | 200 | 640 |
| 388 | 346 | 201 | 641 |
| 1472677 | 113 | 400 | 840 |

These original-code samples do not establish all root actions, scene/resource
conditions, rounding modes or exceptional FP behavior. The backend may further
interpret the coordinate; no visible gameplay defect is inferred.

## Compiler corroboration and working types

Private pinned VC8 `/O2 /GS- /GR /EHsc /MT` scalar controls compile natural
unsigned-to-float conversion to `FILD; TEST; JGE; FADD2^32`; a signed conversion
has no correction. A natural float store of
`static_cast<float>(unsigned_offset) + x` retains the conversion in x87 until
the final store and uses the same DWORD correction constant. An explicit
double-conversion control uses a QWORD correction constant instead. Thus the
native model's wider host arithmetic is not a prescription to introduce a
double source operand, and a C++ float cast is not evidence of an intervening
float32 store under this compiler. These scalar controls are compiler
corroboration, not original function boundaries, TU provenance or canonical
root comparisons. Private sources/receipts remain under
`.analysis/iku-types-20261017/` and `build/IkuUnsignedFloatControls.*`.

ESI is assigned from ECX only at62092F; all131 ESI restores occur immediately
before the standard root RET epilogue. The complete instruction inventory has
60 fixed receiver-relative access locations. LEAs at+4/+130 are address-only
subobject evidence, leaving58 memory-access-backed components in a partial
7B8 working view. The public fact packet records every width, operation,
witness and neutral working field/type projection. This does not establish
the complete class size or uniquely original C++ member declarations.

One direct Ghidra process at a time independently attests the imported PE,
entry68B9D2, x86 Windows target, complete mapped `.text`, root hash and vslot.
It saves the58-component view, ECX/no-stack-argument void root ABI,30 ordinary
callee ABI models and46 correction comments. A fresh read-only process checks
every component's type/name/offset/width, explicit callee parameter types,
returns, calling conventions/purges, root receiver storage and all15132
instructions. The existing common-root view and special x87 conversion helper
are preserved. Primary-project hashes are checked before transferring the
verified clone back; target bytes are unchanged and the clone is removed.

The previously unclassified46-byte adapter406330 has a direct Iku call and
an observed `float __cdecl(float)` surface: it widens its argument for the
known CRT `_fabs @ 68BAAE`, then stores/reloads a float before returning in
ST0. Only that ABI evidence is added to its candidate row. Ownership and
original source/name remain in review; there is no authored/source/exclusion
or exact promotion for this helper.

The new246740-byte decompiler output remains private and hypothetical. Its
17 removed-block warnings are now qualified, but its spacebase/jumptable and
overlapping-global warnings remain. Complete natural C++ recovery still needs
manual action/edge/field/payload review and preservation of the observed float
lifetimes. The next type discriminator is the shared register CALL at621040;
a private receiver-flow diagnostic gives possible vslots8/C at that join.
Do not assign it one callee merely from its immediate physical predecessor.
No decompiler text is pasted as source.

## Reproduce

```bash
python3 scripts/audit-iku-random-float-tails.py > build/iku-random-float-tails.json
python3 scripts/audit-iku-action602-spawn.py --smoke
python3 scripts/audit-iku-action602-spawn.py > build/iku-action602-native.json
python3 scripts/ci.py
git diff --check
```

No shared C++ source/header, compiler flag, accepted unit or exact ledger
changes. No unrelated accepted-unit or aggregate cold replay is claimed.
