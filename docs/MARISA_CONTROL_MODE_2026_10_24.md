# Marisa slot 5C control mode: complete source, nonexact

## Current result

Marisa primary slot+5C `0x004B8280` now has complete reviewed source and a
reproducible full-object comparison. Callable 1771 and complete payload 1788
bytes are target-sized. Exactly nine bytes differ at `0x4B864D..0x4B8655`
(`+0x3CD..+0x3D5`); all 17 adjacent metadata/alignment bytes agree. This is
**source-present only**, not an exact result or a matches.csv entry.

```sh
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-marisa-control-mode --compare --json
```

The first two commands correctly return 1. The full audit requires length and
byte equality across the entire emitted section tail with strict relocation
and literal replay. The third is a bounded semantic diagnostic and returns 0
for 18 native-helper prefixes; it stops before the genuine action callback,
not after executing the complete animation/asset graph.

Selected complete canonical SHA256:
`0db6d5c7835af8e00bbaaa6edb28851dc75ed6ee9a1699c13a2a670813026849`.
Target complete SHA256:
`c5a7b3efb8411936ea2c29941773cc94813aa4fe0353a6ca8e736f587c92f54e`.

The residual is one real receiver-preparation instruction moving around the
next-sequence argument calculation and virtual-slot load:

```text
target: mov ecx,esi; add eax,1; push eax; mov eax,[edx+0x0c]; call eax
source: add eax,1; push eax; mov eax,[edx+0x0c]; mov ecx,esi; call eax
```

No instruction, padding, register constraint or fake dependency is added to
force the schedule. After two neutral controls, retain this source and switch
representatives unless independent type/lifetime/TU evidence changes the
question. Original nominal owner layout and compiler context remain unknown;
there is no proof that standalone matching is impossible or that LTCG is needed.

## Observed target closure and ABI

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Existing RTTI/authored anchor slot+5C cell `0x006C45E0` is independently
read back as 4B8280. Authored ownership and the denominator are unchanged.

Raw traversal closes all 442 instructions, eight RETs and every direct/indirect
edge. Callable `[4B8280,4B896B)` ends with the virtual-slot58 JMP at 4B8969.
That tail restores EDI/ESI/EBX, discards the real four-byte local and forwards
ECX with no stack arguments. It is a terminal virtual transfer, not an unknown
jump-table entry or an extension into the CPU-policy body. Earlier five INT3
bytes isolate entry from the preceding CPU metadata.

A NOP at 896B precedes the two-entry destination table 896C. Eight index bytes
at 8974 map records 0..3 to 835F and 4..7 to 8567. Records 8..11 and 248..255 are
handled by actual comparisons; negative/gap records use the real default.
Metadata ends 897C, followed by four INT3 bytes before the next function.

The receiver is ECX, retained in ESI; EBX/ESI/EDI are saved and the entry's
PUSH ECX reserves a four-byte local. All eight RETs purge no arguments.
The source's void method is a call-view; the complete original C++ type is
not recovered. Partial runtime views must never be constructed or embedded.

There are 26 physical CALLs: one checked deque 4399C0, four facing helpers 478E60,
seven selector calls 4067D0, one native conversion 68A1A0, eight virtual slot 08
calls and five virtual slot 0C calls. The extra slot 58 transfer is a JMP.
Direct helpers have existing accepted/excluded provenance and receive no new
credit. Source uses an ordinary conversion expression for the x87/EAX32 helper.

Primary cells 6C458C/6C4590 bind slots 08/0C to accepted 45BFE0/45C390. Their
current source/ABI supports `int(short)` / `int(int)` ECX methods with RET4.
The updated view uses those actual declarations; their results are ignored.
Slot 58 binds the separately reconstructed Marisa CPU policy 4B4070.

Raw literals retain their access widths: F32 values 2^32/12/0.5/640/12.5/0.4,
and F64 values 10/4/5. Unsigned selector-result consumption requires the real
FILD/sign-test/FADD2^32 paths. The final conversion cache is signed 32, published
as WORD76A and incremented as a full 32-bit sequence argument.

## Source review and bounded trials

The retained source and existing probe unit predate this review and had no
selected mapping or source credit. Its fresh baseline emits 1884 bytes and
first differs at+A3. It is a hypothesis, not current-target evidence.

| Trial | Evidence and full result |
| --- | --- |
|00|Direct WORD76A reads and actual F64 literal widths replace cached-state/float hypotheses. Complete source 2020; missing state-owned exits duplicate real callbacks. |
|01|Native state 3 action exits return after publishing state 2. Complete 1796, all 13 direct/13 virtual calls restored. |
|02|Raw FCOMP640/TEST AH,5 requires x>640 to publish-1, otherwise+1, including NaN. Explicit stores fix the real predicate; full 1800. |
|03|Keep the peer-positive state 2 branch's helper/action block before its dead-peer fallback. Complete 1788 with only the nine-byte scheduling residual. |
|04|Unsigned conversion-cache control changes the actual conversion lowering/frame and emits 1844. Rejected; the signed producer remains. |
|05|Actual slot 08/0C method declarations from accepted callees are byte-neutral against 03. Selected truthful call-view. |
|06|Preincrement versus next+1 in the real sequence argument is fully byte-neutral against 05. Keep the simpler selected expression and stop spelling trials. |

Records 0..3 retain actions 770/703/710/702/711 and state-owned peer-life gates;
records 4..7 retain the 720 sequence/timer loop and post-callback WORD rereads.
Records 8..11 retain the 730/732 choice and separate launch constants. Record
248..255 resets action700 through slot 08 and then reloads/forwards slot 58.
Repeated timer-source bodies are preserved; no unchecked family substitution
or gameplay naming is needed for this complete source.

The actual facing correction is independently executable. The public prefix
audit initializes a real native deque, actual Marisa vtable and seeded original
MT state. Both record families 0/8 use state 3/action700 and reach the genuine
45BFE0 callback with argument 702. Nine x values per family cover signed zero,
640 and neighboring floats, infinities, quiet NaN and signaling NaN. Native
actor fields, launch values, RNG state, helper trace and stack state agree in
18/18 selected prefixes. Native target output is checked independently before
comparing the source. The prior <=640 ternary is rejected on four NaN prefixes.
No helper result or target instruction is substituted.
Vector SHA256:
`3d9bb29db2cd4187e6a7bf4eb958c8f90f6ccf5244f36ac0ec17b8423e72ca2d`.
This is specific facing/launch evidence, not an exhaustive execution matrix or
an exactness substitute.

## Analysis safety and retention

IDA preflight still rejects a different executable. No semantics or writes
from that session are used. One direct CPU 0/nice10 read-only Ghidra run uses
384 MiB and independently attests file/program SHA256, Windows x86 identity,
image base, entry point, all raw-backed sections and the exact root body.
Temporary root/callee views are read back and rolled back; nine pinned primary
DB hashes are unchanged. Decompiled output is a hypothesis, never pasted as
source. The raw CFG independently classifies its warned-about register tail.

Generated raw CFG/literals, full-source/COFF/normalization/difference receipts, DB
attestation, formal builds, and positive/negative facing outputs remain under the
corresponding `build/`. No executables, analysis databases or generated reports are
committed. Existing accepted source, shared headers, compiler settings and
relocation mappings are unchanged. The existing unit is reused; no redundant unit is
added.
