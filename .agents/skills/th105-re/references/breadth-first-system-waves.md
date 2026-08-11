# Breadth-first subsystem waves

Use this workflow for central gameplay systems with many interconnected
functions. It complements exact matching; it does not weaken its acceptance
rule.

## Why this is the default for large systems

Per-function exact tuning is efficient only after the shared ABI, container,
vtable, and dependency graph are reasonably stable. Otherwise several workers
rediscover the same layout and independently tune source against a false
boundary or guessed call convention.

The first TH105 spell/battle wave moved the ledger from 58 to 94 decompiled
functions, expanded the core graph to 370 functions and 429 dependency edges,
and immediately produced two useful exact results: the authored 114-byte
sequence enqueue and a 105-byte native VC8 map specialization correctly moved
to `library`. A second one-hop BattleController expansion then identified
thirteen more formerly unclassified shared setup, input, scenario, fighter,
and manager functions. These are useful unlocks even before their compiler
scheduling is tuned.

The first Battle exact fan-out then converted that breadth into 761 exact
authored bytes: the 529-byte seven-state dispatcher, 224-byte packed local
control collector, and 8-byte synchronized-input availability leaf. At the
same time it bounded the adjacent hard paths instead of hiding them: the RAII
gate is 127/129, synchronized publication is 258/240 with an entry-register
blocker, and fixed-slot save/load have clean-relocation layout probes. This is
strong enough evidence to make the wave loop the default for large gameplay
subsystems.

The next packets added exact setup (479), roster preparation (337), round
initialization (299), terminal publication (90), and spell-linked resolution
(358). Those 1,563 bytes all reuse the same controller/input/fighter contracts,
while their calls promoted setup-slot, fighter-slot, tally, and post-sequence
boundaries for the next breadth layer. This is the expected compounding effect:
new structure lowers exact cost, and exact relocations make the following map
more precise.

A later roster-policy wave shows how to handle huge functions without turning
breadth work into speculative source. One priority-one Aya root at `0x00611D80`
was resolved through its fighter vtable `+0x58` slot. Reading the same slot in
all fifteen vtables exposed four overrides (Reimu, Marisa, Alice, Aya) and one
default body shared by the other eleven fighters. All five are approximately
16 KB, use the same five direct callees, and read/write the same fighter policy
fields. The coordinator recorded a single typed 0x770 view, five signatures,
the vtable ownership matrix, and the full direct dependency set, but left the
functions `identified` because their dozens of action cases are not yet source
implementations. This is the preferred monolith split: map ownership, shared
layout, cases, and dependencies first; factor a common skeleton next; only then
fan out exact tuning.

## Coordinator loop

1. Select one subsystem and its existing core lanes. Verify the target and run
   `scripts/core-worklist.py --ready`.
2. Claim a small, explicit address set. For an existing lane, capture a
   SHA-attested survey:

   ```bash
   python3 scripts/core-lane-survey.py \
     --lane spell-data --lane spell-runtime \
     --output build/spell-system-survey.json
   ```

3. Reconcile every IDA boundary with the ledger. Record disagreements in the
   subsystem map; do not extend an accepted compare span merely because IDA
   groups a tail chunk.
4. Expand at most one direct-call layer at a time. Prefer callees reached by
   several roots, functions joining two core lanes, and type/container
   boundaries. Stop at compiler/runtime/library code or unrelated UI/support
   leaves unless one concretely blocks the subsystem.
5. Promote rows only as far as evidence permits. A complete decompile plus
   calling convention, neutral signature, field/call facts, and boundary note
   may become `decompiled`. Add declarations or partial observed types, never
   fake-return or empty bodies.
6. Update `core-functions.csv`, `core-dependencies.csv`, `core-types.csv`, and
   the subsystem tree together. The graph should state why each new node
   unlocks the system.
7. Split the resulting exact frontier into non-overlapping packets. Assign one
   packet per evidence worker; the coordinator keeps all shared-file, ledger,
   claims, semantic-database, and Git writes.
8. Require each exact worker to return target/object sizes, first mismatch,
   relocation state, shaping class, a reproducible strict command, and minimal
   patch text or a concrete stop condition. Temporary probes are preferred to
   speculative shared edits.
9. Integrate exact results centrally, add canonical match units for durable
   regressions, update reusable VC8 patterns, release claims, validate, commit,
   and repeat from the newly unlocked call/type graph.

## Wave quality gates

A breadth wave is useful when it does at least one of the following without
creating unsupported semantics:

- removes several central `unclassified` rows;
- adds a shared ABI/type contract used by multiple roots;
- connects previously separate core lanes;
- turns a hard monolith into bounded exact packets;
- identifies compiler/library code that should not count as authored progress;
- yields an exact reusable helper or a precise fail-closed blocker.

Stop expanding when the next layer is mostly unrelated support code, when
function boundaries are unresolved, or when names would require guessing
gameplay terminology. At that point exact/type work on the current frontier is
more valuable than another call-graph layer.

## Evidence-worker packet

Send workers an address-bounded request containing:

- exact target identity and IDA-first/read-only rule;
- current source, types, ledger boundary, and known relocations;
- the strict comparator command or canonical match unit;
- permission for temporary probes but not tracked/shared writes;
- requested result schema: exact/mismatch/blocked, sizes, first mismatch,
  relocations, structural finding, minimal patch, and stop condition.

Clone similarity, matching object size, or visual decompiler similarity never
changes a row to `matching`. Only the accepted strict 100% comparison does.
