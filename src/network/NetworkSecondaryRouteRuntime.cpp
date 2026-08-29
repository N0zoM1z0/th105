#include <stddef.h>
#include <string.h>

namespace th105 {

struct NetworkClientOwnerRouteView {
    unsigned char reserved_000[0x04];
    unsigned char state_blob_004[0x44];
    unsigned char reserved_048[0x360];
    unsigned char option_flag_3a8;
    unsigned char reserved_3a9[0x333];
};

class CNetworkClientSecondaryRouteView {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual int route_payload(
        int unused0,
        int *code,
        const unsigned char *packet,
        int unused1,
        void **data,
        unsigned short *length);

private:
    NetworkClientOwnerRouteView *owner()
    {
        return reinterpret_cast<NetworkClientOwnerRouteView *>(
            reinterpret_cast<unsigned char *>(this) - 0x6dc);
    }
};

int CNetworkClientSecondaryRouteView::route_payload(
    int,
    int *code,
    const unsigned char *packet,
    int,
    void **data,
    unsigned short *length)
{
    NetworkClientOwnerRouteView *primary = owner();
    if (packet[0] != 0) {
        *code = static_cast<unsigned char>(primary->option_flag_3a8);
        return 9;
    }
    if (primary->option_flag_3a8 == 0) {
        *code = 0;
        return 9;
    }
    *code = 17;
    *data = primary->state_blob_004;
    *length = 0x44;
    return 0;
}

struct NetworkServerOwnerRouteView {
    unsigned char reserved_000[0x04];
    unsigned char state_blob_004[0x20];
    char name_024[0x20];
    int published_044;
    unsigned char reserved_048[0x35c];
    unsigned char route_ready_3a4;
    unsigned char reserved_3a5[3];
    unsigned char option_flag_3a8;
    unsigned char reserved_3a9[7];
    int copied_state_3b0;
    unsigned char reserved_3b4[0x328];
};

class CNetworkServerSecondaryRouteView {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual int route_payload(
        unsigned int direction,
        int *code,
        const unsigned char *packet,
        int unused,
        void **data,
        unsigned short *length);

private:
    NetworkServerOwnerRouteView *owner()
    {
        return reinterpret_cast<NetworkServerOwnerRouteView *>(
            reinterpret_cast<unsigned char *>(this) - 0x6dc);
    }
};

int CNetworkServerSecondaryRouteView::route_payload(
    unsigned int direction,
    int *code,
    const unsigned char *packet,
    int,
    void **data,
    unsigned short *length)
{
    NetworkServerOwnerRouteView *primary = owner();
    if (direction > 0) {
        if (packet[0]) {
            *code = -1;
            return 9;
        }
        if (!primary->option_flag_3a8) {
            *code = 0;
            return 9;
        }
        if (!primary->route_ready_3a4) {
            *code = 1;
            return 9;
        }
        *code = 17;
    } else {
        if (primary->route_ready_3a4) {
            *code = -1;
            return 9;
        }
        if (!packet[0]) {
            *code = primary->option_flag_3a8 != 0;
            return 9;
        }
        signed char count = static_cast<signed char>(packet[1]);
        if (static_cast<unsigned char>(count) < 0x20 && count > 0) {
            strncpy_s(
                primary->name_024,
                0x20,
                reinterpret_cast<const char *>(packet + 2),
                count);
            const bool option = primary->option_flag_3a8 != 0;
            primary->route_ready_3a4 = 1;
            *code = option ? 0x10 : 0;
        } else {
            *code = -1;
            return 9;
        }
    }

    primary->published_044 = primary->copied_state_3b0;
    *data = primary->state_blob_004;
    *length = 0x44;
    return 0;
}

typedef char ClientRouteOwnerSize[
    sizeof(NetworkClientOwnerRouteView) == 0x6dc ? 1 : -1];
typedef char ServerRouteOwnerSize[
    sizeof(NetworkServerOwnerRouteView) == 0x6dc ? 1 : -1];

} // namespace th105
