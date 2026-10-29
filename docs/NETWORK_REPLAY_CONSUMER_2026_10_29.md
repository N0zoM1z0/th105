# Replay input consumption, JP1.06a

44E210 is now canonical exact170/170.
SHA256:76148799992d77ee751a0f4967978b4383bc7df96f6542c0ac2ee8134d54dc86.

This supersedes the old conclusion that its170-byte register permutation was
only a TU/allocator stop. Correct unsigned destination-word semantics recover
the native allocation naturally, without register or compiler-profile forcing.

## Ownership and exact behavior

The sole direct call found across the current function inventory is44F092,
inside exact CNetworkClientSecondary packet dispatcher44EE80. It immediately
starts packet cleanup and does not consume a return value. The source uses
a void method interface; this does not assert uniqueness of the original
nominal return declaration or modify the existing ignored-return caller.

Native fields establish the6DC-byte primary-client prefix and lock at+DC.
Tag mismatch calls actual virtual slot2C with reason3 and returns. Otherwise
the method computes unsigned packet-sequence minus current-sequence, publishes
metadata, and rejects deltas larger than the incoming deque size without
updating sequence. An admitted delta publishes packet sequence, then consumes
that many incoming values in descending index order.

For each value, decrement occurs before lock entry. The word is loaded with
MOVZX, appended to the client's+6C8 queue, then the lock is released and the
same zero-extended word is forwarded to input sink42B270. Lock/unlock occur
per item, not around the whole batch. No new checks or rollback behavior is
added.

Raw CFG reaches57 instructions/163 bytes and both RET4 exits. The seven-byte
loop alignment at44E269 is included in strict170-byte comparison. There is no
omitted cleanup or remote tail.

## Type and dataflow recovery

The first ordinary source with signed packet/destination deques and post-lock
decrement was164 bytes. Moving the actual countdown before lock restores the
native loop alignment, yielding173 with a redundant short promotion and the
old receiver/register permutation. Widening the local value alone is neutral.

The destination input queue is modeled as std::deque<unsigned short>, matching
the zero-extended bit-pattern transport to the unsigned-short input sink.
That removes the artificial signed-short conversion before push_back and
restores all170 bytes, including this/lock/value register assignment.

An independent reduction keeps the existing incoming std::deque<short> packet
view and its short-reference getter, converting the fetched value to unsigned
short as native MOVZX requires. The complete170-byte candidate remains exactly
the same. That narrower version is selected; no incoming packet header or
accepted parser is changed. All standard deque methods retain their real
pointer/reference ABI and2-byte element storage.

The exact source also retains the physical caller cleanup contract and the
native out-of-line checked getter42D140. No fake zero values, volatile aliases,
inert locals, manual vtables, copied instructions or broad runtime matrix are
used.

## Reproduction

scripts/repo-python scripts/build.py --unit exact-first-network-replay-consumer --compare --json

Source:src/network/NetworkReplayConsumer.cpp.
Evidence:build/frontier-replay-consumer-20261029/formal-build.json,
compare.json and native-facts.json. No existing source/header/accepted consumer
changed. Default CI and diff checks validate final exact tracking and progress.
