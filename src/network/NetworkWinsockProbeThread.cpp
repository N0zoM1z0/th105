#include "engine/CriticalSectionWrapper.hpp"
#include <vector>
#include <string.h>

namespace th105 {
extern "C" __declspec(dllimport) void *__stdcall CreateEventA(
    void *attributes, int manual_reset, int initial_state, const char *name);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
    void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);
extern "C" int __stdcall sendto(unsigned int socket, const char *buffer,
    int size, int flags, const void *endpoint, int endpoint_size);

struct NetworkProbePeer20 {
    unsigned char endpoint_00[16];
    int slot_10;
    unsigned int probe_count_14;
    unsigned int unreviewed_18;
    unsigned int reported_value_1c;
};

struct NetworkUdpProbeWorkerView {
    unsigned char unreviewed_000[0x28];
    unsigned int socket_028;
    unsigned char unreviewed_02c[0x48];
    unsigned char running_074;
    unsigned char unreviewed_075[0x4b];
    unsigned char endpoint_0c0[16];
    unsigned char unreviewed_0d0[4];
    unsigned int probe_count_0d4;
    unsigned char unreviewed_0d8[8];
    CriticalSectionWrapper endpoint_lock_0e0;
    unsigned char unreviewed_0fc[0x0c];
    std::vector<NetworkProbePeer20> peers_108;
    unsigned int active_count_118;
    unsigned int limit_11c;
    CriticalSectionWrapper peer_lock_120;
    unsigned char unreviewed_13c[8];
    unsigned int state_144;

    void remove_peer(unsigned int slot);
};

extern "C" unsigned long __stdcall network_udp_service_thread_416f40(void *parameter)
{
    NetworkUdpProbeWorkerView *owner = static_cast<NetworkUdpProbeWorkerView *>(parameter);
    void *timer_event = CreateEventA(0, 0, 0, 0);
    // Only the five transmitted bytes are established; the original larger
    // local storage type and aligned frame remain unresolved.
    unsigned char packet[5];
    packet[0] = 4;
    while (owner->running_074) {
        const unsigned int active = owner->active_count_118;
        const unsigned long wait_ms = 500 / (active + 1) + 1;
        unsigned int reported = owner->limit_11c < active ? 0 : owner->limit_11c - active;
        EnterCriticalSection(&owner->peer_lock_120.critical_section_04);
        for (unsigned int slot = 0; slot < owner->peers_108.size(); ++slot) {
            if (owner->peers_108[slot].slot_10 != -1)
                reported += owner->peers_108[slot].reported_value_1c;
        }
        LeaveCriticalSection(&owner->peer_lock_120.critical_section_04);
        memcpy(packet + 1, &reported, sizeof(reported));
        for (unsigned int slot = 0; slot < owner->peers_108.size(); ++slot) {
            EnterCriticalSection(&owner->peer_lock_120.critical_section_04);
            if (owner->peers_108[slot].slot_10 != -1) {
                sendto(owner->socket_028, reinterpret_cast<const char *>(packet), 5, 0,
                       owner->peers_108[slot].endpoint_00, 16);
                if (owner->peers_108[slot].probe_count_14++ >= 10)
                    owner->remove_peer(slot);
                LeaveCriticalSection(&owner->peer_lock_120.critical_section_04);
                WaitForSingleObject(timer_event, wait_ms);
            } else {
                LeaveCriticalSection(&owner->peer_lock_120.critical_section_04);
            }
        }
        EnterCriticalSection(&owner->endpoint_lock_0e0.critical_section_04);
        if (owner->state_144 == 0) {
            sendto(owner->socket_028, reinterpret_cast<const char *>(packet), 5, 0,
                   owner->endpoint_0c0, 16);
            if (owner->probe_count_0d4++ >= 10)
                owner->state_144 = 6;
        }
        LeaveCriticalSection(&owner->endpoint_lock_0e0.critical_section_04);
        WaitForSingleObject(timer_event, wait_ms);
    }
    CloseHandle(timer_event);
    return 0;
}

typedef char ProbePeerSize[sizeof(NetworkProbePeer20) == 0x20 ? 1 : -1];
typedef char ProbeSocketOffset[offsetof(NetworkUdpProbeWorkerView, socket_028) == 0x28 ? 1 : -1];
typedef char ProbeRunningOffset[offsetof(NetworkUdpProbeWorkerView, running_074) == 0x74 ? 1 : -1];
typedef char ProbeEndpointOffset[offsetof(NetworkUdpProbeWorkerView, endpoint_0c0) == 0xc0 ? 1 : -1];
typedef char ProbeCounterOffset[offsetof(NetworkUdpProbeWorkerView, probe_count_0d4) == 0xd4 ? 1 : -1];
typedef char ProbeEndpointLockOffset[offsetof(NetworkUdpProbeWorkerView, endpoint_lock_0e0) == 0xe0 ? 1 : -1];
typedef char ProbePeersOffset[offsetof(NetworkUdpProbeWorkerView, peers_108) == 0x108 ? 1 : -1];
typedef char ProbeCountOffset[offsetof(NetworkUdpProbeWorkerView, active_count_118) == 0x118 ? 1 : -1];
typedef char ProbeLimitOffset[offsetof(NetworkUdpProbeWorkerView, limit_11c) == 0x11c ? 1 : -1];
typedef char ProbePeerLockOffset[offsetof(NetworkUdpProbeWorkerView, peer_lock_120) == 0x120 ? 1 : -1];
typedef char ProbeStateOffset[offsetof(NetworkUdpProbeWorkerView, state_144) == 0x144 ? 1 : -1];
} // namespace th105
