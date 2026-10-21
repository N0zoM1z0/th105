# Native font end provider and caller context

`0x00411AD0` now has genuine C++ native-list/GDI end source in the actual
font traversal TU. VC8 naturally lowers its file-local ordinary stdcall source
parameter into **ESI**, with no stack argument. This resolves a concrete
private-entry context question without an external register-ABI facade.

It remains **nonexact168/168, 49/49 instructions, first mismatch+7**. No exact
function or byte is added. The real caller412670 is now324 bytes/116 instructions,
nonexact+0. The earlier326-byte isolated caller remains a frozen prior checkpoint,
not the selected current code.

Only original Japanese TH10.5 v1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking preflights pass. IDA again rejects its wrong open
executable; no database semantics, metadata writes or original-byte patches are
used. All new target facts come from the hash-attested PE.

## Observed full boundary and policy

Independent raw CFG traversal reaches the complete168 bytes/49 instructions,
with a single RET at411B77. Target SHA256:
`68b02c0e179c843e68bb474274a6e27b31038d81e97a900afe08ed54af9083b7`.
The reviewed font caller reaches it at412783 with its existing ESI font pointer.

The complete behavior is:

1. While the native color list is nonempty, delete the front unsigned array,
   then pop/delete the front node. Checked front/pop behavior retains both
   invalid-parameter guards and the native sentinel/rewiring/count operations.
2. Call `SelectObject(dc000, old_font008)` and pass its returned object directly
   to `DeleteObject`. There is no success test, substitution of saved font004,
   or new conditional cleanup.
3. Reload HWND from702A1C and DC from the font after those calls, then call
   `ReleaseDC`. Its result is not used by the text caller.
4. Clear font004, old_font008, then dc000, and return. The chained source
   assignment expresses this observed publication order naturally.

The physical native `std::list<unsigned *>` starts15C: proxy15C, sentinel160,
count164. Source guards the header offset at compile time. DC/font/original-font
fields are actual pointers at000/004/008. The bounded view now extends through
the native list, without claiming the full font size or representing fallback
color168 as count164. Original class spelling and member-versus-file-local
source ownership remain unknown; the file-local model is a measured source
hypothesis, not recovered PDB spelling.

## Compiler evidence and the precise remaining mismatch

A real static C++ provider is defined before `render_text` and called directly
from that actual caller. No fabricated caller, exported private entry, register
attribute, forced save, assembly, inert local or alignment is introduced.

| Complete candidate | Bytes / instructions | Canonical SHA256 prefix | First difference |
| --- | --- | --- | --- |
| end | 168 / 49 | e1daa198 | 411AD7 / +7 |
| actual font caller | 324 / 116 | c23fa0a9 | 412670 / +0 |

End source saves EDI only on the nonempty-list branch and restores it before
GDI work. The target pushes EDI before that branch and pops it after clearing
all three handles. The entire native loop411AE0..411B3D agrees byte-for-byte;
GDI work and zero-store instruction sequences agree but are shifted one byte
by the restore placement. Equal size/algorithm/register entry does not turn
this save-scope difference into an exact result.

Private RTM14.0.50727.42 and SP1
14.0.50727.762 builds (cl/c1xx/c2 versions and hashes recorded) of the same
genuine caller/provider model yield the
same complete end and caller canonical bytes. This excludes those two compiler
versions as a sufficient fix in this measured context. A source edit solely to
force EDI stack traffic would not establish original lifetime/context and is not
selected. Original TU/compiler phase remains open.

Selected source SHA256:
`b05613edec4c197cdbed8bc1c4104a355c96fea5b64ee5b8ba6e4612cdf903fd`.
The ordinary reproducible command is:

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-text-font-render --compare --json
# Expected exit1: both complete nonexact comparisons, no blocked relocation.
```

Native font begin291, glyph624, markup1744 and blend289 still need real provider
source/qualification before a closed linked experiment. The end provider alone
does not resolve the caller's aligned EBP frame or other private argument entries.

## Independent import bindings and affected scope

Three appended IAT bindings are attested independently from PE import records,
initial DWORDs and the actual target FF15 operands:

| IAT | Import | Initial bytes |
| --- | --- | --- |
| 6C000C | GDI32.dll!SelectObject | f25c2e00 |
| 6C0004 | GDI32.dll!DeleteObject | 165d2e00 |
| 6C01DC | USER32.dll!ReleaseDC | 9e5c2e00 |

Existing HWND702A1C binding, addends, validation rules and accepted compiler
settings stay intact. These API names have no accepted explicit binding,
transitive changed-source dependency or native COFF symbol consumer. Therefore
zero accepted units require replay; both affected nonaccepted font/texture units
are freshly rebuilt. Complete texture wrapper/backend candidates remain
110/264 with their prior canonical hashes50731d79/15555b85 and +7/+0 mismatches.
No unrelated or aggregate cold replay is claimed.

## Bounded execution evidence

The private harness executes the complete native end instructions from the PE
and the real compiled source. Native list branches, rewiring, counter updates
and the function's own stores execute normally; only CRT/GDI boundaries have
explicit observer models. This is not real GDI execution or malformed-list
coverage.

All **576 cases pass** across valid lists of0/1/2/4/8/32 nodes, null/non-null
payloads, three initial handle patterns, four SelectObject return values,
ReleaseDC success/failure and optional mutation of HWND/DC during DeleteObject.
Comparisons cover ordered payload/node releases, all list writes/final bytes,
actual SelectObject result passed to DeleteObject, fresh HWND/DC reload,
three zero-store order, EAX observation, ESP and callee-saved registers.
A genuine back/pop_back C++ negative control fails384 cases; only lists with
zero/one node can preserve its release order.

The new324-byte caller separately replays all **13,100** prior logical observer
cases with the actual generated ESI end-entry contract. All pass, with the same
expected trace digestc75c54eb. These caller checks still model provider boundaries;
only the separate576-case run executes the native end body itself.

Formal comparisons, raw/import facts, RTM/SP1 controls and execution receipts
are under `build/font-end-20261021/`; private reproducibility recipes are under
`.analysis/font-end-20261021/`. Completed controls are compressed only after
per-file SHA256 readback: 60,756 ->12,220 bytes. Selected source/header/object
and receipts stay available.

```bash
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

Next: native begin/color/font lifetimes and the remaining genuine providers;
revisit EDI preservation only with new TU/lifetime evidence. Retain current
source as nonexact and do not manufacture stack traffic to equalize a save.
