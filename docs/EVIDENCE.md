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
- **Observed** `0x006ECFD0` is a raw DirectInput backend with an HWND at
  `+0x00`, an `IDirectInput8` pointer at `+0x04`, and no vptr. Its raw keyboard
  state begins at `+0x20` (`0x006ECFF0`). `0x0040D370` returns the DirectInput
  top-bit state for one scan code.
- **Observed** RTTI identifies the vtable installed by `0x00409850` as
  `CInputManager`. Its ten signed hold counters occupy `+0x38..+0x5C`;
  `0x00409AA0` clears those ten dwords and matches the target exactly.
- **Inferred** RTTI and the merge path identify `0x0040A040` as a
  `CInputManagerCluster` accessor. It returns the active input-source byte at
  `+0x74` and matches the target's four bytes exactly.
- **Inferred** `0x0040A050` is the constructor used by CRT initialization for
  the static input-state table storage at `0x006E6BB8`. It clears the three
  pointers at `+0x404`, `+0x408`, and `+0x40C`; its 23 bytes match exactly.
- **Observed** `0x0040A070` clears the 256 dword counters at `0x006E6BB8`,
  calls `0x0040A2F0` for the adjacent storage at `+0x400`, and clears three
  modifier-state bytes at `+0x410..+0x412`. The reconstructed 54 bytes match
  exactly. The helper's reset role is inferred from its sole caller and
  boundary operations; the original container type remains unknown.
- **Observed** `0x0040A1C0` returns true only when the indexed counter equals
  one and each requested state at `+0x410..+0x412` is active. Its 69-byte
  reconstruction matches exactly. The counter update path supports the
  inferred `is_initial_press` name; the three state bytes are kept as generic
  modifiers until their exact Shift/Alt/Control ordering is proven.
- **Observed** `0x0040A0B0` iterates the byte vector at `+0x400`, increments or
  clears the corresponding dword counters from DirectInput top bits, and
  updates three state bytes from scan-code pairs `(0x2A,0x36)`,
  `(0x38,0xB8)`, and `(0x1D,0x9D)`. The first pair is Shift and the latter two
  are consistent with Alt and Control, but the source keeps generic modifier
  names. The faithful VC8 body compiles to 255 bytes; a strict relocated
  positional comparison is 6/263 (2.28%) because the target's dynamic 8-byte
  stack alignment and loop padding shift nearly every subsequent byte. Unsafe
  manual frame shaping was rejected; exact codegen remains open.
- **Observed** `0x0040A220` scans the same checked byte vector for a duplicate
  scan code and otherwise performs `push_back`. Setup code calls it with
  `0x01`, `0x3B..0x44`, `0x57`, and `0x58`. Its faithful non-LTCG VC8 body is
  199 bytes versus the 202-byte target; strict relocated positional equality
  is 3/202 (1.49%) because the target uses the same dynamic alignment pattern
  and an LTCG-internalized vector-insert ABI at `0x0040A350`. Semantics are
  reconstructed, while exact LTCG codegen remains open.
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
- **Inferred** `0x006E62E8` is an asynchronous battle-setup task selector.
  Setup schedules a callback that clears it on completion; callers poll the
  value as a busy state.
- **Observed** `0x006E62FC` holds a `CNetworkBase`-derived session object;
  client/server setup paths install the pointer there.
- **Observed** main-menu scene 2 uses vtable `0x006ACCF4`; its update and render
  functions are `0x00424AB0` and `0x00424860`.
- **Observed** RTTI and COL data identify the vtable slot at `0x006ACC20` as
  `CSelectScenario`'s scalar-deleting destructor `0x004247D0`, not a `CTitle`
  method. It calls the class destructor at `0x00424350`, conditionally invokes
  delete for flag bit zero, and returns `this`. This compiler-generated method
  is recorded for ownership evidence while the source-level destructor remains
  the reconstruction target.
- **Observed** `0x00424840` is `CTitle` vtable slot `+0x14`, called by the scene
  controller when leaving the title scene. It tests whether the tracked UI
  selection byte differs from the current state through `0x0043A290`, and on
  change calls the `0x00439D30` thunk to enable selection-state tracking. The
  reconstructed 20-byte hook matches the target exactly.
- **Observed** adjacent `CTitle` vtable slot `+0x10` is called on scene entry.
  `0x004247F0` preserves the observed previous-scene exclusion order, starts
  `data/bgm/op.ogg` through `0x0043B6D0` when appropriate, clears the network
  session through `0x00439CC0`, and resets UI selection-state tracking. Its
  reconstructed 68 bytes match exactly.
- **Observed** `0x00424A10` advances the title menu's animation counter and
  writes twelve staggered float offsets at `CTitle +0x254`. Its full 147-byte
  contiguous span matches exactly, including ten bytes of internal loop
  alignment padding. Main-worktree evidence now proves helper `0x00406680` is
  the exact orientation-cosine table lookup used by the animation.
- **Observed** RTTI at the vtable containing `0x004253A0` identifies its owner
  as `CSceneBase`. The method calls `0x0041E870`, then maps state 5 to scene 13
  and state 6 to scene 10; its reconstructed 26 bytes match exactly. The
  callee increments the scene field at `+0xB8` and returns 5 or 6 according to
  whether the asynchronous battle-setup task is active. Final game-facing
  names for the states and scene IDs remain inferred.
- **Observed** RTTI/COL data for vtable `0x006ACE68` identifies
  `0x00425980` as `CLoadingWatch`'s scene-entry slot. It plays the shared title
  BGM unless the previous scene ID is 2; the reconstructed 21 bytes match
  exactly.
- **Observed** `0x00424E60` is the RTTI-owned `CTitle` destructor. It releases
  handles at `+0x08` and `+0xA0` through the global resource manager, invokes
  the `+0x1DC` design member's virtual cleanup and destructor, then restores
  three color vptrs and the `CSceneBase` vptr. Natural VC8 member/base
  destruction with `/GS` reproduces all 161 bytes exactly; helper type names
  remain conservative because their precise RTTI identities are unresolved.

## Audio roots

- **Observed** `0x00417E80` creates the DirectSound8 device at `0x006ED3EC`,
  the primary DirectSoundBuffer8 at `0x006ED3E8`, and the optional
  DirectSound3DListener8 at `0x006ED3F0`.
- **Observed** `0x004180D0` releases those three COM interfaces in listener,
  primary-buffer, device order and clears each pointer. The reconstructed
  82-byte shutdown function matches the target exactly after strict BSS
  relocation validation.
- **Observed** `0x00418130` creates a secondary DirectSound buffer, upgrades it
  to `IDirectSoundBuffer8`, releases the temporary interface, and preserves the
  failing HRESULT after displaying the shipped error text. Its reconstructed
  110 bytes match exactly, including the allowlisted `MessageBoxA` IAT call.
- **Observed** `0x004181A0` converts a linear gain with the VC8 CRT `log10`,
  multiplies by `33.220001220703125f * 100.0f`, truncates through
  `_ftol2_sse`, and clamps the DirectSound volume to `[-10000, 0]`. The CRT
  identity is confirmed against pinned VC8 SP1 `libcmt.lib`, including the
  matching `FLDLG2`/`FYL2X` core; the reconstructed 103 bytes match exactly.
- **Observed** `0x00418210` is reached only by a VC8 EH unwind action with a
  hidden EAX pointer to an owning audio object's `+0x30` member. It invokes
  vtable slot zero with scalar-delete flag 1. This compiler-generated cleanup
  continuation has no stable source-level ABI and is excluded from authored
  reconstruction rather than imitated with naked assembly.
- **Observed** `0x00418220` owns the Ogg data-source open sequence: it clears a
  previous stream, opens the reader, installs the observed read/seek/close/tell
  callback table, queries Vorbis info, constructs a 16-bit PCM `WAVEFORMATEX`,
  and calls the final audio initializer. The owning member is at caller `+0x30`
  and the layout is supported through `OggVorbis_File +0x10`, `vorbis_info*`
  `+0x2E0`, loop doubles `+0x12E8/+0x12F0`, and wave format `+0x12F8`.
  Its faithful VC8 object is 292 bytes versus the 291-byte target, with a
  relocation-normalized sequence score of 262/292 (89.88%). Exact matching is
  blocked by target LTCG/private register conventions at entry and the final
  helper; naked-assembly imitation was rejected.
- **Observed** callback table `0x006E3D34` contains read, seek, close, and tell
  functions used by the Ogg stream setup path. Its close slot at `0x004184E0`
  deletes the polymorphic reader at data-source `+0`, clears the pointer, and
  returns success; the reconstructed 25 bytes match exactly. Concrete reader
  type and later data-source fields remain unknown.
- **Observed** the table's tell slot at `0x00418500` invokes reader vtable
  `+0x0C` with `(0, 1)` and subtracts the signed dword at data-source `+8`.
  Its reconstructed 23 bytes match exactly. The vslot behaves as a seek/tell
  operation, but the concrete reader type and exact adjustment meaning remain
  inferred.

## Network and menu transition roots

- **Observed** `0x00425280` receives the `CNetworkBase`-family object returned
  by `get_network_session` on two menu-to-battle transition paths. If its
  pointer at `+0x6B0` is null, it copies the pointer at `+0x6C8`; the 22-byte
  reconstruction matches exactly. The final meanings of both fields remain
  unknown, so the source preserves offset-based names.
- **Observed** `0x004263B0` has 68 direct call xrefs across 17 callers, commonly
  with `ECX=0x006E6260`. It stores a float to `+0x20` and the paired enable byte
  to `+0x2C`; the reconstructed 17 bytes match exactly. Adjacent setters and
  matrix consumers support a shared camera/view-transform state, but no RTTI
  proves the original class or field names, so offset-based member names are
  retained.

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
  by facing and translates by actor position. Although its 91-byte body does
  not read `ECX`, both direct calls in `0x0046C290` load the collision context
  into `ECX`; modeling it as a `CollisionContext` member preserves the existing
  91/91 exact body and reproduces those call sites.
- **Observed** `resolve_fighter_body_collision` at `0x0046C290` consumes both
  current-frame body rectangles, two signed edge-owner globals at
  `0x006D1B6C..0x006D1B6D`, stage-boundary classifications, AABB overlap, and
  proposed-X stage-height gates. The complete implementation covers all four
  edge-pinned and both ordinary half-separation paths; its standalone VC8
  object is 1832 bytes against the 1862-byte target and is not claimed exact.
- **Observed** battle-slot state methods `0x00463270` and `0x00463280` index a
  three-element character-pointer array at `+0x28` and active-byte array at
  `+0x34`. `0x00463290` swaps both fields in lockstep; `0x00464240` activates
  a non-null slot and rebuilds the active-character list, while `0x004641F0`
  clears it on removal. The manager class and original method names remain
  inferred.

## Sakuya action roots

- **Observed** `0x004DEF70` reads the actor command mask at `+0x728` and selects
  special actions in the 500–599 range; live command traces validated the role
  `Sakuya_handle_input_and_select_action`.
- **Observed** `0x004DDB20` handles Sakuya action changes.
- **Observed** actor `+0x158` is current frame data; flags at frame `+0x4C`
  participate in input/cancel gating.

## Input, package, audio, and scenario-select hard roots

- **Observed** `CInputManager` has a `0x38`-byte binding prefix followed by ten
  signed hold counters at `+0x38..+0x5C`. `CInputManagerEx` adds injected and
  resolved 16-bit masks at `+0x60/+0x62` and a selector byte at `+0x64`.
  `0x00409AD0` updates those counters and constructs the logical bit mask; its
  injected and hardware branches now match all 378 target bytes exactly.
- **Observed** `0x00409900` updates the same counters from either a `0x50`-byte
  gamepad state, raw DirectInput keyboard bytes, or a reset-only source. Its
  faithful object is 406 bytes versus the 404-byte target; the remaining
  difference is VC8 zero/high-bit register allocation and equivalent `test`
  forms. `0x00409C50` merges a VC8 deque of sources by signed absolute axis
  magnitude and unsigned button-counter maxima, updating the active source on
  every win. Its 1096-byte object versus 1003-byte target preserves all 27
  checked accesses and is retained as an LTCG-sensitive implementation.
- **Observed** the file-reader hierarchy owns a Win32 handle at `+4`, last read
  size at `+8`, and package size/offset/position/key at `+0xC..+0x18`.
  `CFileReader` seek/destructor/read/last-size/size/scalar-delete, the owner
  destructor, and package size/read functions match exactly: nine functions,
  263 target bytes. Package seek has the same 124-byte body and 113 positional
  bytes; only the origin-2 arithmetic evaluation order differs. The owner open
  path faithfully selects package/plain readers and retains a one-byte
  standalone/LTCG scheduling difference.
- **Observed** `0x00418380` fills a `0x8000`-byte PCM block in at most `0x1000`
  byte `ov_read` chunks, zero-fills a non-looping EOF tail, and seeks to the
  stored loop time for looping streams. `0x00418520` constructs a `.sfl` path,
  reads the sidecar through `FileReaderOwner`, scans `cue` and `adtl` records
  with last-record-wins behavior, and converts unsigned sample positions to
  doubles using the stream sample rate. Both compile faithfully; their final
  stack/x87/private-register shapes remain LTCG-sensitive.
- **Observed** `CSelectScenario` is `0x3EC` bytes. Its embedded guide overlay is
  at `+0x344`, design resource at `+0x2E4`, four texture handles at
  `+0x40/+0xD8/+0x170/+0x218`, and four color objects at
  `+0x44/+0xDC/+0x174/+0x21C`. The `/GS` destructor at `0x00424350` releases
  handles in `+0x218,+0xD8,+0x40,+0x170` order, performs guide/design cleanup,
  restores color/base vptrs, and frees its vector/string storage. The recovered
  source matches all 271 bytes exactly.
- **Observed** the adjacent 862-byte `CSelectScenario` constructor at
  `0x00424470` loads the background, clear marker, and character-name tile
  textures; filters scenario IDs 0..14 through score bytes at `+0x1C`; binds
  design IDs 100, 200, 300, 500..502, and 600..603; and loads guide ID 92.
  The complete source candidate now covers those paths. Its remaining byte
  delta is concentrated in the checked-vector/tree iterator machinery and the
  missing intermediate base-construction type, so it remains `implemented`
  until the target build is available for an integrated comparison.
- **Observed** `0x004238B0` initializes two 20-byte cursor records. Their
  selection field is at cursor `+0x0C` (object `+0x2C8/+0x2DC`), input counter
  pointer at `+0x08`, item count at `+0x00`, and repeat/window fields at
  `+0x04/+0x10`. `0x004239C0` is the real selection state machine: it updates
  GuideOverlay, runs the game-type and scenario cursors, applies a ten-tick
  cosine preview transition, and handles confirm/cancel events.
- **Observed** `0x00423B60` is the full scenario carousel renderer. It draws
  seven wrapped items at 80-pixel spacing, fades each from its absolute X
  offset, checks score bits by game type, fades two selected design objects,
  renders the preview, then renders GuideOverlay. The faithful VC8 object is
  757 bytes versus the 756-byte target; the residual delta is x87 temporary
  scheduling and conversion shape, not omitted render behavior.
- **Observed** `GuideOverlay` is `0xA8` bytes: visibility at `+0`, texture
  handle at `+4`, sprite at `+8`, scroll/wrap floats at `+0x9C/+0xA0`, and
  alpha at `+0xA4`. Its constructor (`0x0043DAF0`), texture loader
  (`0x0043D940`), and wrapped two-draw renderer (`0x0043DA70`) match exactly.
  Update scrolls by 0.5, wraps at the texture width, and fades alpha in steps
  of 15; destructor releases the handle before natural sprite destruction.

The function/global CSV files are the authoritative index for these facts.
