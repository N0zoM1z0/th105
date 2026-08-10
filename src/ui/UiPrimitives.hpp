#pragma once

extern "C" const unsigned int title_color_vtable_anchor[];
extern "C" const unsigned int select_sprite_vtable_anchor[];
extern "C" const unsigned int select_tile_vtable_anchor[];

namespace th105 {

struct UiSprite94 {
    typedef void (__thiscall *SetColor)(UiSprite94 *, unsigned int);
    typedef void (__thiscall *SetTexture)(
        UiSprite94 *, unsigned int, int, int, int, int);
    typedef void (__thiscall *SetTextureOptions)(
        UiSprite94 *, unsigned int, int, int, unsigned int, unsigned int,
        int, int);
    typedef void (__thiscall *Render)(UiSprite94 *, float, float);

    const unsigned int *vtable;
    unsigned int reserved_04;
    unsigned char reserved_08[0x8C];

    UiSprite94()
    {
        reserved_04 = 0;
        vtable = select_sprite_vtable_anchor;
    }
    ~UiSprite94() { vtable = title_color_vtable_anchor; }

    void set_color(unsigned int color)
    {
        reinterpret_cast<SetColor>(vtable[1])(this, color);
    }

    void set_texture(unsigned int handle, int x, int y, int width, int height)
    {
        reinterpret_cast<SetTexture>(vtable[5])(
            this, handle, x, y, width, height);
    }

    void set_texture_options(
        unsigned int handle, int x, int y, unsigned int width,
        unsigned int height, int option, int flags)
    {
        reinterpret_cast<SetTextureOptions>(vtable[4])(
            this, handle, x, y, width, height, option, flags);
    }

    void render(float x, float y)
    {
        reinterpret_cast<Render>(vtable[7])(this, x, y);
    }
};

struct UiTileA4 {
    typedef void (__thiscall *SetColor)(UiTileA4 *, unsigned int);

    const unsigned int *vtable;
    unsigned int reserved_04;
    unsigned char reserved_08[0x9C];

    UiTileA4()
    {
        reserved_04 = 0;
        vtable = select_tile_vtable_anchor;
    }
    ~UiTileA4() { vtable = title_color_vtable_anchor; }

    void set_color(unsigned int color)
    {
        reinterpret_cast<SetColor>(vtable[1])(this, color);
    }

    void render(int scenario_id, int unknown, float x, float y);
    void set_texture(
        unsigned int handle, int x, int y, unsigned int width,
        unsigned int height);
};

struct UiDesignObject {
    typedef void (__thiscall *SetColor)(UiDesignObject *, unsigned int);
    typedef void (__thiscall *Render)(UiDesignObject *, float, float);

    const unsigned int *vtable;
    unsigned char reserved_04[8];
    float x;
    float y;
    bool enabled;

    void set_color(unsigned int color)
    {
        reinterpret_cast<SetColor>(vtable[1])(this, color);
    }

    void render(float render_x, float render_y)
    {
        reinterpret_cast<Render>(vtable[7])(this, render_x, render_y);
    }
};

typedef char UiSprite94_size_must_be_0x94[
    sizeof(UiSprite94) == 0x94 ? 1 : -1];
typedef char UiTileA4_size_must_be_0xa4[
    sizeof(UiTileA4) == 0xA4 ? 1 : -1];

} // namespace th105
