# Select network entry and client update

Canonical exact:4264B0,205 bytes;426580,313 bytes. New authored total518 bytes.
Receipt: build/frontier-4264b0-20261028/formal-build.json.
Native CFG:69/69 and122/122 decoded instructions reachable, respectively,
including executed loop-alignment instructions and complete return paths.
Receipt: build/frontier-4264b0-20261028/boundary.json.

Current RTTI evidence:
- Table6C04AC, COL6D6FD8, type descriptor6E6038 names CSelectSV.
- Table6C0504, COL6D7178, type descriptor6E60D0 names CSelectCL.
- Shared entry4264B0 is in pointer cells6C04BC and6C0514 (slot10).
- Client update426580 is at6C0508 (slot04).

The entry waits for network state3 or disconnection using the real8-byte
event/wait object (CreateEventA,16ms wait, CloseHandle, ordinary EH cleanup).
It copies session204 to208, invokes base entry421120 with the original scene
argument, and clears the derived byte2ED8.

The update requires observed game-mode value5 and exits with2 on menu input1
or disconnection. With scan-code2A or36 held, keys2..10 select indices0..8.
A pending transition performs readiness/process/setup callbacks and can return11.
Otherwise it advances the session, pumps both input peers and selection vslot18,
publishes the setup when that slot returns6, then sets pending2ED8. Other paths
return9. Local names describe the observed interfaces; RTTI ownership is
separate from assumptions about network-mode naming.

Ordinary virtual interfaces preserve AL predicates, late EBX lifetime and
callback order. No manual vtable arithmetic, new guards, fake storage,
compiler override or shared-header edit is used. The local owner is a bounded
non-instantiated runtime view; its opaque range is not newly constructed data.
Only this new unit was built. Origin rules exclude neither root; no generated
EH code earns authored credit.

Target/object SHA-256:
- 205:4d5910512fe0b87e7deedaa9c1c977d4d9238f78aeb2e197dfb172969bfe7b11
- 313:10e92c433cb4422b8eff92ae77904c2d474544b30ebddceca8b490af98cd7d4e

## Server selection update

The CSelectSV override at4262A0 is now independently canonical exact217/217.
Its pointer is6C04B0 (the current SV table slot04). It shares the pending,
readiness, setup and two-peer input protocol but has no client mode5/keyboard
index gate and uses results8/10/2. The local source overrides the existing
view's update_client slot; that inherited method name is not a claim that the
server policy is a client policy.

Fresh receipt build/frontier-4264b0-20261028/server-update.json preserves the
previous205/313 exact peers. This adds217 authored bytes,735 for this Select
entry/update cluster overall. No shared headers or global flags changed.

## Client loading-state mapping

CLoadingCL vtable6C0524 slot04 (cell6C0528) owns426490. Its complete26-byte
body maps the existing base loading update's5/6 states to14/11, with14 as
default. Ordinary switch source is canonical exact26/26; this is authored
scene policy, not a generated adjustor thunk. Origin rules contain no exclusion.
Receipt loading-client.json preserves the205/313/217 exact peers and adds26
authored bytes,761 across this four-function unit. No shared headers changed.
