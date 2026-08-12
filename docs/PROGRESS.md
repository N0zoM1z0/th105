# Reconstruction progress

Generated from `config/functions.csv` and `config/function-origins.csv`.
Only functions with a verified 100% comparison are counted as reconstructed.
Authored-game and external/library results are shown separately and combined.

- Matching functions: **214 / 2976 (7.19%)**
- Matching function bytes: **28,717 / 2,477,469 (1.16%)**
- Reproducible library functions: **56 / 1864 (3.00%)**
- Reproducible library bytes: **22,697 / 166,482 (13.63%)**
- Reproducible third-party functions: **44 / 195 (22.56%)**
- Reproducible third-party bytes: **21,553 / 73,608 (29.28%)**
- Combined exact reconstruction: **270 / 4840 (5.58%) functions**, **51,414 / 2,643,951 (1.94%) bytes**
- Ghidra internal `.text` inventory: **4,840 functions**
- Origin census: **1,864 excluded**, **667 confirmed authored**, **2,309 awaiting origin review**
- Exact within confirmed-authored census: **214 / 667 (32.08%) functions**, **28,717 / 1,308,598 (2.19%) bytes**

| Status | Functions |
| --- | ---: |
| `unclassified` | 2,294 |
| `identified` | 126 |
| `decompiled` | 199 |
| `implemented` | 140 |
| `compiles` | 3 |
| `matching` | 214 |
| `library` | 1,864 |
| `blocked` | 0 |

| Origin | Functions |
| --- | ---: |
| `authored_game` | 667 |
| `compiler_generated` | 1,148 |
| `vc8_runtime` | 500 |
| `third_party` | 195 |
| `import_thunk` | 21 |
| `unknown` | 2,309 |

The legacy authored denominator is every non-`library` ledger row. The
confirmed-authored census is evidence-backed but deliberately incomplete;
`review` rows are not silently counted as either authored or library. Exact
library rows remain excluded from authored-game matching, but are included
in the separately visible library, third-party, and combined reconstruction
metrics.

Run `python3 scripts/function-origins.py --write` and then
`python3 scripts/progress.py` after changing origin or ledger evidence.
