# AyaObject whole-function source controls, 2026-10-23

Target: original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root `0x61A290`; raw attested PE only, because IDA preflight still rejects its
open database. This batch follows the user's TH075-inspired exact-first
priority: compile complete source controls before expanding semantic analysis.

Public source, ABI, headers, unit, mappings and match ledgers are unchanged.
Fresh configured baseline builds and compares nonexact at **+0x22**, target
`0F` / source `8E`. Its complete 20120-byte canonical payload remains
`fad6fa5af2baa1d8b9013d3fe7279bcfea3f136474a0bb9f9a0a52ccd30caf2c`,
metadata at19652; source SHA256 remains
`da5c622d4808d6dd1516dee567923ede8f1a2c6c4ae0655730ba006505710f46`.
No control is selected and no exact credit is added.

## Observed target ownership

Complete raw closure covers 4630 instructions /19522 callable bytes. Target
frame helper `0x4351C0` has eleven physical CALL sites; baseline has thirteen.
The extra sites split one target-shared tail:

| Side | Call site | Reachable action owners |
| --- | --- | --- |
| Target | `0x61A5DB` | 801, 807, 811, 817, 822, 854 |
| Baseline at S | `0x80035D` | 801, 811 |
| Baseline at S | `0x8006A4` | 807 |
| Baseline at S | `0x8012C3` | 817, 822, 854 |

The shared source statements call frame advance, conditionally decrement
lifetime, then read time/frame timer/frame index/sequence in that order and
decrement again on sequence2. CFG ownership uses actual JMP successors and all
seven reviewed switches, with opaque calls assumed to return normally. It is
not a callback/exception or whole-program proof.

The target callable ends exclusively at `0x61EED2`; the next two bytes are
`8B FF` (MOV EDI,EDI), before tables at `0x61EED4..0x61F0A8`. Those 468 table
bytes are followed by eight INT3 bytes before initializer `0x61F0B0`. Thus the
20000-byte enclosing span includes post-table alignment; code plus the reviewed
tables ends at offset19992. Neither span enlarges callable ownership or proves
an original COFF/TU boundary. Candidate metadata starts also include any preceding
compiler alignment, so their offsets are not callable sizes.

## Complete native controls

Seventeen native controls were built serially; fifteen close the configured
full comparison and remain nonexact. Two retain unresolved relocation identities.
All were compiled as full roots, without assembly, copied target bytes, inert
locals, fabricated returns, ABI changes or comparison masks.

| Controls | Count | Payload / metadata start | Result |
| --- | ---: | --- | --- |
| Typed offsets for root fields, all accessed root/sprite/motion fields, and a pointer-only receiver with the same virtual slots | 3 | 20120 /19652 | Complete canonical and mapped bytes equal baseline; no owner is constructed or embedded. |
| Used member tail with `__forceinline` | 1 | 20120 /19652 | Complete payload equals baseline. |
| Ordinary in-class member tail | 1 | 20084 /19616 | A new out-of-line helper has no target binding; comparison rejects the unresolved local call. |
| Six tails shared by an early label, switch break, or equivalent early-return predicate | 3 | 20040 /19572 | Eleven frame sites, but MOV EDI,2 is hoisted before dispatch and the common block moves later. |
| Single-case switch in the shared tail | 1 | 20044 /19576 | Same unwanted constant hoist; nonexact. |
| Join 807 to 801 | 1 | 20256 /19788 | Twelve frame sites; larger and nonexact. |
| Join 807 to 817 | 1 | 20000 /19532 | Twelve frame sites, original dispatch instruction form preserved, but all four scale/rate pairs reverse their recovered operand order. |
| Join 817/822/854 to 801 | 1 | 20000 /19532 | Eleven frame sites, unwanted constant hoist and reversed scale/rate pairs. |
| Reversed addition operands, double rate operand, or used compound-add temporary | 3 | 20000 /19532 | Byte-neutral to the 807-to-817 control. First two alter all four sums; the compound control alters only826. |
| Local fenv access around the four reversed sum expressions | 1 | 20000 /19532 | Byte-neutral; does not restore target operand order. |
| Whole-root fenv access on the same source epoch | 1 | 20264 /19796 | Introduces new literal identities; formal replay stops at an unmapped F32 literal. Raw COFF still has the four reversed field pairs. |

The 807-to-817 payload SHA256 is
`aa4315f2699f8a3ceeaf867b15a01da237029b1b4873890b5458aa1457d3591a`.
It remains nonexact +0x22, target `0F` / source `16`. Its smaller size is not
selection evidence: the strict source graph comparison first finds scale reads
at S `0x80357F` / `0x803507`, respectively rate-first and scale-first. All four
changed pairs have that reversal, not just861. The selected float caller view's
earlier ordering result is specific to its source context.

One actual807 witness retains three sequence reads and all existing observations
for the fully shared 20040-byte control and baseline against target. This is
not a full matrix or a result for the distinct 807-to-817 control. No checker
was relaxed to pass the changed graphs, and no large matrix was run.

For whole-root fenv, private literal inspection finds the new F32 +0.05 payload
uniquely at readonly `0x6C4668`, but the next new F32 -400 literal has no aligned
readonly occurrence. Private replay stops there; no binding is fabricated or
added to the public ledger, and no full canonical hash is claimed for that
control. The unmodified formal comparison remains blocked on its first missing
mapping. The reversed field-read order is independently visible in raw COFF.

## Genuine link context and next action

The ordinary member-tail source was also added to the existing consistent
float-view update/initializer source and compiled with `/GL`. It links with the
same hash-verified real provider objects and pinned CRT/SDK inputs under
`/LTCG`. The linked image retains a real helper symbol and five physical root
calls to it. No target ABI/boundary for this extra helper is established, so
no target binding, complete canonical replay or DLL execution is claimed.
This rejects that concrete helper context; it does not establish an LTCG
impossibility or original source partition.

Continue from the selected public source, focusing on the target's physical
six-action tail sharing and operand lifetimes together. A reduced call count
or payload size must not hide the extra dispatch instruction, later placement
or reversed floating reads. These concrete offset/minimal-owner declarations
and sum-expression variants need no further investigation in the tested epoch.

Private recipes: `.analysis/aya-exact-first-source-20261023/`; receipts and
frozen controls: `build/aya-exact-first-source-20261023/`. Start with
`baseline.json`, `controls.json`, `frame-owners.json`, `common-frame-owners.json`,
`common-tails.json`, `inline-tails.json`, `partial-tails.json`,
`scale-expression-scope.json`, `fenv-controls.json`, `root-fenv-completed.json`,
and `cil-member-tail/inspection.json`. Other predicate and graph diagnostics
retain their logs. Recipes protect completed output paths against overwrite.
Final public-input identity and local CI receipts are `final-state.json` and
`ci.log`. Accepted totals remain unchanged; no aggregate replay was performed.
