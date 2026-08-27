#include "battle/BattleObjectManagerRuntime.hpp"

namespace th105 {

extern unsigned char g_battle_transition_mode;

void BattleObjectManager::publish_stage(int stage, int count, bool notify)
{
    g_battle_transition_mode = static_cast<unsigned char>(stage);
    float scale = count ? 1.0f / static_cast<float>(count) : 0.0f;

    if (notify && !renderers_28.empty() && count > 0) {
        BattleRenderRequest request = {static_cast<unsigned>(stage), scale};
        render_requests_00.push_back(request);
        SetEvent(event_a_20);
        return;
    }

    dispatch_request_467380(static_cast<unsigned>(stage), scale);
}

} // namespace th105
