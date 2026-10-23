# AyaObject 852 native RTM and floating-environment controls

All controls remain unselected. Native RTM reproduces SP1's unresolved facing
conversion shapes; local `fenv_access` also keeps the negative-arm `FIMUL`.
Selected game source remains `e24fb73`, root `0x61A290` remains nonexact.

## Target observations and source epoch

The target is original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Target/status/tracking checks pass. IDA preflight rejects the open database's
different executable; these observations use the attested PE and native COFFs.

The [previous facing packet](AYA_OBJECT_801_CONTEXT_852_FACING_CONTROLS_2026_10_23.md)
is freshly reproduced on current source, including the selected 826 correction.
Target `0x61C98C..0x61C9CA` is 62 bytes / 14 instructions: capture the nested
signed byte with `MOVSX EDX` before the direction branch, then convert with
`FILD` inside each arm. The negative arm converts before loading and negating
state `+0x374`, then uses `FMULP`; the positive arm uses memory `FMUL`.
The product is stored to owner `+0x6AC`. Source spelling remains unknown.

Private scope: `build/aya-852-rtm-20261023/`. `selected.cpp` is the current
source; `int-facing.cpp` changes only the genuinely used facing local from
signed byte to int. The raw byte access and ABI are unchanged. The serial
recipe is `.analysis/aya-852-rtm-20261023/controls.py`. Frozen CPPs, commands,
compiler/frontend/backend hashes and baseline input pins are retained.

## Compiler and source controls

| Control | Full bytes / metadata start | Facing bytes / instructions | Result |
| --- | ---: | ---: | --- |
| SP1 selected | 20132 / 19664 | 67 / 16 | Byte capture; sign extension in each arm |
| SP1 int local | 20120 / 19652 | 56 / 12 | Early `MOVSX`; negative `FIMUL` |
| RTM selected | 20148 / 19680 | 67 / 16 | Same conversion shape as SP1 selected |
| RTM int local | 20136 / 19668 | 56 / 12 | Same conversion shape as SP1 int |
| SP1 int, explicit if/else | 20120 / 19652 | 56 / 12 | Complete canonical payload identical to SP1 int |
| SP1 int, local fenv access | Canonical replay blocked | 64 / 14 raw COFF | Still negative `FIMUL`; extra double store/reload |
| Target | Callable ledger 19522 | 62 / 14 | Early `MOVSX`, two branch-local `FILD`s |

RTM and SP1 here use the same ordinary `/O2 /GS- /GR /EHsc /MT` native profile.
No shared profile is changed. The preceding shared-tail experiment established
the local compiler file versions; this scope additionally pins `c1xx.dll` and
`c2.dll`. Rich build 50727 does not identify the original minor release.
The extra 16 bytes in these RTM objects describe this source context only.

The fenv control places `#pragma fenv_access(on)` around this function and
restores it afterward. It tests floating-environment constraints, without
enabling immediate exception delivery. Compilation succeeds, but canonical
replay rejects a newly emitted unmapped `__real@3d4ccccd` relocation. No target
binding is invented. Its separately labelled raw COFF packet shows that it
does not recover the required conversion shape and adds a QWORD store/reload
before the float product store. No canonical hash or execution agreement is
claimed for it. The source control is not adopted.

The explicit-if control puts the actual product assignment in each direction
arm instead of a conditional expression. It introduces no extra computation;
its complete canonical payload is byte-neutral relative to the int control.

Complete canonical SHA256 values:

- SP1 selected: `a5dc22f5c6f0e93a3fc81592510327c5708c8c4d41938f2bd96eaf7947523ede`.
- SP1 int / explicit if: `c698bc5d37e44b77c058128dd7c7f228905c17f84e748d0e7405789b1caa2cb7`.
- RTM selected: `464540dcd45e389d4e7ab9053e105b7fc4d899d5b5d45030f7d9b162e7fbb1d1`.
- RTM int: `eaff97a0f69917c79e0779ab372b8f35005af7c03ede320a24940b6e095bcbe2`.

## Execution, impact and acceptance limits

Both RTM objects pass 6,528 original-code returns and 6,400 owner-product
write snapshots in the existing 852 auditor. Recorded actor/parameter state,
ordered writes, calls and x87 observations agree. The matrix varies signed
facing boundaries, nonfinite speeds and eight masked x87 control words.
It avoids random/spawn paths and does not cover arbitrary resources, callbacks,
unmasked exceptions or the complete root. Instruction differences remain.

The int-local change preserves 4,267 strict normal-return graph nodes outside
852 under each compiler independently. Comparing SP1 selected against RTM
selected outside 852 fails at mapped PCs `0x804A17` / `0x804A25`: `LEA EDI,
[ECX+0x39]` versus `MOV EDI,0x3C`. This is a failed strict comparison, not a
proof of different effects or whole-root equivalence. No checker was weakened.

All four replayable control comparisons remain nonexact at `+0x22`. No source,
ABI, header, partition, relocation or configured compiler change is selected;
no accepted unit is affected and no aggregate cold replay or exact credit is
claimed. These results rule out the tested native minor-release, environment
access and assignment-form explanations in this source context. They do not
prove an original local type, an LTCG requirement, or standalone impossibility.
Further trials need independent visibility/lifetime/ownership evidence for
the early promotion and branch-local conversions, rather than more repetitions
of these source forms.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-852-facing-lifetimes.py
taskset -c 0 nice -n 10 python3 scripts/audit-aya-object-852-native.py --object build/aya-852-rtm-20261023/rtm-selected.obj --control-object build/aya-852-rtm-20261023/rtm-int.obj --output build/aya-852-rtm-20261023/rtm-native.json
```

The first command is expected to exit nonzero for nonexactness. Per-object
strict comparisons and original-code receipts are in the private scope, not
accepted matching records.
The SP1 int/if objects are retained in `completed-controls.tar.gz`; consult
`retention.json` and restore repository-relative members with `-C .`.
The RTM execution inputs, selected baseline and raw fenv object remain loose.
