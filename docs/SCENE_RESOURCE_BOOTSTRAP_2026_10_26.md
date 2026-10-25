# Scene resource bootstrap 0x0043E2E0

The complete source hypothesis in `src/engine/SceneResourceBootstrap.cpp` builds
as `exact-first-scene-resource-bootstrap`. Full canonical replay compares all
3722 bytes and leaves **11 unequal stack displacement bytes**. It remains
identified/unselected: neither `implemented.csv` nor `matches.csv` gains a row.
No exact authored bytes or functions are added.

## Observed target evidence

Only original Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
was inspected. IDA preflight again rejected the different GUI executable;
no IDA analysis or byte writes were used. Raw PE decoding closes the entire
`43E2E0..43F16A` extent, SHA-256
`6ed872ce668bf9f01a571e00f18e0879828a40ef79c854fc2f5a5f22efeccb4c`.
All3722 bytes decode into823 instructions,821 reachable. The two unreachable
operations at43F006/43F00D are pinned internal alignment. There are no escaping
edges or indirect jumps. The sole RET0 is43F169; six INT3 bytes separate43F170.
The exact162-byte scene-manager initializer41E070 calls this root at41E104
(`e8d7010200`). The frame aligns ESP to8, allocates210 bytes, and uses GS/EH.

The root performs game-specific startup policy:

- It mutates15 local16-byte character names by decrementing every non-NUL byte,
  then inserts into the character-name map6FCF70. Its order is reimu, marisa,
  sakuya, alice, patchouli, youmu, remilia, yuyuko, yukari, suika, udonge, aya,
  komachi, iku, tenshi. It recomputes strlen inside the character loop.
- Stage map6FC60C keys0..14 receive
  `0,11,12,13,14,15,16,17,0,5,18,3,2,4,5`. BGM map6FCA3C receives
  `10,11,12,13,15,14,17,16,18,19,20,21,22,4,5`.
- Effect map6FBF14 receives keys0..9 with100..190, then17 with200, then10..16
  with210..270. These three maps call the same185-byte insert4606E0 48 times.
- Key table6FC618 is reset and registers13 keys:
  `1,59,60,61,62,63,64,65,66,67,68,87,88`.
- A52-byte zeroed binding record receives signed source=-1, directions
  `200,208,203,205`, and seven button DWORDs `44,45,46,30,31,32,1`.
  Assign-profile409D60 copies it to keyboard6FBD60; deque push6183F0 enqueues
  that pointer in the combined input's actual member6FCF80+60.
- The same binding record is cleared and receives buttons0..6. Vector6FCA2C
  assigns input-limit702B48 copies of a104-byte temporary. Base constructor
 409CF0, inputEx vptr6C1154, byte+64=0 and WORD+60=0 are observed. **WORD+62
  is not initialized here.** Base destructor409D50 follows vector assignment.
  Each entry gets its source index/profile and is enqueued through6183F0;
  the invalid-range guard remains present. The larger44D8F0 constructor
  independently shows the same base/vptr/+60 pattern with flag+64=1 and no
  +62 store, without proving this temporary's original nominal type.
- Two selected pointers6FBD3C are cleared and source bytes6FBD38 become FE.
  Profile UI43FCA0, auxiliary6654A0, profiles43BA10, common resources434AC0
  (receiver6FBD3A, RGB255/96/96), and score42F6F0 (receiver6FCC98) follow.
  Flag6FC608 controls SendMessageA(HWND702A1C,104,13,0). BGM percent6FC600
  scales through double arithmetic by0.01f and0.75, rounds to float and calls
  service7026E0/403A30. SE percent6FC604 goes to43B1F0.

The full game policy and actual exact caller establish authored ownership.
That does not transfer authored or library-origin credit to any provider.

## Source and ABI inferences

Private complete base/inputEx views retain virtual destructor/update order,
96/104-byte sizes,52-byte bindings and40-byte hold counters. The retained
InputManager type lacks the base-constructor declaration and has a different
virtual declaration shape, so it is not instantiated unchanged. A pointer-only
member interface describes the independently called deque provider6183F0:
this in ECX, one pointer-reference stack argument and RET4. Its actual body
calls Growmap618290 and allocates16-byte pointer blocks. The member belongs to
the combined input object; it is not an independent global owner.

Eight independent scalar button fields are a same-layout source hypothesis.
They remove the local binding array's GS-buffer classification and recover
native string/temporary placement without padding, attributes or inert locals.
This result does not establish the original field spelling. The declaration
leaves resolved_mask+62 uninitialized because the target does so.

The effect map has DWORD comparisons and DWORD values in this root. Its local
`map<int,int>` projection is not a unique nominal-type claim. Existing accepted
char-key getter declarations and shared headers/bindings are unchanged. VC8
may pool the185-byte insert across compatible8-byte pairs/24-byte nodes;
this work does not establish a unique original specialization or LTCG boundary.

## First whole comparison and finite controls

Every row is a complete compiling source, immediately replayed over its entire
COFF section. Trial sources, objects, canonical bytes and JSON are retained
privately under `.analysis/exact-first-43e2e0-20261026/` and
`build/exact-first-43e2e0-20261026/`. Oversize candidates are diagnostic whole
section comparisons; they do not enlarge the accepted target boundary.

| Complete source/control | Bytes | Unequal positions | Interpretation |
| --- | ---: | ---: | --- |
| First complete source |3895 |2659 | Initial strict attempt first stopped at unqualified EH; full qualification then exposed inlined second deque push |
| Independent actual deque provider |3744 |2494 | Both call sites now use6183F0 |
| Earlier binding lifetime |3744 |2494 | Byte-neutral; retained and closed |
| Separate keyboard/gamepad binding scopes |3712 |2597 | Negative control, frame1F0 instead of210 |
| Same52-byte scalar binding view |3722 |92 | Native local buffer/temporary placement recovered |
| Only observed inputEx initialization |3722 |11 | Removes incorrect extra WORD+62 initialization |
| Signed device index |3722 |11 | Byte-neutral |
| One index reused across both loops |3722 |11 | Byte-neutral; finite counter/storage lane closed |

The final three controls share canonical SHA-256
`dd302ab4d718d3e410fedf672ea3caa5aadf75ba1daf3bdcf86e363d0ded2486`.
Public source keeps the observed-constructor version. The11 differences are at
43E63F,43E6BC,43E7D9,43EF4F,43EF59,43F001,43F072,43F083,43F08F,43F098,
43F09D. Character index/keyboard-pointer temporary/device index use native
ESP+28 versus candidate+14; the device-entry pointer temporary uses native+14
versus candidate+28, including call-time ESP changes. All remaining bytes agree
after full relocation replay. This is not a100% result. No new flag, spelling,
volatile, lifetime or visibility grid is justified by the neutral controls.

## Relocation qualification and reproduction

All actual REL32 providers, EH, vtable, globals and initialized literals are
qualified by the ordinary comparator. Thirteen genuine encoded string objects
have full initialized COFF/PE byte identity. Twenty nonzero-addend references
use the existing addend-specific DIR32 override syntax and independently pinned
literal slices of the actual operand width. Each slice remains relative to its
original object base. This avoids incorrectly requiring a full seven-byte
string payload at an interior six-byte offset; it does not waive any operand.
The public audit independently decodes all33 actual literal loads and rejects
any read crossing its full initialized object extent. No comparator changes,
relocation masks, copied code, assembly, fixed stack homes or buffer padding.

```bash
scripts/repo-python scripts/audit-scene-resource-bootstrap-target.py
scripts/repo-python scripts/build.py --unit exact-first-scene-resource-bootstrap --compare --json
scripts/repo-python scripts/audit-scene-resource-bootstrap-target.py \
  --object build/match-units/ExactFirst_SceneResourceBootstrap.obj
```

Target-only audit exits0. The build/object audit report nonexact and exit1 as
expected. Public receipts: `formal-first.json`, `formal-second.json`,
`public-target-audit.json`, `public-object-audit.json` in the build directory.
The full `scripts/repo-python scripts/verify-exact-units.py --all` replay passes
525 cold accepted units/all1413 functions; receipt `cold-all.log` is in that
same build directory. Exact authored totals remain1413 functions/382816 bytes.

Original variable identity, stack allocator/TU context, nominal map/input types
and original source spelling remain unknown. The lane is parked until new
independent evidence explains those stack homes.
