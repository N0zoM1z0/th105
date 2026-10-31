#include "engine/RenderModeManager.hpp"

namespace th105 {
void RenderModeManager::set_pair_state(
    unsigned char first, unsigned char second)
{
    device_04->SetRenderState(27, first);
    device_04->SetRenderState(15, second);
    device_04->SetRenderState(24, 1);
    device_04->SetRenderState(25, 7);
    device_04->SetTextureStageState(0, 4, 4);
    state_0c.pair_first_18 = first;
    state_0c.pair_second_19 = second;
}
} // namespace th105
