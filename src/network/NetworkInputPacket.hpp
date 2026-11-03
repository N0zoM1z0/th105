#pragma once

#include "NetworkPacketBase.hpp"
#include <deque>

namespace th105 {

class InputPacket24 : public NetworkPacketBase8 {
public:
    InputPacket24() {}
    virtual unsigned int serialize(void *buffer);
    void parse(const unsigned char *input);
    unsigned int sequence_008;
    unsigned char tag_00c;
    unsigned char reserved_00d[3];
    std::deque<short> values_010;
};

} // namespace th105
