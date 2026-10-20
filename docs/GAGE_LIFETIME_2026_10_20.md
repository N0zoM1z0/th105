# CGage and CDesignGage lifetime/color exact recovery

Five independently bounded functions now compare canonically exact in
`gpt-web-gage-lifetime`:153 bytes total. Only original Japanese TH10.5 v1.06a
SHA25656350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e
is used. The attached IDA fails target attestation and supplies no semantics;
new observations come from the hash-attested PE.

| Address | Durable name | Exact bytes | Canonical SHA256 |
| --- | --- | ---: | --- |
|40AD60|CGage_scalar_deleting_destructor|56|6ebe585feb0b2ace8b7d707e99c4c5ebe719c07d8af667d68d599b609d303bbe|
|40AF00|CDesignGage_set_color|11|35166072327d08f8c978024c8e301a2d2e909735d6138b47d1b59650babda85a|
|40AF10|CDesignGage_set_vertex_colors|11|9f6caed2614e152601f10f451fdea233d64dfc0c61c37b808c552968a6d39573|
|40AF20|CDesignGage_multiply_color|11|399fef8631ed6cb89965bbd547959f14414243794fe608b8e50c1b5645f9164d|
|40BAC0|CDesignGage_scalar_deleting_destructor|64|b987927af932e1382784f9a2444fdde91e8ff0ae9e51362faec9837f1a47fb86|

## Observed identity, ownership and ABI

Vtable6D6A38's COL6DCC88 names `CGage`; its four hierarchy entries are
CGage/CSprite/CSpriteBase/IColor with zero-offset, nonvirtual bases. The table
has nine slots:40AD60,40AC50,40AC70,40AC90,406A90,406A60,4070C0,41B3F0,
406BE0. The first four match the destructor/color contract used here.

40AD60 restores its CGage vptr, conditionally releases pointer+A0 through
operator delete6898EA, restores the IColor vptr6C0624 and conditionally deletes
the receiver according to flags bit0. It returns the original receiver in EAX,
preserves ESI and ends with RET4 at40AD95, exclusive end40AD98. Eight INT3
bytes isolate the next body. Both conditional edges and both direct calls
are inside the reviewed body or its identified deallocator; no remote tail
is owned. This body contains the class's owned-value release policy; no
unobserved normal-destructor function is counted separately.

Vtable6D6AA0/COL6DCB00 names `CDesignGage`, with zero-offset
CDesignObjectBase/IColor bases and seven virtual slots. Its destructor40BAC0
destroys the CGage member at+18, using owned pointer+B8, restores member and
outer IColor vptrs, and conditionally deletes the complete receiver. RET4 at
40BAFD ends exclusively40BB00; all local branch targets close inside64 bytes.

The factory at40B66D allocatesBC bytes through scalar new689DCB. Its inlined
construction publishes CDesignGage vtable6D6AA0 at+0, CGage vtable6D6A38 at+18,
clears member+4 (whole+1C) and clears whole+B8. The CGage pointer access at+A0
requires at leastA4 bytes; the containing allocation after prefix18 leaves
exactlyA4 bytes. These observations bound the source member and complete
object extents without adding storage for code generation.

Three11-byte callbacks forward the original argument and ECX+18 to member
vslots04/08/0C through an indirect tail jump. CDesignSprite and CDesignNumber
tables also share these physical callbacks. The durable CDesignGage names
identify one observed owner; each physical body is counted once.

The factory, RTTI and lifetime fields explain the gauge-shaped UI subobject
previously seen by [BattleInfo binding](BATTLE_INFO_GAUGE_BINDING_2026_10_19.md).
They do not independently prove the dynamic XML type of every pointer supplied
to that binding root.

## Source and comparison contract

`src/ui/GageLifetime.cpp` uses ordinary typed inheritance, an owned pointer,
an explicit CGage member destructor and an implicit outer destructor. Color
methods call the real member virtually. Source-local lifetime views retain
all nine gauge and seven design slots, while reusing the existing CSpriteBase
physical layout. Unused runtime slots remain declarations, including opaque
markers whose original signatures remain unproved. Offset/size assertions
guard94/A4/18/BC and the+A0 pointer. Unmodeled ranges account for existing
target object storage and add no function-frame storage.

Constructors express the observed zeroed value/known base initialization and
emit the ordinary class lifetimes/vtables. Constructor bytes, full RTTI data
and the unresolved runtime virtual bodies are not accepted by this unit.
Original C++ declaration ownership and spelling remain hypotheses.

The selected profile is unchanged ordinary VC8 SP1 O2, GS off. There is no
assembly, custom entry convention, copied target byte array, forced register,
manual vptr store or fabricated return. No shared header is edited. One new
zero-addend address binding records CGage's complete36-byte vtable prefix,
with its target RTTI/store evidence. It is used only by this new unit; all
other absolute/code bindings are existing verified entries. The formal
comparator replays every function relocation without masking.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-gage-lifetime --compare --json
python3 scripts/function-origins.py --write --check
python3 scripts/validate-tracking.py --require-target
python3 scripts/ci.py
git diff --check
```

The five prior review candidates become mapped, source-present and matching
with synchronized ledgers and canonical authored-origin evidence. No additional
aliases or unobserved destructor entries receive credit. The factory2666-byte
body, gauge renderer41B3F0 and remaining design runtime methods stay outside
this acceptance. ReimuObject496540 remains nonexact; no aggregate cold replay
or new aggregate percentage is claimed.

## Receipts and pins

Fresh preflight, raw byte/RTTI packets, private trials and the formal report
are under `build/gage-lifetime-20261020/`. `formal-build.json` records all five
complete exact comparisons and build provenance. `target-facts.json` records
the observed fields/tables/factory slice; its private recipe is
`.analysis/gage-lifetime-20261020/facts.py`. The initial direct and source-local
views also reproduce all five bodies; only the latter is selected, to keep
the observed physical slots without expanding a shared header.

Selected CRLF source SHA256 at commit74ccfae:
338fd39a66984f89cd8d27fb72005a71fdc84202a589f8d2fdf0f1101a077492.
The first formal COFF SHA256 is
dd37ac6339c46d1b7adaf6a9e27515abdb47303ea3b62e810fa00f7df3e650a0;
frozen copies are `selected.cpp`/`selected.obj` in that scope. Canonical body
hashes above are independent of raw COFF timestamps.

October21 follow-up: complete renderer41B3F0 recovery names the original
twelve bytes at94 as two float UV spans and a32-bit fill selector, and refines
two previously opaque slot declarations using observed RET16/RET12 contracts.
All five accepted lifetime/color bodies freshly replay exact. Current source
pins and the focused receipt are in
[the rendering record](GAGE_RENDER_2026_10_20.md#affected-accepted-unit-and-reproduction).
The old source/COFF pins above describe the original acceptance epoch; they
do not purport to hash the later source. Renderer41B3F0 remains nonexact.
