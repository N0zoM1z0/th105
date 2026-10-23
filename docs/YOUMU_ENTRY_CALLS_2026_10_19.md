# YoumuObject851 load order and native selector execution

The [October23 physical-tail recovery](YOUMU_ENTRY_PHYSICAL_TAIL_2026_10_23.md)
is the current selection: all target copies and metadata agree,21 callable
bytes remain, and the public592-case audit passes. This page retains the
earlier851 correction and its counterexample, with their original source pins.

The subsequent [auxiliary-sprite checkpoint](ANIMATION_AUXILIARY_SPRITE_2026_10_19.md)
shares the recovered auxiliary layout/provider and changes root source SHA to
7b0dac5f. Its complete canonical payload594a91c1, owner diagnostics and592-case
execution remain unchanged. Source pins below identify this earlier checkpoint.

## Scope and target observations

Only original Japanese TH10.5 v1.06a is used: executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The authored initializer is543670, callable `[543670,544A97)`,5159 bytes,
SHA256 `d680c9d1386e6c3f8cc5e755dffccbbd431864dee308f760cf48fe00274ed245`.
The existing complete raw CFG closes1294 instructions,29 primary destinations,
one auxiliary switch and the596370 external tail. Mapping/source presence
confer no exact credit.

**Observed:** YoumuObject primary vtable6C50BC has selector45C390 at+0C,
frame setter45C180 at+1C, and this initializer at+3C. Its COL6DA790 and eight
RTTI base descriptors independently place AnimationObjectBase at4,
Environment at130h and CObjectBase at330h. A concrete hierarchy source control
has the complete predecessor canonical payload; it does not fix the residual.

**Observed:**851 occupies543DCE..543DF6. It loads heading340 into ECX and
the vptr into EDI, stores word1 at344, then executes `FLD dword [ECX+8]`.
The float conversion, slot+C call and ordinary epilogue follow. The predecessor
source09dd36f0 instead captures a double **value before** the state store.
That ordering is unsupported by the target. Earlier documents that retain
it as a hypothesis do not validate it.

**Observed ABI witnesses:** a fresh build of
`cross-v106a-animation-sequence-virtuals` is exact; its int selector45C390
reproduces202/202. The existing natural-short probe independently reproduces
those same202 bytes and RET4, SHA256
`dd6808825102feaf752f50030bba523485d6c03828599435509c2e09359abcd4`.
Both use ECX self and a four-byte argument slot; the callee consumes the low
word. These witnesses support compatible machine interfaces. They do not
uniquely recover the original C++ declaration or discarded return type.

## Selected source correction

`YoumuObjectActionEntry.cpp` now captures the851 parameter pointer, stores
state344, and reads parameters[2] afterward. It dispatches through the existing
`AnimationSequenceObjectView` int interface to the same actual vtable cell.
This adds no new prototype, virtual slot, helper, forced register or global
alias promise. The ordinary short-interface correction merges target-distinct
851/854 destinations; this existing int interface preserves all29 destinations
and all23 previously equal owner diagnostics. Shared headers, object layout,
compiler settings, accepted units and relocation bindings remain unchanged.

| Selected artifact | Value |
| --- | --- |
| Source SHA256 | `bd1777d699408446fd484f063483d931a48fd2bc2fb34db15d6ddf907d4054ae` |
| Canonical5488-byte payload SHA256 | `594a91c1273e04ea2f3bd6524c4fc844ba44194a06f4efd31e147465bb77df64` |
| Code/alignment prefix; adjacent metadata | 5156;332 bytes |
| Target metadata start | 5160 |
| Frame; conversion calls; RETs | 10h;20;22 |
| Target conversion calls; RETs | 21;23 |
| Strict first mismatch | +80 /5436F0, default-branch displacement |
| Owner diagnostics | 23/30, with no prior equal owner lost |

Only16 bytes of the entire canonical payload change from predecessor4b9bf0a4.
The full5159-byte strict comparison still fails. Because the source metadata
starts four bytes earlier, do not describe its5159-byte comparison hash as a
callable hash. No matching ledger row, exact-byte credit or aggregate claim is
added.

## Execution evidence and counterexample

The new `scripts/audit-youmu-object-entry-calls.py` executes both the original
PE and freshly compiled candidate at separate addresses under Unicorn1.0.2.
Original target code/vtables and the sequence resources are read-only.
Every callee executes its actual target instructions; none is replaced or
assigned a synthetic result. Execution and writes fail closed outside the
reviewed root/helper/object/stack extents. The fixture uses a real action tree,
258 linked sequence blocks, valid untextured frames and the original texture,
frame and sprite-commit paths.

The matrix has588 ordinary cases:812/820/821/848/850/851/854,14 finite parameter
bit patterns, three initial sequence values and two x87 precisions. Four extra
851 ABI stress inputs put heading[2] over state344 and use257.5 or257.75.
The target word store changes that float to just above256 before converting
it. The old value capture instead converts257. This is a machine-level alias
counterexample, **not** evidence that factory-owned game objects can contain
this overlap. The previously observed positive-count factory allocation is
separate; not every writer/lifetime or a compiler-visible no-alias contract is
closed.

Fresh selected execution passes0/592. Each side reaches592 real selector,
tree lookup, frame, texture and commit chains and returns through native RET.
All388h object bytes, selector arguments, helper trace, nonvolatile registers,
ESP, x87 TOP and control word are checked. The old09dd36f0 source fails exactly
4/592, all the deliberate alias cases: target256 versus candidate257, with
resulting sequence/frame-pointer differences. Its588 ordinary cases pass.
The negative control shows why the earlier load-order hypothesis cannot be
accepted solely from sampled ordinary objects or unchanged owner counts.

This remains bounded execution evidence. It does not cover other actions,
nonzero textures, auxiliary-renderer ownership, arbitrary resource graphs or
whole-root semantics, and does not establish canonical equality.

## Other source controls and remaining uncertainty

The strongest unselected850-only control uses the same existing int facade.
It gives canonical SHA256
`eb6d6f06fb16ac60e4c6e132dc4a8b9b4989918d8fa5b72d84dc59f973e50685`,
prefix/payload5160/5492,21 conversions/23 RETs,25/30 diagnostics and zero
metadata differences. Only30 callable bytes differ, first+5BA/543C2A.
However, it retains the old851 load order. It is a useful compiler-phase
witness, not a suitable source checkpoint. Combining corrected851 with850
again collapses850's physical copy (prefix5152,20 conversions/22 RETs).

| Evidence-backed control | Complete result |
| --- | --- |
| Shared active821/848 pointer, optional const823 payload or850 pointer reuse | Recovers821 but adds a conversion/return copy and loses five prior owners |
| Add854's real state-one edge into that shared pointer load | Still22 conversions/24 RETs; four prior owners lost |
| Explicit captured slot+C dispatch for post-state851 with int850 | Correct load order and21/23 counts;106 or109 body differences and five prior owners lost |
| Named850 short/int/double carriers or a long conversion | Complete predecessor payload unchanged |
| Named851 post-state long/short/int/double or reference through local short interface | Merges target-distinct851/854; public owner audit rejects it |
| Independently checked physical Youmu RTTI hierarchy | Complete predecessor payload unchanged; corrected short851 still merges |
|823 used direction locals, typed payload constness and additional int interface | No overall improvement; the extra823 int interface worsens the30-byte witness |

These are controlled source/ABI/lifetime observations for this context. They
do not prove LTCG is necessary or sufficient. Remaining work includes821's
handoff into848 after its pointer load,823's selector/spawn register choices,
820/850's physical tail and851's remaining pointer/call preparation. Do not
add invented interfaces, dummy lifetimes or false ABI contracts to force them.

## Reproduction and analysis receipts

```bash
python3 scripts/build.py --unit gpt-web-youmu-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py youmu-object-action-entry \
  build/match-units/GptWeb_YoumuObjectActionEntry.obj \
  --unit gpt-web-youmu-object-action-entry --json
python3 scripts/audit-youmu-object-entry-calls.py \
  build/match-units/GptWeb_YoumuObjectActionEntry.obj
python3 scripts/build.py --unit cross-v106a-animation-sequence-virtuals --compare --json
scripts/compile-unit.sh scripts/probes/animation-sequence-word-abi.cpp \
  build/youmu-word-abi.obj
python3 scripts/compare-unit-object.py cross-v106a-animation-sequence-virtuals \
  build/youmu-word-abi.obj --address 0x0045C390 --json
```

The root comparator is expected to return1/nonexact; owner/native and callee
checks return0. To reproduce the historical negative source independently:

```bash
git show 993cd94:src/characters/YoumuObjectActionEntry.cpp > .analysis/youmu-old851.cpp
scripts/compile-unit.sh .analysis/youmu-old851.cpp build/youmu-old851.obj
python3 scripts/audit-youmu-object-entry-calls.py build/youmu-old851.obj
```

The final command must return1 with four alias-only differences. No historical
object or source file is required to trust a cached result. Existing-object
comparisons and the native auditor report build provenance as unverified;
use the preceding producer command/report for that separate assertion.

Full private source/control/compile recipes are under
`.analysis/youmu-entry-carriers-20261019/`; canonical packets, fresh official
build/owner/native reports, ABI witnesses and Ghidra receipts are under
`build/youmu-entry-carriers-20261019/`. They occupy under8MiB combined.
The required IDA preflight again rejects the wrong open executable. Two direct
read-only Ghidra passes use128MiB heap, CPU0 and no analysis/write/save;
they independently attest imported/file identity, entry, mapped text, root
bytes and RTTI descriptor bytes/names. All nine primary database hashes agree
afterward; temporary aliases are removed. An initial attempt without an820
instruction failed closed and is preserved separately. No target bytes,
metadata or analysis database are patched. No cold aggregate replay is claimed.
