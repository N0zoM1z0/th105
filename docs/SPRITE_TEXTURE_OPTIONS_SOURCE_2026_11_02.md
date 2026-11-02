# CSprite texture options: complete source, not exact

Target is original Japanese TH105 v1.06a, SHA-256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Native ownership and boundary

0x406A90 is a complete 334-byte body ending with RET28, 100 instructions,
one direct call at 0x406ACD to texture-size query 0x404E60, no indirect calls.
The primary CSprite table at 0x6C0668 owns it at slot 0x6C0678. COL slot
0x6C0664 points to 0x6DCCDC and type descriptor 0x6FA52C names CSprite.
The adjacent slot owns the independently exact 39-byte set_texture wrapper.
The authored-origin rule pins the complete body hash, RTTI and query edge.

Native body SHA-256:
cef4fe718e7b4a273a2644a8a1a781a6412fdb70a7e0f8bdd31c27471990e3af.

## Source and bounded observation

src/ui/SpriteTextureOptions.cpp defines the existing real CSprite virtual.
Signed rectangle dimensions and pivots are converted and stored before the
texture-size query. The query receives manager 0x702798 and the original handle;
width and height outputs reuse consumed argument storage. Corresponding signed
and unsigned integer aliasing is used, with no fabricated stack object or ABI.
UV corners use integer x+width / y+height followed by unsigned texture extent
division. Four colors become white, Z becomes 0.5, RHW and scales become 1,
and angle becomes zero. XY and the vptr remain untouched.

The pinned VC8 O2 strict-FP unit emits all 334 bytes, but first differs at
+149 (0x406B25), with a UV spill/store scheduling residual. Canonical source hash:
016ffee9797eb505250a078eeb30134111a148eaba4a6dd10679dfebed3795f2.
No source spelling, flag, fake local, ABI or register grid was attempted.
The previously closed exactness lane remains closed.

scripts/audit-sprite-texture-options.py freshly checks the selected object and
executes both complete bodies under six finite modeled texture-query returns.
Cases cover zero/nonzero/high-bit handles, signed coordinates/dimensions/pivots,
and high-bit unsigned extents. Every complete 0x94-byte object agrees with the
independent expected result. The guard checks the exact 28 dword write footprint,
query receiver/arguments/pre-query publication, RET28 and nonvolatile registers;
volatile registers are poisoned at the helper return. A mutated handle-store
address is rejected by the guarded write callback. Wrong output also rejects.
Four focused tests check preserved coordinates, query identity/count, missing or
duplicate writes, and the unsigned-extent UV corner.

This is not actual texture lookup, COM/OS execution, arbitrary aliasing,
overflow, FP exception or universal equivalence proof. Both native and source
closed CFGs are checked. The source is available for future genuine provider
visibility work, not evidence of the original translation-unit partition.

## Reproduction and accounting

- scripts/repo-python scripts/build.py --unit exact-first-sprite-texture-options --compare --json
  returns comparison_failed (expected; not an acceptance receipt).
- scripts/repo-python scripts/audit-sprite-texture-options.py
- scripts/repo-python -m unittest discover -s tests -p test_sprite_texture_options.py
- scripts/repo-python scripts/ci.py

No shared header or existing source unit changed, so no accepted consumer was
invalidated. Only the selected source-present and authored-origin rows change.
Exact stays 1426 / 443399 bytes. Source 1637, authored 1656, mapped 1827,
review 295, excluded 2076, units 814. No matches.csv addition.
Private build/audit evidence is in build/frontier-sprite-options-source-20261102.

Scoped authored-origin validation passes 1 / 334; corrupted whole-body hash,
wrong vtable slot and wrong type descriptor are all rejected. Full default CI
passes 966 tests in 102.751 seconds. The earlier global origin --check timed out
without a receipt; no global origin replay or success is claimed.
