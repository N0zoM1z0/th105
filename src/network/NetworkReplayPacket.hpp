#pragma once

#include "NetworkPacketBase.hpp"
#include <deque>

namespace th105 {

class ReplayPacket28 : public NetworkPacketBase8 {
public:
    ReplayPacket28() {}
    virtual unsigned int serialize(void *buffer);
    virtual void parse_compressed(const unsigned char *input);
    unsigned int sequence_008;
    unsigned int metadata_00c;
    unsigned char tag_010;
    unsigned char reserved_011[3];
    std::deque<short> values_014;
};

} // namespace th105
