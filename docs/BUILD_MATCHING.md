# VC8 build and exact matching

The target's linker/Rich metadata establishes the VC8 family and compiler build
50727; `config/tools.lock.toml` pins the current VC8 SP1 candidate environment.
The exact profile remains unproven for authored 1.06a code.

## Acceptance boundary

An exact function requires all of the following:

- an accepted target address/size in `config/functions.csv`;
- a durable authored mapping in `config/reccmp-functions.csv`;
- source selected in `config/implemented.csv`;
- a reproducible unit in `config/match-units.toml`;
- strict COFF symbol/extent validation and relocation replay;
- zero byte differences against canonical `resources/th105.exe`;
- a `matches.csv` row with command/report evidence and a simultaneous
  `matching`/`100.00` ledger update.

Build success, objdiff similarity, decompiler resemblance, and old 1.06
reports do not satisfy this boundary.

## Focused loop

```bash
python3 scripts/verify-target.py
python3 scripts/build.py --check
python3 scripts/build.py --unit UNIT --compare --json
```

Start with a small natural function. Recover calling convention, member
layout, narrow signedness, EH behavior, callees/globals, and likely object
ownership before register/branch shaping. Use the pinned compiler naturally;
never add assembly, machine-code arrays, fake behavior, padding, or ABI lies.

The existing unit format can group tightly coupled functions in one VC8 probe,
which is useful when COMDATs, templates, inline dependencies, or LTCG-shaped
ownership make TH08's one-function assumptions unsuitable.

## Relocations and boundaries

`compare-function.py` fails closed on unknown REL32/DIR32 targets, unexpected
addends, unsupported COFF ownership, and target identity changes. Add a
relocation mapping only after both target bytes and semantic ownership are
supported.

IDA extents do not define compiler boundaries. Tail chunks, jump tables,
EH funclets, thunks, and adjacent constants must be proven from control flow
and COFF records. If LTCG makes a truthful standalone object impossible,
record the blocker; do not weaken the comparator or invent a source boundary.

## Cross-version hypothesis migration

Retained 1.06 source and raw-byte identity can accelerate selection, but neither
is authority for 1.06a. The accepted first wave used this sequence:

1. intersect old authored/source hypotheses with unique raw-identical 1.06a
   candidate spans;
2. reconcile the current candidate and semantics;
3. compile the natural retained C/C++ with the pinned VC8 profile;
4. supply only current-target-backed relocation mappings; and
5. accept the function only after the canonical comparator reports zero
   differences and a cold unit replay succeeds.

Do not translate REL32 destinations by address delta alone. During the first
wave, a delta-derived target for the second `load_spell_data` loader produced a
real mismatch; current IDA disassembly identified `0x00434300`, which made the
source comparison exact. Treat that failure mode as a general rule for moved
callees.

### Structural-fingerprint migration

When raw identity no longer survives a patch, retained exact source can still
provide a safe *ranking* signal without weakening acceptance. Compile the
retained source with the pinned VC8 profile, disassemble both the COFF function
and current 1.06a candidates, and normalize only relocation/address-sensitive
operands (for example branch destinations and large absolute immediates). Rank
candidates by instruction/operand shape, then return to the normal bounded
function loop. A structural score is never a mapping or exact-match claim.

The first target-backed use of this method recovered seven additional authored
functions / 1,069 bytes: `0x00412A20`, `0x004284C0`, `0x0042B2F0`,
`0x0042B460`, `0x0045DBA0`, `0x00493D40`, and `0x0053CDF0`. For every one,
current-target call destinations were reconciled from the 1.06a instruction
stream and IDA call graph before the canonical comparator was run; all seven
then reached zero differences under fresh VC8 builds.

Normalized signatures are intentionally non-unique for template and clone
families. The roster object-manager spawn bodies and manager-base constructors,
for example, produce multiple equally strong structural candidates. Do not
break such ties by address order or old-version deltas. Use class-specific
xrefs, vtables/RTTI, neighboring recovered anchors, and current relocation
semantics to establish identity, then require the same canonical zero-difference
comparison.

The comparator's `symbol_base` identifies a COFF symbol and need not equal the
durable semantic name in `reccmp-functions.csv`. This is useful when retained
source still carries an old address suffix or when a class-qualified compiled
symbol has a cleaner durable name.

## Shared changes

After any shared layout/header/flag/object-graph/relocation change, rebuild
every affected accepted unit. Aggregate totals require:

```bash
python3 scripts/verify-exact-units.py --all
```

The replay is cold and sequential by default so stale or concurrent build
products cannot support a published exact total.
