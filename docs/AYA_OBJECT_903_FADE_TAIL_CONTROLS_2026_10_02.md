# AyaObject 903 fade-tail and x87 controls, 2026-10-02

## Bounded result

This continues [the case 8 alpha checkpoint](AYA_OBJECT_903_CASE8_ALPHA_SNAPSHOT_2026_10_02.md) for `AyaObject_update_action_state_vslot28 @ 0x0061A290`. The only analyzed target is the original Japanese 1.06a executable, SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`. The retained source and exact ledgers are unchanged by this control.

**Target instruction observation:** case 2's fading x87 path at `61E827..61E83B` orders `FMULP`, `MOV AL,[ESI+113]`, `FSTP [ESI+120]`, then `CMP AL,20`. Case 3 multiplies at `61E91B` and jumps from `61E921` to the case 2 `MOV AL` at `61E829`. The retained candidate instead orders `FMULP`, `FSTP`, `MOV AL`, `CMP` in case 2; its case 3 stores before loading alpha too. Case 8 owns the candidate's common fade tail, while the target's case 8 jumps into the tail in case 2. These are placement and scheduling differences, not proof of a different source computation.

Two private VC8 controls each changed only case 2/3, with the already retained case 8 snapshot held fixed:

| Source hypothesis | Candidate case 2 order | Candidate case 3 order | Whole-root comparison |
| --- | --- | --- | --- |
| Retained direct store, then alpha guard | `FMULP, FSTP, MOV AL, CMP` | `FMUL, FSTP, MOV AL, CMP` | Nonexact `+0x22` |
| Read a real `prior_alpha` before the second reset store | `MOV AL, FMULP, CMP, FSTP` | `MOV AL, FMUL, CMP, FSTP` | Nonexact `+0x22` |
| Carry the real multiplied `float`, read alpha, then write the value | `MOV AL, FMULP, CMP, FSTP` | `MOV AL, FMUL, CMP, FSTP` | Nonexact `+0x22` |

The two private controls produced the **same canonical comparison-window SHA-256**, `3c8c34853f91b3f2802b2ba587d52389a95b6abe3c466037f01db48717598033`, with candidate metadata 19,548 and 903 at 1,726 bytes/372 instructions. The earlier alpha read is too early relative to both target paths; neither source spelling is retained. These controls do not establish that a different natural C++ spelling or original TU/LTCG context cannot produce the target order.

**Separate exit observation:** the four case 9 coordinate guard branches target `61A42C`, whereas the candidate branches target `61A359`. Those two 15-byte decrement-and-return tails are byte-identical in the hash-attested PE (`838630030000ff5f5e5d5b8be55dc3`). The apparent edge mismatch therefore does not establish a behavior change or justify altering the case 9 guard. It remains a physical tail-placement difference for canonical matching. This is limited to those exits; it does not prove whole-path equivalence, including x87 exceptions or surrounding effects.

The checker `.analysis/aya-903-order-20261002/prove-fade-tail-controls.py` binds target PE, private source and COFF hashes, decoded path ordering, both comparison windows, 903 sizes and the two target exit byte sequences. Its report and private objects live under `build/aya-903-order-20261002/`; private existing-object comparisons lack configured-build provenance. The configured retained object is still the one from [the preceding checkpoint](AYA_OBJECT_903_CASE8_ALPHA_SNAPSHOT_2026_10_02.md), whose source/object hashes were read back unchanged. No exact credit or shared ABI/header/helper/compiler/relocation contract changed.

Next work should seek independent original compiler/TU/LTCG or value-lifetime evidence for the shared fade tail, or another target-backed semantic discrepancy. Repeating these two case 2/3 spellings or changing case 9's coordinate predicate to force an exit address is unsupported. The attached IDA session again failed target identity and was not used; raw target PE bytes supplied this evidence. No Ghidra import or aggregate cold replay is claimed.
