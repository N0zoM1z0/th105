#include "NetworkSimplePackets.hpp"

namespace th105 {

struct NetworkPacketByte12 {
    unsigned char reserved_000[8];
    unsigned char value_008;

    unsigned int serialize_type1(unsigned char *out) const;
    void parse_type1(const unsigned char *in);
};

unsigned int NetworkPacketByte12::serialize_type1(unsigned char *out) const
{
    out[0] = 1;
    out[1] = value_008;
    return 2;
}

void NetworkPacketByte12::parse_type1(const unsigned char *in)
{
    value_008 = in[1];
}

unsigned int SceneAckPacket0C::serialize(void *buffer)
{
    unsigned char *out = static_cast<unsigned char *>(buffer);
    out[0] = 2;
    out[1] = state_008;
    return 2;
}

unsigned int NetworkRequestInfo8::serialize(void *buffer)
{
    unsigned char *out = static_cast<unsigned char *>(buffer);
    out[0] = 5;
    return 1;
}

unsigned int NetworkDelayPacket12::serialize(void *buffer)
{
    unsigned char *out = static_cast<unsigned char *>(buffer);
    out[0] = 7;
    out[1] = delay_008;
    return 2;
}

unsigned int NetworkTerminatePacket8::serialize(void *buffer)
{
    unsigned char *out = static_cast<unsigned char *>(buffer);
    out[0] = 8;
    return 1;
}

} // namespace th105
