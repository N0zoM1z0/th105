#include "engine/CriticalSectionWrapper.hpp"
#include "input/InputSelection.hpp"
#include <deque>
#include <stddef.h>
namespace th105 {
struct NetworkImportPeer { unsigned char reserved[4]; unsigned char value_004; };
struct NetworkImportPacket {
    unsigned char reserved_000[8];
    unsigned char value_008[2];
    unsigned char tag_00a[2];
    std::deque<short> queues_00c[2];
    unsigned char peer_byte_034[2];
    unsigned char flag_036, flag_037;
    unsigned int value_038;
    unsigned char sequence_03c;
};
struct ClientImportSlot {
    unsigned int value_000;
    unsigned char reserved_004, tag_005, reserved_006[2];
    std::deque<short> queue_008;
    NetworkImportPeer *peer_01c;
};
struct PlayerSlotCopyView {
    std::deque<unsigned short> *copy_deck(std::deque<unsigned short> *, int);
};
class ScopedClientStateLock {
public:
    explicit ScopedClientStateLock(CriticalSectionWrapper *lock) : lock_(lock) { lock_->enter(); }
    ~ScopedClientStateLock() { lock_->leave(); }
private:
    CriticalSectionWrapper *lock_;
};
class ClientImportView {
public:
    virtual ~ClientImportView();
    virtual void slot_04(); virtual void slot_08(); virtual void slot_0c();
    virtual void slot_10(); virtual void slot_14();
    virtual void import_snapshot(const NetworkImportPacket *packet);
    virtual void slot_1c(); virtual void slot_20(); virtual void slot_24();
    virtual void slot_28(); virtual void set_state(unsigned char);
    unsigned char reserved_004[0x20c];
    unsigned char flag_210, flag_211, reserved_212[2];
    ClientImportSlot slots_214[2];
    unsigned int value_254;
    unsigned char reserved_258[4];
    CriticalSectionWrapper critical_25c;
    unsigned char reserved_278[0x12d];
    unsigned char pending_3a5;
    unsigned char reserved_3a6[0x312];
    unsigned char sequence_6b8;
    unsigned char reserved_6b9[3];
    unsigned int value_6bc, value_6c0;
    unsigned char reserved_6c4[0x1c];
    int mode_6e0;
};
typedef char ImportPacketExtent[sizeof(NetworkImportPacket)==0x40?1:-1];
typedef char ImportLockOffset[offsetof(ClientImportView,critical_25c)==0x25c?1:-1];
typedef char ImportModeOffset[offsetof(ClientImportView,mode_6e0)==0x6e0?1:-1];
void ClientImportView::import_snapshot(const NetworkImportPacket *packet)
{
    ScopedClientStateLock scope(&critical_25c);
    if (mode_6e0 == 1) {
        if (sequence_6b8 != packet->sequence_03c) {
            set_state(3);
            unsigned char sequence = packet->sequence_03c;
            value_6bc = 0;
            value_6c0 = 0;
            sequence_6b8 = sequence;
            for (int i = 0; i < 2; ++i) {
                slots_214[i].value_000 = packet->value_008[i];
                slots_214[i].tag_005 = packet->tag_00a[i];
                slots_214[i].queue_008 = packet->queues_00c[i];
                slots_214[i].peer_01c->value_004 = packet->peer_byte_034[i];
            }
            flag_210 = packet->flag_036;
            flag_211 = packet->flag_037;
            value_254 = packet->value_038;
        }
    } else {
        slots_214[0].value_000 = packet->value_008[0];
        slots_214[0].tag_005 = packet->tag_00a[0];
        slots_214[1].value_000 = packet->value_008[1];
        slots_214[1].tag_005 = packet->tag_00a[1];
        slots_214[0].queue_008 = packet->queues_00c[0];
        slots_214[0].peer_01c->value_004 = packet->peer_byte_034[0];
        reinterpret_cast<PlayerSlotCopyView *>(get_player_slot_record(0))->copy_deck(
            reinterpret_cast<std::deque<unsigned short> *>(&slots_214[1].queue_008), slots_214[1].value_000);
        flag_210 = packet->flag_036;
        flag_211 = packet->flag_037;
        value_254 = packet->value_038;
    }
    pending_3a5 = 1;
}
}
