# Exact shared secondary-animation replacement

## Result and scope

`CharacterObjectEffectEmitter::replace_secondary_animation @ 0x00496420` is
**274/274 canonical exact** against original Japanese TH105 1.06a SHA-256
`56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e`.
Its direct callers include 48 sites in nine RTTI-owned roster Object roots.
This is a shared dependency recovery, not a character-completion wave.

Source: `src/characters/CharacterObjectSecondaryAnimation.cpp`.
Unit: `gpt-web-secondary-animation-replacement`, existing `/O2 /GS` profile.
No assembly, extra storage, padding, volatile, fake liveness or custom calling
convention was introduced. The canonical body hash is
`7f23a75bc598a02d6f0b6c23549610b908fa7df5834b1539060899ec352ee111`.
Local report: `build/secondary-replacement-native-formal.json`.

```bash
python3 scripts/check-ida-mcp.py
python3 scripts/typed-re.py 0x00496420 --json
python3 scripts/build.py --unit gpt-web-secondary-animation-replacement --compare --json
```

The root is newly credited for 274 bytes. Compiler-generated find and EH
machinery are not added to authored progress. Three existing sibling methods
remain exact after the source split: release at `0x004963F0` (43 bytes),
alpha at `0x00496370` (35), and flags at `0x00632C10` (27). Their filtered
report is `build/secondary-replacement-sibling-formal.json`. No unrelated
modules or aggregate cold rebuild were run.

## Fresh observations

The attested IDA packet reconciles the complete main body and its associated
remote EH code. The main body saves FS:0, reserves eight local bytes, and
performs ordinary deletion/new construction of a 0x54 renderer at owner
offset +0x338. The allocator cleanup slot is at ESP+0x0C after the prologue.
Later the iterator result buffer uses that same slot, after new construction
has finished and before the tree call at `0x004964AD`.

The int argument is sign-normalized through a 16-bit value before its address
is passed as the key. The returned iterator is checked for a valid owner and
against the end node. Its node's value at +0x10 points to a block containing a
checked vector of 0x88-byte frames. Selecting frame zero preserves the exact
null/size checks and the multiplication-based element-count division. The
real renderer initializer is then called with the original five arguments
and owner/frame pointers. The main RET at `0x0049652F` pops 0x14 bytes.

The target EH cleanup at `0x006BBC00` frees the allocation on constructor
failure. The handler at `0x006BBC0B` uses the matching eight-byte-frame cookie
and unwind offsets. Native source generates those same observed offsets;
the 274-byte authored comparison does not add the remote compiler machinery
to its byte count.

## Cause of the old stack discrepancy

The retained facade declared a caller-owned POD iterator and an explicit
output pointer to a method named `lower_bound`. It produced 274 bytes but
reserved twelve local bytes, keeping the allocation cleanup slot separate
from the eight-byte iterator. Rebuilding only that old function independently
confirmed the discrepancy; it was not a stale report or surrounding-TU effect.

A by-value POD-return facade does not solve it either. Although its member-call
ABI also uses a hidden result buffer, it retains the twelve-byte frame and
accesses the known stack result directly: 278 bytes. Merely changing a return
declaration is not equivalent to recovering the original native iterator.

The actual VC8 container expression is sufficient:

```cpp
typedef std::map<int, AnimationSequenceBlockVectorView *> SecondarySequenceMap;
AnimationSequenceBlockVectorView *const block =
    reinterpret_cast<SecondarySequenceMap *>(sequence_tree_160)->find(key)->second;
AnimationSequenceFrame &frame = block->frames_00[0];
```

Its real temporary checked iterator and dereference implementation let VC8
reuse the completed new-expression cleanup slot. This naturally produces
the target eight-byte frame, EAX-to-ESI iterator return use, every stack
displacement, and the complete main function. The native map is 0x0C bytes;
the older `AnimationSequenceTree` is only an eight-byte prefix view, not a
complete native map layout. The checked vector block remains 0x20 bytes.
Compile-time assertions pin these native sizes without altering shared headers.

This explains a reproducible compiler/source distinction, not unique original
class names or exact historical TU partition. The new source has a dedicated
unit so the successful native STL visibility does not become a global change.

## Independent compiler-library witness

The target at `0x0045C320` was previously classified as generated VC8
`std::_Tree::find`, with an int/byte specialization anchor in
`config/vc8-generated-int-byte-tree-origin-anchors.toml`. A fresh 105-byte IDA
packet and the pointer-valued specialization emitted by this new source agree:
**105/105 canonical exact**, with comparison hash
`3be84050d552bc5febe06a6be1b509ce5db9dd0cc3a4d6ea9b57ade5bde24229`.
The misleading old facade name is not used for the new source's call mapping.
The library helper retains its existing exclusion; matching it is not game
authorship evidence.

Reproduce that check using the new unit's exact decorated find symbol:

```bash
python3 - <<'PY'
import subprocess
import tomllib
with open('config/match-units.toml', 'rb') as stream:
    unit = tomllib.load(stream)['units']['gpt-web-secondary-animation-replacement']
symbol = next(mapping.split('=', 1)[0]
              for mapping in unit['functions'][0]['rel32_targets']
              if mapping.startswith('?find@'))
raise SystemExit(subprocess.call([
    'python3', 'scripts/compare-function.py', '0x0045C320', unit['object'],
    '--symbol-base', symbol, '--json']))
PY
```

The following shared root to investigate is the 2,434-byte secondary-animation
update at `0x004309F0`. This result makes native checked-iterator lifetimes a
concrete source hypothesis there, not permission to impose arbitrary stack
slots. CPU `0x005F1F80`, common Fighter `0x004740C0`, and that update root are
still nonexact.
