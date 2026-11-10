# Replay header reader: exact main and exception scopes

The Japanese TH10.5 1.06a replay-header reader `0x00429A30` now matches all
313 original callable bytes. Its source creates the real local filename string,
appends the supplied path, opens a plain file, reads the first four bytes and
returns that value, or returns -1 if opening fails. The exact replay-list
formatter calls it at `0x0042A296`. The real 12-byte polymorphic file lifetime
is shared unchanged with the already exact replay filename builder; no manual
vtable, synthetic storage, fabricated call target or forced register is used.
The original nominal source type and translation-unit layout are unknown.

The decisive source shape is the genuine empty-string construction followed
by an append and the existing concrete plain-reader lifetime. Earlier standalone
hypotheses had stopped at roughly 293/313; the actual shared lifetime and
string behavior naturally produce the full result. The native routine does not
check the file-read result before returning the local value. This is a faithful
reconstruction of the observed code, not a claim of safe malformed-file or
short-read behavior.

The original body and the independent cold rebuild both hash to
`7b806a89700b2d3f9220e0848a68b5c1fe52be0684658414d8821421eb3663f3`.
A separate provenance-gated audit replays the complete 48-byte remote cleanup
and handler section at `0x006B7B40`, and the complete 44-byte unwind map and
FuncInfo at `0x006DDC58`. All code, relocation roles, action, state count and
metadata fields agree. These remote regions are proof of scope, not extra
credited authored bytes. No OS exception unwinding or real file I/O is executed.

The configured and cold bodies, exact 501-byte replay formatter and 159-byte
constructor, and exact 1322/1323-byte filename builder/pattern functions all
replayed after extracting the unchanged shared reader class. Scoped origin
materialization changed only this entry to canonical exact; it did not rerun every
unrelated origin evidence validator.

Reproduce serially with `scripts/repo-python scripts/build.py --unit
exact-first-replay-header-read --compare --json` followed by
`scripts/repo-python scripts/audit-replay-header-read-eh.py`. This adds one
function and 313 authored bytes, not a full application-link claim.
Target-independent CI passed 1,027 tests, including mutations of every byte of
the complete metadata fixture, and generated-progress/whitespace checks.
