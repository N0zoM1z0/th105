#include "NetworkAckInfoPacket.hpp"
#include <deque>
#include <stddef.h>
#include <string.h>

namespace th105 {

typedef char ack_size[sizeof(NetworkAckInfoPacket40)==0x40?1:-1];
typedef char ack_value[offsetof(NetworkAckInfoPacket40,value_008)==0x08?1:-1];
typedef char ack_status[offsetof(NetworkAckInfoPacket40,status_00a)==0x0a?1:-1];
typedef char ack_deque[offsetof(NetworkAckInfoPacket40,values_00c)==0x0c?1:-1];
typedef char ack_peer[offsetof(NetworkAckInfoPacket40,peer_034)==0x34?1:-1];
typedef char ack_tail[offsetof(NetworkAckInfoPacket40,tail_038)==0x38?1:-1];

unsigned int NetworkAckInfoPacket40::serialize(void *buffer)
{
    unsigned char *output = static_cast<unsigned char *>(buffer);
    *output++ = 4;
    for (int side = 0; side < 2; ++side) {
        *output++ = value_008[side];
        *output++ = status_00a[side];
        *output++ = static_cast<unsigned char>(values_00c[side].size());
        unsigned index = 0;
        if (values_00c[side].size() > 0) {
            do {
                const short &value = values_00c[side].at(index);
                memcpy(output, &value, sizeof(value));
                output += 2;
                ++index;
            } while (index < values_00c[side].size());
        }
        *output++ = peer_034[side];
    }
    *output++ = tail_036;
    *output++ = tail_037;
    memcpy(output, &tail_038, sizeof(tail_038));
    output += 4;
    *output++ = sequence_03c;
    return static_cast<unsigned int>(output - static_cast<unsigned char *>(buffer));
}

void NetworkAckInfoPacket40::parse(const unsigned char *input)
{
    const unsigned char *source = input + 1;
    for (int side = 0; side < 2; ++side) {
        value_008[side] = *source++;
        status_00a[side] = *source++;
        unsigned char count = *source++;
        values_00c[side].clear();
        if (count > 20) {
            tail_036 = 0;
            tail_037 = 0;
            return;
        }
        if (count > 0) {
            int remaining = count;
            do {
                short value;
                memcpy(&value, source, sizeof(value));
                values_00c[side].push_back(value);
                source += 2;
            } while (--remaining);
        }
        peer_034[side] = *source++;
    }
    tail_036 = *source++;
    tail_037 = *source++;
    memcpy(&tail_038, source, sizeof(tail_038));
    source += 4;
    sequence_03c = *source;
}

} // namespace th105
