#pragma once
#include <deque>
#include <stddef.h>
namespace th105 {
// In-process state snapshot, not MatchSetup or the CDPP_ACK_INFO packet object.
// Pointer-only consumers below do not establish an original nominal class name.
// One side of the snapshot. Its checked deque is a native VC8 deque<short>.
struct NetworkStateSide20 {
    unsigned int value_00;
    unsigned char byte_04;
    unsigned char byte_05;
    unsigned char byte_06;
    unsigned char reserved_07;
    std::deque<short> queue_08;
    unsigned int peer_1c;
};

struct NetworkStateRecord4C {
    unsigned char reserved_000[4];
    unsigned char byte_004;
    unsigned char byte_005;
    unsigned char reserved_006[2];
    NetworkStateSide20 sides_008[2];
    unsigned int value_048;
};
typedef char NetworkStateSideExtent[sizeof(NetworkStateSide20)==0x20?1:-1];
typedef char NetworkStateRecordExtent[sizeof(NetworkStateRecord4C)==0x4c?1:-1];
typedef char NetworkStateRecordSides[offsetof(NetworkStateRecord4C,sides_008)==0x08?1:-1];
} // namespace th105
