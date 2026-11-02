#pragma once
#include <deque>
#include <stddef.h>
namespace th105 {
// In-process state snapshot, not MatchSetup or the CDPP_ACK_INFO packet object.
// Pointer-only consumers below do not establish an original nominal class name.
struct NetworkStateRecord4C {
    unsigned char reserved_000[4];
    unsigned char byte_004;
    unsigned char byte_005;
    unsigned char reserved_006[2];
    unsigned int value_008;
    unsigned char byte_00c;
    unsigned char byte_00d;
    unsigned char byte_00e;
    unsigned char reserved_00f;
    std::deque<short> queue_010;
    unsigned int peer_024;
    unsigned int value_028;
    unsigned char byte_02c;
    unsigned char byte_02d;
    unsigned char byte_02e;
    unsigned char reserved_02f;
    std::deque<short> queue_030;
    unsigned int value_044;
    unsigned int value_048;
};
typedef char NetworkStateRecordExtent[sizeof(NetworkStateRecord4C)==0x4c?1:-1];
typedef char NetworkStateRecordFirstQueue[offsetof(NetworkStateRecord4C,queue_010)==0x10?1:-1];
typedef char NetworkStateRecordSecondQueue[offsetof(NetworkStateRecord4C,queue_030)==0x30?1:-1];
typedef char NetworkStateRecordFirstTail[offsetof(NetworkStateRecord4C,byte_00e)==0x0e?1:-1];
typedef char NetworkStateRecordSecondTail[offsetof(NetworkStateRecord4C,byte_02e)==0x2e?1:-1];
} // namespace th105
