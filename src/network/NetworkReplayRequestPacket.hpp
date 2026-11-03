#pragma once

#include "NetworkPacketBase.hpp"

namespace th105 {

class NetworkRequestReplay10 : public NetworkPacketBase8 {
public:
    NetworkRequestReplay10() {}
    virtual unsigned int serialize(void *buffer);
    void parse(const unsigned char *input);
    unsigned int value_008;
    unsigned char tag_00c;
    unsigned char reserved_00d[3];
};

} // namespace th105
