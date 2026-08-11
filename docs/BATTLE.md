# Battle core map

This note is the entry point for agents working on gameplay rather than menus,
audio, or input plumbing. Addresses and phase ordering below are observed in the
original Japanese v1.06a target. Semantic names remain reconstruction names
unless explicitly supported by RTTI.

Use `docs/BATTLE_SIMULATION_SYSTEM.md` for the breadth-first controller tree,
one-hop dependency expansion, boundary gate, and exact-worker frontier. This
file retains the detailed collision, hit, spell-runtime, and phase algorithms.

## Active-frame order

The active battle-state controller dispatches each frame through `0x00470940`.
Active round states execute the following stable sequence:

```text
manager virtual +0x40
  -> 0x0046A5B0  character action and owned-object update
  -> 0x0046D620  attack/projectile collision and hit resolution
  -> 0x0046C290  fighter body overlap and pushback
  -> 0x0046A5C0  position, status, and timer commit
  -> 0x0046A5D0  post-update phase
  -> manager virtual +0x30
```

State 1 uses the same surrounding update phases but omits `0x0046D620`; it is
therefore not yet an active damage phase. States 2 through 5 run the complete
pipeline when their state-specific gates allow simulation.

## Character update phase

`0x0046A5B0` enters `0x00463610`, which iterates active fighters and their
owned object managers. The Sakuya vtable provides concrete slot evidence:

- raw fighter vtable `+0x3C` is `0x004DDB20`, the action-change handler;
- raw fighter vtable `+0x40` is `0x00476520`. Older notes that called
  `0x004DDB20` slot `+0x40` counted the preceding RTTI locator cell and must
  not be used when reconstructing C++ virtual layout;
- the common update at `0x00459E50` reaches vtable `+0x50`, which is
  `0x004DEF70`, the input/action selector;
- fighter `+0x658` is the owned-object manager used during this phase.

The exact wrapper `0x0046A5B0` loads the context pointer from `0x006E623C` and
tail-jumps to `0x00463610`. That function makes five separate complete passes
over the fighter vector at context `+0x3C/+0x40`: fighter raw vslot `+0x40`,
owned-manager vslot `+0x0C`, fighter vslot `+0x28`, direct common update
`0x00459E50`, then owned-manager vslot `+0x10`. Every pass repeats the original
VC8 checked-vector bounds path and reaches `0x0067B884` on failure. VC8 places
the `std::vector` object at context `+0x38`; its allocator/pair base makes the
observed begin/end/capacity triplet land at `+0x3C/+0x40/+0x44`. Preserving
that layout produces an exact 323-byte reconstruction.

## Attack and projectile collision phase

The `AttackObject` base has vtable `0x006AEB44`. Constructors at `0x00461A90`
and `0x004927D0` first call its constructor at `0x0045E3A0` before installing
the `Character` and `CharacterObject` vtables. This establishes a shared
collision-data base for fighters and their spawned objects. The complete
193-byte constructor calls `0x00421310` on `this+4`, installs the AttackObject
vtable, and initializes directly observed fields through `+0x32C`. The callee
installs the `CEffectSprite` vtable `0x006AC72C` and resets fighter-action
scratch. Its cleanup tail-jumps to the exact seven-byte `IColor` destructor at
`0x0041EAA0`, and the compiler-generated `CEffectSprite` scalar deleting
destructor at `0x0041EB30` is exact across its 31-byte contiguous span. This
proves the RTTI chain `CEffectSprite -> CSpriteEx -> CSpriteBase -> IColor` at
the start of the embedded `this+4` object. The constructor source has the exact
79-byte size and behavior;
standalone VC8 differs only by swapping the derived-vptr and EH-state stores,
so final byte acceptance is deferred to the first linked LTCG island.

AttackObject RTTI independently proves `AttackObject -> AnimationObject`, with
`AnimationObjectBase` at `+0x04` and `Environment` at `+0x130`. The former owns
the `CEffectSprite` member at its own offset zero; `AnimationObject` ends after
the pointer at `+0x154`, for a size of `0x158`. Modeling the constructor-owned
AttackObject tail as the following inlined state subobject preserves the target
boundary between base initialization and derived field stores. The resulting
`0x0045E3A0` constructor is an exact 193/193-byte match.

Four adjacent shared methods are identified without assigning gameplay terms.
`0x0045AA10` and `0x0045AA30` call one- or two-argument helpers and then the
same virtual slot `+0x3C`; their addresses occur across AttackObject-family
vtables. `0x0045AA60` tail-dispatches one of 64 entries from a table at
object `+0x164`, while `0x0045AA90` forwards four arguments plus object
`+0x170` to the handler at `0x0046BBA0` through the battle root. Their call
order and fields are observed, but helper, slot, and table semantics remain
unknown.

`0x0046D620` clears and fills six per-side collision lists from current fighter
and object frame data. The complete observed orchestration is:

1. Free and relink all six transient lists, zero their counts, and clear the
   two deferred-result channels.
2. For each of two fighters, copy byte `+0x4E9` to `+0x4EA`, enumerate owned
   objects through the manager at fighter `+0x658` vslot `+0x24`, and classify
   eligible payloads into the three list families.
3. Insert the fighters themselves into family 0 and family 2.
4. Dispatch the collision passes in this order:

   - `0x0046D370` (`dispatch_family1_object_clashes`) enumerates active object
   pairs and calls `0x0046C070` for object-object clash handling.
   - `0x0046D160` (`dispatch_family2_against_family1`) resolves interactions
   between classified object lists through `0x0046BFD0`, falling back to
   `0x0046BF20` when not consumed.
   - `0x0046D040` evaluates every family-0 attack candidate against the
   opposing fighter.
   It performs shape overlap and state gates, then dispatches special outcomes
   or falls through to the general hit resolver at `0x0046B570`.
5. Apply the deferred per-player channels only after all family-0 fighter
   resolution has completed.

The complete orchestration now has maintainable source in `CollisionPhase.cpp`.
VC8 emits 1398 bytes versus the 1405-byte target and reproduces all 21 observed
checked-list failure calls. A narrow volatile view of the reset count reproduces
the target's `0x2C` stack frame; the first mismatch is now register allocation
at `+0x5`, where the target retains `this` in `EBP`. The remaining gap is
register/spill and reset-loop scheduling. Exposing the sentinel-slot lifetime
does recover the target-like `ESI=this+0x30` and `EBX=this+0x7C`, but it also
makes VC8 reserve `EBP` as a zero register and shrinks the function to 1382
bytes, so that diagnostic variant is not integrated.
The two internal list passes are likewise source-complete. `0x0046D160` emits
527/525 bytes with all 19 target failure calls, the target `0x28` stack frame,
and exact endpoint slots `+0x24/+0x2C/+0x34`; its first remaining difference is
register allocation at `+0x5`. `0x0046D370` emits 667/686 bytes after changing
its iterator to reload the owning list sentinel. It retains all 25 target
failure calls; explicit owner checks are rejected because they add two guards
rather than reproducing the target's enclosing iterator-owner lifetimes.
All three remain `implemented`, never `matching`, until the accepted comparator
reports exact bytes.

The former deferred-result dependency `0x0045BF10` is exact, while
`0x00454890` is verified VC8 standard-library code and tracked as `library`.

`0x0045AEC0` (`prepare_collision_geometry_from_frame`) now has complete source
in `CollisionPreparation.cpp`. It materializes each
fighter/object frame into collision-ready scratch before list insertion. It
caches the frame at object `+0x1A4`, transforms family-0 records into 16-byte
entries at `+0x204` with optional descriptor pointers at `+0x304`, transforms
family-1 records into `+0x1B4/+0x318`, handles the optional extension at
`+0x194`, and builds an optional primary entry at `+0x2F4/+0x32C`. Frame bits
`0x400000`, `0x800000`, and `0x1000000` select observed preparation modes; no
gameplay terminology is assigned. The integrated VC8 function is now 2162
bytes versus the 2156-byte target. The family-0 branch order follows the
target's descriptor-present fallthrough, its mirrored descriptor path performs
the four independently checked vector reads visible in the executable, and
the extension's nonzero-angle path now precedes its scalar path. Direct
pointer-slot assignments are intentionally unrolled in all three oriented
descriptor paths; collapsing them behind a cached output pointer loses target
alias/reload behavior. Strict comparison still stops on a defined
`vector::at` failure-path COMDAT. The current object uses a `0x34` stack frame
versus the target's `0x3C`, and the first target word copy still uses `MOVZX`
where the object uses a 16-bit `MOV`. Its
object-local `_Xran` helper is 106 bytes while the target helper reached from
the corresponding failure path is 123 bytes, so the internal relocation is
not treated as equivalent by name or exception string. Its ledger status
therefore remains `implemented` with no percentage claim.

Its three direct geometry leaves are exact reconstructions. `0x0045A190`
transforms a four-int local box with actor position at `+0xEC/+0xF0` and signed
direction at `+0x104`; every coordinate conversion deliberately executes
`ceil`, spills to single precision, and then calls `_ftol2_sse`. `0x0045A2E0`
repeats the same conversion sequence but swaps the local Y endpoints in the
mirrored-X branch.
The natural VC8 source reproduces their full 335- and 445-byte x87 spill
schedules exactly.

`0x0045A4A0` is a six-argument `__stdcall` builder for one four-int local box
and one four-int auxiliary descriptor. It evaluates the direct and
quarter-period-shifted orientation values, then uses four intentionally
unrolled sign quadrants and twelve `_ftol2_sse` conversions per path. The
quadrants select opposite rotated corners and emit the two edge vectors rooted
at the first corner. This complete source is an exact 1386-byte match. The
neutral reconstruction name is retained because the target proves the geometry
but not its original gameplay terminology.

All three compare exactly from the shared translation unit:

```bash
scripts/compile-unit.sh src/battle/CollisionPreparation.cpp build/wave18/CollisionPreparation.obj
python3 scripts/compare-function.py 0x0045A190 build/wave18/CollisionPreparation.obj
python3 scripts/compare-function.py 0x0045A2E0 build/wave18/CollisionPreparation.obj
python3 scripts/compare-function.py 0x0045A4A0 build/wave18/CollisionPreparation.obj
```

The paired orientation leaves are exact reconstructions. `0x00406680` indexes
`g_orientation_cosine_table[abs(angle * 10) % 3600]`; `0x00406650` indexes the
same table at `abs(angle * 10 - 900) % 3600`. Initializer `0x00406780` fills
the 3600-float table at `0x006E8E58` using x87 `fcos` at 0.1-degree increments,
which establishes the cosine and quarter-shifted sine roles. Their strict
comparison commands both report 100%:

```bash
scripts/compile-unit.sh src/engine/AngleLookup.cpp build/wave11/AngleLookup.obj
python3 scripts/compare-function.py 0x00406650 build/wave11/AngleLookup.obj
python3 scripts/compare-function.py 0x00406680 build/wave11/AngleLookup.obj
```

Terms such as graze, guard, spell, and armor must not be assigned to individual
branches until flags and live behavior prove them. At present, clash and general
hit roles are supported by the data flow; the finer result taxonomy is not.

### Collision scratch lists

The collision/list manager is `0xA8` bytes. Its six temporary lists are three
families for two player slots:

| Family / slot | List object | Sentinel pointer | Count |
| --- | ---: | ---: | ---: |
| 0 / 0 | `+0x2C` | `+0x30` | `+0x34` |
| 0 / 1 | `+0x38` | `+0x3C` | `+0x40` |
| 1 / 0 | `+0x44` | `+0x48` | `+0x4C` |
| 1 / 1 | `+0x50` | `+0x54` | `+0x58` |
| 2 / 0 | `+0x5C` | `+0x60` | `+0x64` |
| 2 / 1 | `+0x68` | `+0x6C` | `+0x70` |

Each list object is 12 bytes. `0x0046A7F0` allocates its persistent sentinel;
`0x0046D000` allocates transient 12-byte nodes laid out as `{next, prev,
CharacterObject *payload}`. `0x0046D620` frees all prior-frame nodes, relinks
the sentinel to itself, and resets the count without freeing payloads. Fields
`+0x74/+0x78` and `+0x7C/+0x80` hold deferred per-player results applied after
collision dispatch.

The target proves three geometry classifications but not their original game
terms, so documentation calls them families 0, 1, and 2. Family 1 feeds
object-object clash at `0x0046D370`; family 2 feeds object interactions at
`0x0046D160`; family 0 feeds attack-vs-fighter dispatch at `0x0046D040`.

Both object-list passes traverse sentinel links rather than their count fields.
`0x0046D370` performs a same-list pass for each player and then a slot-0 versus
slot-1 pass; the frame-flag filters are intentionally asymmetric between outer
and inner payloads. `0x0046D160` walks family-2 sources against family-1 and
tries `0x0046BFD0` before `0x0046BF20`. Neither pass touches the deferred-result
fields; `0x0046D620` applies those only after the family-0 fighter phase.

The three allocation/initialization leaves are now exact reconstructions:
`0x0041FEA0` creates a 12-byte self-linked sentinel, `0x0046A7F0` stores it
at list `+4` and zeros count `+8`, and `0x0046D000` creates a transient node.
The list field at `+0` is deliberately left unnamed because initialization
does not touch it.

The insertion helper at `0x00454890` is VC8
`std::list<pointer>::_Incsize`: it checks `0x3FFFFFFF - count` against the
requested increment, throws `length_error("list<T> too long")` on overflow,
and otherwise increments list `+8`. This is compiler/standard-library code and
is excluded from authored reconstruction progress.

### Frame-flag result leaf

`0x0046BE90` is an exact reconstructed leaf beneath `0x0046D040`. It checks
four ordered pairs between candidate-frame flags at `candidate+0x1A4->+0x50`
and fighter-frame flags at `fighter+0x158->+0x4C`. A matching pair writes
result code `3` to both objects at `+0x180`, resets collision extents, and
returns true. The target proves this mechanism but not its original gameplay
term, so the source uses the neutral name `try_frame_flag_pair_outcome`.

`0x0046D040` is the per-candidate attack-versus-fighter orchestrator. After
state and shape gates, it tries outcomes in strict order: `0x0046BE90`,
`0x0046BDE0`, `0x0046CE20`, then the ordinary resolver `0x0046B570`.
The ordinary resolver now has complete source in `GeneralHitResolver.cpp`. It
performs scratch reset, scaled threshold/result selection, action-code and
conditional boost selection, candidate/fighter output setup, hit-quantity and
response calculation, owner and deferred-channel accounting, signed depletion
handling, virtual callbacks, effects, final extent reset, and indexed-event
dispatch. The boosted path multiplies response floats by 1.5, uses four thirds
of the descriptor-scaled quantity, and sets owner flag bit `0x20`; these are
observed operations, not inferred game terms. A volatile pointer reload plus an
unsigned-byte flag view reproduces the target's byte test and branch layout,
while a double local keeps the threshold value on the x87 stack across the
shared suffix. The current object is 1533 bytes versus the 1579-byte target;
its first difference at `+0x53` is only the target using `ECX` versus VC8 using
`EAX` for that frame reload. Names for individual result and action codes
remain deliberately unresolved.

`0x0046BDE0` is now an exact reconstruction of the second outcome leaf. It
checks three candidate flag bits plus fighter frame/short gates, optionally
uses `adjust_counter_482`, writes neutral result code `6`, emits effect `0x34`,
and resets extents. The source name stays flag-oriented because the original
gameplay term is not proven.

## Damage scalars and spell-card runtime

The two 347-byte scalar providers at `0x00459ED0` and `0x0045A030` now have
complete source. Both multiply the source fighter, target fighter, and attack
owner factors, blend an observed current quantity into a `0.7..1.0` factor,
apply an indexed signed modifier divided by ten, then apply frame-bit and owner
bit modifiers. They differ in which frame and current quantity they read. VC8
emits 333 bytes for each; the first mismatch at `+0x3` is the target retaining
the source pointer in `EDX` while the object uses `EAX`. The target proves the
arithmetic and field flow, but not the original names of the individual
modifiers.

`0x0046BBA0` consumes the forwarded scalar in the hit path. It conditionally
resets exchange scratch, scales the incoming integer quantity, adjusts fighter
counter `+0x558`, updates owner fields `+0x498/+0x494/+0x49A`, applies the
positive recovery factor at `+0x4D4`, clamps and subtracts fighter `+0x174`,
invokes context vslot `+0x2C` on depletion, and accumulates the result at
fighter `+0x178`. Its current object is 299/301 bytes; the remaining two-byte
gap is prologue/register scheduling rather than a missing behavioral phase.

The observed statistics path is also modeled. `0x0042C100` first rejects
nonzero game mode and setup option two, then selects a 16-byte range header at
`ScoreData+0x198 + selector*0x10`. Each record is 24 bytes: keys are at `+0`
and `+8`, the update count at `+0x10`, and a signed maximum at `+0x14`. A
matching record increments the count and raises the maximum. Its natural object
is 94/191 bytes because the target retains repeated checked-range validation
paths; no absent insertion path is inferred from that code-size difference.

The spell data loader selector at `0x00430DE0` is an exact 71-byte
reconstruction. It chooses the normal `spellcard.csv` loader or alternate
`storySpell.csv` loader, returns false on failure, and calls the shared
post-load finalizer only after success. `0x004317A0` performs checked lookup in
the fighter-local tree and then the common tree at `0x006E4E14`; its source is
target-sized at 179 bytes, with the remaining mismatch in checked-iterator
owner register allocation.

The selector container below that loader is now structurally recovered. Both
`SpellDataOwner+0x20` and `+0x34` are 0x14-byte deque-like headers whose blocks
hold eight shorts. `0x00430C30` is the exact 71-byte checked front accessor.
`0x00430D90` is an exact 78-byte selector: it returns signed `-1` when empty,
otherwise reads the front ID, advances the circular absolute head modulo eight
times the block capacity, decrements the live count, and resets the head when
the count reaches zero.

`0x00430C80` is now source-complete post-load behavior. It zeroes the 32-byte
table at owner `+0x48`, traverses every ID in the deque at `+0x20`, resolves the
ID through `0x004317A0`, and for records whose byte at `+0x1C` equals one stores
the low ID byte at table index `record+0x1E`. VC8 currently emits 226 bytes
versus the 257-byte target. The target retains a 0x10-byte checked-iterator
frame, an owner-identity check, and longer owner/block register lifetimes; this
is a compiler-shaping blocker, not missing transformation logic.

The large parser at `0x00432E20` is a free four-argument `__stdcall` boundary.
Callers `0x00433490` and `0x00433540` preserve their owner separately while
pushing the character name, CSV path, optional four-byte handle deque, and
spell tree; the callee's `ret 0x10` proves four stack arguments and rules out a
truthful member-function ABI. Its maintainable implementation is now in
`SpellCardParser.cpp`. The source preserves the complete row loop, deep-copy
record insertion, optional individual card resources, 16-record composite
publication, descending checked-tree traversal, and owned cleanup. The ledger
retains the 1602-byte body boundary while IDA reports a 1644-byte entry span;
strict comparison currently stops at the verified local EH-handler relocation.
The remaining work is asset/global relocation mapping, EH lifetime shaping,
and compiler scheduling, not missing parser behavior. Its observed row schema is integer, string, byte, short, string,
short, short. It publishes fields at record offsets `+0x1C`, `+0x1E`, `+0x3C`,
`+0x3E`, `+0x40`, `+0x44`, and `+0x48`, formats
`data/card/%s/card%03d.bmp`, and stores images through a
deque-like owner. Every 16 records it builds a `0x200` by `0x100` composite and
publishes its handle at record payload `+0x40`.

The four former record/string blockers are now closed with VC8 probes.
`0x00408A40` is the exact 251-byte `std::string::append(string,off,count)`
specialization. `0x00431430` is the exact 137-byte checked spell-map iterator
predecessor, and `0x00432310` is the exact 185-byte unique map insertion body.
`0x00431950` is the exact 189-byte `SpellRecordView` copy constructor: two real
0x1C owning strings and the observed repeated short-copy subobjects reproduce
every target byte. The map evidence fixes a 0x60-byte node, 0x50-byte
key/value pair, 0x0C-byte insert result, and 0x0C-byte tree header.

The two path wrappers at `0x00432D80` and `0x00433490` are implemented at
146/148 and 159/161 bytes. Each matches through its meaningful branch body;
the remaining two-byte tails are truthful translation-unit/LTCG register
scheduling differences, not missing parser calls. Their target frames retain
stack cookies and an indirect `wsprintfA` import.

The shared insertion boundary at `0x00416A50` is no longer semantically
opaque. Target instructions match VC8 SP1 `include/deque` `push_back` for a
four-byte element exactly: the 0x14-byte header is map pointer `+4`, map size
`+8`, first offset `+0x0C`, and live size `+0x10`; `_DEQUESIZ` is four and a
missing block allocates 16 bytes. A forced `std::deque<unsigned long>` probe
matches all 117 bytes after resolving `_Growmap` to `0x00416D10`; the latter
also matches its 344-byte contiguous VC8 specialization exactly. Both standard
library bodies are classified `library`; callers may use the resulting
0x14-byte deque contract without reimplementing either function.

The spell parser's texture and CSV-reader boundaries are now concrete. The
101-byte `0x00404F30` acquires an index-plus-generation handle from a shared
pool, delegates creation/population of an A8R8G8B8 texture, returns the handle
only for a nonnegative status, and otherwise recycles it. Both spell parsers
pass the same upload state and a 512-by-256 target for paths formatted as
`data/card/%s/card%03d.bmp`. The target proves handle ownership and failure
rollback, but not the original class names of the pool or upload state.

The reader used by `0x00432E20` is a 0x2E-byte observed prefix. Its row-deque
header is at `+0x04..+0x10`, outer iterator owner/position at `+0x18/+0x1C`,
current row/field position at `+0x24/+0x28`, and parser comment/quote flags at
`+0x2C/+0x2D`. The recovered API is:

- `0x0040EB20`: load, parse owned row/field copies, reset iteration, then free
  the temporary input buffer;
- `0x0040EE50`: consume an integer field, returning zero when exhausted;
- `0x0040EF50`: consume a field into an owning VC8 string copy, assigning empty
  when exhausted;
- `0x0040F050`: advance to the next row and reset the field iterator;
- `0x0040F780`: destroy all owned fields, rows, blocks, and the deque map.

`0x00432E20` consumes each record as integer, string, two integers, string,
and two integers, advances the row, and explicitly clears the reader. It does
not test the reader-load result, so the resource is required to parse
successfully. Two inventory rows remain deliberately non-contiguous:
`0x0040EB20` tracks 164 body bytes within the 0xAA-byte entry span and
`0x0040F780` tracks 119 body bytes within the 0x7D-byte entry span. IDA sizes
must not overwrite those ledger values.

At runtime, `0x0045BC30` only consumes a sequence entry when fighter category
`+0x72C` equals two and signed state `+0x55A` is positive. It dispatches the
front record through the player-indexed context, optionally updates the score
record using peer key `+0x330`, self key `+0x330`, record id, and statistic
candidate `+0x64C`, advances the sequence, publishes the next record's
`+0x1E/+0x3C` values, and clears `+0x655/+0x64C`. The source emits 282/346
bytes. Its external `g_info_manager` reference is now accepted through a
strict direct-address relocation mapping, so comparison reaches the remaining
code-shape difference. `0x0045C690` selects a record, optionally prepares
its resource at `+0x44`, transfers the observed two-short sequence record, and
publishes pending state. It emits 193/259 bytes; the remaining difference is
the target's EH-bearing `0x94`-byte sprite local and register schedule.

The exact finalize caller also resolves `0x0042C060`: outside excluded game
and session modes, it scans the selected `ScoreData+0x198` range of 0x18-byte
records, matches keys at `+0x00/+0x08`, and increments the sequence-result
counter at `+0x0C`. The adjacent `0x0042C100` uses the same layout to increment
`+0x10` and update the signed high-water field at `+0x14`.

`0x0045BBB0` is now an exact 118-byte shared front-sequence readiness gate.
It first requires signed available count `+0x55A` to exceed the requested
index, then compares that count against slot word `+0x02`, subtracting one when
fighter state `+0x4B8` equals two and clamping the threshold to one. Target
xrefs prove exactly two call sites in each of all fifteen character
dispatchers. Its faithful ternary deliberately repeats the checked slot access
on the non-clamp path, matching the target rather than applying unsupported
common-subexpression elimination.

The action-transition phase at `0x004631E0` is also source-complete. It packs
nonzero state from `+0x6C8/+0x6C4/+0x6C0/+0x6BC` and signed positive/negative
tests from `+0x6B8/+0x6B4` into one byte, passes selector `0x5A` and that word
to the subobject at `this+0x710`, and returns the callee's full EAX. It has 407
call sites across 28 functions, including every character dispatcher. Natural
VC8 emits 134 bytes versus the 136-byte target because it folds the final byte
OR into the subsequent 32-bit promotion; the ledger therefore says `compiles`.

`0x0045F140` now provides maintainable source for the observed fighter battle-state
reset: owned-state cleanup, subordinate phases, initial position and facing,
counter/scalar defaults, the two eight-element tables at `+0x604/+0x624`,
action reset, category-dependent sequence setup, checked front access, initial
record publication, and action `700`. VC8 emits 1231/1247 bytes and matches the
target prefix through `+0x340` after recovering the original two 32-byte
`memset` shapes, preloading the action-reset vcall, and placing the category-two
spell path in the target fallthrough. The
first unresolved difference is a target-only speculative `LEA ECX,[ESI+4F0]`
before the long branch; the checked-iterator suffix still differs in register
coloring and guard scheduling. The source covers all phases observed in the
current decompile, while further semantic audit remains open.

The adjacent `0x00462050` now has complete source in
`FighterResourceInitialization.cpp`. It first parses per-character PAT and
palette resources through `0x00460B50`, loads exactly 64 indexed wave handles
through the exact `0x0045E080`, and invokes the exact spell-data selector. It
then formats the face resource and up to ten `back/spell%03d.bmp` resources,
stores the face handle at `+0x338`, registers back handles in the dword deque at
`+0x68C`, applies player-relative `-1/+1` values at `+0x3C4/+0x3C8`, and ends
with the cut-in component at `+0x3D0`. VC8 emits the same 333-byte size as the
target. Remaining bytes differ in the target's LTCG-preserved unused argument
bits and virtual-call register scheduling, not in a missing phase.

`0x0045E080` is an exact 132-byte reconstruction. It resolves `+0x330` to a
borrowed character path component, loads `data/se/%s/%03d.wav` for indices
zero through 63 through the global wave-handle manager, and stores the opaque
handles in the table pointed to by `Fighter+0x164`. The fighter does not own or
release the underlying wave objects in this function.

`0x00464320` has complete 197-byte source against the 199-byte target. Its
`0xA0`-byte `FighterCutinResource` contains a handle, a `0x94`-byte embedded
sprite, selector at `+0x98`, and terminal state at `+0x9C`. It formats
`data/stand/cutin/%s.bmp`, configures sprite vslot `+0x14` with the loaded
handle and observed extents, applies the selector-one float pair, and stores
`-1` at `+0x9C`. No local release path is present.

The remaining large shared boundary `0x00460B50` reads
`data/character/%s/%s.pat`, loads `palette%03d.bmp` handles into the container
at `+0x130`, and builds checked tree/deque records through `+0x160` and
`+0x65C`. Its corrected contiguous span is 3885 bytes ending at
`0x00461A7C`; the older inventory size omitted `0x68` bytes. Its local reader,
lists, and EH cleanup still require concrete record types before source is
claimed.

## Body collision and geometry

Attack damage is resolved before fighter body separation.

- `0x0046ACB0` resets the collision context extents at `+0x1C..+0x28`.
- `0x0046A9A0` accumulates those fields from two four-integer coordinate
  records and is reconstructed exactly.
- `0x0046AB80` and `0x0046ABD0` exactly project one or two AABBs vertically
  with descriptor words `+4/+0x0C`, then call the integer extent accumulator.
- `0x0046AA30` performs the corresponding float-coordinate accumulation after
  selecting and converting extrema.
- `0x0046ACD0` converts a local rectangle into a world AABB using actor
  position at `+0xEC/+0xF0` and facing at `+0x104`.
- `0x0046AD30` exactly gates and accumulates float AABB overlap. Its source
  materializes four float differences in the target's non-sequential scratch
  order, ANDs their raw IEEE-754 sign words, and tests `0x80000000` before
  calling the float extent accumulator. This produces the complete 97-byte
  target rather than the former 95-byte optimized shape.
- `0x0046AEA0` exactly reconstructs the four signed half-space expressions
  used to test a point against an AABB plus a four-word descriptor.
- `0x0046AC40` exactly reconstructs effect dispatch at the midpoint of the
  accumulated extents. Its VC8 double-`0.5` data relocation is verified
  against both the COFF literal and target bytes before comparison.
- `0x0046ADA0` tests one AABB against such a descriptor, while `0x0046B000`
  performs an ordered descriptor-pair broad phase and five point tests. Both
  now have complete source, including extent accumulation and return paths.
  The former's natural VC8 object is 246 bytes versus the 248-byte target: the
  optimizer replaces the target's final `AND EBP,ESI; TEST EBP,EBP` with
  `TEST ESI,EBP`. The latter's isolated object is 232 bytes versus 252 because
  its register lifetimes and branch layout still differ from the target.
- `0x0046C290` now has complete source for fighter body separation. It reads
  fighter roots at context `+0x0C/+0x10`, clears the per-fighter response at
  `+0x6A4`, and returns when either current frame (`+0x158`) has no body AABB
  pointer at frame `+0x54`. Two signed global bytes latch which fighter owns
  each stage edge (`0`, `1`, or `-1` for unlatched). After transforming both
  local rectangles, the function resolves four edge-pinned cases directly;
  otherwise it chooses a separation direction from AABB centers (with vertical
  center as the tie-break), splits penetration by `0.5`, gates both proposed X
  moves against stage height, and computes the coupled facing-relative response.
  The standalone VC8 object is now 1853 bytes versus the 1862-byte target. Its
  ABI, 0x40-byte frame, `ESI=this`, member-helper calls, edge-owner cold-block
  placement, four pinned-edge responses, ordinary separation direction, and
  both motion guards are established. The remaining nine-byte gap is isolated
  to the first ordinary response suffix: VC8 keeps a different pair of x87
  values live while coloring the two coupled-motion slots. The ledger therefore
  truthfully keeps it `implemented`.

Collision objects expose two observed box groups without proven gameplay
names. Group A uses signed count `+0x1AF`, boxes at `+0x204`, and optional shape
pointers at `+0x304`; group B uses signed count `+0x1B0`, boxes at `+0x1B4`,
and shape pointers at `+0x318`. An optional primary box pointer is at `+0x32C`.
`0x0046AF30` tests group A against the primary box, `0x0046B100` tests group A
against group B, and `0x0046B290` tests group B against group B. Debug drawing
colors the groups differently, but that does not prove hitbox/hurtbox labels.

The group counts are signed bytes and every loop index is sign-extended before
box or pointer indexing. `0x0046B100` and `0x0046B290` select the descriptor-pair
helper, one-descriptor helper, or inline AABB predicate from the two descriptor
null states. They OR every pair result and do not return early after an overlap;
preserving that traversal is required even when only a boolean result is used.
The two 398-byte functions are byte-isomorphic apart from 17 bytes accounting
for their group offsets and call displacements. Complete source now covers
`0x0046AF30`, `0x0046B100`, and `0x0046B290`; their current integrated VC8
objects are respectively 161/194, 321/398, and 321/398 bytes. They remain
`implemented` because VC8 assigns different registers and does not reproduce
the target's repeated descriptor reloads and stack scheduling.

`0x0046C070` handles one observed group-B object-pair overlap after
`0x0046B290` succeeds. It compares two 16-bit values from each current frame
record, writes neutral result codes at object `+0x180/+0x184`, and resets the
collision extents. The ordered table is fully mapped, including the unusual
branch where the left object's `+0x184` byte is derived from the right object's
`+0x1A0` byte. All comparisons are signed 16-bit. No graze, guard, cancel, or
priority terminology is assigned without live proof. The faithful source now
lives in `ObjectResponses.cpp`; VC8 emits 557 bytes instead of 542 because it
tail-merges one repeated result/reset suffix that the target keeps separate.

Inside the family-2 versus family-1 pass, `0x0046D160` first tries
`0x0046BFD0`, which transfers owner pointers and flips facing after group-B
geometry succeeds. Its fallback `0x0046BF20` performs group-A versus group-B
geometry, writes frame-derived outputs, subtracts from the other object's
`+0x174`, and dispatches frame event/effect values. `0x0046BFD0` now has an
exact 147-byte VC8 reconstruction in `ObjectResponses.cpp`. `0x0046BF20`
remains one instruction away: the target gratuitously zero-extends a 16-bit
load before immediately storing only its low 16 bits, while every otherwise
exact natural source shape uses a 16-bit load. Twenty-three bounded source and
type variants either retain that load or disturb later register scheduling.
Its integrated source is 162 of 164 bytes equal (98.78%) and remains
`implemented`, not `matching`.

The larger nonzero outcome selector is also bounded. `0x0046CE20` obtains a
selector from `0x0045CB20`; selector zero returns false to the ordinary hit
resolver, selectors `1/3/5/6` use `0x0046C9E0`, and selectors `2/4` use
`0x0046CC00`. The two subpaths share scratch/resource accounting and a normal
result-code-2 response, but differ in their counter transition rules, terminal
gates, and effect codes (`0x32` versus `0x33`). Their names remain neutral until
live behavior establishes the original gameplay terminology.

All three paths now have source in `OutcomePaths.cpp`, including the complete
selector table, virtual action dispatch, per-path counter transitions, terminal
handoff, deferred accounting, and effect/event outputs. Natural VC8 emits 517,
524, and 320 bytes versus target sizes 530, 542, and 446. The first two retain
the current-frame pointer where the target reloads it; the dispatcher is shaped
very differently by its target switch table and unmerged case suffixes. They
therefore remain `implemented`, not matching.

The selector at `0x0045CB20` is also implemented. It returns codes `0..6` from
the incoming frame byte, current frame flags, two signed state windows, stage
surface, cached direction, battle state, and an observed random-roll policy.
Its adjacent `0x0045CB00` state-window leaf (`0x96..0xC7`) is an exact 28-byte
reconstruction. The selector's natural object is 601 bytes versus 620.

The selector's RNG dependency is also reconstructed exactly. `0x00406880` is
the MT19937 next-word routine, including twist, fallback seed, state index, and
tempering. `0x004069A0` performs the target's unsigned quotient mapping; it can
produce the requested upper endpoint for a small tail of raw values, so the
source deliberately does not replace it with a conventional modulo or uniform
distribution helper.

Their shared terminal helper `0x0046BCD0` is now an exact 260-byte
reconstruction. It consumes one observed 200-unit counter step, resets the hit
exchange scratch, writes result code 2 and descriptor outputs, updates deferred
per-player accounting, emits indexed event `0x14` through `0x00439DC0` and
collision effect `0x35`, then resets extents. The counter-step helper is
`0x00459C90`. `0x0045CA70`, used by this helper and both normal outcome
paths, is also exact: it compares the paired fighters' x coordinates, writes
signed facing `1/-1`, and reports whether the facing changed.

## Physics and state commit

The exact wrapper `0x0046A5C0` loads the same global context at `0x006E623C`
and tail-jumps to `0x00463760`. The latter makes three separate complete
checked-vector passes, in this exact order:

- `0x00459860`: position integration and stage-bound clamping for fighter
  coordinates `+0xEC/+0xF0`;
- `0x0045CDD0`: transient status processing;
- `0x0045CF00`: timer decrement and cleanup.

`0x0045CDD0` now has complete source-level behavior. It updates the paired
`+0x48A/+0x48C` counters, resets floats `+0x6AC/+0x4DC/+0x4E0`, clamps signed
shorts `+0x174/+0x47C`, steps the embedded object at `+0x3D0`, decrements
positive dword `+0x670`, selects `+0x4B8` from short `+0x4B2` or global
`0x006E4E20`, and normalizes 32 signed bytes at `+0x624` into `+0x604`.
The integrated VC8 object is 300 bytes versus the 301-byte target and remains
`implemented`; its first difference at `+0x11E` is only the false-loop's
8-bit versus 32-bit mask scheduling.

`0x0045CF00` is fully decompiled as the third pass. It first suppresses the
pass when the paired fighter at `+0x170` has nonzero `+0x48C`, otherwise gives
local short `+0x186` an early-return countdown. It then processes the observed
`+0x4A0..+0x4B2` countdown group, the `+0x4A2/+0x4A4` state-window gate,
frame bit `0x1000`, and the `+0x558/+0x55A/+0x72C` threshold callback path.
Every normal suffix tail-jumps to the separate ledger function `0x00459D30`,
which updates `+0x482..+0x488` and can notify a global virtual sink. IDA
currently absorbs that tail target into `0x0045CF00`; reconstruction and
comparison must retain the authoritative 470-byte local span ending at
`0x0045D0D5`.

The pass ordering supplies a cross-fighter continuity guarantee: all fighters
finish `0x0045CDD0` before any fighter enters `0x0045CF00`, so the paired
fighter `+0x48C` suppression reads a completed pass-two state rather than an
iteration-order-dependent partial update. The same VC8 vector layout and
checked `operator[]` shape produce an exact 187-byte reconstruction of the
three-pass outer phase.

`0x00459860` itself is exact at 270 bytes. Its two stage-boundary dependencies
are now exact as well: `0x00434390` classifies x at the observed 40/1240
boundaries (59 bytes), and `0x004343D0` tests proposed x against the 0x500-float
stage-height table with five units of y clearance (120 bytes). The source keeps
the target's x87 double-expression order rather than simplifying the comparisons.

`0x0046A5D0` is an exact 51-byte post-update phase. It calls context vslot
`+0x3C`, clears context field `+0x08`, calls Info-manager vslot `+0x10`, then
calls `0x00425CD0` and tail-dispatches `0x00425F10`, both with opaque global
state `0x006E6260` in `ECX`.

Two exact per-frame reset leaves at `0x0046A610` and `0x0046A6A0` clear
different observed subsets of fighter fields `+0x6B4..+0x728` for both player
slots. These are intentionally named by field range until callers prove phase
or gameplay terminology. `0x0046B520` is also exact: it subtracts and clamps
fighter short `+0x482`, applies a state-5 gate from `+0x4B8`, and raises short
`+0x486` to the resulting floor value.

Two additional exact fighter gates now bound the general hit path:
`0x0045CAE0` tests signed short `+0x13C` against `0x32..0x95`, while
`0x0045CD90` additionally requires positive y at `+0xF0` and zero short
`+0x49E`. The adjacent exact `0x0045CB00` leaf tests the same signed state
against `0x96..0xC7`. `0x00434860` compares y against an x-dependent stage-height
helper. Both the wrapper and helper `0x00434800` are exact: the
helper rounds positive x with double `0.5`, clamps at table index `0x4FF`, and
reads the 0x500-float height table at `0x006E4E38`.

`0x0046A940` resets the shared exchange scratch used by five hit-resolution
paths: it copies target `+0x174` to `+0x47C`, clears target `+0x4A2`, initializes
owner `+0x491/+0x494/+0x498..+0x49C`, and resets an indexed 0x34-byte manager
entry. It is now an exact 93-byte reconstruction. Its `0x00469E40` indexed-entry
reset is also exact at 26 bytes and tail-calls `0x0051D0D0` to release its
owned-pointer buffer. The absolute manager pointer at `0x006E6248` is accepted
only through a strict zero-filled BSS relocation mapping.

The collision phase's deferred channel at context `+0x7C/+0x80` now ends in an
exact 150-byte leaf, `0x0045BF10` (`apply_deferred_counter_558`). Unless fighter
byte `+0x72C` equals 2, it subtracts a signed short from counter `+0x558`; when
the subtraction crosses zero and signed byte `+0x55A` is positive it wraps by
500, emits effect `0xA0` at `(x, y + 100.0)`, and advances the controller rooted
at `+0x55C`. Otherwise it clamps the counter to zero. These remain neutral
counter/controller names until runtime evidence supports a gameplay term.

The hit pipeline obtains frame-derived quantities through exact sibling
wrappers `0x0045AAE0` and `0x0045AB10`. They multiply a candidate scale by the
signed descriptor short at `+0x1C` or `+0x20`, respectively, then tail-dispatch
the VC8 float-to-int truncation helper. `0x0045B870` adjusts an observed
signed-short counter at `+0x558`, with near-limit scaling and an upper cap of
500. Its faithful C++ is not yet register-scheduled exactly.

The scale provider `0x0045A030` is identified as the product of several
candidate/owner/fighter scalars and conditional modifiers. `0x0045AAE0` now has
an exact natural-C++ match, including its tail jump to verified VC8 runtime
`_ftol2_sse`; that runtime is tracked as library code rather than authored
progress.

The adjacent no-relocation leaf `0x0045AAC0` is also exact. It returns zero
when pointer `+4` is null and otherwise divides the byte difference between
pointers `+8` and `+4` by `0x88`. Its structural contract is proven; the
element type and original gameplay name are not.

The collision/list manager constructed by `0x0046A810` installs
`CBattleManagerBase::vftable` at `0x006AF634` and constructs three pairs of
12-byte list-like elements. This object is distinct from the higher-level
battle-state controller that calls the frame phases above.

`0x0046B420` is an exact 195-byte, 16-step cross-manager phase sequence over the
object manager, fighter container, static service, and effect manager; it does
not directly manipulate hit fields. The vtable `+0x38` wrapper `0x0046B4F0`
calls that sequence and then an Info-manager-family virtual slot `+0x14`.
Its natural source is complete and a private split-TU probe is 34/34 exact, but
the integrated same-TU form remains `implemented` because the standard
comparator intentionally rejects its internally defined REL32 call.

## Recommended reconstruction lanes

Keep claims address-bounded, but do not optimize the work queue for easy
progress counts. The central hard functions now have complete semantic source,
so the highest-value lanes are:

The machine-readable version of this frontier is maintained in
`config/core-functions.csv` and `config/core-dependencies.csv`. Agents should
run `python3 scripts/core-worklist.py --ready` before claiming work; see
[`CORE_FRAMEWORK.md`](CORE_FRAMEWORK.md). The generated action and blocker
columns follow the live function ledger and do not promote placeholder
contracts to implemented source.

1. Shape `0x0045AEC0` against its 2156-byte target, beginning with the two
   missing group-A loop locals that account for the `0x34`/`0x3C` frame gap,
   then close the entry `MOVZX` schedule and `vector::at` COMDAT boundary.
2. Shape the list orchestrators `0x0046D160`, `0x0046D370`, and `0x0046D620`
   using their recorded stack-frame and checked-iterator differences.
3. Implement the proven spell-card dependencies around parser `0x00432E20`
   and fighter resource initializer `0x00462050`; then use those contracts to
   shape `0x0045BC30`, `0x0045C690`, and `0x0045F140` without synthetic EH.
4. Restore the checked-range form of score updater `0x0042C100` and close the
   scalar/hit gaps at `0x00459ED0`, `0x0045A030`, and `0x0046BBA0`.
5. Close geometry codegen gaps in `0x0045A190`, `0x0045A2E0`, `0x0045A4A0`,
   `0x0046AF30`, `0x0046B000`, `0x0046B100`, and `0x0046B290`.
6. Continue hit/object responses at `0x0046BF20`, `0x0046C070`, and the larger
   `0x0046CE20` outcome branch.
7. Shape the now-complete `0x0046C290` body-separation source, then connect it
   outward to the remaining fighter status/timer phase at `0x0045CDD0` and
   `0x0045CF00` and the battle state machine at `0x0046FE80..0x00470940`.

Small exact leaves remain useful only when they unblock one of these core paths
or prove an ABI/layout dependency.
