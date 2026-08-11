# Spell-card system reconstruction map

This is the breadth-first map for spell-card data, assets, battle sequencing,
and the handoff into the fifteen character dispatchers. It is based on the
Japanese v1.06a target and one SHA-attested IDA MCP survey:

```bash
python3 scripts/core-lane-survey.py \
  --lane spell-assets --lane spell-data --lane spell-runtime \
  --output build/spell-system-survey.json
```

The survey currently covers 34 registered core functions. The first expansion
pass found eight additional direct parser/runtime dependencies that had still
been `unclassified`; they are now explicit nodes in the core graph. Function
ledger boundaries remain authoritative even where IDA groups adjacent chunks.

## System tree

```text
SpellDataOwner [layout contracted]
├── +0x00 DwordDeque4 image/resource handles
├── +0x14 SpellTree local records, int key -> 0x4C SpellRecordView
├── +0x20 ShortDeque8 loaded IDs
├── +0x34 ShortDeque8 selected IDs
└── +0x48 selected-value table

CSV and asset load
├── 0x00430DE0 loader selector [exact]
├── wrappers
│   ├── 0x00432D80 first-parser wrapper [implemented]
│   └── 0x00433490 resource-parser wrapper [implemented]
├── free parser ABI, not SpellDataOwner members
│   ├── 0x004325B0 five-argument filtered parser [implemented]
│   └── 0x00432E20 four-argument card-resource parser [implemented]
├── CSV reader 0x0040EB20/EE50/EF50/F050/F780 [decompiled]
├── record/tree contracts
│   ├── 0x00431950 SpellRecordView deep copy [exact]
│   ├── 0x00431430 int-tree iterator predecessor [library exact]
│   ├── 0x00432310 int-tree unique insert [library exact]
│   ├── 0x004316C0 int-tree checked find [library exact]
│   ├── 0x00431590 short-tree nil allocation [decompiled]
│   ├── 0x00431730 short-tree checked find [decompiled]
│   ├── 0x00431ED0 short-tree unique insert [decompiled]
│   ├── 0x00432040 checked ShortTree range erase [decompiled]
│   └── 0x0042D240 SpellTree recursive subtree destruction [implemented]
├── owner cleanup
│   ├── 0x00432500 clear image handles and record tree [exact]
│   └── 0x004132D0 clear DwordDeque4 storage [decompiled]
└── resources
    ├── 0x00404EC0 acquire/load one texture handle [decompiled]
    ├── 0x00404F30 build 512x256 composite [decompiled]
    ├── 0x00416A50 four-byte handle deque append [library exact]
    └── 0x00406C30 optional sprite resource vcall adapter [decompiled]

Post-load and battle runtime
├── 0x00430C80 finalize loaded spell data [implemented]
├── 0x00430D90 select queued record ID [exact]
├── 0x004317A0 local-then-common record lookup [implemented]
├── 0x0045C690 prepare next sequence slot [implemented]
│   ├── slot is 0x98 bytes: two shorts + 0x94-byte sprite
│   ├── 0x0045C5A0 allocate/enqueue slot [exact]
│   ├── 0x0045C440 VC8 deque<FighterSequenceSlot>::_Growmap [library exact]
│   └── 0x00453B70 copy the embedded sprite [decompiled]
├── 0x0045BBB0 front-entry availability gate [exact]
├── 0x0045BC30 consume/callback/statistics/advance [implemented]
├── 0x0045BA40 pop front and publish next record fields [implemented]
├── 0x0045C7A0 rotate front sequence slot to back [implemented; 15/15 roster]
├── 0x00431860 configure indexed record display/callback state [compiles]
└── 0x0045C8B0 action-change indexed sequence window [implemented]
    ├── 0x0045B900 checked iterator dereference [implemented; 38-byte exact prefix]
    ├── 0x0045C620 native VC8 checked deque erase(iterator) [library exact]
    └── display callback + embedded sequence effect publication [effect exact]

Character fan-out
└── fifteen input dispatch roots -> docs/CHARACTER_ACTION_ROOTS.md
    ├── shared fourteen-helper command prelude
    ├── record IDs 200-series
    └── character spell actions 600-series plus roster-specific 650+ branches
```

The action-change bridge `0x0045C8B0` now has complete compiling source for
all observed checked-range, iterator, effect, display-callback, erase-loop, and
live-count behavior. Its standalone VC8 object is 392 bytes against the
446-byte target, with the first delta at `+0x02`; exact work is isolated to
stack/register shaping and target-style repeated checked deque expansion.

The adjacent `0x0045C7A0` is an all-roster input-selector primitive rather
than an orphan: every one of the fifteen character input roots tail-jumps to
it when switching the shared sequence mode. Its source checked-copies the
front 0x98-byte slot, destroys and pops the original, enqueues the copy at the
back, and republishes the live count. The 247-byte standalone object versus
265-byte target isolates the remaining gap to the original CSprite copy/EH
special-member folding.

## Corrected ABI and layouts

IDA callers prove that both large parser bodies are callee-cleanup free
functions. `0x004325B0` receives character name, path, the owner's handle deque
at `+0x00`, destination tree at `+0x14`, and a mode argument. `0x00432E20`
receives the same first four arguments without the mode value. The prior
unused-`this` member model was false and has been removed from the source
contracts.

`0x0045C5A0` allocates `0x98` bytes per queued entry. It copies the record ID
and word at `+0x00/+0x02`, then calls `0x00453B70` to copy the `0x94`-byte
sprite at `+0x04`. This proves that the old four-byte enqueue parameter was an
incomplete view, not a standalone record type.

The adjacent `0x0045C440` body is not authored pointer-array growth. A native
VC8 `std::deque<FighterSequenceSlot>` probe matches the 338-byte ledger body
exactly; its `UINT_MAX / 0x98` length gate proves one sequence slot per deque
block. The object's three bytes beyond the ledger span are alignment only.

RTTI further identifies the embedded 0x94-byte payload as the global
`CSprite`, derived from `CSpriteBase` and `IColor`, with vtable `0x006AC668`.
The target's EH cleanup at `0x0045B8F0` only restores the IColor vptr. A
truthful derived-class probe produces the required GS/EH frame but calls an
out-of-line IColor constructor that the linked target folded away; therefore
`0x0045C690` remains an explicit special-member/LTCG blocker rather than being
modeled as a trivial byte blob.

The two large parsers share the row schema: integer key, owning name string,
one-byte selector, signed short value, owning description string, and two more
short values. The optional resource path is
`data/card/%s/card%03d.bmp`. Rows are inserted into the int-key tree; when an
image owner exists, groups of sixteen names are joined with `<br>`, rendered to
a 512x256 composite, and published back to the most recent records.
`0x004325B0` additionally builds and consults a short-key temporary tree and
erases it at exit. Its complete authored source now compiles to 1960 bytes
against the authoritative 1885-byte ledger body with every relocation
resolved. The first-byte delta is the VC8 aligned EH frame, so exact work can
start from a bounded compiler-shaping packet rather than rediscovering parser
behavior. This pass also corrected `0x00432040` from a SpellTree-specific
contract to the concrete ShortTree specialization used by the parser.

The spell-sequence consumer `0x0045BC30` now emits the exact target size
(346/346); its first 204 bytes match exactly. The remaining delta begins after
the second checked-front access and is limited to value-register and store
scheduling, while callback, statistics, sequence advance, lookup, and terminal
state behavior are all present.

The shared indexed display callback at `0x00431860` now has complete source and
a full `PlayerIndexedCallbackView` layout through its 0x154-byte caller stride.
It handles the null-source clear path, initializes the six display parameters,
performs the local-then-common record lookup, clamps name width to 272 pixels,
selects the normal or alternate vertical alignment, invokes the embedded
display receiver's vtable slot `+0x10`, and publishes the active/source fields.
The canonical VC8 object is the exact target size (234/234) and matches the
first 113 bytes.  The remaining delta begins at the optimizer's choice of
`EDX` versus `EDI` for name length and clamped width, so this is now a bounded
exact-tuning packet rather than an uncovered gameplay callback.

The owner cleanup at `0x00432500` is now exact at 171/171. Its source releases
every image handle, clears the four-dword deque, calls `0x0042D240` as a real
`SpellTree::__thiscall` member, and restores the tree sentinel and count. This
exact caller corrected the previous free-function ABI hypothesis for the
recursive subtree destructor.

The neighboring sequence advance at `0x0045BA40` also has complete source. It
checks and removes the current deque entry, performs the folded embedded-sprite
cleanup, publishes the signed state byte, and conditionally copies the next
record's maximum. A truthful `CSprite` destructor expression now produces an
exact-size 198/198 object and extends the exact prefix to 46 bytes. The remaining
delta is checked-end operand scheduling and the target's LTCG-folded
CSprite/IColor cleanup rather than missing gameplay behavior.

`0x0042D240` now also has complete recursive destruction source: it destroys
right subtrees, walks left, releases both owning strings, and frees every
non-nil 0x60-byte node. The strict result is 116 bytes against the 108-byte
ledger span with first mismatch `+0x0C`; only VC8 prologue/register scheduling
remains after the member ABI correction proved by exact `0x00432500`.

## Boundary gate

Six IDA boundaries disagree with the ledger and are deliberately not adopted:

| Address | Ledger bytes | IDA bytes | Rule |
| --- | ---: | ---: | --- |
| `0x00408B40` | 183 | 186 | keep ledger span |
| `0x0040EB20` | 164 | 170 | keep ledger span |
| `0x0040F780` | 119 | 125 | keep ledger span |
| `0x00430C80` | 257 | 260 | keep ledger span |
| `0x004325B0` | 1885 | 1985 | keep ledger span |
| `0x00432E20` | 1602 | 1644 | keep ledger span |

These are work-packet conflicts, not permission to extend comparison ranges.

## Exact-match fan-out frontier

Breadth is now sufficient to split exact work without rediscovering the graph:

1. Runtime lane: finish the post-`+0xCC` VC8 schedule in exact-size
   `0x0045BC30`, then use the complete 185/198 `0x0045BA40`, exact
   `0x0045C5A0`, and library-exact `0x0045C440` to isolate the shared
   CSprite/LTCG boundary at `0x0045C690`.
2. Data lane: `0x004317A0`, exact-size `0x00431860`, `0x00430C80`, and the complete 116/108
   `0x0042D240`; retain exact `0x00432500` as the cleanup regression gate.
3. Wrapper lane: `0x00432D80` and `0x00433490` after the corrected free-parser ABI.
4. Hard parser lane: tune the now-complete `0x004325B0` and `0x00432E20`
   sources with their strict tree/string/resource relocation manifests while
   keeping all six boundary conflicts fail-closed.
5. Character fan-out: split each dispatcher into its proven 600-series spell
   group only after the shared sequence and record contracts above compile.

No empty parser, runtime, or character body should be added merely to link a
larger target. Unimplemented branches remain declarations and ledger packets.
