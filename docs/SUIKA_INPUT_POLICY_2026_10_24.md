# Suika input policy: fourth complete exact family member

## Accepted result

Suika Fighter primary slot `+0x50 @ 0x005AED00` accepts **5,849 callable
bytes** and the full **5,888-byte emitted payload**, including alignment and
all nine switch destinations. The first complete source matches immediately;
a formal build and a separate cold build reproduce exactness with all **117
relocations** replayed. Metadata receives no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-suika-input-policy --compare --json
python3 scripts/audit-suika-input-policy.py
```

Run both commands. The full-payload audit requires exact section-tail length
and every byte through the public strict COFF owner/relocation/literal checks.
The first formal object and provenance are retained, then only this new unit's
active object/provenance is removed before an independent compile and both
comparisons. The pinned VC8 SP1 `/O2` profile remains unchanged.

Callable SHA256:
`c083d03c10bd5736354c1c025f2216c4b3e9b10f612fa855931aad01b72ea146`.
Complete canonical SHA256:
`aad5c91e0526eabc05c81285aa78e1723f0adbccb30f92f8745ce47724f4940b`.

The source is one ordinary complete body in `src/characters/SuikaInputPolicy.cpp`
with declaration-only pointer views. Never instantiate or embed those views.
Original names, complete owner layouts and original ignored-return declarations
remain unknown. Declaration-only callees earn no implementation or exact credit.
There is no assembly, copied target array, artificial padding, fake return,
inert local or ABI/register forcing, and no compiler/profile/source-shape search.

## Observed target facts

The only target is original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The frozen RTTI roster anchor binds primary-vtable cell `0x006C5BDC`, slot
`+0x50` in Suika vtable `0x006C5B8C`, to this root; the raw aligned-pointer
scan independently reads the same destination. Authored ownership is unchanged;
only this accepted row's origin evidence becomes `canonical-exact-authored`.

Raw CFG traversal closes **1,667 instructions**, **31 RETs**, **six external
tail JMPs**, all internal direct edges and all nine switch destinations.
The callable ends exclusively at `0x5B03D9` after an internal JMP. The natural
three-byte `LEA ECX,[ECX]` alignment occupies `0x5B03D9..0x5B03DB`; the table
occupies `0x5B03DC..0x5B03FF`. Neither extends the authored callable extent.
The frame reserves eight bytes and preserves EBX/EBP/ESI/EDI.

There are **126 physical calls**: 100 direct and 26 virtual slot `+0x08`
calls. Direct calls comprise five stage predicates, six deque subscripts,
two front predicates, ten finalizers, 47 command-window queries, 21 packed-input
initializations and nine other gates. External tails go once to `0x45DDA0`,
once to `0x464200` and four times to `0x4633A0`. The object has106 REL32 and
11 DIR32 fields: one float reference, one table base and nine destinations.
The existing float `__real@43200000 @ 0x006C32D4` is the observed160.0f
comparison literal. No shared literal or relocation mappings change.

Callee destinations, native cleanup and AL/AX/EAX consumption agree with the
separately reviewed family protocols. Signed word window/state reads, signed
byte tiers, byte flags and four-byte masks keep their native widths. Source
retains independent repeated calls, actual action/query pairs and post-call
field accesses. Physical call counts are diagnostic; acceptance is the strict
whole-payload zero-difference comparison.

## Independently reviewed changes from Sakuya

[Sakuya's exact body](SAKUYA_INPUT_POLICY_2026_10_24.md) supplies a source
hypothesis. Complete raw bytes/edges and changed argument/width sites are
reviewed before compilation. The family sequence alignment only locates
changes; it is not an acceptance score. Independently attested Ghidra views
corroborate the interpretation and are not mechanically copied into C++.

| Surface | Suika behavior retained from native instructions |
| --- | --- |
| Ground queued commands | Nine records200..208 finalize600..608. |
| Ground masks400/200 | Adds signed byte+60D tier531/530, then+609 tier526/525, then521/520; all use flag+755. |
| Ground masks4/2 | Signed byte+608 selects506/501 and505/500 through flag+754. |
| Ground masks40/20 | Signed byte+60A selects545/541 and545/540 through flag+756. Both high tiers genuinely query and dispatch545, sharing the physical success block. |
| Ground high-bit masks | Retains+60B566/561 and565/560 through flag+757. |
| Air queued command | Record200 finalizes650. |
| Air masks400/200 | Both +609 and+60D must be zero; then523/522 is queried/dispatched through flag+755. |
| Air masks4/2 | Signed byte+608 selects508/507 through flag+754, without a regular fallback. |
| First normal group | Retains the321-to322 shortcut and repeated air308 query; distance threshold is160.0f. |
| Second ground normal group | Forward path uses401 before400 fallback, with the actual resource-failure skip. |
| Second air normal group | UP406 is attempted before neutral/forward405 and404 fallback; a failed406 resource check continues to the following real gates. |
| Final air group | Uses414 in both the upper direction path and fallback; the latter still repeats eligibility after its independent query. |

No Remilia-style +12C clear or +730 reset is added. This reviewed first complete
source emits exactly5,888 bytes and matches without a C++ correction.

## Validation and retained evidence

The required IDA preflight rejects the other executable open there. No semantics
or writes from that session are used. One read-only Ghidra process independently
attests file/program identity, Windows x86 language/compiler, image base,
entry `0x68B9D2`, every raw-backed mapped section and this root hash. Temporary
function/ABI, observed-tail and virtual-call metadata are read back and rolled
back. Every pinned primary database hash remains unchanged. CPU0/nice10 and
384 MiB configured heap bound Ghidra; compilation is serial on CPU0/nice10.

Private recipes, whole-CFG setup and unchanged first source/header snapshots
remain under `.analysis/exact-first-suika-slot50-20261024/`. The corresponding
`build/` directory retains raw facts/disassembly, complete CFG and nine table
edges, family diagnostic, attestation/logs/database pins, formal/cold receipts,
first formal object/provenance, relocation counts and original origin row.

The table-only negative changes a generated COFF byte, leaving the target
untouched. The complete audit rejects it at `+0x16DC / 0x5B03DC`, target49 /
source4A. Previously accepted Remilia/Tenshi/Sakuya source/header inputs stay
unchanged. No broad runtime matrix or new aggregate cold replay is claimed.
Continue independently checked complete slot+0x50 peers.
