#pragma once

#include "CriticalSectionWrapper.hpp"

#include <list>
#include <stddef.h>

namespace th105 {

typedef long D3DHResult;
typedef void *D3DWindowHandle;

// Minimal source-level COM contract for the current Direct3D9 backend.  The
// target's indirect call offsets close these method positions independently;
// ordinary virtual dispatch keeps the ABI explicit without manual vtable math.
struct D3DUnknown {
    virtual D3DHResult __stdcall QueryInterface(const void *, void **) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};

struct D3DSwapChain9 : D3DUnknown {
    virtual D3DHResult __stdcall Present(
        const void *source_rect,
        const void *destination_rect,
        D3DWindowHandle destination_window,
        const void *dirty_region,
        unsigned flags) = 0; // 3
};

struct D3DDevice9 : D3DUnknown {
    virtual D3DHResult __stdcall TestCooperativeLevel() = 0;        // 3
    virtual unsigned __stdcall GetAvailableTextureMem() = 0;       // 4
    virtual D3DHResult __stdcall EvictManagedResources() = 0;      // 5
    virtual D3DHResult __stdcall GetDirect3D(void **) = 0;         // 6
    virtual D3DHResult __stdcall GetDeviceCaps(void *) = 0;        // 7
    virtual D3DHResult __stdcall GetDisplayMode(unsigned, void *) = 0; // 8
    virtual D3DHResult __stdcall GetCreationParameters(void *) = 0; // 9
    virtual D3DHResult __stdcall SetCursorProperties(unsigned, unsigned, void *) = 0; // 10
    virtual void __stdcall SetCursorPosition(int, int, unsigned) = 0; // 11
    virtual int __stdcall ShowCursor(int) = 0;                     // 12
    virtual D3DHResult __stdcall CreateAdditionalSwapChain(void *, void **) = 0; // 13
    virtual D3DHResult __stdcall GetSwapChain(unsigned, void **) = 0; // 14
    virtual unsigned __stdcall GetNumberOfSwapChains() = 0;       // 15
    virtual D3DHResult __stdcall Reset(void *) = 0;                // 16
    virtual D3DHResult __stdcall Present(const void *, const void *, D3DWindowHandle, const void *) = 0; // 17
#define TH105_D3D_SLOT(N) virtual void __stdcall d3d_slot_##N() = 0;
    TH105_D3D_SLOT(18)
    TH105_D3D_SLOT(19)
    TH105_D3D_SLOT(20)
    TH105_D3D_SLOT(21)
    TH105_D3D_SLOT(22)
    TH105_D3D_SLOT(23)
    TH105_D3D_SLOT(24)
    TH105_D3D_SLOT(25)
    TH105_D3D_SLOT(26)
    TH105_D3D_SLOT(27)
    TH105_D3D_SLOT(28)
    TH105_D3D_SLOT(29)
    TH105_D3D_SLOT(30)
    TH105_D3D_SLOT(31)
    TH105_D3D_SLOT(32)
    TH105_D3D_SLOT(33)
    TH105_D3D_SLOT(34)
    TH105_D3D_SLOT(35)
    TH105_D3D_SLOT(36)
    TH105_D3D_SLOT(37)
    TH105_D3D_SLOT(38)
    TH105_D3D_SLOT(39)
    TH105_D3D_SLOT(40)
#undef TH105_D3D_SLOT
    virtual D3DHResult __stdcall BeginScene() = 0;                 // 41
    virtual D3DHResult __stdcall EndScene() = 0;                   // 42
    virtual D3DHResult __stdcall Clear(
        unsigned, const void *, unsigned, unsigned, float, unsigned) = 0; // 43
#define TH105_D3D_SLOT(N) virtual void __stdcall d3d_slot_##N() = 0;
    TH105_D3D_SLOT(44)
    TH105_D3D_SLOT(45)
    TH105_D3D_SLOT(46)
    TH105_D3D_SLOT(47)
    TH105_D3D_SLOT(48)
    TH105_D3D_SLOT(49)
    TH105_D3D_SLOT(50)
    TH105_D3D_SLOT(51)
    TH105_D3D_SLOT(52)
    TH105_D3D_SLOT(53)
    TH105_D3D_SLOT(54)
    TH105_D3D_SLOT(55)
    TH105_D3D_SLOT(56)
#undef TH105_D3D_SLOT
    virtual D3DHResult __stdcall SetRenderState(unsigned, unsigned) = 0; // 57
#define TH105_D3D_SLOT(N) virtual void __stdcall d3d_slot_##N() = 0;
    TH105_D3D_SLOT(58)
    TH105_D3D_SLOT(59)
    TH105_D3D_SLOT(60)
    TH105_D3D_SLOT(61)
    TH105_D3D_SLOT(62)
    TH105_D3D_SLOT(63)
    TH105_D3D_SLOT(64)
#undef TH105_D3D_SLOT
    virtual D3DHResult __stdcall SetTexture(unsigned, void *) = 0; // 65
#define TH105_D3D_SLOT(N) virtual void __stdcall d3d_slot_##N() = 0;
    TH105_D3D_SLOT(66)
    TH105_D3D_SLOT(67)
    TH105_D3D_SLOT(68)
#undef TH105_D3D_SLOT
    virtual D3DHResult __stdcall SetSamplerState(
        unsigned sampler, unsigned type, unsigned value) = 0; // 69
#define TH105_D3D_SLOT(N) virtual void __stdcall d3d_slot_##N() = 0;
    TH105_D3D_SLOT(70)
    TH105_D3D_SLOT(71)
    TH105_D3D_SLOT(72)
    TH105_D3D_SLOT(73)
    TH105_D3D_SLOT(74)
    TH105_D3D_SLOT(75)
    TH105_D3D_SLOT(76)
    TH105_D3D_SLOT(77)
    TH105_D3D_SLOT(78)
    TH105_D3D_SLOT(79)
    TH105_D3D_SLOT(80)
    TH105_D3D_SLOT(81)
    TH105_D3D_SLOT(82)
#undef TH105_D3D_SLOT
    virtual D3DHResult __stdcall DrawPrimitiveUP(
        unsigned primitive_type,
        unsigned primitive_count,
        const void *vertices,
        unsigned stride) = 0; // 83
#define TH105_D3D_SLOT(N) virtual void __stdcall d3d_slot_##N() = 0;
    TH105_D3D_SLOT(84)
    TH105_D3D_SLOT(85)
    TH105_D3D_SLOT(86)
    TH105_D3D_SLOT(87)
    TH105_D3D_SLOT(88)
#undef TH105_D3D_SLOT
    virtual D3DHResult __stdcall SetFVF(unsigned fvf) = 0; // 89
};

struct D3DDisplayMode16 {
    unsigned width_00;
    unsigned height_04;
    unsigned refresh_rate_08;
    unsigned format_0c;
};

struct D3DPresentParameters38 {
    unsigned back_buffer_width_00;
    unsigned back_buffer_height_04;
    unsigned back_buffer_format_08;
    unsigned back_buffer_count_0c;
    unsigned multisample_type_10;
    unsigned multisample_quality_14;
    unsigned swap_effect_18;
    D3DWindowHandle device_window_1c;
    int windowed_20;
    int enable_auto_depth_stencil_24;
    unsigned auto_depth_stencil_format_28;
    unsigned flags_2c;
    unsigned fullscreen_refresh_rate_30;
    unsigned presentation_interval_34;
};

struct D3DCaps130 {
    unsigned char bytes_000[0x130];
};

struct DeviceResetListener;

struct D3DBackend {
    CriticalSectionWrapper critical_section_000;
    D3DUnknown *direct3d_01c;
    D3DDevice9 *device_020;
    D3DSwapChain9 *swap_chain_024;
    D3DCaps130 caps_028;
    D3DPresentParameters38 presentation_158;
    D3DDisplayMode16 display_mode_190;
    long saved_window_style_1a0;
    D3DHResult cooperative_result_1a4;
    unsigned unknown_1a8;
    std::list<DeviceResetListener *> reset_listeners_1ac;
};

extern D3DBackend g_d3d_backend;

extern "C" __declspec(dllimport) int __stdcall TryEnterCriticalSection(
    Win32CriticalSection24 *critical_section);

void shutdown_d3d_backend();

typedef char D3DPresentParameters_size_must_be_0x38[
    sizeof(D3DPresentParameters38) == 0x38 ? 1 : -1];
typedef char D3DDisplayMode_size_must_be_0x10[
    sizeof(D3DDisplayMode16) == 0x10 ? 1 : -1];
typedef char D3DCaps_size_must_be_0x130[
    sizeof(D3DCaps130) == 0x130 ? 1 : -1];
typedef char D3DBackend_direct3d_offset_must_be_0x1c[
    offsetof(D3DBackend, direct3d_01c) == 0x1c ? 1 : -1];
typedef char D3DBackend_device_offset_must_be_0x20[
    offsetof(D3DBackend, device_020) == 0x20 ? 1 : -1];
typedef char D3DBackend_swap_chain_offset_must_be_0x24[
    offsetof(D3DBackend, swap_chain_024) == 0x24 ? 1 : -1];
typedef char D3DBackend_caps_offset_must_be_0x28[
    offsetof(D3DBackend, caps_028) == 0x28 ? 1 : -1];
typedef char D3DBackend_presentation_offset_must_be_0x158[
    offsetof(D3DBackend, presentation_158) == 0x158 ? 1 : -1];
typedef char D3DBackend_display_mode_offset_must_be_0x190[
    offsetof(D3DBackend, display_mode_190) == 0x190 ? 1 : -1];
typedef char D3DBackend_cooperative_offset_must_be_0x1a4[
    offsetof(D3DBackend, cooperative_result_1a4) == 0x1a4 ? 1 : -1];
typedef char D3DBackend_listener_list_offset_must_be_0x1ac[
    offsetof(D3DBackend, reset_listeners_1ac) == 0x1ac ? 1 : -1];

} // namespace th105
