# Reconstruction progress

Generated from `config/functions.csv`. Only functions with a verified
100% comparison are counted as reconstructed.

- Matching functions: **213 / 2976 (7.16%)**
- Matching function bytes: **28,664 / 2,477,462 (1.16%)**
- Ghidra internal `.text` inventory: **4,838 functions**
- Origin census: **1,862 excluded**, **665 confirmed authored**, **2,311 awaiting origin review**
- Exact within confirmed-authored census: **213 / 665 (32.03%) functions**, **28,664 / 1,308,136 (2.19%) bytes**

| Status | Functions |
| --- | ---: |
| `unclassified` | 2,297 |
| `identified` | 127 |
| `decompiled` | 199 |
| `implemented` | 137 |
| `compiles` | 3 |
| `matching` | 213 |
| `library` | 1,862 |
| `blocked` | 0 |

| Origin | Functions |
| --- | ---: |
| `authored_game` | 665 |
| `compiler_generated` | 1,148 |
| `vc8_runtime` | 498 |
| `third_party` | 195 |
| `import_thunk` | 21 |
| `unknown` | 2,311 |

The legacy authored denominator is every non-`library` ledger row. The
confirmed-authored census is evidence-backed but deliberately incomplete;
`review` rows are not silently counted as either authored or library.

Run `python3 scripts/function-origins.py --write` and then
`python3 scripts/progress.py` after changing origin or ledger evidence.
