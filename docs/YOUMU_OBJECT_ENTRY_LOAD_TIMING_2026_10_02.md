# YoumuObject entry load timing, 2026-10-02

## Fresh bounded baseline

**Observed:** `YoumuObject_initialize_action_entry @ 0x00543670` retains its
reviewed callable `[543670,544A97)`, 5,159 bytes, against the original Japanese
1.06a executable SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh configured VC8 comparison first differs at `+0x80`, target `9D` /
candidate `97`, in the default-exit branch displacement. The first 128
canonical bytes agree. Candidate metadata starts at `+0x1424` (5,156), versus
target `+0x1428` (5,160). The candidate mapper preserves 29 distinct action
owners and zero splits; strict instruction/edge diagnostics remain 6/30
including entry. Source and exact ledgers are unchanged.

Callable SHA-256:
`d680c9d1386e6c3f8cc5e755dffccbbd431864dee308f760cf48fe00274ed245`.
Compared candidate-window SHA-256:
`0b174356a268e762184a61f94774ae9af698df7af1ae230a548e055594de1acb`.
Retained source SHA-256: `3201011cbbb0c0736bf3041496fae8dd192d79c9e51470e9c31ac4f6f6f294af`.
The compared window includes candidate-adjacent metadata and is not its
callable-body hash.

Raw traversal reaches all 1,294 instructions / 5,159 bytes, with no unreached
ranges or unresolved indirect exits. Both primary and nested switches remain
validated against target tables. Shared roster Object callee ranking was
rerun before further source analysis; no new callee is promoted by this work.
The IDA preflight again rejects the attached SHA beginning `10350095`; all
observations use the hash-attested PE, with no new database/decompiler output.

## Action851 observation and negative control

**Observed:** target851 begins at `543DCE`:

1. `543DCE MOV ECX,[ESI+340]` captures the heading pointer.
2. `543DD4 MOV EDI,[ESI]` captures the receiver's vptr.
3. `543DD6 MOV word [ESI+344],1` writes the state word.
4. `543DDF FLD dword [ECX+8]` loads the sequence value.
5. `543DE2 CALL 68A1A0` converts it to an integer.
6. `543DE7 MOV EDX,[EDI+C]; 543DEA MOV ECX,ESI; 543DEC PUSH EAX;
   543DED CALL EDX` invokes the sequence selector.

The baseline candidate starts at `543DC8`, loads heading[2] into ST(0) at
`543DCE`, then captures the vptr and writes the state word at `543DD3`.
Its selector argument PUSH precedes receiver placement into ECX. Both physical
owners occupy 40 bytes, but neither load timing nor instruction schedule agrees.

**Inferred and tested:** moving the real `double const sequence_value`
declaration after `state_344 = 1` expresses target load/store order in source.
The control compiles, but VC8 merges target-distinct 851/854 switch destinations:
29 becomes 28; candidate metadata moves to 5,116. The strict owner audit fails
closed with `candidate merges distinct target physical owners`. Canonical
comparison is still nonexact at +0x80, with compared-window SHA-256
`2da35e6af65f914594d3c7b4ed94823170677017d58d7293e333a5c14618fd95`.
This control is not retained. It proves neither source-level equivalence under
all heading aliases nor that the original source necessarily used double.
The baseline declaration remains a hypothesis that preserves physical owners.

## Action800 conversion carrier control

**Observed:** target800 converts heading[2] at `543721`, loads slotC into EDX
at `543726`, puts the receiver in ECX at `543729`, then pushes EAX at
`54372B` and calls EDX. The same-sized candidate exchanges receiver placement
and the PUSH. Similar single-instruction scheduling differences occur in
other owners; equal owner sizes are not regional byte acceptance.

**Inferred and tested:** materializing this actual converted selector
argument in one local `int const sequence` before the call is a natural
source-value representation. The resulting whole compared window is
byte-identical to the baseline, including 29 owners, metadata at 5,156 and
6/30 instruction/edge diagnostics. It is not retained. This closes that
carrier spelling as a cause of the current action800 residual under the
configured compiler profile.

Neither control establishes an assembly requirement. Complete raw decoding
of this callable contains none of FSINCOS, FRNDINT, FSIN, FCOS, FPTAN or FPATAN.
The [TH08 instruction-island reference](YOUMU_SHARED_ZERO_RETURN_AND_CONTROLS_2026_10_02.md)
and the exact natural-source
[sprite-rotation x87 control](SPRITE_PIVOT_ROTATION_2026_10_02.md) remain
separate evidence; they cannot determine this root's compilation context.

## Remaining physical ownership and reproduction

The fresh target/candidate owner spans are explicitly:

| Owner | Target | Candidate |
| --- | ---: | ---: |
| 820 | 12 | 26 |
| 850 | 57 | 37 |
| 851 | 40 | 40 |
| 854 | 9 | 9 |

The target820 jump at `543C16` enters the 850 tail at `543DA7`, after its two
scale stores. The candidate hoists angle work into 820 and uses another
shared selector path. The
[earlier switch-closure evidence](YOUMU_OBJECT_ENTRY_SWITCH_CLOSURE_2026_09_26.md)
already records negative duplication, post-switch join, scoped-value and
compiler visibility probes; they are not repeated here. Original shared-tail
placement, virtual-call lowering, value/register lifetimes and TU/LTCG context
remain unknown. Preserve distinct target owners and full callable acceptance.

```bash
python3 scripts/build.py --unit gpt-web-youmu-object-action-entry --compare --json
python3 scripts/audit-giant-action-owners.py youmu-object-action-entry \
  build/match-units/GptWeb_YoumuObjectActionEntry.obj \
  --unit gpt-web-youmu-object-action-entry --json
```

Finished-worktree reports:
`build/youmu-object-entry-load-final-20261002.json` and
`build/youmu-object-entry-load-final-owners-20261002.json`.
Private controls and compare/export helpers are in
`.analysis/youmu-object-entry-lifetimes-20261002/`; corresponding reports and
hash-pinned raw instruction packets are in
`build/youmu-object-entry-lifetimes-20261002/`.
No source, shared ABI/header, compiler flag, relocation map, object partition
or exact acceptance changes. No cold aggregate replay is claimed.
