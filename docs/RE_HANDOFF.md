# Current reconstruction handoff

## Phase

Two canonical 1.06a authored-exact waves are established. The active phase is
expanding authored classification and exact source recovery beyond raw-identity
seeds using current-target-backed structural remapping where appropriate.

## Verified state

- Canonical SHA-256:
  `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
- `resources/th105.exe` is byte-identical to the executable extracted from the
  official `th105_update_106a.exe` payload.
- IDA metadata, entry `0x0068B9D2`, five separated mapped-byte samples, required
  read tools, and a function query pass `scripts/check-ida-mcp.py`.
- The fresh IDA auto-analysis inventory remains 4,001 candidates. The corrected tracked ledger has 4,004: current-target boundary evidence recovered `CFileReader_dtor @ 0x0040CEB0` plus source-level fighter phase entries `0x00464630` and `0x00464780`, all of which IDA had attached as tail chunks instead of standalone entries. Current reviewed state is 259 authored functions, 685 classified exclusions, and 3,060 still awaiting origin/boundary review.
- All 259 confirmed authored functions are source-present and canonical exact:
  34,865 exact authored bytes across 127 configured VC8 units.
- The newest retained-source migration wave added 159 functions / 21,378 bytes
  beyond the prior 100-function checkpoint. Structural instruction shape and
  relocation-masked bytes are used only for candidate ranking; every accepted
  function still requires current 1.06a semantic/relocation evidence and a fresh
  canonical zero-difference comparison.
- The lifetime/template origin lane now excludes twelve compiler-generated functions through SHA-pinned VC8 replay: the original checked `PatRecord88` vector helpers, nested `PatRaw16` erase/assignment/destructor clone groups, the implicit `PatRecord88` copy constructor, and current `std::map<unsigned, void*>::find @ 0x0046EA60`. Generated clone groups are accepted only when the complete current-inventory fingerprint hit set equals an explicitly declared equivalence group; the vector-copy rule still permits only its single manifest-bounded `0xCC` alignment byte.
- `Alice_handle_event_bridge @ 0x0050ED00` is now 1075/1075 exact from a narrow natural C++ lifecycle view. Current 1.06a proves the byte return ABI, real virtual action/sequence slots, 22-event semantics, 19-destination jump table, and 121-byte sparse index table; the compiler-owned switch tables trail the accepted ledger body in the same COMDAT.
- `PatRecord88_construct @ 0x00460F90` and `PatRecord88_destroy @ 0x0045FFD0` are 300/300 and 515/515 exact with the current FrameData base and three checked nested vectors; the same pinned VC8 model now classifies current `vector<PatRaw16>::erase @ 0x0045FBD0` as compiler-generated.
- `test_aabb_against_descriptor_shape @ 0x0046B7B0` is 248/248 exact after expressing the already-proved signed broad-phase rejection as an equivalent bit-31 test; this preserves the target AND/TEST/JS schedule without assembly or register forcing.
- `load_indexed_character_wave_resources @ 0x0045F680` is 132/132 exact without source surgery. Current target reads `record_key_330`, resolves the character name at `0x0043BF80`, formats `data/se/%s/%03d.wav`, calls wave service `0x00702288` through `0x00401AF0`, and stores 64 returned handles through Fighter `+0x164`; all non-relocation bytes already matched before current relocation reconciliation.
- The current lifecycle/PAT wave adds exact `Alice::handle_event_bridge` (1,075 bytes) plus full `PatRecord88` construction/destruction (300/515 bytes). The recovered PAT layout now has a 0x1C `FrameData` base, checked `vector<PatRaw16>` members at +0x58/+0x68 and checked `vector<PatRaw16*>` at +0x78; the unique 88-byte value-vector `erase` helper is independently excluded as generated VC8 template code.
- Refined PAT layout evidence also removes `vector<PatRaw16>::operator= @ 0x00460AD0` and the implicit `PatRecord88` copy constructor `0x00460C90` from the authored denominator through SHA-pinned VC8 generated-COMDAT replay. The latter only matches after treating +0x3A/+0x4A as natural alignment gaps and the `FrameData` copy constructor as an out-of-line base lifetime; explicit padding-array members or an inlined implicit base copy do not reproduce the target.
- `load_spell_csv_via_325b0 @ 0x00434300` and `load_spell_csv_via_32e20 @ 0x00434A10` are 148/148 and 161/161 exact after correcting the parser ABI: current wrappers and independent caller `0x00434AC0` all restore `ECX = SpellDataOwner*` immediately before the parser call. Modeling the parser bodies as unused-`this` member functions naturally restores the two missing `mov ecx, esi` instructions and preserves the owner register in the alternate branch.
- `config/claims.csv` remains header-only. IDA Pro remains the sole semantic
  backend.

## Cross-version seed decision

The former repository targeted 1.06 (`3,039,232` bytes), not 1.06a, so its
addresses, classifications, and exact claims remain invalid for the current
target. A raw-byte uniqueness survey may be used only to prioritize retained
source hypotheses.

The first migration wave intersected old authored/exact hypotheses with unique
raw-identical 1.06a candidates, then rebuilt every retained source with the
pinned VC8 toolchain and required a fresh canonical zero-difference compare.
That procedure promoted 47 functions; raw identity by itself promoted none.
REL32 destinations were checked against the current target. In particular, the
second loader called by `load_spell_data` is `0x00434300` in 1.06a; a guessed
cross-version delta produced a mismatch and was rejected before IDA confirmed
the current call target.

## Next bounded work

Continue origin/boundary review so the authored denominator becomes meaningful,
then expand exact recovery from the 259 accepted functions. Use
`scripts/rank_retained_exact.py --only-unconfigured` to prioritize historical
exact source that never had an old match unit. Same-size zero non-relocation
mismatch candidates are especially productive, but ambiguous template/clone
families must be disambiguated with
current xrefs/vtables/RTTI/relocations. Treat every old 1.06 address, callee,
name, and implementation as a hypothesis until independently reconciled
against 1.06a.

The 95% authored-function and authored-byte goals cannot be reported yet: 3,060
provisional candidates still need authored/excluded classification, so the
global authored denominator is not established. Do not use the current 259/259
exact subset as a substitute denominator.

## Routine checkpoint

```bash
python3 scripts/verify-target.py
python3 scripts/check-ida-mcp.py
python3 scripts/validate-tracking.py --require-target
python3 scripts/build.py --check
python3 scripts/progress.py --check
python3 scripts/verify-exact-units.py --all
python3 scripts/ci.py
git diff --check
```
