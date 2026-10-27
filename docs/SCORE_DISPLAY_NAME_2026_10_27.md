# Score display-name selection, 0x0042E990

## Observed target and boundary

The canonical Japanese 1.06a executable SHA-256 remains
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
The complete 990-byte body ends with RET8 at 42ED6B, followed by two INT3 bytes.
All 311 decoded instructions are reachable through direct edges. There are no
inline tables, remote chunks, indirect calls or branches. Canonical body SHA:
848993bfd662100b1cb3b0792b6ad3ffca55dd03c30f240312707ea91d9fb6e6.

CMenuEnd calls the body at 4405D2 with ECX from the score-data accessor, an int
character key and a pointer to its live native string; it tests AL afterward.
This authored UI caller and the game-specific score/record policy establish
ownership independently of adjacency and IDA's provisional candidate name.
The preserved native 4C-byte allocation has GS/EH setup and handler 6B7FB0.

The direct repository IDA preflight failed because mcp==1.26.0/uv was unavailable
in its launch environment. The authorized Factory native IDA route subsequently
attested the correct file hash, base, entry 68B9D2, required operations and first
inventory entry. Its entry bytes e8ca9f0000e916feffff matched the canonical PE.
Disassembly, decompilation and the 4405D2 xref query succeeded. The decompiler is
corroboration, not source or byte authority. The previous wrong-target GUI note
is not evidence about this freshly attested session.

## Complete source behavior

`src/config/ScoreDisplayName.cpp` uses a non-instantiated bounded score view,
real VC8 vector/map/deque/string types and the already reviewed 20-byte deque
plus 12-byte spell-map resource group. It does not claim the original class name.

- Unsigned RNG(10) result zero selects common key 15; values below five select
  from the secondary vector at +6C; other values retain the requested character.
  The native empty-vector guard remains; there is no added fallback.
- A separate RNG(10) chooses signed-byte category 2, 1 or 0. The native signed
  word at spell-record +3E is compared against its sign extension.
- A real deque collects matching map keys, preserving ordered traversal. The
  character path loads its resources and ignores the loader return value.
- Empty choices return false without modifying the output. Both RAII owners
  still clean up. No explicit resource clear is added to this early exit.
- A uniformly indexed choice is looked up through the existing local/common
  record service; the name is assigned to the caller's string without a new
  null check. The common map at +9C or character map at +A8 + 12*character gets
  an absent zero-valued entry, then a separate find post-increments the count.
- Only an old count of zero appends the exact 26-byte `<color FF8080> new</color>`
  literal. The character success path explicitly clears spell entries before
  normal reverse destruction. The common path does not add that call.

Native output stores and converted-key temporaries support an unsigned selected
key passed to signed map keys; the iterator storage is shared across the real
common/character workflows. These are source-shape inferences, not recovered
original declarations. No assembly, padding, artificial locals or ABI changes
are used. All callee implementations remain outside this ownership increment.

## Complete-body trials and exact result

Every trial compiled the complete function serially on CPU0/nice10 with the
unchanged VC8 SP1 O2/GS/EH profile. Original first source: 1041 bytes, 941 unequal
positions among shared bytes. Explicit count initialization produced 1017 bytes;
unsigned key with that lifetime produced 1023. A const-reference control was
byte-neutral. Reversed end/find comparison produced 981 but removed a native
owner check and was rejected. Unsigned-key temporary comparison produced 993;
sharing the real spell iterator recovered the native frame and first 205 bytes.
Finally, a real default-constructed count iterator assigned before the comparison
preserved the target's find-before-end sequence and recovered **990/990 exact**.
The final source has no shaping-only objects; both iterators are used.

The canonical manifest unit is `exact-first-score-display-name`. Its formal
comparison validates the whole COFF section and replays every relocation, not a
masked or structural score. The 6B7FB0 EH address and 6C1168 string are separately
bound in the relocation ledger. The 42D1B0 checked deque index and 6183F0 append
remain compiler/container services, not newly accepted authored functions.

Reproduce with the pinned repository launcher:

```
scripts/repo-python scripts/build.py --unit exact-first-score-display-name --compare --json
scripts/repo-python scripts/audit-score-display-name-target.py --object build/match-units/ExactFirst_ScoreDisplayName.obj
```

Receipts and complete trial sources are under
`build/frontier-42e990-20261027/`: first/count/key/end-first/count-ref/temp-key/
iterator/shared-count/count-assign comparisons, `formal-first.json`,
`formal-audit-first.json`, `formal-second.json`, `formal-audit-second.json`,
`origins-write.log`, `origins-check.log`, `cold-all.log`, and `local-ci.log`.
The already-started cold aggregate passed all529 units/1417 functions. Initial
CI found four stale inventory assertions; only their current counts were fixed.
Final `local-ci-final.log` is pending at writing and its exit file controls the
checkpoint. Future iterations follow focused new/affected-unit builds rather
than repeating this full-corpus run. Prior accepted units are not silently
reclassified or given new exactness credit.

## Limits

The static audit checks full closure, RET8, AL-consuming caller, 15 container
guards, exact call census and the literal. It adds no runtime matrix. RNG,
resource I/O, STL implementations and exception unwinding are not executed by
this audit. Original nominal class identity, source spelling and TU remain
unknown. Exact compiler output is not a claim that those unknowns were recovered.
