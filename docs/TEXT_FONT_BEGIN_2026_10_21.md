# Native ANSI font begin provider

`0x004119A0` now has complete genuine C++ begin source in the actual font
traversal TU, alongside native end411AD0. Ordinary VC8 naturally receives the
begin font in **ESI**, with no stack arguments. Source is **nonexact291/291**,
84 source instructions versus83 target, first mismatch4119A7/+7. No exact
function or byte is added.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking preflights pass. IDA rejects its wrong open
executable; no IDA semantic/metadata operation or original-byte patch is used.
New observations come from the hash-attested PE and pinned compiler/SDK.

## Complete target observations

Raw CFG traversal reaches all291 bytes/83 instructions through the single RET
at411AC2. Complete target SHA256:
`1c9a673b94a0d9a20e34859f3dc3ef0841720700f1a13cb1e318b3314358cf00`.
The candidate-main direct-edge census finds the reviewed text caller412670
at412706, using ESI. It does not establish all indirect or remote-chunk callers.

The sequence is:

1. `CreateFontA(height114,0,0,0,weight118,italic11C,0,0,128,4,0,2,49,face00C)`;
   publish its returned font at004. Italic is zero-extended from one byte.
2. GetDC with current HWND702A1C; publish DC000. Reload font004 for
   SelectObject, and publish its returned original-font handle at008.
3. Call GetTextMetricsA with a real ANSI metric buffer. Copy tmAscent to13C.
   No success branch or source-added metric initialization occurs.
4. Set cursor134/138 from origin124/128 plus the **full unsigned byte11D**.
   It is not converted to a Boolean offset. Clear flags16C/16D and publish the
   base-color pointer158 into active154, before any list payload release.
5. While native list15C is nonempty, delete the front unsigned array and pop
   the front node. Both checked front/pop guards and native link/count writes
   remain genuine STL behavior.

Neither CreateFontA nor metrics failure introduces an early return in the
target. The source retains that sequence without manufacturing error handling.
Original full font class, spelling and TU are unknown. The prefix now names
only observed GDI/style/position/list/flag fields through16D.

The256-byte face slot is corroborated by the independent exact network-result
caller44DCB0: raw44DD04 pushes capacity256 for strcpy_s at44DD58, then44DDCA
calls configure4115A0. Raw4115AF..B7 copies0x128 bytes into owner+00C. Existing
count/duration/mode labels in other source views are working names; the begin
API independently proves height/weight/origin use at these physical offsets.
This checkpoint does not rename or reselect those accepted consumers.

## SDK and native layout corroboration

PE import descriptors, actual FF15 operands and initial IAT words independently
establish the newly appended bindings:

| IAT | Original import | Initial bytes |
| --- | --- | --- |
| 6C0014 | GDI32.dll!CreateFontA | 265d2e00 |
| 6C0240 | USER32.dll!GetDC | aa5c2e00 |
| 6C0000 | GDI32.dll!GetTextMetricsA | 345d2e00 |

The pinned x86 SDK's `WinGDI.h` defines TEXTMETRICA as eleven LONG fields and
nine BYTE fields, size56, with tmAscent at+4. Source uses that layout and LONG
widths. The initial int-to-SDK-LONG correction is byte-neutral for all three
complete source functions; it is not an alignment trick.

The native list's initial word was incorrectly called a debug proxy in earlier
notes. The pinned release `_Container_base` is empty. A separate compile-only
witness verifies the node/pointer/value allocator subobjects at list+0/+1/+2
and sizeof(list)=12. Sentinel/count are at+4/+8. Raw constructor411430 also
initializes160/164 without zeroing15C. The correct description is allocator
storage at15C, sentinel160, count164. Source already uses real `std::list`;
this corrects the interpretation without changing accepted container code.

## Complete compiler results

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
# Expected exit1: three complete nonexact comparisons, no blocked relocation.
```

Selected source SHA256:
`57ac98ceaf7a6d81a0ba42419f92e3de6b2909be5dd5e41b1cf7bce035b5263e`.

| Complete source | Bytes / instructions | Canonical SHA prefix | First mismatch |
| --- | --- | --- | --- |
| begin4119A0 | 291 / 84 | 728a7bf3 | +7 |
| end411AD0 | 168 / 49 | e1daa198 | +7 |
| text412670 | 322 / 115 | 7087f023 | +0 |

Begin source has a56-byte local metric frame; target reserves64 bytes and saves
EDI before GDI work. Source saves EDI only for a nonempty list and jumps over
six bytes of loop alignment. Target's alignment LEA falls through. The entire
native list loop411A60..411ABD agrees, but these frame/save/alignment differences
remain significant. No dummy local, forced metric size/alignment, padding or
register attribute is added. The private source begin's unreachable alignment
also needs proper source-extent qualification before any strict linked selection.

End's complete canonical bytes are unchanged. The actual caller shrinks324 to
322 bytes when the genuine begin also supplies ESI; it still lacks the target
aligned EBP frame and other private providers. This is measured compiler context,
not exact acceptance or a proof that standalone recovery is impossible.

Both affected nonaccepted font and texture units are rebuilt. Texture wrapper
and backend remain110/264, canonical50731d79/15555b85, nonexact+7/+0. Explicit
binding, transitive-source and native COFF-symbol scans find zero accepted
consumers of the changed prefix/context or three added API names. No unrelated
or aggregate cold replay is claimed.

## Bounded execution evidence

The native begin harness executes complete target/source instructions, including
their actual list operations and field writes. Only CRT/GDI boundaries have
explicit observers. All **4,320 cases pass** across valid lists0/1/2/4/8/32,
outline bytes0/1/2/127/255, three metric ascents/style/origin sets, four API result
patterns, null payloads and optional callback mutations. It checks all14 font
arguments, handle and field reloads, full-byte coordinate offset, flag/base-color
publication order, native list releases/rewiring, final bytes, ESP and preserved
registers. The observer always writes all56 metric bytes, even when returning0;
this does not cover failure with unwritten metric memory or real GDI execution.
Coordinate inputs avoid signed overflow; arbitrary malformed lists and stack
read/write-footprint equality are not claimed.

Two genuine compiled C++ controls detect regressions. Booleanizing the outline
fails all4320 ordered traces, including3456 final font-state differences; other
cases still expose changed publication order. Moving active-color publication
after list cleanup fails3600 nonempty-list traces, even though final bytes agree.
These distinguish intermediate callback-visible state from final-only agreement.

The new322-byte caller separately passes all **13,100** existing logical observer
cases with both actual ESI begin/end entry contracts. Its expected trace digest
remainsc75c54eb. This models provider boundaries, unlike the separate native begin
run; no complete font/GDI runtime claim follows.

Full raw/import/config-caller facts, native layout witness, controls and formal/
execution receipts are under `build/font-begin-20261021/`; private recipes are
under `.analysis/font-begin-20261021/`. Completed controls are compressed only
after per-file SHA256 readback: 117,804 ->24,186 bytes. Selected
source/header/object/receipts remain.

```bash
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next: real owner/config construction and glyph/markup/blend provider closure,
then measure genuine closed-TU/link context for the remaining frame/save scope.
Do not force extra stack storage or repeat neutral compiler-version controls.
