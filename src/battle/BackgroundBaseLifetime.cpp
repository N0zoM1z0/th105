#include "battle/EffectSprite.hpp"
#include "ui/Title.hpp"
#include <vector>
#include <stddef.h>

namespace th105 {

struct BackgroundBase {
    virtual ~BackgroundBase();

    std::vector<unsigned> handles_a_04;
    std::vector<CSpriteEx> sprites_a_14;
    std::vector<unsigned> handles_b_24;
    std::vector<CSpriteEx> sprites_b_34;
    float value_44;
    float value_48;
    float value_4c;
    float value_50;
    float value_54;
    float value_58;

    BackgroundBase();
};

typedef char bg_handles_a[(offsetof(BackgroundBase, handles_a_04)==0x04)?1:-1];
typedef char bg_sprites_a[(offsetof(BackgroundBase, sprites_a_14)==0x14)?1:-1];
typedef char bg_handles_b[(offsetof(BackgroundBase, handles_b_24)==0x24)?1:-1];
typedef char bg_sprites_b[(offsetof(BackgroundBase, sprites_b_34)==0x34)?1:-1];
typedef char bg_value44[(offsetof(BackgroundBase, value_44)==0x44)?1:-1];
typedef char bg_size[(sizeof(BackgroundBase)==0x5c)?1:-1];

BackgroundBase::BackgroundBase()
    : handles_a_04(), sprites_a_14(), handles_b_24(), sprites_b_34()
{
    value_44 = value_48 = value_4c = value_50 = value_54 = value_58 = 0.0f;
}

BackgroundBase::~BackgroundBase()
{
    for (unsigned i = 0; i < handles_b_24.size(); ++i)
        g_title_resource_manager.release_title_resource_handle(handles_b_24[i]);
    for (unsigned i = 0; i < handles_a_04.size(); ++i)
        g_title_resource_manager.release_title_resource_handle(handles_a_04[i]);
}

}
