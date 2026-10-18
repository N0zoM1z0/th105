# Reimu CPU counter reads, 2026-10-19

The complete `Reimu_update_cpu_action_policy @48D390` candidate now reads its
signed764 field directly in action bounds instead of freezing it in one local
scalar after initialization. This recovers separate signed lower/upper tests
across the action tree. It remains **nonexact**: the first strict difference
is now `+97 / 48D427`: the candidate hoists a flag-preserving
`LEA EDI,[EBX+1]` ahead of the existing JLE guard. No exact
bytes, function, boundary, origin or source-present count are added.

## Observed target and compiler evidence

The target remains original Japanese 1.06a, executable SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The accepted callable `[48D390,49120F)` is15999 bytes, SHA256
`3bd363994e140603ae0ec249ffd3a36b1ae0448e72a389e417c4cc7a6d113e2d`.
Existing complete CFG/ABI/vtable evidence is unchanged. The direct read-only
Ghidra run independently checked executable/entry/text/root identity and read
back the typed15999-byte void ECX method. Nine primary DB files remain
unchanged; no IDA semantic data, factory adapter, copied project or concurrent
Ghidra process was used. New private receipts are in `build/reimu-cpu-shape/`
and `.analysis/reimu-cpu-shape-20261019/`.

At action300, target `48D6C3..48D6D4` loads the764 word and compares AX with10
and90 using separate JL/JG guards. Action320 at `48E2AB..48E2BF` separately
rejects negative values and values above90. The preceding counter reset/RNG
initialization already agreed with the old candidate; the initial suspicion
that initialization itself had been folded was disproved.

The old local snapshot made VC8 emit subtract/unsigned-range tests instead.
Changing only C++ block scope produced an identical complete canonical
payload. Direct field expressions still let VC8 eliminate repeated loads,
but no longer trigger those unsigned range combinations. They require no
volatile qualifier, helper, fabricated CFG, padding, assembly or ABI change.
This is a source-shape explanation supported by the compiler experiment,
not proof of unique original C++ spelling or a new gameplay fix.

The native diagnostic now also reports decoded word-CMP/conditional-branch
counts from entry to the first common-policy guard:

| Physical interval | End | JL | JG | JA/JBE |
| --- | --- | ---: | ---: | ---: |
| Target | 48E61D | 97 | 56 | 0 |
| Old snapshot candidate | 48E490 | 38 | 2 | 52 |
| Selected field reads | 48E62D | 92 | 55 | 0 |

This interval includes prelude/action/resource/sequence words and excludes
later action arms placed after the common guard. It is not a logical action
coverage total, semantic score or exact-byte measurement. In particular,
changing the first mismatch from+12E to+97 does not measure the whole change.

## Controls and remaining ownership differences

All controls use ordinary VC8 SP1 O2 compilation with unchanged GS/FP flags,
headers, layout, unit and relocation bindings. Only the field-read source is
selected. Private controls remain disposable below `build/reimu-cpu-shape/`:

| Source property | Callable prefix | COFF payload | Result |
| --- | ---: | ---: | --- |
| Prior snapshot | 15244 | 15785 | Unsigned range folding |
| Separate per-action scalar scopes | 15244 | 15785 | Entire payload identical to prior source |
| Neutral store order only | 15300 | 15841 | Range folding remains |
| Direct field reads, selected | 15860 | 16401 | Separate signed word guards |
| Field reads plus neutral store order | 15784 | 16325 | Undesired neutral/facing tail sharing |
| One root-scope word reference | 15864 | 16405 | Signed guards, different address lifetime/code |

The combined neutral-order control merges part of action300's neutral and
facing stores, whereas the target retains distinct bodies. Target neutral
entry48D6D6 is shared by300/320/two321 arms. A smaller payload is not a reason
to select a different physical partition; the existing store expressions
remain unchanged in the selected source.

The selected root has3965 decoded instructions and50 RETs, versus target4126
and52. All five helper identities and cleanup contracts remain unchanged.
Target/source selector sites are121/117. A separate policy0 CFG closure pins
all four missing selector copies to that region: target entry48FC0C reaches
1488 instructions and37 selector sites; candidate entry48FC8D reaches1359
instructions and33 sites. Both closures have no unresolved indirect or
internal-call exits and call only the real selector. Selector counts outside
that region agree at84 each; this alone does not prove their memberships.
Policy0 reaches50 target/49 source RET sites; the whole-root RET totals also
reflect the still-different conditional EBP-save/early-return arrangement.

Do not apply the field-read change mechanically to policy0's selection roll.
The target has only two76A accesses, both stores. It preserves the actual
selector result in ECX (`48FC28`) before storing CX (`48FC2D`) and uses that
cached narrow value in subsequent conditions. Recover its FP lifetimes,
source branches and call/return sharing separately; the current evidence
does not prove an original TU/LTCG boundary or explain every clone.

## Build pins and reproduction

| Artifact | SHA256 |
| --- | --- |
| Selected source | `4e146107a6707a593e54ba4e3b54972dd8379799e859ceac7493e5ddaf3e8d7a` |
| Object used for native replay | `6c8d8035a657b9d462938ebb2f9ebd344edd0654a750a99e550e470d8e2f895f` |
| Full16401-byte canonical payload | `8baf522260e54665fb7bf441a6ff4db19863b1483387b86f082f4c1792d36547` |

The old full payload is
`fe974ea52a9c60011287f966997396f45b9ab30033da1c26879b56ddbfbbdf7b`.
COFF file timestamps can vary on a fresh build; compare source, compiler,
build receipt and canonical payload rather than requiring the object hash
alone to be deterministic.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-reimu-cpu-action-policy --compare --json
taskset -c 0 nice -n 10 python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --cases 5000
taskset -c 0 nice -n 10 python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --reimu-edge-cases
taskset -c 0 nice -n 10 python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --selection-cases
taskset -c 0 nice -n 10 python3 scripts/audit-cpu-policy-paths.py \
  build/match-units/GptWeb_ReimuCpuActionPolicy.obj --root reimu --height-cases
```

Strict comparison intentionally returns a mismatch. Native results are finite
entry-to-RET diagnostics with original helpers, full actor/RNG/call evidence
and masked PC53 x87 state. They do not establish all branches, exceptional
inputs/concurrency, original source identity or byte equality. No all-unit
cold replay or aggregate exact percentage is claimed.

The finished object passes **0/67242** differences:5000 general,45714 edge,
16160 selection and368 height cases. Fixture input hashes are unchanged from
the [initial source checkpoint](REIMU_CPU_SOURCE_2026_10_19.md); all reports
pin the new object/payload above. Policy0 confirms actual rolls0..100 and
visits all1488 target instructions/4892 bytes with no missing instruction
addresses. Its finite callsite correspondence observes38 target/34 source
sites including the entry draw;46420 paired observations have no output
differences. This agrees with the independent37/33 static policy0 closure,
but does not prove a complete caller bijection or branch coverage.

Final gates are `python3 scripts/validate-tracking.py --require-target`,
local `python3 scripts/ci.py` and `git diff --check`. Only this source unit is
affected; shared headers, ABI, flags, relocation ledgers and accepted exact
units are unchanged. Detailed local reports remain under
`build/reimu-cpu-shape/`; source-present and exact census values are unchanged.
