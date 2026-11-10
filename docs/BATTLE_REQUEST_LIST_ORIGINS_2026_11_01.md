# Battle render-request list growth

## Complete canonical proof

The unchanged BattleObjectStage.cpp owns actual std::list<BattleRenderRequest>
at manager+0. The record has unsigned kind and float value, eight bytes total.
Native exact publisher467850 calls push_back466DB0 at46789B. That50-byte helper
calls value-node allocation466940 at466DC4 and checked growth466D10 at466DCF.
The value-node59 and push50 were already excluded under older template proofs;
they receive no new attribution credit here.

Fresh unchanged source with GS enabled emits the complete native160-byte growth
body, including its security cookie and length_error lifetime. The old accepted
publisher unit retains its original GS-disabled profile, and fresh120-byte
publisher comparison remains exact. The new compiler-only unit uses the actual
native GS requirement, not register/ABI/source spelling controls.

Canonical whole-body results:

- 466D10 growth160: 2a0576a09d944559a7836dbcace49c147a32b1c255241d50e6316aaf11437226.
- 466DB0 push50: 06ec25e7c863f54549cadf590b6020aa924159284c2f57d4b55441484244f7be.
- 466940 node59: 6648d4c6e9643c98b3902f16ef298d5703037138b2c98227e320a4ccd3e39e8f.

All code/data relocations are resolved; no masks in the formal canonical proofs.
The separate origin fingerprint retains .70 coverage,24 nonrelocation bytes,
zero alignment-tail tolerance and full-inventory uniqueness, with every named
call target checked. Growth has128 nonrelocation bytes of160.

## Exception ownership

The maximum count is1FFFFFFF, consistent with the actual eight-byte record.
The native literal at6D6968 is `list<T> too long` including its NUL terminator.
Growth constructs std::logic_error through401670 before publishing length_error
vtable6C0888 and throwing through68A153. Native length_error COL6DC82C and
logic_error COL6DC87C independently identify those types. ThrowInfo6E3BE0 has
three catchable records: length_error40, logic_error40 and exception12, all
primary displacement0 and nonvirtual base displacement -1. Their copy routines
are402570,4017A0 and689F82. These helper identities do not claim the two
still-review logic_error bodies are exact.

The source-emitted exception labels bind to the actual metadata, literal and
cookie. Handler6BC8B8 has a16-byte address-ownership witness only; remote EH
cleanup/FuncInfo equality is not claimed or credited. Complete ordinary growth
flow ends in RET4; the error branch calls the known noreturn C++ throw routine.

## Accounting and checks

Only growth466D10 moves review to compiler-generated/excluded. Excluded1951,
review409; authored exact1445/445336, source1647, authored1667 and mapped1815
remain unchanged. Units769. No source C++ changes, authored helper credit,
all-exact rebuild or push.

Reproduce:

scripts/repo-python scripts/build.py --unit exact-first-battle-request-list-runtime --compare --json
    scripts/repo-python scripts/build.py --unit cross-v106a-battle-object-stage --compare --json

The new generated-origin rule independently passes its entire selected count160,
body hash, caller edge and complete inventory uniqueness checks.

## Bounded preceding negative

A genuine cutin/release CIL context combined unchanged FighterCutinLifetime,
DesignBaseCleanupLinked and actual EffectSpriteColors providers. The complete
cutin remains95/native96 with the same handle-load/EH scheduling residual.
No unsupported DIR32/EH/RTTI linked gate was relaxed. This is a closed negative
experiment, not a new cutin reconstruction or acceptance.
