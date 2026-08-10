# Seed reverse-engineering evidence

Evidence labels used by this repository:

- **Observed**: supported by shipped instructions and/or live state of the exact target.
- **Inferred**: a data-flow conclusion that is not exhaustively validated.
- **Hypothesized**: a candidate awaiting a targeted check.

## Scene and input roots

- **Observed** `0x006ECE7C` is the current engine scene ID,
  `0x006ECE78` the requested ID, and `0x006ECE44` the scene-controller pointer.
  The transition function at `0x00407F80` commits requested to current after a
  controller swap.
- **Observed** `0x006ECFF0` is the 256-byte DirectInput keyboard state filled by
  `GetDeviceState` in the main loop at `0x004080E0`.
- **Observed** `0x006E6300` is the P1 input object; bindings begin at `+0x08`,
  signed hold counters at `+0x38`, and the logical mask at `+0x62`.
- **Inferred** `0x006E6370` is the P2 input object. It begins exactly one
  `0x70`-byte player-input object after P1 and is returned by `0x00439C80`.
- **Observed** `0x006E7520` is the combined menu-input object.
- **Observed** `0x006ECFD0` is a `CInputManager` base whose raw keyboard state
  begins at `+0x20` (`0x006ECFF0`). `0x0040D370` returns the DirectInput
  top-bit state for one scan code.
- **Observed** `0x006E6BB8` is a static 256-entry dword input-state table;
  `0x0040A210` writes a zero-extended byte to one entry.
- **Observed** `0x006E6B38` is the game-configuration object; its CPU
  difficulty field at `+0x64` is read and clamped by the configuration menu.
- **Observed** `0x006E7238` is the static score-data object. CRT initialization
  constructs it, and its accessor feeds the `score.dat` serializer.
- **Observed** `0x00439C00` computes `0x006E64C0 + slot * 0x33C`; selection
  callers use slots 0 and 1. The record field names are not recovered.
- **Observed** `0x00439C10` clears `0x006E62DC[slot]` and stores `0xFE` to
  `0x006E62D8[slot]`; `0x00439C30` and `0x00439C60` read those exact fields.
- **Observed** `0x00439C50` returns `0x006E7558`, which is combined menu input
  `+0x38`. `0x00409C50` establishes the counter range at that offset.
- **Inferred** `0x006E62E4` is a session setup option. Its getter and setter
  are exact, but its final enum name is not yet proven.
- **Observed** `0x006E62FC` holds a `CNetworkBase`-derived session object;
  client/server setup paths install the pointer there.
- **Observed** main-menu scene 2 uses vtable `0x006ACCF4`; its update and render
  functions are `0x00424AB0` and `0x00424860`.

## Battle and frame roots

- **Observed** `0x006E6244` is a live `CBattleManagerBase`/derived pointer.
  Fighter roots are manager `+0x0C` and `+0x10`.
- **Inferred** `0x006E6FE8` is the shared match-setup block. Callers use its
  fields for both character IDs, stage/BGM selection, decks, and battle-scene
  initialization; `0x00439870` returns its address.
- **Observed** fighter positions are `+0xEC/+0xF0`, velocity `+0xF4/+0xF8`,
  facing at `+0x104`, action/sequence/pose/frame at
  `+0x13C/+0x13E/+0x140/+0x142`, and HP/max HP at `+0x174/+0x176`.
- **Observed** `transform_local_aabb_to_world` at `0x0046ACD0` mirrors local X
  by facing and translates by actor position. `resolve_fighter_body_collision`
  at `0x0046C290` consumes current frame data and its body rectangle.

## Sakuya action roots

- **Observed** `0x004DEF70` reads the actor command mask at `+0x728` and selects
  special actions in the 500–599 range; live command traces validated the role
  `Sakuya_handle_input_and_select_action`.
- **Observed** `0x004DDB20` handles Sakuya action changes.
- **Observed** actor `+0x158` is current frame data; flags at frame `+0x4C`
  participate in input/cancel gating.

The function/global CSV files are the authoritative index for these facts.
