# AyaObject actions810/821 predicate consumption

## Observed and selected

The original Japanese1.06a PE is hash-attested as
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA remains rejected for wrong-image identity; observations use the original PE.
The bounded source unit is AyaObject update root0x61A290, ledger size19522.

Target calls at61AA22,61AAA4 and61BB35 immediately consume `TEST AL,AL; JE`.
The selected source previously generated `TEST EAX,EAX` at all three sites.
The first/last callee is435DC0 (42 bytes); the middle is5F9310 (64 bytes).
Their accepted int-return declarations remain unchanged. Three explicit
`static_cast<unsigned char>` conversions at the calling conditions recover
the observed low-byte consumption without changing ABI or helper definitions.

## Return-range proof and limits

`predicate_return_range.py` enumerates both edges of every decoded conditional
branch, tracking full EAX values conservatively. Entry EAX is unknown. Allowed
normal calls clobber EAX; partial-register writes cannot prove its high bytes.
Indirect calls/branches, outside edges, unvisited instructions and unknown or
non-Boolean normal returns are rejected. MOV EAX,immediate and XOR EAX,EAX
are the only recognized full-width definitions.

For435DC0, RET435DE3 receives EAX1 and RET435DE9 receives EAX0. For5F9310,
RET5F9348 receives EAX1 and RET5F934F receives EAX0. Their internal435D60 calls
are permitted to return with arbitrary EAX; each predicate subsequently defines
the complete result. Thus replacing the callers' full-width tests by low-byte
tests preserves their immediate JE decisions on actual normal helper returns.
This is code-generation recovery, not evidence of a gameplay behavior defect.
No termination, exception, callback or whole-root equivalence claim is made.

Six unit controls cover both Boolean arms, partial AL assignment, non-Boolean
EAX, one bad branch arm, call clobber and an external jump.

## Full-object delta and comparison

`audit-aya-object-predicate-widths.py` pins all three original consumers, checks
the current consumers and can compare the complete canonical payload against
the predecessor object. Only offsets7FA,879,1979 change, each opcode85 to84.
All other bytes, call positions and metadata are unchanged. Full size remains
20048, metadata starts19580; no shared header/profile/relocation changes occur.

- Previous full canonical SHA256:
  `00c1b4bc8129e1e0c2b8119a1d559bfccf1efa30d4bcd2a813e0d34a1d3e4b8a`.
- Selected full canonical SHA256:
  `8af8ee94e0b848aa1b4d903ccc3404b504167e18515d033379d3f0f71ff43d36`.
- Selected19522-byte comparison SHA256:
  `00239c7a7cfd17dc871116ffa385351c09fe15187849f2db350afd0f9930caf1`.

The configured full-root comparison remains nonexact at offset22(hex),
target0F/source49. No exact count/byte credit is added. Other root control,
shared-return placement, x87 scheduling and scratch-lifetime questions remain.

## Reproduction

Run serially; the configured comparison is expected to report nonexact:

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-aya-object-vslot28-full-root --compare --json
python3 scripts/audit-aya-object-predicate-widths.py --output build/aya-predicate-widths-20261022/width-proof.json
python3 -m unittest discover -s tests -p test_predicate_return_range.py -v
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The retained local `build/aya-predicate-widths-20261022/previous.obj` was copied
before the source edit. Passing it as `--previous-object` also verifies the
complete three-byte delta. Local receipts are `selected-formal.json` and
`width-proof.json` in that directory; binaries/reports are not committed.
