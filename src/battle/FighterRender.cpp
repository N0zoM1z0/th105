#include "AnimationSpriteState.hpp"
#include "BattleRenderHelpers.hpp"
#include <list>
namespace th105 {
struct FighterRenderFrame { unsigned char prefix_00[4]; short x_04,y_06; };
struct FighterHistoryEntry { CSpriteEx sprite; signed char blend; };
struct FighterRenderHistory {
 std::list<FighterHistoryEntry> entries;
 signed char period;
 short alpha_divisor;
 unsigned color_mask;
 void enqueue(const CSpriteEx *,signed char);
 void pop_front_if_any();
};
struct FighterRenderView {
 void *vptr;
 AnimationSpriteState sprite_004;
 unsigned char pad_130[0x28];
 FighterRenderFrame *frame_158;
 unsigned char pad_15c[0x14];
 FighterRenderView *peer_170;
 unsigned char pad_174[0x12];
 short hitstop_186;
 unsigned char pad_188[0x304];
 short peer_gate_48c;
 unsigned char pad_48e[0x1e2];
 int countdown_670;
 FighterRenderHistory history_674;
 void render();
};
typedef char FrameOffset[offsetof(FighterRenderView,frame_158)==0x158?1:-1];
typedef char HistoryOffset[offsetof(FighterRenderView,history_674)==0x674?1:-1];
void FighterRenderView::render()
{
    float frame_x=frame_158->x_04;
    float frame_y=frame_158->y_06;
    sprite_004.sprite_000.reset_transform();
    sprite_004.sprite_000.scale_x(static_cast<float>(sprite_004.object_facing_100));
    sprite_004.sprite_000.scale_x(sprite_004.reset_one_118,
        static_cast<float>((frame_x+sprite_004.reset_zero_104)*sprite_004.object_facing_100));
    sprite_004.sprite_000.scale_y(sprite_004.reset_one_11c,
        static_cast<float>(frame_y-sprite_004.reset_zero_108));
    sprite_004.sprite_000.rotate_xyz(sprite_004.reset_zero_120,sprite_004.reset_zero_124,
        static_cast<float>(sprite_004.reset_zero_128*sprite_004.object_facing_100),
        static_cast<float>((frame_x+sprite_004.reset_zero_104)*sprite_004.object_facing_100),
        static_cast<float>(frame_y-sprite_004.reset_zero_108),0.0f);
    sprite_004.sprite_000.translate(static_cast<float>(-sprite_004.object_facing_100*frame_x),-frame_y,0.0f);
    if(hitstop_186>0 && is_state_13c_in_32_95(reinterpret_cast<Fighter *>(this)))
        sprite_004.sprite_000.translate(static_cast<float>(sprite_004.object_x_0e8+(2-4*(hitstop_186%2))),
            -sprite_004.object_y_0ec,0.0f);
    else
        sprite_004.sprite_000.translate(sprite_004.object_x_0e8,-sprite_004.object_y_0ec,0.0f);
    if(hitstop_186==0 && peer_170->peer_gate_48c==0) {
        history_674.enqueue(&sprite_004.sprite_000,2);
        if(countdown_670<=0) {
            history_674.pop_front_if_any();
            history_674.pop_front_if_any();
        }
    }
    g_battle_background_layout.transform_sprite(&sprite_004.sprite_000);
}
}
