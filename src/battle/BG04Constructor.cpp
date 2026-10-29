#include "battle/BackgroundDerived.hpp"
#include "battle/SpriteTextureSetup.hpp"
#include "ui/DesignBaseLifetime.hpp"
#include "ui/Title.hpp"

namespace th105 {
struct BG04TextureLoadView {
    DesignTextureHandle load_texture(const char *,unsigned *,unsigned *);
};
static const char bg04_cloud2_path[]="data/background/BG04/cloud2.bmp";
BG04::BG04() : BackgroundBase()
{
    initialize_common_4664a0(4,0);
    handles_b_24.assign(1,0);
    sprites_b_34.assign(1,CEffectSprite());
    unsigned width,height;
    handles_b_24[0]=reinterpret_cast<BG04TextureLoadView *>(&g_title_resource_manager)
        ->load_texture(bg04_cloud2_path,&width,&height).value;
    reinterpret_cast<SpriteTextureSetupView *>(&sprites_b_34[0])
        ->set_texture_options(handles_b_24[0],0,0,640,192,320,80);
    state_64=0;
}
}
