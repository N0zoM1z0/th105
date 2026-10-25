# Complete effect resource loader437EC0

The complete2528-byte source remains **nonexact** after full canonical replay:
79 unequal positions, first4383B5, full candidate SHA
`94b3933b2f738df5bc2b78da6ea254f3bec748027eba57fcefc6dccfca1ab49b`.
Direct WORD-member and real group-lifecycle visibility controls are whole-payload
byte-neutral. This finite lane is closed; there is no implemented/matches row.

## Observed target

All work uses original Japanese1.06a SHA
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/status/tracking checks pass. IDA still fails with10350095 and was
not used. The source and ABI were recovered from hash-attested PE instructions.

Main437EC0..4388A0 exclusive is2528 bytes, SHA
`e0d31abb77468f60189ea2e9473f5896f0a08155057d03d81e74bfc40ce94566`.
All794 decoded instructions close through RET4 at43889D; there are no escaping
direct edges or indirect jumps. Independent4388A0 begins immediately afterward.
The native GS/EH prologue allocates364 scalar bytes, installs handler6B86F2,
and saves EBX/EBP/ESI/EDI. Twenty-five invalid-parameter sites remain present.
The linear CFG audit follows normal call fallthroughs; the separately pinned
vector range-error provider40C350 is an exceptional/nonreturning contract.

Three independent exact30-byte effect manager wrappers46F900/4245B0/4389B0
call this receiver at+8, ignore EAX and then preallocate their object pools.
Their current source/type families corroborate authored effect-resource policy.
The new origin rule pins the full root and those three incoming E8s. It adds
one authored candidate, without changing any helper origin/exclusion.

Native reader callbacks use vslot4, with27 static read sites and widths:
1,2,128,4,4,4,4,1,4,4, then seven WORDs, byte, WORD, four bytes, four WORDs.
Counts at runtime vary with loops/branches. Version is consumed but not checked.
The signed WORD texture count resizes the vector at receiver+64. Each128-byte
filename is prefixed by the split directory using the exact format `%s%s` at
6D6A18, then loaded through404C90 into a checked vector element. No slash or
terminator is synthesized by the parser. The split call40D0B0 receives the
global702918 in ECX plus three stack arguments; its body does not use ECX.

The signed DWORD entry count controls group parsing. Ordinary keys replace
an existing map entry, append a group, reset previous to0 and next to self,
and establish the chain root. Key-2 appends a continuation using the previous
deque back and repairs previous/next/root links. Key-1 reads alias key/target
pairs into two owning lists and skips frame parsing. Reverse list backs later
resolve aliases through the map; unresolved targets are skipped and both lists
are popped. All normal and exceptional owning lifetimes remain represented.

Groups are32-byte polymorphic objects: vector at+4, byte flag+14, links+18/+1C.
The group constructor422AE0, destructor422660 and copy provider422E00 are fully
pinned. The frame vector's4229E0 provider copies **eight16-bit fields** at+4..12,
byte+14 and optional pointer+18, with vptr6C0908. Frames have size1C, rather than
the previous Fighter loader's88-byte records. Group/frame ownership and exact
original nominal names remain separate questions.

For each frame, a DWORD texture index narrows to WORD+A; seven WORD reads fill
C,E,10,12,4,6,8, followed by byte+14. Tag2 allocates32 bytes: signed WORD modes
0/1/2 set the payload mode1/2/3; other modes leave it untouched. Four bytes are
read into payload+7,+6,+5,+4. A signed WORD divided by double100 is narrowed to
float and propagated through payload+8/+C/+10; three further signed WORDs become
float fields+14/+18/+1C. No Fighter-only field or collision vector is consumed.

The native temporary before vector assign clears **all28 bytes, including the
vptr**, and then explicitly clears its byte tag/payload pointer. The first
retained FrameData hypothesis preserves a published vptr and therefore was not
adopted. The new local physical view preserves the observed destructive clear;
shared accepted types/headers and their earlier claims are unchanged.

## Whole-function comparisons and stop condition

`src/battle/EffectResourceLoading.cpp` is complete. It uses real checked STL
containers, scoped file/list ownership, an actual32-byte group type and an
actual28-byte frame type. Declaration-only providers keep their independently
observed ABI. The root uses a runtime-only nonconstructing receiver view.
All exact callers ignore EAX, and the native exit does not assign a logical
return value; the source uses void and does not invent a return. The original
formal return type remains unknown. No assembly, copied code bytes, inert
locals, padding, shared flag changes or fake dependencies are used.

| Full source trial | Bytes | Canonical result |
| --- | ---: | --- |
| first complete retained FrameData hypothesis |2544 | Compared immediately;2211 unequal target-range positions |
| actual eight-WORD copied fields/implicit copy visibility |2514 |2314 unequal positions; root is14 bytes shorter |
| observed path receiver |2528 |741 unequal positions |
| observed whole-object28-byte frame clear |2528 |79 unequal positions; first4383B5 |
| direct typed WORD fields |2528 |Whole payload unchanged |
| genuine group constructor/destructor definitions in the same TU |2528 |Whole payload unchanged |

The group visibility control uses the real observed `frames.clear()` operation
in both lifecycle bodies; their helpers receive no exact/origin credit. Its
private extra vtable binding is qualified by native group construction/copy/
destruction and is not added to public ledgers. Public source keeps the minimal
declaration-only group providers. The two neutral controls end this finite lane.
Original local/nominal identities and TU/backend scheduling remain unknown;
do not infer LTCG impossibility from this standalone result.

Two independent public builds, `formal-first.json`/`formal-second.json`, emit the
same2528 bytes. Public full-section audit replays every relocation and reports
the same SHA/79 differences. The first1269 canonical bytes agree exactly;
remaining differences involve reader-call scheduling, argument registers and
stack displacements, rather than a missing branch/reader site. Equal size is
diagnostic evidence and conveys no exact credit. No broad behavior matrix was
needed to establish these byte/width/lifetime facts.

## Reproduction

```bash
scripts/repo-python scripts/build.py --unit exact-first-effect-resources --compare --json
scripts/repo-python scripts/audit-effect-resources-target.py
scripts/repo-python scripts/audit-effect-resources-target.py --object build/match-units/ExactFirst_EffectResources.obj
```

Build/object audit exit1/nonexact; target-only audit exits0. Receipts are below
`build/effect-resource-437ec0-20261026/`; private first/control sources, bindings
and full-replay recipes are below `.analysis/effect-resource-437ec0-20261026/`.
Only the root EH prefix and complete5-byte format literal add data rows; the
path receiver aliases the already attested module-path global. Prior source,
headers/profiles and bindings are unchanged. Heavy work is CPU0/nice10, serial;
available memory remained over10GB and swap stayed134MB during focused work.
Fresh `origins-check.log` passes all4024 rows with1603 authored/1419 excluded/
1002 review candidates. `cold-all.log` passes all526 accepted units/1414
functions under the current manifest; exact authored bytes remain385903.
Target-backed floating audit still passes all1999 references. This root adds
no exact or source-selected credit.
