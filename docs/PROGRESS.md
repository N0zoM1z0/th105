# Reconstruction progress

Generated from `config/functions.csv`. Only functions with a verified
100% comparison are counted as reconstructed.

- Matching functions: **209 / 2976 (7.02%)**
- Matching function bytes: **28,248 / 2,475,712 (1.14%)**
- Ghidra internal `.text` inventory: **4,838 functions**
- Origin census: **1,862 excluded**, **655 confirmed authored**, **2,321 awaiting origin review**
- Exact within confirmed-authored census: **209 / 655 (31.91%) functions**, **28,248 / 1,302,805 (2.17%) bytes**

| Status | Functions |
| --- | ---: |
| `unclassified` | 2,307 |
| `identified` | 130 |
| `decompiled` | 194 |
| `implemented` | 133 |
| `compiles` | 3 |
| `matching` | 209 |
| `library` | 1,862 |
| `blocked` | 0 |

| Origin | Functions |
| --- | ---: |
| `authored_game` | 655 |
| `compiler_generated` | 1,148 |
| `vc8_runtime` | 498 |
| `third_party` | 195 |
| `import_thunk` | 21 |
| `unknown` | 2,321 |

The legacy authored denominator is every non-`library` ledger row. The
confirmed-authored census is evidence-backed but deliberately incomplete;
`review` rows are not silently counted as either authored or library.

Run `python3 scripts/function-origins.py --write` and then
`python3 scripts/progress.py` after changing origin or ledger evidence.
