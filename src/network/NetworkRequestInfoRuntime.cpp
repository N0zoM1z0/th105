#include "NetworkSimplePackets.hpp"
#include "NetworkWinsockSendClient.hpp"
#include <stddef.h>

namespace th105 {

struct CNetworkServerRequestView {
    void send_request_info();

    unsigned char reserved_000[0x3b4];
    NetworkWinsockSendClientView send_3b4;
    unsigned char buffer_5b4[0x20];
};

void CNetworkServerRequestView::send_request_info()
{
    NetworkRequestInfo8 request;
    NetworkRequestInfo8 *packet = &request;
    send_3b4.send_server(
        0, buffer_5b4, packet->serialize(buffer_5b4), 0x20, 0);
}

struct CNetworkClientRequestView {
    void send_request_info();

    unsigned char reserved_000[0x3b4];
    NetworkWinsockSendClientView send_3b4;
    unsigned char buffer_5b4[0x50];
};

void CNetworkClientRequestView::send_request_info()
{
    NetworkRequestInfo8 request;
    NetworkRequestInfo8 *packet = &request;
    send_3b4.send_client(
        buffer_5b4, packet->serialize(buffer_5b4), 0x50, 0);
}

typedef char NetworkRequestInfo8_size_must_be_0x08[
    sizeof(NetworkRequestInfo8) == 0x08 ? 1 : -1];
typedef char CNetworkServerRequestView_buffer_offset_must_be_0x5b4[
    offsetof(CNetworkServerRequestView, buffer_5b4) == 0x5b4 ? 1 : -1];
typedef char CNetworkClientRequestView_buffer_offset_must_be_0x5b4[
    offsetof(CNetworkClientRequestView, buffer_5b4) == 0x5b4 ? 1 : -1];

} // namespace th105
