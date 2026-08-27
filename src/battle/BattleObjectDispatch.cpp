#include "battle/BattleObjectManagerRuntime.hpp"
#include "battle/BackgroundDerived.hpp"

namespace th105 {

void BattleObjectManager::dispatch_request_467380(unsigned kind, float value)
{
    BackgroundBase *created;
    switch (kind) {
    case 0:  created = new BGCommon(0, 0); break;
    case 1:  created = new BGCommon(1, 0); break;
    case 2:  created = new BG02(); break;
    case 3:  created = new BGCommon(3, 0); break;
    case 4:  created = new BG04(); break;
    case 5:  created = new BGCommon(5, 0); break;
    case 6:  created = new BGCommon(6, 0); break;
    case 10: created = new BGCommon(10, 86); break;
    case 11: created = new BGCommon(11, 86); break;
    case 12: created = new BGCommon(12, 86); break;
    case 13: created = new BGCommon(13, 86); break;
    case 14: created = new BGCommon(14, 0); break;
    case 15: created = new BGCommon(15, 86); break;
    case 16: created = new BG16(); break;
    case 17: created = new BGCommon(17, 86); break;
    case 18: created = new BGCommon(18, 0); break;
    default: created = new BGCommon(0, 0); break;
    }

    if (!renderers_28.empty()) {
        if (value != 0.0f)
            created->set_transition_4654f0(0, value);
        else
            created->set_transition_4654f0(1, 0.0f);

        for (std::list<BackgroundBase *>::iterator it = renderers_28.begin();
             it != renderers_28.end(); ++it)
            (*it)->set_transition_4654f0(2, -0.01f);
    } else {
        created->set_transition_4654f0(1, 0.0f);
    }

    renderers_28.push_back(created);
}

} // namespace th105
