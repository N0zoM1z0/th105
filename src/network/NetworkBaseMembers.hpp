#pragma once

#include "../input/InputManager.hpp"
#include <deque>
#include <stddef.h>

namespace th105 {

struct PacketResultBase4 {
    PacketResultBase4() : result_004() {}
    unsigned int result_004;
};

class ScenePacket0C : public PacketResultBase4 {
public:
    ScenePacket0C() {}
    virtual unsigned int serialize(void *buffer);

    unsigned char payload_008[4];
};

class InputPacket24ConstructorView : public PacketResultBase4 {
public:
    InputPacket24ConstructorView() {}
    virtual unsigned int serialize(void *buffer);

    unsigned int sequence_008;
    unsigned char tag_00c;
    unsigned char reserved_00d[3];
    std::deque<short> values_010;
};

struct NetworkInputEndpoint7C {
    CInputManagerEx input_000;
    std::deque<short> queue_068;
};

struct NetworkQueueSlot20 {
    unsigned int sequence_000;
    unsigned char side_004;
    unsigned char reserved_005[3];
    std::deque<short> queue_008;
    void *input_01c;
};

// The native EH action receives owner+20C and destroys two slots at+8.
// Keep this real nested lifetime; the following eight parent bytes remain opaque.
struct NetworkQueuePair48 {
    unsigned char prefix_00[8];
    NetworkQueueSlot20 slots_08[2];
};

typedef char NetworkMembersInputExtent[sizeof(NetworkInputEndpoint7C) == 0x7c ? 1 : -1];
typedef char NetworkMembersPacketExtent[sizeof(InputPacket24ConstructorView) == 0x24 ? 1 : -1];
typedef char NetworkMembersQueueExtent[sizeof(NetworkQueueSlot20) == 0x20 ? 1 : -1];
typedef char NetworkMembersEndpointQueue[offsetof(NetworkInputEndpoint7C, queue_068) == 0x68 ? 1 : -1];
typedef char NetworkMembersSlotQueue[offsetof(NetworkQueueSlot20, queue_008) == 8 ? 1 : -1];
typedef char NetworkMembersPairSlots[offsetof(NetworkQueuePair48, slots_08) == 8 ? 1 : -1];

} // namespace th105
