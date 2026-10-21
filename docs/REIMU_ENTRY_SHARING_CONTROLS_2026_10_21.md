# ReimuObject initializer sharing and evaluation controls

The complete initializer at4A1CE0 remains nonexact. A fresh focused build
reproduces the selected3803a002 source,4892 callable bytes,5440-byte canonical
payload65298d36, fourteen body differences and zero differences in548 adjacent
metadata bytes. First mismatch remains4A2E20/+1140h. No candidate below is
selected and no new exact or partial credit is recorded.

Only the canonical Japanese1.06a PE is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh raw decoding verifies all4892 bytes/1325 instructions and callable hash
`1cda9c10ed7d9ab2225800db60a62f45099c7cd3d7adec15621bfa3a49b8e6c1`.
Residual906/999 windows are selected from those decoded instruction boundaries.
The attached IDA database still fails target attestation; no database semantics,
metadata writes or target patches are used.

## Complete bounded sharing families

The observed auxiliary tables share two actual angle-write tails among
905..908. The private generator varies whether each of905/906/907 reaches
each tail through an explicit goto or its ordinary identical store/break.
Both definitions stay in908; no operation, fake return or padding is added.
The six bits are `(905,2),(905,3),(906,2),(906,3),(907,2),(907,3)`.
Selected source is mask0Ch. All other63 masks are compiled serially.

All64 expressions retain the4892/5440 code/payload extents. They produce48
distinct canonical payloads;17 have all metadata bytes equal. None improves
the fourteen body differences. The entire callable and all compiler tables
are compared, rather than accepting either shared tail independently.

A second family covers the actual common state_370=1.0f destination. Its
four bits choose explicit joins from902/905/906/907 into the existing908
assignment; mask0 is the selected ordinary-store source. Of fifteen private
variants, masks1/4/5 retain every selected payload byte. The other twelve
have4896 callable bytes; their changed boundary is not treated as a positional
body-difference score. No member of this sixteen-expression family matches.

These finite families do not exhaust every possible source arrangement or
establish a standalone/LTCG impossibility. They close specific previously
untested combinations of target-supported sharing, including interactions
that isolated case rewrites could not rule out.

## Other genuine evaluation controls

Moving the existing, used shared-parameter declaration before the initial
stores is byte-neutral. A function-scoped int used as the actual selector
argument in906/999 is also neutral. Sharing one real int or short variable
across all32 parameter-derived selector calls likewise reproduces every
65298d36 payload byte. These add no unused storage or fabricated behavior.

Moving only angle2 or angle3's definition to905 yields fifteen body differences,
with one/zero metadata differences respectively, and an earlier4A2D89 mismatch.
Neither improves the selected complete result. A direct pointer-to-virtual-
member expression in906/999 emits an additional virtual-call thunk. The strict
comparator rejects its unknown REL32 target; that control has no canonical
result, invented alias or accepted match.

There are85 private candidates in total:84 complete relocation replays and
one explicitly blocked thunk control. Baseline is counted separately. All
builds run on CPU0/nice10, with one VC8 process at a time. Unchanged selected
bytes do not require repeating the prior672-case native matrix; no new native
coverage, accepted-unit aggregate or compiler-context conclusion is claimed.

## Retained evidence

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-entry --compare --json
```

The command remains an expected nonzero canonical comparison. Reports and
hash-pinned controls are under `build/reimu-entry-evaluation-20261021/`, with
`evaluation-summary.json`, `target-facts.json`, both matrix summaries and the
individual comparisons. `selected.cpp`, `selected.obj` and
`selected-canonical.bin` preserve the fresh baseline. Unselected inputs/outputs
are gzip-compressed only after verified round trips; the compression receipt
retains original hashes. Private recipes remain under the matching `.analysis/`
scope. The public source, headers, unit settings, relocations and tracking
ledgers remain unchanged.
