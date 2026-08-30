#pragma once

#include "UiPrimitives.hpp"

#include <new>

namespace th105 {

struct CNumberTileVertex {
    float x_00;
    float y_04;
    float z_08;
    float rhw_0c;
    unsigned int color_10;
    float u_14;
    float v_18;
};

class CNumberTileA4 {
public:
    const unsigned int *vtable;
    unsigned int texture_handle_04;
    CNumberTileVertex vertices_08[4];
    float width_78;
    float height_7c;
    float anchor_x_80;
    float anchor_y_84;
    float scale_x_88;
    float scale_y_8c;
    float rotation_90;
    float texture_u_94;
    float texture_v_98;
    float texture_width_u_9c;
    float texture_height_v_a0;

    CNumberTileA4()
    {
        texture_handle_04 = 0;
        vtable = select_tile_vtable_anchor;
    }
    ~CNumberTileA4() { vtable = title_color_vtable_anchor; }

    void set_texture_options(
        unsigned int handle,
        int x,
        int y,
        int width,
        int height,
        int option,
        int flags);
    void render(float x, float y, int column, int row);
};

typedef char CNumberTileA4_size_must_be_0xa4[
    sizeof(CNumberTileA4) == 0xA4 ? 1 : -1];
typedef char CNumberTileVertex_size_must_be_0x1c[
    sizeof(CNumberTileVertex) == 0x1C ? 1 : -1];

// Current RTTI identifies the 0xCC owner at CMenuConnect+0x108 as CNumber.
// The 0x28-byte controller prefix owns a CTile-compatible 0xA4 object at +0x28.
// CNumber's constructor body clears the value adapter only after the tile has
// completed construction; this ordering is required by the shipped ctor EH.
class CNumber {
public:
    CNumber() { number_value_24 = 0; }
    virtual ~CNumber();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();

    void initialize(
        unsigned int texture, int a, int b, int c, int d, int e,
        float f, int g, int h, int i);
    void render(int value, float x, float y, int digits, char sign_mode);

    template <typename T>
    void bind_value(T value);

private:
    float glyph_width_04;
    float spacing_08;
    float scale_0c;
    float secondary_scale_10;
    int columns_14;
    int reserved_18;
    int reserved_1c;
    unsigned char mode_20;
    unsigned char reserved_21[3];
    void *number_value_24;
    CNumberTileA4 tile_28;
};

template <typename T>
class TNumberValue {
public:
    explicit TNumberValue(T value) : value_04(value) {}
    virtual ~TNumberValue();
    virtual void slot_04();

private:
    T value_04;
};

template <typename T>
void CNumber::bind_value(T value)
{
    if (number_value_24)
        operator delete(number_value_24);
    number_value_24 = new TNumberValue<T>(value);
}

typedef char CNumber_size_must_be_0xcc[
    sizeof(CNumber) == 0xCC ? 1 : -1];
typedef char TNumberValue_intptr_size_must_be_0x08[
    sizeof(TNumberValue<int *>) == 0x08 ? 1 : -1];

} // namespace th105
