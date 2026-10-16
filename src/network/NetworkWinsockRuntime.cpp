#include <winsock2.h>
#include <windows.h>

namespace th105 {
extern "C" CRITICAL_SECTION g_winsock_ref_lock;
extern "C" unsigned int g_winsock_refcount;
extern "C" WSADATA g_winsock_data;

static void __stdcall show_winsock_error(const char *text)
{
    char message[256];
    wsprintfA(message, "Winsock-Error:%05d %s", WSAGetLastError(), text);
    MessageBoxA(0, text, message, 0);
}

extern "C" bool network_winsock_acquire()
{
    EnterCriticalSection(&g_winsock_ref_lock);
    if (g_winsock_refcount == 0) {
        WSAStartup(2, &g_winsock_data);
        int error = WSAStartup(2, &g_winsock_data);
        if (error != 0) {
            switch (error) {
            case WSASYSNOTREADY: show_winsock_error("WSASYSNOTREADY"); break;
            case WSAVERNOTSUPPORTED: show_winsock_error("WSAVERNOTSUPPORTED"); break;
            case WSAEINPROGRESS: show_winsock_error("WSAEINPROGRESS"); break;
            case WSAEPROCLIM: show_winsock_error("WSAEPROCLIM"); break;
            case WSAEFAULT: show_winsock_error("WSAEFAULT"); break;
            }
            LeaveCriticalSection(&g_winsock_ref_lock);
            return false;
        }
    }
    ++g_winsock_refcount;
    LeaveCriticalSection(&g_winsock_ref_lock);
    return true;
}

extern "C" void network_winsock_release()
{
    EnterCriticalSection(&g_winsock_ref_lock);
    if (g_winsock_refcount > 0) {
        --g_winsock_refcount;
        if (g_winsock_refcount == 0)
            WSACleanup();
    }
    LeaveCriticalSection(&g_winsock_ref_lock);
}

typedef char NetworkWinsockDataSize[sizeof(WSADATA) == 0x190 ? 1 : -1];

} // namespace th105

#include <vector>
#include <deque>
#include <stdlib.h>
#include <stddef.h>

namespace th105 {
extern "C" const char network_udp_socket_error[];
extern "C" const char network_udp_bind_error[];
extern "C" unsigned long __stdcall network_winsock_send_thread(void *owner);
extern "C" unsigned long __stdcall network_winsock_receive_thread(void *owner);
extern "C" unsigned long __stdcall network_udp_service_thread_416f40(void *owner);

struct NetworkInitializeKey16 {
    int words_00[4];
};

// POD: the target initializes only slot_10 before copying the whole record.
struct NetworkInitializePeer20 {
    unsigned char endpoint_00[16];
    int slot_10;
    unsigned char unreviewed_14[12];
};

struct NetworkInitializeThread8 {
    void wait_for_exit();
    void start(LPTHREAD_START_ROUTINE entry, void *owner)
    {
        wait_for_exit();
        handle_00 = CreateThread(0, 0, entry, owner, 0, &thread_id_04);
    }
    HANDLE handle_00;
    DWORD thread_id_04;
};

class NetworkUdpInitializeView {
public:
    bool initialize(const NetworkInitializeKey16 *key, int port);
    unsigned char unreviewed_000[4];
    NetworkInitializeKey16 key_004;
    NetworkInitializeKey16 key_014;
    unsigned char unreviewed_024[4];
    SOCKET socket_028;
    sockaddr_in local_endpoint_02c;
    unsigned char unreviewed_03c[0x20];
    NetworkInitializeThread8 send_worker_05c;
    NetworkInitializeThread8 receive_worker_064;
    NetworkInitializeThread8 service_worker_06c;
    unsigned char running_074;
    unsigned char unreviewed_075[3];
    void *heap_buffer_078;
    unsigned char unreviewed_07c[0x8c];
    std::vector<NetworkInitializePeer20> peers_108;
    unsigned int active_peer_count_118;
    unsigned int peer_limit_11c;
    unsigned char unreviewed_120[0x24];
    unsigned int state_144;
    unsigned char unreviewed_148[0x20];
    std::deque<unsigned int> pending_tokens_168;
};

static bool __stdcall bind_udp_socket(NetworkUdpInitializeView *owner, int port);

bool NetworkUdpInitializeView::initialize(const NetworkInitializeKey16 *key, int port)
{
    state_144 = 1;
    peer_limit_11c = 16;
    NetworkInitializePeer20 peer;
    peer.slot_10 = -1;
    peers_108.assign(16, peer);
    active_peer_count_118 = 0;
    key_004 = *key;
    key_014 = *key;
    if (!network_winsock_acquire())
        return false;
    socket_028 = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_028 == INVALID_SOCKET) {
        show_winsock_error(network_udp_socket_error);
        network_winsock_release();
        return false;
    }
    if (!bind_udp_socket(this, port)) {
        network_winsock_release();
        return false;
    }
    if (heap_buffer_078 != 0) {
        free(heap_buffer_078);
        heap_buffer_078 = 0;
    }
    running_074 = 1;
    pending_tokens_168.clear();
    send_worker_05c.start(network_winsock_send_thread, this);
    SetThreadPriority(send_worker_05c.handle_00, 15);
    receive_worker_064.start(network_winsock_receive_thread, this);
    SetThreadPriority(receive_worker_064.handle_00, 15);
    service_worker_06c.start(network_udp_service_thread_416f40, this);
    return true;
}

static bool __stdcall bind_udp_socket(NetworkUdpInitializeView *owner, int port)
{
    owner->local_endpoint_02c.sin_family = AF_INET;
    owner->local_endpoint_02c.sin_port = htons(static_cast<unsigned short>(port));
    owner->local_endpoint_02c.sin_addr.s_addr = INADDR_ANY;
    if (bind(owner->socket_028, reinterpret_cast<const sockaddr *>(&owner->local_endpoint_02c),
             sizeof(owner->local_endpoint_02c)) == SOCKET_ERROR) {
        show_winsock_error(network_udp_bind_error);
        return false;
    }
    return true;
}

typedef char InitializePeerSize[sizeof(NetworkInitializePeer20)==0x20?1:-1];
typedef char InitializeThreadSize[sizeof(NetworkInitializeThread8)==8?1:-1];
typedef char InitializeKeySize[sizeof(NetworkInitializeKey16)==16?1:-1];
typedef char InitializeSocketOffset[offsetof(NetworkUdpInitializeView,socket_028)==0x28?1:-1];
typedef char InitializeSendThreadOffset[offsetof(NetworkUdpInitializeView,send_worker_05c)==0x5c?1:-1];
typedef char InitializeRunningOffset[offsetof(NetworkUdpInitializeView,running_074)==0x74?1:-1];
typedef char InitializePeerOffset[offsetof(NetworkUdpInitializeView,peers_108)==0x108?1:-1];
typedef char InitializeStateOffset[offsetof(NetworkUdpInitializeView,state_144)==0x144?1:-1];
typedef char InitializeQueueOffset[offsetof(NetworkUdpInitializeView,pending_tokens_168)==0x168?1:-1];
} // namespace th105
