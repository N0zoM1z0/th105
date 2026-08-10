# Source layout

The source tree is created module-by-module as binary ownership is established.
The planned modules are defined in `config/modules.toml`; character-specific
implementations belong below `src/characters/`.

`battle/GameMode.cpp` contains the first two exact function-byte matches.
Progress remains ledger-driven; the presence of a source file alone is not
counted.
