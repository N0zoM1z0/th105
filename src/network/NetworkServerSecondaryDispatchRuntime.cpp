#include "NetworkInputPacket.hpp"
#include "NetworkReplayRequestPacket.hpp"
#include "../engine/CriticalSectionWrapper.hpp"
#include "NetworkAckInfoPacket.hpp"

#include <deque>
#include <stddef.h>

namespace th105 {

struct PacketResultBase4 {
    PacketResultBase4() : result_004(0) {}
    unsigned int result_004;
};

class SceneAckPacket0C : public PacketResultBase4 {
public:
    SceneAckPacket0C() {}
    virtual unsigned int serialize(void *buffer);
    unsigned char state_008;
    unsigned char reserved_009[3];
};



class EmbeddedStatePacket8 {
public:
    virtual unsigned int serialize(void *buffer);
    virtual void parse(const unsigned char *input);
    unsigned int result_004;
};


class NetworkServerPrimarySecondaryDispatchView {
public:
    virtual ~NetworkServerPrimarySecondaryDispatchView();
    virtual void slot_01();
    virtual void slot_02();
    virtual void slot_03();
    virtual void slot_04();
    virtual void slot_05();
    virtual void consume_ack_info(NetworkAckInfoPacket40 *packet);
    virtual void slot_07();
    virtual void consume_input(InputPacket24 *packet);
    virtual void slot_09();
    virtual void slot_0a();
    virtual void slot_0b(int reason);

    int dispatch_secondary_request(
        unsigned int context, const NetworkRequestReplay10 *request);
    void send_packet(unsigned int channel, void *packet, int option);

    unsigned char reserved_004[0x44];
    CriticalSectionWrapper critical_048;
    EmbeddedStatePacket8 state_packet_064;
    unsigned char state_06c;
    unsigned char reserved_06d[3];
    EmbeddedStatePacket8 state_packet_070;
    unsigned char state_078;
    unsigned char reserved_079[8];
    signed char delay_081;
    unsigned char reserved_082[0x325];
    unsigned char pending_3a7;
    unsigned char reserved_3a8[0x334];
};

typedef char ServerPrimarySecondaryDispatchSize[
    sizeof(NetworkServerPrimarySecondaryDispatchView) == 0x6dc ? 1 : -1];

class CNetworkServerSecondaryDispatchView {
public:
    virtual void slot_00();
    virtual void slot_01();
    virtual void slot_02();
    virtual void dispatch_packet(
        unsigned int context, const unsigned char *packet, int unused);

    int secondary_state_004;

private:
    NetworkServerPrimarySecondaryDispatchView *owner()
    {
        return reinterpret_cast<NetworkServerPrimarySecondaryDispatchView *>(
            reinterpret_cast<unsigned char *>(this) - 0x6dc);
    }
};

void CNetworkServerSecondaryDispatchView::dispatch_packet(
    unsigned int context, const unsigned char *packet, int)
{
    if (context > 0) {
        if (packet[0] == 11) {
            NetworkRequestReplay10 request;
            request.value_008 = *reinterpret_cast<const unsigned int *>(packet + 1);
            request.tag_00c = packet[5];
            owner()->dispatch_secondary_request(context, &request);
        }
        return;
    }

    switch (packet[0]) {
    case 1: {
        CriticalSectionWrapper *critical = &owner()->critical_048;
        critical->enter();
        owner()->state_packet_070.parse(packet);
        if (owner()->state_06c == owner()->state_078) {
            SceneAckPacket0C request;
            request.state_008 = owner()->state_06c;
            owner()->send_packet(0, &request, 0x50);
        }
        critical->leave();
        break;
    }
    case 2: {
        CriticalSectionWrapper *critical = &owner()->critical_048;
        critical->enter();
        owner()->state_packet_070.parse(packet);
        critical->leave();
        break;
    }
    case 3: {
        InputPacket24 request;
        request.parse(packet);
        owner()->consume_input(&request);
        break;
    }
    case 8: {
        CriticalSectionWrapper *critical = &owner()->critical_048;
        critical->enter();
        owner()->pending_3a7 = 1;
        critical->leave();
        break;
    }
    case 4: {
        NetworkAckInfoPacket40 request;
        request.parse(packet);
        owner()->consume_ack_info(&request);
        break;
    }
    case 5:
        owner()->slot_04();
        break;
    case 7: {
        unsigned char delay = packet[1];
        CriticalSectionWrapper *critical = &owner()->critical_048;
        critical->enter();
        owner()->delay_081 = static_cast<signed char>(delay);
        critical->leave();
        break;
    }
    default:
        break;
    }
}

typedef char ServerSecondaryDispatchSize[
    sizeof(CNetworkServerSecondaryDispatchView) == 0x08 ? 1 : -1];
typedef char SceneAckPacket0C_size_s[sizeof(SceneAckPacket0C)==0x0c?1:-1];
typedef char InputPacket24_size_s[sizeof(InputPacket24)==0x24?1:-1];
typedef char NetworkAckInfoPacket40_size_s[sizeof(NetworkAckInfoPacket40)==0x40?1:-1];
typedef char NetworkRequestReplay10_size_s[sizeof(NetworkRequestReplay10)==0x10?1:-1];

} // namespace th105
