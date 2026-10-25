# Collision debug geometry 0x0045E950

The complete3087-byte function is canonical exact from ordinary pinned VC8
source in `src/battle/CollisionDebugGeometry.cpp`, unit
`exact-first-collision-debug-geometry`. Two independent public builds and the
full-section object audit reproduce target SHA-256
`3aaec51dd009afb0b872650367815c5ea99d67598017ad342423cc5d6bb63e5a`
with zero differences. This accepts one authored function/3087 bytes. It grants
no source-selection, exact or origin credit to the drawing providers.

## Observed target evidence

Fresh target/ledger preflight used only original Japanese1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
The wrong GUI IDA again failed identity attestation. Analysis used the verified
raw PE, with no IDA/Ghidra semantics or target writes.

The complete `45E950..45F55F` body contains892 instructions,891 reachable.
The sole unreachable instruction is the seven-byte LEA alignment at45EB59.
All branches stay within the body, there are no indirect calls/jumps, and the
only RET0 is45F55E. One following INT3 separates the independent45F560 entry.
The scalar frame is1C bytes, with EBX/EBP/ESI/EDI saves and no EH/GS prologue.
Full COFF section size equals the independently closed target size.

Exact18-byte manager wrapper53B1A0 materializes code45E950 with a zero member
this-adjustor, shifts its manager receiver by4 and calls exact72-byte checked
list dispatcher58BEE0 at53B1AC. Wrapper SHA is
`c3b8386db90175da16d4b04aacee8d9fdf3aad7f5ee1b6775808fd67d723cfbc`.
The public audit pins both complete bodies and the actual pointer/adjustor/edge.
The existing manager interface calls this an int-returning callback, whose
result is ignored. The new void receiver view leaves that shared declaration
unchanged; the original nominal return type and class spelling remain unknown.
No fake return is added.

The body has20 static line-call sites to401180 and one filled-rectangle site
to4012A0. Runtime line count depends on the two loops and selected alternatives;
20 is not a fixed number of lines per invocation. The148-byte line provider
ends in RET20; both395-byte rectangle exits use RET24. Their full target hashes
and argument cleanup are independently pinned by the audit. They retain their
prior nonexact/source-selection state.

## Observed geometry policy

- Optional rectangle pointer+32C draws four axis-aligned edges in packed color
  FF00FFFF. Coordinates add camera offsets6FBCCC/6FBCD0 and multiply scale
  6FBCD4. These globals use their existing loader-zero virtual-tail mappings.
- Frame pointer+158 leads to the16-byte-element vector at+58. A nonzero size
  enables a loop controlled by signed count byte+1B0. Rectangles advance16 bytes
  from receiver+1B4; optional split pointers advance4 bytes from+318.
- The second gate adds vector+68 size and the boolean of pointer+194. It then
  requires DWORD+180==0 and signed byte+184>0. Its signed count byte is+1AF;
  rectangles begin+204 and split pointers+304. The addition remains arithmetic,
  preserving the actual zero test rather than replacing it with a logical OR.
- Each loop keeps the observed null rectangle-address test. A missing split
  draws the four axis-aligned edges. With a split, four DWORDs are captured once
  before rendering: `(ux,uy,vx,vy)`. Edges join LT to LT+u and LT+v, and RB to
  RB-u and RB-v. Rectangle fields and camera values reload around draw calls.
  The first loop uses packed color FF0000FF; the second uses FFFF0000.
- If pointer+168 equals this receiver, signed WORD+49E is multiplied by signed
  facing byte+104 and capped above at300. A filled FFFF0000 marker spans X to
  X+width, with Y transformed as cameraY-Y and cameraY+(4.0-Y). The4.0 operand
  is the existing double literal at6C0CC8; negative widths are not clamped away.

This game-specific collision/count/owner policy plus the exact manager callback
establishes authored ownership independently of compiler/library signatures.

## First whole comparison and one correction

The first complete source was immediately compiled and compared over all3087
bytes. The first strict attempt stopped at the unbound line interface. Binding
both target-observed drawing providers through ordinary REL32 replay exposed
exactly one unequal byte, at45F497: native `cmp edi,eax` versus emitted
`cmp eax,edi`. The source initially said `related == this`.

Writing the observed operand order, `this == related`, makes the complete
function exact. Both are ordinary pointer equality expressions; no conditions,
flags, liveness, padding or register ABI were invented. No further source trials
were needed. Private first source/object/replay and corrected source/object
remain under `.analysis/exact-first-45e950-20261026/` and the matching build
scope. The first complete canonical SHA was
`480532ec359bea88d774d1c8c81177f6e164149d00d044fd27b5e67570678fe8`.

The nonconstructing receiver uses typed offset accesses, actual checked-vector
size behavior, numeric colors and ordinary float narrowing. Split components
are real used scalars. Explicit float casts preserve the target's x87 coordinate
rounding before argument publication. No compiler profile, shared header,
existing global mapping or relocation row changed. The two drawing methods are
declaration-only interfaces at their observed x86 member ABI.

## Reproduction and limits

```bash
scripts/repo-python scripts/audit-collision-debug-geometry-target.py
scripts/repo-python scripts/build.py --unit exact-first-collision-debug-geometry --compare --json
scripts/repo-python scripts/audit-collision-debug-geometry-target.py \
  --object build/match-units/ExactFirst_CollisionDebugGeometry.obj
```

Target and object audits exit0; both public builds report full3087/3087 exact.
Receipts: `formal-first.json`, `formal-second.json`, `public-object-audit.json`.
The initial public manifest check needed its explicit boolean `enable_gs=false`;
that configuration-only error is retained as `formal-config-error.json` and is
not a compiler trial. It does not change the profile used by the first source.

Nominal classes, original source spelling and original TU identity remain
unknown. The byte result does not prove a unique source or propagate exactness
to the primitive renderers or another debug callback. Continue with independent
review of the paired rectangle provider4012A0; prior floating-profile grids
remain closed unless new target or source-lifetime evidence changes the question.

The final `scripts/repo-python scripts/function-origins.py --check` read-back
passes all4024 rows (`origins-check.log`). Full
`scripts/repo-python scripts/verify-exact-units.py --all` passes526 cold accepted
units/all1414 functions, including this3087-byte function (`cold-all.log`).
Current exact authored totals are1414 functions/385903 bytes. The target-backed
floating relocation audit also passes all1999 references (`literals-check.log`).
