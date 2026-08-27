#include "battle/BattleObjectManagerRuntime.hpp"

namespace th105 {

#define TH105_BG_OVERRIDES() \
    virtual void slot_04(); \
    virtual void slot_08(); \
    virtual void slot_0c(); \
    virtual void slot_10(); \
    virtual void render_sprite(CSpriteEx *sprite)

struct BGCommon : BackgroundBase {
    unsigned char observed_tail_5c[0x08];
    BGCommon(int background_id, int variant);
    TH105_BG_OVERRIDES();
};
struct BG02 : BackgroundBase {
    unsigned char observed_tail_5c[0x0c];
    BG02();
    TH105_BG_OVERRIDES();
};
struct BG04 : BackgroundBase {
    unsigned char observed_tail_5c[0x0c];
    BG04();
    TH105_BG_OVERRIDES();
};
struct BG16 : BackgroundBase {
    unsigned char observed_tail_5c[0x0c];
    BG16();
    TH105_BG_OVERRIDES();
};
#undef TH105_BG_OVERRIDES

typedef char bgcommon_dispatch_size[(sizeof(BGCommon) == 0x64) ? 1 : -1];
typedef char bg02_dispatch_size[(sizeof(BG02) == 0x68) ? 1 : -1];
typedef char bg04_dispatch_size[(sizeof(BG04) == 0x68) ? 1 : -1];
typedef char bg16_dispatch_size[(sizeof(BG16) == 0x68) ? 1 : -1];

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
