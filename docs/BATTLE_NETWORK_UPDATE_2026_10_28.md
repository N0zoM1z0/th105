# Network battle updates 426180 and426380

Current RTTI-owned CBattleSV/CBattleCL tables6C04E8/6C0540 put these roots at
slot04 (cells6C04EC/6C0544). Complete native extents are247/267 bytes.
Raw recursive CFG reaches every decoded instruction and all return paths:
build/frontier-426180-20261028/boundary.json.

Both routines exit2 on disconnection. UI-selection change or renderer phase5
uses the guarded session6C0<-6D8 copy and renderer scene-phase dispatch.
Otherwise the battle peer updates, the session advances, and mode3 selects
the inline-copy return path. Other modes pump transition callbacks, dispatch
renderer phase1 through the existing out-of-line guarded-copy helper, and
flush replay values when the loop ends. The client UI-phase1 path additionally
resets combined input counters. Native return codes differ between SV and CL;
the explicit source preserves those differences.

Ordinary branch source emits250/259 with first+126 because the renderer-phase
comparison uses CMP instead of the native SUB. A real switch dispatch closes
that prefix: current252/native247 first+179 and259/native267 first+237.
The remaining differences are shared-return branch targets / tail merging.
Positive outer nesting and explicit switch defaults are byte-neutral. No
redundant cases, liveness tricks or goto/assembly shaping were added.

Current receipt: build/frontier-426180-20261028/structured-switch.json.
Earlier controls: formal-build.json,phase-switch.json. Neither root receives
source-selection or exact credit. Only this new unit was built; no existing
caller interface or shared header changed.
