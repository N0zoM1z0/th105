#pragma once

#include "NetworkPacketBase.hpp"
#include <stddef.h>

namespace th105 {

class NetworkRequestInfo8 : public NetworkPacketBase8 {
public:
    virtual unsigned int serialize(void *buffer);
    virtual void parse(const unsigned char *) {}
};

class NetworkDelayPacket12 : public NetworkPacketBase8 {
public:
    virtual unsigned int serialize(void *buffer);
    virtual void parse(const unsigned char *input) { delay_008 = input[1]; }

    unsigned char delay_008;
    unsigned char reserved_009[3];
};

class SceneAckPacket0C : public NetworkPacketBase8 {
public:
    virtual unsigned int serialize(void *buffer);
    virtual void parse(const unsigned char *input) { state_008 = input[1]; }

    unsigned char state_008;
    unsigned char reserved_009[3];
};

class NetworkTerminatePacket8 : public NetworkPacketBase8 {
public:
    virtual unsigned int serialize(void *buffer);
    virtual void parse(const unsigned char *) {}
};

typedef char NetworkRequestInfoExtent[sizeof(NetworkRequestInfo8) == 8 ? 1 : -1];
typedef char NetworkDelayPacketExtent[sizeof(NetworkDelayPacket12) == 0x0c ? 1 : -1];
typedef char NetworkDelayPayloadOffset[
    offsetof(NetworkDelayPacket12, delay_008) == 8 ? 1 : -1];
typedef char SceneAckPacketExtent[sizeof(SceneAckPacket0C) == 0x0c ? 1 : -1];
typedef char SceneAckPacketPayloadOffset[
    offsetof(SceneAckPacket0C, state_008) == 8 ? 1 : -1];
typedef char NetworkTerminatePacketExtent[
    sizeof(NetworkTerminatePacket8) == 8 ? 1 : -1];

} // namespace th105
