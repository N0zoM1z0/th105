#include "InputManager.hpp"

namespace th105 {

namespace {

struct RawGamepadStateVectorLayout {
    unsigned int allocator_state;
    RawGamepadState *begin;
    RawGamepadState *end;
    RawGamepadState *capacity;
};

} // namespace

void InputStateTable::set_input_state_table_entry(unsigned char index, bool state)
{
    entries[index] = state;
}

bool DirectInputBackend::is_raw_key_down(unsigned char scan_code) const
{
    return (raw_keyboard_state[scan_code] & 0x80) != 0;
}

RawGamepadState *DirectInputBackend::get_gamepad_state(int index)
{
    if (index < 0 || index >= gamepad_count)
        return 0;

    DirectInputBackend *backend = this;
    RawGamepadStateVectorLayout *states =
        reinterpret_cast<RawGamepadStateVectorLayout *>(&backend->gamepad_states);
    RawGamepadState *begin = states->begin;
    unsigned int size = 0;
    if (begin != 0)
        size = static_cast<unsigned int>(states->end - begin);
    if (begin == 0 || static_cast<unsigned int>(index) >= size)
        _invalid_parameter_noinfo();
    return states->begin + index;
}

int DirectInputBackend::get_gamepad_button_count(int index)
{
    if (index < 0 || index >= gamepad_count)
        return 0;
    return gamepad_button_counts[index];
}

void CInputManager::reset_counters()
{
    counters[0] = 0;
    counters[1] = 0;
    counters[2] = 0;
    counters[3] = 0;
    counters[4] = 0;
    counters[5] = 0;
    counters[6] = 0;
    counters[7] = 0;
    counters[8] = 0;
    counters[9] = 0;
}


namespace {

struct DirectInputPollDevice;
struct DirectInputPollVtable {
    void *slots_00[6];
    long (__stdcall *set_property)(DirectInputPollDevice *, const void *, const void *);
    long (__stdcall *acquire)(DirectInputPollDevice *);
    void *slot_20;
    long (__stdcall *get_device_state)(DirectInputPollDevice *, unsigned int, void *);
    void *slots_28[15];
    long (__stdcall *poll)(DirectInputPollDevice *);
};
struct DirectInputPollDevice {
    DirectInputPollVtable *vtable;
};

} // namespace

void poll_direct_input_gamepads()
{
    if (g_direct_input_backend.direct_input == 0)
        return;

    for (int index = 0; index < g_direct_input_backend.gamepad_count; ++index) {
        if (g_direct_input_backend.gamepad_devices[index] == 0)
            continue;

        DirectInputPollDevice *device = static_cast<DirectInputPollDevice *>(
            g_direct_input_backend.gamepad_devices[index]);
        if (device->vtable->poll(device) < 0) {
            device = static_cast<DirectInputPollDevice *>(
                g_direct_input_backend.gamepad_devices[index]);
            device->vtable->acquire(device);
        }

        device = static_cast<DirectInputPollDevice *>(
            g_direct_input_backend.gamepad_devices[index]);
        device->vtable->get_device_state(
            device,
            sizeof(RawGamepadState),
            &g_direct_input_backend.gamepad_states[index]);
    }
}


struct DirectInputObjectInstanceView {
    unsigned char reserved_000[24];
    unsigned int type_018;
};

struct DirectInputRangeProperty {
    unsigned int size;
    unsigned int header_size;
    unsigned int object;
    unsigned int how;
    int minimum;
    int maximum;
};

int __stdcall configure_gamepad_axis(
    const DirectInputObjectInstanceView *object, void *)
{
    DirectInputRangeProperty property;
    property.object = object->type_018;
    property.size = sizeof(property);
    property.header_size = 16;
    property.how = 2;
    property.minimum = -1000;
    property.maximum = 1000;

    DirectInputPollDevice *device = static_cast<DirectInputPollDevice *>(
        g_direct_input_backend.gamepad_devices.back());
    return device->vtable->set_property(
               device, reinterpret_cast<const void *>(4), &property) >= 0;
}

} // namespace th105
