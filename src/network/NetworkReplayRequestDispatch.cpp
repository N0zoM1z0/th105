#include "engine/CriticalSectionWrapper.hpp"
#include "NetworkAckInfoPacket.hpp"
#include <deque>
#include <stddef.h>
namespace th105 {
struct DispatchResultBase { DispatchResultBase(): result(0) {} unsigned result; };
struct DispatchPacketView { virtual unsigned serialize(void *buffer); };
struct DispatchReplay : DispatchResultBase {
    DispatchReplay() {}
    virtual unsigned serialize(void *buffer);
    unsigned sequence, metadata;
    unsigned char tag, reserved[3];
    std::deque<short> values;
};
struct DispatchRequest { unsigned char reserved[8]; unsigned sequence; unsigned char tag; };
struct DispatchPeer { unsigned char reserved[4]; unsigned char value; };
struct DispatchSide {
    unsigned char value; unsigned char reserved1[4]; unsigned char status; unsigned char reserved2[2];
    std::deque<short> values; DispatchPeer *peer;
};
struct DispatchSend {
    void send(unsigned channel, const void *data, unsigned size, int option, unsigned *result);
};
struct DispatchOwner {
    unsigned char reserved_000[0xdc]; CriticalSectionWrapper replay_lock;
    unsigned char reserved_0f8[0x118]; unsigned char tail0,tail1; unsigned char reserved_212[2];
    DispatchSide sides[2]; unsigned tail_value; unsigned char reserved_258[4]; CriticalSectionWrapper ack_lock;
    unsigned char reserved_278[0x13c]; DispatchSend sender; unsigned char reserved_3b5[0x1ff];
    unsigned char buffer[0x100]; void *input_sink; unsigned char tag; unsigned char reserved_6b9[3];
    unsigned replay_sequence, replay_metadata, reserved_6c4; std::deque<short> history;
    void dispatch(unsigned channel, const DispatchRequest *request);
};
typedef char SideSize[sizeof(DispatchSide)==0x20?1:-1];
typedef char AckSize[sizeof(NetworkAckInfoPacket40)==0x40?1:-1];
typedef char ReplaySize[sizeof(DispatchReplay)==0x28?1:-1];
typedef char ReplayLockOff[offsetof(DispatchOwner,replay_lock)==0xdc?1:-1];
typedef char SideOff[offsetof(DispatchOwner,sides)==0x214?1:-1];
typedef char TailValueOff[offsetof(DispatchOwner,tail_value)==0x254?1:-1];
typedef char SenderOff[offsetof(DispatchOwner,sender)==0x3b4?1:-1];
typedef char BufferOff[offsetof(DispatchOwner,buffer)==0x5b4?1:-1];
typedef char TagOff[offsetof(DispatchOwner,tag)==0x6b8?1:-1];
typedef char MetadataOff[offsetof(DispatchOwner,replay_metadata)==0x6c0?1:-1];
typedef char HistoryOff[offsetof(DispatchOwner,history)==0x6c8?1:-1];
typedef char AckLockOff[offsetof(DispatchOwner,ack_lock)==0x25c?1:-1];
void DispatchOwner::dispatch(unsigned channel, const DispatchRequest *request)
{
    if (request->tag != tag) {
        NetworkAckInfoPacket40 packet;
        ack_lock.enter();
        for (int i=0;i<2;++i) {
            packet.value_008[i]=sides[i].value;
            packet.status_00a[i]=sides[i].status;
            packet.values_00c[i]=sides[i].values;
            packet.peer_034[i]=sides[i].peer->value;
        }
        packet.tail_036=tail0;
        packet.tail_038=tail_value;
        packet.tail_037=tail1;
        packet.sequence_03c=tag;
        DispatchPacketView *view=reinterpret_cast<DispatchPacketView *>(&packet);
        sender.send(channel,buffer,view->serialize(buffer),0,0);
        ack_lock.leave();
    } else {
        DispatchReplay packet;
        packet.sequence=request->sequence;
        packet.tag=tag;
        packet.metadata=replay_metadata;
        replay_lock.enter();
        for (unsigned i=request->sequence; i<request->sequence+60 && i<history.size(); ++i) {
            packet.values.push_back(history.at(i));
            ++packet.sequence;
        }
        replay_lock.leave();
        DispatchPacketView *view=reinterpret_cast<DispatchPacketView *>(&packet);
        sender.send(channel,buffer,view->serialize(buffer),0xa0,0);
    }
}
}
