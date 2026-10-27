# Replay filename pattern expansion, 0x00429B70

The first complete source matches **1323/1323 bytes** under unchanged VC8 O2/GS.
Its directly affected same-TU caller42A560 remains1322/1322. Both are compared
by `exact-first-replay-filename`; this is not whole-corpus replay.

## Target and ABI evidence

Canonical Japanese1.06a SHA256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.
The1323-byte body ends at RET16 42A098 with five separating INT3 bytes.
455 instructions decode,454 are reachable; the three-byte LEA alignment at
429E9D remains compared. There are no indirect jumps or remote chunks.
All65 COFF relocations replay. Whole-body SHA256:
9ce6204a02bce00fcf83893d69005bee07be14fb8ec49ecb05ed00949a50d1a4.

The already exact replay filename builder calls42A68A/42A6AD with its receiver,
a live std::string pointer, config key and two nullable player-name pointers.
It does not use a returned value. The complete source uses void, preserving the
native incidental EAX values without inventing a return expression. Supported
name/prototype metadata was written to attested IDA and read back; no byte patch.

## Source semantics

The implementation is added to `src/battle/ReplayFilename.cpp` using genuine
VC8 string find/replace, CRT multibyte search, native time/tm and a260-byte local
formatting buffer. It keeps the original eight replacement loops, not a generic
formatter abstraction that would change evaluation order or code generation.

- Slash/backslash checks inspect the existing output string before reading the
  configured pattern. A match assigns empty and returns. This is not validation
  of the subsequently loaded INI value, and is not silently strengthened.
- Read the replay section/key into the buffer, then assign the output string.
- Replace d1/d2 date tokens, t1/t2 time tokens, p1 then p2 player-name tokens,
  and c1 then c2 character tokens in that exact order. Every search restarts at0.
  No replacement-count guard or recursive-token protection is added.
- Nullable player pointers skip their loops; second-player/second-character
  replacement additionally requires the native versus byte at+EC.
- The first character in story mode receives the native `_story` suffix. Both
  character bytes are sign-extended. Slot0 is read through the native checked
  vector at+F4 with independently established80-byte envelope stride. The local
  record is read-only partial storage, never constructed, copied or allocated.

New complete-NUL literal mappings are pinned by canonical callsite immediates
and matching COFF literal bytes. String/CRT/INI/character lookup callees gain no
new authored implementation credit. Original names/full owner layout remain
unknown. No assembly, padding, artificial liveness or ABI coercion is used.

## Reproduce

```
scripts/repo-python scripts/build.py --unit exact-first-replay-filename --compare --json
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/ci.py
```

`build/frontier-429b70-20261027/` retains the first complete source/object
comparison, target disassembly/facts, formal-first/second.json and final-CI
log/exit. Final CI is pending at writing; its terminal receipt determines the
checkpoint. Only the shared caller/helper unit is rebuilt. No new runtime
matrix or actual INI/file operation is executed by these static comparisons.
