# Scene-owned resource shutdown

Canonical JP1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

## Ownership and source policy

CSceneManager RTTI table6C74AC slot04 owns41E120. Its25-byte body calls the
264-byte43D670 resource shutdown, releases paired wave buffers401A80 and
finally forwards to BGM shutdown4034F0. This is an explicit scene lifecycle
policy, not an atexit/compiler-generated helper.

43D670 lowers the scene-loader thread priority and waits, persists score data,
closes the network socket and releases its texture, deletes the current shared
network session, destroys shared battle/profile resources, clears deck and
battle effect resources, cleans both player profiles, releases128 event sound
handles, updates window-mode state, and copies both profile names into config
before saving. Native globals independently pin profile stride33C/name98,
config string stride1C, and the128-entry handle range. The window message is
WM_SYSKEYDOWN/VK_RETURN with zero lParam; no additional guard is added.

The socket member pointer is prepared before retaining the session owner,
matching the existing exact clear_network_session43B0A0 source. That independently
supported ownership lifetime changes the initial263-byte candidate to exact264;
no forced register or fake alias barrier. The later shared-session reload and
conditional delete/clear remain visible, as the intervening calls can change it.

## Canonical results

- shutdown_scene_resources43D670:264/264.
  SHA da5c943f62daad444755973b0bed34f337e334c68b28b2c1cc751aba97a245b1.
- CSceneManager::shutdown41E120:25/25.
- Existing CSceneManager::initialize41E070 remains162/162 in the affected TU.

New source: src/engine/SceneResourceShutdown.cpp.
Extended owner: src/engine/SceneManagerRuntime.cpp.
Receipts under build/frontier-43d670-20261028:
socket-owner-lifetime.json, scene-owner.json, boundary.json.
Complete boundary review preserves the outgoing tail to427390 for43D670 and
to4034F0 for41E120. Their callee internals receive no new exact credit; notably
pending GameConfig save and BGM shutdown are not implied exact by these callers.
Only289 authored bytes are added, with incremental validation of other units.
