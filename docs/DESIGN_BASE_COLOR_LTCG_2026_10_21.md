# Complete profile design color exact

`ProfileRenderListView_set_color @ 0040BFE0` is complete canonical **81/81**
against original Japanese TH10.5 v1.06a, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

```bash
python3 scripts/build.py --unit gpt-web-profile-render-list-color-runtime --compare --json
```

Both complete canonical bodies have SHA256
`fc4ce6e449091bf4552ac4c93e8a3ab1e53b2c993af32ccfdbe2a2b7fc77a961`.

## Observed evidence and unchanged source

All 36 instructions in `40BFE0..40C030` are reachable and close through RET4;
the following fifteen CC bytes are excluded. ECX owns the design view, with
checked list +14 and head +18. The loop reloads the head, validates the checked
iterator, dispatches each object's vslot +4 with the color, then validates
increment after the callback. The incoming color stays in the EBP-based
argument slot in the target.

The canonical target's CDesignBase RTTI/vtable identity was recovered in the
[native-vector audit](DESIGN_BASE_NATIVE_VECTOR_2026_10_21.md). Its vtable
`6C08AC` slot +4 at `6C08B0` points here. Exact caller owners `43F900` and
`440170` have freshly verified raw E8 edges `43F951/4401DB`. The durable
profile-facing mapping and existing source view name are retained; their
original C++ spelling is not established by byte equality.

The selected CRLF source is entirely unchanged, SHA256
`54bcd029b0af977013bbb24cb8b028d957e1de886fbed89633df7b0a66461f2f`.
Its fresh ordinary COFF result remains 74/81 with complete source canonical
`5bb8ba6193c21ed6485a6219048e0650a0a4bc248b218f3e13e3d5713fe3604d`.
Inspired by the independently exact CDesignBase render, a genuine resolved
GL/LTCG build of this same source naturally retains the eight-byte-aligned
frame and reproduces all 81 bytes. No source local, field, type, loop spelling,
attribute, assembly or forced calling convention is changed.

The formal unit now uses `linked_candidate`/`vc8-sp1-ltcg-o2`, with an explicit
empty data-binding list. Source export/map ownership and both complete CFGs
are checked. Three actual VC8 runtime import-thunk calls replay by name to
invalid-parameter target `68A143`; all other bytes agree without normalization.
The source has no absolute game-data reference or internal vtable store.
This resolves the old frame blocker for this function; it does not prove that
all aligned-frame mismatches have the same explanation.

## Records and verification scope

One existing source-present function gains exact81-byte acceptance. No new
source, mapping, layout/header or relocation binding is added. The old
source-only authored origin rule is retired in favor of the canonical exact
origin baseline. Before retirement, the complete body hash, both caller edges
and vtable-cell witnesses were checked successfully and recorded privately.
The 197 surviving rules have unchanged selections, are disjoint from this
address, and need no unrelated anchor replay.

Only this previously nonexact unit's compiler profile changes, so only this
unit requires replay. Caller ABI/bindings and every predecessor accepted unit's
source/profile are unchanged. No cold aggregate replay or new aggregate
percentage is claimed. The earlier same-day iterator-layout/SSE/RTM controls
remain valid historical ordinary-COFF observations, not current blockers.

Reports and raw facts are in `build/design-base-color-20261021/`, with private
recipes in `.analysis/design-base-color-20261021/`. Target/tracking preflight
passes; IDA again rejects its wrong-target session. No Ghidra session or
database write is used. Heavy work is pinned to CPU0 at nice10. Original
source spelling/TU partition and the CDesignBase binary loader implementation
remain open; Reimu496540 remains nonexact at+31.
