#pragma once

#include "NetworkPacketBase.hpp"
#include <deque>
#include <stddef.h>

namespace th105 {

class NetworkAckInfoPacket40 : public NetworkPacketBase8 {
public:
    NetworkAckInfoPacket40() {}
    virtual unsigned int serialize(void *buffer);
    virtual char parse(const unsigned char *input);

    unsigned char value_008[2];
    unsigned char status_00a[2];
    std::deque<short> values_00c[2];
    unsigned char peer_034[2];
    unsigned char tail_036;
    unsigned char tail_037;
    unsigned int tail_038;
    unsigned char sequence_03c;
    unsigned char reserved_03d[3];
};

typedef char NetworkAckInfoPacket40_size[
    sizeof(NetworkAckInfoPacket40) == 0x40 ? 1 : -1];

} // namespace th105
