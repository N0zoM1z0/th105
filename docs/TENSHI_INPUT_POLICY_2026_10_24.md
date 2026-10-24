# Tenshi input policy: independently checked exact family peer

## Accepted result

Tenshi primary-vtable slot `+0x50 @ 0x0064B7A0` cold-replays exact across
**5,352 callable bytes** and the complete **5,384-byte emitted payload**.
The complete comparison replays all **108 relocations**, including every
switch-table entry. This adds one authored exact function / 5,352 code bytes;
the adjacent destination table earns no authored-byte credit.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-tenshi-input-policy --compare --json
python3 scripts/audit-tenshi-input-policy.py
```

Replay both commands. The full-payload audit uses the public comparator's
strict COFF symbol/owner, relocation and floating-literal validation, requires
the exact section-tail length, and compares every byte without masking.
An independent canonical compile passed, then a separate cold build after
removing only this new unit's active object/provenance passed both checks again.
The first object and all input/receipt snapshots are retained.

Callable SHA256:
`e8aca9d1190639346f7ab67861631de9f363df6a7a539375cbda107f9b0174b2`.
Complete canonical SHA256:
`20bb75cd53cebe9b7714eb97bc8fdd4160b2310e2599d38aaef74acbb2b064d5`.
The source is one natural body in `src/characters/TenshiInputPolicy.cpp`, with
a declaration-only header. It uses the unchanged pinned VC8 SP1 `/O2` profile.
There is no assembly, target array, inert local, artificial padding, fake return
or register/ABI forcing. Never construct or embed these pointer-only views.
Original names, complete layouts and original return declarations remain unknown.

## Observed target facts

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. The existing frozen RTTI anchor binds cell `0x006C67E4` to Tenshi's
primary slot `+0x50` and this address. Authored disposition is unchanged; the
accepted row now uses the generated canonical-exact baseline evidence.

Raw CFG traversal reaches all **1,515 instructions**, **26 RETs** and **seven
external tail JMPs**. All direct internal targets and the eight indirect table
destinations are decoded instruction starts. The callable is
`0x64B7A0..0x64CC87`, ending exclusively at `0x64CC88` after an internal JMP.
There is no alignment gap before the table at `0x64CC88..0x64CCA7`.
The frame has eight local bytes and saves EBX/EBP/ESI/EDI.

The body has **114 physical calls**: 91 direct and 23 virtual slot `+0x08`
calls. Direct calls comprise five stage predicates, six deque subscripts,
two front predicates, nine command finalizers, 43 command-window queries,
17 packed-input initializations and nine other gates. External tails go once
to `0x45DDA0`, once to `0x464200`, and five times to `0x4633A0`.
The complete object has 98 REL32 fields and ten DIR32 fields: one numeric
reference, one table base and eight destination pointers.

Receivers, stacked arguments, AL/AX/EAX consumption and native cleanup match
the already reviewed family call contracts. The input window is a captured
signed word, command bits remain four-byte masks, and the new +82E gate uses
a signed word comparison. No declaration-only callee receives implementation,
origin or exact credit. The full source retains independent repeated calls,
post-call field reads and real early exits.

The one new readonly binding is `__real@430c0000` at `0x006C4C60`: the four
bytes `00 00 0C 43` encode 140.0f, consumed by FCOMP at `0x64C584`.
This previously unresolvable symbol has no prior accepted consumer; existing
bindings remain unchanged.

## Reviewed differences from the Remilia representative

[Remilia's accepted body](REMILIA_INPUT_POLICY_2026_10_24.md) supplied a source
hypothesis only. Raw instruction/edge comparison ranked common regions, then
all changed conditions, arguments, offsets and exits were reviewed before
compiling the complete peer. Addresses and layout changes were not inferred
from roster order or version deltas.

| Surface | Tenshi behavior retained from native instructions |
| --- | --- |
| Special-command groups | Ground masks400/200 use566/561 and565/560; masks4/2 use546/540 and545/540; masks40/20 use505/501 and505/500. |
| Additional tier | Ground high-bit groups read signed word+82E, then byte+609 and527/526, before525 and521/520 fallbacks. |
| Air special commands | Only masks4/2 select548/547 through byte+60A; no normal tier fallback. |
| Special-action cleanup | No Remilia-style +12C clear or +730 word reset is added. |
| Air queued record | Record207 finalizes657; it does not reuse Remilia's206-to606 path. |
| Ground state200 | Adds305 with a window query in the first normal group; adds408/418 without window queries in the later two groups, retaining the actual mode/direction gates. |
| Normal follow-ups | Retains320-to321 and300-to320; omits Remilia's321/frame-to322 and306-to325 shortcuts. |
| Air neutral direction | Tests the actual +6B4 dword for zero, rather than multiplying it by facing. |
| Distance | Uses140.0f, with the actual float subtraction/absolute-value rounding. |
| Last ground group | Adds411 after the two independent412 attempts; final410 does not repeat the earlier eligibility gate. Air fallback414 still does. |

The first complete peer source emitted5,428 bytes and differed in one copied
fallback: ground mask4 incorrectly retained541 rather than native540. Native
pushes at `0x64BCE6/0x64BD33` establish both the query and action540. Correcting
that real argument recovers the shared fallback block with mask2, reduces
packed-input calls18 to17 and virtual calls24 to23, and emits the complete
5,384-byte zero-difference payload. No source-shape sweep or compiler-profile
change was needed. The earlier draft remains available as negative evidence.

## Attestation, validation and retained evidence

IDA's required preflight again rejected the other open executable. A single
existing Ghidra project was independently attested against executable identity,
Windows x86 language/compiler, image base, entry `0x68B9D2` and every raw-backed
mapped section before semantic use. It ran read-only, analysis disabled,
CPU0/nice10 with a384 MiB configured heap. Temporary function/ABI, observed
external-tail and action-call metadata were read back and rolled back; all
pinned primary database files have identical before/after hashes. Pseudocode
remains corroborating hypothesis, not source or acceptance evidence.

Private recipes and two complete source revisions remain under
`.analysis/exact-first-tenshi-slot50-20261024/`. The corresponding `build/`
directory retains raw facts/disassembly, full CFG closure, the family diagnostic,
attested views/logs/database pins, formal and independent cold comparisons,
complete-payload receipts and the previous origin-baseline row.

A negative control changes only the first table byte in a generated object.
The complete audit rejects it at `+0x14E8 / 0x64CC88`, target E9/source EA.
The target is never patched. No large runtime matrix or aggregate cold replay
is claimed. Previously accepted source/header inputs and unit descriptors stay
unchanged; this peer is accepted separately from Remilia, whose own exact
result is preserved. Continue other complete slot+0x50 peers under the same
independent review and two-command acceptance discipline.
