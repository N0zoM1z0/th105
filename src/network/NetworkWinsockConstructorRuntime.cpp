#include "../engine/CriticalSectionWrapper.hpp"

#include <deque>
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

class NetworkCriticalSectionCtorView {
public:
    NetworkCriticalSectionCtorView()
    {
        InitializeCriticalSection(&critical_section_04);
    }
    virtual ~NetworkCriticalSectionCtorView();

public:
    Win32CriticalSection24 critical_section_04;
};

NetworkWinsockPolymorphicBase::~NetworkWinsockPolymorphicBase()
{
}

NetworkThreadHandleCtorView::~NetworkThreadHandleCtorView()
{
    wait_for_exit();
}

NetworkCriticalSectionCtorView::~NetworkCriticalSectionCtorView()
{
    DeleteCriticalSection(&critical_section_04);
}

struct NetworkListValue8 {
    unsigned int first_00;
    unsigned int second_04;
};

struct NetworkCheckedListNode18 {
    NetworkCheckedListNode18 *next_00;
    NetworkCheckedListNode18 *previous_04;
    void *owner_08;
    NetworkListValue8 value_0c;
    unsigned char constructed_14;
    unsigned char is_head_15;
    unsigned char reserved_16[2];
};

NetworkCheckedListNode18 *__cdecl allocate_network_checked_list_node_18();

struct NetworkCheckedListA0C {
    NetworkCheckedListA0C()
    {
        head_04 = allocate_network_checked_list_node_18();
        head_04->is_head_15 = 1;
        head_04->previous_04 = head_04;
        head_04->next_00 = head_04;
        head_04->owner_08 = head_04;
        size_08 = 0;
    }
    ~NetworkCheckedListA0C();

    unsigned int allocator_00;
    NetworkCheckedListNode18 *head_04;
    unsigned int size_08;
};

struct NetworkCheckedListB0C {
    NetworkCheckedListB0C()
    {
        head_04 = allocate_network_checked_list_node_18();
        head_04->is_head_15 = 1;
        head_04->previous_04 = head_04;
        head_04->next_00 = head_04;
        head_04->owner_08 = head_04;
        size_08 = 0;
    }
    ~NetworkCheckedListB0C();

    unsigned int allocator_00;
    NetworkCheckedListNode18 *head_04;
    unsigned int size_08;
};

struct NetworkSendRecord20CtorView {
    unsigned char reserved_00[0x20];
};

void __stdcall construct_network_send_pool_68(void *storage);

struct NetworkSendPool68CtorView {
    __forceinline NetworkSendPool68CtorView()
    {
        construct_network_send_pool_68(storage_00);
    }
    ~NetworkSendPool68CtorView();

    unsigned char storage_00[0x68];
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
    NetworkCheckedListA0C pending_0fc;
    std::vector<NetworkSendRecord20CtorView> records_108;
    unsigned char reserved_118[8];
    NetworkCriticalSectionCtorView critical_120;
    NetworkThreadHandleCtorView worker_13c;
    unsigned char reserved_144[8];
    std::vector<unsigned int> indices_14c;
    NetworkCheckedListB0C pending_15c;
    std::deque<unsigned int> pending_tokens_168;
    NetworkSendPool68CtorView send_pool_17c;
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
typedef char NetworkListValue8_size[
    sizeof(NetworkListValue8) == 0x08 ? 1 : -1];
typedef char NetworkCheckedListNode18_size[
    sizeof(NetworkCheckedListNode18) == 0x18 ? 1 : -1];
typedef char NetworkCheckedListA0C_size[
    sizeof(NetworkCheckedListA0C) == 0x0c ? 1 : -1];
typedef char NetworkCheckedListB0C_size[
    sizeof(NetworkCheckedListB0C) == 0x0c ? 1 : -1];
typedef char NetworkSendPool68CtorView_size[
    sizeof(NetworkSendPool68CtorView) == 0x68 ? 1 : -1];
typedef char NetworkWinsockState314CtorView_size[
    sizeof(NetworkWinsockState314CtorView) == 0x314 ? 1 : -1];
typedef char NetworkWinsockState314CtorView_heap_offset[
    offsetof(NetworkWinsockState314CtorView, heap_buffer_078) == 0x78 ? 1 : -1];
typedef char NetworkWinsockState314CtorView_records_offset[
    offsetof(NetworkWinsockState314CtorView, records_108) == 0x108 ? 1 : -1];
typedef char NetworkWinsockState314CtorView_endpoint_offset[
    offsetof(NetworkWinsockState314CtorView, pending_tokens_168) == 0x168 ? 1 : -1];
typedef char NetworkWinsockState314CtorView_final_critical_offset[
    offsetof(NetworkWinsockState314CtorView, critical_1e4) == 0x1e4 ? 1 : -1];

} // namespace th105
