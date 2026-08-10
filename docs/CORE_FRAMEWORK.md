# Gameplay reconstruction framework

This framework gives agents a shared map of the danmaku, skill, battle,
collision, score, and spell-card reconstruction frontier before every target
function has source. It deliberately uses declarations and manifests rather
than fake function bodies.

## Why there are no behavioral stubs

A placeholder that returns zero or performs no work is dangerous in a binary
reconstruction project: it can link successfully, look implemented to another
agent, and conceal missing target behavior. This repository instead separates
four concepts:

- `config/functions.csv` remains the source of truth for name, ABI, signature,
  status, source file, and exact-match evidence.
- `config/core-functions.csv` selects the gameplay-first scope and assigns a
  lane and priority without duplicating function status.
- `config/core-dependencies.csv` records the minimum dependency status needed
  to work on a caller, together with an evidence pointer.
- `config/core-types.csv` records complete, partial, and opaque type views. An
  observed size for a partial view is an evidence boundary, not a claim that
  the C++ struct is complete.

`src/battle/CoreContracts.hpp` adds compile-time checks for complete layouts
and member-function typedefs for central ABI contracts. It defines no target
function body. `CoreContracts.cpp` exists only so the pinned VC8 compiler can
validate the header in isolation.

## Lanes and dependency direction

```text
spell-assets ──> spell-data ──> spell-runtime ──> fighter-init
                         └────> score

geometry ──> collision-phase ──> hit-resolution
                       └───────> battle-phase
```

The graph is curated, not an automatic assertion that every Ghidra call edge
is semantically understood. Every durable edge must name its evidence. Runtime,
compiler, and imported calls may be omitted when they are not reconstruction
work; unknown authored boundaries are included because they block useful type
contracts.

## Agent commands

Validate all framework manifests and referenced headers:

```bash
python3 scripts/core-worklist.py --check
```

Show the highest-priority unclaimed functions whose recorded dependencies meet
their minimum status:

```bash
python3 scripts/core-worklist.py --ready --limit 30
python3 scripts/core-worklist.py --ready --lane hit-resolution
```

Machine-readable handoff and graph output are available without generated
files in the repository:

```bash
python3 scripts/core-worklist.py --lane spell-data --json
python3 scripts/core-worklist.py --lane collision-phase --dot > build/collision.dot
python3 scripts/core-worklist.py --blockers --limit 20
python3 scripts/core-worklist.py --explain 0x00430C80
python3 scripts/core-worklist.py --explain 0x0045B9E0 --json
```

`--blockers` ranks unmet direct dependencies with a deliberately simple weight:
priority-1 callers contribute 100 points, priority-2 callers 10, and priority-3
callers 1. This is an impact queue, not a progress score; it helps find a small
contract that releases several hard gameplay callers. `--explain ADDRESS`
produces an address-bounded handoff packet containing the live ledger fields,
claim, dependencies, reverse dependents, evidence, and whether each contract is
currently satisfied. Agents should attach this packet to a claim rather than
copying stale task descriptions between chats.

The action column is derived from the live function ledger:

| Ledger status | Suggested action |
| --- | --- |
| `unclassified` | establish contract and neutral name |
| `identified` | decompile and document complete control flow |
| `decompiled` | implement a faithful source body |
| `implemented` / `compiles` | shape and compare |
| `matching` / `library` | dependency is ready; do not claim for progress |
| `blocked` | read the concrete blocker before taking the lane |

An active row in `config/claims.csv` always removes the function from `--ready`
output. A claimed function remains visible in normal and JSON output so a
coordinator can inspect the owner and blockers.

## Adding a placeholder contract

1. Prove the address belongs in the gameplay scope using target callers,
   callees, strings, fields, RTTI, or vtables.
2. Add the address to `core-functions.csv`; do not change its ledger status
   merely because it is now in the framework.
3. Record only supported dependencies. Use `required_status=identified` when a
   stable ABI/name is sufficient, `decompiled` for a required control-flow
   contract, `implemented` for a required source dependency, and `matching`
   only when byte identity is genuinely necessary.
4. Add or refine a type in `core-types.csv`. Mark incomplete object layouts as
   `partial`, even when the observed target span is large.
5. Put declarations in the narrow module header. Add a compile-time check to
   `CoreContracts.hpp` only for a complete view.
6. Run the framework validator and compile `CoreContracts.cpp`.

Do not add an empty body, synthetic return value, guessed enum, or guessed
class size. Do not promote a function status from the framework alone.

## Current high-value frontier

The manifests make two different kinds of work explicit:

- hard shaping lanes that already have semantic source, including
  `0x0045AEC0`, `0x0046B570`, `0x0046D160`, `0x0046D370`, and `0x0046D620`;
- contract-unlocking lanes around the spell parsers and resource ownership,
  especially `0x00432E20` and `0x00462050`.

The spell-runtime frontier now has an exact checked short-deque front at
`0x00430C30` and exact selector/advance behavior at `0x00430D90`. The post-load
transform at `0x00430C80` is source-complete; its remaining mismatch is a
checked-iterator owner/lifetime shaping problem. Together these establish two
0x14-byte short-deque headers at `SpellDataOwner+0x20` and `+0x34`, followed by
the 32-byte indexed output table at `+0x48`.

This allows parallel agents to work on small dependency boundaries without
abandoning central hard functions for easy progress counters.
