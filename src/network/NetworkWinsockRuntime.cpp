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

typedef char NetworkWinsockDataSize[sizeof(WSADATA) == 0x190 ? 1 : -1];

} // namespace th105
