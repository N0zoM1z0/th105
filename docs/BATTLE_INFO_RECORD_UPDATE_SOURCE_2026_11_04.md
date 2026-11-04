# Battle information-record update source

The target `0x0046FF30` is a 2,005-byte game-owned gauge and effect update,
called by independently exact normal and story InfoManager updates. Its full
body and those two edges are pinned in `BATTLE_INFO_RUNTIME_ORIGIN_2026_11_03.md`.

The complete source hypothesis covers gauge interpolation, visibility groups,
sequence indicators, and owned effect release/creation. Unlike earlier private
controls, it uses the real checked `std::deque<FighterSequenceSlot>::front()`
operation rather than handwritten iterator checks. Its pointer-only field view
represents the `+0x534` dword as a signed count, which the native update adds to
the signed state byte and compares as an integer. Compile-time checks pin that
offset and the genuine deque's 20-byte physical size. The virtual effect call
uses a typed interface, not a manual vtable.

Fresh VC8 emits a 1,919-byte body and outlines the standard deque `front`
operation, whereas the native body contains its checked logic. That local helper
has no independently established target call binding, so strict comparison is
**blocked**, not an ordinary byte mismatch. No guessed helper, source-byte
percentage or exact credit is added. Source semantics and actual runtime effect
and deque behavior remain hypotheses pending further review. The body size is
not a canonical comparison. Receipts are under
`build/frontier-info-runtime-natural-20261104/`.
The two exact callers and their two same-unit peers replayed exact. The focused
origin rule and all 1,030 target-independent CI tests passed. These checks do
not resolve the new candidate's outlined deque helper or prove gameplay.
