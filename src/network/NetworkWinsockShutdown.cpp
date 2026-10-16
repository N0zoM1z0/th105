#include <winsock2.h>
#include <windows.h>
#include <cstdlib>
#include <stddef.h>
#include <vector>

namespace th105 {

struct BattleThreadHandleShutdownView {
    void *handle_00;
    unsigned long thread_id_04;

    void wait_for_exit();
};

struct NetworkShutdownPeer20 {
    unsigned char endpoint_00[16];
    int slot_10;
    unsigned char unreviewed_14[12];
};

struct NetworkWinsockShutdownView {
    unsigned char reserved_000[0x28];
    SOCKET socket_028;
    unsigned char reserved_02c[0x30];
    BattleThreadHandleShutdownView worker_05c;
    BattleThreadHandleShutdownView worker_064;
    BattleThreadHandleShutdownView worker_06c;
    unsigned char running_074;
    unsigned char reserved_075[3];
    void *heap_buffer_078;
    unsigned char reserved_07c[0x44];
    unsigned char endpoint_0c0[16];
    unsigned char unreviewed_0d0[0x14];
    CRITICAL_SECTION endpoint_lock_0e4;
    unsigned char unreviewed_0fc[0x0c];
    std::vector<NetworkShutdownPeer20> peers_108;
    unsigned char unreviewed_118[0x24];
    BattleThreadHandleShutdownView worker_13c;
    unsigned int state_144;
    unsigned char reserved_148[0x98];
    HANDLE event_1e0;

    void remove_peer(unsigned int slot);
    void shutdown_412fd0();
};

extern "C" CRITICAL_SECTION g_winsock_ref_lock;
extern "C" unsigned int g_winsock_refcount;

static void __stdcall prepare_udp_shutdown(NetworkWinsockShutdownView *owner)
{
    const unsigned char opcode = 0x0b;
    EnterCriticalSection(&owner->endpoint_lock_0e4);
    sendto(owner->socket_028, reinterpret_cast<const char *>(&opcode), 1, 0,
           reinterpret_cast<const sockaddr *>(owner->endpoint_0c0), 16);
    LeaveCriticalSection(&owner->endpoint_lock_0e4);
    for (unsigned int slot = 0; slot < owner->peers_108.size(); ++slot)
        owner->remove_peer(slot);
    owner->state_144 = 1;
}

void NetworkWinsockShutdownView::shutdown_412fd0()
{
    if (!running_074)
        return;

    prepare_udp_shutdown(this);
    running_074 = 0;
    SetEvent(event_1e0);

    worker_13c.wait_for_exit();
    worker_06c.wait_for_exit();

    shutdown(socket_028, 1);
    shutdown(socket_028, 0);
    closesocket(socket_028);

    worker_05c.wait_for_exit();
    worker_064.wait_for_exit();

    EnterCriticalSection(&g_winsock_ref_lock);
    if (g_winsock_refcount > 0) {
        --g_winsock_refcount;
        if (g_winsock_refcount == 0)
            WSACleanup();
    }
    LeaveCriticalSection(&g_winsock_ref_lock);

    if (heap_buffer_078 != 0) {
        std::free(heap_buffer_078);
        heap_buffer_078 = 0;
    }
}

typedef char NetworkWinsockShutdownView_socket_offset[
    offsetof(NetworkWinsockShutdownView, socket_028) == 0x28 ? 1 : -1];
typedef char NetworkWinsockShutdownView_running_offset[
    offsetof(NetworkWinsockShutdownView, running_074) == 0x74 ? 1 : -1];
typedef char NetworkWinsockShutdownView_worker_offset[
    offsetof(NetworkWinsockShutdownView, worker_13c) == 0x13c ? 1 : -1];
typedef char NetworkWinsockShutdownView_event_offset[
    offsetof(NetworkWinsockShutdownView, event_1e0) == 0x1e0 ? 1 : -1];

typedef char ShutdownPeerSize[
    sizeof(NetworkShutdownPeer20) == 0x20 ? 1 : -1];
typedef char ShutdownEndpointOffset[
    offsetof(NetworkWinsockShutdownView, endpoint_0c0) == 0xc0 ? 1 : -1];
typedef char ShutdownEndpointLockOffset[
    offsetof(NetworkWinsockShutdownView, endpoint_lock_0e4) == 0xe4 ? 1 : -1];
typedef char ShutdownPeerOffset[
    offsetof(NetworkWinsockShutdownView, peers_108) == 0x108 ? 1 : -1];
typedef char ShutdownStateOffset[
    offsetof(NetworkWinsockShutdownView, state_144) == 0x144 ? 1 : -1];
} // namespace th105
