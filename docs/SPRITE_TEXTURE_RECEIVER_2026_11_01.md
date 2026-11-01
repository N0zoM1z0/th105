# Actual sprite texture receiver

The seven-argument texture method now belongs to the actual CSpriteEx class.
Its existing exact implementation takes an unsigned handle and six signed int
rectangle/pivot parameters. The five-argument wrapper, animation callers,
background constructors, event initializer and CSelect use that member directly.
The unrelated empty call views and nonconstructed derived receiver are removed.
This is a coherent source ownership improvement, not proof of unique original
source spelling or an old physical calling-convention mismatch.

The file-local rectangle helper remains in the same translation unit. Its
ordinary static stdcall declaration still generates the compiler-private EAX
receiver and RET24. No external shim, forced register, noinline or fake vptr
recipe was introduced. Public manifest symbol selectors and call bindings now
refer to CSpriteEx; addresses and physical argument slots do not change.

## Evidence and scope

Private signed-parameter-only and real-owner controls produced the identical
normalized CSelect main payload SHA256
76c04f844fb8c2d9d30293de2e1831edc3eeb9ab2acc442138825ddf43e64d33.
The selected source retains 13 differing bytes out of 4247, first at +2931
(0x00423D13). Full remote EH code461 and metadata188 compare exactly. Neither
main nor support regions receive new exact credit. BG02 and EventEffect remain
nonexact; changing the receiver does not qualify them.

The quoted-include closure contains122 manifest units. All99 units containing
242 accepted authored roots were rebuilt serially on CPU0/nice10 and compared
without regressions. The provider193, local helper261, wrapper37, animation
callers, BG04/BG16 and Select destructor845 all remain exact. Additional fresh
whole owner comparisons preserve the implicit sprite constructor16/callback7
and record cleanups8/15. The complete sprite RTTI/actual array-site gates pass.
Only after these reviews were the three normalized sprite source hashes and
the record gate's raw EffectSprite.hpp hash renewed. No validator was relaxed.

Private evidence: build/frontier-sprite-owner-20261101/ and
.analysis/frontier-select-texture-contract-20261101/. These are local generated
artifacts, not distributable source inputs. All changed C++ files retain CRLF.

Authored totals remain1431 functions/443916 bytes; source-present1636,
excluded2059, review313, units803. This commit supplies no new matching credit.
Do not repeat signedness/receiver spelling trials to attack the remaining
argument-load schedule without new independent source evidence.
