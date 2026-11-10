# Battle origin evidence, 2026-11-03

The original Japanese 1.06a image is SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

- `0x432420` is a 196-byte selection shuffle: it repeatedly chooses a random checked deque entry and moves it within the spell selection deque. Its complete CFG reaches all 196 bytes and terminates at its sole RET; the independently exact `0x432520` mode setter calls it at `0x432538`. Body SHA-256: `540ef3b2fd1fd978957bf2df18d4d2272af85f78ec0ad79cfd09f1b904a8dbe0`.
- `0x4666A0` is the 670-byte battle-manager overlay rendering body. Its complete CFG reaches all bytes and the RET, with no indirect or outgoing jumps; the independently exact phase method `0x466980` tail-jumps to it at `0x4669DE`. Body SHA-256: `916c2058290c838da9b3a11d5ba076df2b0b0156f3ba375a3b314058f656a40f`.

These game-policy bodies and original caller edges establish authored ownership. At
that checkpoint both source hypotheses were unselected and nonexact. The shuffle
source is now selected but remains nonexact; the overlay was subsequently recovered
exactly, as documented in BATTLE_RENDER_TAIL_EXACT_2026_11_04.md.

## Replay header and round reset

The full 313-byte replay-header read `0x429A30` is called at `0x42A296` by the
freshly exact replay-list formatter `0x42A150`; its SHA-256 is
`7b806a89700b2d3f9220e0848a68b5c1fe52be0684658414d8821421eb3663f3`. The full
290-byte battle-round reset `0x471180` is called at `0x444E0D` by the freshly exact
continue-menu update `0x444C70`; its SHA-256 is
`bf64af9cf4b91fa500f9fef4f90c8c9415c211fb7f164d271c69ce45a6f46317`. Both closed CFGs
reach every byte and have no indirect or outgoing direct jumps. Their game-specific
behavior and exact caller edges establish authored ownership. Prior source
hypotheses remain unselected/nonexact; no exact-byte gain.

## Profile menu state handlers

The exact profile-menu dispatcher `0x44D240` tail-jumps to the primary handler
`0x44BCF0` at `0x44D2DC` and state-one handler `0x44CA80` at `0x44D2E6`. Complete
native code hashes and the seven- and four-entry original switch tables are pinned.
Recursive decoding with those tables reaches all 256 and 446 body bytes,
respectively; the tables themselves are excluded from these body counts. This
supports game-authored ownership, not source or exact credit. Previous natural
source candidates remain unselected and nonexact.

## Profile and result policies

Three complete native UI policies have separately exact owner edges and are
classified as authored, without adding exact-match credit:

- `427C60` (333 bytes) updates profile editor selection, with a call from the
  exact profile state-six owner at `44D04C`. Its full body closes 112 reachable
  instructions and 12 direct calls. The retained 330-byte source remains
  unselected and nonexact.
- `4472A0` (619 bytes) updates the active result menu, reached by the exact
  wrapper's tail jump at `447586`. Its full body closes 175 reachable
  instructions and 27 direct calls. Its prior source is now selected but remains
  nonexact.
- `44B540` (790 bytes) captures profile keyboard and gamepad input, called by
  the exact key configuration update at `44B8A5`. The CFG reaches 194
  instructions; the only skipped seven bytes at `44B659` are the original
  LEA alignment instruction after a direct jump. The complete native hash
  includes those bytes. The latest retained 785-byte candidate has a 780-byte
  exact prefix but a different final return topology. It is now selected and
  remains nonexact; an older 389-byte-prefix note is superseded.

The origin rule pins all complete body hashes and exact-owner edges. No runtime
input, rendering or complete gameplay execution is claimed. The target-specific
rule was checked directly; no full origin-census replay is claimed.

The three owner units were rebuilt. The profile and key-config units pass;
the result unit reports overall mismatch because its separate result-menu
constructor remains nonexact, while its `447560` owner itself is exact 43/43.
Tracking and target-independent CI pass.
