# Shared Fighter root: linked frame, switch and tail evidence

Target observations below refer only to Japanese TH105 1.06a, executable
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
`Fighter_update_common_action_state @ 4740C0` is a shared dependency of all
15 roster action roots. Its reviewed callable span remains
`[4740C0,4768AB)`, 10219 bytes / 2799 instructions, body SHA256
`7def23cf4826d7511260e7d9ea8db18848c43a7b77939bb42724a29af117a0c6`.
The provisional candidate, origin, name and source ledgers were checked.
No source selection, header, ABI ledger, match unit or exact credit changed.

## Selected source and ordinary controls

`src/battle/FighterCommonActionState.cpp` stays at on-disk CRLF SHA256
`f53478cf4aa721094a153c2c94991430e7f89007321daf599345a4bcdff23265`.
A fresh focused build still has strict first mismatch `+0x14 / 4740D4`,
10801 canonical section bytes and 53/66 instruction/edge-identical owners.
The section SHA256 is
`f72e0b9eed9f9ac5167af49873d7cd3a4c26712f7bdcd6c50b5249eeb5e6c045`.
Owner counts are diagnostic and award no authored bytes.

Three private ordinary-COFF controls were rejected:

| Source control | Section bytes | Identical owners |
| --- | ---: | ---: |
| Compare the stored float against zero at `LABEL_6`, removing `v3` | 10809 | 52/66 |
| Explicit high-dispatch guards and separate low/high switches | 11268 | 22/66 |
| Route action 50 through existing `v3/v4` and `LABEL_6/8` | 10717 | 51/66 |

The last control has the right conceptual shared destination, but VC8 moves
action 50's tail to action 162 instead of retaining the target's early tail.
Its action-50 owner shrinks from 134 to 49 bytes. Merely spelling the shared
goto does not recover the physical join. It also changes action 799's shape.
The canonical section SHA256 is
`57ca030b3f004e22e2aef9d4dc0d6774185af6e333b24c1709599eb33d71cc60`.

## Real linked controls

The existing real-link probe supplies 24 ordinary source provider objects,
the genuine SDK deque instantiation and pinned VC8 static CRT libraries.
27/28 selected dependency functions compare exactly; handle lookup `417800`
remains explicitly nonexact. There are no stub callees, code ABS bindings,
unresolved-link overrides or execution claims. Twelve data bindings refer
only to hash-attested target data; same-address view aliases remain provisional
C++ declaration hypotheses. The deque's complete 94-byte ABI/body witness
remains exact, with no authored library credit.

The script previously ignored `--help` and performed a build. This triggered
one baseline build during discovery. It is now an argparse CLI: `--help` is
read-only, and `--inspect-image/--inspect-map` reuse existing link products.
Subsequent controls compiled one private `/GL` root and relinked the same
hash-guarded providers sequentially, without rebuilding those providers.

Flattening the original nested dispatch into one cached-int switch recovers
the target's `SUB EAX,50`, but coalesces low destinations from 51 to 48.
Narrowing only locals `v3/v4/v30/v53/v58/v63` from double to float also
removes the candidate's aligned EBP frame. `/Z7` does not restore the missing
destinations. These local-type changes are unselected hypotheses.

A further control puts complete action 50/51/52/62/63/64 bodies in six real
`__forceinline` member helpers. The 63/64 parent sites return rather than
joining the old switch exit. Combining this with the narrowed locals gives:

| Root shape | Code plus pre-table padding | Reachable code | Low/high destinations | E8 calls | Virtual/direct tails |
| --- | ---: | ---: | --- | ---: | --- |
| Unmodified generated baseline | 10236 | 10233 | 51/15 | 207 | 0/0 |
| Flat switch, floats, six helpers | 10472 | 10470 | 50/15 | 205 | 8/13 |
| Original nested switches, floats, six helpers | 10248 | 10247 | 51/15 | 200 | 8/13 |
| Target | 10220 | 10219 | 51/15 | 198 | 8/13 |

The nested control restores the target JE-to-action-54 edge but retains
`ADD EAX,-50`, whereas the target uses `SUB`. Its 28 extra reachable bytes
do not mean it is almost exact: only 46/66 diagnostic owners agree, versus
53/66 in selected ordinary source. Restoring all six double declarations
and the 63/64 parent breaks brings back the aligned EBP frame and loses the
target-shaped tails. No helper boundary or local type was adopted.

The two extra direct calls in the nested float/helper control are both
physically owned by **low:162**: target one E8, candidate three. The candidate
duplicates boundary classification and frame advancement there; the target
reuses action 50's tail. All other physical owners have equal direct-call
counts. This locates a concrete sharing problem rather than a global flag
or general LTCG limitation.

## Closing legitimate tails without masking bytes

The old linked CFG inspector rejected any register exit or direct external
JMP. The new opt-in common-root qualifier keeps those raw inventories and
requires all of them to receive independent ABI evidence:

- The entry has the reviewed four-byte frame and saved EBX/ESI/EDI shape.
  Receiver flow traverses the same reachable instructions as the raw CFG.
- All eight register tails preserve the entry receiver in ECX and load slot
  `+14`. The existing target audit reattests 16 distinct RTTI/vtable owners,
  primary CharacterEx PMD `(0,-1,0)`, and common target `45C220`.
- The thirteen direct tails resolve through unique, same-address-normalized
  map identities. One calls scratch reset `435110` with `ECX=this+4`; seven
  call advancement `4351C0` with `ECX=this`; five call motion reset `45AF40`
  with `ECX=this`. All three actual linked helper bodies are raw-equal to
  their accepted 67/62/27-byte target bodies and have plain zero-pop RETs.
- Every tail has the complete reviewed frame restoration. Only the observed
  receiver setup and final field/conversion operations may intervene, and
  no branch or switch destination may enter inside that epilogue.

An unknown receiver, conflicting flow join, other vslot, missing restore,
unreviewed epilogue operation, changed linked callee or unqualified exit
blocks closure. The default inspector still rejects external tails.

Three negative controls mutate only a disposable copy of the linked probe,
never the target: `this+4` to `this+8`, `ADD ESP,4` to `ADD ESP,8`, and one
byte in the actual motion-reset callee. All three are rejected by their
corresponding receiver, frame or callee-body check. The copy was removed.

Diagnostic replay accepts an external E9 only at a qualified instruction
site whose unique map identity agrees with the canonical callee. It rewrites
only that REL32 displacement; E9 stays E9. Missing, wrong, ambiguous or unused
qualifications fail. All HIGHLOW fields, literal identity/width/section,
target data bytes, jump-table indices/destinations and alignment still pass
the full existing checks. No accepted-unit comparator was relaxed.

The nested control consumes all 180 HIGHLOW fields, including 66 switch
destinations, four table references and 110 literal references. Its full
canonical envelope SHA256 is
`426220470224a09c9ceced017ce30a4a53fbeb835aab61ddaf5e8e2e6b1498ea`.
The strict 10219-byte window SHA256 is
`68181f50c909f57b44bbb602accd548d43779bece53370df9b62dd04e38ce7f5`;
it remains **nonexact at +0x14 / 4740D4**. This is diagnostic comparison,
not an original-TU, gameplay-equivalence or acceptance claim.

## Reproduction and analysis provenance

```bash
python3 scripts/build.py --unit gpt-web-fighter-common-action-state --compare --json
python3 scripts/audit-common-fighter-indirect-tails.py --json
python3 scripts/probe-common-fighter-ltcg.py --inspect-image build/common-fighter-entry/nested-float-handlers/CommonRoot.dll --inspect-map build/common-fighter-entry/nested-float-handlers/CommonRoot.map
```

Without cached providers, the original no-argument link probe regenerates
them. Inspect mode checks target/tool/library hashes, all provider object and
source hashes and their current unit-input digests before reuse. Its receipt
attests the inspected image/map hashes, not a new build. Private control
patches and the one-root compiler/link commands remain in
`.analysis/common-fighter-entry-20261017/` and the ignored build receipts.
The nested control's generated source SHA256 is
`a2070ee3dbeabfc4c1c1f9fdc412d4fcd1810ffa8a3d6fdb6af730b3e728f5cd`.
Its linked image SHA256 is
`93a88aba314d167e14913c5933a4870e80a732c24c39299ff84af350e54de51a`.

IDA preflight still rejects the wrong executable. A single direct read-only
Ghidra clone, capped at 768 MiB/two CPUs, independently attested imported/file
identity, entry `68B9D2`, Windows x86 language, complete mapped `.text` and
this root hash. It read back `SUB @4740DE`, the rounded clamp at `474122`,
the pop/join at `474139/47413B`, advancement at `474161`, representative
direct tails, and both destination/index table pairs. The success marker was
checked; all nine primary database files stayed hash-identical, and the
disposable clone was removed. Database analysis remains corroboration.

Next: recover the action-50/162 shared x87 continuation while retaining the
current exact local owners, then address the 73/88 block movement. Keep the
linked tail qualification available; do not repeat the rejected dispatch,
local-type or helper shapes without new evidence.

Obsolete generated build trees/reports and rejected-control binaries were
removed: 63723419 bytes (60.77 MiB), leaving 2668335 bytes before the final
CI gate. Retained products cover the current ordinary root, two linked
controls, their evidence and the 24-provider cache. The separate Ghidra
clone had already been removed. Toolchains, canonical target and primary
analysis databases were preserved.

A fresh ordinary check commutes the shared `v4 > v3` predicate to `v3 < v4`
without changing types or rounding points. It falls to52/66 with10805 section
bytes, emits `FCOMP` against memory zero rather than target `FCOMP ST(1)`,
retains late162 ownership and loses799. Section SHA256 is
`0aa2e5a4b3a1d42d03f602f8032388c179d59ad4fb7a758503ef2cfcd41a5b97`.
This reconfirms an old source-shape negative and is not adopted. Active work
moves to [Reimu's81550-byte root](REIMU_ACTION_ENTRY_2026_10_17.md) instead of
repeating the existing common-root control matrices.
