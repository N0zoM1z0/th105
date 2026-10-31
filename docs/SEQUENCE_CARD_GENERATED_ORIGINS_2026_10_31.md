# Genuine sequence-card compiler origins

The broad emitted-symbol scan found a143-byte implicit sprite assignment and
515-byte checked deque range erase in an old sequence-advance control object.
That object was not accepted: its source control had been restored out.

A new explicit compiler-origin probe now reuses the actual independently exact
FighterSequenceRotate.cpp card/sprite declarations and asks the original VC8
std::deque to erase a range. This is a compiler-instantiation witness, not a
fabricated gameplay caller, replacement for the native advance function or a
way to force register allocation in an authored root. No source copy body,
manual vptr assignment, dummy iterator or machine code is introduced.

Pinned /O2 /GS now reproduces both entire canonical bodies:

- 45CFB0/143: implicit SequenceRotateSprite94 copy assignment. The ordinary
 compiler operation copies real fields and preserves destination dynamic type.
- 45D830/515: checked deque<SequenceRotateCard>::erase(iterator, iterator),
 including both range-copy directions, real element teardown, every check,
 return iterator and all absolute/relative relocations.

The public vc8-sequence-card-library-origin unit compares all658 bytes.
Full-inventory source fingerprints independently pass unchanged0.70 minimum
coverage,24-byte minimum, no alignment tail and complete unique hit sets. The
source's exact nominal template spelling is a recovered view, not claimed as
unique original text. These two bodies are compiler exclusions only.

The directly reused selected rotation265 and implicit copy116 freshly replay
exact, as do all96 generated rotation support bytes. Source, existing profiles,
shared declarations and verification tools are unchanged. The failed advance
163/168 controls remain failed and unselected.

Receipts under build/frontier-sequence-generated-20261031: formal.json,
rotation.json and rotation-auxiliary.json. The source-origin validation is in
build/frontier-boost-library-20261031/vc8-generated-sequence-card-lifetime-106a-validation.json.

Exclusions become1782 and review449; units761. Exact1578/448979, source1776,
authored1796 and mapped1803 are unchanged. No compiler bytes count as game
matching progress.
