#include "RenderModeManager.hpp"

namespace th105 {

void RenderModeManager::set_blend_mode(int mode)
{
    int old_mode = state_0c.blend_mode_00;
    if (old_mode == mode)
        return;

    switch (mode + 8 * old_mode - 1) {
    case 0:
        device_04->SetRenderState(171, 1);
        // fall through
    case 32:
        device_04->SetRenderState(19, 5);
        // fall through
    case 16:
        device_04->SetRenderState(20, 6);
        break;

    case 24:
        device_04->SetRenderState(171, 1);
        device_04->SetRenderState(20, 6);
        break;

    case 1:
        device_04->SetRenderState(171, 1);
        // fall through
    case 33:
        device_04->SetRenderState(19, 5);
        // fall through
    case 9:
        device_04->SetRenderState(20, 2);
        break;

    case 25:
        device_04->SetRenderState(171, 1);
        break;

    case 2:
    case 34:
        device_04->SetRenderState(171, 3);
        device_04->SetRenderState(19, 5);
        device_04->SetRenderState(20, 2);
        break;

    case 10:
        device_04->SetRenderState(171, 3);
        device_04->SetRenderState(20, 2);
        break;

    case 18:
        device_04->SetRenderState(171, 3);
        break;

    case 3:
    case 27:
        device_04->SetRenderState(171, 1);
        // fall through
    case 11:
    case 19:
        device_04->SetRenderState(19, 1);
        device_04->SetRenderState(20, 3);
        break;

    default:
        break;
    }

    state_0c.blend_mode_00 = mode;
}

int RenderModeManager::set_gate_states(
    unsigned char gate7, unsigned char gate14)
{
    device_04->SetRenderState(7, gate7);
    int result = device_04->SetRenderState(14, gate14);
    state_0c.gate_7_10 = gate7;
    state_0c.gate_14_11 = gate14;
    return result;
}

int RenderModeManager::set_state_23(int value)
{
    int result = device_04->SetRenderState(23, value);
    state_0c.state_23_14 = value;
    return result;
}

} // namespace th105
