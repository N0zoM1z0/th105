#include "input/InputManager.hpp"

namespace th105 {

void *probe_direct_input_device_index(std::vector<void *> &items, unsigned index)
{
    return items[index];
}

unsigned probe_direct_input_state_size(const std::vector<RawGamepadState> &items)
{
    return items.size();
}

void *probe_direct_input_device_back(std::vector<void *> &items)
{
    return items.back();
}

void probe_direct_input_device_push(
    std::vector<void *> &items, void * const &value)
{
    items.push_back(value);
}

void probe_direct_input_int_push(
    std::vector<int> &items, const int &value)
{
    items.push_back(value);
}

} // namespace th105
