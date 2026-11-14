#include "battle/EffectSprite.hpp"
#include "ui/Title.hpp"
#include <stddef.h>
namespace th105 {

struct FighterCutinLifetime {
    DesignTextureHandle handle_00;
    CSprite sprite_04;
    int selector_98;
    int state_9c;
    ~FighterCutinLifetime();
};
typedef char FighterCutinLifetime_size[sizeof(FighterCutinLifetime)==0xa0?1:-1];
typedef char FighterCutinLifetime_sprite_offset[offsetof(FighterCutinLifetime,sprite_04)==4?1:-1];
FighterCutinLifetime::~FighterCutinLifetime()
{
    if (handle_00 != 0) {
        g_title_resource_manager.release_title_resource_handle(handle_00);
        handle_00=0;
    }
}
}
