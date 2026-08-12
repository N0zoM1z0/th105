# Reconstruction progress

Generated from `config/functions.csv`. Only functions with a verified
100% comparison are counted as reconstructed.

- Matching functions: **211 / 2976 (7.09%)**
- Matching function bytes: **28,398 / 2,476,136 (1.15%)**
- Ghidra internal `.text` inventory: **4,838 functions**
- Origin census: **1,862 excluded**, **657 confirmed authored**, **2,319 awaiting origin review**
- Exact within confirmed-authored census: **211 / 657 (32.12%) functions**, **28,398 / 1,303,745 (2.18%) bytes**

| Status | Functions |
| --- | ---: |
| `unclassified` | 2,305 |
| `identified` | 129 |
| `decompiled` | 195 |
| `implemented` | 133 |
| `compiles` | 3 |
| `matching` | 211 |
| `library` | 1,862 |
| `blocked` | 0 |

| Origin | Functions |
| --- | ---: |
| `authored_game` | 657 |
| `compiler_generated` | 1,148 |
| `vc8_runtime` | 498 |
| `third_party` | 195 |
| `import_thunk` | 21 |
| `unknown` | 2,319 |

The legacy authored denominator is every non-`library` ledger row. The
confirmed-authored census is evidence-backed but deliberately incomplete;
`review` rows are not silently counted as either authored or library.

Run `python3 scripts/function-origins.py --write` and then
`python3 scripts/progress.py` after changing origin or ledger evidence.
