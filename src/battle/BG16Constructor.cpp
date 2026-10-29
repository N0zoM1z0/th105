#include "battle/BackgroundDerived.hpp"
#include "battle/SpriteTextureSetup.hpp"
#include "ui/Title.hpp"
#include "ui/DesignBaseLifetime.hpp"
namespace th105 {
struct BG16TextureLoadView { DesignTextureHandle load_texture(const char *,unsigned *,unsigned *); };
BG16::BG16() : BackgroundBase()
{
    initialize_common_4664a0(16,0);
    handles_b_24.assign(4,0);
    { CEffectSprite fill; sprites_b_34.assign(4,fill); }
    unsigned width,height;
    handles_b_24[0]=reinterpret_cast<BG16TextureLoadView *>(&g_title_resource_manager)->load_texture("data/background/BG16/0001.bmp",&width,&height).value;
    reinterpret_cast<SpriteTextureSetupView *>(&sprites_b_34[0])->set_texture_options(handles_b_24[0],0,0,width,height,128,128);
    handles_b_24[1]=reinterpret_cast<BG16TextureLoadView *>(&g_title_resource_manager)->load_texture("data/background/BG16/0002.bmp",&width,&height).value;
    reinterpret_cast<SpriteTextureSetupView *>(&sprites_b_34[1])->set_texture_options(handles_b_24[1],0,0,width,height,128,128);
    handles_b_24[2]=reinterpret_cast<BG16TextureLoadView *>(&g_title_resource_manager)->load_texture("data/background/BG16/0003.bmp",&width,&height).value;
    reinterpret_cast<SpriteTextureSetupView *>(&sprites_b_34[2])->set_texture_options(handles_b_24[2],0,0,width,height,0,64);
    handles_b_24[3]=reinterpret_cast<BG16TextureLoadView *>(&g_title_resource_manager)->load_texture("data/background/BG16/0004.bmp",&width,&height).value;
    reinterpret_cast<SpriteTextureSetupView *>(&sprites_b_34[3])->set_texture_options(handles_b_24[3],0,0,width,height,32,32);
    state_64=0;
}
}
