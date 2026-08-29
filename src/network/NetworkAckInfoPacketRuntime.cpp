#include <deque>
#include <stddef.h>

namespace th105 {

struct AckPacketResultBase4Runtime {
    unsigned int result_004;
};

class NetworkAckInfoPacket40Runtime : public AckPacketResultBase4Runtime {
public:
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

typedef char ack_size[sizeof(NetworkAckInfoPacket40Runtime)==0x40?1:-1];
typedef char ack_value[offsetof(NetworkAckInfoPacket40Runtime,value_008)==0x08?1:-1];
typedef char ack_status[offsetof(NetworkAckInfoPacket40Runtime,status_00a)==0x0a?1:-1];
typedef char ack_deque[offsetof(NetworkAckInfoPacket40Runtime,values_00c)==0x0c?1:-1];
typedef char ack_peer[offsetof(NetworkAckInfoPacket40Runtime,peer_034)==0x34?1:-1];
typedef char ack_tail[offsetof(NetworkAckInfoPacket40Runtime,tail_038)==0x38?1:-1];

unsigned int NetworkAckInfoPacket40Runtime::serialize(void *buffer)
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
                *reinterpret_cast<unsigned short *>(output) =
                    static_cast<unsigned short>(values_00c[side].at(index));
                output += 2;
                ++index;
            } while (index < values_00c[side].size());
        }
        *output++ = peer_034[side];
    }
    *output++ = tail_036;
    *output++ = tail_037;
    *reinterpret_cast<unsigned int *>(output) = tail_038;
    output += 4;
    *output++ = sequence_03c;
    return static_cast<unsigned int>(output - static_cast<unsigned char *>(buffer));
}

char NetworkAckInfoPacket40Runtime::parse(const unsigned char *input)
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
            return static_cast<char>(count);
        }
        if (count > 0) {
            int remaining = count;
            do {
                int value = *reinterpret_cast<const unsigned short *>(source);
                values_00c[side].push_back(reinterpret_cast<const short &>(value));
                source += 2;
            } while (--remaining);
        }
        peer_034[side] = *source++;
    }
    tail_036 = *source++;
    tail_037 = *source++;
    tail_038 = *reinterpret_cast<const unsigned int *>(source);
    source += 4;
    sequence_03c = *source;
    return static_cast<char>(tail_038);
}

} // namespace th105
