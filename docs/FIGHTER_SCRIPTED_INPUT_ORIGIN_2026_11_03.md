# Fighter scripted-input origin, JP 1.06a

The pinned original body at `0x463E40` spans 753 bytes (SHA-256 `f4fc93f5a85590424dd4f614584f07b853b9541eeeeeffbb58915e3d20fabddc`). Its decoded body implements the game-specific fighter input snapshot, state dispatch, deque history and probability policy described in `KNOWLEDGE_BASE.md`. The boundary audit covers all 753 bytes and identifies one indirect virtual tail jump; it does not by itself prove that destination's ownership.

Two independently canonical-exact callers replayed in this checkpoint: round initialization at `0x470BC0` (306 bytes) calls the target at `0x470C02` and `0x470C0A`; pre-reset at `0x472230` (314 bytes) calls it at `0x472272` and `0x47227A`. These body and edge anchors establish authored game ownership. Receipts: `build/frontier-scripted-input-origin-20261103/`.

Earlier natural-source analysis reached 751/native753 but that implementation is not present in the current tracked source tree. Original source, TU and compiler context remain unresolved. This is an origin classification only: no source-present or canonical exact bytes are credited.
