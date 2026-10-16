# Aya CPU source types and genuine link context, October 17

The active root remains `Aya_update_cpu_action_policy @ 0x006126E0`, 16,032
bytes / 4,097 instructions. This follow-up replaces integer address carriers
and the opaque sequence-access declaration with actual pointer/container
source. Ordinary VC8 compilation remains byte-neutral and **nonexact**.
No exact authored bytes are added.

## Retained source and library witness

The target repeatedly loads the opponent pointer at +170 and accesses its
float coordinates +EC/+F0, action word +13C and word +174. Eleven local
carriers now use `CpuActionPolicyView *`, with typed coordinate accesses,
instead of storing object addresses in `int`. This is a method-prefix model,
not proof of a complete dynamic class or object size. The shared header and
physical offsets remain unchanged.

The sequence access is now the actual checked
`std::deque<FighterSequenceSlot>::operator[]` from the pinned VC8 headers,
with a size assertion for its 20-byte prefix. The independently reviewed
record is 0x98 bytes. All 25 accesses consume record zero just as the original
calls do. Record tags use the named `record_id_00` field, preserving explicit
unsigned interpretation where the original consumers use WORD values.
No facade body, helper-result hook or executable address binding is
introduced. The selected root unit binds the real template symbol to4399C0.

```bash
python3 scripts/build.py --unit gpt-web-aya-cpu-action-policy --compare --json
python3 scripts/compare-unit-object.py cross-v106a-battle-info-record-render build/match-units/GptWeb_AyaCpuActionPolicy.obj --address 0x004399C0 --json
```

The first command retains the ordinary whole-root mismatch. The second
reuses the **existing library unit's** contract and reports **94/94 exact**
for the template emitted in the new CPU object. Its object hash agrees with
the separate fresh root build receipt. Existing-object comparison itself
attests no compiler provenance. The target is already classified as compiler
code; no duplicate match-unit address, authored mapping or match credit is
added. The witness supplies a genuine source dependency, without uniquely
identifying the original compiler patch revision or template element type.
Record ownership/layout has independent game-side evidence.

The root retains comparison-window SHA-256
`5469429ac8cec4a43cfd73bec917fa0c36a970d269bf9fb2418bc0b4f454c5e0`,
first difference+12E /61280E,14/41 diagnostic owners, metadata16052 and section
tail16677. The full canonical section tail is also compared with the earlier
ordinary object, not just its first16032 bytes. This is byte neutrality, not
canonical equality to the original executable.

## Genuine closed LTCG experiment

```bash
python3 scripts/probe-aya-cpu-ltcg.py --float-aliases preserve
python3 scripts/probe-aya-cpu-ltcg.py --float-aliases all
```

The new script compiles only this root with /GL, then links it with the real
MT, selector and angle objects under their existing accepted profiles. The
angle object's strict-FP profile is preserved. All three dependency units are
freshly built and canonically compared; the checked deque comes from actual
VC8 headers, and the float conversion/runtime implementation comes from the
real static CRT. The resulting DLL uses the CRT's actual startup. An initial
/NOENTRY link pulled the main-startup member and failed on `_main`; no fake
main was supplied. Normal DLL startup closes that dependency correctly.

Both final links have zero unresolved inputs. There are no /FORCE options,
source stubs, manufactured callers, vtable facades or executable ABS bindings.
Receipts record compiler/header pins, all object and CRT/SDK-library hashes,
source/generated-source/image/map hashes and complete commands. Generated
source and binaries remain below `build/aya-cpu-ltcg-probes/`. The linked
images are not executed, and no whole-image/canonical matching result is
claimed from a prologue inspection.

The preserved source produces:

```text
push ebp; mov ebp,esp; and esp,-8; sub esp,16
```

A controlled source variant changes the ten used double aliases to float.
Three hold only exact860/960 constants; the others hold float fields or
already-float distance values. The generator verifies all assignments and
refuses an arithmetic or otherwise unreviewed value before narrowing it.
The variant instead begins:

```text
sub esp,12; push ebp; push esi; mov esi,ecx; push edi
```

It has **no aligned EBP frame**, but still differs from the shipped entry,
which also saves EBX and has different register lifetimes. This is new
negative/positive phase evidence: the earlier aligned-frame result depended
on a source-type hypothesis and cannot by itself rule out every LTCG context.
It does not establish that this root originally used LTCG or that the float
variant has the original numerical/exception contract. None of these float
controls, compiler flags or link partitions replaces the retained root.

Two narrower private controls were also genuinely linked. Changing only the
constant aliases or only the field/value aliases retains the aligned EBP
frame; both groups must change in this tested context. In ordinary COFF,
constant-only aliases are byte-neutral, whereas field/all aliases change the
window hash to
`69d377d78d54419f9e057d174ce6256647f31f09fcf47c340959167d709f125b`
and metadata to16024. These are rejected source controls, not matches.

## Other bounded discriminators

- Pure bitwise evaluation of action300's two bounds emits extra boolean work,
  33 instructions /154 bytes versus target30/141. Rejected.
- An early switch break in its first arm remains folded, 29/138; a full-width
  counter with explicit narrow consumers is neutral for that arm. Rejected.
- Chained random/store assignment and store-first reload keep14/41 owners;
  a wide random local changes word tests, while explicit narrow consumption
  restores the copy but leaves interval folding and sharing unresolved.
  None is retained merely for a local instruction or size improvement.
- Pinned RTM compiler/C1/C2 hashes from `VC8_RTM_PROBE.md` were rechecked.
  Current Aya RTM output retains the+12E mismatch and16052 metadata. Its
  15/41 diagnostic result gains only policy100's alignment owner; it does not
  justify changing the configured SP1 profile.

## Verification and working state

The source/root/library comparisons and native checks use only original
Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`,
root hash
`7efa001552238230ac86c77f48f36a217cc486e847f85cb924527c64e2dc6e09`.
Fresh native checks pass0/200 finite and0/470 command cases. They cover the
retained source through genuine RET, retaining
all original helper instructions and the earlier actor/RNG/call/stack/CW
comparison limits. Earlier5000 finite and470 command results retain their
checkpoint scope; fresh reports have the `aya-cpu-layout-final-` prefix.
No unrelated accepted-unit or aggregate cold replay is claimed.

Direct Ghidra attests executable/import identity, actual entry and all mapped
.text bytes before updating the source-oriented +170 pointer in the existing
CPU prefix view and its root comment. A fresh process reads it back; view
size, field widths, the4097-instruction body and target bytes remain unchanged.
The type is a shared prefix model, not a new complete-class assertion. The
visible duplicate project is removed after verified transfer to the primary
working project. IDA preflight rejects its different target and is unused.

Local reports include `build/aya-cpu-layout-native-source.json`,
`aya-cpu-layout-native-deque-exact.json`, `aya-cpu-layout-byte-neutral.json`,
`aya-cpu-layout-closed-{preserve,all}.json` and
`aya-cpu-layout-ghidra-{save,readback}.log`. Private phase controls are under
`.analysis/aya-cpu-layout-20261017/`. Remaining work is whole-root canonical
matching: the mixed COFF/LTCG source context and inherited control/register/
shared-tail ownership remain open, with no standalone/LTCG impossibility claim.
