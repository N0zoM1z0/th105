# AyaObject903 shared-tail placement controls

Follow-up to [shared fade recovery](AYA_OBJECT_903_SHARED_FADE_2026_10_22.md).
The selected source at018e8fc is unchanged. Four complete-root VC8 controls ran
serially at CPU0/nice10 against hash-attested original Japanese1.06a. Startup
verification/status/tracking passed; the known wrong-image IDA session was
rejected and not used. No exact credit or accepted-unit contract changes.

## Target edges and hypotheses

The target's shared alpha/store path belongs physically to sequence2, reached
from sequence3 at61E921. Its low-alpha branch at61E837 is JB61A359; the shared
color tail begins61E83D and sequence8 jumps there. Target61A359 is the existing
15-byte lifetime-decrement/return path also used by action800's phase/owner/
coordinate guards. This is an actual shared edge, not merely similar returns.

The selected candidate still places its alpha/store block after sequence3,
uses JAE to the color tail owned by sequence8, and owns a local low-alpha RET.
The goal of these controls was to recover those physical choices without
changing the newly recovered alpha-read lifetime.

## Complete builds

| Control | Full bytes | Canonical SHA256 | Result |
| --- | ---: | --- | --- |
| Sequence2 falls directly into shared store; initial-phase branch breaks |20036|623294c32b653875c56df1232a75948b08525755d3e660d3afdce43ea481902d|Byte-neutral|
| Sequence3 falls directly into shared store placed after3 |20036|623294c32b653875c56df1232a75948b08525755d3e660d3afdce43ea481902d|Byte-neutral|
| Low alpha explicitly jumps to existing action800 coordinate-retirement label |20040|edae9b3223308d95e54f3c603770159bb7aacede636f38dd9a0902b040e5961b|Rejected|
| Move complete sequence8 source before2 to test color predecessor ordering |20036|cf73e5f2914385e38c41eab4b3875b8531ae2a30c53eddb7f42c185df46ea555|Rejected|

The first two results equal the complete selected payload, not just the first
comparison window. Lexical fallthrough versus GOTO did not change this merge.

The explicit retirement label makes9031688 bytes/361 instructions, but grows
the whole root by4 bytes and moves its entry from offset17444 to17457. The
candidate still has JAE-to-color and a local return after the shared store.
Several owner-health, owner-action/sequence and boundary-retirement branches
now target that903-local return, opposite to the intended existing early-root
tail. The label did not fix a physical owner in place. No dynamic equivalence
claim is made for this unselected control.

Moving sequence8 earlier keeps9031696 bytes/361 instructions but also moves
its instructions earlier physically. Its SUB AL/color stores remain there;
the2/3 alpha guard branches backward to that sequence8-owned tail. The target
requires sequence8 in its later position and the color tail after sequence2.
This control changes order without recovering the observed ownership.

These are negative controls for these specific source shapes. They do not
establish standalone native impossibility or a requirement for LTCG. Further
work needs a distinct lifetime/merge-context lead; repeating these fallthrough,
retirement-label or predecessor-order spellings adds no evidence.

## Selected state and reproduction

A final configured rebuild still has full20036 and the selected canonical
SHA256623294c3 above. Comparison remains nonexact at offset34/hex22,
target0F/candidate3B, compared-window SHA256
`5456dd932b8d71d0fcc7ffbc58c3bb4ce3495d6cc1ef2ddb95dd5aa1c73f27d0`.
The14-byte read/store recovery and previous3168 native/4463 other-path graph
results remain tied to unchanged selected inputs. They were not rerun or
claimed as new validation of the rejected controls. Exact totals remain1381
functions/234914 bytes; no aggregate replay claim.

Recipes and complete CPP inputs:
`.analysis/aya-903-tail-placement-20261022/{probe,retirement,color-order}.py`
and sibling source files. Build/comparison/provenance receipts, owner reports
and final `selected-formal.json` remain under
`build/aya-903-tail-placement-20261022/`.

Eight completed private OBJ/BIN files were archived into `completed-controls.tar.gz`
in that build directory:240624 bytes to64375 bytes. Every decompressed member
length/SHA256 was checked before deleting the originals. The manifest is
`archive-verification.json`; archive SHA256:
`5e3192866645e5ac0831519790293e082dd587395a2135caa54f75fd9d5dd2f9`.
Recipes/CPPs/JSON receipts and the configured object were retained. Restore
archive members before re-running a private owner audit.

Final gate: `python3 scripts/ci.py` followed by `git diff --check`. Neither a
source-present mapping nor these diagnostic/control results constitute exact
acceptance. The full large-function objective remains open.
