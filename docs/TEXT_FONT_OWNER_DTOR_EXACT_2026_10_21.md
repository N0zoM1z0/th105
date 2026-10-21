# Native font owner destruction: complete210/210 exact

`TextFontOwner194::~TextFontOwner194 @ 0x004114C0` is canonical
**210/210 bytes, all59 instructions**, from genuine native C++ GL/LTCG.
Constructor411430 remains138/138 in the same changed TU. The newly reproduced
71-byte STL cleanup is a compiler witness/exclusion, not authored exact credit.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking preflights pass. IDA rejects its wrong open
executable, so raw PE instructions and pinned compiler/header/link evidence
supply the facts. No database semantics/writes or original-byte patches are used.

## Complete boundary and ownership

Raw traversal reaches every210 bytes through RET411591, before fourteen INT3
bytes and the separate configure entry4115A0. Target/canonical source SHA256:
`bca6292e5e37ba2aadd6231017c3dcc9e10d28807ba36ae84fec4e4af07aa2de`.
The exact PlayerSlotRecord and NetworkSessionResult lifetimes call it at
4315E0/44DEF2, on the same physical owner used for construction/configuration.
These are independent ownership edges, not boundary guesses from adjacency.

The source's explicit destructor body:

1. While list15C is nonempty, delete the front unsigned array and pop/delete
   its node. Native checked front/pop guards and link/count writes are retained.
2. If base-color158 is nonnull, delete that array and zero158 inside the same
   branch. No additional target-unwritten pointer clearing is added.
3. Allow actual C++ member destruction to clean the string170 and list15C, in
   reverse declaration order. The string's heap/SSO choice, capacity15/size0/
   buffer-first-byte reset and final list cleanup are native library behavior.

This function does not own the separate GDI begin/end handle release. No source
GDI deletion, manual SSO/list destructor, fake return or synthetic cleanup CFG
is introduced. Original class/TU spelling and unobserved fields remain unknown;
the guarded194-byte source view continues to represent the observed ABI.

## Compiler-phase result

Ordinary COFF is203 bytes/54 instructions, nonexact+0. It has an ordinary frame,
saves EDI only on the nonempty-list path, and ends with a normal-ECX tail jump
to `_Tidy`. The genuine GL/LTCG caller/callee context yields the target aligned
EBP frame, whole-function EDI preservation and E8 call with the list in ESI.
The compiler then restores the parent's saved registers and returns normally.
All210 bytes agree, not merely those affected by the first mismatch.

The source uses standard destructor/member definitions. There is no forced
frame/alignment, inert local, explicit register ABI or invented provider.
The only initial comparison blocker was the linked resolver requiring the
actual decorated scalar-delete name `??3@YAXPAX@Z`; correcting that unit-local
mapping preserved all existing resolver rules.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-owner --compare --json
```

Selected current source SHA256:
`635607c583a855881f0cb45e40206f1a7afa9231d80f30c7e16d144f6d81c199`.

| Complete body | Bytes | Canonical SHA prefix | Credit |
| --- | --- | --- | --- |
| constructor411430 | 138 | de916b65 | previously accepted authored |
| destructor4114C0 | 210 | bca6292e | new authored exact |
| compiler `_Tidy`408A00 | 71 | a3e8a804 | compiler-only witness/exclusion |

All three have full symbol/CFG boundaries and zero differences. Existing five
GS-support IAT bindings suffice; neither root has new absolute game references,
vtable/EH ownership, import stubs, warning exceptions or cropped comparisons.

## Independently qualified compiler island

Following `th105-library`, the71-byte/24-instruction408A00 body is positively
identified as native VC8 list cleanup, with both layout and actual exact-parent
ownership evidence. Full target SHA256:
`a3e8a804e3fda4269c0a7507204778073fee77dfb715060c915916f2160007c0`.

The exact destructor adds15C to its ESI receiver, then reaches408A00 at411587.
Its real CIL `_Tidy` map entry is unique and unexported. The configured
`private_from` contract checks complete source/target parent CFGs, their sole
actual E8 edge to that entry and named-callee agreement. The helper is not
exported to manufacture the target register contract.

Independent source-PE inspection derives the whole helper extent from the next
linker symbol, excluding only the outside INT3 tail. All71 bytes agree after
the two scalar-delete REL32 operands are bound through actual source linker
thunks importing `MSVCR80.dll!??3@YAXPAX@Z` to original6898EA. There is no
helper-sized prefix crop. The pinned `<list>` source has SHA256
`11cd2edd5f34036b95bcb8eb0323e466ce0c535227c7e2612fc8703976ab4a3b`;
standard code remains in the compiler include tree rather than being copied
into an authored module.

It reanchors next/previous to the sentinel, zeros count, releases every node
and the sentinel, and clears the head. Real native member ownership distinguishes
this generated method from an arbitrary authored lookalike; byte shape alone
is not used as an origin fingerprint. The reproducing source specialization is
`list<unsigned *>`; other trivial word/pointer specializations can pool, so
exclusive original specialization, exact patch level or TU are not inferred.

408A00 is recorded as `compiler_generated/runtime/exclude`, statusidentified,
without an authored source-file selection, implemented entry or matches row.
The unit retains it only as a reproducible compiler witness. Its previous
review row moves to exclusion; it contributes **zero authored exact bytes**.
Sentinel4040B0's existing exclusion and constructor credit remain unchanged.

## Accounting, scope and checks

This checkpoint adds **one authored exact function /210 bytes**. Destructor
moves to the canonical origin baseline. The old manual family rule now selects
only pending configure4115A0:439 bytes, six exact caller edges and its complete
hash. No overlapping manual/canonical classification or inherited configure
source/exactness is allowed.

Only `src/assets/TextFontOwner.cpp` and its existing unit change build inputs.
That one affected accepted unit is cold-rebuilt, preserving constructor138 and
verifying destructor210 plus the compiler71 witness. All other accepted unit
definitions and shared headers/compiler flags/relocation ledgers remain intact.
No unrelated or aggregate cold replay is claimed; progress is a ledger snapshot.

Full raw facts, initial COFF control, canonical/private-caller results, source/
PE/map/provenance snapshots and cold receipts are under
`build/font-owner-dtor-20261021/`; corresponding private recipes are under
`.analysis/font-owner-dtor-20261021/`. Completed controls are compressed only
after per-file SHA256 readback; accepted evidence snapshots remain available.

```bash
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next: actual439-byte configuration source, then real glyph/markup/blend closure
before measuring a complete font TU. Font begin/end/text and the Reimu root
remain explicitly nonexact.
