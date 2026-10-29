# Weather resources and stage-row initialization

Native46A260 has941 bytes. Complete selected source now models the policy,
but remains946 bytes and is not exact. This batch adds no authored exact bytes.

## Independent ownership correction

Exact shared battle bootstrap438F50 calls46A260 at439091. Its effect owner is
0xE8, with texture handles08, sprites18, transition deque28, stage map3C and
weather emitter48. The initializer calls vector<CEffectSprite>::_Assign_n at
4663E0 and publishes CEffectSprite vptr6C072C on the fill temporary. That helper
is independently exact186 bytes with0xE8 elements, as recorded in
EFFECT_SPRITE_OWNER_2026_10_29.md. The earlier vector<CSpriteEx>/resize hypothesis
is superseded. Existing lifetime/runtime views now use the actual element type.
The transition entry still carries a normal CSpriteEx base pointer.

## Recovered policy and lifetime order

The emitter loads data/weather/effect/effect.pat with count0. Both resource
vectors assign17 entries. A per-iteration260-byte path buffer loads
 data/weather/%02d.bmp and configures each sprite from actual texture dimensions,
with pivot width/2,height. There is no added null/failure guard.

A0x30-byte CSV owner loads data/csv/background/sky.csv. Each row starts with
a signed-byte stage key, followed by17 unsigned-byte event entries. The real
map is map<signed char,vector<unsigned char>>; nonconst pair construction and
conversion to the map's const-key value account for the two native vector-copy
calls. The existing exact map/container providers are preserved.

Native advance_row at46A54B executes before the row-vector destructor. The
older do/while hypothesis destroyed that local before advancing. Selected
source keeps the row alive through the call and breaks afterward on false;
normal RAII then destroys the row on either branch. Temporary map values are
destroyed before advance_row, independently of the longer-lived row.

Finally the weather object manager releases tracked objects, stage becomes-2,
event/global IDs become16, the companion global becomes0, transitions clear,
the current battle stage is published, and the three position floats become0.
The CSV owner remains alive until after this reset sequence.

## Exactness boundary

Native SHA256:
52388b4f6d985f8d10764657c0bf16d88b6ecf70855acdd53cfb10997de5fbd1.
Complete selected946-byte SHA256:
a6b0ca76207e7c58bb50b1150a71ebda3d14347660d235b4043a4a84f8c453f4.
The first mismatch is+247 at46A357, where native uses a texture-output slot at
7C and source at4C. Native places the CSV object at4C and later pair/result
values at80/94; the candidate uses CSV70 and pair/result50/64. The shifted
instruction lengths and loop scheduling remain unaccepted. No stack padding,
manual vptr, copied byte sequence or register forcing is used.

Direct handle-value return and a named output API are byte-identical here.
Named pair lifetime produced934 bytes and is not selected. Natural make_pair,
vector(count,value), and resize controls introduced their own unbound helpers;
they were not relabeled as the target's different calls. Those controls are
closed unless new source-partition evidence appears. Their compilation is not
exact credit. The selected explicit insert has the observed _Insert_n boundary.

## Focused replay

scripts/repo-python scripts/build.py --unit exact-first-event-effect-initialize --compare --json
scripts/repo-python scripts/build.py --unit gpt-web-event-effect-state-lifetime --compare --json
scripts/repo-python scripts/build.py --unit gpt-web-event-effect-state-runtime --compare --json

The latter two preserve all five accepted functions160/173/153/123/86. Both
existing generated-origin manifests were also freshly verified: all five
anchors retain unique fingerprints across the4024-candidate inventory.
Reports are in build/frontier-event-effect-loader-20261029/, including
full-public.json and anchors.json. The formal root comparison intentionally
reports mismatch; its941-byte prefix hash is not a complete-source hash.
