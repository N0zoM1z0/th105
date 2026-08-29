#include <stddef.h>

namespace th105 {

// Current CDPP_REQ_INFO construction proves this split layout.  The four-byte
// non-polymorphic base is initialized before the derived object publishes its
// vfptr; a single-level polymorphic class reverses those two stores.
struct NetworkRequestInfoBase4 {
    NetworkRequestInfoBase4() : value_004(0) {}
    unsigned int value_004;
};

class NetworkRequestInfo8 : public NetworkRequestInfoBase4 {
public:
    NetworkRequestInfo8() {}
    virtual unsigned int serialize(
        void *buffer, unsigned int capacity, void *extra);
};

struct NetworkServerSendView {
    void send_server(int channel, const void *buffer, unsigned int size);
};

struct NetworkClientSendView {
    void send_client(const void *buffer, unsigned int size);
};

struct CNetworkServerRequestView {
    void send_request_info();

    unsigned char reserved_000[0x3b4];
    NetworkServerSendView send_3b4;
    unsigned char reserved_3b5[0x1ff];
    unsigned char buffer_5b4[0x20];
};

void CNetworkServerRequestView::send_request_info()
{
    NetworkRequestInfo8 request;
    NetworkRequestInfo8 *packet = &request;
    const unsigned int size = packet->serialize(buffer_5b4, 0x20, 0);
    send_3b4.send_server(0, buffer_5b4, size);
}

struct CNetworkClientRequestView {
    void send_request_info();

    unsigned char reserved_000[0x3b4];
    NetworkClientSendView send_3b4;
    unsigned char reserved_3b5[0x1ff];
    unsigned char buffer_5b4[0x50];
};

void CNetworkClientRequestView::send_request_info()
{
    NetworkRequestInfo8 request;
    NetworkRequestInfo8 *packet = &request;
    const unsigned int size = packet->serialize(buffer_5b4, 0x50, 0);
    send_3b4.send_client(buffer_5b4, size);
}

typedef char NetworkRequestInfo8_size_must_be_0x08[
    sizeof(NetworkRequestInfo8) == 0x08 ? 1 : -1];
typedef char CNetworkServerRequestView_buffer_offset_must_be_0x5b4[
    offsetof(CNetworkServerRequestView, buffer_5b4) == 0x5b4 ? 1 : -1];
typedef char CNetworkClientRequestView_buffer_offset_must_be_0x5b4[
    offsetof(CNetworkClientRequestView, buffer_5b4) == 0x5b4 ? 1 : -1];

} // namespace th105
