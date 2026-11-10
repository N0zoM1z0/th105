# Youmu intermediate base lifetime

## Independent evidence and source correction

Native primary Youmu vtable6C5144 has COL6DA8BC and hierarchy Youmu,
CharacterEx, Character, AttackObject, AnimationObject, AnimationObjectBase,
Environment. CharacterEx's own table6C3F94 has COL6D9B10. Character's
slot0 at6C2BE4 contains purecall689934, supporting the abstract destructor
interface already used by the accepted CharacterEx lifetime source.

The previous constructor view skipped CharacterEx. YoumuConstructor.cpp now
adds that real intermediate base, forwarding construction to Character and
using its already independently established empty normal destructor policy.
The existing CharacterEx normal body491BC0 republishes its own table then
enters Character462CE0. No manual vptr stores or Youmu destructor body are
introduced. Existing unknown storage remains a physical prefix view, not a
claim about the complete CharacterEx allocation or all its member types.

## Complete canonical results

- Authored constructor53B330 remains159/159, SHA256
  b62f24fc5c5b06c1cb9040a64f1dd80c6371305946ce87fd43918cc923fc9d83.
- Compiler scalar deleting destructor53B3D0 is now49/49, SHA256
  85f6a61bf7d6dd2e0681416059d3132c14ffc497a6006231aa36350ba0b05d88.

The latter has15 complete instructions through RET4 at53B3FE, cleaning the
actual deque at7D0 through420A80, then CharacterEx lifetime, Character teardown
and conditional scalar delete6898EA. All three code relocations and the actual
CharacterEx table binding are resolved canonically. No masked or prefix credit.
The implicit normal28-byte destructor is emitted but has no assigned native
identity or separate credit. No remote exception-body equality is claimed.

Raw complete destructor and RTTI facts: native.json in the same directory.

## Attribution and replay

The existing scalar-wrapper rule now covers142 / 4,740 compiler bytes. Its
51 selected owner units were freshly rebuilt serially after the changed source,
manifest and anchor digest, retaining full canonical and native-owner checks.
This is a bounded provenance refresh, not an all-exact cold rebuild.

Youmu's49 bytes move review to excluded, not to authored matches. Authored
exact1445/445336, source1647 and authored1667 stay unchanged. Excluded1950,
review410, mapped1815 and units768. The preceding141-wrapper accounting
correction remains historically valid; this is one newly proven compiler body.

Reproduce:

scripts/repo-python scripts/build.py --unit exact-first-youmu-constructor --compare --json
    scripts/repo-python scripts/scalar_wrapper_origins.py --check
