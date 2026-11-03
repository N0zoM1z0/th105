#pragma once

namespace th105 {

// RTTI identifies IPacket as the offset-zero polymorphic base. The two concrete slots are serializer then parser; the shared void parser
// signature is inferred from implementations and unused return values.
struct NetworkPacketBase8 {
    NetworkPacketBase8() : result_004(0) {}
    virtual unsigned int serialize(void *buffer);
    virtual void parse(const unsigned char *input);
    unsigned int result_004;
};

typedef char NetworkPacketBaseSize[sizeof(NetworkPacketBase8) == 8 ? 1 : -1];

} // namespace th105
