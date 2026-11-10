# Fighter cutin resource lifetime465420

Source registration was updated on 2026-11-04; earlier unselected-status statements below are historical.

The local sprite view below has been replaced by actual global CSprite with
the same95-byte candidate. See CHARACTER_RESOURCE_SPRITES_2026_11_02.md; the
folded handle/sprite prefix does not uniquely prove an A0 cutin owner.

Complete candidate95/native96 remains nonexact at+40; no exact/source-selection
credit. Target SHA:c585cf40128cc4f0c32264c9d6948718f2f5f2aaf6982c56cdc59111164b0572.

The exact cutin loader4651E0 and existing FighterResources contract identify
handle00,0x94 sprite04,selector98/state9C in the0xA0 resource. Fighter destruction
462CE0 calls465420 during reverse member cleanup. The new local lifetime view
uses actual CSpriteBase plus the five real transform floats, allowing implicit
sprite destruction to restore IColor naturally after authored handle release.
The handle is cleared only after a nonzero release. No vptr stores are authored.

The first40 bytes, full EH prologue and final sprite teardown are established.
Remaining comparison starts where target compares handle memory directly and
reloads it after EH-state publication; current VC8 loads and tests the handle
once before that publication. The one-byte size difference is not acceptance.
No volatile handle, fake reload, manual EH or forced register is added.
The handler is the genuinely folded6B839B already attested by ScenarioRenderEntry
lifetime, not a new guessed address. Shared resource headers remain unchanged.

## Source registration, 2026-11-04

The existing source is selected for the native shared handle/sprite cleanup prefix.
The 96-byte body, its edge from the Character destructor and its call to the exact
title-resource release are target-pinned. Resource release and clearing are game
ownership policy; the following sprite cleanup is implicit. Because the body is
folded, this does not establish a unique original full cutin class or 0xA0 extent. A
fresh build reproduces 95/native96 with first difference +40; no exact bytes or
whole-game behavior are claimed.
