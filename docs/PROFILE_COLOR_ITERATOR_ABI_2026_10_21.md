# Profile render-list color iterator ABI

40BFE0 remains **74/81, nonexact at+0**. The source now asserts the actual
checked-iterator size/alignment, without changing any generated callable byte.
The older explanation that there is no eight-byte source local is incorrect:
the existing iterator is eight bytes, aligned to four. Its size alone does not
explain the target's eight-byte ESP alignment. No new exact is recorded.

## Observed target

Only original Japanese TH10.5 v1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh target/tracking checks pass; IDA rejects10350095... and supplies no
semantics. No Ghidra process, metadata write or target patch is used.

The complete81-byte body40BFE0..40C031 contains36 instructions, one RET4
at40C02E and fifteen following INT3 bytes. The receiver is ECX; the incoming
color word is read at EBP+8. The existing list view starts at receiver+14,
with its head at+18. Nodes use next+0 and payload pointer+8. Each payload is
called through vslot+4 with the color word; source void is an inferred view.

Loop40BFF2 reloads the current end/head pointer every iteration. The checked
owner comparison and checks before dereference/increment call68A143. The
virtual callback precedes increment validation. These are concrete traversal
constraints, not evidence of arbitrary callback/list-mutation coverage.
Raw direct calls43F951 and4401DB lie in already accepted43F900/440170 owners;
their acceptance is retained ledger evidence, not a fresh caller replay.
Target body SHA256:
`fc4ce6e449091bf4552ac4c93e8a3ab1e53b2c993af32ccfdbe2a2b7fc77a961`.

Target prologue PUSH EBP/MOV EBP,ESP/AND ESP,-8/PUSH ECX remains unexplained.
The source's74-byte body instead holds the color in EBP. Original source,
iteration spelling and TU/compiler context remain open; the frame difference
does not prove a standalone or LTCG impossibility.

## Compiler-emitted layout witness and guards

A private COFF data witness evaluates the actual pinned VC8 source types:

| Source type fact | Value |
| --- | ---: |
| sizeof checked iterator | 8 |
| __alignof checked iterator | 4 |
| sizeof container | 12 |

These are compiler-emitted constant data, not host-model guesses or new target
stack storage. The current source already declares that iterator. Two public
compile-time assertions now guard its8-byte size and4-byte alignment, alongside
the existing list-offset assertion. They allocate no object and do not request
alignment. No field, method ABI, shared header, flag or binding is changed.

The guards preserve the entire74-byte canonical source body:
`5bb8ba6193c21ed6485a6219048e0650a0a4bc248b218f3e13e3d5713fe3604d`.
Selected CRLF source SHA256:
`54bcd029b0af977013bbb24cb8b028d957e1de886fbed89633df7b0a66461f2f`.
Frozen formal COFF SHA256:
`56a6d0839698bcc26cf82afda684efe6a68c64ea35369f461d32a657aec50c4a`.
The existing ordinary SP1 O2/GS-off profile remains selected.

## Bounded controls

| Private control | Complete result |
| --- | --- |
| Postincrement instead of preincrement | Identical74-byte body |
| /arch:SSE2 | Identical74-byte body |
| /GS | Identical74-byte body |
| VC8 RTM | Identical74-byte body |
| /Z7 | Identical74-byte body |
| const_iterator with the mutable container | 87 bytes; nonexact+0 |
| std::for_each/bind2nd/mem_fun | Unrelocated39-byte body; comparison blocked on a generated virtual-call thunk |

A separate COFF macro witness reports `_M_IX86_FP=2` with the SSE2 option,
confirming that it took effect. The Z7 object contains both .debug$S and
.debug$T. Neither option explains this frame in the tested source. These are
bounded results, not transferable compiler rules or a flag-combination search.

The const-iterator whole87-byte canonical SHA256 is
`cb47dfb7b7d0d359fc64ba6f85aa982edef0fa342b6c0eaae3c678ecffc66de9`;
the standard comparator's hash covers only its81-byte compared prefix.
Do not describe that prefix hash as the complete87-byte function.

The algorithm control caches an end node and bypasses the original checked-
iterator call pattern. Its generated local virtual-call thunk has no qualified
target binding; no address is invented to obtain a canonical result. The39-byte
figure is unrelocated COFF structure, not target equality. No control is selected
and no numerical/native regression coverage is claimed for these experiments.

## Retained evidence and next boundary

`build/profile-list-color-20261021/` retains baseline, selected formal object,
private controls, COFF layout witnesses and `facts-summary.json`. Private
recipes are in the same-named `.analysis/` directory. The source guards alone
change the selected program source; implementation bytes remain unchanged.
40C040/40C0A0 sibling frame observations retain their earlier epochs and are
not promoted or freshly replayed by this40BFE0 work.

The preceding4A1CE0 initializer was also freshly rebuilt:4892 callable bytes,
14 differences,548 equal metadata bytes and first4A2E20. Its discarded-result
and parameter-snapshot trials duplicate controls already recorded on the same
3803a002 source; they are explicitly classified as revalidation, not independent
new evidence. Its selected source and all acceptance rows remain unchanged.
The two duplicate initializer owner graphs are SHA-checked/gzip-compressed;
`revalidation-compression.json` records each readback. Frozen source/COFF/
canonical inputs and comparison receipts remain; restore the `.gz` reports
before old private recipes. No aggregate cold replay or new aggregate
percentage is claimed.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-profile-render-list-color-runtime --compare --json
# Expected exit1:74/81, first difference40BFE0.
```
