#include <stddef.h>
#include <string.h>

namespace th105 {

struct NetworkClientOwnerSecondaryView {
    int dispatch_secondary_request(int context, const void *packet);

    unsigned char reserved_000[0x04];
    unsigned char state_blob_004[0x44];
    unsigned char reserved_048[0x360];
    unsigned char option_flag_3a8;
    unsigned char reserved_3a9[3];
    int option_bits_3ac;
    int copied_state_3b0;
    unsigned char reserved_3b4[0x11c];
    int mode_4d0;
    unsigned char reserved_4d4[0x208];
};

#pragma pack(push, 1)
struct NetworkInboundReplay6 {
    unsigned char type_000;
    unsigned int value_001;
    unsigned char tag_005;
};
#pragma pack(pop)

struct NetworkRequestReplayBase4 {
    NetworkRequestReplayBase4() : base_value_004(0) {}
    unsigned int base_value_004;
};

class NetworkRequestReplay10 : public NetworkRequestReplayBase4 {
public:
    NetworkRequestReplay10() {}
    virtual unsigned int packet_type() const;

    unsigned int value_008;
    unsigned char tag_00c;
    unsigned char reserved_00d[3];
};

// The factory at 0x0043CEA1 allocates 0x6E4 bytes.  Current RTTI fixes this
// secondary subobject at +0x6DC, so the interface itself is eight bytes:
// vfptr + one state dword.  Its methods use the current-proven owner relation
// rather than pretending the secondary object is standalone.
class CNetworkClientSecondaryView {
public:
    virtual CNetworkClientSecondaryView *configure(
        int flags, const void *state_blob, int unused);
    virtual int set_option_bits(int value);
    virtual void slot_2();
    virtual int handle_request(
        int context, const NetworkInboundReplay6 *packet, int unused);

    int secondary_state_004;

private:
    NetworkClientOwnerSecondaryView *owner()
    {
        return reinterpret_cast<NetworkClientOwnerSecondaryView *>(
            reinterpret_cast<unsigned char *>(this) - 0x6dc);
    }
};

CNetworkClientSecondaryView *CNetworkClientSecondaryView::configure(
    int flags, const void *state_blob, int)
{
    NetworkClientOwnerSecondaryView *primary = owner();
    primary->option_bits_3ac = flags;
    if ((flags & 1) != 0) {
        secondary_state_004 = 1;
        primary->mode_4d0 = 4;
    } else {
        secondary_state_004 = 0;
    }
    primary->option_flag_3a8 = static_cast<unsigned char>(
        (static_cast<unsigned int>(flags) & 0x10u) > 0);
    memcpy(primary->state_blob_004, state_blob, 0x44);
    primary->copied_state_3b0 =
        *reinterpret_cast<const int *>(primary->state_blob_004 + 0x40);
    return this;
}

int CNetworkClientSecondaryView::set_option_bits(int value)
{
    owner()->option_bits_3ac = value;
    return value;
}

int CNetworkClientSecondaryView::handle_request(
    int context, const NetworkInboundReplay6 *packet, int)
{
    if (packet->type_000 == 11) {
        NetworkRequestReplay10 request;
        request.value_008 = packet->value_001;
        request.tag_00c = packet->tag_005;
        return owner()->dispatch_secondary_request(context, &request);
    }
    return reinterpret_cast<int>(packet);
}

typedef char NetworkClientOwnerSecondaryView_size_must_be_0x6dc[
    sizeof(NetworkClientOwnerSecondaryView) == 0x6dc ? 1 : -1];
typedef char NetworkInboundReplay6_size_must_be_0x06[
    sizeof(NetworkInboundReplay6) == 0x06 ? 1 : -1];
typedef char NetworkRequestReplay10_size_must_be_0x10[
    sizeof(NetworkRequestReplay10) == 0x10 ? 1 : -1];
typedef char CNetworkClientSecondaryView_size_must_be_0x08[
    sizeof(CNetworkClientSecondaryView) == 0x08 ? 1 : -1];

} // namespace th105
