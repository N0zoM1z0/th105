# Fighter PAT and palette resource loading 0x00461B70

Source registration was updated on 2026-11-04; see `LARGE_SOURCE_REGISTRATION_2026_11_04.md`. Earlier references to unselected status are historical.

Update 2026-10-31: actual shared reader operations now reduce the complete
public candidate to 3885 bytes. Only four relocated byte positions differ,
the operand order of two deque iterator range-check loads. Still nonexact;
no exact credit. See EFFECT_READER_FORWARDING_EXACT_2026_10_31.md.
The 3898-byte reports below describe the earlier source.

The complete source in `src/battle/FighterPatResourceLoading.cpp` compiles as
`exact-first-fighter-pat-resources`. Its complete 3898-byte COFF section remains
**nonexact+13** against the 3885-byte target. It is identified/unselected;
`implemented.csv` and `matches.csv` are unchanged. The root adds one observed
authored identity, with no helper-origin or exact credit.

## Observed target closure

Only original Japanese 1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
was used. Fresh target/ledger preflight passed; IDA again rejected the different
GUI executable. No IDA session, Ghidra process or target patch was used.

The complete `461B70..462A9D` body is 3885 bytes, SHA-256
`8705c5b085b7e7c1977252b79929296687a251f1e22216c9521d02143f934d42`.
All 1227 instructions decode;1226 are reachable. The sole unreachable operation
is the pinned three-byte LEA alignment at 4621DD. RET 0 is 462A9C, followed by
three INT3 bytes before an independent five-byte thunk. There are no indirect
jumps. The one outgoing E9 at 461F30 targets vector range-error provider 40C350.
Exact 333-byte Fighter resource initializer 463070 calls the root at 46308A
(`e8e1eaffff`). This establishes the actual member-call entry independently of
retained source names or disassembler ownership.

The public audit reuses the existing target-pinned range-error evidence from
`linked_noreturn.py`: full 123-byte helper, full 74-byte C++ throw routine, terminal
throw call, three catchable exception layouts, error message, noncontinuable
exception record and actual kernel32 RaiseException IAT identity. It qualifies
this external exit without extending the root or granting new exclusion/credit.
The helper SHA is
`a02adc82307ea7507f3024cd6bb4d30229469d2464a73be1c15b8955745445e2`.
It is not an import thunk and is not an accepted source helper match.

The target aligns ESP to 8, allocates 3A8 bytes and uses GS/EH. Its static call
census includes 60 reader virtual calls at vtable+4, three wsprintfA calls,
33 invalid-parameter checks, two raw 16 vector assignments, one independent
PatGroup constructor, two PatGroup destructors and one inlined group constructor.

## Observed application policy

- Character id comes from Fighter+330 through 43BF80. PAT path is
  `data/character/%s/%s.pat`; failed open skips parsing and destroys the reader
  owner. The first byte is consumed without a version check. Signed 16 texture
  count controls assignment of the texture vector pointed to by Fighter+130.
- Signed palette byte+335 selects `data/character/%s/palette%03d.bmp`.
  Receiver 7028D8 loads palette config 6FA258 in format 16. Each texture entry
  reads 128 filename bytes, forms `data/character/%s/%s`, and calls texture
  service 702798/404C90; vector access retains its range-error path.
- Signed 32 entry keys use commands-1 and-2. Ordinary keys erase an existing
  mapping if present, append a32-byte group to deque Fighter+65C, initialize
  its links and insert into the map pointed to by Fighter+160. Command-2
  appends a continuation, connects the previous group's next link and the
  new group's previous/root links, using one actual back operation after append.
  Command-1 reads an alias key/target pair into two real lists and skips group
  contents. Alias pairs are resolved from the backs of both lists after parsing.
- Each group reads WORD+10, WORD+12, BYTE+14 and a signed 32 frame count. Its
  vector is assigned count copies of an actual 136-byte frame temporary.
  Frame constructor 460F90 and destructor 45FFD0 are independently accepted
  providers; no new credit is assigned to them here.
- Each frame consumes a32-bit texture index but stores its low WORD at+A.
  It then reads WORDs at+C,+E,+10,+12,+4,+6,+8 and tag BYTE+14.
  Tag 2 allocates 32 bytes at+18. Mode WORD0/1/2 maps to DWORD1/2/3; other
  modes leave that allocation's mode uninitialized. Bytes+7,+6,+5,+4 are read
  in that order. A signed WORD divided by 100.0 initializes FLOATs+8,+C,+10;
  three further signed WORDs become FLOATs+14,+18,+1C.
- Frame WORDs+1C..+38, two signed WORDs scaled by 100.0 into FLOATs+3C/+40,
  WORDs+44/+46, two bytes at+48, a further byte at+49 and DWORDs+4C/+50 follow.
  A flag controls an optional owned 16-byte allocation at+54. Two signed byte
  counts assign 16-byte value vectors+58/+68 and a pointer vector+78. The first
  read loop retains the observed second checked access after each callback.
  The second optionally allocates/reads one 16-byte payload per pointer slot.
  Flag 01000000 copies the second value vector into the first.

The complete character-resource/format/chain/alias policy and exact caller
establish authored ownership separately from STL/CRT implementation provenance.

## Inferences and finite source controls

The new root uses existing physical PatRecord88/PatGroup contracts and ordinary
checked STL operations. Its four-byte reader-owner view declares the actual
constructor/open/destructor providers; original nominal owner identity remains
unknown. Mutable pointer members are reloaded at their actual use sites after
reader callbacks. Complete owner objects are used for actual local lifetimes;
Fighter itself is only accessed through its established pointer and fields.

The source includes the genuine existing `PatGroup.cpp` definition. That
visibility naturally reproduces the target's selective constructor inlining;
no noinline attribute, compiler-profile change or fabricated helper is used.
The texture path buffer lives only in the texture loop. This permits its stack
storage to be reused by the later frame temporary, as observed in the target.
It does not prove a unique original spelling or every buffer's declared extent.

Every row below is a complete compiling body with full relocation replay.
Counts compare the whole candidate-sized target address range, including bytes
beyond the main target when the object is oversized; they are diagnostic only.
They neither enlarge the root boundary nor define a similarity score.

| Complete trial | Bytes | Unequal positions | Result |
| --- | ---: | ---: | --- |
| First complete source |3898 |3645 | Immediately compared; initial strict stop was unqualified EH, then all providers/data qualified |
| Callback member reloads |3898 |3324 | Removes prematurely cached texture/map pointers |
| Normal group first |3898 |3339 | Recovers physical default-path ordering |
| Signed command switch |3898 |3338 | Recovers command order and EH lexical context |
| Root-local eight-WORD frame view |3898 |3338 | Byte-neutral; private only, discarded |
| Named frame lifetime with that view |3914 |2561 | Changes constructor-result use and grows code; rejected |
| Texture-loop path scope |3898 |3332 | Recovers stack sharing, frame 3A0 |
| Genuine PatGroup visibility |3978 |3439 | Recovers frame 3A8 and native selective inlining |
| One continuation back |3914 |2388 | Removes three extra checks; native 33 remain |
| Explicit frame member references |3914 |2388 | Byte-neutral |
| Local group receiver expression |3898 |3143 | Recovers derived receiver formation; no long-lived alias |
| Member references in the new phase |3898 |3143 | Byte-neutral again; finite reference lane closed |

The word-array view and named-lifetime negative control are not copied into public
source. Final full-section SHA is
`7ab0c272d2f58c47e071d1b51edbd43f70a550ed529b87f0f186cfd9dc2471e2`. The public
ledger-sized comparator hashes its first 3885 bytes as
`b73d385728e8133defc28ae520fd3f616bb101c3ac8dd562f852642d6c6bf855`. Within the
actual main there are 3130 unequal positions; all 3898 diagnostic positions
contain 3143 differences. Remaining size, stack homes, vtable-call scheduling and
pointer-vector erase register allocation remain nonexact. No source-selection or
exact claim follows from recovered size/frame/guard counts or local operation
alignment.

## Reproduction and remaining limits

```bash
scripts/repo-python scripts/build.py --unit exact-first-fighter-pat-resources --compare --json
```

Target-only audit exits 0. Build/object audit report nonexact and exit 1 as
expected. Public receipts are `formal-first.json`, `formal-second.json`,
`public-target-audit.json` and `public-object-audit.json` in the build directory.
All actual REL32 targets, initialized format objects, palette receiver and EH
entry are qualified through the ordinary comparator. There are no relocation
masks, extent waivers, copied target code, assembly, inert locals or padding.
Shared headers, accepted providers and previous relocation rows are unchanged.

Original scalar/local identity, nominal field/container types, original source
spelling, final scheduling and TU/EH context remain unknown. The finite reference
controls are closed; further spelling/type/flag grids need independent evidence.

The full `scripts/repo-python scripts/verify-exact-units.py --all` replay passes
525 cold accepted units/all1413 functions; `cold-all.log` is retained in that
same build directory. Exact authored totals remain 1413 functions/382816 bytes.
The target-backed floating relocation audit passes all 1999 references.
The final `scripts/repo-python scripts/function-origins.py --check` read-back
passes all 4024 rows; its receipt is `origins-check.log` in the build directory.
