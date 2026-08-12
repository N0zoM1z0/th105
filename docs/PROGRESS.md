# Reconstruction progress

Generated from `config/functions.csv`. Only functions with a verified
100% comparison are counted as reconstructed.

- Matching functions: **214 / 2976 (7.19%)**
- Matching function bytes: **28,717 / 2,477,469 (1.16%)**
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
`review` rows are not silently counted as either authored or library.

Run `python3 scripts/function-origins.py --write` and then
`python3 scripts/progress.py` after changing origin or ledger evidence.
