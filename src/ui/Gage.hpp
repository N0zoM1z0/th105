#pragma once
#include "engine/Sprite.hpp"
#include <new>
namespace th105 {
// Existing float-returning value interface used by the gauge renderer.
struct GageValueView { virtual float value() = 0; };
}
// Native RTTI: CGage -> CSprite -> CSpriteBase -> IColor.
class CGage : public CSprite {
public:
    CGage();
    virtual ~CGage() { if (value_a0 != 0) ::operator delete(value_a0); }
    virtual void render(float x, float y);
    virtual void render_fvf4142(float x, float y);
    float u_span_94, v_span_98;
    int fill_mode_9c;
    th105::GageValueView *value_a0;
};
typedef char CGage_size[sizeof(CGage) == 0xA4 ? 1 : -1];
typedef char CGage_value_offset[offsetof(CGage, value_a0) == 0xA0 ? 1 : -1];
