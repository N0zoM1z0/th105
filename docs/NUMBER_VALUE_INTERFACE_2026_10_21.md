# CNumber value adapter interface

`TNumberValue<int*>`'s integer getter at **0x4424B0** and floating getter at
**0x4424C0** are complete **6/6 canonical exact** functions. The real
`CMenuConnect` constructor naturally emits both template methods; its existing
728-byte match remains exact. This adds two functions and 12 accepted bytes.

## Target observations

Only the original Japanese 1.06a PE is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA attestation still rejects the open database, so these are raw PE facts.

Vtable 6C1BC0 points to 4424B0 and 4424C0 in its first two slots. Its preceding
COL pointer is 6D8234. The COL names type descriptor 6E6C38,
`.?AV?$TNumberValue@PAH@@`, and hierarchy descriptor 6D8248. The hierarchy's
two base descriptors, 6D8264 and 6D8218, identify the complete template and
`.?AUINumberValue@@`. Their displacement records establish the nonvirtual,
zero-offset base. This is game-owned value binding, also published by the
accepted CMenuConnect constructor, rather than a library identification from
a short instruction pattern.

The complete getter bodies are three instructions each:

| Entry | Operations | Result | SHA256 |
| --- | --- | --- | --- |
|4424B0|load bound pointer from ECX+4; load its int; RET|EAX|`cc0c36569e9d714e268b514bb0b8b8c3be99f2d10b6a9d6330d43d40b31fda68`|
|4424C0|load bound pointer from ECX+4; FILD its int; RET|x87 ST0|`7fed2494da422656429cca334abcd3853e6dc0ba042a8fc78be36a005a8aa9f0`|

Each RET is followed by ten INT3 bytes before the next aligned entry. There
are no branches, calls, relocations or additional owned tails. The six-byte
ledger candidates agree with complete target and COFF extents.

Consumer 414EB0 calls slot 0 for integer rendering and slot 4 for floating
rendering. It prepares the later renderer's arguments before the virtual call;
the getter itself takes no stack arguments. The floating result is stored to
a four-byte outgoing argument. CNumber's accepted lifetime releases the
adapter directly through operator delete, without invoking either slot as a
destructor.

## Source correction and limits

`src/ui/CNumberRuntime.hpp` replaces the old destructor/unknown-slot placeholder
with the RTTI-backed INumberValue base and two actual value getters, and gives
the owned pointer its interface type. TNumberValue retains its eight-byte
layout and the genuine bind_value allocation path. The ordinary template
definitions are emitted by `src/ui/MenuConnectConstructorRuntime.cpp` without
synthetic calls or explicit instantiation.

The floating getter uses a float source view. Its six bytes also permit a
nominal double return; the observed ST0-to-dword consumer supports the selected
view but does not uniquely recover the original declaration. Method names,
namespace spelling and original translation-unit partition remain inferred.
No RTTI or data-section exact claim is made.

## Focused reproduction

Run sequentially, on CPU 0 at nice 10:

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-menu-connect-constructor-runtime --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-cnumber-runtime --compare --json
```

The first command reports **728/728, 6/6, 6/6 exact** under the existing VC8
SP1 O2 /GS profile. The second retains **312/312 exact** at 414F10 and the
previous **102/104 nonexact** initializer at 414E40; its exit status 1 is the
known initializer mismatch. Both source consumers of the changed header were
replayed, and their old comparisons are unchanged. The separate lifetime view
does not include this header. No unrelated or aggregate replay is claimed.

| Selected input/output | SHA256 |
| --- | --- |
|CNumberRuntime.hpp|`05504d384d3bf6aa24e32a93d5fad78ec7af6bff4ce0acfd7be042ed1f8a8d12`|
|MenuConnectConstructorRuntime.cpp|`a2c46066a8cb784c55029f6bf3b5d5b6d5ab6939d91e85ddea9dadeba73c1334`|
|Formal constructor COFF|`ab18d5ef24e795b6f35e788d6c6ca147ef6066181cb4713224043988771f6bb2`|
|Canonical constructor body|`24eabb7746a05f06b724d86aad8273907d616ddad3d4aadd14c989f28d5b360d`|
|Canonical integer renderer|`81e97825bba4e4de5c56b2873015ddf9f600f9ef64b9498822873213251f2d66`|

Private receipts are in `build/design-number-render-20261021/`:
`adapter-target.json`, `formal-build.json`, `number-baseline.json`,
`number-affected.json` and `acceptance-delta.json`. The latter confirms all
196 origin-rule selections are unchanged and exclude the two newly accepted
candidates; only their official canonical-exact authored baseline rows change.
No complete origin-anchor replay was needed.

CDesignNumber's outer renderers 40AF80/40AFC0 and private dispatch/floating
helpers 414EB0/415050 were unselected at this interface checkpoint. The
subsequent [render recovery](DESIGN_NUMBER_RENDER_2026_10_21.md) accepts the
outer renderers and dispatch with complete private helper visibility; the
floating renderer remains nonexact. ReimuObject 496540 remains nonexact at
49655F/+31.
