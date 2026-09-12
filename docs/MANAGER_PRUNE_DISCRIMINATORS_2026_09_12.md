# Shared manager prune: bounded negative controls

This is a **nonexact** investigation, not additional authored progress.
Source at checkpoint `38bf8c2` remains unchanged:
`CharacterObjectManagerBaseRuntime::update_and_prune` in
`src/characters/CharacterObjectManagerRuntime.cpp`.

## Fresh evidence

Target: original JP 1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Fresh preflight and IDA packet:
`build/manager-prune-current-preflight.json` and
`build/manager-prune-current-typed.json`.
The bounded body is `0x0058BE10..0x0058BEDE`, 207 bytes, ending with RET 8.
IDA reports caller site `0x0058BF4F` in the shared update wrapper `0x0058BF30`.

The source invokes the two-word multiple-inheritance member pointer, checks
the object's state at +0x330, releases its handle at +0x334 if inactive,
then erases the native checked-list iterator. A single-function source copy
including the existing runtime header independently reproduces the production
discrepancy. Nothing depends on compiling unrelated manager methods.

Canonical target body hash:
`604fd9653a8afa45c8eb1a1293c76c7f7233460c07c35384fd4067a68844598b`.
The 207-byte baseline comparison hash is
`6af113e1d91700990344018fbb3ef1742cf1f97b84000871670c4d67f2dd76cc`,
with first mismatch +0xA5. The final native list unlink uses EAX/ECX/EDX
in the target where the candidate rotates those scratch roles. This is
still a whole-function failure, not a permitted register-normalized match.

## Measured source/compiler distinctions

| Private probe | Result against the complete 207-byte boundary |
| --- | --- |
| Unchanged isolated method, SP1 | 207 bytes; first mismatch +0xA5 |
| Same method, pinned RTM compiler and C++ headers | Same 207-byte comparison hash as SP1 |
| Native `template<class Object>` manager with the same vtable/pool/list field order and explicit instantiation for the existing MI object view | Same 207-byte comparison hash |
| Active-state arm increments and `continue`s, followed by the inactive release/erase statements outside the `if` | Same 207-byte comparison hash |
| Replace `it = list.erase(it)` with `list.erase(it++)` | 207 bytes but different entry/frame, first mismatch +0x00 |
| Put `state == 0` release/erase arm first and increment in `else` | 210 bytes; first mismatch +0x29 |

The template test changes the real class/source instantiation contract, not
the machine calling convention. It does not explain this mismatch. The RTM
media and executable hashes are documented in [VC8_RTM_PROBE.md](VC8_RTM_PROBE.md).
The postincrement test changes the lifetime of a genuinely used iterator;
its different frame is evidence against that spelling, not an invitation to
add dummy storage. Both branch tests preserve ordinary loop semantics.

Private files and JSON reports are under `build/manager-prune-*` with suffixes
`baseline`, `rtm`, `postincrement`, `continue`, and `zero-first`. The template
object uses the same method body in `NativeManager<Object>`, a dependent
`std::list<Object *>` and `typename ObjectList::iterator`. Its decorated symbol
is passed explicitly to `compare-function.py` with the existing unit's three
REL32 mappings. None of these probe objects is recorded as an accepted build.

For focused baseline comparison after compiling just this method with
`scripts/compile-unit.sh`, reuse the unchanged unit contract:

```bash
python3 scripts/compare-unit-object.py gpt-web-character-object-manager-runtime \
  build/manager-prune-baseline.obj --address 0x0058BE10 --json
```

These results rule out the tested spellings and this RTM/SP1 distinction for
the current source. They do not prove an LTCG barrier or exhaust historical
TU visibility and source contracts. No shared header, production source,
compiler flag, relocation mapping, origin row or exact ledger was changed.
Continue with new target-backed evidence rather than repeating these probes
or forcing the three scratch registers.
