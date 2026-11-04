# Scenario runtime reset source

The 334-byte native `CScenarioData::reset_runtime_state` at `457E40` is now
individually selected. The exact story-page loader at `4583E0` calls it at
`458415`; its complete body hash and that edge are pinned by
`scenario-runtime-reset-authored-106a`. Recursive decoding reaches the complete
body and its final tail jump to system-effect release `436E60`; that separate
callee remains nonexact and receives no credit here.

The existing source resets checked text-entry state, three owned strings,
scenario counters, three render lists and system effects. It retains narrow
out-of-line interfaces for the three target-observed STL member call sites;
the actual standard container ownership remains in the existing shared header.
The fresh source candidate is 339 bytes against 334 native bytes, with the
first difference at +2 in frame allocation and register lifetime. Equal
semantics or source presence is not a canonical match; no exact bytes are
added. There is no claim of original source spelling or gameplay execution.

Reproduce using `scripts/repo-python scripts/build.py --unit
exact-first-scenario-runtime-reset --compare --json`; mismatch is expected.
The specific origin rule was checked directly; no full origin census was
replayed. See `build/frontier-scenario-reset-register-20261104/compare.json`.
