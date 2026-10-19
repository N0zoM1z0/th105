# Shared Object action980: complete exact recovery, 2026-10-19

`CharacterObject_continue_action_980 @ 0x00596370` is now canonical
**323/323**, using the existing `gpt-web-object-action-980` unit. This
supersedes the pending scheduling diagnosis in
[the October 2 report](OBJECT_ACTION980_COMPILER_SCHEDULING_2026_10_02.md).
The sole executable-source change is the local virtual sequence selector's
parameter declaration: `int` becomes `short`. No compiler flag, shared header,
helper definition, field layout or relocation binding changes.

## Target observations and acceptance

The target remains original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The callable is `[00596370,005964B3)`, with body SHA256
`1ae566c8e8a9230cc7ce1ff75a2b472ef0b4886b1f63786506b2735dadecd7bc`.
Fresh raw traversal reaches all82 instructions/all323 bytes, with one RET at
5964B2, no holes, no internal calls and no unresolved indirect exits. The
following13 bytes are INT3 alignment, outside the accepted callable.

The receiver enters in ECX; there are no stack arguments and RET pops none.
The seven direct calls are three68A1A0 float-to-integer conversions, three
4067D0 RNG calls and one435160 oriented-motion call. A separate virtual call
uses vslot+0C. Seven REL32 and seven DIR32 fields are fully replayed by the
canonical comparator, including the numeric literals. The origin remains
authored game code. A fresh canonical vtable/decoded-edge census finds one
JMP to this continuation from each of the fifteen Object entry candidate
spans. Reimu's edge is at4A2F8B after restoring its caller frame and preserving
ECX. These are tail transfers, correcting the old rule's description of them
as direct calls; the census does not close every caller's CFG or confer exact
credit on those roots. Its receipt is `roster-incoming-edges.json` in the build
directory below. The old authored-only rule is removed now that the origin
census obtains this function from canonical exact acceptance.

The configured baseline still failed at+21/596391. With only the local
signed-word selector declaration refined, VC8 naturally emits the target:

```text
mov ecx,esi ; push eax ; mov eax,[edi+0Ch] ; call eax
```

Both the private control and a fresh build of the selected source compare
323/323. Formal reproduction:

```bash
python3 scripts/build.py --unit gpt-web-object-action-980 --compare --json
```

The formal source SHA256 is
`aaeea10088dbb80fdf8544ce984de751839bf591a83498eceaec81ebba93fe8a`.
The formal receipt records the object/compiler/input hashes; the COFF timestamp
can change the object hash on a rebuild. Receipts are
`build/object980-short-context-20261019/formal-unit.json` and
`boundary-and-relocations.json` in the same directory. The unit, source and
accepted ledgers retain the complete reproducible result.

## What the width result establishes

The target selector consumes a word from a four-byte stack argument slot;
the recent Aya/Reimu caller work already tested a corresponding short view.
Revisiting the older action980 source with that evidence closes its entire
callable. The earlier inability to change this scheduling window was a
limitation of the tested source hypothesis, rather than proof that ordinary
COFF could not reproduce it.

This exact caller does not uniquely recover the original complete class,
source partition, or unused selector return type. Keep those unknowns separate
from the full byte equality. The refinement is local to this source; the shared
selector implementation/header and its accepted consumers are unchanged.

## Reimu root controls and remaining work

The substantial Reimu Object initializer at4A1CE0 remains nonexact: all4892
callable bytes are compared, with14 differing bytes in906/999 and all548
adjacent metadata bytes equal. Its selected source and complete canonical
5440-byte payload65298d36 remain unchanged. No partial credit is awarded.

Fresh controls cover parameter-lane structure versus float array, all short
argument casts, sequence snapshots, outer breaks, nested returns, angle
references, local selector helpers, explicit default/case1, a one-case999
switch, and reversing the source owner of the observed906/908 angle tails.
RTM, explicit precise mode and disabling intrinsics are also tested. Successful
controls preserve the selected full payload, except defining both tails in905,
which reproduces the earlier16-byte difference result. These controls are
unselected. A repeated optional-selector helper and `/Os` compile but no longer
have the expected42-destination root table; the structural exporter rejects
them and no canonical-equality claim is made for either.

Sources/scripts are under `.analysis/reimu-object-entry-source-20261019/`;
commands, compiler pins, packets and failure logs are under
`build/reimu-object-entry-source-20261019/`. Builds run serially atCPU0/nice10.
The root residual still requires an independent source/compiler-context
explanation; the successful action980 change is not a general scheduling rule.

## Saved Ghidra boundary correction

Direct Ghidra independently re-attests the imported target identity, Windows
x86 analysis target, entry68B9D2, full mapped text, and both callable hashes.
Both function entries were absent from the previous saved primary; earlier
root views were ephemeral read-only analysis. Merely supplying a4892-byte
function body did not bound the decompiler: its root p-code contained51
instruction addresses from the external596370 continuation.

A private copy first creates the two reconciled functions, each with ECX:4,
void return storage and zero stack purge. The root still has those51 external
p-code addresses. Applying a CALL_RETURN **analysis flow override** to the
already proved external tail JMP at4A2F8B reduces the count to zero. It does
not rewrite the instruction bytes. The helper's p-code also stays within its
323-byte callable. Root and helper are saved, reopened read-only, and checked
again for signature/storage/body/flow and zero external p-code addresses.
The readback project file hashes remain unchanged before promotion.

The current primary pins are
`build/object980-short-context-20261019/primary-db-after.json`; the archive
loader pins describe its predecessor. The Java script and controller are
under `.analysis/object980-short-context-20261019/`; write/readback logs and
receipts are in the corresponding build directory. An initial entry-only
attempt correctly failed the out-of-body check and was not promoted, despite
Ghidra returning zero and saving the project. Explicit success/error/readback
checks remain necessary. Decompiler text is still a hypothesis, and the
remaining indirect-call prototypes are not thereby recovered.
