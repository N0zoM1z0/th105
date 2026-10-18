# Reimu CPU wall masks and compiler phases, 2026-10-19

Two more policy0 wall guards now use the target's ordered predicates. All
four negative wall guards preserve C0/C2 unordered behavior. The15999-byte
root at48D390 remains nonexact at+12E/48D4BE, with118 source/121 target
selector sites and48/52 RETs. No exact credit is added.

## Target-attested remaining wall guards

The executable remains original Japanese1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable `[48D390,49120F)` SHA256 is
`3bd363994e140603ae0ec249ffd3a36b1ae0448e72a389e417c4cc7a6d113e2d`.
Authored vslot+58, void ECX ABI and four metadata tables are unchanged.

The preceding [NaN checkpoint](REIMU_CPU_NAN_WALLS_2026_10_19.md) fixed two
close-distance guards using actual exceptional-X counterexamples. This
checkpoint checks both directions of the remaining two mid-distance guards
against real target execution and raw target instructions:

| Input height/roll/facing at distance150 | Target comparison/mask/branch | Policy |
| --- | --- | --- |
| self0,peer0,roll20,facing1 | FCOMPP48FE56; TEST AH,5 at48FE5A; JNP48FE5D | 3 |
| self0,peer0,roll20,facing-1 | FCOMP48FE6E; TEST AH,5 at48FE76; JP48FE79 | 3 |
| self100,peer0,roll30,facing1 | FCOMPP49083E; TEST AH,5 at490842; JNP490845 | 11 |
| self100,peer0,roll30,facing-1 | FCOMP490856; TEST AH,5 at49085E; JP490861 | 11 |

Facing1 uses selfX100/peerX250; facing-1 uses selfX1100/peerX950. Original
helpers execute without substitutions. The comparison masks distinguish C0
from C0/C2; opposite ordered relations are not their unordered complements.
The selected source explicitly negates the ordered near-wall expression in
these two guards, matching the already-corrected pair.

These are instruction-backed corrections, not two newly observed runtime
NaN counterexamples. The current exceptional-X fixtures reach the earlier
close-distance arms after integer distance conversion; they do not establish
every unordered entry into a mid-distance guard. Keep the evidence classes
separate.

Encoding-preserving source-to-source comparison covers all4008 functional
instruction ordinals. Only eight additional TEST/Jcc instructions differ:
TEST DL,AH/JNE -> TEST AH,5/JNP and TEST AH,1/JE -> TEST AH,5/JP at the
two directional legs of the two guards. Direct-edge destinations agree by
instruction ordinal; all other encodings and external/literal identities
are unchanged. All eight local table operands and47 metadata pointer
destinations preserve their roles/ordinals. Before policy0 the entire code
prefix is byte-identical.

The two longer TEST instructions consume the prior two-byte post-RET8BFF
alignment. No source padding is added. Prefix/payload remain15920/16461;
the functional instruction count stays4008, while the decoded prefix count
changes4009->4008 because the alignment instruction disappears. This does
not confer partial exact credit or fix terminal sharing.

## Compiler and genuine dependency controls

These controls use the preceding input source SHA256
`7102660c044b225578aeb52fb5379ef20925ed813f34e7ab6815e760384f01eb`,
retained as `build/reimu-cpu-phase/Baseline.cpp`. They are unselected and
must not be attributed to a later source revision without replay.

**Compiler revision:** verify the three RTM compiler/front-end/back-end hashes
from [RTM provenance](VC8_RTM_PROBE.md), then compile identical source/options.
RTM14.00.50727.42 and SP1 produce the same entire16461-byte canonical payload
`4a4cb565b9c023fb82e6f4fbb01e63df711d3b3f59ce15fef1c1f9c52b581792`.
This rejects a compiler-revision-only explanation on that input, not every
original compiler/source context.

**Native container boundary:** use the real VC8
`std::deque<FighterSequenceSlot>::operator[](0)` with its checked SDK COFF
instantiation. The provider is independently94/94 exact at4399C0, including
its standard receiver/argument/cleanup behavior. The ordinary root is again
fully byte-identical to the preceding16461-byte bounded-view source. A map
name or compatible-looking call alone is not used as ABI proof.

**Genuine closed link:** compile the root/GL and use that exact SDK provider,
fresh exact MT/selector/angle COFF units, real static CRT/SDK libraries and
the actual CRT DLL startup. No fake caller, stub helper, unresolved override
or executable address binding is supplied. The exported preserved-type root
starts `push ebp; mov ebp,esp; and esp,-8; sub esp,12`, unlike target.
Its prologue is enough to reject that candidate; no root acceptance or
execution is claimed for this aligned-frame image.

**Five float-copy aliases:** v95/v96/v97/v99/v100 hold only already-float
vertical/horizontal distances or copies of those aliases. The private
generator checks every assignment before changing only their declarations
from double to float; no arithmetic expression is narrowed. In the same
closed link this removes the aligned EBP frame and restores the target's
first12 entry bytes. This demonstrates a source-type dependency of that
frame, not proof that the target used LTCG or that these were original types.

The float-copy candidate receives full qualification:

- All3993 code-prefix instructions/15888 bytes are reachable; four bound-
  and index-checked switches close, with no unresolved transfers or tails.
- SDK helper remains94/94 in the linked image. The three engine dependencies
  retain exact fresh COFF receipts; MAP ownership is checked, including the
  SDK inline-symbol marker. The conversion comes from the pinned real CRT.
- All334 fields replay independently:154 E8 calls,125 width/bit-checked
  immutable literals, eight local table operands and47 code pointers.
  The180 HIGHLOWs equal the complete DIR32 inventory. Three trailing INT3
  bytes are a separately qualified next-owner alignment gap.
- The genuine linked and ordinary16429-byte payloads agree completely:
  `ec562ac4a335d83410a0d8736e0af5eccefc7835ea1f231e42788838079b6413`.
  Both remain nonexact at+12E/48D4BE. Five real callees retain the observed
  surface25 checked-deque/1 MT/118 selector/4 angle/6 conversion calls.

The float/link controls remain unselected. A correct entry frame and
genuine/ordinary correspondence do not recover the target's complete sharing.
The linked images are not executed. Original TU/caller visibility, further
lifetimes and other honest LTCG contexts remain unknown. Do not repeat these
unchanged revision/container/alias controls without independent new evidence.

## Selected source and verification

| Artifact | SHA256 |
| --- | --- |
| Selected source | `1d121503b98277c808727f58af725f13642dfe5ab78ee91bb03aa32b283876d5` |
| Fresh ordinary object | `4c84ca27f5bae8eb850092456c56c9f81f0635c79b40c625731df4448a80078a` |
| Canonical16461-byte payload | `07cb7a406e5c136ccd25e97287419f58e7b8b7eaccd502af81e0cb811fbac091` |

Fresh selected execution passes0/16160 selection,0/5000 general,0/368
height/NaN and0/20200 exceptional-X cases:0/41728 overall. Selection visits
all1488 target policy0 instructions and confirms actual rolls0..100. All49
finite selector-pair records,63 coupled terminal records, representative
cases and publication/x87 observations agree with the preceding source after
mapping source sites by instruction ordinal. General cases execute all five
original helpers. These are finite diagnostics, not complete gameplay or
exception equivalence.

Reports, four actual target paths, normalization, compiler pins, exact
dependency receipts and complete private link recipes are retained below
`build/reimu-cpu-phase/`. To repeat the pre-checkpoint link use
`python3 build/reimu-cpu-phase/native-link.py build/reimu-cpu-phase/Baseline.cpp`,
then its `float-link.py`, `inspect-float.py` and `qualify-float.py` recipes.
Regenerate the float ordinary packet with
`python3 build/reimu-cpu-phase/native-packet.py build/reimu-cpu-phase/float-link/ordinary.obj float-coff`
before the correspondence recipe when rebuilding from cleaned artifacts.
Generated sources/images/compiler files remain ignored, not reconstruction
deliverables. Selected ordinary-source reproduction uses the existing unit:

```bash
python3 scripts/build.py --unit gpt-web-reimu-cpu-action-policy --compare --json
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu \
  --selection-cases --selection-x87 --selection-terminals
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --x-position-cases
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --cases 5000
python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --height-cases
python3 scripts/ci.py
git diff --check
```

Read-only Ghidra independently re-attests file/entry/text/root bytes and
typed metadata; nine primary DB hashes remain unchanged and the alias is
removed. The384MiB/CPU0 recipe is under
`.analysis/reimu-cpu-phase-20261019/`. Required IDA preflight rejects its
wrong target; no IDA semantics or factory adapter is used. Selected ABI,
headers, compiler flags, source partition and relocation contracts are
unchanged. No aggregate cold replay or new exact function/byte is claimed.
