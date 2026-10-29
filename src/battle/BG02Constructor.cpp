#include "battle/BackgroundDerived.hpp"
#include "battle/SpriteTextureSetup.hpp"
#include "ui/DesignBaseLifetime.hpp"
#include "ui/Title.hpp"
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *,const char *,...);
namespace th105 {
struct BG02TextureLoadView {
    DesignTextureHandle load_texture(const char *,unsigned *,unsigned *);
};
BG02::BG02() : BackgroundBase()
{
    initialize_common_4664a0(2,0);
    handles_b_24.assign(48,0);
    { CEffectSprite fill; sprites_b_34.assign(48,fill); }
    unsigned width,height;
    for(int i=0;i<16;++i) {
        char path[260];
        wsprintfA(path,"data/background/BG02/left/a%02d.bmp",i);
        handles_b_24[i*3]=reinterpret_cast<BG02TextureLoadView *>(&g_title_resource_manager)->load_texture(path,&width,&height).value;
        reinterpret_cast<SpriteTextureSetupView *>(&sprites_b_34[i*3])->set_texture_options(handles_b_24[i*3],0,0,width,height,0,0);
        wsprintfA(path,"data/background/BG02/center/b%02d.bmp",i);
        handles_b_24[i*3+1]=reinterpret_cast<BG02TextureLoadView *>(&g_title_resource_manager)->load_texture(path,&width,&height).value;
        reinterpret_cast<SpriteTextureSetupView *>(&sprites_b_34[i*3+1])->set_texture_options(handles_b_24[i*3+1],0,0,width,height,0,0);
        wsprintfA(path,"data/background/BG02/right/c%02d.bmp",i);
        handles_b_24[i*3+2]=reinterpret_cast<BG02TextureLoadView *>(&g_title_resource_manager)->load_texture(path,&width,&height).value;
        reinterpret_cast<SpriteTextureSetupView *>(&sprites_b_34[i*3+2])->set_texture_options(handles_b_24[i*3+2],0,0,width,height,0,0);
    }
    state_64=0;
}
}
