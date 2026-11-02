#pragma once
#include "engine/Sprite.hpp"
#include "Gage.hpp"
#include "CNumberRuntime.hpp"
#include <stddef.h>

class CDesignObjectBase : public IColor {
public:
    CDesignObjectBase() : base_x_04(0.0f), base_y_08(0.0f), enabled_14(true) {}
    virtual ~CDesignObjectBase() {}
    virtual void set_color(unsigned int) {}
    virtual void set_vertex_colors(const unsigned int *) {}
    virtual void multiply_color(unsigned int) {}
    virtual void render_offset(float, float) {}
    virtual void render() {}
    // The third word is observed as float in the sprite override.
    virtual void set_render_parameters(unsigned int, unsigned int, float) {}
    float base_x_04, base_y_08, x_0c, y_10;
    bool enabled_14;
};

class CDesignSprite : public CDesignObjectBase {
public:
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    virtual void render_offset(float, float);
    virtual void render();
    virtual void set_render_parameters(unsigned int, unsigned int, float);
    CSprite sprite_18;
};

class CDesignGage : public CDesignObjectBase {
public:
    CDesignGage();
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    virtual void render_offset(float, float);
    virtual void render();
    CGage gage_18;
};

class CDesignNumber : public CDesignObjectBase {
public:
    CDesignNumber();
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    virtual void render_offset(float, float);
    virtual void render();
    th105::CNumber number_18;
};

typedef char DesignObjectBaseSize[sizeof(CDesignObjectBase) == 0x18 ? 1 : -1];
typedef char DesignObjectBaseX[offsetof(CDesignObjectBase, base_x_04) == 4 ? 1 : -1];
typedef char DesignObjectBaseY[offsetof(CDesignObjectBase, base_y_08) == 8 ? 1 : -1];
typedef char DesignObjectX[offsetof(CDesignObjectBase, x_0c) == 0x0c ? 1 : -1];
typedef char DesignObjectY[offsetof(CDesignObjectBase, y_10) == 0x10 ? 1 : -1];
typedef char DesignObjectEnabled[offsetof(CDesignObjectBase, enabled_14) == 0x14 ? 1 : -1];
typedef char DesignSpriteSize[sizeof(CDesignSprite) == 0xac ? 1 : -1];
typedef char DesignGageSize[sizeof(CDesignGage) == 0xbc ? 1 : -1];
typedef char DesignNumberSize[sizeof(CDesignNumber) == 0xe4 ? 1 : -1];
typedef char DesignSpriteMember[offsetof(CDesignSprite, sprite_18) == 0x18 ? 1 : -1];
typedef char DesignGageMember[offsetof(CDesignGage, gage_18) == 0x18 ? 1 : -1];
typedef char DesignNumberMember[offsetof(CDesignNumber, number_18) == 0x18 ? 1 : -1];
