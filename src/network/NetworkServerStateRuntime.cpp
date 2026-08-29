#include "../engine/CriticalSectionWrapper.hpp"

#include <deque>
#include <stddef.h>

namespace th105 {

struct NetworkByte4Peer {
    unsigned char reserved_000[4];
    unsigned char byte_004;
};

// Current server vtable slots 2/3 exchange this 0x4c state snapshot.  The two
// 0x14 members are native checked VC8 deque<short> objects.
struct NetworkStateRecord4C {
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

struct CNetworkServerStateView {
    void import_state(const NetworkStateRecord4C *source);
    bool export_state(NetworkStateRecord4C *destination);

    unsigned char reserved_000[0x0dc];
    CriticalSectionWrapper critical_0dc;
    unsigned char reserved_0f8[0x108];
    NetworkByte4Peer *peer_200;
    unsigned char reserved_204[0x0c];
    unsigned char byte_210;
    unsigned char byte_211;
    unsigned char reserved_212[2];
    unsigned int value_214;
    unsigned char byte_218;
    unsigned char byte_219;
    unsigned char byte_21a;
    unsigned char reserved_21b;
    std::deque<short> queue_21c;
    NetworkByte4Peer *peer_230;
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
    unsigned char export_pending_3a5;
    unsigned char ack_pending_3a6;
    unsigned char reserved_3a7[0x311];
    unsigned char sequence_6b8;
    unsigned char reserved_6b9[0x0f];
    std::deque<short> queue_6c8;
};

void CNetworkServerStateView::import_state(const NetworkStateRecord4C *source)
{
    critical_25c.enter();
    queue_21c = source->queue_010;
    peer_230->byte_004 = peer_200->byte_004;
    value_214 = source->value_008;
    byte_219 = source->byte_00d;
    byte_21a = source->byte_00e;
    value_234 = source->value_028;
    byte_239 = source->byte_02d;
    byte_23a = source->byte_02e;
    byte_210 = source->byte_004;
    byte_211 = source->byte_005;
    value_254 = source->value_048;
    ack_pending_3a6 = 1;
    critical_25c.leave();
}

bool CNetworkServerStateView::export_state(NetworkStateRecord4C *destination)
{
    critical_25c.enter();
    const unsigned char pending = export_pending_3a5;
    critical_25c.leave();
    if (pending) {
        critical_0dc.enter();
        ++sequence_6b8;
        if (sequence_6b8 == 0)
            sequence_6b8 = 1;
        queue_6c8.clear();
        critical_0dc.leave();

        critical_25c.enter();
        destination->value_008 = value_214;
        destination->byte_00c = byte_218;
        destination->byte_00d = byte_219;
        destination->byte_00e = byte_21a;
        destination->queue_010 = queue_21c;
        destination->peer_024 = reinterpret_cast<unsigned int>(peer_230);
        destination->value_028 = value_234;
        destination->byte_02c = byte_238;
        destination->byte_02d = byte_239;
        destination->byte_02e = byte_23a;
        destination->queue_030 = queue_23c;
        destination->value_044 = value_250;
        destination->byte_005 = byte_211;
        destination->byte_004 = byte_210;
        destination->value_048 = value_254;
        export_pending_3a5 = 0;
        critical_25c.leave();
        return true;
    }
    return false;
}

struct NetworkAckRecord24 {
    unsigned char reserved_000[0x08];
    unsigned int sequence_008;
    unsigned char peer_tag_00c;
    unsigned char reserved_00d[3];
    std::deque<short> values_010;
};

struct CNetworkServerAckRecordView {
    void consume_ack(const NetworkAckRecord24 *record);

    unsigned char reserved_000[0x48];
    CriticalSectionWrapper critical_048;
    unsigned char reserved_064[0x08];
    unsigned char peer_tag_06c;
    unsigned char reserved_06d[0x11];
    unsigned short value_07e;
    unsigned char reserved_080[0x18];
    unsigned int sequence_limit_098;
    unsigned char reserved_09c[0x64c];
    unsigned int sequence_high_water_6e8;
};

void CNetworkServerAckRecordView::consume_ack(const NetworkAckRecord24 *record)
{
    critical_048.enter();
    if (record->sequence_008 <= sequence_limit_098 &&
        record->peer_tag_00c == peer_tag_06c) {
        if (!record->values_010.empty())
            value_07e = record->values_010.at(0);
        else
            value_07e = 0;
        const unsigned int sequence = record->sequence_008;
        if (sequence_high_water_6e8 < sequence)
            sequence_high_water_6e8 = sequence;
    }
    critical_048.leave();
}

typedef char NetworkStateRecord4C_size_must_be_0x4c[
    sizeof(NetworkStateRecord4C) == 0x4c ? 1 : -1];
typedef char CNetworkServerStateView_critical_offset_must_be_0x25c[
    offsetof(CNetworkServerStateView, critical_25c) == 0x25c ? 1 : -1];
typedef char CNetworkServerStateView_flags_offset_must_be_0x3a5[
    offsetof(CNetworkServerStateView, export_pending_3a5) == 0x3a5 ? 1 : -1];
typedef char CNetworkServerStateView_queue_offset_must_be_0x6c8[
    offsetof(CNetworkServerStateView, queue_6c8) == 0x6c8 ? 1 : -1];
typedef char NetworkAckRecord24_size_must_be_0x24[
    sizeof(NetworkAckRecord24) == 0x24 ? 1 : -1];
typedef char CNetworkServerAckRecordView_high_water_offset_must_be_0x6e8[
    offsetof(CNetworkServerAckRecordView, sequence_high_water_6e8) == 0x6e8 ? 1 : -1];

} // namespace th105
