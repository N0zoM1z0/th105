# DirectInput axis callback

`configure_gamepad_axis @40DB40` is canonical exact166/166 through
`exact-first-directinput-axis`, using the unchanged `InputManager.cpp` source.
The original ordinary161-byte stack-alignment stop is closed by genuine
`/O2 /GL` compilation and `/LTCG` with the pinned static CRT. The existing
24-byte property has ordinary alignment4; native eight-byte stack alignment
and20h frame arise from the compiler, not padding or source alignment.

The callback is normal stdcall(object,context), RET8. It sets a real range
property with size24, header16, object type from+18, DIPH_BYID2, minimum-1000
and maximum1000. Native checked vector.back() selects the latest gamepad and
COM vtable slot+18 performs SetProperty(DIPROP_RANGE4,&property). HRESULT>=0
becomes BOOL1, otherwise0. No extra safety or normalization behavior is added.

The new data binding covers only backend702A28+10/+14/+18: the existing vector
owner/begin/end. Each canonical zero-initialized location is verified; no old
binding is broadened. Three ordinary invalid-parameter calls are fully resolved
through the actual CRT implementation and mapped to68A143. No callback address
or code-as-data replay is required for this exported callback root. No C++ EH.

The complete target/canonical hash is
6a498e18eba190f0ac34c2f89574f5e3af6f8be2117dfac0a08d862965b6f8c4.
Fresh Factory metadata/entry, five mapped samples, inventory, disassembly,
decompilation and call-graph probes are retained in
build/frontier-directinput-cil-20261030/ida-preflight.json. The normal formal
recipe independently validates source-symbol ownership, complete CFG and all
operand relocations. No assembly, fake liveness or fabricated calling convention.

```
scripts/repo-python scripts/build.py --unit exact-first-directinput-axis --compare --json
scripts/repo-python scripts/ci.py
```

Receipt: build/frontier-directinput-cil-20261030/formal.json.
No existing source/header/compiler profile was edited. Earlier exact ordinary
input-manager receipts remain valid and are preserved. This new isolated linked
unit adds166 authored bytes; it does not accept gamepad enumeration or bootstrap.
Their real callback/checked-vector graph is the next relevant context lead.
