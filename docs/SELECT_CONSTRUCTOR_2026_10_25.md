# Complete CSelect constructor and remote cleanup

`CSelect::CSelect @ 0x004231A0` now has complete reviewed ordinary C++ source
in `src/ui/SelectConstructor.cpp/.hpp`. The formal and independent fresh builds
both produce **4247/4247 main bytes with 13 unmasked differences**. All **461
remote EH code bytes and 188 EH metadata bytes agree** after relocation replay.
This is source-present, **not exact**. No matches.csv row or partial exact credit
is added. Preserve this residual and switch candidates after the finite controls
below; neither compiler-profile impossibility nor original TU ownership is proved.

## Target observations

Only Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Fresh target/status/target-required tracking checks pass. IDA preflight
again rejects GUI executable SHA `10350095...`; no IDA calls or writes follow.
The implementation was manually derived from all 1149 raw PE instructions,
with the pre-existing RTTI/caller/EH origin pins independently read back.
No Ghidra process is launched for this scope.

The main span is `[4231A0,424237)`, SHA256
`9b34d6dea240fd40eede0bba84ffd3a81daeeea29dcf98296b19ee83d5551bea`.
CFG traversal reaches 1148 instructions/4241 bytes, closes at RET0 `424236`,
and has no visible outgoing normal branch or indirect jump. The sole skipped
six-byte LEA at `4239AA..4239AF` remains in the full comparison. The existing
`select-base-constructor-authored-106a` rule pins this boundary, CSceneBase and
CSelect RTTI vptr writes, exact derived constructors `41E160`/`41E1C0`, the
exact factory's call `41E45F`, and all 19 remote cleanup states/actions.

The factory allocates `0x2ED8` bytes; the selected constructor-only physical
view asserts this size and member offsets. The input member at `+18` is
RTTI-identified **CInputManagerCluster**, size `78`, with the accepted `60`
byte base and native checked deque. It is not the smaller CInputManagerEx.
Other real members include three checked int vectors, two native strings,
two CDesignBase owners, sprite/tile arrays, 30 effect managers and two guides.
Their ordinary lifetimes account for all 19 unwind states without manual EH.

Remote regions are not included in the main callable ledger size:

| Region | Target address | Bytes | Canonical SHA256 |
| --- | --- | ---: | --- |
| 19 cleanup actions + handler | `6B7380..6B754D` | 461 | `2ca5bebe7eed1a590f097ed2c30450f3e27bcff90e75ee6996e52b53cd01c2f1` |
| FuncInfo + 19-entry unwind map | `6DD6CC..6DD78C` | 188 | `b5e889978983af7d8b0d1d06b21923a9e0e149bcd161852a9eb49ea0220dcab0` |

The handler starts at `6B751F`, after 415 cleanup bytes. The native COFF owns
these in `.text$x` and `.xdata$x`. The ordinary main comparator's `.text`
restriction is unchanged. The dedicated diagnostic replays every relocation
in both EH sections and compares their complete tails, including all nonoperand
bytes. It verifies all 19 actual defined funclet identities/offsets and both
metadata owners against the pinned target contract. Unsupported, overlapping,
out-of-range or unbound operands block the diagnostic. Five target-free tests
cover late relocations, absolute pins, overlap/escape, operand roles and tails.

## Complete source behavior

The body constructs its nested owners before loading character/background UI
resources. Network presence chooses the two selection-record pointers and
flags source; offline flags also set the `+93` gate. It binds IDs100..115,
hides two entries for that gate, and populates the three selection vectors with
16, 7 or 5 entries according to the observed flag tests. The third vector uses
the actual third table only on the 16-entry path and -1 on the other paths.

Two cursors use IDs200+i/300+i. The constant ID400 object supplies the back-
sprite anchor. Both back sprites deliberately consume the dimensions from the
second texture load. Background picture/name arrays follow checked vector
indices. IDs100/200/300 of the background design become three anchors; IDs500..
502 become three bound objects. The mode4/5 tests retain two separate calls.
Guide loads are 3/4 or 90/91. The final 15-iteration loop loads each palette
and stand pattern and spawns two effects on the first of each manager pair,
using the actual double32/double8 coordinate additions and direction/side args.

All physical direct-callee counts agree, as do one RET, 10 genuine virtual
calls and five USER32 `wsprintfA` IAT calls. This inventory is corroboration;
the byte comparison remains decisive.

## Evidence-backed source trials

Each row compares the whole source immediately after that change. Private
receipts and original source snapshots remain under
`.analysis/exact-first-select-base-ctor-20261025` and
`build/exact-first-select-base-ctor-20261025`.

| Question / control | Main bytes / differing bytes | Canonical main SHA256 prefix |
| --- | --- | --- |
| First complete source; explicit scalar result slot | 3880 / 3831 | `0d73d5f2` |
| Real four-byte handle value members restore all zero initializations | 4231 / 1124 | `a574665c` |
| Independent map-result stores preserve observed empty/nonempty arms | 4247 / 1006 | `b52ac22c` |
| Actual native `find_object` helper visible at constant-ID inline sites | 4247 / 280 | `08c173df` |
| Natural hidden class results from texture loader | 4247 / 60 | `5561538d` |
| Put two handle assignments inside call arguments | byte-identical / 60 | `5561538d` |
| Actual virtual dispatch instead of the old function-pointer facade | 4247 / 13 | `76c04f84` |
| Pass the back-texture handle as a four-byte class value | byte-identical / 13 | `76c04f84` |
| Make the accepted five-argument CSpriteEx wrapper visible | byte-identical / 13 | `76c04f84` |

The first object was compared immediately; an unknown handler binding was
resolved from the existing target-pinned EH records before any source tuning.
Its first 415 cleanup bytes and all 188 metadata bytes already agreed. Its
handler differed at two frame offsets. Scalar handle arrays had omitted three
two-element zero initializations and emitted two target-absent memset calls.
The existing `DesignTextureHandle` value model naturally emits every observed
store; no unrolled byte/store recipe is inserted.

`404C90` writes and returns its first stack argument and closes both exits with
RET16. The natural four-byte class-return view produces the observed hidden
result argument without an explicit long-lived scalar local, restoring the
`1C8` frame and every EH offset. Native virtual dispatch fixes two artificial
argument/vptr scheduling sequences introduced by UiSprite94's inline function-
pointer facade. Header/type changes are confined to this new constructor TU.

The retained main SHA256 is
`76c04f844fb8c2d9d30293de2e1831edc3eeb9ab2acc442138825ddf43e64d33`.
The 13 differences are within `423D13..423D28`: the seven-argument call to
`407160` loads the back handle and width/height in a different register order.
Both paths push handle, zero, zero, width, height, zero, zero and use the same
receiver; no intervening stores/calls alter those inputs. Every byte outside
this small argument sequence agrees. The two last complete controls reproduce
all main/EH payloads byte-for-byte; close these parameter/wrapper questions.
No assembly, fake dependencies, forced registers or inert storage is used.

## Scope and unknowns

Original nominal handle/helper names and TU partition remain hypotheses. The
visible `CDesignBase::find_object` definition is the same real checked-map
behavior as the accepted method. This object emits an unaccepted 118-byte
standalone helper versus the separately accepted linked121-byte method; that
emission receives no implementation/matching credit. Only CSelect is selected
by this unit. This is not a recovered whole-program link boundary.

The palette receiver is observed as ECX `7028D8`. The source takes the address
of the existing one-byte `g_bootstrap_mode` alias and uses a pointer-only call
view. It does not invent another complete global owner at that address. The
palette data alias pins an observed prefix, not the unknown whole extent.
All local views/unused member gaps express observed ABI/storage; none are used
to force stack padding. Callee declarations confer no implementation credit.

## Reproduction and next scope

Run serially on CPU0 at nice10:

```sh
scripts/repo-python scripts/build.py --unit exact-first-select-constructor --compare --json
scripts/repo-python scripts/audit-select-constructor.py
TH105_ENABLE_GS=1 TH105_FP_MODE=default TH105_INLINE_MODE=default \
  scripts/compile-unit.sh src/ui/SelectConstructor.cpp build/select-cold.obj
scripts/repo-python scripts/audit-select-constructor.py --object build/select-cold.obj
```

The comparisons intentionally return1 while the main is nonexact. Formal and
fresh independent builds agree on all three region hashes. Source selection
raises source-present1543 to1544 and mapped1562 to1563; exact stays1403/359740
bytes. No aggregate cold replay is claimed. Only new exclusive data aliases
and function-local bindings are added; prior accepted keys are unchanged.

A read-only ledger census finds no other source-missing authored candidate in
4096..17999 bytes. Next select the complete medium representative `491C40`
(provisional3785 bytes, RTTI-owned Fighter primary virtual), with fresh target/
CFG/call/ABI review. Keep the CSelect residual parked absent new independent
evidence instead of cycling through byte-neutral argument spellings.
