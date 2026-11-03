#pragma once

namespace th105 {

// RTTI identifies IPacket as the offset-zero polymorphic base. The serializer
// slot and result word are established; original spelling and abstractness are unknown.
struct NetworkPacketBase8 {
    NetworkPacketBase8() : result_004(0) {}
    virtual unsigned int serialize(void *buffer);
    unsigned int result_004;
};

typedef char NetworkPacketBaseSize[sizeof(NetworkPacketBase8) == 8 ? 1 : -1];

} // namespace th105
