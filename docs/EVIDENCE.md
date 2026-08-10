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
- **Observed** `0x006E7520` is the combined menu-input object.
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
