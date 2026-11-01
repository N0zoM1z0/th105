# ScoreData owned-prefix construction and implicit destruction

The complete ScoreData constructor43E1A0 is canonical306/306 and adds306
authored exact bytes. The separately emitted implicit destructor43DF10 is
canonical393/393 but compiler-owned, with zero authored credit.

## Actual source lifetime

The already-established ScoreDataDefaults.hpp members supply the source types:
two checked unsigned sets, four int vectors, a common int/int map, twenty
per-character maps at+A8 and twenty24-byte-record vectors at+198. The pointer/
array fields and their ordering are independently consumed by exact defaults
and persistence. The new lifetime view models the observed owned prefix through
+2D8, not an assertion that no unobserved trivial tail exists in the original
nominal class.

After those members construct, the authored constructor body clears only
initialized_00. Native43E2BB performs this last store. An initializer-list store
would occur before the members and is not substituted; other scalar flags,
arrays and padding are not reset by this constructor. Loader zero-initialization
of the actual static object is a separate operation.

The source defines the corresponding static lifetime. This naturally emits
the implicit destructor and its registration callback. There is no authored
destructor declaration or body in selected source, no handwritten member
cleanup, manual vptr write, duplicated construction/destruction, assembly,
padding local, register assignment or synthetic exception control.

A preliminary explicit-empty-destructor diagnostic also reproduced393 code
bytes, but it is not the selected provenance witness. The selected real static
lifetime independently emits that complete destructor implicitly.

## Complete code and callbacks

- Constructor306, all92 instructions reachable, RET at43E2D1:
  991bc3a6dde8fab75eeea8f3d07879689361f418cc7e241cc8ff31a513ec690c.
- Implicit destructor393, all128 instructions reachable, RET at43E098:
  3ace549e00663599e8e143969780c8a6806b4b3ebada3123e36e4facca547c1b.
- Native map constructor43E0A0/43, vector constructor4460D0/14,
  map destructor41F0C0/52 and vector destructor435F90/42 all freshly match
  their entire source emissions. The14-byte vector constructor stays review
  under the unchanged generic minimum-byte policy; no new helper credit.

The constructor passes count20/stride12 and count20/stride16 to the original
VC8 array-construction helper. The destructor reverses the real member order
and passes the same complete destructor callbacks to the array teardown helper.
All call fields and callback addresses are resolved. Full callback bytes are
pinned independently before they bind the root's absolute pointer arguments.

The native handler addresses6B8F2B/6B8E9B are bound at the actual source fields.
Their16-byte prefixes establish address ownership only. This checkpoint does
not claim full equality of remote EH FuncInfo/unwind maps or execute exception
unwinding. Every byte of each bounded ordinary function remains compared.

## Independent static ownership

Native initializer6BEC30/22 loads ScoreData6FCC98, calls43E1A0 at6BEC35, and
registers callback6BF170 through _atexit68AF1E. The callback's complete10-byte
body loads the same object and tail-calls43DF10. The source-generated .text$yc/
.text$yd functions reproduce both whole bodies after their named COFF link
relocations. The ordinary .text comparator was not relaxed to accept these
sections: a separate private section-aware metadata witness resolves every
original field and compares all22/10 bytes.

Initializer SHA256:886bc2e6e4ccd9aa80fe766cb0afce0d97f7c831ff4583e166e530f34f5013d7.
Callback SHA256:cfd5e50e3e789c911dd746c0c80f428de27f883e57941926e1ca1594abbc9a55.
No new initializer candidate or byte credit is invented. The existing callback
classification is preserved.

## Provenance and regression

The implicit destructor's separate generated-origin rule freshly recompiles
selected source and verifies329 non-relocation bytes, all repeated named call
sites, its complete393-byte native hash, full-inventory uniqueness and the
existing callback's actual E9 edge. Its0.70/24/no-tail thresholds are unchanged.
The constructor is the only new matches.csv row.

    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-score-data-lifetime --compare --json
    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-score-defaults --compare --json
    taskset -c 0 nice -n 10 scripts/repo-python scripts/build.py --unit exact-first-score-persist --compare --json

All six lifetime-unit functions pass; existing defaults2428 and persistence1155
also freshly pass. ScoreDataDefaults.hpp and the old consumers are unchanged.
The larger loader's known operand-order residual remains outside this scope.

Receipts:build/frontier-score-owner-lifetime-20261101/final.json, defaults.json,
persist.json, static-witness.json and canonical.json. The generated-origin
receipt is retained under build/frontier-boost-library-20261031.
Source:src/config/ScoreDataLifetime.cpp. Default CI312 passes.

Exact1586/450027 authored bytes; source1788/authored1808/mapped1815,
excluded1805/review414/units767. No destructor, callback, template or metadata
bytes enter the authored exact numerator.

The subsequent SCORE_VECTOR_DEFAULT_2026_11_01.md proof separately classifies
4460D0/14 through its complete original member and actual array caller. The
generic minimum-byte policy is unchanged; there is no additional authored or
parent/EH credit.
