# Native font configuration: complete439/439 exact

`TextFontOwner194::configure @ 0x004115A0` is canonical **439/439 bytes,
all128 instructions**, from ordinary typed C++ compiled through genuine
GL/LTCG. Constructor411430138/138, destructor4114C0210/210 and compiler-only
list cleanup408A0071/71 remain exact in the changed owner TU. This checkpoint
adds one authored exact function /439 bytes; it grants no compiler credit.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target and tracking preflights pass. IDA and the typed-RE database
preflight reject the wrong open executable; all accepted observations come
from the hash-attested raw PE and actual pinned compiler/linker products.

## Observed behavior and complete boundary

The normal ECX member receives one config pointer, reaches RET4 at411754,
and covers all439 bytes through411756. Full target/canonical SHA256:
`956579b761782920fcbd5bace551efbd03e12c27f8ab1adeefb4dd0a4147e535`.
The source extent is derived independently from the linked symbol and closed
CFG, with no target-sized crop. All six REL32 calls are resolved canonically;
there are no game absolute-data, vtable or EH metadata operands in this root.

The genuine config assignment copies0x128 bytes to owner+0C with REP MOVSD.
The six bytes at10C..111 are three start/end RGB pairs. If all pairs match,
configure packs the start colors as R<<16 | G<<8 | B into fallback168.
That flat branch preserves existing base158 and active154 pointers.

Otherwise it conditionally deletes the old base array, then directly assigns
`new unsigned[height]` to158. There is no intervening zero store. The compiler
naturally emits the target array-allocation overflow gate. For last=height-1,
each signed index y from0 through last produces, independently per channel,
`(end-start)*y/last + start`; the three values are packed into the new array.
Only this gradient branch publishes base158 to active154.

Both branches then delete each temporary list15C front array and pop its node.
The actual native container supplies the target checked front/pop guards,
link writes, scalar node deletion and count decrement. Configure retains the
sentinel and string; unlike owner destruction it does not destroy members.
The existing source layout remains194 bytes with config0C/list15C/string170.

These are target observations, not proposed improvements. No extra pointer
reset, height clamp or changed interpolation rounding is introduced. Gradient
height1 reaches division by zero in the observed instructions; caller-domain
and exception-policy recovery remain open. Exact C++ source spelling, nominal
class name and original TU ownership are not proven by this reproducing view.

Six independent canonical-exact caller bodies still reach configure:

| Caller | E8 site |
| --- | --- |
| 431440 | 43156B |
| 434AC0 | 434BD1 |
| 43FCA0 | 43FD89 |
| 44DCB0 | 44DDCA |
| 454EC0 | 454EFC |
| 454FE0 | 455026 |

Each edge is read directly from the pinned PE and checked against its current
matching caller row. These cross-subsystem uses establish authored ownership
independently of adjacency. The prior manual family-origin rule is removed:
all three owner roots now use canonical-exact-authored. Its complete configure
hash and six incoming edges remain fail-closed regression evidence, including
a wrong-destination negative control. Compiler exclusions remain separate.

## Compiler result, scope and reproduction

The first natural source is404 bytes/122 instructions in ordinary COFF,
canonical698a90c6 and nonexact+0. Genuine GL/LTCG yields the target aligned EBP
frame, EBX owner and complete439/128 instruction stream on the first build.
There is no register/frame forcing, inert local, assembly or fake provider.
Selected source SHA256:
`233deecebe2d92e87cc175b15efa89dfa9a4da7aa1a7101046545edeb679fced`.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-owner --compare --json
```

Only the owner source and its unit change build inputs. The one affected
accepted unit is cold-rebuilt after final ledger edits: both previous authored
roots remain exact, alongside new configure and the existing private compiler
witness. Shared headers, profiles, relocation ledgers and other accepted-unit
definitions are unchanged. No unrelated or aggregate cold replay is claimed;
the progress SVG reports the updated ledger snapshot with its provisional
authored denominator and separate origin-review bar.

Receipts, raw target/source disassembly, linked provenance, native COFF control,
full caller facts and affected-scope audit are under
`build/font-owner-config-20261021/`; private recipes are under
`.analysis/font-owner-config-20261021/`. Completed controls are compressed only
after per-file SHA256 readback. The final local gate is:

```bash
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next: actual glyph/markup/blend providers and coherent full-font TU evidence.
Font begin/end/text and the larger Reimu496540 root remain nonexact.
