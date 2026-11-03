# Battle origin evidence, 2026-11-03

The original Japanese 1.06a image is SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.

- `0x432420` is a 196-byte selection shuffle: it repeatedly chooses a random checked deque entry and moves it within the spell selection deque. Its complete CFG reaches all 196 bytes and terminates at its sole RET; the independently exact `0x432520` mode setter calls it at `0x432538`. Body SHA-256: `540ef3b2fd1fd978957bf2df18d4d2272af85f78ec0ad79cfd09f1b904a8dbe0`.
- `0x4666A0` is the 670-byte battle-manager overlay rendering body. Its complete CFG reaches all bytes and the RET, with no indirect or outgoing jumps; the independently exact phase method `0x466980` tail-jumps to it at `0x4669DE`. Body SHA-256: `916c2058290c838da9b3a11d5ba076df2b0b0156f3ba375a3b314058f656a40f`.

These game-policy bodies and original caller edges establish authored ownership. Prior near-size source hypotheses remain nonexact and unselected; these classifications add no source or exact-byte credit. Receipts: `build/frontier-spell-shuffle-origin-20261103/`.
