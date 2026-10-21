# Texture surface dimension query 404E60

`TitleResourceManager::get_texture_size @ 0x00404E60` is canonical **148/148**
through `gpt-web-texture-size-query`. The target remains original Japanese
1.06a, SHA256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA preflight rejects the open image; all target observations below come from
the independently hash-attested PE. No database semantics or writes are used.

## Observed boundary, ABI and behavior

The existing candidate is exactly `404E60..404EF4` exclusive. All 57 decoded
instructions are reachable through its normal CFG, ending in RET12 at
`404E8B` or `404EF1`. Five preceding and twelve following INT3 bytes isolate
the body. No remote tail, jump table or alignment byte is included. Complete
target and canonical source SHA256 are both
`fb5c9084440583b332ff2425662c9f116dade8db2925ecda1583c778177e80c1`.

ECX is the receiver; the three stack words carry the handle and two output
pointers. The source uses void as an inferred view; this does not prove the
original return spelling. Actual incoming E8 witnesses include two already
accepted callers and one pending caller:

| Caller | Call site | Current caller state |
| --- | --- | --- |
| Sprite texture setup `407160` | `407183` | Accepted exact |
| Secondary animation initialization `430750` | `430878` | Accepted exact |
| Design gage initialization `41B280` | `41B2B9` | Source-present, nonexact |

Handle zero writes 256 to width and height, then returns without provider
calls. Otherwise the body enters the existing backend's critical section at
`7036A0+4`, calls the real handle lookup at `417800`, dereferences the returned
resource cell and obtains texture level zero through vslot `+48`. The returned
surface supplies its descriptor through vslot `+30`. The body publishes the
descriptor's width then height, releases the surface through vslot `+8`, and
leaves the same backend lock. It does not test the HRESULTs and has no outer
EH cleanup. Driver failure, bad handles/pointers and actual exception unwinding
are not independently execution-qualified here.

The accessed descriptor words at +18/+1C and COM positions correspond to
Direct3D9's [surface descriptor](https://learn.microsoft.com/en-us/windows/win32/direct3d9/d3dsurface-desc),
[GetSurfaceLevel](https://learn.microsoft.com/en-us/windows/win32/api/d3d9/nf-d3d9-idirect3dtexture9-getsurfacelevel)
and [GetDesc](https://learn.microsoft.com/en-us/windows/win32/api/d3d9/nf-d3d9-idirect3dsurface9-getdesc).
Microsoft's [SDK interface declarations](https://github.com/microsoft/win32metadata/blob/main/generation/WinSDK/RecompiledIdlHeaders/shared/d3d9.h)
independently corroborate the vtable prefixes. These are external API evidence,
not proof of the original SDK release, C++ names or original TU partition.

## Genuine source and compiler context

| File | Purpose |
| --- | --- |
| [TextureSizeQuery.cpp](../src/assets/TextureSizeQuery.cpp) | Complete query behavior and ordinary virtual COM calls |
| [D3DTextureQuery.hpp](../src/engine/D3DTextureQuery.hpp) | Used Direct3D9 COM prefixes and native 32-byte descriptor |
| [ResourceHandleLookupRuntime.hpp](../src/assets/ResourceHandleLookupRuntime.hpp) | Existing lookup view moved to a header without layout or body changes |
| [TextureSizeQueryUnit.cpp](../src/assets/TextureSizeQueryUnit.cpp) | Includes the one genuine lookup definition and query definition for CIL |

The ordinary COFF query is 147 bytes and differs at entry; the target starts
with an eight-byte-aligned EBP frame. The supported VC8 O2/GL/LTCG unit naturally
emits all 148 target bytes with the genuine lookup definition visible. Its
`preserve_public_members` contract retains and independently witnesses the
lookup's actual ordinary thiscall export; the query keeps its real E8 call.
No unused exact copy substitutes for the actual caller.

The formal unit uses the existing import-runtime path. The actual VC8
`msvcrt.lib(gs_report.obj)` needs five Kernel32 IAT symbols in addition to the
query's Enter/Leave imports. All five were already attested in the relocation
ledger and original import directory; the unit explicitly lists those data
cells. No executable address is supplied as an ABS symbol, and no generated
provider code, alignment declaration, padding or fabricated return is added.
The static-lifecycle contract is unchanged. An earlier private static-CRT
control also produced byte equality but did not satisfy that contract and is
not the accepted configuration.

The 417800 class declaration moves into a header so the query can use the
actual existing native-vector view. Its ordinary independent probe remains
**nonexact with a 196-byte source body**; before/after canonical source SHA256 is unchanged at
`8b555d49eadfdb899972c17a5ad87ec39f2aa6ba848d92c385c8f7e1a79439da`.
This checkpoint gives 417800 no exact or library credit. The aggregate source
includes its one definition rather than copying it; do not link both this
match unit and its independent probe as an application. Recursive quoted-include
input hashing covers both implementation files and their headers.

## Relation to the larger ReimuObject work

The real-provider investigation for `496540` compiled the 25 decoded direct
callees from actual source. The quantized lookup candidates remain nonexact;
a consistent private float-return view does not prove their original types.
Additional real source providers and pinned CRT/SDK libraries reduce the
context to one missing function: this texture query, reached through secondary
animation initialization.

Whole source files also brought unused method references into the link. `/Gy`
preserved the reviewed helper results but did not eliminate those diagnostics.
Private source partitioning therefore retains complete real methods for wave
dispatch, effect emission, background scalar updates and secondary animation
construction/destruction/initialization/color. All seven selected methods
recompare exact. No synthetic method body replaces a missing dependency.
`build/reimu-object-provider-link-20261022/gy/partition-link-summary.log`
records the remaining 404E60 edge before its reconstruction.

This supplies a real dependency for the larger context; it does not accept
`496540`, which retains its selected source and nonexact +31 result. Next wire
this real provider into that experimental link, then vary genuine CIL helper
visibility one context at a time. Neither LTCG necessity nor standalone-object
impossibility is inferred for the larger root.

## Reproduction and accounting

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-texture-size-query --compare --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-resource-handle-lookup --compare --json
```

The first command is exact 148/148; the second remains an expected nonzero
comparison with the unchanged 417800 source payload. Reports are
`build/texture-size-query-20261022/formal.json`, `lookup-header-replay.json`
and `target-facts.json`; private generation recipes remain in
`.analysis/reimu-object-provider-link-20261022/`.

Unused default native-provider objects are retained losslessly in
`build/reimu-object-provider-link-20261022/native-default-inputs.tar.gz`;
`native-default-archive.json` records each original size/hash and the archive
hash. Every member was read back and verified before removing its loose copy.
Restore from the repository root with `tar -xzf` and that archive path. Active
Gy inputs, accepted outputs, sources, recipes and databases remain in place.

This promotes one existing candidate from review to authored exact, adding one
mapping, one source-present function and 148 exact bytes. No full aggregate
cold replay is claimed. The final local CI and whitespace gate must pass before
commit or push.
