#include "../engine/CriticalSectionWrapper.hpp"
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

class TerminatePacket8 : public PacketResultBase4 {
public:
    TerminatePacket8() {}
    virtual unsigned int serialize(void *buffer);
};

class InputPacket24 : public PacketResultBase4 {
public:
    InputPacket24() {}
    virtual unsigned int serialize(void *buffer);
    void parse(const unsigned char *input);
    unsigned int sequence_008;
    unsigned char tag_00c;
    unsigned char reserved_00d[3];
    std::deque<short> values_010;
};

class AckInfoPacket40 : public PacketResultBase4 {
public:
    AckInfoPacket40();
    virtual unsigned int serialize(void *buffer);
    char parse(const unsigned char *input);
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

class ReplayPacket28 : public PacketResultBase4 {
public:
    ReplayPacket28() {}
    virtual unsigned int serialize(void *buffer);
    void parse_compressed(const unsigned char *input);
    unsigned int sequence_008;
    unsigned int metadata_00c;
    unsigned char tag_010;
    unsigned char reserved_011[3];
    std::deque<short> values_014;
};

class EmbeddedStatePacket8 {
public:
    virtual unsigned int serialize(void *buffer);
    virtual void parse(const unsigned char *input);
    unsigned int result_004;
};

class NetworkClientPrimarySecondaryDispatchView {
public:
    virtual ~NetworkClientPrimarySecondaryDispatchView();
    virtual void slot_01();
    virtual void slot_02();
    virtual void slot_03();
    virtual void slot_04();
    virtual void slot_05();
    virtual void consume_ack_info(AckInfoPacket40 *packet);
    virtual void slot_07();
    virtual void consume_input(InputPacket24 *packet);
    virtual void slot_09();
    virtual void slot_0a();
    virtual void slot_0b(int reason);

    int send_scene_packet(void *packet, int option);
    int send_simple_packet(void *packet, int option);
    int consume_replay(ReplayPacket28 *packet);

    unsigned char reserved_004[0x44];
    CriticalSectionWrapper critical_048;
    EmbeddedStatePacket8 state_packet_064;
    unsigned char state_06c;
    unsigned char reserved_06d[0x0b];
    unsigned char state_078;
    unsigned char reserved_079[0x32e];
    unsigned char pending_3a7;
    unsigned char reserved_3a8[0x334];
};

typedef char PrimaryDispatchSize[
    sizeof(NetworkClientPrimarySecondaryDispatchView) == 0x6dc ? 1 : -1];

class CNetworkClientSecondaryDispatchView {
public:
    virtual CNetworkClientSecondaryDispatchView *configure(int, const void *, int);
    virtual int set_option_bits(int value);
    virtual void dispatch_packet(const unsigned char *packet, int unused);
    virtual int handle_request(int, const void *, int);

    int secondary_state_004;

private:
    NetworkClientPrimarySecondaryDispatchView *owner()
    {
        return reinterpret_cast<NetworkClientPrimarySecondaryDispatchView *>(
            reinterpret_cast<unsigned char *>(this) - 0x6dc);
    }
};

void CNetworkClientSecondaryDispatchView::dispatch_packet(
    const unsigned char *packet, int)
{
    switch (packet[0]) {
    case 1: {
        CriticalSectionWrapper *critical = &owner()->critical_048;
        critical->enter();
        owner()->state_packet_064.parse(packet);
        if (owner()->state_06c == owner()->state_078) {
            SceneAckPacket0C request;
            request.state_008 = owner()->state_078;
            owner()->send_scene_packet(&request, 0x50);
        }
        critical->leave();
        break;
    }
    case 2: {
        CriticalSectionWrapper *critical = &owner()->critical_048;
        critical->enter();
        owner()->state_packet_064.parse(packet);
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
        TerminatePacket8 request;
        owner()->send_simple_packet(&request, 0x50);
        CriticalSectionWrapper *critical = &owner()->critical_048;
        critical->enter();
        owner()->pending_3a7 = 1;
        critical->leave();
        break;
    }
    case 4: {
        AckInfoPacket40 request;
        request.parse(packet);
        owner()->consume_ack_info(&request);
        break;
    }
    case 5:
        owner()->slot_04();
        break;
    case 9:
    case 10: {
        ReplayPacket28 request;
        request.parse_compressed(packet);
        owner()->consume_replay(&request);
        break;
    }
    default:
        break;
    }
}

typedef char SceneAckPacket0C_size[sizeof(SceneAckPacket0C)==0x0c?1:-1];
typedef char TerminatePacket8_size[sizeof(TerminatePacket8)==0x08?1:-1];
typedef char InputPacket24_size[sizeof(InputPacket24)==0x24?1:-1];
typedef char AckInfoPacket40_size[sizeof(AckInfoPacket40)==0x40?1:-1];
typedef char ReplayPacket28_size[sizeof(ReplayPacket28)==0x28?1:-1];
typedef char SecondaryDispatchSize[sizeof(CNetworkClientSecondaryDispatchView)==0x08?1:-1];

} // namespace th105
