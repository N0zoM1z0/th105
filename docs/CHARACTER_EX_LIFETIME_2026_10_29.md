# CharacterEx destruction, JP1.06a

Two complete canonical matches are now accepted:

- Normal destructor491BC0:11/11, SHA256
  8a3d388058882e830c54eef91f4ac4273e89caea1872781ace4f6ee0316e401e.
- Scalar deleting destructor64B770:36/36, SHA256
  da85bd1331540f98efa1a89c4567591ef6a47008e7a7f40b3b552d731ce4a2d8.

Only47 new bytes are counted. The905-byte Character base destructor462CE0
remains an external declaration and receives no source or exact credit here.

## Independent class evidence

Vtable6C3F94 has COL6D9B10/type descriptor6E7D84 naming CharacterEx. Its
hierarchy places CharacterEx, Character, AttackObject and AnimationObject
on the primary prefix, AnimationObjectBase at+4 and Environment at+130.
Its first slot contains64B770. The independently known Reimu table6C412C
also shares that deletion entry; this is not inferred from address adjacency.

491BC0 republishes CharacterEx's table then tail-enters Character destruction
at462CE0.64B770 performs the same base lifetime sequence, then conditionally
calls operator delete6898EA when flags bit1 is set and returns this with RET4.
All11/36 bytes are the complete compiler sections, not prefixes or wrappers
whose ownership is inferred solely from byte shape.

The natural derived destructor emits both bodies from the same ordinary TU.
Its destructor-only base interface is abstract: native Character table6C2BE4
has purecall689934 in slot0. These are narrow interface views; no complete
Character allocation or all-method vtable reconstruction is claimed.

That independently observed purity also corrects the constructor-facing
CharacterConstructorView destructor declaration to pure virtual. A fresh
constructor build remains byte-identical at557 bytes, with the same nine
nonexact store-order bytes. No accepted caller/header changed.

## Reproduction

scripts/repo-python scripts/build.py --unit exact-first-character-ex-lifetime --compare --json

Source:src/characters/CharacterExLifetime.cpp.
Formal receipt and raw hierarchy facts:
build/frontier-character-ex-lifetime-20261029/formal-build.json and rtti.json.
Constructor recheck:build/frontier-character-constructor-20261029/formal-pure-base.json.

Default CI and diff checks validate the final exact ledgers and progress.
