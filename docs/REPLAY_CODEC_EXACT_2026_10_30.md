# Shared replay/score memory codec

The authored compression4067F0 and decompression406890 wrappers are canonical
exact153/153 and151/151 in `exact-first-replay-codec`: **304 new authored bytes**.
Both complete linked-symbol bodies and closed CFGs pass the existing strict
comparator. No prefix, provider or alignment-byte credit is added.

This closes the old ordinary-COFF aligned-frame stop through newly available
real provider context, not source coercion. The exact pinned zlib1.2.3 headers
and C sources are built by the existing source-locked PNG/zlib provider. Only
zlib archive members required by the wrappers are linked; the unused PNG
archive grants no code/provider credit. Source ownership, original archive
inputs and hashes are recorded by the normal link recipe. `/O2 /GL` + `/LTCG`
naturally emits the native `AND ESP,-8` and3Ch local frame. `z_stream` remains
56 bytes with alignment4, using its actual upstream declaration. No alignas,
packing change, dummy local, handwritten prologue or register binding is used.

## Semantics and evidence

Each wrapper initializes only zalloc/zfree/opaque to zero, invokes the original
versioned initializer with the exact six-byte NUL string1.2.3 and sizeof56,
then publishes input/output pointers and capacities. Deflate uses level-1 and
Z_FINISH; inflate uses Z_NO_FLUSH. Z_STREAM_END succeeds, as does Z_OK with
remaining output capacity. Other statuses return0 immediately, without adding
an End call absent from the target. A failing End also returns0. Success returns
original output capacity minus remaining capacity; it does not read total_out.

Source entry points match the existing ScoreLoad/ScorePersist declarations;
network packet callers independently use the same native cdecl four-argument
memory codec. The library destinations are deflateInit_667590, deflate665C10,
deflateEnd6663F0, inflateInit_6679C0, inflate667AD0 and inflateEnd6690D0.
The public comparator validates every E8 through the actual linked library
symbol. The complete source-owned version literal is checked before its sole
PUSH address is replayed to6D69D0. Neither root has C++ cleanup EH.

Fresh Factory metadata, entry point and all five mapped samples passed again.
Function inventory, disassembly, decompilation and caller/callee evidence are
retained in build/frontier-replay-zlib-cil-20261030/ida-evidence.json. Target and
canonical-source hashes:
-4067F0:49372bd901381e34bdc4360bb1ae7a655fc1e4e6c4f4513e5506e56362545dce
-406890:e29a0ef8cc48a960829252af8cb761f64bec1f8a645f207cf251d3b02ff9a8a4

## Validation scope

The codec source and match unit are new; no existing accepted source consumer
or shared compiler flag changes. Existing receipts are preserved. Source-lock
verification is rerun by the new build. No all-unit or all-origin rebuild is
needed. All target-backed early failures remain intact, without introducing
new defensive/runtime tests.

```
scripts/repo-python scripts/build.py --unit exact-first-replay-codec --compare --json
scripts/repo-python scripts/ci.py
```

Formal receipt: build/frontier-replay-zlib-cil-20261030/formal-final.json.
The now-real codec provider can support subsequent full score/network caller
investigation; this checkpoint does not claim those callers are exact.
