# Reconstruction progress

Generated from `config/functions.csv`. Only functions with a verified
100% comparison are counted as reconstructed.

- Matching functions: **209 / 2977 (7.02%)**
- Matching function bytes: **28,248 / 2,476,352 (1.14%)**
- Ghidra internal `.text` inventory: **4,838 functions**
- Origin census: **1,861 excluded**, **650 confirmed authored**, **2,327 awaiting origin review**
- Exact within confirmed-authored census: **209 / 650 (32.15%) functions**, **28,248 / 1,300,754 (2.17%) bytes**

| Status | Functions |
| --- | ---: |
| `unclassified` | 2,314 |
| `identified` | 138 |
| `decompiled` | 182 |
| `implemented` | 131 |
| `compiles` | 3 |
| `matching` | 209 |
| `library` | 1,861 |
| `blocked` | 0 |

| Origin | Functions |
| --- | ---: |
| `authored_game` | 650 |
| `compiler_generated` | 1,148 |
| `vc8_runtime` | 497 |
| `third_party` | 195 |
| `import_thunk` | 21 |
| `unknown` | 2,327 |

The legacy authored denominator is every non-`library` ledger row. The
confirmed-authored census is evidence-backed but deliberately incomplete;
`review` rows are not silently counted as either authored or library.

Run `python3 scripts/function-origins.py --write` and then
`python3 scripts/progress.py` after changing origin or ledger evidence.
