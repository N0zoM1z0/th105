# Profile writer4317A0: restore checked deck indexing

The retained source's operator[] was not a complete semantic reconstruction.
Native4319B7 loads the current deque size,4319B9 compares the item index, and
4319BB branches on size<=index to the terminal431AAB CALL431610. The existing
positive compiler-origin rule identifies431610 as the deque range-exception
helper; its117-byte body ends in CxxThrowException. Only after this guard come
three checked-iterator validations and element-address calculation. This is
std::deque<unsigned short>::at, not ordinary operator[].

The source now writes each deck through .at(item_index). Natural indexed for
loops over the actual twenty-deck array and each byte-sized serialized count
also recover the target initial JBE loop guard, size-field pointer carrier at
receiver+1BC, and20-byte deck progression. No raw container offsets or manual
exception path are authored. Count truncation to one byte, two34h-byte blocks,
two one-byte flags and two-byte deck entries remain as observed. This is a
restoration of existing behavior, not added defensive checking.

## Complete callable and exception lifetime

Independent native CFG reaches all261 instructions/784 bytes, including the
nonreturn terminal call. Target main SHA-256:
2cce2b6f179d22fdbe4a2e6863501072dea6be3a4600680e2c93c7e6f46f5126.
Normal return is RET4 at431AA8; INT3 follows the terminal call at431AB0.

The source has the same complete784-byte callable plus one trailing INT3 in
its785-byte COFF section. Its full section SHA-256 is
080e5d6ebbe7d352089e76729bb4cc486cbd3d4a52215861fa35a7a6f8b84682.
It remains nonexact, first+147/431833 in string-member address scheduling.
Further independent integer-register scheduling differs around destruction
and WriteFile arguments. No padding removal, opcode patch or partial credit.

The real local strings and CFileWriter retain three unwind states and /GS.
The generated40-byte handler has two security-cookie checks, FuncInfo magic
19930522/maxState3 and the normal FrameHandler3 edge. Cleanup actions take the
same EBP-relative locations (-2C,-48,-5C) as native6B80F0/6B80F8/6B8100 and
invoke the two string destructors or writer destructor. Native handler6B8108,
FuncInfo6DE338, unwind map and action bytes are independently pinned by the
existing profile-binary-writer-authored-106a origin rule. The relocation key
records the actual complete handler fingerprint; it does not author EH code.

## Focused outcomes

- Old unselected writer754/native784 lacked the range-throw semantics.
- Changing only operator[] to at produces786-byte COFF output, nonexact+147.
- Indexed nested loops produce785 bytes, including the trailing INT3, with
  native-sized callable and unchanged first residual.
- Existing cross-v106a-profile-data-writer siblings remain exact: normal
  destructor407BF0 21, write407C10 35, scalar deleting destructor407C70 45,
  normalizer431690 145.
- Writer is now positively source-selected under its existing authored origin;
  no new exact or excluded bytes. Public header/layout/other TUs are unchanged.

The ordinary comparator replays every body relocation; the raw audit separately
closes the no-return boundary and the real compiler-generated cleanup metadata.
Default CI follows final ledger/progress changes. Earlier statements that this root
had only compiler scheduling left are superseded by the observed missing range
guard.

## Adjacent reader declaration cleanup

PlayerSlotProfileLoad.cpp's local reader view previously supplied unconditional
zero-return bodies for seek/size, although this caller never invokes them. Those
unsupported bodies are now declarations only. This is generated-source equality, not
a new canonical or vtable acceptance. No reader layout, used virtual method, exact
ledger or public header changes.

## November 8: complete cleanup comparison

With the recovered global CFileWriter identity, the current emitted object now
compares equal for all 64 bytes of remote cleanup/handler code at `0x006B80F0`
and all 60 bytes of unwind/FuncInfo metadata at `0x006DE320`. The three cleanup
actions destroy the two strings at frame offsets -0x2C/-0x48 and the writer at
-0x5C. Their unwind chain is `[-1, 0, 0]`; both cookie checks, the handler's
FuncInfo pointer and its FrameHandler3 tail are included. The complete writer
destructor also matches its 21-byte native body.

The equal SHA-256 values are `b399506949614420a9de44371b6ce2e09e66974cd6a6289c7d83407c74a39aac`
for EH code and `dbc25bc35c067e5d216c56805d7b9b41403092ed7ddca0e480055545b0e6d9c7`
for metadata. This closes the earlier address/structure-only EH evidence.

The main callable remains nonexact at +147. Both complete callable graphs have
261 reachable instructions, including the terminal deque range-exception call;
all 50 call, branch and return instructions have identical locations and bytes.
The source section retains its separate trailing INT3. Inspection of the unequal
slices finds the existing string-member address scheduling and temporary integer
register allocation differences, not a missing cleanup or range-check path.
No source change is justified by that inspection alone.

The focused check verifies current compiler/source/object provenance, complete
section ownership, every EH relocation and both callable graphs. No new exact root
is recorded.

## 2026-11-14: exact

`ProfileMenuBaseData::save_to_profile` at 0x4317A0 is canonical exact, 784/784.
The guard for an empty saved name is `string_098 == ""`. VC8's `operator==` inlines
to `compare(0, size(), "", 0)`, with the literal length folded. The old explicit
call `compare(0, string_098.size(), profile_name_empty, 0)` produced the same
arguments but scheduled `lea edi, [esi+0x98]` after the literal push instead of
before it. The unit maps the `""` literal symbol `??_C@_00CNPNBAHC@?$AA@` to the
existing `_profile_name_empty` relocation at 0x6D69D6.
