# Source layout

The source tree is created module-by-module as binary ownership is established.
The planned modules are defined in `config/modules.toml`; character-specific
implementations belong below `src/characters/`.

The current 1.06a ledgers accept 47 source-present authored functions / 3,304
bytes as canonical exact across 28 cold-replayable VC8 units. Progress remains
ledger-driven; the presence of a source file alone is not counted.
