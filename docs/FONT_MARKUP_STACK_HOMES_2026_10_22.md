# Markup stack homes and genuine member-context controls

This follows [the earlier lifetime traces](FONT_MARKUP_FRAME_LIFETIMES_2026_10_22.md)
at `411FA0`, using only the attested Japanese1.06a PE. The target/status/tracking
preflights pass; the wrong IDA image is rejected. No markup source, owner size,
compiler profile, ABI facade or exact credit is selected by these controls.
The real-caller investigation separately yields the selected
[packed input correction](TEXT_FONT_PACKED_INPUT_2026_10_22.md) at412670.

## Complete normal stack flow

The fresh native baseline is the preceding b88ed013 source epoch: target main
1744 bytes /463 reachable instructions, source1728 /455, canonicala3c2e09c,
first difference+16, reserved local frames796 versus788 bytes. Both complete
normal CFGs are closed. A new all-path ESP analysis follows every normal edge
and enforces identical stack depth at each join and balanced ESP at RET8.
Twenty-six direct callee cleanup contracts are inspected through normal target
branch/RET surfaces. Those cleanup contracts are used for source flow as well;
this is not a full execution proof for every library callee or exception path.

The fixed frame after saved registers/cookie is entry-SP minus33C/target and
334/source. Offsets below are hexadecimal relative to that fixed frame.

| Observed home / address | Target | Native source |
| --- | ---: | ---: |
| Token allocation base; later ruby text pointer |18|14|
| Native deque receiver |1C|18|
| Tokenizer context |30|38|
| Width output shadow |34|30|
| Height output shadow |38|2C|
| Persistent length/count |3C original payload|34 consumed count|
| Temporary string receiver |44|40|
| Ruby config receiver |64|60|
| Ruby owner receiver |18C|188|
| Delimiter array |324|31C|
| Upper GS cookie |32C|324|

Target14..17 and320..323 have **no direct normal-main ESP references**.
This locates the two four-byte gaps rather than calling them missing variables.
It does not prove that arbitrary indirect callees or exception machinery cannot
access them. The saved registers/cookie occupy the preceding fixed-frame words;
the first gap is not a hidden direct read/write found by the audit.

The target also reuses tokenizer-context home30 for a color byte, while source
reuses former buffer home14. Both reuse their output homes for later color
bytes. These are different actual live-home allocations, not extra logical
color parameters or evidence for padding the font type.

Fresh target/source EH facts retain four states with to-state graph
`[-1,0,1,0]`: deque, temporary string, placement delete and local font owner.
The source's cleanup displacements remain four bytes closer to the entry frame
than target's corresponding object references. Handler/metadata byte equality
and actual unwinding are not claimed. The earlier independent0x194 owner-to-
cookie placements remain a separate constraint on enlarging the shared type.

## Library and ownership controls

The installed alternate header tree contains real differences in xstring's
copy-constructor/base initialization and in xutility/yvals, while deque/xmemory
are identical. The complete tree is hashed before a private compile. With the
same SP1 compiler and SDK, changing only these CRT/STL headers reproduces all12
baseline font canonical hashes/extents, including the original markup frame. The local
directory label does not prove the original game's header release/provenance.

Two further pre-correction-source controls use the ordinary pinned profile:

| Control | Markup result |
| --- | --- |
| Direct calls to the same array allocation/release functions for raw char storage |1728, complete canonical hash unchanged|
| Explicit `std::string(token,strlen(token))` constructor |1714, still frame788 and nonexact+16; other11 bodies unchanged|

Neither control is selected or presented as a broad runtime qualification.
Shorter code and equivalent token values do not recover the target stack homes.

## Genuine whole-font member context

Private copies of the pre-correction owner/header/render source are compiled together
under O2/Ob1/GL/GS. One variant keeps the real file-local parser; another adds a
normal parser member declaration/definition and updates its actual render call.
No class data/vptr/layout changes and no custom register convention are made.
Pinned import-runtime libraries and attested external data/IAT bindings resolve
both images; no executable ABS provider is used. The renderer is the sole
initial export, and both complete markup normal CFGs close.

The pair emits byte-identical1554-byte /408-reachable-instruction markup bodies,
both still reserving788 bytes and returning RET8. However, actual caller/value
inspection distinguishes this context from target: CIL chooses **EDX cursor**,
ECX height output, and font/width on the stack. Target uses **EDX font**, ECX
height output, and cursor/width on the stack. Equal cleanup/register counts
therefore do not establish the target's private interface.

The same CIL inputs are then relinked while retaining the observed ordinary
owner constructor/destructor/configure/config-constructor interfaces. Both
variants again have byte-identical1554-byte parser bodies with the same wrong
argument roles and788-byte frame. Each real owner operation is actually called
once by markup; available owner body sizes are138/210/439/67. Those sizes alone
are not a new canonical provider comparison. Neither image is executed and no
parent/EH exactness claim is made. The selected packed-input caller correction
also leaves that tested CIL parser size/frame unchanged.

## Evidence and next constraints

Private recipes are in `.analysis/font-markup-homes-20261022/`; receipts are in
the matching `build/` directory: `baseline-formal.json`, `baseline-facts.json`,
`target-facts.json`, `stack-homes.json`, `eh-facts.json`, `rtm-header.json`,
`raw-array-storage.json`, `bounded-token.json`, `member-contexts.json` and
`public-member-contexts.json`, with exact source/tool/object/image pins and
actual caller windows. The selected input correction's `formal.json` preserves
the complete baseline markup body and its original private native interface.

The two gaps, allocation-argument cleanup, payload/count lifetime, color-home
reuse and original compilation ownership remain unexplained. These measurements
rule out the tested substitutions; they establish neither a general LTCG
requirement nor a standalone-object impossibility. Keep the native0x194/0x128
owner/configuration sizes and recover further lifetimes from actual operands.
