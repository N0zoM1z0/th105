# Font end/reset exact in their real CIL context, 2026-10-22

`TextFont_finish_text_render @ 411AD0` is newly accepted168/168 and
`TextFont_reset_markup_color @ 4118F0` is newly accepted162/162. The unchanged
owner/render source in the existing genuine LTCG image preserves EDI across
the same complete scopes as the target. No C++ source, ABI facade, padding,
forced export, compiler flag or canonical comparison rule changes are needed.

Only original Japanese1.06a is used, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
IDA again rejects its unrelated open executable. The attested PE supplies
target observations; the pinned VC8 build supplies actual linked code.

## Concrete native versus linked results

The existing `TextFontLinked.cpp` includes the real owner and render sources.
The renderer is an actual exported root; end/reset are genuine file-local
typed definitions reached from it, directly or through markup. They remain
unexported and receive their actual ESI owner contract naturally. No synthetic
caller or private-register declaration is introduced.

| Function | Ordinary native diagnostic | Actual CIL result |
| --- | --- | --- |
| end411AD0 |168 bytes, e1daa198, nonexact+7|168/168 exact,68b02c0e |
| reset4118F0 |161 bytes,261fc985, nonexact+7|162/162 exact,8b90f385 |
| begin4119A0 |291 bytes,728a7bf3, nonexact+7|291 bytes,f9651374, nonexact+59 |

Ordinary end saves/restores EDI around only its nonempty-list loop. The target
and linked body save it before the branch and restore it after handle cleanup.
Ordinary reset similarly releases EDI before color restoration; target and
linked code retain it through both real tails, with the target's complete
162-byte extent. All existing list, GDI and color behavior stays in genuine C++.

Begin's linked64-byte metric frame/save scope agrees with the target, but
publication of the returned font relative to the HWND read still differs.
It remains selected in the native unit and receives no exact credit. Neither
matching size nor partial frame agreement is acceptance.

Full canonical hashes:

| Exact function | SHA256 |
| --- | --- |
| end168 | `68b02c0e179c843e68bb474274a6e27b31038d81e97a900afe08ed54af9083b7` |
| reset162 | `8b90f385b2069c2a33647ee19cf5d92e31a1cefcd5f28ebcd5acc8249afe2171` |

End replays four named E8 fields and four attested data references. Reset
replays four E8 fields without absolute data references. The ordinary
`operator_delete` COFF role becomes the actual pinned runtime import spelling
`??3@YAXPAX@Z`, retaining target6898EA; no new callee address or library credit
is added. Both complete bodies close under the existing strict CFG and
HIGHLOW/operand checks. No byte, alignment, RET or relocation is excluded.

## Explicit ownership of the static leaves

The actual map labels end/reset `CIL library: CIL module` in its `Static
symbols` table. That label alone is insufficient to establish ownership.
The existing named-object entry check remains unchanged and rejects them.
The linked verifier now supports a separate `private_static_leaf = true`
contract only with an explicit included-source path:

- Source file must be an actual quoted-include dependency of the configured
  one-input import-runtime CIL build. The leaf and each caller must have
  reviewed source in that same file.
- The exported anchor retains its unique named CIL-object identity. Every
  static intermediate and leaf must have one symbol/VA, the exact static map
  owner, a matching `Static symbols` entry, and no aliases or exports.
- Each full source/target caller CFG must have one reachable E8 to the next
  body, at the recorded target site. The exported anchor must map that actual
  callee. All source address operands and relocation fields retain checks.
- Only after this witness succeeds can the ordinary complete leaf byte/CFG/
  relocation comparison run. A zero-intermediate path is allowed exclusively
  for this explicit static-leaf form; previous empty ordinary paths still fail.

End's path is renderer412670 -> end411AD0, target call412783. Reset's is
renderer412670 -> markup411FA0 -> reset4118F0, calls41276A and41260F. In the
fresh image their leaf VAs are10001730 and10001D70. Actual source callsites
are1000259C and1000241B respectively; the parser is reached at10002577.
These addresses are build observations, not original nominal identities.

Four new tests cover direct/intermediate successful paths and reject missing
reviewed leaf source, wrong or missing calls, foreign/duplicate/exported map
entries, missing static tables, unqualified role flags and forced exports.
Existing tests continue to reject bad source dependencies, cycles, cropped/
unreachable callers and unsupported/incorrect address relocations. The strict
named-object helper still rejects a generic CIL owner, even with the new flag.

Caller witnesses attest normal CFG, ownership and address roles. They do not
accept renderer335/+19, markup, EH handlers/unwind or whole GDI execution.
No source-body or same-name/map-only shortcut substitutes for the final full
canonical equality.

## Selection, replay and limits

The two descriptors move from `gpt-web-text-font-render` to the existing
`gpt-web-text-font-color-linked` unit, with one selection per address. Eight
native comparisons remain; public source/header/profile and emitted native
alternatives are unchanged. Existing linked color411790 stays352/352.
The two provisional authored-origin rules are retired for their canonical
match-origin rows; authored/source counts and byte denominator stay unchanged.

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-text-font-color-linked --compare --json
python3 scripts/compare-linked-unit.py gpt-web-text-font-color-linked --address 0x00411AD0 --json
python3 scripts/compare-linked-unit.py gpt-web-text-font-color-linked --address 0x004118F0 --json
taskset -c 0 nice -n 10 python3 scripts/build.py --unit gpt-web-text-font-render --compare --json
```

Whole mixed units intentionally exit1 for nonexact candidates. Selecting
either new leaf yields exact after repeating its complete actual caller path.
Because ownership verification changed, all10 accepted linked units plus the
native font unit receive serial cold replay:11 units/25 accepted functions.
This is a scoped replay, not a new all-unit aggregate claim. Prior576 end and
240 reset observer cases retain their native source epochs; no new arbitrary
alias, real GDI, allocation-failure or EH execution claim is made.

Evidence is under `build/font-edi-scope-20261022/`: `existing-context.json`,
`selected-linked-build.json`, `scoped-replay.json`, focused reports and logs.
Private `capture.py` and `replay.py` remain in the corresponding `.analysis/`
directory. Actual configured public linked/native inputs remain available.

The ledger gains two functions/330 bytes:1,381 exact/234,914 bytes, authored
denominator2,136,806 (10.99%). Glyph624/+89, markup and Reimu496540 remain
pending. Next inspect begin's concrete font-publication/HWND-read order in
the genuine context without changing its source on frame agreement alone.
