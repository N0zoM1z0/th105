#pragma once

#include "battle/BackgroundBase.hpp"

namespace th105 {

#define TH105_BG_OVERRIDES() \
    virtual void slot_04(); \
    virtual void slot_08(); \
    virtual void slot_0c(); \
    virtual void slot_10(); \
    virtual void render_sprite(CSpriteEx *sprite)

struct BGCommon : BackgroundBase {
    BGCommon(int background_id, int variant);
    virtual ~BGCommon();
    TH105_BG_OVERRIDES();
};

struct BG02 : BackgroundBase {
    int state_64;
    BG02();
    virtual ~BG02();
    TH105_BG_OVERRIDES();
};

struct BG04 : BackgroundBase {
    int state_64;
    BG04();
    virtual ~BG04();
    TH105_BG_OVERRIDES();
};

struct BG16 : BackgroundBase {
    int state_64;
    BG16();
    virtual ~BG16();
    TH105_BG_OVERRIDES();
};

#undef TH105_BG_OVERRIDES

typedef char bgcommon_size_must_be_0x64[(sizeof(BGCommon) == 0x64) ? 1 : -1];
typedef char bg02_size_must_be_0x68[(sizeof(BG02) == 0x68) ? 1 : -1];
typedef char bg04_size_must_be_0x68[(sizeof(BG04) == 0x68) ? 1 : -1];
typedef char bg16_size_must_be_0x68[(sizeof(BG16) == 0x68) ? 1 : -1];

} // namespace th105
