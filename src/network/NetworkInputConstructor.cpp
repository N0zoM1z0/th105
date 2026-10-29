#include "../input/InputManager.hpp"

#include <deque>
#include <stddef.h>
// Complete 0x7c endpoint construction; the two-slot interface is independently
// pinned by RTTI/vtable evidence, not the partial shared input-manager view.
namespace th105 {
class InputCore60View {
public:
    InputCore60View();
    virtual ~InputCore60View();
    virtual void update_raw();
    InputBindings bindings;
    HoldCounters hold;
};
class NetworkInputConstructorView : public InputCore60View {
public:
    virtual ~NetworkInputConstructorView();
    virtual void update_raw();
    unsigned short injected_60, resolved_62;
    bool use_injected_64;
};
struct NetworkInputEndpointConstructorView {
    NetworkInputEndpointConstructorView();
    ~NetworkInputEndpointConstructorView();
    NetworkInputConstructorView input;
    std::deque<short> queue_68;
};
typedef char InputCtorQueue[
    offsetof(NetworkInputEndpointConstructorView, queue_68) == 0x68 ? 1 : -1];
typedef char InputCtorSize[
    sizeof(NetworkInputEndpointConstructorView) == 0x7c ? 1 : -1];
NetworkInputEndpointConstructorView::NetworkInputEndpointConstructorView()
{
    input.use_injected_64 = true;
    input.injected_60 = 0;
    queue_68.clear();
}

NetworkInputEndpointConstructorView::~NetworkInputEndpointConstructorView()
{
}
}
