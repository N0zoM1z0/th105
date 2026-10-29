#include "battle/BackgroundDerived.hpp"
#include "battle/SpriteTextureSetup.hpp"
#include "ui/Title.hpp"
namespace th105 {
static const char bg04_cloud2_path[] = "data/background/BG04/cloud2.bmp";
BG04::BG04() : BackgroundBase() {
    initialize_common_4664a0(4,0);
    unsigned handle_token=0; handles_b_24.assign(1,handle_token);
    { CEffectSprite fill; sprites_b_34.assign(1,fill); }
    {
      struct Dimensions { unsigned height; unsigned width; } dimensions;
      handles_b_24[0]=*g_title_resource_manager.load_texture(&handle_token,bg04_cloud2_path,&dimensions.width,&dimensions.height);
    }
    reinterpret_cast<SpriteTextureSetupView *>(&sprites_b_34[0])->set_texture_options(handles_b_24[0],0,0,640,192,320,80);
    state_64=0;
}
}
