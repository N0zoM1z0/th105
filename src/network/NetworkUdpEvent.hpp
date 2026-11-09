#pragma once

// Original six-slot UDP event interface; there is no virtual destructor.
class INetworkUDPEventProc {
public:
    virtual void on_accepted(unsigned code, const void *payload, unsigned size);
    virtual void on_rejected(unsigned code);
    virtual void on_primary_data(const void *payload, int size);
    virtual void on_peer_data(unsigned slot, const void *payload, int size);
    virtual int route_payload(unsigned slot, int *code,
        const unsigned char *payload, int size, void **reply,
        unsigned short *reply_size);
    virtual void on_peer_removed(unsigned slot);
private:
    int state_04;
};

typedef char NetworkUdpEventInterfaceSize[
    sizeof(INetworkUDPEventProc) == 8 ? 1 : -1];
