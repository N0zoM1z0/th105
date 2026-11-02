# Profile deck actual render members, 2026-11-02

Pinned Japanese v1.06a SHA-256:
56350024879199861579c11b0e1c67b9590e10a8d40cd5996b109deec9afca7e.

ProfileDeckEdit.hpp replaces its extension-array sprite/tile subclasses with
actual CSprite and CTile members. These are the same field extents and identities
already recovered in its constructor view. The complete owner remains0x6B0.
ProfileDeckRender.cpp replaces its manual-vptr local with actual CSprite,
removes the dispatch macro, uses named scale fields and normal base conversion,
and calls actual sprite/tile members without receiver casts. The unit's direct
call bindings now use real methods. No control flow, arithmetic, missing-count
policy, compilation flags or preservation barriers change.

Fresh before/after controls retain renderer0x448F60's full2521-byte candidate,
SHA-256 73fb53f64d54c145d1e16c345045f4fa3373de46b173a6e9a648b64145942e38.
It remains nonexact; the previous iterator/lifetime schedule is not forced.
Destructor0x44A950 remains full353 exact bytes, SHA-256
20f4f8667cd3d24cb32ee004bce6127a0e8a6c9f749753ec2c127a134321368e.
The30-byte scalar wrapper is unchanged. Actual include closure: six units,
seven accepted roots in five units freshly exact. The scalar and pending
renderer also retain fresh HEAD hashes after final source simplification.

The local sprite emits the complete actual RTTI graph273 and nine-slot table,
both matching. Full destructor EH is185 bytes at0x6B9E30, including handler
0x6B9ECE, plus124 bytes of FuncInfo/unwind metadata reached by that handler.
All309 support bytes match. The map cleanup0x43DED0 is independently compared
as a whole52-byte body, and deque cleanup0x448DE0 as a whole5-byte tail. The
resource-group cleanup retains its existing qualified target0x42E900. Shared
physical member cleanup addresses do not imply exclusive nominal identities.

Constructor view and remaining outer design/resource views are not unified
by this change. No runtime/gameplay or full-program linkage claim is made.
No support, prefix or nonexact bytes are added to authored acceptance.
Private scripts and reports are under
.analysis/frontier-deck-render-real-sprites-20261102/ and
build/frontier-deck-render-real-sprites-20261102/. Full CI passed962 tests
(98.574 seconds), tracking, generated progress and whitespace checks. Both
working-tree and staged diff checks passed.

Totals unchanged:1427 exact /443604 bytes,1637 source-present,1656 authored,
1826 mapped,2074 excluded,297 review and813 units.
