# Reimu: complete returning projectile requests

The `478FA0` root now has **800 passing native comparisons through complete
owned-object requests and volleys**, including nested object811 companions.
The previous request-entry stops did not execute these returning callbacks.
This extends [the real effect backend](REIMU_EFFECT_RETURNS_2026_10_18.md);
the selected game source, compiler profile and exact ledgers remain unchanged.

## Target and observed manager path

Target is the original Japanese TH10.5 1.06a executable, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete root remains `[478FA0,48CE2E)`,81550 bytes. The IDA preflight
rejects the different attached executable; these observations use canonical
PE bytes and actual native execution, without database or instruction writes.

The actual manager constructor `493750` calls base construction `493570`,
installs vptr `6C40FC`, records the owner at `+64`, and preallocates/releases
**256 objects** through `4936D0`. The experiment executes this complete path
for each input. It checks256 pool slots, generations and free entries before
entering the root; it does not replace the constructor with a smaller pool.

The root's real wrapper `465190` dispatches manager slot+4 to `4938D0`.
The actual `4935E0/493340` acquire/link path reuses slots from255 downwards;
generation starts at257 after preallocation. The manager allocates/copies the
live caller parameter array, installs owner/related/peer/resource links and
invokes the real action selection and virtual callbacks. The root then resumes,
prepares subsequent arrays and finishes its frame/state work through RET.
The actual owning destructor `4939C0` runs after each snapshot, including
object, parent/child, container, heap and lock cleanup.

## Nested811 behavior

An initial five-request811 fixture returned **ten tracked objects**, exposing
another real callback layer. Each sequence0 parent creates a sequence1 object
of the same id. The observed copied parameters are `(angle,speed,0)` for the
parent and `(angle,0,1)` for its companion. List order alternates parent/child.
Each parent has one child in its checked deque at `+350`; the child points back
through `+34C`. All objects retain the real Fighter owner/related/peer links.

Canonical callback bytes independently corroborate this graph. The vptr
`6C40A4` points slot+3C to `4A1CE0`. Its sequence-zero branch at `4A1EF2`
prepares angle from `+12C`, zero and one, then calls the existing parented
wrapper `4FCA60` at **`4A1F3C`**, with id811 and three copied words.
That exact-backed wrapper forwards this object as parent and its related
Fighter to the same manager. The4892-byte callback ledger extent is still
provisional; this window does not establish a new compiler boundary, source
selection or exact result for that callback.

| Root actions | Object id | Direct requests by level0/1/2 | Tracked objects after callbacks |
| --- | --- | --- | --- |
|500/501/502/503|810|2/4/6|2/4/6|
|505/506/507/508|811|3/4/5|6/8/10|
|510/511/512/513|812|3/4/5|3/4/5|
|410/414, first and second shot nodes|801|one per node|one per node|

These are dynamic request/object counts, not physical call-site equality.
All copied parameter sequences and their order are checked against actual
target results. In particular, all positive and negative fan iterations return
before the next root array update; neither later requests nor companions are
simulated.

## Native comparison

`scripts/audit-reimu-owned-returns.py` reuses the effect auditor's base-producer,
complete relocation, callable/metadata and eleven stack/request checks. The
two native hosts now share `scripts/native/reimu_native_host.hpp`, including
the partial PE loader, real CRT setup and code protection/checks. The common
header is included in input hashes. Executable allocations also flush the
instruction cache after protection changes. No accepted game unit depends on
this tool header.

As before, the host resolves105 real kernel32 imports, blocks65 other imports
and terminates on exceptions. The canonical executable remains at `00400000`;
the qualified source-derived COFF root has separate protected storage at
`04000000`. Every original `.text` byte and every candidate byte is checked
unchanged after each case. The linked diagnostic DLL is not executed.

The supplied, read-only animation graph includes both Fighter and projectile
actions, nine sequences, fourteen-frame capacity, zero textures and zero wave
handles. It is fixture data, not game assets. Target `4065B0` initializes the
actual orientation table at each requested PC53/64 setting; target `406670`
then seeds MT with0 or5489. The symbolic `_control87` conversion remains
distinct from raw hardware control words.

The full cohort has720 fan inputs and80 aiming-shot inputs. It crosses all12
fan actions/three levels and both410/414 shot nodes, five raw facings, both
precisions and two seeds. Each process executes2960 direct requests and960
companions: **3920 tracked projectile results**. Target self-checks require
the expected complete volley, final sequence/frame/timer/counter/state, pool
generation/free counts, action ids and full copied-parameter sequence.

Snapshots include all4096 actor bytes, all904 bytes of each tracked object,
its allocation pointer, actual parameter heap extent and copied words, logical
child deque entries, MT index/state, pool counters and observed FP control.
Const VC8 `std::deque<void*>` views read the target's existing child entries;
no game container operation or result is replaced. Unused container capacity,
inactive pool-object bytes, allocator metadata and other globals are outside
the snapshot. No compared bytes, pointers or padding are masked.

| Witness | Inputs | Differences |
| --- | ---: | ---: |
| Expanded ordinary root, complete real backend |800|0|
| Independent repeated target process |800|0|
| Wrong third811 projectile angle |800|80|

Each complete passing snapshot stream is **8,947,204 bytes**, SHA-256
`dbe66ddc071d51b5b40b3c689170124afb339ba0e564e626a116eb17a75b26c2`.
The14-input smoke subset also passes, with50 tracked objects per process.

The compiled negative changes the third direct811 projectile's level0 angle
from-10 to-15 after two complete requests. All12 unoptimized expanded source
arms contain that expression; only505..508 survive constant folding. It
retains the strict envelope and all static contracts. The first four complete
object/parameter/child records remain byte-identical in all80 differing cases:
the first two direct projectiles and their companions are correct. The third
projectile/companion differ, while all800 actor snapshots stay equal. Thus the
test detects a later-volley error that an initial request-entry check misses.
This private control never changes selected reconstruction source.

## Reproduction and current limits

Run heavy commands serially on CPU0 at nice10:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-owned-returns.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-effect-returns.py
```

Use `--smoke` for the14-input owned subset. For the negative, copy the base
producer's expanded source/header below `build/`, require exactly12 occurrences
of `parameters[0] = -10.0f; parameters[1] = 23.0f; parameters[2] = 0.0f;`, and
change only the first constant to-15. Compile with the base ordinary compile
receipt's command, changing only source and `/Fo` paths, then pass that object
with `--object` and a separate output directory. The resulting audit returns1
for80 differences. Private compile/native receipts are under
`build/reimu-owned-control/`; the positive is under `build/reimu-owned-returns/`.
Large temporary streams/build products can be regenerated and are cleaned
after verification; compact witnesses and receipts remain.

The shared-host change also requires the focused effect regression: current
effect123 remains0/600, and its post-effect wrong-comparison control remains
480/600. No old full historical matrix or aggregate cold replay is claimed.
All builds/native processes ran serially with child peak RSS approximately301MiB.

The selected ordinary object remains
`41bf3b15ff2dbf6cf7c25e0c0191ab18d963782e0e7fab5d3b9af82c0ab245fd`,
and base canonical payload remains
`826889ee7ec055e44def5cc1602de2fae75f58403e2332194ec3b20cd55dc0d3`.
Root prefix81544/text82916/frame570h and first strict+17/478FB1 persist.
Native equality does not confer canonical byte equality. Root remains
unclassified/declaration-only; there is no new source-present/exact credit.
Other returning effect/projectile families, arbitrary runtime/heap/resource
states, exceptions and complete application initialization remain unproved.
Continue closing those paths and the physical sharing/source-context gaps
before accepting the root.
