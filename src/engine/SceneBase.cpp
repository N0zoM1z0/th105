#include "SceneBase.hpp"

namespace th105 {

int CSceneBase::map_battle_setup_state_to_scene()
{
    switch (advance_battle_setup_state()) {
    case 5:
        return 13;
    case 6:
        return 10;
    default:
        return 13;
    }
}

} // namespace th105
