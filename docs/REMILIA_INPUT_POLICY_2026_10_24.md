# Remilia input policy: first complete medium-function exact representative

## Accepted result and replay

Remilia primary-vtable slot `+0x50` at `0x00556070` is now canonically exact
across **5,415 callable bytes**. The complete **5,448-byte emitted payload**,
including its alignment byte and eight-entry destination table, also matches.
This adds one authored exact function / 5,415 code bytes. Adjacent compiler
metadata earns no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-remilia-input-policy --compare --json
python3 scripts/audit-remilia-input-policy.py
```

Both commands must pass when replaying this representative. The first performs
the ordinary configured VC8 COFF comparison. The second uses the same strict
COFF owner/relocation/literal engine on the complete payload and requires its
exact length and all bytes, including switch metadata. It does not mask
registers, relocations, alignment or table entries.

An independent canonical build passed, then its active object/provenance were
removed after preserving the first object. A separate cold build passed both
commands again. Callable SHA256 is
`5826caad72458acb5c751f270555eca4c9d4cc0830c25fc3e9333d9cd9a20583`;
complete canonical payload SHA256 is
`aa8fea23fd443bab1f58993e3f8d41f3ee7d262b70f2ea3d5ec74a6e75c3dcec`.
Both builds use the unchanged pinned VC8 SP1 `/O2` profile, without assembly,
target arrays, inert locals, padding, fake returns or ABI workarounds.

Sources are `src/characters/RemiliaInputPolicy.cpp` / `.hpp`. The receiver and
sequence-subscript interfaces are pointer-only call views: never instantiate
or embed them. Numeric command keys, field offsets and independent repeated
calls intentionally remain. Original class identity, full layouts and original
return declarations are not recovered by the emitted-byte match.

## Observed target boundary, ownership and ABI

The target is only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The frozen RTTI anchor assigns pointer cell `0x006C5414`, primary slot `+0x50`,
to Remilia and this function. No origin classification changes.

Raw target CFG traversal reaches all **1,470 instructions**, with no missing
instruction starts or unresolved indirect exits. The callable is
`0x556070..0x557596`, ending exclusively at `0x557597`; its last instruction
is an internal JMP to the shared action-dispatch tail. There are **16 RETs**
and **eight external tail JMPs**: once to `0x45DDA0`, once to `0x464200`, and
six to `0x4633A0`. The frame has eight local bytes and saves EBX/EBP/ESI/EDI.

The next byte at `0x557597` is NOP alignment. The destination table occupies
`0x557598..0x5575B7`, with eight pointers to the reviewed 200..207 command
arms. The eight subsequent INT3 bytes precede the next callable at `0x5575C0`.
These bytes are not folded into the authored callable boundary.

The body has **109 physical calls**: 94 direct and 15 virtual slot `+0x08`
calls. Direct calls include five stage predicates, six native deque subscripts,
two front-entry predicates, eight command finalizers, 45 command-window
queries, 19 packed-input initializations and nine other gate calls. All normal
and tail destinations are bound separately. The complete COFF section has
**112 relocations**: 94 call fields, eight tail fields, one numeric reference,
one table address and eight table entries.

The entry consumes only ECX this and has no stacked arguments. Existing
accepted wrapper `run_common_character_update @ 0x45B420` already models
slot `+0x50` as a result-ignored callback. This checkpoint retains that runtime
view without claiming an original void declaration. Action slot `+0x08` passes
ECX and one four-byte integer slot. The queued 700..799 path explicitly
zero-extends the selected word. All gate callees' actual native argument
slots, AL/AX/EAX consumption and RET cleanup were checked against their complete
bodies and existing accepted source. Declaration-only callees earn no source
or exact credit. In particular, `0x494450` and `0x45DDA0` stay unaccepted.

## Target-backed source details

The incoming signed window word at `*(this+15C)+12` and both command masks at
`*(this+158)+4C` are captured before the first possible external call. Later
fields and command-window queries retain their individual read/call epochs.
The native extra input guard is retained. Front-sequence checks call the real
subscript operation repeatedly, rather than caching the first record.

The repeated signed-byte tier gates and 500..599 override conditions remain
ordinary short-circuit C++. Every real store at +754..757, +491, +730 and +12C
is retained in its own path. Normal commands preserve set-action followed by
input reset, including the shared physical tail. The 90.0f distance test keeps
the native float subtraction and absolute-value rounding steps.

Do not normalize these observed differences:

- In the `0x40` command group, query 525 dispatches **526**, and query 520
  dispatches **521**. The `0x20` group keeps the unincremented action numbers.
- The air `0x20000000` tier queries **566** before dispatching **565**.
- Two directional branches can independently query command 402, or 412, twice.
  A failed first query does not eliminate the second actual call.
- Existing action 306 can dispatch **325** without another command-window
  query; the ordinary fallback separately queries and dispatches 306.
- Ground follow-ups are 321/frame>=8 to322, 320 to321 and 300 to320.

The first complete handwritten draft compared the whole body immediately.
That comparison exposed the two `0x40` action-number mistakes above. Correcting
them restored the target's two additional physical packed-input calls and left
only the initial queued-action range check different. The draft's eager local
cache emitted LEA/subtract plus one unsigned range guard; reading the actual
field directly emits the target's two comparisons, with identical defined
700..799 semantics. This third complete source compiled to zero differences.
This is evidence for this VC8 context, not a rule that field caching is always
wrong. No compiler-flag, hierarchy or broad register search was needed.

## Database evidence and retained receipts

IDA preflight again rejected its mismatched open image. Ghidra independently
attested the executable hash, Windows x86 compiler/language, image base,
entry `0x68B9D2` and every raw-backed section. It ran alone, read-only with
analysis disabled, CPU0/nice10 and a 384 MiB configured heap. The temporary root
and ABI metadata were read back and rolled back; all pinned primary database
files have identical before/after hashes.

The initial decompiler view incorrectly treated returning calls as PIC branches
and expanded tail callees, dropping real paths. Temporary native parameter,
return-width and purge facts repaired the normal calls. Observed external tail
instructions received temporary CALL_RETURN analysis annotations; indirect
action calls received their actual this/one-four-byte-argument view. These metadata changes
never patched target bytes. The final pseudocode is still a hypothesis; raw
pushes, conditions, field widths, complete CFG and canonical comparison control
acceptance. Source was written as natural C++ from those observations.

Private recipes and three complete source revisions are retained under
`.analysis/exact-first-remilia-slot50-20261024/`. Receipts are under the matching
`build/` directory: `raw-facts.json`, `target.asm`, `cfg-closure.json`,
`call-surfaces.json`, native callee exports, attested database logs/hashes,
`formal-compare.json`, `formal-full-payload.json`, `cold-compare.json` and
`cold-full-payload.json`.

A negative control changes only one byte in the generated COFF switch table,
not the target. The complete-payload audit rejects it at `+0x1528 / 0x557598`,
target B9/source BA. The source callable bytes remain untouched. Retain
`negative-table.obj` and `negative-table-result.json`; this proves the added
metadata check observes the table rather than merely trusting callable equality.

## Continuation and limits

This is the medium-function representative for further independently reviewed
Fighter slot `+0x50` peers. Reuse its common body only after comparing the new
root's complete boundaries, special gates, command/action pairs, offsets,
callee ABI and every changed exit. Do not infer identity from roster order or
copy addresses/layouts by delta.

The earlier RemiliaObject initializer `0x55BE70` remains nonexact and unchanged.
No large execution matrix, whole-game runtime result or aggregate cold replay
is claimed. The accepted root is byte-exact; names and gameplay interpretations
remain provisional. Existing accepted source/header inputs and unit descriptors
are unchanged.
