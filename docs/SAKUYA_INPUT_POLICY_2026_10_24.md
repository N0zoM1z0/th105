# Sakuya input policy: complete exact family peer

## Accepted result

Sakuya Fighter primary slot `+0x50 @ 0x004DF4B0` accepts **5,897 callable
bytes** and the complete **5,940-byte emitted payload**, including alignment
and all ten switch destinations. The first complete source already matches;
a formal build and a separate cold build reproduce the result. All **120
relocations** are replayed. Only the callable earns authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-sakuya-input-policy --compare --json
python3 scripts/audit-sakuya-input-policy.py
```

Run both commands. The second requires exact section-tail length and every
payload byte using the public strict comparator's COFF ownership, relocation
and floating-literal checks. No masked or sequence-alignment score is accepted.
The first formal object/provenance is retained separately; removing only this
new unit's active object/provenance before another compile establishes the cold
replay. The unchanged pinned VC8 SP1 `/O2` profile is used throughout.

Callable SHA256:
`0a1c73560522163b6a4da3a12258e9a00a6ea9781698cdd1f9cdc4775599c588`.
Complete canonical SHA256:
`57689f32d9ee39731ad0682f45652b77a0f9c6e26323c9e879fe61a9504812c3`.

The source is one ordinary C++ body in `src/characters/SakuyaInputPolicy.cpp`
with declaration-only, pointer-only views. Never construct or embed them.
Original names, full owner layout and original ignored-return declarations
remain unknown. No declaration-only callee gains implementation or exact credit.
No assembly, target arrays, padding, fake returns, inert locals or ABI/register
forcing were introduced. No compiler-profile or source-shape sweep was needed.

## Observed target facts

Only hash-attested original Japanese 1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The existing frozen RTTI anchor binds Sakuya primary-vtable cell `0x006C4964`
(slot `+0x50`, vtable `0x006C4914`) to this root. A raw aligned-pointer scan
independently reads the same target. Ownership disposition remains authored;
only this accepted row's origin evidence becomes `canonical-exact-authored`.

Raw traversal closes all **1,687 instructions**, **33 RETs**, **six external
tail JMPs**, and every direct/internal and ten-way indirect edge. The callable
ends exclusively at `0x4E0BB9` after an internal JMP. The three-byte
`LEA ECX,[ECX]` at `0x4E0BB9..0x4E0BBB` aligns the adjacent destination table
at `0x4E0BBC..0x4E0BE3`; it is emitted naturally and earns no authored credit.
The frame reserves eight bytes and saves EBX/EBP/ESI/EDI.

There are **129 physical calls**: 102 direct and 27 virtual slot `+0x08`
calls. Direct calls comprise five stage predicates, six deque subscripts,
two front predicates, eleven command finalizers, 47 command-window queries,
22 packed-input initializations and nine other gates. External tails go once
to `0x45DDA0`, once to `0x464200` and four times to `0x4633A0`.
The complete object has 108 REL32 and twelve DIR32 fields: one float reference,
one table base and ten destinations. The existing `__real@42b40000` binding
at `0x006C3D8C` is the observed 90.0f literal; no global bindings change.

Native callee destinations and call/cleanup widths agree with the separately
reviewed family protocols. The captured window and action predicates use
signed words; byte flags and signed-byte tiers retain their observed widths.
The action call uses a real polymorphic receiver's slot `+0x08`. The full
source preserves repeated calls and post-call field reads.

## Independently reviewed family differences

[Tenshi's accepted body](TENSHI_INPUT_POLICY_2026_10_24.md) supplies a source
hypothesis only. Complete raw CFG, argument and width review precedes the first
compile. An independently attested Ghidra view corroborates the interpretation;
its generated expressions are not pasted as source.

| Surface | Sakuya behavior retained from native instructions |
| --- | --- |
| Ground queued commands | Ten records200..209 finalize600..609, rather than the peer's eight records. |
| Ground masks400/200 | Signed byte+608 selects506/501 and505/500 through flag+754. |
| Ground masks4/2 | Signed byte+60A selects546/541 and545/540 through flag+756. |
| Ground masks40/20 | Signed byte+609 selects526/521 and525/520 through flag+755. |
| Ground high-bit masks | Signed byte+60B selects566/561 and565/560 through flag+757; there is no Tenshi +82E tier. |
| Air queued command | Record206 finalizes656. |
| Air masks400/200 | Both +608 and+60C must be zero, then503/502 is queried and dispatched through flag+754. |
| Air masks4/2 | Signed byte+60A selects548/543 and547/542; both include regular fallbacks. |
| First ground normal group | Retains305, adds321-to322 without a frame check, retains320-to321 and300-to320, and uses90.0f. |
| First air normal group | Attempts308 with UP/FORWARD, then independently queries308 again with UP. The309 neutral gate tests +6B4 directly. |
| Second ground normal group | Forward path queries400, and fallback independently queries400 again. A failed resource gate skips to group+6FC. |
| Second air normal group | Adds neutral/forward404 before406 and its independent404 fallback. |
| Final ground group | Retains411 and repeats eligibility after the final410 query; air fallback414 also retains its repeated eligibility. |

No Remilia-style +12C clear or +730 reset is added. The first complete source
emits exactly5,940 bytes and matches immediately. The initial private diagnostic
accidentally requested only5,932 bytes (an eight-entry table size); correcting
the report extent to the observed ten-entry table removes that report-only
length error. No C++ source correction was required.

## Validation and retained evidence

IDA preflight rejects the other executable still open there; no semantics or
writes from that session are used. One read-only Ghidra process independently
attests file/program hashes, Windows x86 language/compiler, image base, entry
`0x68B9D2`, every raw-backed section and the root hash. Temporary function/ABI,
observed-tail and virtual-call metadata are read back and rolled back. All
pinned primary database hashes remain unchanged. CPU0/nice10 and a384 MiB
configured heap bound the analysis; builds are serial with the same CPU/nice.

Recipes and the unchanged first complete source/header snapshots remain under
`.analysis/exact-first-sakuya-slot50-20261024/`. The corresponding `build/`
directory retains raw facts, full CFG closure, all ten table edges, disassembly,
attestation/logs/database hashes, the first formal object, independent cold
receipts, relocation counts, original origin row and retained input hashes.

A negative control changes only the first table byte in a generated COFF object.
The complete audit rejects it at `+0x170C / 0x4E0BBC`, target F9/source FA.
The target is untouched. Existing Remilia/Tenshi source/header inputs remain
unchanged. No new aggregate cold replay or broad runtime matrix is claimed.
Continue complete slot+0x50 peers, independently checking their differences.
