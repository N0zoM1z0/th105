// JP1.06a CDesignGage rendering and CDesignSprite scale entry40AEE0.
// Complete canonical matches; docs/GAGE_DESIGN_RENDER_2026_10_21.md
// and docs/DESIGN_SPRITE_SCALE_2026_10_21.md.
#include <stddef.h>
#include "DesignObjects.hpp"
void CDesignSprite::set_render_parameters(unsigned, unsigned, float scale)
{
    sprite_18.scale_x_88 = scale;
    sprite_18.scale_y_8c = scale;
}

void CDesignGage::render()
{
    if (enabled_14)
        gage_18.render(x_0c + base_x_04, y_10 + base_y_08);
}
void CDesignGage::render_offset(float x, float y)
{
    if (enabled_14)
        gage_18.render(x_0c + base_x_04 + x, y_10 + base_y_08 + y);
}
void CDesignSprite::render()
{
    if (enabled_14)
        sprite_18.render(x_0c + base_x_04, y_10 + base_y_08);
}
void CDesignSprite::render_offset(float x, float y)
{
    if (enabled_14)
        sprite_18.render(x_0c + base_x_04 + x, y_10 + base_y_08 + y);
}
typedef char ColorViewSize[sizeof(IColor) == 4 ? 1 : -1];
typedef char GageMemberSize[sizeof(CGage) == 0xa4 ? 1 : -1];
typedef char DesignBaseSize[sizeof(CDesignObjectBase) == 0x18 ? 1 : -1];
typedef char DesignGageSize[sizeof(CDesignGage) == 0xbc ? 1 : -1];
typedef char GageMemberOffset[offsetof(CDesignGage, gage_18) == 0x18 ? 1 : -1];
typedef char BaseXOffset[offsetof(CDesignObjectBase, base_x_04) == 4 ? 1 : -1];
typedef char BaseYOffset[offsetof(CDesignObjectBase, base_y_08) == 8 ? 1 : -1];
typedef char XOffset[offsetof(CDesignObjectBase, x_0c) == 0xc ? 1 : -1];
typedef char YOffset[offsetof(CDesignObjectBase, y_10) == 0x10 ? 1 : -1];
typedef char EnabledOffset[offsetof(CDesignObjectBase, enabled_14) == 0x14 ? 1 : -1];
typedef char DesignSpriteSize[sizeof(CDesignSprite) == 0xac ? 1 : -1];
typedef char DesignSpriteMemberOffset[offsetof(CDesignSprite, sprite_18) == 0x18 ? 1 : -1];
typedef char SpriteScaleXOffset[offsetof(CSprite, scale_x_88) == 0x88 ? 1 : -1];
typedef char SpriteScaleYOffset[offsetof(CSprite, scale_y_8c) == 0x8c ? 1 : -1];
