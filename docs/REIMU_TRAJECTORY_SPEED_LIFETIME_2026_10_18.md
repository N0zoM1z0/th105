# Reimu: recover the shared trajectory-speed lifetime

The staged520..523 source now reuses one real float for the near and far
request pairs. The resulting root changes only24 FLD/FSTP displacement bytes,
moving those values into the target's stack slot. All other82892 canonical
candidate bytes stay identical. Callable/metadata fit and frame570h remain;
the complete root is still nonexact at+541.

## Observed target and staged source change

Target is Japanese TH10.5 v1.06a, SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Root478FA0 owns `[478FA0,48CE2E)`,81550 bytes, SHA-256
`dbf6f375a809fea91cbbccf0f8cff2196f40cba11458c98e475a290b623053e6`.
The rejected IDA session supplies no semantics. This work uses raw attested
PE, complete ordinary relocation replay and real native callbacks.

Qualified CFG/ESP propagation locates the preceding candidate's speed at20h
and the target's at24h, relative to ESP after the complete aligned prologue. Both target
near/far calculations use that same m32 slot across the respective returning
requests. Coordinate scratch remains at14h; raw `[ESP+disp]` text alone would
confuse these offsets because argument pushes change ESP.

`src/characters/ReimuActionStateMid520Cases.hpp` replaces the two separate
`const float near_speed/far_speed` locals with mutable `float shot_speed`.
It initializes the near value, consumes it twice, then assigns and consumes
the far value twice. Helper calls, calculation order, rounding, parameter
arrays, input reloads and all requests remain in their existing order.
Every value is consumed by a real request. No padding, inert local, assembly,
new helper, layout, ABI, compiler flag or binding change is introduced.

**Inference:** one reused source variable explains the observed physical
lifetime and produces the required slot. Original variable names/spelling
are not proved. The address/name/source-present/exact ledgers stay unchanged;
the root remains authored/unclassified/declaration-only.

## Complete current candidate verification

The genuine current ordinary object SHA-256 is
`0a950c1fec476022ed45c663d529902c1b0393d679aa29d26d48a4f967d46c3c`.
Prefix81544/payload82916/frame570h retain strict fit. The complete linked and
ordinary canonical payloads agree, SHA-256
`9cdc589ffda90ef1828616df337228363291abe7e1487f781b7560d6c08e6766`.
All2464 relocation fields/1281 HIGHLOWs,11 switches,15 request-buffer contracts
and preparation contracts qualify; the12-byte linker gap remains separate.
No diagnostic DLL is executed.

Comparison with the preceding canonical payload `a6dc1ccf...` proves exactly
24 one-byte ESP displacement changes, all in m32 FLD/FSTP operands and all+4.
The complete remaining82892 bytes, including branch/call fields and switch
metadata, are unchanged. New first difference remains+541/4791BD, the same
JNE displacement. Current full128-action/32-callee census retains eight
partition differences and zero per-action callee-count differences.

A private ordinary object from exactly the new generated C++ passes all320
complete five-request inputs:1600 real815 objects per process, actual manager
construction/copy/callbacks/root RET/destruction and an independent target
repeat. All3678724 snapshot bytes agree, SHA-256
`f9630d9758d2f36018d17f26867b475e5709d711ae25cdfe9a203536f28ecd41`.
The current producer then proves identical generated-source/header/tool pins
and all82916 canonical bytes against this already executed object. This avoids
repeating the identical full-return run after promotion. Fresh current-object
focused native checks also pass0/1888, with no buffer/preparation mismatch.
These preserve their existing request-entry/helper/RET boundaries.

```sh
nice -n 10 taskset -c 0 python3 -B scripts/probe-reimu-action-ltcg.py
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-root-stack.py build/reimu-ltcg/ordinary.obj --action 520 --action 521 --action 522 --action 523 --require-partitions --native
nice -n 10 taskset -c 0 python3 -B scripts/audit-reimu-call-sharing.py build/reimu-ltcg/ordinary.obj
```

Use `audit-reimu-trajectory-returns.py` to regenerate the complete returning
comparison. No historical full matrix or aggregate cold replay is claimed.

## Coupled full-width control and remaining exits

The preceding full-width direction control becomes more informative with this
speed lifetime. Its complete physical520/521 spans,881/794 bytes, now have
identical encoded instructions and owner-relative branch identities under the
existing owner diagnostic. All registers, widths, literals and virtual-call
encodings remain significant. This is diagnostic equality of physical spans,
not canonical matching credit for part of a function.

That control still has prefix81688/payload83060/frame570h and canonical SHA-256
`b59f170344a18ea7187efc9975d3f5774a641e634ce5fa6a2ec836da33235410`.
Its known complete owned243/wave77 sharing partitions remain the positive
direction evidence; six callees still differ from the target. It is exactly
the current generated source plus twenty fresh full-width direction captures.
It exceeds138/136 and is not executed or selected.522 contains an extra local
landing tail and advancement exit;523's remaining differences concern the
destinations of those shared exits.

Focused controls keep the same genuine helpers and ordinary flags:

| Control | Prefix / payload | Decoded E8 / RET | Disposition |
| --- | --- | --- | --- |
|Full-width, reused speed|81688 /83060|1181 /152|Over138/136|
|Full-width, RTM42 core, same SP1 headers, preceding separate speeds|81732 /83104|1181 /152|Over182/180|
|127 terminal case breaks, real region returns, reused speed|81624 /82996|1176 /149|Over74/72|
|Terminal breaks plus one real common-action fallback|81640 /83012|1180 /150|Over90/88|

The RTM control tests changed full-width input, not an unchanged-input repeat
or original patch-level identification. Terminal breaks retain conditional
early returns and defaults. The final control routes only actual defaults to
one end-of-function common call; handled high cases return before it. Neither
uses fake results or dead control flow. Shorter code alone does not establish
the target's sharing. These counts are complete decoded-prefix observations,
not reachability proofs. Every oversized control stays read-only.

Local recipes, receipts, complete deltas and owner/ESP packets are retained
below `build/reimu-direction-lifetimes/`. Keep the genuine current cache and
the useful full-width/reused-speed diagnostic; duplicate rejected products
and native streams are disposable. All9 primary database hashes remain
unchanged. Serial CPU0/nice10 jobs peak at321144KiB for producer refresh and
307672KiB for the complete-return check. Uninitialized740 paths, other runtime
contexts, original source/visibility and full root equality remain unknown.
Continue from522/523's shared exits while preserving the recovered speed slot;
do not repeat these unchanged controls or promote span diagnostics to matches.
