# CFade timer policies

Canonical JP1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

Current RTTI table6C74C4, COL6DBDA4 and type descriptor6E9148 identify CFade.
Slots08/0C own41E250/41E270. The already exact render slot41E290 independently
reads color04 and signed timer08 to draw the two60-frame fade halves.

- update_fade41E250: when timer reaches120, clear timer and color; increment
  only a nonzero timer; return true.
- advance_to_midpoint41E270: return true at60. Otherwise reflect timers greater
  than60 through120, increment, and return false. The comparison stays signed.

Both complete30-byte roots are canonical exact in
cross-v106a-render-scene-consumers. Source replaces only the two previously
untyped virtual declarations with their actual bool-returning policies and
ordinary method definitions. No vtable loads, new guards or forced state.

Focused replay also preserves all six existing accepted peers:
41E04043,41E290142,41E920132,41F6A062,41F8A053,41F410217 bytes.
Receipts: build/frontier-41e250-20261028/formal-build.json and boundary.json.
Only the two authored methods add60 exact bytes; unchanged receipts remain
incremental rather than a fresh whole-repository replay.
