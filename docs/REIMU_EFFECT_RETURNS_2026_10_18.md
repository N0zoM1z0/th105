# Reimu: returning through a real effect manager

The root at `478FA0` now has a bounded native comparison **through effect123
creation and its returning continuation**. Earlier Unicorn cohorts stopped at
the real wrapper entry `435240`. This experiment executes the actual wrapper,
manager, allocator, locks and effect callbacks, then lets the root return.
The selected reconstruction source and exact ledgers are unchanged.

## Target and execution boundary

Target: original Japanese TH10.5 1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The complete reviewed callable remains `[478FA0,48CE2E)`, 81550 bytes, as in
[the entry evidence](REIMU_ACTION_ENTRY_2026_10_17.md). The IDA preflight still
rejects the different attached executable; no IDA semantics are used.

`scripts/audit-reimu-effect-returns.py` first audits the genuine base producer
and all eleven source stack/request contracts. It rejects callable or metadata
excess. It replays the ordinary COFF root at `04000000`, with actual canonical
callee/data addresses and correctly relocated local metadata. This candidate
has its own read/execute allocation; the original root stays intact.

The VC8 host in `scripts/native/reimu_effect_returns.cpp` maps the attested PE
at its preferred `00400000` address. The parent checks the complete file hash
before and after execution. The host compares every raw `.text` byte against
the file before execution and after every case, and protects executable
sections against writes. Candidate bytes are protected and checked too.
No original instruction, virtual entry, callback or result is replaced.

The host resolves all 105 kernel32 imports against Wine's real implementations.
The other 65 imports are null and any attempted use terminates the probe.
An exception also terminates execution; there is no resumed or substituted
exception path. The game entry point and application startup are never called.
This is a partial diagnostic loader, not a reconstructed application.

## Runtime and supplied data

Raw startup instructions `68B85B..68B8B1` establish five OS-version global
stores. The host supplies those stores from the real `GetVersionExA` result,
then calls the actual target security-cookie initializer `6959A1`, heap
initializer `695947(1)` and thread/lock initializer `68EDFA`. Both initializers
must return success. Heap allocation/free and critical-section operations then
run through original target code and real Wine APIs. No heap or lock stub is
installed. This does not establish complete CRT/application initialization.

Each case constructs a fresh effect manager with actual `4378F0`, checks its
`6C1490` vptr and `437C00` emission slot, and borrows two supplied untextured
resource-container headers at manager `+64/+88`. The separate actor/effect
animation graphs are read-only, at `03000000` and `03200000`; actor storage is
at `02000000`. They are fixture data, not original game assets.

The original root calls `435240`, which dispatches through that actual manager.
Its real acquire/link path `437BA0/4379D0` allocates an effect, updates checked
vectors/list and generation state, then `437C00` invokes the actual effect
selection and finalizer. The host verifies one linked object, matching pool
slot zero, generation one, handle `00010000`, vptr `6C14BC`, effect id123,
active state and the real actor context. The root then completes its remaining
sequence/frame work and returns to its ordinary C++ caller.

After taking the snapshot, the host restores the borrowed headers and calls
the actual owning manager destructor `437DF0`. Its object/container/lock
cleanup executes before the next case. The fixture covers fresh allocation;
pool reuse, loaded textures, other effect families and owned projectiles remain
outside this proof.

## Focused results

The full cohort crosses actions208/211/220/221/222, raw facings
`-128/-1/0/1/127`, initial vertical speeds2.5/20, X positions
`-0/640/33554432`, MT seeds0/5489, and x87 PC53/64: **600 inputs**.
The native host uses VC8's symbolic `_control87` masks, converting the requested
raw fixture words `027F/037F` into `_PC_53/_PC_64`; the API encoding is not the
raw hardware control word. It checks the observed API value after the root.

Counter5 forces the actual effect123 request before the continuation. Low
vertical speed then selects sequence2 for four actions, whereas211 skips that
condition. Target self-checks require240 sequence2/counter1 results and360
sequence1/counter6 results, all at frame0/timer1 with one real effect.

Each compared snapshot contains all4096 actor bytes, all376 effect bytes,
the MT index and2496-byte state, object count and observed FP control value:
**6980 bytes per input**. No pointer, padding or other bytes are masked.
The target is run twice in fresh processes and must reproduce every byte
before the candidate comparison is considered.

| Compiled witness | Cases | Differences |
| --- | ---: | ---: |
| Current expanded ordinary root, real backend |600|0|
| Independent repeated target process |600|0|
| Wrong post-effect vertical comparison |600|480|

The wrong source changes `< 4.0f` to `> 4.0f` in all eight expanded low-family
arms, retaining their shared compiler context. It still creates one actual
effect and returns, but chooses the wrong subsequent sequence. For example,
target208 returns sequence2/counter1, while this control returns
sequence1/counter6. Thus this check detects behavior after the old request-entry
stop. All600 effect/MT/count/FP portions still equal target; only the actor
portion differs in480 cases. Two earlier single-arm controls exceeded the strict envelope and were
rejected before execution; the envelope was not relaxed.

Receipts and native outputs are under `build/reimu-effect-returns/`; the
negative is under `build/reimu-effect-return-control/`. The passing complete
snapshot-stream SHA-256 is
`e536835e35f9d1cec1e42a0a63ed15a65cd41afbdbcb4830be61944ddfd8f4dc`.
The receipt records this digest along with repeated-target equality,
source/tool/input hashes, commands and Wine version. The initial completed
run used Wine9.0 and peaked at approximately301MiB child RSS across compilation
and native execution. All heavy commands ran serially, on CPU0 at nice10.
Large input/snapshot streams and unused native build products were removed
after verification; compact first-case witnesses and receipts remain. The
commands below regenerate the full streams.

## Reproduction and limits

With the current genuine base producer available:

```bash
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-effect-returns.py
```

Use `--smoke` for the40-input subset. For a compiled negative, copy the base
producer's expanded `root-input/ReimuActionStateDispatch.cpp` and staging
header below `build/`, require exactly eight occurrences of
`velocity_y_f8 < 4.0f`, and replace them with `velocity_y_f8 > 4.0f`.
Compile using the base `ordinary.compile-receipt.json` command with only its
source and `/Fo` paths changed, then pass the resulting object with `--object`
and a separate `--output-dir`. The audit returns1 for the480 detected
differences. Its private compile receipt records this natural wrong-source
control; no checked-in reconstruction source changes.

The selected ordinary object remains SHA-256
`41bf3b15ff2dbf6cf7c25e0c0191ab18d963782e0e7fab5d3b9af82c0ab245fd`;
the base canonical payload remains
`826889ee7ec055e44def5cc1602de2fae75f58403e2332194ec3b20cd55dc0d3`.
Whole-root comparison is still nonexact at `+17/478FB1`, with frame570h,
code prefix81544 and text82916. Native state equality is not canonical byte
equality. Root status stays unclassified/declaration-only, with no new exact
or source-present credit. No shared layout/profile or accepted unit changed,
and no historical full replay or aggregate cold replay ran.

This proves only the supplied single-thread effect123 contexts and compared
state. Other globals, arbitrary stacks/initial heaps, exceptions, rendering,
returning effect124/125 and owned-object manager continuations remain open.
Next extend this real backend to those request families while retaining the
unresolved physical call-sharing evidence.
