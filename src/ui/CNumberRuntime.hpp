#pragma once

#include "UiPrimitives.hpp"
#include "Tile.hpp"

#include <new>

namespace th105 {

// Current RTTI identifies the 0xCC owner at CMenuConnect+0x108 as CNumber.
// The 0x28-byte controller prefix owns a actual CTile 0xA4 object at +0x28.
// CNumber's constructor body clears the value adapter only after the tile has
// completed construction; this ordering is required by the shipped ctor EH.
struct INumberValue;

class CNumber : public ::IColor {
public:
    CNumber()
    {
        typedef char ValueOffset[offsetof(CNumber, number_value_24) == 0x24 ? 1 : -1];
        typedef char TileOffset[offsetof(CNumber, tile_28) == 0x28 ? 1 : -1];
        number_value_24 = 0;
    }
    virtual ~CNumber()
    {
        if (number_value_24 != 0)
            operator delete(number_value_24);
    }
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);

    void initialize(
        unsigned int texture, int a, int b, int c, int d, int e,
        float f, int g, int h, int i);
    void render(int value, float x, float y, int digits, char sign_mode);

    template <typename T>
    void bind_value(T value);

private:
    friend class CDesignBase;
    friend void __stdcall render_bound(CNumber *number, float x, float y);
    friend void __stdcall render_floating(CNumber *number, float value,
        float x, float y, int integer_digits, int fractional_digits,
        char sign_mode);
    float glyph_width_04;
    float spacing_08;
    float scale_0c;
    float secondary_scale_10;
    int columns_14;
    int reserved_18;
    int reserved_1c;
    unsigned char mode_20;
    unsigned char reserved_21[3];
    INumberValue *number_value_24;
    CTile tile_28;
};

// RTTI proves a zero-offset INumberValue base. Slots 0/4 read the binding;
// CNumber releases the adapter directly, without a virtual destructor call.
struct INumberValue {
    virtual int get_integer() = 0;
    virtual float get_floating() = 0;
};

template <typename T>
class TNumberValue : public INumberValue {
public:
    explicit TNumberValue(T value) : value_04(value) {}
    virtual int get_integer() { return static_cast<int>(*value_04); }
    virtual float get_floating() { return static_cast<float>(*value_04); }

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
