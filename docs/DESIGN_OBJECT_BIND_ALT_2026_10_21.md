# UI design-object binding: complete 118-byte exact reconstruction

`UiDesignResource_bind_object_alt @ 0x00420B90` is canonical **118/118 exact**,
SHA256 `663afb38180408beed34f80e9d9c0ddb44feec986aac016287f387669af51541`.
The new ordinary COFF unit is `gpt-web-design-object-bind-alt`. It adds one
authored function; the native tree helper receives no new credit.

Only original Japanese 1.06a SHA256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`
is used. Target/status/tracking preflights pass. IDA rejects its wrong open
image, so all new facts use the canonical PE and pinned VC8 compilation.
No database, target bytes, compiler profile or relocation policy is changed.

## Observed body and source inference

Fresh complete CFG decoding owns all 118 bytes / 44 instructions and reaches
the RET8 instructions at 420BDE and 420C03. Eight preceding and ten following
bytes are INT3 padding. The already-exact profile initializer 43FCA0 directly
calls this entry at 43FDB8; the five-byte edge is independently read back.

The receiver arrives in ECX. Its map begins at +20. A native unsigned-key
lookup calls 40CDA0 with an iterator result buffer and key reference. Comparison
checks the iterator owner against the receiver's map, then compares the node
against the sentinel. End writes null through the first stack argument.
Dereference separately checks the owner/sentinel and writes node+10 through
that output pointer. All three invalid-parameter calls are retained.

`DesignObjectBinding.cpp` uses the real `std::map<unsigned int, UiDesignObject *>`
and native checked iterators in the existing 34-byte CDesignBase physical view.
The signed source ID converts to the map's unsigned key, naturally recovering
the argument-slot lifetime, EDI owner, EBX head and ESI node. It adds only a
nonvirtual declaration to `DesignBaseLifetime.hpp`; data layout and vtable order
remain unchanged. The method name and void source view are supported models,
not a unique recovery of the original nominal API or source partition.

| Complete source | Bytes | Result |
| --- | ---: | --- |
| Retained hand-written tree/iterator facade | 122 | Nonexact at +35 |
| Real native map and checked iterator | 118 | Complete canonical exact |

The earlier facade-based stop condition does not apply to this native source.
This body differs from the independently accepted 121-byte lookup 40CC50:
420B90 naturally has no aligned EBP frame under ordinary COFF. Its acceptance
does not duplicate that function or assume an identical original declaration.

Native member instantiation supplies the genuine ECX/RET8 tree-find boundary;
no external register facade or handwritten iterator checks are used. The full
caller comparison replays the named find and three invalid-parameter E8 fields.
All opcode, branch, stack, store and return bytes are included. Compiler helper
40CDA0 remains excluded from authored progress without new exact credit.

## Verification and retained evidence

```bash
taskset -c 0 nice -n 10 python3 scripts/build.py \
  --unit gpt-web-design-object-bind-alt --compare --json
python3 scripts/validate-tracking.py --require-target
taskset -c 0 nice -n 10 python3 scripts/ci.py
git diff --check
```

The header's actual transitive include closure has 17 accepted units including
the new binder. All **54 predecessor accepted functions plus the new binder**
are cold-built and compared serially; no unrelated unit or aggregate cold
total is claimed. The existing cleanup 40BB40 and all seven render/lookup
functions remain exact.

Facts, retained/native controls, the formal build and per-unit affected replay
receipts are below `build/design-object-bind-alt-20261021/`. The corresponding
`.analysis/` recipe derives the scope from real source dependencies and accepted
addresses. The old `DesignResource.cpp`/Title facade remains an unselected
hypothesis; existing callers and that broad header are untouched. Only the
118-byte binder moves from identified to source-present and exact. Original
API/type spelling and larger resource/loader TU ownership remain unknown.
