# CDesignBase cleanup and gauge controls

Historical source-present checkpoint. The later
[complete310-byte exact reconstruction](DESIGN_BASE_CLEANUP_EXACT_2026_10_21.md)
supersedes the cleanup source/type/context and nonexact status below. The
gauge controls keep their recorded source epoch.

Target: original Japanese TH10.5 v1.06a, SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
This checkpoint adds complete cleanup source; **no exact function is added**.

## Observed cleanup

`40BB40..40BC75` is310 bytes/119 instructions, SHA256
`5c8d5c4c66df8434fe8eeeb2277cac7a1960ce07de381c57e844b35bbc4502a3`.
CDesignBase primary RTTI and vtable6C08AC own slot14 at6C08C0.
All119 instructions are reachable when the unconditional error transfer
`40BC25 -> 40C350` terminates its path. That separate vector-at failure
constructs `std::out_of_range`; its string/ThrowInfo and unresolved compiler
context are documented in
[the collision preparation audit](COLLISION_GEOMETRY_PREPARATION_2026_10_19.md).
It receives no new origin exclusion or exact credit.

The function deletes the object at the **back** of list+14 and pops back,
repeating until empty. It then releases every handle from vector+4 in
increasing index order, using checked `at` and the normal public115-byte
release404D70. Finally it erases the vector's begin/end range. Neither the
map+20 nor persistent iterator+2C is reset. Source preserves those observed
side effects and uses native containers and virtual deletion.

```bash
python3 scripts/build.py --unit gpt-web-design-base-cleanup --compare --json
# Expected exit1: complete315-byte ordinary source is nonexact at+0.
```

The source omits the target's aligned EBP frame. Native scalar-vector erase
also retains a compatibility check and calls `memmove_s`, while the target
contains an assignment loop. This leaves original element type and TU/compiler
visibility open; the existing unsigned-element declaration remains a hypothesis.
A private four-byte aggregate-element control instead outlines native erase
and blocks on that unqualified helper. It does not justify changing the shared
header. RTM and SP1 produce identical normalized315-byte cleanup candidates.
No frame padding, handwritten container internals or private-register facade
is introduced. The inherited assembly release implementation is not included.

## Gauge experiment result

The current complete source for initializer41B280 is unchanged. Two additional
genuine caller/callee parameter-order controls and an RTM compiler control all
produce the same normalized360-byte function as SP1, SHA256
`52572feed070b2da682c1b4727319d2a6118f655d32d32d9630b197f5affb1bc`.
Each remains nonexact at41B285/+5, with mode inECX rather than targetEAX.
This rejects these specific explanations, without an impossibility claim.
The parent40B000 still blocks on unqualified local EH; neither function gains
exact credit.

## State and reproduction

`src/ui/DesignBaseCleanup.cpp` and its focused unit are source-present.
The new positive authored rule pins the complete target body and vtable cell.
All198 predecessor origin selectors remain unchanged and disjoint; the new
bounded witnesses pass. No shared header, existing unit, relocation ledger or
accepted source changes, so no predecessor unit needs rebuilding. There is no
cold aggregate replay or aggregate exact claim.

Cleanup evidence and recipes are under
`build/design-base-cleanup-20261021/` and its corresponding `.analysis/` scope;
gauge controls are under `build/gage-initialize-matching-20261021/`.
Cleanup source SHA256:
`cbf04850c56c45cb3d09d48c11f6217a7d01d031b0474eed145679f80e2872b9`.
Formal COFF SHA256:
`4f4f9dedee9f83ed8ca64721fdafbbbaffb004d7a04afee591b85b704574dedd`.
IDA preflight rejects the wrong image; all new observations use the canonical
PE. Builds are serial on CPU0 at nice10. Next: recover genuine texture-release
provider visibility for the larger design lifetime/loading context.
