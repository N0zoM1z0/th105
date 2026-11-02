#pragma once
#include "battle/EffectSprite.hpp"
// Native RTTI: CTile -> CSpriteBase -> IColor; four inherited virtual slots.
class CTile : public CSpriteBase {
public:
 CTile() {}
 virtual ~CTile() {}
 void set_texture(unsigned handle,int x,int y,int width,int height);
 void set_texture_options(unsigned handle,int x,int y,int width,int height,int pivot_x,int pivot_y);
 void render(float x,float y,int column,int row);
 float pivot_x_80,pivot_y_84,scale_x_88,scale_y_8c,angle_90;
 float u_origin_94,v_origin_98,u_step_9c,v_step_a0;
};
typedef char CTile_size[sizeof(CTile)==0xa4?1:-1];
typedef char CTile_pivot[offsetof(CTile,pivot_x_80)==0x80?1:-1];
typedef char CTile_uv[offsetof(CTile,u_step_9c)==0x9c?1:-1];
