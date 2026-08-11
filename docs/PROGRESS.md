# Reconstruction progress

Generated from `config/functions.csv`. Only functions with a verified
100% comparison are counted as reconstructed.

- Matching functions: **150 / 4807 (3.12%)**
- Matching function bytes: **17,597 / 2,637,530 (0.67%)**
- Ghidra internal `.text` inventory: **4,838 functions**

| Status | Functions |
| --- | ---: |
| `unclassified` | 4,383 |
| `identified` | 136 |
| `decompiled` | 48 |
| `implemented` | 87 |
| `compiles` | 3 |
| `matching` | 150 |
| `library` | 31 |
| `blocked` | 0 |

Run `python3 scripts/progress.py` after changing the ledger.
