# AyaObject 903 auxiliary sequence order, 2026-10-02

## Bounded result

This continues [the distinct sequence 4/5 checkpoint](AYA_OBJECT_903_DISTINCT_SEQUENCE_BRANCHES_2026_10_02.md) for `AyaObject_update_action_state_vslot28 @ 0x0061A290`. The original Japanese v1.06a executable has SHA-256 `56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`; the target callable `[61A290,61EED2)` has 19,522 bytes and SHA-256 `18c813a20cea427b2c3577e2612e3f2e949a191ee2496dc9204331758bebb895`.

**Target observation:** the auxiliary table at `61F080` has ten distinct entries, physically ordered by sequence index 0 through 9. The retained source had case 6 immediately after case 1. Its candidate table placed physical case 6 before cases 2–5. Moving only the existing case 6 source block after case 5 preserves the case behavior and makes the configured candidate table at `61F098` ten distinct, physically ordered entries too. This is a source-layout hypothesis supported by target table order; it does not establish the original source spelling or whole-function equality.

| Sequence | Target entry | Candidate entry |
| ---: | ---: | ---: |
| 0 | `61E65F` | `61E699` |
| 1 | `61E69C` | `61E6D6` |
| 2 | `61E744` | `61E77E` |
| 3 | `61E858` | `61E886` |
| 4 | `61E926` | `61E972` |
| 5 | `61E9A5` | `61E9F1` |
| 6 | `61EA00` | `61EA4C` |
| 7 | `61EA6A` | `61EAB6` |
| 8 | `61EB3C` | `61EB7D` |
| 9 | `61EB7C` | `61EBD3` |

The prior case 4/5 proof still checks all 218 bytes/40 instructions and internal/external edges after a 76-byte placement translation. Case 6 occupies 106 bytes/21 instructions on both sides. Its control edges and instruction sequence agree after translation, but four operand sites use different registers: owner load/WORD guard `EDX` versus `EAX`, and facing-byte load/stack store `EAX` versus `ECX`. The target case 6 shares the movement tail entered at `61E701` with case 1; the candidate enters its corresponding `61E73B`. This is scoped structural evidence, not a canonical match.

The configured full-root comparison remains **nonexact at +0x22**, target `0F` / candidate `27`. The source SHA-256 is `cbdd5a4d39e282ee03f66a8fadfbb905014d57db1d9efc3a03e7ca93039492f3`; configured object SHA-256 is `d525406d00bf70e08333646dc82a713c1eaf4ced5bff196c36e1ee26ee84aa89`; comparator-window SHA-256 is `87a6008b96bfdfdea43fa2bede685a3175d64c1e47531079afe7cdbfd823ae8a`. Candidate metadata begins at 19,548, 24 bytes beyond target metadata 19,524; section tail is 20,016. The 19,522-byte comparator window ends 26 bytes before candidate metadata. The window hash does not establish candidate body equality. No exact-ledger credit is added.

## Verification and remaining unknowns

The private proof `.analysis/aya-903-order-20261002/prove-sequence-order.py` verifies target PE identity, retained source/object hashes, target table bytes, relocated COFF table bytes, strict physical ordering, case 6 lengths/edges, and the four register differences. The prior case 4/5 proof was rerun on the configured object. Final reports use `build/aya-903-order-final-*20261002.json` and the configured build object `build/match-units/GptWeb_AyaObjectActionState.obj`.

The final object still has 903 at 1,726 bytes/372 instructions against target 1,697 bytes/364 instructions, and raw diagnostics 3/34 (entry/800/980). The target traversal covers all 4,630 instructions/19,522 bytes through seven switches; the main switch has 33 distinct destinations and zero splits. The 124/124 guard model, all 18 selector conversions, 826 postspawn and 861 owner/payload paths, two 641-value unsigned-Y paths, 450 scoped emission cases, RTTI byte-call widths, and 852 translated patterns were rerun against this object. Their scope is limited to the asserted intervals and models. No shared ABI/header/helper/compiler/object-partition or accepted-unit relocation contract changed.

The remaining 903 cases and physical tail, case 1/6 register lifetimes, 852 FILD/facing/scratch homes, 826/861 sharing, and original TU/LTCG context remain unresolved. IDA still fails target identity and was not used. No Ghidra import or aggregate cold replay is claimed. The local `scripts/ci.py` and `git diff --check` gate is required before commit.
