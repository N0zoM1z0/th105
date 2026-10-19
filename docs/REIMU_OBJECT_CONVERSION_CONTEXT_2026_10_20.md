# ReimuObject conversion and compilation context

## Target and fresh baseline

Bounded root `ReimuObject_initialize_action_entry @4A1CE0` remains
implemented and nonexact. Original Japanese v1.06a executable SHA256 is
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Callable `[4A1CE0,4A2FFC)` is4892 bytes, SHA256
`1cda9c10ed7d9ab2225800db60a62f45099c7cd3d7adec15621bfa3a49b8e6c1`.
The42 primary destinations, seven auxiliary switches,1325 instructions,
39 RETs and registered596370 tail remain unchanged.

Fresh `gpt-web-reimu-object-action-entry` compilation repeats source
`3803a002807ee0a329e9721c4e814bc11159711e6dc515afbf2e88a5df7fd6dd`.
The new baseline object SHA256 is
`95d4a2d956f3eaf406f593341094ae34adfd8bd044384b9e0fad09fcd6ede21f`.
Full5440-byte canonical payload remains
`65298d3670c2c739162abc2d7172dc3db194835b05eedd407688a0b5e3be1347`:
fourteen differing body bytes in906/999, all548 metadata bytes equal,
41/43 owner-relative instruction/edge diagnostics and first strict difference
+1140h/4A2E20. No source, ABI, profile or ledger selection is made here.

## Twenty-one controlled attempts

All compiler invocations are serial at CPU0/nice10. Fifteen controls reproduce
every byte of the baseline payload:

| Property tested | Controls |
| --- | ---: |
|Embedded `/Z7` debug information|1|
|Signed32-bit `long` conversion in906/999|1|
|Used inline selector helper: float member in906/999 or all31 conversions, float free helper in906/999, double member in906/999 or all31 conversions|5|
|Explicit signed sequence-word reads with the signed declaration, or unsigned storage with the same signed interpretation|2|
|`/Gr`, leaving the explicit external declarations unchanged|1|
|Current physical hierarchy; template parent/typed fighter owner; derived state ownership from364h; both template and derived state|4|
|Explicit800-based outer selector with correspondingly shifted case expressions|1|

The helper bodies perform the actual conversion and virtual selection; no
return, local or behavior is fabricated. The sequence-word controls keep its
two-byte representation and existing signed uses. All are payload-neutral;
none recovers906's call preparation or999's pointer/call registers.

Fresh raw COL6D9C8C readback confirms all eight RTTI entries and offsets:
ReimuObject/CharacterObjectEx<Reimu,ReimuObject>/CharacterObject at0,
CObjectBase at330h, AttackObject/AnimationObject at0, AnimationObjectBase at4
and Environment at130h. The existing physical hierarchy's function body is
checked against the current source, differing only in its inherited sprite
member name. The template controls use a typed fighter pointer and retain
the same three byte-view accesses at fighter+605h. Moving the existing
364h..386h state members changes source ownership while retaining the checked
388h view and offsets; it adds no padding. Original field ownership and complete
class declarations remain hypotheses. Every hierarchy control is byte-neutral.
Explicitly expressing the observed800 index bias also preserves the complete
payload; shifting both selector and case expressions retains every signed-word
action/default outcome without introducing a runtime local.

Four other controls have complete private relocation replay but remain wrong:

| Control | Code / payload | Result |
| --- | --- | --- |
|64-bit integer conversion in906/999|4892 /5440|20 differing body bytes; metadata equal; two real calls move to68A1D6|
|64-bit conversion at all31 parameter conversions|4892 /5440|123 differing body bytes; metadata equal|
|`/fp:strict`|5160 /5708|Wrong code extent;27 conversion calls use68A1BC|
|`/Oy-`|4796 /5344|Wrong extent and initial EBP prologue|

These replayed helper addresses come from the independent member witness below,
not aliases to the baseline conversion entry. For candidates with a different
code boundary, a positional comparison across that boundary mixes code and
metadata; no body-difference count or partial-byte credit is claimed for them.

`/fp:fast` compiles with code/payload4796/5344, but introduces an unbound
`__real@3f800000` data relocation. No arbitrary target pool address is selected.
Its report contains only unrelocated COFF structure, not a canonical payload.
The installed `/Zi` attempt fails with C1902, "Program database manager
mismatch"; its code-generation effect is unknown. It is not evidence against
an original debug-information setting. These two attempts are distinguished
from the nineteen fully replayed controls above.

## Conversion entries are distinct, not interchangeable aliases

The pinned SP1 `libcmt.lib` has SHA256
`3bc6c5b90f8507964839fd0264d8565c3b766d01f9efcad336532a11e8f06ac3`.
`scripts/extract-msvc-library-object.py` extracts
`../build/intel/mt_obj/ftol2.obj`, SHA256
`571c5539497ab6ae752435d5a3c96bc7f186f96ab2fc6dedf37a12c2169fb5d3`.

**Observed:**the complete171-byte text matches target68A1A0..68A24B after
replaying exactly two DIR32 fields at offsets2/30. Both reference the writable
target7039C8 corresponding to `___sse2_available`. No other bytes are masked
or changed. The complete replay is unique in target `.text`, with SHA256
`aeb7a87183a558dd228b968d6264bdeb993114992b7807d638c943a2adadd1a2`.
The member's public symbols establish these internal entry offsets:

| Archive symbol | Offset | Target entry |
| --- | --- | --- |
|`__ftol2_sse`|0|68A1A0|
|`__ftol2_pentium4`|9|68A1A9|
|`__ftol2_sse_excpt`|1Ch|68A1BC|
|`__ftol2`|36h|68A1D6|

906 CALL4A2E1A and999 CALL4A2FB6 both target68A1A0. The exception-sensitive
entry additionally checks the floating control word; the64-bit entry begins
the x87 conversion path. They cannot be rebound to68A1A0 merely to qualify
a candidate. The private exporter uses their actual witnessed entries when
diagnosing64-bit/strict controls. No public binding is changed.

This member is already excluded as VC8 runtime by the existing origin rule.
The witness adds **no authored byte/function credit**, no origin-accounting
change and no new candidate split at the internal labels. It does not uniquely
identify the original compiler patch revision or archive release if another
release contains identical instructions. Archive symbols here are provenance
evidence, not newly promoted project function names. This is a read-only
provenance comparison, not a configured or accepted exact match unit; no
`matches.csv` or matching-status result is recorded for the member.

## Execution, database safety and reproduction

Fresh baseline execution passes0/672 with the existing input SHA256
`95ec78bf917491d75b16bb6865ce1db5c9af6dbb500dcc733e16e198c73e18b5`.
Its scope remains the admitted906/999 selector/frame/sprite protocol, including
624 actual helper chains; it is not whole-root semantic coverage. No changed
control is executed. See [the execution contract](REIMU_OBJECT_ENTRY_CALLS_2026_10_19.md).

Direct read-only Ghidra re-attests executable/imported identity, base/entry,
x86/windows target, mapped text, complete root bytes, both relevant vtable
cells, the void4892-byte function and registered terminal edge. It checks the
two target conversion calls, decodes the171-byte island and verifies its hash.
All nine primary database files remain unchanged; the temporary alias is
removed. No IDA semantics or factory adapter is used.

Recipes are below `.analysis/reimu-entry-conversion-context-20261020/`;
reports/inputs are below `build/reimu-entry-conversion-context-20261020/`.
`probe.py` covers scalar/helper/flag controls, `hierarchy.py` the four layout
controls, `ftol.py` the complete member proof and `ghidra.py` the independent
readback. `summary.json` records hashes/results before redundant files are
removed. The current source, accepted helper inputs and genuine65298d36
closure remain unchanged; no aggregate cold replay or LTCG impossibility is
claimed. The fourteen906/999 register/preparation bytes remain unresolved.
