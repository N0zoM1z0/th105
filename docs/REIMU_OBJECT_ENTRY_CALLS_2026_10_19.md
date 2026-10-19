# ReimuObject906/999 real selector execution

## Target and fresh comparison

This is a bounded continuation of the authored initializer
`ReimuObject_initialize_action_entry @004A1CE0`, callable
`[004A1CE0,004A2FFC)`,4892 bytes. Only original Japanese1.06a executable
SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Callable SHA256 is
`1cda9c10ed7d9ab2225800db60a62f45099c7cd3d7adec15621bfa3a49b8e6c1`.
The existing RTTI/vtable6C40A4/slot3C ownership,42 primary destinations,
seven auxiliary switches,39 RETs and596370 tail remain unchanged.

A fresh ordinary build of the unchanged source SHA256
`3803a002807ee0a329e9721c4e814bc11159711e6dc515afbf2e88a5df7fd6dd`
still has14 differing callable bytes, zero differences in548 adjacent metadata
bytes and41/43 instruction/edge owner diagnostics. Both callable extents are4892
bytes/1325 instructions. The complete5440-byte canonical payload remains
`65298d3670c2c739162abc2d7172dc3db194835b05eedd407688a0b5e3be1347`.
The first strict difference remains+1140h/4A2E20. No game source, ABI, profile,
relocation binding, implemented row or exact credit is changed.

## Observed call shapes and rejected source hypothesis

**Observed:**906's conversion call68A1A0 at4A2E1A is followed by target
`MOV EDX,[EDI+0C]; MOV ECX,ESI; PUSH EAX; CALL EDX`. The candidate instead
publishes ECX and pushes EAX before loading/calling through EAX. The target's
906 sequence4 parameter pointer uses EDX where the candidate uses ECX.

In999 the target reads the parameter pointer into EDX at4A2FA9 and loads its
third float at4A2FB1; the candidate uses EAX. After conversion4A2FB6, target
loads/calls the virtual through EAX, whereas the candidate uses EDX. These are
the two complete85/66-byte owner diagnostics that still differ.

The preceding Fighter-root direction-carrier recovery suggested testing
conversion-value lifetimes here. This is a new hypothesis, not a transferable
VC8 rule: the remaining Object windows do not read facing. Used int locals in
906 alone,999 alone or both, used float locals in both, and implicit float-to-short
selector conversions all reproduce every byte of the unchanged65298d36 payload.
None is selected. The experiment does not establish a TU/LTCG impossibility or
prove the original conversion spelling.

Direct read-only Ghidra independently checks executable/imported identity,
base400000, entry68B9D2, x86/windows analysis target, mapped text, complete
callable bytes and the original selector/frame vtable entries before inspecting
these windows. It also verifies the4892-byte void function view and registered
terminal596370 edge. All nine primary database hashes agree afterward; the
temporary project alias is removed. The first audit used an incorrect999 range
start4A2FAB inside an instruction and failed closed; the raw instruction boundary
4A2FA9 was then checked successfully. No target or saved database bytes changed.

## Actual helper execution and sensitivity

`scripts/audit-reimu-object-entry-calls.py` executes the original PE unchanged
and loads the fully relocation-replayed candidate at a separate800000 address.
It requires a5440-byte envelope,1325 decoded callable instructions/39 RETs and
all548 canonical metadata bytes, and rejects unbound relocations. Both code
mappings are read/execute; a write guard restricts writes to the object and
stack. The supplied ten-sequence tree/frame/vector graph is read-only, has a
zero texture handle and uses the original ReimuObject vtable. No helper result,
instruction, vtable entry or callback return is substituted.

The full matrix passes **0/672**:336 inputs per action,14 float request bit
patterns,12 initial sequence values(-1 through10), and x87 precision53/64.
Requests include positive/negative zero, fractional values0.5/-0.5, and valid
selector destinations0..9. Every input must restore the native RET ABI and
nonvolatile registers with balanced TOP. The checker compares all388h object
bytes, selector arguments, ordered helper-entry traces and FPCW.

**624** inputs require actual68A1A0 conversion,45C390 selection,45C320 tree
lookup,45C180/45C110 frame application,436760 sprite-frame forwarding,
40C100 texture-vector lookup,407160/407230 setup and4073A0/4073C0 transform
reset/commit through native root RET. The other48 exercise906's zero guard.
Both sides visit102 root instructions; this is not whole-root instruction
coverage. Input SHA256 is
`95ec78bf917491d75b16bb6865ce1db5c9af6dbb500dcc733e16e198c73e18b5`.

Two real negative source controls retain the envelope/metadata gates and each
have15 differing body bytes instead of14:

| Control | Actual mismatches | Canonical payload SHA256 |
| --- | ---: | --- |
|999 final sequence test4->5|48/672|`c1290ec7592f5d19c9167e2a4d0a070a87c422791c43697c8d1036c8087c1d20`|
|906 sequence4 phase113 clear0->1|28/672|`293b83907c343a5073b9bf9b1475d3e7c9639b6e11e1a90a2dbb7bfddc87f4ae`|

Both auditors exit1 because actual state differs, after successfully completing
all672 inputs. This is sensitivity evidence for this admitted matrix. It does
not prove exceptional floats, negative/out-of-range selected destinations,
textured/resource/world graphs, other action owners, or canonical equality.
Smoke192 is a subset, not additional unique coverage. The existing whole-root
semantics and compiler-context unknowns remain open.

## Reproduction and retained state

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-reimu-object-action-entry --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-giant-action-owners.py reimu-object-action-entry build/match-units/GptWeb_ReimuObjectActionEntry.obj --unit gpt-web-reimu-object-action-entry
taskset -c 0 nice -n 10 python3 scripts/audit-reimu-object-entry-calls.py build/match-units/GptWeb_ReimuObjectActionEntry.obj
```

The first command still returns1 for the strict mismatch. The execution auditor
accepts an existing object and explicitly does not claim build provenance;
the fresh build report is `build/reimu-init-direction-baseline-20261019.json`.
Its object SHA256 is
`7ca8c6a3200d19110cb3df3769878251982a2b56bb6908e63d09698ba4563a2f`;
COFF timestamps can change on reproduction, while source/canonical pins remain.

Reports, current canonical packet, native/negative receipts and nine-file DB
pins are below `build/reimu-entry-carriers-20261019/`. Private probe/export,
negative-control and read-only Ghidra recipes are under the corresponding
`.analysis/` directory. Unselected carrier source/object copies are regenerable.
VC8 builds were serial; heavy analysis ran on CPU0/nice10 with a128MiB Java heap.
Accepted unit inputs are unchanged; no aggregate cold replay is claimed.
