# Exact shared secondary-animation update

## Result and reproduction

`SecondaryAnimationRenderRuntimeView::update_secondary @ 0x004309F0` is
**2434/2434 canonical exact** against original Japanese TH105 1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete compared body hash is
`bff81f4ee3b1397982d2b42c588d3fcf0d92343ddc03f90ff1250e81a798fae3`.

Source: `src/battle/SecondaryAnimationRender.cpp`.
Existing unit: `gpt-web-secondary-animation-runtime`, unchanged VC8 SP1
`/O2 /GS-` profile, headers, layouts and relocation bindings.
This closes the shared strip-update root, not an individual character root.
Its existing shared manager wrapper mapping is `0x004937D0 -> 0x004309F0`;
the IDA `get_callers` response in this packet is null, not a new call census.

```bash
python3 scripts/check-ida-mcp.py
python3 scripts/typed-re.py 0x004309F0 --max-bytes 2434 --json
python3 scripts/build.py --unit gpt-web-secondary-animation-runtime --json
python3 scripts/compare-unit-object.py gpt-web-secondary-animation-runtime \
  build/match-units/GptWeb_SecondaryAnimationRuntime.obj \
  --address 0x004309F0 --json
```

Local evidence: `build/secondary-update-acceptance-preflight.json`,
`build/secondary-update-current-typed.json`,
`build/secondary-update-native-build.json`, and
`build/secondary-update-native-formal.json`.
The existing-object comparator alone does not establish compiler provenance;
the preceding formal unit build and its provenance file do.
No unrelated accepted modules or global cold build were rerun.

## Exact observations and boundary

Fresh target-attested IDA instructions describe a signed update-step gate,
checked-deque expiration, render gate, source-point insertion, and four switch
entries for sizes 0 through 3 plus the larger-size default arm. Hermite and
normalization calls build both edges of the strip in five curve loops.
The initial stack alignment is eight bytes and local allocation is 0xA0.
All branches, calls, floating instructions, native checked-container checks,
register choices and stack displacements match over the whole body.

The last shared epilogue begins at `0x0043136A` and ends with RET at
`0x00431371` (root +0x981). Earlier RET instructions do not terminate the
comparison. The switch at `0x00430B3F` uses the separate four-entry table at
`0x00431374`: `0x0043136A`, `0x00430B46`, `0x00430B76`, `0x00430D97`.
These addresses were independently read from the hash-verified PE, alongside
the IDA switch evidence. The exact object's section tail is 2452 bytes:
2434 callable bytes, two alignment bytes and sixteen table bytes. Do not
misinterpret that tail as an eighteen-byte function-size excess, or credit
the table/alignment as new authored instructions.

## Source-lifetime discriminator

The old source at checkpoint `e416937` staged five loop normalization inputs
as named vectors: four function-scope objects and one loop-local object.
A fresh isolated build reproduced the old first mismatch at +0x43. Its
actual last RET is +0x971, sixteen bytes early, despite a 2436-byte section
tail. Initial checked-iterator stack homes were 0x18 lower; shorter memory
encodings and subsequent loop alignment account for the body-length change.

The recovered loop expression is ordinary vector construction:

```cpp
D3DXVec2Normalize(&normal, &SecondaryAnimationPoint(
    shared_previous.y - shared_center.y,
    shared_center.x - shared_previous.x));
```

VC8 accepts the address of this class temporary in its existing Microsoft
extension mode. Its pointer is consumed within the full expression; no
pointer is retained past the temporary's lifetime. This is not a portable
ISO C++ spelling to mechanically impose on other toolchains.
These actual expression lifetimes naturally recover the target's iterator
storage reuse, all later vector homes and loop alignment. No new storage,
unions, padding, volatile, fake liveness, assembly or forced registers are used.

The first normalization input remains a named, field-staged vector, exactly
as in the retained source. Making **all six** inputs expression temporaries
is a useful negative control: it reproduces the entire frame and boundary
but still differs in seven bytes at +0x23A..+0x240. At +0x239 the target loads
the scaled normal from the stack before adding the first deque point;
that variant reverses the two floating operands. Restoring only the first
named input gives the complete canonical result. Do not treat floating
operand commutation or a normalized instruction score as exactness.

Private discriminator reports are
`build/secondary-update-baseline-formal.json`,
`build/secondary-update-temporary-formal.json`, and
`build/secondary-update-first-named-formal.json`.
The final source was then independently built in the original production TU
and passed the full 2434-byte comparison, not merely the isolated probe.

## Interpretation and remaining scope

The matching source demonstrates a sufficient native C++ lifetime contract;
it does not uniquely recover historical variable names or source formatting.
Older notes describing this root as nonexact or its sixth input as a required
named loop local are superseded by this whole-function result.
Together with the 274-byte replacement at `0x00496420`, this closes the
remaining authored comparison gaps in this shared secondary-animation lane.
The CPU root `0x005F1F80`, common Fighter root `0x004740C0`, and quantized
sine/cosine roots remain nonexact. Apply the lifetime lesson only where fresh
target evidence supports it; it is not a universal compiler tuning recipe.
