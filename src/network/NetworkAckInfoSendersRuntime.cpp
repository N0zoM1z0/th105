#include "../engine/CriticalSectionWrapper.hpp"

#include <deque>
#include <stddef.h>

namespace th105 {

struct AckPacketResultBase4 {
    AckPacketResultBase4() : result_004(0) {}
    unsigned int result_004;
};

class NetworkPacketSerializeOnlyView {
public:
    virtual unsigned int serialize(void *buffer);
};

class NetworkAckInfoPacket40 : public AckPacketResultBase4 {
public:
    NetworkAckInfoPacket40() {}
    virtual unsigned int serialize(void *buffer);

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

struct NetworkPeerByte5 {
    unsigned char reserved_000[4];
    unsigned char byte_004;
};

struct NetworkClientSend4View {
    int send_client(
        const void *buffer,
        unsigned int size,
        int option,
        unsigned int *result);
};

struct NetworkServerSend5View {
    int send_server(
        unsigned int channel,
        const void *buffer,
        unsigned int size,
        int option,
        unsigned int *result);
};

class CNetworkClientAckSenderView {
public:
    void send_ack_info_if_ready();

    void *vfptr_000;
    unsigned char reserved_004[0x238];
    std::deque<short> queue_23c;
    NetworkPeerByte5 *peer_250;
    unsigned char reserved_254[8];
    CriticalSectionWrapper critical_25c;
    unsigned char reserved_278[0x12d];
    unsigned char gate_a_3a5;
    unsigned char gate_b_3a6;
    unsigned char reserved_3a7[0x0d];
    NetworkClientSend4View send_3b4;
    unsigned char reserved_3b5[0x1ff];
    unsigned char buffer_5b4[0x50];
};

typedef char CNetworkClientAckSender_queue_off[
    offsetof(CNetworkClientAckSenderView, queue_23c) == 0x23c ? 1 : -1];
typedef char CNetworkClientAckSender_critical_off[
    offsetof(CNetworkClientAckSenderView, critical_25c) == 0x25c ? 1 : -1];
typedef char CNetworkClientAckSender_gate_off[
    offsetof(CNetworkClientAckSenderView, gate_a_3a5) == 0x3a5 ? 1 : -1];
typedef char CNetworkClientAckSender_send_off[
    offsetof(CNetworkClientAckSenderView, send_3b4) == 0x3b4 ? 1 : -1];
typedef char CNetworkClientAckSender_buffer_off[
    offsetof(CNetworkClientAckSenderView, buffer_5b4) == 0x5b4 ? 1 : -1];

void CNetworkClientAckSenderView::send_ack_info_if_ready()
{
    CriticalSectionWrapper *lock = &critical_25c;
    lock->enter();
    const unsigned char ready = gate_a_3a5 & gate_b_3a6;
    lock->leave();
    if (!ready)
        return;

    NetworkAckInfoPacket40 packet;
    lock->enter();
    packet.values_00c[1] = queue_23c;
    packet.peer_034[1] = peer_250->byte_004;
    NetworkPacketSerializeOnlyView *request =
        reinterpret_cast<NetworkPacketSerializeOnlyView *>(&packet);
    send_3b4.send_client(
        buffer_5b4,
        request->serialize(buffer_5b4),
        0,
        0);
    lock->leave();
}

class CNetworkServerAckSenderView {
public:
    void send_ack_info_if_ready();

    void *vfptr_000;
    unsigned char reserved_004[0x20c];
    unsigned char tail_210;
    unsigned char tail_211;
    unsigned char reserved_212[2];
    unsigned char side0_value_214;
    unsigned char reserved_215[4];
    unsigned char side0_status_219;
    unsigned char reserved_21a[2];
    std::deque<short> side0_queue_21c;
    NetworkPeerByte5 *side0_peer_230;
    unsigned char side1_value_234;
    unsigned char reserved_235[4];
    unsigned char side1_status_239;
    unsigned char reserved_23a[2];
    std::deque<short> side1_queue_23c;
    NetworkPeerByte5 *side1_peer_250;
    unsigned int tail_254;
    unsigned char reserved_258[4];
    CriticalSectionWrapper critical_25c;
    unsigned char reserved_278[0x12e];
    unsigned char gate_3a6;
    unsigned char reserved_3a7[0x0d];
    NetworkServerSend5View send_3b4;
    unsigned char reserved_3b5[0x1ff];
    unsigned char buffer_5b4[0x50];
};

typedef char CNetworkServerAckSender_side0_off[
    offsetof(CNetworkServerAckSenderView, side0_value_214) == 0x214 ? 1 : -1];
typedef char CNetworkServerAckSender_critical_off[
    offsetof(CNetworkServerAckSenderView, critical_25c) == 0x25c ? 1 : -1];
typedef char CNetworkServerAckSender_gate_off[
    offsetof(CNetworkServerAckSenderView, gate_3a6) == 0x3a6 ? 1 : -1];

void CNetworkServerAckSenderView::send_ack_info_if_ready()
{
    CriticalSectionWrapper *lock = &critical_25c;
    lock->enter();
    const unsigned char ready = gate_3a6;
    lock->leave();
    if (!ready)
        return;

    NetworkAckInfoPacket40 packet;
    lock->enter();
    packet.value_008[0] = side0_value_214;
    packet.status_00a[0] = side0_status_219;
    packet.value_008[1] = side1_value_234;
    packet.status_00a[1] = side1_status_239;
    packet.values_00c[0] = side0_queue_21c;
    packet.peer_034[0] = side0_peer_230->byte_004;
    packet.tail_036 = tail_210;
    packet.tail_037 = tail_211;
    packet.tail_038 = tail_254;
    NetworkPacketSerializeOnlyView *request =
        reinterpret_cast<NetworkPacketSerializeOnlyView *>(&packet);
    send_3b4.send_server(
        0,
        buffer_5b4,
        request->serialize(buffer_5b4),
        0,
        0);
    lock->leave();
}

} // namespace th105
