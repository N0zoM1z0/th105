#include "../engine/CriticalSectionWrapper.hpp"
#include "NetworkUdpPacketPool.hpp"

#include <deque>
#include <map>
#include <stddef.h>
#include <stdlib.h>
#include <vector>

namespace th105 {

class NetworkWinsockPolymorphicBase {
public:
    __forceinline NetworkWinsockPolymorphicBase() {}
    virtual ~NetworkWinsockPolymorphicBase();

    unsigned char reserved_004[0x58];
};

struct NetworkThreadHandleCtorView {
    NetworkThreadHandleCtorView() : handle_00(0) {}
    ~NetworkThreadHandleCtorView();

    void wait_for_exit();

    void *handle_00;
    unsigned long thread_id_04;
};

typedef NetworkUdpPacketCriticalSectionView NetworkCriticalSectionCtorView;

NetworkWinsockPolymorphicBase::~NetworkWinsockPolymorphicBase()
{
}

NetworkThreadHandleCtorView::~NetworkThreadHandleCtorView()
{
    wait_for_exit();
}

// Endpoint lookup412A60 independently proves the +FC IP-key multimap.
struct NetworkPeerRecord20;
typedef std::multimap<unsigned int, NetworkPeerRecord20 *> NetworkPeerIndex0C;

// Lifetime-only two-trivial-word tree view; key/mapped semantics remain unknown.
typedef std::map<unsigned,unsigned> NetworkPendingTree0C;

struct NetworkSendRecord20CtorView {
    unsigned char reserved_00[0x20];
};

class NetworkWinsockState314CtorView : public NetworkWinsockPolymorphicBase {
public:
    NetworkWinsockState314CtorView();
    virtual ~NetworkWinsockState314CtorView();

public:
    NetworkThreadHandleCtorView worker_05c;
    NetworkThreadHandleCtorView worker_064;
    NetworkThreadHandleCtorView worker_06c;
    unsigned char running_074;
    unsigned char reserved_075[3];
    void *heap_buffer_078;
    unsigned short port_07c;
    unsigned char reserved_07e[2];
    void *callback_080;
    NetworkCriticalSectionCtorView critical_084;
    unsigned char reserved_0a0[0x40];
    NetworkCriticalSectionCtorView critical_0e0;
    NetworkPeerIndex0C peer_index_0fc;
    std::vector<NetworkSendRecord20CtorView> records_108;
    unsigned char reserved_118[8];
    NetworkCriticalSectionCtorView critical_120;
    NetworkThreadHandleCtorView worker_13c;
    unsigned char reserved_144[8];
    std::vector<unsigned int> indices_14c;
    NetworkPendingTree0C pending_15c;
    std::deque<unsigned int> pending_tokens_168;
    NetworkUdpPacketHandleManager64 send_pool_17c;
    void *event_1e0;
    NetworkCriticalSectionCtorView critical_1e4;
    unsigned char reserved_200[0x114];
};

NetworkWinsockState314CtorView::NetworkWinsockState314CtorView()
{
    callback_080 = 0;
    heap_buffer_078 = 0;
    port_07c = 0;
}

NetworkWinsockState314CtorView::~NetworkWinsockState314CtorView()
{
    if (heap_buffer_078 != 0) {
        free(heap_buffer_078);
        heap_buffer_078 = 0;
    }
}

typedef char NetworkThreadHandleCtorView_size[
    sizeof(NetworkThreadHandleCtorView) == 0x08 ? 1 : -1];
typedef char NetworkWinsockPolymorphicBase_size[
    sizeof(NetworkWinsockPolymorphicBase) == 0x5c ? 1 : -1];
typedef char NetworkCriticalSectionCtorView_size[
    sizeof(NetworkCriticalSectionCtorView) == 0x1c ? 1 : -1];
typedef char NetworkPeerIndex0C_size[
    sizeof(NetworkPeerIndex0C) == 0x0c ? 1 : -1];
typedef char NetworkPendingTreeSize[sizeof(NetworkPendingTree0C)==0x0c?1:-1];
typedef char NetworkWinsockState314CtorView_size[
    sizeof(NetworkWinsockState314CtorView) == 0x314 ? 1 : -1];
typedef char NetworkWinsockState314CtorView_heap_offset[
    offsetof(NetworkWinsockState314CtorView, heap_buffer_078) == 0x78 ? 1 : -1];
typedef char NetworkWinsockState314CtorView_records_offset[
    offsetof(NetworkWinsockState314CtorView, records_108) == 0x108 ? 1 : -1];
typedef char NetworkWinsockState314CtorView_endpoint_offset[
    offsetof(NetworkWinsockState314CtorView, pending_tokens_168) == 0x168 ? 1 : -1];
typedef char NetworkWinsockState314CtorView_event_offset[
    offsetof(NetworkWinsockState314CtorView, event_1e0) == 0x1e0 ? 1 : -1];
typedef char NetworkWinsockState314CtorView_final_critical_offset[
    offsetof(NetworkWinsockState314CtorView, critical_1e4) == 0x1e4 ? 1 : -1];

} // namespace th105

namespace th105 {
extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void *,int);
extern "C" __declspec(dllimport) int __stdcall GetExitCodeThread(void *,unsigned long *);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);
void NetworkThreadHandleCtorView::wait_for_exit(){
 if(handle_00){
  SetThreadPriority(handle_00,15);
  unsigned long exit_code=259;
  while(exit_code==259)GetExitCodeThread(handle_00,&exit_code);
  CloseHandle(handle_00);handle_00=0;
 }
}
}

// Real member definitions share this owner CIL context.
#include "NetworkUdpPacketPool.cpp"
