#include "../engine/CriticalSectionWrapper.hpp"

#include <deque>
#include <stddef.h>

namespace th105 {

struct NetworkPeerByte5 {
    unsigned char reserved_000[4];
    unsigned char byte_004;
};

struct NetworkEndpointAdvance7C {
    unsigned char reserved_000[0x78];
    unsigned int remaining_078;

    void advance();
};

struct NetworkAuxRecord39 {
    unsigned char reserved_000[0x20];
    std::deque<short> queue_020;
    unsigned char reserved_034;
    unsigned char peer_byte_035;
    unsigned char reserved_036[3];
};

// Small CNetworkServer primary-vtable methods.  Current RTTI fixes the owner;
// offsets here are the same 0x6DC CNetworkBase physical fields established by
// NetworkBaseRuntime.cpp plus Server-owned counters through +0x6E8.
struct CNetworkServerSmallRuntimeView {
    void reset_base();
    void reset_server();
    bool maintain_endpoints();
    void import_aux(const NetworkAuxRecord39 *source);

    unsigned char reserved_000[0x48];
    CriticalSectionWrapper critical_048;
    unsigned char reserved_064[0x1c];
    signed char state_080;
    unsigned char reserved_081[0x5b];
    CriticalSectionWrapper critical_0dc;
    NetworkEndpointAdvance7C endpoint_0f8;
    NetworkEndpointAdvance7C endpoint_174;
    unsigned char reserved_1f0[0x40];
    NetworkPeerByte5 *peer_230;
    unsigned char reserved_234[0x08];
    std::deque<short> queue_23c;
    NetworkPeerByte5 *peer_250;
    unsigned char reserved_254[0x08];
    CriticalSectionWrapper critical_25c;
    unsigned char reserved_278[0x12d];
    unsigned char export_pending_3a5;
    unsigned char reserved_3a6[0x33a];
    unsigned int counter_6e0;
    unsigned int accumulator_6e4;
    unsigned int high_water_6e8;
};

void CNetworkServerSmallRuntimeView::reset_server()
{
    critical_048.enter();
    reset_base();
    state_080 = 2;
    counter_6e0 = 0;
    accumulator_6e4 = 0;
    high_water_6e8 = 0;
    critical_048.leave();
}

bool CNetworkServerSmallRuntimeView::maintain_endpoints()
{
    critical_0dc.enter();
    if (endpoint_0f8.remaining_078 > static_cast<unsigned int>(state_080)) {
        endpoint_0f8.advance();
        endpoint_174.advance();
        critical_0dc.leave();
        return true;
    }
    critical_0dc.leave();
    return false;
}

void CNetworkServerSmallRuntimeView::import_aux(
    const NetworkAuxRecord39 *source)
{
    critical_25c.enter();
    queue_23c = source->queue_020;
    peer_250->byte_004 = source->peer_byte_035;
    export_pending_3a5 = 1;
    critical_25c.leave();
}

struct NetworkStateRecord4CPublish {
    unsigned char reserved_000[4];
    unsigned char byte_004;
    unsigned char byte_005;
    unsigned char reserved_006[2];
    unsigned int value_008;
    unsigned char byte_00c;
    unsigned char byte_00d;
    unsigned char byte_00e;
    unsigned char reserved_00f;
    std::deque<short> queue_010;
    unsigned int peer_024;
    unsigned int value_028;
    unsigned char byte_02c;
    unsigned char byte_02d;
    unsigned char byte_02e;
    unsigned char reserved_02f;
    std::deque<short> queue_030;
    unsigned int value_044;
    unsigned int value_048;
};

class CNetworkServerPublishView {
public:
    virtual ~CNetworkServerPublishView();
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
    virtual void slot_0b(int value);

    bool publish_snapshot(NetworkStateRecord4CPublish *destination);

    unsigned char reserved_004[0x0d8];
    CriticalSectionWrapper critical_0dc;
    unsigned char reserved_0f8[0x118];
    unsigned char byte_210;
    unsigned char byte_211;
    unsigned char reserved_212[2];
    unsigned int value_214;
    unsigned char byte_218;
    unsigned char byte_219;
    unsigned char byte_21a;
    unsigned char reserved_21b;
    std::deque<short> queue_21c;
    unsigned int peer_230;
    unsigned int value_234;
    unsigned char byte_238;
    unsigned char byte_239;
    unsigned char byte_23a;
    unsigned char reserved_23b;
    std::deque<short> queue_23c;
    unsigned int value_250;
    unsigned int value_254;
    unsigned char reserved_258[4];
    CriticalSectionWrapper critical_25c;
    unsigned char reserved_278[0x12d];
    unsigned char pending_3a5;
    unsigned char reserved_3a6[0x312];
    unsigned char sequence_6b8;
    unsigned char reserved_6b9[3];
    unsigned int value_6bc;
    unsigned int value_6c0;
    unsigned char reserved_6c4[4];
    std::deque<short> queue_6c8;
    unsigned char reserved_6dc[4];
    int sample_count_6e0;
};

bool CNetworkServerPublishView::publish_snapshot(
    NetworkStateRecord4CPublish *destination)
{
    CriticalSectionWrapper *state_lock = &critical_25c;
    state_lock->enter();
    const unsigned char pending = pending_3a5;
    state_lock->leave();
    if (pending) {
        critical_0dc.enter();
        queue_6c8.clear();
        const bool no_samples = sample_count_6e0 == 0;
        value_6bc = 0;
        value_6c0 = 0;
        if (no_samples) {
            ++sequence_6b8;
            if (sequence_6b8 == 0)
                sequence_6b8 = 1;
        }
        critical_0dc.leave();

        state_lock->enter();
        destination->value_008 = value_214;
        destination->byte_00c = byte_218;
        destination->byte_00d = byte_219;
        destination->byte_00e = byte_21a;
        destination->queue_010 = queue_21c;
        destination->peer_024 = peer_230;
        destination->value_028 = value_234;
        destination->byte_02c = byte_238;
        destination->byte_02d = byte_239;
        destination->byte_02e = byte_23a;
        destination->queue_030 = queue_23c;
        destination->value_044 = value_250;
        destination->byte_005 = byte_211;
        destination->byte_004 = byte_210;
        destination->value_048 = value_254;
        const bool still_no_samples = sample_count_6e0 == 0;
        pending_3a5 = 0;
        if (!still_no_samples)
            slot_0b(5);
        state_lock->leave();
        return true;
    }
    return false;
}

typedef char NetworkAuxRecord39_queue_offset_must_be_0x20[
    offsetof(NetworkAuxRecord39, queue_020) == 0x20 ? 1 : -1];
typedef char CNetworkServerSmallRuntimeView_critical_offset_must_be_0xdc[
    offsetof(CNetworkServerSmallRuntimeView, critical_0dc) == 0xdc ? 1 : -1];
typedef char CNetworkServerSmallRuntimeView_counter_offset_must_be_0x6e0[
    offsetof(CNetworkServerSmallRuntimeView, counter_6e0) == 0x6e0 ? 1 : -1];
typedef char NetworkStateRecord4CPublish_size_must_be_0x4c[
    sizeof(NetworkStateRecord4CPublish) == 0x4c ? 1 : -1];
typedef char CNetworkServerPublishView_pending_offset_must_be_0x3a5[
    offsetof(CNetworkServerPublishView, pending_3a5) == 0x3a5 ? 1 : -1];
typedef char CNetworkServerPublishView_sample_offset_must_be_0x6e0[
    offsetof(CNetworkServerPublishView, sample_count_6e0) == 0x6e0 ? 1 : -1];

} // namespace th105
