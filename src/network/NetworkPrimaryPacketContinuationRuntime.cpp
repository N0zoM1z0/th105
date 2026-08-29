#include "../engine/CriticalSectionWrapper.hpp"

#include <deque>
#include <stddef.h>

namespace th105 {

class NetworkPacketWithResult8 {
public:
    virtual unsigned int serialize(void *buffer);
    unsigned int result_004;
};

struct NetworkClientSend4View {
    int send_client(
        const void *buffer,
        unsigned int size,
        int option,
        unsigned int *result);
};

struct NetworkPeerByte5 {
    unsigned char reserved_000[4];
    unsigned char byte_004;
};

struct NetworkStateRecord4CView {
    unsigned char reserved_000[0x0e];
    unsigned char side0_tail_00e;
    unsigned char reserved_00f[0x1f];
    unsigned char side1_tail_02e;
    unsigned char reserved_02f[0x1d];
};

class CNetworkClientPacketContinuationView {
public:
    int send_packet_with_result_44e6a0(
        NetworkPacketWithResult8 *packet, int option);
    void import_ack_info_tail_44e6d0(
        const NetworkStateRecord4CView *source);

    unsigned char reserved_000[0x200];
    NetworkPeerByte5 *local_peer_200;
    unsigned char reserved_204[0x16];
    unsigned char side0_tail_21a;
    unsigned char reserved_21b[0x1f];
    unsigned char side1_tail_23a;
    unsigned char reserved_23b[0x15];
    NetworkPeerByte5 *remote_peer_250;
    unsigned char reserved_254[8];
    CriticalSectionWrapper critical_25c;
    unsigned char reserved_278[0x12e];
    bool ack_pending_3a6;
    unsigned char reserved_3a7[0x0d];
    NetworkClientSend4View sender_3b4;
    unsigned char reserved_3b5[0x1ff];
    unsigned char packet_buffer_5b4[0x128];
};

int CNetworkClientPacketContinuationView::send_packet_with_result_44e6a0(
    NetworkPacketWithResult8 *packet, int option)
{
    return sender_3b4.send_client(
        packet_buffer_5b4,
        packet->serialize(packet_buffer_5b4),
        option,
        &packet->result_004);
}

void CNetworkClientPacketContinuationView::import_ack_info_tail_44e6d0(
    const NetworkStateRecord4CView *source)
{
    critical_25c.enter();
    remote_peer_250->byte_004 = local_peer_200->byte_004;
    side0_tail_21a = source->side0_tail_00e;
    side1_tail_23a = source->side1_tail_02e;
    ack_pending_3a6 = 1;
    critical_25c.leave();
}

class CNetworkServerAdaptiveDelayView {
public:
    void update_adaptive_delay_44f550(int unused);

    unsigned char reserved_000[0x80];
    signed char adaptive_delay_080;
    signed char base_delay_081;
    unsigned char reserved_082[0x16];
    unsigned int sequence_098;
    unsigned char reserved_09c[0x644];
    int sample_count_6e0;
    int sample_sum_6e4;
    unsigned int high_water_6e8;
};

class NetworkServerInputVirtualBase {
public:
    virtual ~NetworkServerInputVirtualBase();
    virtual void slot_01();
    virtual void slot_02();
    virtual void slot_03();
    virtual void slot_04();
    virtual void slot_05();
    virtual void slot_06();
    virtual void slot_07();
    virtual void slot_08();
    virtual void slot_09();
    virtual void slot_0a();
    virtual void slot_0b();
    virtual void slot_0c();
    virtual void update_adaptive_delay(int value);
};

struct NetworkServerSend5View {
    int send_server(
        unsigned int channel,
        const void *buffer,
        unsigned int size,
        int option,
        unsigned int *result);
};

class CNetworkServerInputPublishView : public NetworkServerInputVirtualBase {
public:
    void publish_input_frame_44f9a0();

    unsigned char reserved_004[0x44];
    CriticalSectionWrapper critical_048;
    unsigned char reserved_064[0x18];
    unsigned short current_07c;
    unsigned short previous_07e;
    signed char adaptive_delay_080;
    unsigned char reserved_081[0x0f];
    NetworkPacketWithResult8 packet_090;
    unsigned int sequence_098;
    unsigned char reserved_09c[4];
    std::deque<short> history_0a0;
    unsigned char reserved_0b4[0x28];
    CriticalSectionWrapper critical_0dc;
    unsigned char reserved_0f8[0x68];
    std::deque<short> output_a_160;
    unsigned char reserved_174[0x68];
    std::deque<short> output_b_1dc;
    unsigned char reserved_1f0[0x18];
    unsigned char *input_208;
    unsigned char reserved_20c[0x1a8];
    NetworkServerSend5View sender_3b4;
    unsigned char reserved_3b5[0x1ff];
    unsigned char packet_buffer_5b4[0x134];
    unsigned int high_water_6e8;
};

void CNetworkServerAdaptiveDelayView::update_adaptive_delay_44f550(int)
{
    const unsigned int distance = sequence_098 - high_water_6e8;
    if (distance < 10 && sequence_098 > 0) {
        ++sample_count_6e0;
        sample_sum_6e4 += distance;
        int result = sample_sum_6e4;
        if (sample_count_6e0 > 0) {
            if (sample_count_6e0 < 20000) {
                signed char candidate = static_cast<signed char>(
                    base_delay_081 + result / sample_count_6e0);
                signed char lower = candidate > base_delay_081
                    ? candidate : base_delay_081;
                int chosen;
                if (lower > 10) {
                    chosen = 10;
                } else {
                    chosen = candidate > base_delay_081
                        ? candidate : base_delay_081;
                }
                adaptive_delay_080 = static_cast<signed char>(chosen);
                return;
            }
        }
        if (sample_count_6e0 > 20000) {
            sample_count_6e0 = 0;
            sample_sum_6e4 = 0;
        }
    }
}

void CNetworkServerInputPublishView::publish_input_frame_44f9a0()
{
    CriticalSectionWrapper *lock = &critical_048;
    lock->enter();
    if (sequence_098 - high_water_6e8 >
        static_cast<unsigned int>(adaptive_delay_080 + 3)) {
        unsigned char *buffer = packet_buffer_5b4;
        NetworkPacketWithResult8 *packet = &packet_090;
        sender_3b4.send_server(
            0,
            buffer,
            packet->serialize(buffer),
            0x50,
            &packet->result_004);
        lock->leave();
        return;
    }

    const unsigned short current =
        *reinterpret_cast<unsigned short *>(input_208 + 0x62) & 0x3ff;
    current_07c = current;
    ++sequence_098;
    unsigned int current_value = current;
    int previous_value = static_cast<unsigned short>(previous_07e);
    history_0a0.push_front(
        reinterpret_cast<const short &>(previous_value));
    history_0a0.push_front(
        reinterpret_cast<const short &>(current_value));
    while (history_0a0.size() >
           2 * (sequence_098 - high_water_6e8)) {
        history_0a0.pop_back();
        history_0a0.pop_back();
    }

    unsigned char *buffer = packet_buffer_5b4;
    NetworkPacketWithResult8 *packet = &packet_090;
    sender_3b4.send_server(
        0,
        buffer,
        packet->serialize(buffer),
        0x50,
        &packet->result_004);
    update_adaptive_delay(0);

    critical_0dc.enter();
    current_value = current;
    output_a_160.push_back(
        reinterpret_cast<const short &>(current_value));
    current_value = static_cast<unsigned short>(previous_value);
    output_b_1dc.push_back(
        reinterpret_cast<const short &>(current_value));
    critical_0dc.leave();
    lock->leave();
}

typedef char NetworkStateRecord4CView_size[
    sizeof(NetworkStateRecord4CView) == 0x4c ? 1 : -1];
typedef char CNetworkClientPacketContinuationView_peer_offset[
    offsetof(CNetworkClientPacketContinuationView, local_peer_200) == 0x200
        ? 1 : -1];
typedef char CNetworkClientPacketContinuationView_critical_offset[
    offsetof(CNetworkClientPacketContinuationView, critical_25c) == 0x25c
        ? 1 : -1];
typedef char CNetworkClientPacketContinuationView_sender_offset[
    offsetof(CNetworkClientPacketContinuationView, sender_3b4) == 0x3b4
        ? 1 : -1];
typedef char CNetworkClientPacketContinuationView_buffer_offset[
    offsetof(CNetworkClientPacketContinuationView, packet_buffer_5b4) == 0x5b4
        ? 1 : -1];
typedef char CNetworkServerAdaptiveDelayView_counter_offset[
    offsetof(CNetworkServerAdaptiveDelayView, sample_count_6e0) == 0x6e0
        ? 1 : -1];
typedef char CNetworkServerInputPublishView_history_offset[
    offsetof(CNetworkServerInputPublishView, history_0a0) == 0x0a0
        ? 1 : -1];
typedef char CNetworkServerInputPublishView_input_offset[
    offsetof(CNetworkServerInputPublishView, input_208) == 0x208
        ? 1 : -1];
typedef char CNetworkServerInputPublishView_buffer_offset[
    offsetof(CNetworkServerInputPublishView, packet_buffer_5b4) == 0x5b4
        ? 1 : -1];
typedef char CNetworkServerInputPublishView_high_water_offset[
    offsetof(CNetworkServerInputPublishView, high_water_6e8) == 0x6e8
        ? 1 : -1];

} // namespace th105
