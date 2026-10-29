# Complete Character destruction, JP1.06a

462CE0 now has complete905-byte source selected. It remains nonexact in one
byte, so none of these905 bytes is added to the exact ledger.

Native SHA256:da514c9794ee2bc53351b4f4f246b76e45ebdce219411e81f603ff77014b7f35.
Source SHA256:352716b40062c2f2437d4d50ffb824ac3fdf14cc39725d1531342cf82b302e1f.

Exact CharacterEx scalar destruction64B770 calls it at64B779, and the exact
normal CharacterEx destructor tail-enters it. Native republishes the abstract
Character vtable6C2BE4, then performs actual resource/member/base destruction.
This is game-owned lifecycle policy, not generic-container ownership inferred
from a pattern.

## Complete boundary and source ownership

The905-byte extent includes the first main RET at462FB6 and the remote
texture-deque loop462FC0..463063 after it. Checked vector and deque failures
tail-enter40C350 and431610. Raw normal CFG covers264 instructions/890 bytes;
all15 other bytes are retained and compared, including the unreachable
jump/alignment span after the first RET. No remote loop or error path is cut.

The source releases:
- Every texture in the owned vector at base+130, then clears it.
- Every texture in the deque at+68C, then clears it.
- Texture+338 and all64 wave handles through the newly exact401BD0 release.
- The wave array, virtual object manager+658, vector owner and action map.
- Real history, texture, phase-render list, PAT-group and sequence members,
  spell resource containers, cut-in sprite resource and AttackObject base.

The source uses ordinary delete/delete[], standard containers and actual
visible AttackObject destruction. No manual vptr publication or handwritten
machine code is used. Range checks come from the native checked STL accessors,
not added defensive behavior. The array-delete target is the actual five-byte
free-delegating thunk68AA26, which itself enters6898EA.

The existing Pattern Group and spell-resource types supply real element
ownership. Sequence records contain a94-byte sprite after their first4 bytes;
the render-history list uses the established sprite/blend record. Unaccessed
owner ranges stay explicit and are not instantiated as new unrelated objects.

## Corrected handle-vector type

The first complete scalar-vector hypothesis emitted935 bytes and an inline
memmove_s absent from native. The target instead calls the same generated
range-erase boundary as the independently exact design-resource cleanup.
Using the existing four-byte DesignTextureHandle value class restores that
operation and yields905 bytes. This is a real container element-type change,
not a compatibility guard or call stub.

The constructor-facing vector at+130 is reconciled to the same handle-class
type. A fresh constructor build stays exactly the same557-byte nonexact
candidate55da99cc, including its nine known EH/store-order differences.
No accepted shared header or caller changes.

## Remaining byte and controls

At462DF6 native loads EDX from [EDI+ECX], while source loads EDX from [ECX+EDI].
The SIB byte at462DF8 is0F versus39. Both scales are1; every other byte in the
complete905-byte body is equal. This is not waived as exact.

A genuine zero-constructed four-byte wave-handle element and a typed accessed
base-prefix view retain the same candidate. Signed fixed-loop count adds a
second branch difference and is rejected. An inline value-conversion form
changes register allocation and seven bytes; class-by-value transport is
neutral. Neither is selected. The source keeps unsigned bounded indexing and
direct access to the actual handle value. Do not continue commutative-address,
register or dummy-lifetime spelling grids for this one byte.

Native full27-byte handler6BB1F4 references FuncInfo6E0D60 and thirteen unwind
states at6E0D84. The generated source FuncInfo independently has13 states.
No EH-body acceptance is inferred from metadata count agreement.

## Reproduction

scripts/repo-python scripts/build.py --unit exact-first-character-destructor --compare --json
scripts/repo-python scripts/build.py --unit exact-first-character-constructor --compare --json

Source:src/characters/CharacterDestructor.cpp.
Evidence:build/frontier-character-destructor-20261029/formal-build.json,
constructor-handle-class.json, native-facts.json and source-eh.json.
Default CI and diff checks validate final tracking/progress. No broad runtime
matrix or cold corpus build is required.
