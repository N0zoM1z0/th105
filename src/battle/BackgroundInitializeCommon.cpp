#include "battle/BackgroundBase.hpp"
#include "ui/Title.hpp"
#include <vector>
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);
namespace th105 {
struct BackgroundSpriteTextureView : CSpriteEx {
    void set_texture_region_407160(
        unsigned handle, int x, int y, int width, int height,
        int pivot_x, int pivot_y);
};
void BackgroundBase::initialize_common_4664a0(int background_id, int variant)
{
    char path[260];
    handles_a_04.assign(30, 0);
    sprites_a_14.assign(30, CEffectSprite());
    for (int i = 0; i < 30; ++i) {
        const int col = (i % 6) * 256;
        const int row = (i / 6) * 256;
        wsprintfA(path, "data/background/BG%02d/0000_%02d.bmp", background_id, i);
        unsigned loaded;
        handles_a_04[i] = *g_title_resource_manager.load_texture(&loaded, path, 0, 0);
        if (handles_a_04[i] != 0) {
            reinterpret_cast<BackgroundSpriteTextureView *>(&sprites_a_14[i])
                ->set_texture_region_407160(
                    handles_a_04[i], 0, 0, 256, 256,
                    700 - col,
                    variant - row + 860);
        }
    }
}
}
