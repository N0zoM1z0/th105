# Constant-one list growth: generated-code origin

The entire 154-byte 0x40C6D0 function is the VC8 LTCG constant-one
`std::list<BgmHandleResult>::_Incsize` specialization. It is generated STL,
not an additional authored game function. Its native whole-body SHA256 is
`53f43d6b94ee4409ec6f29a8b9a66da8eb0a3afd5c713792587c11e82778fd1f`.

## Real owner and complete root

The exact 351-byte BGM play function 0x4036E0 calls this helper three times, at
0x403787, 0x4037E2 and 0x40381D. The existing pinned static-CIL BGM source graph
naturally emits the typed helper, without an exported helper, fake ABI, source
barrier or copied target instructions. A fresh rebuild must retain all three
accepted roots in the unit: BGM play, its independently qualified prepare
body and PCM routine. The actual emitted BGM parent calls its own `_Incsize`
at the corresponding three offsets.

The complete closed source and target function match after only identified
address-role replay: three named calls, EH handler, security cookie, exact
`list<T> too long` literal, actual length_error ThrowInfo and RTTI vtable.
Every other byte is significant; nothing is masked. Full body uniqueness is
checked across the entire same-size candidate inventory, not only review rows.
The exact source graph, source dependencies, four relevant VC8 headers, target,
compiler profile and static runtime are pinned.

## Exception and supporting evidence

The complete27-byte handler, 8-byte cleanup action, 36-byte FuncInfo and
8-byte unwind map are compared, including each actual relocation role. The
length_error ThrowInfo, three-catchable-type array and full length_error,
logic_error and exception descriptors, sizes and copy pointers are checked
against the target. The actual named RTTI and full literal are verified.
Both logic_error constructors and their complete exception metadata are replayed;
the 50-byte length_error destructor, 25-byte copy constructor, 38-byte string
destructor and noncontinuable CxxThrowException witness are independently
compared. These support records receive no new authored or exact credit.

## Validation and accounting

`linked-bgm-list-growth-106a` selects only 0x40C6D0 through its strict anchor and
freshly rebuilds the existing exact BGM unit. The scoped validator checks the
complete root, all actual call/data references, parent edges, metadata and
full-inventory uniqueness. Five contract tests plus target root, handler, unwind,
ThrowInfo and literal corruption controls reject their respective mutations. A full
global origin replay is not claimed.

Only one origin row moves review → compiler-generated exclusion: review293,
excluded2078. Exact1426 /443399 bytes, authored1656, source1637, mapped1827,
units814 and candidates4027 stay unchanged. Other list specializations are not
classified by this single-body proof.
