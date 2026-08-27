#include "battle/BackgroundBase.hpp"
#include "battle/AnimationRenderVirtuals.hpp"
#include "battle/BattleBackgroundLayout.hpp"
#include "engine/RenderModeManager.hpp"
namespace th105 {
void BackgroundBase::render_base_sprites_4659e0() {
 g_render_mode_manager.set_blend_mode(1); g_render_mode_manager.set_mode(1);
 g_render_mode_manager.set_sampler_state(0,1,3); g_render_mode_manager.set_sampler_state(0,2,3);
 int i=0; do {
  if(handles_a_04[i]!=0) {
   CSpriteEx &sprite=sprites_a_14[i];
   sprite.reset_transform(); sprite.translate(value_44,value_48,0.0f);
   g_battle_background_layout.place_sprite(&sprite,1.0f,1.0f);
   if(sprite.working_quad_0b0[3].x < 0.0f) {
   } else if(sprite.working_quad_0b0[0].x > 640.0f) {
   } else if(sprite.working_quad_0b0[3].y < 0.0f) {
   } else if(sprite.working_quad_0b0[0].y > 480.0) {
   } else {
    reinterpret_cast<SpriteRenderEffectView *>(&sprite)->render_rgb(value_50,value_54,value_58);
   }
  }
  ++i;
 } while(i<30);
 g_render_mode_manager.set_sampler_state(0,1,1); g_render_mode_manager.set_sampler_state(0,2,1);
}
}
