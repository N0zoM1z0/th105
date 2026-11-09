#include "NetworkUdpEvent.hpp"

// Native INetworkUDPEventProc default callback policy. The physical base table
// shares the three-word no-op and one-word no-op among multiple event slots.

void INetworkUDPEventProc::on_accepted(unsigned, const void *, unsigned) {}
void INetworkUDPEventProc::on_rejected(unsigned) {}
void INetworkUDPEventProc::on_primary_data(const void *, int) {}
void INetworkUDPEventProc::on_peer_data(unsigned, const void *, int) {}
int INetworkUDPEventProc::route_payload(unsigned, int *,
    const unsigned char *, int, void **, unsigned short *)
{
    return 9;
}
void INetworkUDPEventProc::on_peer_removed(unsigned) {}
