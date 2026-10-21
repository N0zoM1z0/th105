# CDesignBase virtuals and object lookup exact

Target: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Six new complete authored functions total **968 exact bytes**. The existing
135-byte render remains exact in the same unit:

```bash
python3 scripts/build.py --unit gpt-web-design-base-render --compare --json
```

| Function | Address | Complete bytes | Canonical SHA256 |
| --- | --- | ---: | --- |
| set vertex colors | `40C040` | 81 | `d9cd55f5e5367bacffb5d3374a49f63fe003f04adbe873862869c9e8e718dfa8` |
| multiply color | `40C0A0` | 81 | `c08882c69cc9bf6a40c4a56c6582a395fdfa8b6877f1307ce7908a9f2e6428b1` |
| render offset | `40BE20` | 153 | `034cc1a7433d4a14fc19fb3f68b6c93da064d5921fb0ad85bb34b121712807fe` |
| render through object | `40BD10` | 258 | `892e3e6af0f986d453880d296e5f5a67a77f38139a826374f072247ac93c0ac6` |
| render offset through object | `40BEC0` | 274 | `68697e5a9260739c2a53e6c6ec5c93c797beb693d322881958c20ad137c6f127` |
| find object | `40CC50` | 121 | `4105453da67949f2c03a21cadf4233fefb0fcc3cd3d10b578938979fd3386e7f` |

## Observed target behavior and corrected ABI

All callable spans close through complete reachable raw CFGs and ordinary RET
boundaries. The six new functions have respectively 36/36/59/92/97/49
instructions. CDesignBase RTTI `.?AVCDesignBase@@`, COL `6D7594` and primary
vtable `6C08AC` own the five virtuals through cells
`6C08B4/6C08B8/6C08C8/6C08CC/6C08C4`. The two render-through methods directly
call the lookup at `40BD27/40BED7`; lookup calls the native tree helper at
`40CC72 -> 40CDA0`.

Color methods use local checked iterators over list +14, reload end/head +18,
and forward to object slots +8/+C. Render methods resume the checked member
iterator +2C/+30. Offset rendering dispatches two floats through object slot
+10. The through methods render the stop object inclusively and increment
before breaking. They reset to begin only when reaching end; otherwise the
next member position persists for subsequent render calls. A failed lookup
writes null, so traversal continues to end unless an element itself matches.

The old header's `move(float,float)` at design slot +18 was wrong: `40BEC0`
pops twelve bytes and takes x/y/ID. The old `move_mode(float,float,int)` at
+1C was also wrong: `40BE20` pops eight bytes and takes only x/y. These slots
now declare `render_offset_through` and `render_offset`; slot +20 is
`render_through`. No vtable order, member size or offset changes.

Lookup uses ECX for the owner and RET8 for output-pointer/ID arguments. It
searches the unsigned-key map at +20 and writes either null or the mapped
object through its first argument. Source `int object_id` causes the native
unsigned-key temporary observed in the target. This supported source spelling
does not uniquely establish the original nominal ID type or source API.

## Real compiler-library boundary, without an ABI shim

The natural lookup source initially calls a CIL-owned native `map::find` that
LTCG specializes to a private register protocol. The target retains the shared
ECX/RET8 result-buffer/key-reference boundary. An ordinary COFF explicit
instantiation of the **actual pinned native tree's find member** preserves
that boundary before CIL linking. The provider is
`src/library/UiDesignObjectMap.cpp`; it contains no replacement implementation,
register annotation, source bytes or authored game function. Instantiating only
the needed member keeps the library input to about9 KB.

| Lookup key source | Tree find context | Complete lookup result |
| --- | --- | --- |
| unsigned ID | CIL only | 109/121, nonexact |
| signed ID, unsigned key conversion | CIL only | 117/121, nonexact |
| unsigned ID | real ordinary COFF member | 113/121, nonexact |
| signed ID, unsigned key conversion | real ordinary COFF member | **121/121 exact** |

All four controls also preserve the complete five other new virtuals and
existing render. The combined lifetime/visibility evidence, rather than a
size guess or a forced register declaration, selects the final source. All
seven formal functions have independent source-owned export/map/CFG bounds.
Named REL32 fields replay to the observed callees; no absolute game-data
reference, artificial alignment, assembly or inert storage is added.

The compiler helper at `40CDA0` is **find**, rather than lower_bound alone:
after lower-bound traversal it checks the key in the reverse direction and
chooses end on inequality. Pinned VC8 `xtree` lines959..965 corroborate that
algorithm. Its 105-byte native COFF provider is **105/105 nonexact at+8**;
no compiler exact or authored credit is claimed. Existing exclusion ownership
is unchanged. Its historical origin-rule ID is retained, with corrected prose
and new target body-hash/exact-owner call witnesses. The game lookup's full
121-byte exact result does not imply the provider body is exact.

## Replay, records and remaining work

The shared header's complete quoted-include closure selects 14 actual units.
All **44 predecessor accepted functions** remain exact, including the existing
render; the focused expanded unit also compares all six new functions. No
unrelated unit or cold aggregate replay is claimed. All197 origin-rule
selectors are unchanged and disjoint from the six newly accepted addresses;
only the amended compiler rule's new witnesses need evidence replay.

`functions.csv`, `function-origins.csv`, `reccmp-functions.csv`,
`implemented.csv` and `matches.csv` record the six complete acceptances.
The source remains in `DesignBaseRender.cpp`, with corrected declarations in
`DesignBaseLifetime.hpp` and the native compiler-library provider separate.
Raw span/vtable/caller facts, four controls, formal comparisons and all affected
replays are below `build/design-base-virtuals-20261021/`; private recipes are in
the same-named `.analysis/` folder. IDA preflight rejects its wrong-target
session; no Ghidra, database mutation or target patch is used. Builds run
serially on CPU0 at nice10.

Original source/TU spelling and exact compiler-helper bytes remain open.
The 2666-byte CDesignBase loader `40B000` still has no selected provider body;
its full implementation and the cleanup method `40BB40` are the next larger
class-closure work. Reimu496540 remains nonexact at+31.
