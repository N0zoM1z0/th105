# Active result-menu source

`CMenuResult::update_active` at `0x4472A0` is now canonical exact across its
complete 619-byte callable, using `exact-first-result-menu-active` and pinned
VC8 SP1 `/O2 /EHsc`. The full native control-flow walk covers 175 instructions,
27 direct calls and four returns, with no unreachable gap. The exact 43-byte
`0x447560` wrapper supplies the owning tail edge. Authored ownership remains
established independently by `ui-input-result-policy-authored-106a`.

## Recovered contracts, November 9, 2026

- Character selection uses the real checked `std::vector<int>` subscript,
  rather than a manually expanded guard. The existing 16-byte storage view
  agrees with the native allocator/begin/end/capacity layout.
- The three parallel result containers are borrowed through one typed view:
  `deque<int>` at `+0xCC` and `+0xE0`, then `deque<short>` at `+0xF4`, with a
  `0x108` record stride. These are the same types and offsets used by the real
  population source. No view is constructed and no shared object layout changes.
  Reading the fields directly removes the old accessor-return register artifact.
- Replay setup clears the actual short deque at setup `+0x30`. Its real
  `thiscall` `_Tidy` is native `0x420A80`, not a fabricated fastcall buffer API.
- Menu installation calls the actual C++ `push_ui_selection_menu_facade` at
  `0x43B0F0`, whose exact five-byte body forwards to checked list insertion at
  `0x4406F0`. The old `extern "C"` declaration suppressed the throw contract
  under `/EHsc`; C++ linkage restores the native `-1` new-expression EH state
  before installation, including the allocation-null path.
- Confirm, profile and cancel are mutually exclusive branches. A negative
  replay skips setup and reaches the final true return. This recovers all four
  native return sites without dummy returns, padding or compiler-option trials.

The earlier 620-byte source differed at `+81`. Replacing only the selection
vector and install declaration left a 600-byte candidate; real deque clearing
restored the two-byte receiver preparation. The native branch structure and
actual result fields resolve the remaining differences. Getter-based views
remained nonexact even when they had the same total size.

## Complete verification

Callable SHA-256:
`f95a8af2443985dabebcfdda804b1b71ab603c8444e17303c2a349e8b5bbe0a1`.
The full EH section at `0x6B9A90` is 38 bytes, including the allocation cleanup
funclet and handler. Its complete 44-byte metadata section begins at `0x6DF7F0`.
Every code and absolute relocation is replayed against the pinned Japanese
1.06a executable, with zero differences in both sections.

The emitted short/int deque subscripts (100 bytes each), short deque teardown
(104), push_back (119) and map growth (344) also match their real native bodies.
The direct wrapper and menu-install facade/stack are freshly rebuilt and exact.
The separate result initialization body remains nonexact; it was not changed.

Reproduce the root with: `scripts/repo-python scripts/build.py --unit
exact-first-result-menu-active --compare --json`. Only the 619 authored callable
bytes are newly credited. No gameplay or integrated runtime test was run.
