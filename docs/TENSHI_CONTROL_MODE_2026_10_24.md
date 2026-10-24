# Tenshi control mode: complete source and parked constant-promotion residual

## Result and reproduction

Tenshi Fighter primary slot `+0x5C @0x00649330` now has complete source in
`src/characters/TenshiControlMode.cpp` with a pointer-only declaration header.
The target owns **2973 callable bytes** and a **3268-byte emitted payload**.
The first complete source emits3252 bytes and remains **nonexact** at
`+0xA6 /0x006493D6`: a branch displacement changes because downstream code
retains constants differently. No matches row or new exact credit is added.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit exact-first-tenshi-control-mode --compare --json
python3 scripts/audit-tenshi-control-mode.py
```

Both commands correctly return1. Formal comparison replays all61 function
relocations (17 REL32 /44 DIR32); the full audit also compares every emitted
table/alignment byte and requires the exact3268-byte section-tail length.
The separate `.debug$F` SECTION relocation supplies no callable evidence.

Target callable SHA256:
`98a9f90864ff06cdf043b79a2b75ee8654d596e5eb215b4575ea895a2f885b9f`.
Target full SHA256:
`c27154f9d1e0e8fbd390a24bfe1bd61a6d899f64a7b3d9bd26bb9395a4327046`.
Selected source full canonical SHA256:
`779c8af0d46764e6a8e1f13fee4e8dde6f82fc768fede6ecc0034c04b156f063`.

Never construct or embed these pointer views. Original full owner layout, type
names, unaffected virtual signatures and original TU context remain unknown.
Declaration-only callees gain no implementation or exact credit. There is no
assembly, copied byte array, artificial padding, inert local, fake return,
ABI/register forcing or compiler-profile search.

## Observed target facts

The only binary is original Japanese1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Existing RTTI ownership establishes authored origin; primary slot5C cell6C67F0
points to649330. The same table binds slot08/0C to45BFE0/45C390 and slot58 to
the shared5F1F80 policy. A raw register-target chain at649879..649885 proves
the genuine slot58 tail; it is not an unresolved computed jump table.

Complete raw traversal closes **713 instructions**, **20 RET0s**, **25 calls**,
all internal direct edges and all ten destination entries. Seventeen calls are
direct:4399C0 once,478E60 three times,4067D0 nine times,465190 four times.
Eight are virtual action calls. The separate virtual CPU tail earns no callee
credit. Main prologue reserves10h, saves ESI/EDI, and the larger state arm later
saves EBX/EBP. There are no remote chunks or EH paths in this bounded source.

Callable end is exclusive649ECD; LEA alignment occupies three bytes. Destination
tables at649ED0/649EE8/649EF8 contain3/4/3 entries. Index tables at649EDC and
649F04 contain12 and240 bytes. Payload ends exclusively649FF4; all preceding
and following padding is independently checked. Adjacent metadata gives no
additional authored-byte credit.

| Independently reviewed surface | Native behavior preserved |
| --- | --- |
| Prefix |Clear commands, signed peer174>0 gate, then the additional50..199 action reset; signed55A gate follows. |
| Records0..3 |Initial770 needs action700 only. Repeat the peer gate after deque access. Publish state2 before710; state2 faces again. Unsigned RNG12 produces signed-facing horizontal motion; RNG4 plus double12.0 and float.35 complete701. Ordered x<=640 retains its unordered behavior. |
| Records4..7 |Initial770; repeated peer gate; state1 uses zero-first action0/700 check and720, with no state increment. |
| Records8..11 |Identifier3/2/1/0 periods50/60/80/120; unsigned RNG40 plus double70.0 supplies packet[0], packet[1..2]=6f/9f. Spawn920 uses RNG1000 plus double120.0 for x and float900.0 for y. Action0/700 selects731; otherwise increment DWORD83C. |
| Records12..15 |Initial770; repeated peer gate; publish state2 before740; later face, unsigned RNG8 plus double5.0, RNG4 plus double12.0, float.5, then701/state1. |
| Records248..255 |Conditional action0 and genuine virtual CPU tail. |
| Records16..19 |Ready action700/0 selects771. Otherwise action750/sequence1 enables independent phase736 checks at1/2/3 and signed health<=7500/5000/2500. Each sets74C=2f, packet0/0/18f, policy state1, next phase, three180 timers, then spawns940 with integer facing*30 converted to float for x and double120.0 for y. Independent checks allow multiple spawns if successive phases qualify. |
| Policy state1 |Health intervals>=7500,>=5000,>=2500 and lower have distinct inclusive/exclusive boundaries, word timers, alternating76C, one-shot76E and signed76C%3. The RNG100 branch uses unsigned<50. All native early returns and the top-health fallthrough remain. |
| Policy states2..8 |Each publishes the actual738 output before its timer guard. Expired2/3/5 converge to6 with delay60;4 to5 with180;6 to1 with120;7 to8 with60;8 to1 with30. State0 only resets output0/delay240. |

Spawn argument order, byte direction, signed integer facing multiplication,
packet lifetime, float rounding captures and repeated post-call reads follow
raw operands. Identifier switch has no initialized default; native default
loads an uninitialized stack period. Source preserves that absence rather than
inventing a fallback. Valid-domain assumptions and invalid-input behavior are
not claimed recovered. Global6FA894 remains `g_match_identifier`.

## Whole comparison and finite controls

First complete probe00 already recovers every physical call, return and tail
count and the destination/index-table shapes. Its698 callable instructions
contrast with713 native instructions. The remaining native instructions are
one EBP save, initialization to3, reassignment to240 and twelve EBP restores.
Target uses this real constant register for three spawn counts, the phase3
store/check and two240 timer stores; source uses immediate operands instead.
The resulting main/table addresses and alignment differ. Diagnostic instruction
alignment can classify this residual but does not make any region canonically
exact or establish original compiler/TU identity.

Two isolated, target-supported controls were compiled and compared completely:

1. Probe01 uses an unsigned-byte variant formal, supported by the existing
   accepted66-byte spawn wrapper and its manager's byte-only consumption.
   It produces exactly the same3252 canonical bytes as probe00.
2. Probe02 makes the equality-only76A view unsigned short, consistent with the
   observed zero-extending reads; signed timer, health and remainder consumers
   remain unchanged. It also produces exactly the same complete candidate.

Both are negative results, not nominal-type proofs. Keep the simpler signed
state/int-variant baseline, stop repeating these controls and select another
complete representative. No claim is made that LTCG is necessary or sufficient;
new independent lifetime/type/TU evidence is required to reopen this residual.
No runtime matrix was needed to resolve a concrete ambiguity in this scope.

The only new literal is float18.0 bytes00009041 at6C3E50, loaded by native
64990C/6499C9/649A88. A new named allowlist key is referenced only through this
function's explicit `__real@41900000` override. Existing default mappings and
all accepted-unit bindings are unchanged, so no previous accepted source unit
is affected. The ordinary literal auditor validates both the source encoding
and hash-attested target bytes; the function comparator performs strict replay.

## Validation and retained evidence

IDA preflight rejects the different executable currently open there; no session
semantics or writes are used. One read-only Ghidra run independently attests
file SHA, image base, entry68B9D2, Windows x86 language/compiler and every raw
section against the PE. It creates only a temporary raw-bounded2973-byte view
and temporary callee types, reads them back, and rolls them back. All nine
pinned primary DB hashes remain unchanged. Decompiled expressions are reviewed
hypotheses; source is written from independently checked operations and edges.

Private recipes/frozen probes are in
`.analysis/exact-first-tenshi-slot5c-20261024/`; the matching `build/` scope
retains raw CFG/tables/literals, attestation/readback/DB pins, all comparisons
and the formal object. Ghidra heap384MiB/one CPU; builds serial CPU0/nice10.
Local CI and whitespace gate precede commit/push. Iku's exact representative
and all earlier accepted sources remain unchanged. Current ledger exact count
stays1396/324774 bytes, with no aggregate cold replay claim.
