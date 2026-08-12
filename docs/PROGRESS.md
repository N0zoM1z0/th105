# Reconstruction progress

Generated from `config/functions.csv`. Only functions with a verified
100% comparison are counted as reconstructed.

- Matching functions: **209 / 4789 (4.36%)**
- Matching function bytes: **28,248 / 2,634,588 (1.07%)**
- Ghidra internal `.text` inventory: **4,838 functions**

| Status | Functions |
| --- | ---: |
| `unclassified` | 4,136 |
| `identified` | 131 |
| `decompiled` | 179 |
| `implemented` | 131 |
| `compiles` | 3 |
| `matching` | 209 |
| `library` | 49 |
| `blocked` | 0 |

Run `python3 scripts/progress.py` after changing the ledger.
