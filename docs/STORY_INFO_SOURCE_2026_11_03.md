# Story battle-info update source, 2026-11-03

The existing complete source for `BattleInfoRecordF8::update_story_471930` is now recorded individually. The native 323-byte body has SHA-256 `7422f38ee095768cde15559079fe5d8fef4b61440a84782d4eb334753ec2285a`, 118 decoded instructions and two complete return paths. The exact InfoManager update calls it at `0x471CA7`; its unit and three other accepted roots were freshly rebuilt and passed.

The story-specific policy smooths displayed health and the secondary gauge, publishes countdown progress, and updates byte-wrapping alpha, colors and visibility. The implementation retains the observed callback reloads and does not add saturation or null guards. `STORY_INFO_UPDATE_2026_10_28.md` documents its field and control-flow evidence and bounded negative controls.

The public `exact-first-story-info-update` unit compiles to 321 bytes against native 323 and first differs at offset 67. It is source-present but nonexact. No suffix-only or partial-byte credit is assigned. Fresh receipts are `build/frontier-story-info-source-20261103/source-final.json` and `caller-final.json`.
