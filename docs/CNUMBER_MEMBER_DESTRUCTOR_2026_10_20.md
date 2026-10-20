# CNumber normal destructor: complete40-byte exact result

`CNumber_dtor @0x0040ADB0` is now canonical **40/40 exact** against the
original Japanese TH10.5 v1.06a executable, SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
The ordinary C++ source is `src/ui/CNumberLifetime.cpp`, unit
`gpt-web-cnumber-lifetime`. No compiler-profile, shared-header, layout or
relocation-binding change is required.

## Target observations

Raw code begins40ADB0 and ends with RET at40ADD7, exclusive end40ADD8.
Eight INT3 bytes separate it from the next function at40ADE0. The EH cleanup
entries6B9477 and6B95B7 tail-jump to40ADB0 with an existing receiver in ECX;
they are callers of the reusable body, not extra bytes owned by it. The body
saves/restores ESI and uses RET0. Existing CNumber RTTI COL6DCBEC and vtable
6C1B60 establish its zero-offset IColor base and deleting-destructor/color
virtual family.

The destructor restores the CNumber vptr, conditionally releases its value
pointer at+24 through operator delete6898EA, then writes:

1. IColor vptr6C0624 to embedded tile+28 at40ADC9.
2. IColor vptr6C0624 to the outer base at40ADD0.

The original retained narrow lifetime source implicitly generated the tile
destructor. It emitted40 bytes and matched the first26, but reversed these
two final vptr stores. The scalar deleting destructor already emitted the
target order and was accepted; same-sized ordinary destruction was not exact.

## Source recovery and verification

An explicit ordinary `virtual ~CNumberTileLifetime() {}` gives the embedded
member its own source-level destructor body. VC8 naturally emits member
cleanup before outer base cleanup in the complete destructor. There are no
manual vptr stores, explicit destructor calls, fake work, assembly, forced
registers, or new exception specifications. This is a coherent lifetime source
hypothesis, not proof of unique original C++ spelling.

The existing narrow view's size/offset assertions remain unchanged. No other
source includes this CPP, and its only configured unit is the lifetime unit;
all five affected functions are rebuilt and canonically compared:

| Address | Function | Exact bytes | Canonical SHA256 |
| --- | --- | ---: | --- |
|40ADB0|normal destructor|40|9580a90c84334d9d57c121ace658cf8990e5e68a76cc06b6073a75fcee66ce77|
|40ADE0|set_color|11|bf4d327b151205ff0a92ecc8ad2ba4fa03ca0af1acf770c9b0cf72b1720802ab|
|40ADF0|set_vertex_colors|11|3491a19e7efbd469e360ea164021e57cb06c6a3b55d1984b4e752ed8d8b92a1b|
|40AE00|multiply_color|11|7c9f5cdc2112cf9befefce1599df662ff511aa1d3968b005d0f547413ba114af|
|40AE10|scalar deleting destructor|60|778cb8774685a6977529384329fe9092b6778a76ccfaa59999f0c5d619e007dd|

Only the normal destructor adds new exact credit: one function/40 bytes.
Source-present mappings, target boundary, origin, four prior exact rows and
all bindings remain in place. `functions.csv` and `matches.csv` are updated
together. The preliminary authored-origin rule is retired in favor of the
standard canonical-exact authored evidence; classification is unchanged.
Ledger-count and cold-selection expectations are updated to include this
new acceptance. This result does not accept CNumber initialization or ReimuObject's
larger update root.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-cnumber-lifetime --compare --json
python3 scripts/validate-tracking.py --require-target
python3 scripts/ci.py
git diff --check
```

Fresh preflight passes target/tracking checks. The attached IDA still has
the wrong target, so all new observations use the hash-attested PE. Frozen
baseline/control/formal reports and CPP/COFF inputs are retained under
`build/cnumber-lifetime-order-20261020/`; private regeneration uses the
corresponding `.analysis/` directory. `baseline-build.json` records the
40-byte/+1A predecessor and four exact siblings; `selected-build.json`
records all five exact results with build provenance and relocation replay.

Selected CRLF source SHA256:
73b71deda022c6b2794cc7b08f086c2d6b71f044870716fe4e478e6f6a6b0254.
The first formal COFF has SHA256
eb0279b3761ff18a4f885d05c6924f0f72d26e5676549e0d2140afdadd4f65b7;
subsequent builds can change raw COFF identity while preserving the canonical
payloads above. No cold aggregate replay or aggregate percentage is claimed.
