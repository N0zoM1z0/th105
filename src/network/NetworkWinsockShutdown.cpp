#include <winsock2.h>
#include <windows.h>
#include <cstdlib>
#include <stddef.h>

namespace th105 {

struct BattleThreadHandleShutdownView {
    void *handle_00;
    unsigned long thread_id_04;

    void wait_for_exit();
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
    unsigned char reserved_07c[0xc0];
    BattleThreadHandleShutdownView worker_13c;
    unsigned char reserved_144[0x9c];
    HANDLE event_1e0;

    void prepare_shutdown_4130d0();
    void shutdown_412fd0();
};

extern "C" CRITICAL_SECTION g_winsock_ref_lock;
extern "C" unsigned int g_winsock_refcount;

void NetworkWinsockShutdownView::shutdown_412fd0()
{
    if (!running_074)
        return;

    prepare_shutdown_4130d0();
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

} // namespace th105
