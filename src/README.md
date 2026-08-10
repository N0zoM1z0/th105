# Source layout

The source tree is created module-by-module as binary ownership is established.
The planned modules are defined in `config/modules.toml`; character-specific
implementations belong below `src/characters/`.

The initial source files contain five exact function-byte matches across battle,
configuration, and input accessors. Progress remains ledger-driven; the
presence of a source file alone is not counted.
