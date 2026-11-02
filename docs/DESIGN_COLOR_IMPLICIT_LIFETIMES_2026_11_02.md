# Shared design color interface and compiler-only default lifetimes

## Source and independently bounded controls

DesignColorLifetimeView is now an alias of the existing global IColor, rather
than a separate interface with identical layout. CDesignBase remains34 bytes
with its existing vector/list/map/iterator members. CSelect calls the actual
CDesignBase::load virtual method directly; its two SelectDesignCall surrogates
are removed. No signature, algorithm or virtual slot changes.

Three sequential controls distinguished independent properties:

1. Actual IColor alias alone preserves constructor153, destructor154, deleting
   wrapper30, CSelect constructor4247/13 and CSelect destructor845 exactness.
2. Removing the old artificial `destroy_design_base_for_lifetime_probe` caller
   still emits all three canonical lifetime bodies from ordinary construction.
3. Removing the explicit CDesignBase constructor declaration/body too, and
   compiling the existing real SelectConstructor.cpp, naturally emits the
   entire implicit default constructor153, destructor154 and scalar30. The
   complete CSelect parent remains4247/13, not a new matching parent.

The accepted lifetime unit keeps its identity but now selects actual emitted
symbols from SelectConstructor.cpp with the same ordinary /O2/GS profile.
DesignBaseLifetime.cpp is removed. There is no new emission-only helper,
artificial owner, force-inline/outline barrier, raw vptr recipe or byte stub.

## Conservative accounting correction

The two normal lifetimes at4217F0/153 and421890/154 contain only compiler-managed
member construction/destruction. Their zero-difference comparisons remain
valid, but their307 bytes are no longer credited as authored game code.
Original explicit-empty versus implicit source spelling is not claimed unique;
the generated machinery carries no independently authored behavior.

The source-pinned `implicit-design-base-lifetimes-106a` rule selects exactly
these two bodies. The existing generic implicit-member gate gains an explicit
`default_constructor` kind limited to the parameterless ordinary-thiscall
mangled suffix; wrong argument/copy/private signatures are rejected. No
threshold or byte mask is introduced. The normal destructor stays implicit.

Only these two ledger rows are reclassified and removed from implemented.csv
and matches.csv. The already-excluded scalar30 remains excluded. Named mapping,
source selection and canonical proof remain available. New totals:

- Authored exact1427 /443604 bytes, previously1429 /443911.
- Source-present1634, authored1653, excluded2074.
- Mapped1823, review300, provisional4027, units812 unchanged.

This is an accounting correction, not a code-match regression or progress gain.

## Native ownership and complete verification

`audit-design-color-owner.py` verifies whole153/154/30 bytes from the real owner,
all ten virtual roles in native table6C08AC/40, primary native CDesignBase RTTI,
and its one zero-offset IColor base. The actual shared global IColor metadata
matches all93 unique bytes. Both native CSelect member-construction calls to
4217F0 match source relocation roles. Complete namespace-qualified derived
CDesignBase RTTI, loader EH and whole-executable linkage are not claimed.

The actual include closure is44 units. Before withdrawing the two generated
roots,34 units/70 then-accepted roots were freshly replayed with zero changes;
after withdrawal that set retains33 units/68 authored roots. Source-only
neighbors were also compared. Existing loader40B000 unresolved EH symbol and
scenario458440 unresolved string-constructor boundaries remain blocked;
explicit pre-change-header builds reproduce those same blockers. They are
not counted as successful comparisons.

The existing record-cleanup gate2/23, implicit CSpriteEx gate and scalar30
owner proof were freshly rerun. Constructor EH461/metadata188 remain exact.
All eight CSelect owner body hashes, four guarded render cases and12 guarded
character cases/negative controls remain stable. Four new design-table tests
check virtual roles, full extent/addends and all40 native slot-byte mutations;
two generic-gate tests cover valid and invalid default constructors.

Private evidence: `.analysis/frontier-design-color-20261102/` and
`build/frontier-design-color-20261102/`. No global origin-ledger rewrite,
whole-corpus rebuild, IDA semantic reuse or push; native jobs serial CPU0/nice10.
