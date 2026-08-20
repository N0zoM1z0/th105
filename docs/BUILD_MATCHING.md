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

## Shared changes

After any shared layout/header/flag/object-graph/relocation change, rebuild
every affected accepted unit. Aggregate totals require:

```bash
python3 scripts/verify-exact-units.py --all
```

The replay is cold and sequential by default so stale or concurrent build
products cannot support a published exact total.
