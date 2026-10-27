# Story progress refresh, 0x0042E3F0

## Result and superseded evidence

The complete existing source now compiles to **860/860 canonical exact bytes**
under its unchanged VC8 O2/GS-off unit. The same object retains the accepted
95/95 event publisher at42E750. No shared header, helper ABI or compiler flag
changed. Both comparisons run through `gpt-web-score-story-progress`.

A fresh baseline reproduced the old876-byte body, first difference42E4E5,
245-byte exact prefix and two extra iterator-owner validations. The new test
uses the actual native `std::vector<int>::clear()` operation on secondary then
primary indices, rather than expressing clear as `erase(begin(), end())`.
That ordinary operation naturally removes the16 extra bytes and reproduces the
whole body; no manual removal of checks, iterator facades or copied bytes.
This supersedes the old pending/TU-stop conclusion for this function only.
The old begin+size experiment does not rule out a true container clear call.

## Target-backed scope

Target remains original Japanese1.06a SHA256
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
The860-byte callable ends with RET0 at42E74B and four separating INT3 bytes.
Raw decode contains316 instructions,315 reachable; the sole unreachable
six-byte LEA alignment at42E6DA is retained in the complete compared extent.
No indirect control edges or remote chunks were discovered. Full body SHA256:
7244a3ee62bd835b17f9abdae49ae34aff70f21c350a99d40b0c4868874db9f2.

Raw CALLs42E79E/42F695/42FD2C from the event publisher, defaults and load routines
independently establish game score ownership. The refreshed attested IDA xrefs
agree; raw PE remains byte/boundary authority. The direct IDA launcher remains
unavailable for its missing MCP runtime, while Factory native IDA is usable.

The retained source counts15 event flags, grants the native prerequisite-based
primary availability, sets aggregate bit100 from event14, clears secondary then
primary index vectors, and repopulates both. If primary remains empty it grants
0/1/2 and rebuilds; if secondary is empty it grants/inserts0..12. The15-cell
views describe the actual loop range, not the complete20-cell nominal owner.
No unrelated gameplay names, ownership rules or return values changed.

## Reproduction and affected scope

```
scripts/repo-python scripts/build.py --unit gpt-web-score-story-progress --compare --json
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ci.py
```

The only source consumer is this unit; the already exact event95 is rerun with
refresh860. Other callers retain the same address and unchanged sources. This
checkpoint uses the authorized new/directly-affected-unit workflow; it does not
claim a fresh whole-corpus cold replay. Prior unchanged receipts remain valid.

Receipts: `build/frontier-42e3f0-20261027/` contains baseline/clear previews,
`target-facts.json`, full disassembly, `formal-first.json`, `formal-second.json`,
origin/progress refresh and `local-ci.log`. The final CI is pending at writing;
use its durable terminal exit file. No new runtime matrix or test suite added.
