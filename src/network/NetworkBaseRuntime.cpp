#include "../engine/CriticalSectionWrapper.hpp"
#include "../input/InputManager.hpp"
#include "../ui/UiPrimitives.hpp"

#include <deque>
#include <stddef.h>

namespace th105 {

// Current CNetworkBase owns two 0x7c input endpoints.  CInputManager is a
// member at +0, not a base class: the distinction is byte-significant because
// inheritance would publish an extra derived vptr during destruction.
struct NetworkInputEndpoint7C {
    CInputManager input_000;
    unsigned char reserved_060[0x08];
    std::deque<short> queue_068;

    ~NetworkInputEndpoint7C() {}
};

struct NetworkQueueSlot20 {
    unsigned char reserved_000[0x08];
    std::deque<short> queue_008;
    unsigned char reserved_01c[0x04];

    ~NetworkQueueSlot20() {}
};

// The current +0x3b4 member has its own independently observed polymorphic
// lifetime at 0x00412cc0.  Only its physical extent is needed by this TU.
class NetworkWinsockState314 {
public:
    virtual ~NetworkWinsockState314();

private:
    unsigned char reserved_004[0x310];
};

// Narrow lifetime view of the complete current 0x6dc CNetworkBase owner.
// The empty C++ destructor intentionally relies on reverse member destruction;
// do not replace it with a handwritten cleanup list.
class CNetworkBaseLifetimeView {
public:
    virtual ~CNetworkBaseLifetimeView();

private:
    unsigned char reserved_004[0x44];
    CriticalSectionWrapper critical_048;
    unsigned char reserved_064[0x3c];
    std::deque<short> queue_0a0;
    std::deque<short> queues_0b4[2];
    CriticalSectionWrapper critical_0dc;
    NetworkInputEndpoint7C inputs_0f8[2];
    unsigned char reserved_1f0[0x24];
    NetworkQueueSlot20 slots_214[2];
    unsigned char reserved_254[0x08];
    CriticalSectionWrapper critical_25c;
    unsigned char reserved_278[0x04];
    UiSprite94 sprites_27c[2];
    unsigned char reserved_3a4[0x10];
    NetworkWinsockState314 winsock_3b4;
    std::deque<short> queue_6c8;
};

CNetworkBaseLifetimeView::~CNetworkBaseLifetimeView()
{
}

// Method-focused view of the same physical owner.  Keeping the two endpoint
// accesses through one short-lived element pointer reproduces the current
// source dataflow: queue.clear() and CInputManager::reset_counters() consume
// the same 0x7c element before advancing to the next one.
struct CNetworkBaseResetView {
    void reset_runtime();

    unsigned char reserved_000[0x48];
    CriticalSectionWrapper critical_048;
    unsigned char reserved_064[0x08];
    unsigned char peer_byte_06c;
    unsigned char reserved_06d[0x0f];
    unsigned short state_07c;
    unsigned short state_07e;
    unsigned char reserved_080[2];
    unsigned char state_082;
    unsigned char state_083;
    unsigned int state_084;
    unsigned int state_088;
    unsigned int state_08c;
    unsigned char reserved_090[0x08];
    unsigned int state_098;
    unsigned char reserved_09c[0x04];
    std::deque<short> queue_0a0;
    unsigned char reserved_0b4[0x28];
    CriticalSectionWrapper critical_0dc;
    NetworkInputEndpoint7C inputs_0f8[2];
    unsigned char reserved_1f0[0x18];
    CInputManager *input_208;
    unsigned char reserved_20c[0x199];
    unsigned char export_pending_3a5;
    unsigned char ack_pending_3a6;
    unsigned char state_3a7;
};

void CNetworkBaseResetView::reset_runtime()
{
    critical_048.enter();
    critical_0dc.enter();
    input_208->reset_counters();

    NetworkInputEndpoint7C *endpoint = &inputs_0f8[0];
    endpoint->queue_068.clear();
    endpoint->input_000.reset_counters();
    endpoint = &inputs_0f8[1];
    endpoint->queue_068.clear();
    endpoint->input_000.reset_counters();

    state_083 = 0;
    state_082 = 0;
    state_084 = 0;
    state_088 = 0;
    state_08c = 0;
    state_07c = 0;
    state_07e = 0;
    state_098 = 0;
    queue_0a0.clear();
    export_pending_3a5 = 0;
    ack_pending_3a6 = 0;
    state_3a7 = 0;
    critical_0dc.leave();
    critical_048.leave();
}

typedef char NetworkInputEndpoint7C_size_must_be_0x7c[
    sizeof(NetworkInputEndpoint7C) == 0x7c ? 1 : -1];
typedef char NetworkQueueSlot20_size_must_be_0x20[
    sizeof(NetworkQueueSlot20) == 0x20 ? 1 : -1];
typedef char NetworkWinsockState314_size_must_be_0x314[
    sizeof(NetworkWinsockState314) == 0x314 ? 1 : -1];
typedef char CNetworkBaseLifetimeView_size_must_be_0x6dc[
    sizeof(CNetworkBaseLifetimeView) == 0x6dc ? 1 : -1];
typedef char CNetworkBaseResetView_input_offset_must_be_0xf8[
    offsetof(CNetworkBaseResetView, inputs_0f8) == 0xf8 ? 1 : -1];
typedef char CNetworkBaseResetView_input_pointer_offset_must_be_0x208[
    offsetof(CNetworkBaseResetView, input_208) == 0x208 ? 1 : -1];
typedef char CNetworkBaseResetView_flags_offset_must_be_0x3a5[
    offsetof(CNetworkBaseResetView, export_pending_3a5) == 0x3a5 ? 1 : -1];

} // namespace th105
