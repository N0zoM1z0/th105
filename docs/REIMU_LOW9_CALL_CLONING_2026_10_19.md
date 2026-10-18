# Reimu: one source advancement call, four compiler copies

A single shared C++ advancement expression still produces a separate action9
machine call. Listed and plain builds agree in every canonical byte. Static
dataflow and actual execution both find empty x87 stacks at the relevant calls.
VC8 RTM preserves the same sharing as SP1. These observations narrow the
remaining compiler/source-context question; the selected source stays at
6c35f95. No implementation, exact-byte or aggregate-progress credit changes.

## Target observations and source control

Target is original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Authored root 478FA0 remains `[478FA0,48CE2E)`, 81550 bytes, SHA256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The ledger state remains unclassified/declaration-only.

The target's advancement call 47973E has complete membership
0/2/9/71/72/74/145. Setup entry 47973C is empty under the reviewed callee-effect
model. Cleanup entry 47973A consumes one live FLDZ zero before that setup.
Action9's JE479711 enters 47973C; its crossing path falls through the shared
6/7/8/9/306 action10 landing at 479713. Raw observations and earlier memberships
are detailed in the [coupled-exit note](REIMU_LANDING_EXIT_CONSTRAINTS_2026_10_18.md).

The new private control expresses both shared exits, preserving the selected
float conversions and the recovered 197/658 and 198/608 landings. All seven
advancement edges enter one C++ label; its sole call expression is line244.
VC8 `/FAcs` independently associates four actual CALL instructions with it:

| Complete action membership | Target sites | Source copies of line244 |
| --- | --- | --- |
| 0/2 | 479236, 4792CD | 47923A, 4793B9 |
| 0/2/9/71/72/74/145 | 47973E | absent |
| 0/2/71/72/74/145 | absent | 47A605 |
| 9 | absent | 479718 |

The two 0/2-only copies correspond to existing target sites. The extra9 copy
is the remaining regression. Every listed CALL offset is checked against the
COFF symbol's canonical replay and resolves to4351C0. This is observed compiler
copying from one source expression, not proof of the original source spelling
or the compiler pass responsible.

The listed ordinary object SHA256 is
`2469f03c068149a89a545e876878f669473a8a64114f3edf8da044f7ded7e8ea`.
The same source without `/FAcs` has identical complete82808-byte canonical
payload, SHA256
`ebb683d86b09c0fa31822b2597f23739742a4ba8d4c9acd1102321d2c92b0fc8`.
Source SHA256 is `5453f8f67c906884706925a071b59734fc7b4f4c98b5381f8c34b7de414afa2f`.
Prefix81436/frame570h, all11 switches and all15 request/stack contracts qualify.
No assembly is used as reconstruction source; the listing is compiler output.

Height and motion-clear complete partitions now agree, so differing direct
partitions fall6 to4, but the previously correct seven-action advance/RET group
splits. Physical advancement counts become121/121 while300/320 still merge.
This conceals the missing300/320 site with an extra9 site. The control is not
selected. Complete owned243/243, wave77/77, sequence-slot+C and prior action10
landing groups remain preserved. Indirect physical counts remain220/219.

## Conditional static model and actual entry states

The worklist covers20243/20243 target and20255/20255 source instructions.
There are no conflicting depths, underflows or overflows; maximum depths are
3/4. All153 target and154 source RETs have depth0, and all ordinary call entries
have depth0. The split9 advance and six-action common advance both enter empty.

This model assumes empty contiguous root-entry tags, ordinary successful paths,
the five reviewed floating-return callees, the one __ftol2_sse pop and zero net
x87 effects for the other26 direct callees and slots8/C/14. These are explicit
conditional effects; arbitrary callee paths, entry tags, unmasked exceptions
and environment restoration remain unproved. The model does not establish why
the backend copies the block.

Actual helper execution passes **0/5752 differences**: 0=832, 2=832, 9=1600,
71=735, 72=730, 74=735 and145=288. Stops are5536 real RETs,206 effect requests
and10 owned-object requests. Inputs come from the existing low, recovery and
movement families; every run explicitly supplies empty x87 tags/TOP0 at root
entry. The target and source each reach5292 real4351C0 entries. Every observed
entry has occupied-tag count0 and TOP0, including1472 action9 entries per side.
All seven actions reach the target common site; source9 uses its separate copy.
Actor/argument/helper/FP comparisons still pass. No target instruction, helper
or callback result is patched. Returning world requests and arbitrary FP
environments remain outside this proof.

Two preliminary adapter invocations aborted on differing family-check APIs;
neither is a passing result. The corrected adapter retains the low family's
two-argument check and movement's three-argument check. Recovery has no extra
check callback; its paired result and inherited ABI/x87 checks remain active.
Final input SHA256 is
`9ed7b3cbee1faf12bdd7aae0f99a252e3dd4ef4357e3c041fbdef01bde9cba16`.

## Source controls and compiler-version limit

Reversing9's crossing/advance early-return spelling changes no selected payload
byte. Factoring the landing with a real int action10 parameter changes no byte
relative to the corresponding explicit landing control. Neither repairs the
coupled membership. These are new controls on the current source phase; do not
repeat them without independent evidence.

The identical one-expression source and header are also compiled with the
previously hash-pinned VC8 RTM cl/c1xx/c2. RTM prefix81464/payload82836/frame570h
qualify; all32 direct-callee, virtual-slot, indirect and RET partitions agree
with the SP1 control, including the extra9 copy. Its canonical payload is
`1020af807d18cd2ba71840c07fe2bfa685360a8f265f02f3fe9016e743962b5a`.
RTM is not executed or selected. Both versions emit all seven FIMULs with the
current explicit float conversions; the earlier RTM zero-FIMUL result belongs
to the pre-conversion source. Rich build50727 alone does not resolve patch
provenance, and this experiment excludes neither version for other source/TU
contexts. Every control remains nonexact at+541=4791BD.

## Reproduction and retained evidence

Selected source is unchanged; its public producer remains
`scripts/probe-reimu-action-ltcg.py`. Private recipes and receipts live in
`build/reimu-low9-x87/`:

```bash
nice -n 10 taskset -c 0 python3 -B build/reimu-low9-x87/one-advance.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-low9-x87/one-advance/candidate.obj
nice -n 10 taskset -c 0 python3 -B build/reimu-low9-x87/qualify-listing.py
nice -n 10 taskset -c 0 python3 -B build/reimu-low9-x87/native-advance.py build/reimu-low9-x87/one-advance/candidate.obj
```

`trace-control.py OBJECT REPORT` records the conditional full-CFG model;
`listing-proof.json`, `native-advance.json` and `payload-summary.json` pin the
results. The native adapter SHA256 is
`0f7e1efe54170aec7d5cd3cea75d7e76ce5eba909b71945e7bcbfa80ef397025`.
These are private diagnostics, not acceptance units. Regenerate discarded
products before rerunning dependent commands.

Direct read-only Ghidra independently attests executable identity, entry point,
language/compiler, mapped .text and root hash before inspecting the bounded
landing/advance/FLDZ windows and eight common-setup edges. All nine primary DB
hashes remain unchanged; the temporary alias is removed. Heavy work is serial
on CPU0/nice10. Ghidra uses a128MiB heap, takes10.37s and peaks312MiB; native
execution takes47.77s and peaks168MiB. No historical matrix or all-unit replay
is run. Selected source, ABI, profiles, ledgers and accepted units remain intact.

Cleanup removes 19 obsolete control/listing products (5.10MiB),
preserving all164 current genuine-cache files, recipes, reports and small listing
excerpts. CI-created bytecode is separately disposable. The mandatory finished
worktree gate remains `python3 scripts/ci.py` and `git diff --check`.
