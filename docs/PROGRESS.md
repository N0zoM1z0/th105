# Reconstruction progress

Generated from `config/functions.csv` and `config/function-origins.csv`.
Only functions with a verified 100% comparison are counted as reconstructed.
Authored-game and external/library results are shown separately and combined.

- Matching functions: **214 / 2943 (7.27%)**
- Matching function bytes: **28,717 / 2,474,126 (1.16%)**
- Reproducible library functions: **233 / 1897 (12.28%)**
- Reproducible library bytes: **77,115 / 169,825 (45.41%)**
- Reproducible third-party functions: **221 / 228 (96.93%)**
- Reproducible third-party bytes: **75,971 / 76,951 (98.73%)**
- Combined exact reconstruction: **447 / 4840 (9.24%) functions**, **105,832 / 2,643,951 (4.00%) bytes**
- Ghidra internal `.text` inventory: **4,840 functions**
- Origin census: **1,897 excluded**, **667 confirmed authored**, **2,276 awaiting origin review**
- Exact within confirmed-authored census: **214 / 667 (32.08%) functions**, **28,717 / 1,308,598 (2.19%) bytes**

| Status | Functions |
| --- | ---: |
| `unclassified` | 2,261 |
| `identified` | 126 |
| `decompiled` | 199 |
| `implemented` | 140 |
| `compiles` | 3 |
| `matching` | 214 |
| `library` | 1,897 |
| `blocked` | 0 |

| Origin | Functions |
| --- | ---: |
| `authored_game` | 667 |
| `compiler_generated` | 1,148 |
| `vc8_runtime` | 500 |
| `third_party` | 228 |
| `import_thunk` | 21 |
| `unknown` | 2,276 |

The legacy authored denominator is every non-`library` ledger row. The
confirmed-authored census is evidence-backed but deliberately incomplete;
`review` rows are not silently counted as either authored or library. Exact
library rows remain excluded from authored-game matching, but are included
in the separately visible library, third-party, and combined reconstruction
metrics.

Run `python3 scripts/function-origins.py --write` and then
`python3 scripts/progress.py` after changing origin or ledger evidence.
