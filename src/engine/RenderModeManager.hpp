#pragma once

#include "D3DBackend.hpp"

#include <stddef.h>

namespace th105 {

struct DeviceResetListener {
    virtual void on_device_lost() = 0;
    virtual void on_device_reset() = 0;
};

struct RenderModeState28 {
    int blend_mode_00;
    int sampler_mode_04;
    int state_22_08;
    int current_mode_0c;
    union {
        unsigned packed_10;
        struct {
            unsigned char gate_7_10;
            unsigned char gate_14_11;
            unsigned char unknown_12;
            unsigned char unknown_13;
        };
    };
    unsigned state_23_14;
    union {
        unsigned packed_18;
        struct {
            unsigned char pair_first_18;
            unsigned char pair_second_19;
            unsigned char mode_flag_1a;
            unsigned char unknown_1b;
        };
    };
};

struct RenderModeManager : DeviceResetListener {
    D3DDevice9 *device_04;
    unsigned unknown_08;
    RenderModeState28 state_0c;
    unsigned char unknown_28[2];
    unsigned char reset_flag_2a;
    unsigned char unknown_2b;
    unsigned state_2c;
    unsigned clear_color_30;

    bool begin_frame();
    void finish_frame();
    void prepare_frame();
    void set_mode(int mode);
    D3DHResult set_sampler_state(
        unsigned sampler, unsigned state, unsigned value);
    D3DHResult submit_primitive(
        unsigned primitive_type,
        unsigned primitive_count,
        const void *vertices,
        unsigned stride,
        unsigned fvf);
    D3DHResult submit_textured_primitive(
        unsigned texture_handle,
        unsigned primitive_type,
        unsigned primitive_count,
        const void *vertices,
        unsigned stride,
        unsigned fvf);
    int draw_rect(
        float left,
        float top,
        float right,
        float bottom,
        unsigned color,
        unsigned char filled);
    int draw_rect_int(
        const int *rect,
        unsigned color,
        unsigned char filled);
    void set_blend_mode(int mode);
    unsigned char set_pair_state(
        unsigned char first, unsigned char second);
    int set_gate_states(unsigned char gate7, unsigned char gate14);
    int set_state_23(int value);
    void set_state_22(int mode);
    int apply_render_mode(int mode, unsigned char flag);

    virtual void on_device_lost();
    virtual void on_device_reset();
};

extern RenderModeManager g_render_mode_manager;

bool present_d3d_frame();

typedef char RenderModeState_size_must_be_0x1c[
    sizeof(RenderModeState28) == 0x1c ? 1 : -1];
typedef char RenderModeManager_device_offset_must_be_0x04[
    offsetof(RenderModeManager, device_04) == 0x04 ? 1 : -1];
typedef char RenderModeManager_state_offset_must_be_0x0c[
    offsetof(RenderModeManager, state_0c) == 0x0c ? 1 : -1];
typedef char RenderModeManager_reset_flag_offset_must_be_0x2a[
    offsetof(RenderModeManager, reset_flag_2a) == 0x2a ? 1 : -1];
typedef char RenderModeManager_clear_color_offset_must_be_0x30[
    offsetof(RenderModeManager, clear_color_30) == 0x30 ? 1 : -1];

} // namespace th105
