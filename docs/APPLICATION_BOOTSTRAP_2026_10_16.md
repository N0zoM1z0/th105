# Application bootstrap and its private helper island

## Target observations

All observations use original Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh raw CFG reconciliation reaches every byte of all four callables, with
no overlapping decode, gaps, indirect jumps or outgoing direct branches:

| Entry | Instructions | Target bytes | Returns | Canonical VC8 result |
| --- | ---: | ---: | ---: | --- |
| `Application_initialize @ 407DA0` | 164 | 472 | 2 | 447/472, first difference +2 |
| `Application_initialize_window_paths @ 40D020` | 36 | 137 | 1 | **137/137 exact** |
| `Application_initialize_graphics @ 4147E0` | 180 | 547 | 4 | 539/547, first difference +0 |
| `Application_initialize_audio @ 418670` | 174 | 583 | 6 | 561/583, first difference +2 |

The last column gives complete candidate/target extents, not a percentage of
matching bytes. Only the path helper receives an exact row. Body SHA-256s:

```text
407DA0 0bd28b47c79d27772dbb6171f55da61f1d00b14543177d6735b7813ac7e65119
40D020 8ad374e1fdcf4e398b4e5720d15454f27435bd3ae2d4f48580c517279788dae3
4147E0 655ebd37d76ed149f0f37f6c82ca0b1428763e2ee3aa71e6db8533455564f5ae
418670 32326c72192f86557516f3f1e32b2ca738cf97e8ff35c0f27d0121e1ece7504e
```

Source-present WinMain calls the root at `665A6A`, passing application singleton
`702820` in ECX and the 40-byte startup value on the stack. Raw incoming E8
searches find only the root's `407E12`, `407E43` and `407EBE` calls to the three
helpers, respectively; no aligned .rdata/.data helper pointers were found.
These observations support testing a closed TU; they do not prove the original
source partition or exclude computed references.

## Behavior and source selection

The root copies ten option dwords into application+8, publishes window/instance,
normalizes option byte+27 into global `7028D8`, and selects manager/fade callbacks.
It starts the one-millisecond timer period, seeds MT19937 from timeGetTime,
checks CoInitialize, initializes window paths, and optionally hides the cursor.
After setting running+4C it applies the graphics, input, audio and IME gates.
Graphics/control/scene thread owners use eight-byte handle/id records at
application+58/+50/+6C and the existing exact wait helper `414640`. The graphics
and scene threads get priority -15; the control thread has no priority call.
The manager/fade initialization and manager vslot+10 scene creation follow the
observed current/previous scene zeroing order and initial-state stores.

The path helper publishes HWND `702A1C` and instance `702A20`. Its real
260-byte module-path buffer uses GetModuleFileNameA, searches for '/' and then
'\\', retains the last separator by writing last[1]=0, and copies with
strcpy_s to `702918`, capacity260. The target does not guard the result after
the second separator search. The source preserves that observed behavior.

Graphics initialization saves GWL_STYLE at `703840`, obtains Direct3D9 and the
adapter display mode, and zeroes the 56-byte presentation record. If either
requested dimension is nonpositive, it zeroes a real 60-byte WINDOWINFO and
uses its client rectangle. The target does not set cbSize after zeroing.
Presentation settings include one back buffer, windowed mode, automatic depth
stencil format75, flags2 and interval1 or `80000000`. Device creation tries
HAL/flags44, HAL/flags24, then REF/flags24. Success fills 304-byte caps, obtains
swap chain0 and clears color/depth. Failure messages and titles are pinned to
the actual Shift-JIS strings.

Audio initialization creates and initializes DirectSound8, tries cooperative
level2 then1, obtains native 96-byte capabilities, and creates a primary buffer
from a real 36-byte descriptor. Option bit0 enables flag16 and listener
QueryInterface; listener success also AddRefs the primary buffer. Play uses
flags1. The source reloads the global owner after COM calls, matching target
storage lifetime observations. GUIDs and error strings are independently pinned.

`src/platform/ApplicationBootstrap.cpp` keeps the root and all three complete
static helpers together. Ordinary `static __stdcall` helper definitions allow
VC8 to choose private register conventions naturally; there is no external
thiscall facade for a free helper. Narrow COM views and native API-written
records preserve actual slots and widths. Unobserved application fields remain
opaque; the accessed prefix is not a complete-class size claim. Existing shared
headers and compiler flags are unchanged.

## ABI, accepted result and remaining unknowns

| Entry | Observed target arguments | Stack purge |
| --- | --- | ---: |
| `407DA0` | ECX receiver; options pointer on stack | 4 |
| `40D020` | ECX instance; HWND on stack | 4 |
| `4147E0` | EAX width; ESI HWND; height and byte sync on stack | 8 |
| `418670` | ECX HWND; flags on stack | 4 |

The complete path helper's naturally optimized ABI and all137 bytes match,
including its 264-byte GS frame. All REL32/DIR32 relocations replay under the
formal manifest; complete target and complete COFF section tail have the same
SHA-256 shown above. A new bootstrap-only backend alias allows precisely its
observed field addends; earlier accepted backend mappings are unchanged.

The root still uses EBP as receiver in the candidate, whereas the target has an
eight-byte-aligned frame and EBX receiver. Graphics retains HWND in ESI but the
candidate passes width in ECX, sync in AL and only height on the stack/RET4;
the target additionally has a 16-byte-aligned 72-byte frame. Audio's candidate
passes flags in ECX and HWND in EDI/RET0, and reserves136 GS bytes versus the
target140. Keep those caller/callee codegen differences explicit.

A single diagnostic /GL /GS compilation and two serial LTCG links, exported
versus retained-only, preserved the three nonexact entries. Both audio probes
reserved140 bytes, but through an eight-byte-aligned EBP frame absent from the
target, and retained the wrong private argument assignment. This establishes
that compiler phase can change frame reservation without changing real locals;
it neither reproduces the target nor proves an LTCG-only obstacle. The linked
DLLs had unresolved references, were inspected only, and were never executed
or accepted. Original TU visibility, argument optimization and frame ownership
remain unknown. Do not add padding, inflated buffers or forced registers.

## Reproduction and durable state

```bash
python3 scripts/audit-candidate-boundaries.py 0x00407DA0 0x0040D020 0x004147E0 0x00418670 --json
python3 scripts/build.py --unit cross-v106a-application-bootstrap --json
python3 scripts/compare-unit-object.py cross-v106a-application-bootstrap build/match-units/CrossV106a_ApplicationBootstrap.obj --json
python3 scripts/compare-unit-object.py cross-v106a-application-bootstrap build/match-units/CrossV106a_ApplicationBootstrap.obj --address 0x0040D020 --json
```

The complete comparison intentionally reports three mismatches. The final
selected comparison succeeds. Fresh reports are
`build/application-bootstrap-formal.json`,
`build/application-bootstrap-window-formal.json` and
`build/application-bootstrap-boundaries.json`.
Four source selections and durable names are recorded. The three nonexact
roots have an independent authored-origin rule with body hashes, checked
incoming/outgoing edges and data operands; the exact helper uses the canonical
baseline. Only these four origin rows change. Existing fingerprint inputs and
rules are checked unchanged and preserved without recompiling unrelated
library anchors or replaying every exact unit.

Sequential direct Ghidra sessions independently attest executable/program SHA,
image base, entry/external entry marker, x86 Windows identity and every mapped
.text byte before saving all four names, extents and parameter storage. Normal
thiscall is used only for the root; private helper storage is explicit and
custom. Same-session readback and a fresh read-only session verify names,
sizes, purges, storage and complete body hashes. Scripts stay under
`.analysis/application-bootstrap-20261016/ghidra-scripts/`; logs are
`build/application-bootstrap-ghidra-*.log`. Each process uses a 768MiB heap and
two active processors. The unattested IDA session is not used for analysis.
