#include "engine/CriticalSectionWrapper.hpp"
#include "NetworkAckInfoPacket.hpp"
#include "NetworkReplayPacket.hpp"
#include "NetworkReplayRequestPacket.hpp"
#include <deque>
#include <stddef.h>
namespace th105 {
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
    void dispatch(unsigned channel, const NetworkRequestReplay10 *request);
};
typedef char SideSize[sizeof(DispatchSide)==0x20?1:-1];
typedef char AckSize[sizeof(NetworkAckInfoPacket40)==0x40?1:-1];
typedef char ReplaySize[sizeof(ReplayPacket28)==0x28?1:-1];
typedef char ReplayLockOff[offsetof(DispatchOwner,replay_lock)==0xdc?1:-1];
typedef char SideOff[offsetof(DispatchOwner,sides)==0x214?1:-1];
typedef char TailValueOff[offsetof(DispatchOwner,tail_value)==0x254?1:-1];
typedef char SenderOff[offsetof(DispatchOwner,sender)==0x3b4?1:-1];
typedef char BufferOff[offsetof(DispatchOwner,buffer)==0x5b4?1:-1];
typedef char TagOff[offsetof(DispatchOwner,tag)==0x6b8?1:-1];
typedef char MetadataOff[offsetof(DispatchOwner,replay_metadata)==0x6c0?1:-1];
typedef char HistoryOff[offsetof(DispatchOwner,history)==0x6c8?1:-1];
typedef char AckLockOff[offsetof(DispatchOwner,ack_lock)==0x25c?1:-1];
void DispatchOwner::dispatch(unsigned channel, const NetworkRequestReplay10 *request)
{
    if (request->tag_00c != tag) {
        NetworkAckInfoPacket40 packet;
        ack_lock.enter();
        for (int i=0;i<2;++i) {
            packet.value_008[i]=sides[i].value;
            packet.status_00a[i]=sides[i].status;
            packet.values_00c[i]=sides[i].values;
            packet.peer_034[i]=sides[i].peer->value;
        }
        packet.tail_036=tail0;
        packet.tail_037=tail1;
        packet.tail_038=tail_value;
        packet.sequence_03c=tag;
        NetworkPacketBase8 *view=&packet;
        sender.send(channel,buffer,view->serialize(buffer),0,0);
        ack_lock.leave();
    } else {
        ReplayPacket28 packet;
        packet.sequence_008=request->value_008;
        packet.tag_010=tag;
        packet.metadata_00c=replay_metadata;
        replay_lock.enter();
        for (unsigned i=request->value_008; i<request->value_008+60 && i<history.size(); ++i) {
            packet.values_014.push_back(history.at(i));
            ++packet.sequence_008;
        }
        replay_lock.leave();
        NetworkPacketBase8 *view=&packet;
        sender.send(channel,buffer,view->serialize(buffer),0xa0,0);
    }
}
}
