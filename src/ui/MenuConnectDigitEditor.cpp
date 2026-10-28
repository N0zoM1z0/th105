#include "ui/MenuCursor.hpp"
#include "ui/UiPrimitives.hpp"
#include <stddef.h>
namespace th105 {
struct EndpointEditButtons { int horizontal, vertical, confirm, cancel; };
extern "C" EndpointEditButtons *__cdecl endpoint_edit_buttons();
extern "C" void __cdecl dispatch_indexed_event(unsigned);
extern "C" bool __cdecl is_menu_initial_press(int,int,int,int);
extern UiDesignObject *g_profile_message_main;
struct ConnectDigitEditorView {
    unsigned char prefix_000[0x3f8];
    MenuCursorState cursors_3f8[2];
    unsigned short address_420[4];
    unsigned port_428;
    int update();
};
typedef char ConnectDigitEditor_address_offset[
    offsetof(ConnectDigitEditorView,address_420)==0x420?1:-1];
int ConnectDigitEditorView::update()
{
    MenuCursorState *cursor = cursors_3f8;
    unsigned char changed = static_cast<unsigned char>(
        cursor[0].update() | (cursor[1].update() * 2));
    bool editing_address = cursors_3f8[0].selection < 12;
    int part, digit;
    if (editing_address) {
        digit = 2 - cursors_3f8[0].selection % 3;
        part = cursors_3f8[0].selection / 3;
    } else {
        digit = 16 - cursors_3f8[0].selection;
        part = 4;
    }
    if (changed & 1) {
        dispatch_indexed_event(0x27);
        if (editing_address) {
            int power = 1;
            for (int i=0; i<digit; ++i) power *= 10;
            cursors_3f8[1].selection = 9 - address_420[part] / power % 10;
        } else {
            int power = 1;
            for (int i=0; i<digit; ++i) power *= 10;
            cursors_3f8[1].selection = 9 - port_428 / power % 10;
        }
        return 0;
    }
    if (changed & 2) {
        dispatch_indexed_event(0x27);
        if (editing_address) {
            unsigned value = address_420[part];
            address_420[part] = 0;
            unsigned power = 1;
            for (int i=0; i<3; ++i) {
                if (i == digit)
                    address_420[part] += static_cast<unsigned short>((9-cursors_3f8[1].selection)*power);
                else
                    address_420[part] += static_cast<unsigned short>((value%10)*power);
                value /= 10;
                power *= 10;
            }
        } else {
            unsigned value = port_428;
            port_428 = 0;
            unsigned power = 1;
            for (int i=0; i<5; ++i) {
                if (i == digit)
                    port_428 += (9-cursors_3f8[1].selection)*power;
                else
                    port_428 += (value%10)*power;
                value /= 10;
                power *= 10;
            }
        }
        return 0;
    }
    if (endpoint_edit_buttons()->confirm == 1) {
        g_profile_message_main->enabled = false;
        dispatch_indexed_event(0x28);
        return 1;
    }
    if (endpoint_edit_buttons()->cancel == 1 || is_menu_initial_press(1,0,0,0)) {
        g_profile_message_main->enabled = false;
        dispatch_indexed_event(0x29);
        return 2;
    }
    return 0;
}
}
