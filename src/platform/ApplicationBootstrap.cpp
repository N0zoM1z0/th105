// Complete caller/private-helper island; keep these definitions in one TU.
// Target ABI and nonexact residuals: docs/APPLICATION_BOOTSTRAP_2026_10_16.md.
#include "platform/ApplicationStartupOptions.hpp"
#include "platform/SystemUtilities.hpp"
#include "engine/D3DBackend.hpp"
#include "engine/SceneBase.hpp"
#include "audio/DirectSound.hpp"
#include <string.h>

namespace th105 {
extern "C" __declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(void *, char *, unsigned long);
extern "C" __declspec(dllimport) long __stdcall GetWindowLongA(void *, int);
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(void *, const char *, const char *, unsigned);
extern "C" __declspec(dllimport) int __stdcall GetWindowInfo(void *, void *);
extern "C" __declspec(dllimport) unsigned __stdcall timeBeginPeriod(unsigned);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) long __stdcall CoInitialize(void *);
extern "C" __declspec(dllimport) int __stdcall ShowCursor(int);
extern "C" __declspec(dllimport) void *__stdcall CreateThread(void *, unsigned long, unsigned long (__stdcall *)(void *), void *, unsigned long, unsigned long *);
extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void *, int);
extern "C" __declspec(dllimport) long __stdcall CoCreateInstance(const Guid &, void *, unsigned long, const Guid &, void **);

extern void *g_bootstrap_window;
extern void *g_bootstrap_instance;
extern bool g_bootstrap_mode;
extern const char graphics_error_title[], graphics_create_error[];
extern const char graphics_display_error[], graphics_device_error[];
extern const char sound_error_title[], sound_create_error[], sound_initialize_error[];
extern const char sound_cooperative_error[], sound_buffer_error[], sound_listener_error[];
extern const Guid sound_class_id, sound_interface_id, sound_listener_id;
void __cdecl mt19937_seed_u32(unsigned);
void __cdecl initialize_default_render_state();
void __cdecl initialize_input_controllers();
void __cdecl initialize_ime_window_state();
extern "C" unsigned long __stdcall bootstrap_control_thread(void *);
extern "C" unsigned long __stdcall bootstrap_graphics_thread(void *);
extern "C" unsigned long __stdcall bootstrap_scene_thread(void *);

struct BootstrapRect16 { long left, top, right, bottom; };
struct BootstrapWindowInfo60 {
    unsigned size;
    BootstrapRect16 window, client;
    unsigned style, extended_style, status, border_x, border_y;
    unsigned short window_type, creator_version;
};
struct BootstrapDirect3D9 : D3DUnknown {
    virtual D3DHResult __stdcall RegisterSoftwareDevice(void *) = 0;
    virtual unsigned __stdcall GetAdapterCount() = 0;
    virtual D3DHResult __stdcall GetAdapterIdentifier(unsigned, unsigned, void *) = 0;
    virtual unsigned __stdcall GetAdapterModeCount(unsigned, unsigned) = 0;
    virtual D3DHResult __stdcall EnumAdapterModes(unsigned, unsigned, unsigned, void *) = 0;
    virtual D3DHResult __stdcall GetAdapterDisplayMode(unsigned, D3DDisplayMode16 *) = 0;
    virtual D3DHResult __stdcall CheckDeviceType(unsigned, unsigned, unsigned, unsigned, int) = 0;
    virtual D3DHResult __stdcall CheckDeviceFormat(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned) = 0;
    virtual D3DHResult __stdcall CheckDeviceMultiSampleType(unsigned, unsigned, unsigned, int, unsigned, unsigned *) = 0;
    virtual D3DHResult __stdcall CheckDepthStencilMatch(unsigned, unsigned, unsigned, unsigned, unsigned) = 0;
    virtual D3DHResult __stdcall CheckDeviceFormatConversion(unsigned, unsigned, unsigned, unsigned) = 0;
    virtual D3DHResult __stdcall GetDeviceCaps(unsigned, unsigned, void *) = 0;
    virtual void *__stdcall GetAdapterMonitor(unsigned) = 0;
    virtual D3DHResult __stdcall CreateDevice(unsigned, unsigned, void *, unsigned,
        D3DPresentParameters38 *, D3DDevice9 **) = 0;
};
extern "C" BootstrapDirect3D9 *__stdcall Direct3DCreate9(unsigned);

struct DirectSoundBufferDescription {
    unsigned size, flags, bytes, reserved;
    void *format;
    Guid algorithm;
};
struct BootstrapSoundCaps96 { unsigned size; unsigned fields_004[23]; };
struct BootstrapDirectSound8 : DirectSound8 {
    virtual HResult __stdcall get_caps(BootstrapSoundCaps96 *) = 0;
    virtual HResult __stdcall duplicate_buffer(DirectSoundBuffer *, DirectSoundBuffer **) = 0;
    virtual HResult __stdcall set_cooperative_level(void *, ULong) = 0;
    virtual HResult __stdcall compact() = 0;
    virtual HResult __stdcall get_speaker_config(ULong *) = 0;
    virtual HResult __stdcall set_speaker_config(ULong) = 0;
    virtual HResult __stdcall initialize(const Guid *) = 0;
    virtual HResult __stdcall verify_certification(ULong *) = 0;
};

static void __stdcall initialize_window_paths(void *instance, void *window);
static bool __stdcall initialize_graphics(void *window, int width, int height, bool synchronized);
static bool __stdcall initialize_audio(void *window, unsigned flags);

struct BootstrapThread8 {
    void *handle;
    unsigned long id;
    void wait_for_exit();
};
struct BootstrapSceneManager {
    virtual void initialize();
    virtual void shutdown();
    virtual void update();
    virtual unsigned char render();
    virtual IScene *create_scene(unsigned);
};
struct BootstrapFade {
    virtual bool initialize();
};
struct ApplicationBootstrapView {
    void *window_00, *instance_04;
    ApplicationStartupOptions options_08;
    unsigned char unknown_030[8];
    unsigned long timestamp_038;
    unsigned char unknown_03c[0x10];
    bool running_04c;
    unsigned char unknown_04d[3];
    BootstrapThread8 control_050, graphics_058;
    void *event_060;
    BootstrapThread8 worker_064, scene_06c;
    BootstrapSceneManager *manager_074;
    BootstrapFade *fade_078;
    IScene *previous_scene_07c, *current_scene_080;
    unsigned char unknown_084[0x0c];
    void *event_090;
    CriticalSectionWrapper scene_lock_094;
    unsigned initial_state_0b0;
    int transition_0b4;
    bool initialize(const ApplicationStartupOptions *options);
};

bool ApplicationBootstrapView::initialize(const ApplicationStartupOptions *options)
{
    options_08 = *options;
    window_00 = options_08.window_00;
    instance_04 = options_08.instance_04;
    g_bootstrap_mode = options_08.flag_27 != 0;
    manager_074 = static_cast<BootstrapSceneManager *>(options_08.application_callbacks_14);
    fade_078 = static_cast<BootstrapFade *>(options_08.secondary_callbacks_1c);
    timeBeginPeriod(1);
    mt19937_seed_u32(timeGetTime());
    if (CoInitialize(0) < 0)
        return false;
    initialize_window_paths(instance_04, window_00);
    if (!options_08.cursor_visible_24)
        ShowCursor(0);
    running_04c = true;
    if (options_08.graphics_enabled_20) {
        if (!initialize_graphics(window_00, options_08.graphics_option_08,
                options_08.graphics_option_0c, options_08.graphics_flag_25))
            return false;
        graphics_058.wait_for_exit();
        graphics_058.handle = CreateThread(0, 0, bootstrap_graphics_thread, 0, 0, &graphics_058.id);
        SetThreadPriority(graphics_058.handle, -15);
        initialize_default_render_state();
    }
    if (options_08.input_enabled_21) {
        if (!initialize_direct_input(window_00, instance_04))
            return false;
        if (!initialize_keyboard_device())
            return false;
        if (!initialize_mouse_device())
            return false;
        initialize_input_controllers();
    }
    if (options_08.audio_enabled_22 && !initialize_audio(window_00, options_08.audio_option_10))
        return false;
    if (options_08.ime_enabled_23)
        initialize_ime_window_state();
    timestamp_038 = timeGetTime();
    manager_074->initialize();
    if (fade_078)
        fade_078->initialize();
    initial_state_0b0 = options_08.initial_state_18;
    previous_scene_07c = current_scene_080 = 0;
    transition_0b4 = -1;
    current_scene_080 = manager_074->create_scene(initial_state_0b0);
    scene_06c.wait_for_exit();
    scene_06c.handle = CreateThread(0, 0, bootstrap_scene_thread, 0, 0, &scene_06c.id);
    SetThreadPriority(scene_06c.handle, -15);
    control_050.wait_for_exit();
    control_050.handle = CreateThread(0, 0, bootstrap_control_thread, 0, 0, &control_050.id);
    return true;
}

static void __stdcall initialize_window_paths(void *instance, void *window)
{
    g_bootstrap_window = window;
    g_bootstrap_instance = instance;
    char path[260];
    GetModuleFileNameA(0, path, sizeof(path));
    char *last = strrchr(path, '/');
    if (!last)
        last = strrchr(path, '\\');
    last[1] = 0;
    strcpy_s(g_module_path_text.path, sizeof(g_module_path_text.path), path);
}

static bool __stdcall initialize_graphics(void *window, int width, int height, bool synchronized)
{
    g_d3d_backend.saved_window_style_1a0 = GetWindowLongA(window, -16);
    g_d3d_backend.direct3d_01c = Direct3DCreate9(32);
    if (!g_d3d_backend.direct3d_01c) {
        MessageBoxA(0, graphics_create_error, graphics_error_title, 0);
        return false;
    }
    if (static_cast<BootstrapDirect3D9 *>(g_d3d_backend.direct3d_01c)->GetAdapterDisplayMode(0, &g_d3d_backend.display_mode_190) < 0) {
        MessageBoxA(0, graphics_display_error, graphics_error_title, 0);
        return false;
    }
    memset(&g_d3d_backend.presentation_158, 0, sizeof(g_d3d_backend.presentation_158));
    if (width <= 0 || height <= 0) {
        BootstrapWindowInfo60 info;
        memset(&info, 0, sizeof(info));
        GetWindowInfo(window, &info);
        width = info.client.right - info.client.left;
        height = info.client.bottom - info.client.top;
    }
    D3DPresentParameters38 &parameters = g_d3d_backend.presentation_158;
    parameters.back_buffer_width_00 = width;
    parameters.back_buffer_height_04 = height;
    parameters.back_buffer_format_08 = g_d3d_backend.display_mode_190.format_0c;
    parameters.back_buffer_count_0c = 1;
    parameters.multisample_type_10 = 0;
    parameters.swap_effect_18 = 1;
    parameters.device_window_1c = window;
    parameters.windowed_20 = 1;
    parameters.enable_auto_depth_stencil_24 = 1;
    parameters.auto_depth_stencil_format_28 = 75;
    parameters.flags_2c = 2;
    parameters.fullscreen_refresh_rate_30 = 0;
    parameters.presentation_interval_34 = synchronized ? 1 : 0x80000000u;
    if (static_cast<BootstrapDirect3D9 *>(g_d3d_backend.direct3d_01c)->CreateDevice(0, 1, window, 0x44, &parameters, &g_d3d_backend.device_020) < 0
        && static_cast<BootstrapDirect3D9 *>(g_d3d_backend.direct3d_01c)->CreateDevice(0, 1, window, 0x24, &parameters, &g_d3d_backend.device_020) < 0
        && static_cast<BootstrapDirect3D9 *>(g_d3d_backend.direct3d_01c)->CreateDevice(0, 2, window, 0x24, &parameters, &g_d3d_backend.device_020) < 0) {
        MessageBoxA(0, graphics_device_error, graphics_error_title, 0);
        return false;
    }
    memset(&g_d3d_backend.caps_028, 0, sizeof(g_d3d_backend.caps_028));
    g_d3d_backend.device_020->GetDeviceCaps(&g_d3d_backend.caps_028);
    g_d3d_backend.device_020->GetSwapChain(0, reinterpret_cast<void **>(&g_d3d_backend.swap_chain_024));
    g_d3d_backend.device_020->Clear(0, 0, 3, 0, 1.0f, 0);
    return true;
}

static bool __stdcall initialize_audio(void *window, unsigned flags)
{
    if (CoCreateInstance(sound_class_id, 0, 3, sound_interface_id,
            reinterpret_cast<void **>(&g_direct_sound_globals.direct_sound)) < 0) {
        MessageBoxA(0, sound_create_error, sound_error_title, 0);
        return false;
    }
    if (static_cast<BootstrapDirectSound8 *>(g_direct_sound_globals.direct_sound)->initialize(0) < 0) {
        MessageBoxA(0, sound_initialize_error, sound_error_title, 0);
        return false;
    }
    if (static_cast<BootstrapDirectSound8 *>(g_direct_sound_globals.direct_sound)->set_cooperative_level(window, 2) < 0 && static_cast<BootstrapDirectSound8 *>(g_direct_sound_globals.direct_sound)->set_cooperative_level(window, 1) < 0) {
        MessageBoxA(0, sound_cooperative_error, sound_error_title, 0);
        return false;
    }
    BootstrapSoundCaps96 caps;
    memset(&caps, 0, sizeof(caps));
    caps.size = sizeof(caps);
    static_cast<BootstrapDirectSound8 *>(g_direct_sound_globals.direct_sound)->get_caps(&caps);
    unsigned listener = flags & 1;
    DirectSoundBufferDescription description = {};
    description.size = sizeof(description);
    description.flags = 9 | (listener ? 16 : 0);
    if (static_cast<BootstrapDirectSound8 *>(g_direct_sound_globals.direct_sound)->create_sound_buffer(&description,
            reinterpret_cast<DirectSoundBuffer **>(&g_direct_sound_globals.primary_sound_buffer), 0) < 0) {
        MessageBoxA(0, sound_buffer_error, sound_error_title, 0);
        return false;
    }
    if (listener) {
        if (g_direct_sound_globals.primary_sound_buffer->query_interface(&sound_listener_id,
                reinterpret_cast<void **>(&g_direct_sound_globals.direct_sound_listener)) < 0) {
            MessageBoxA(0, sound_listener_error, sound_error_title, 0);
            return false;
        }
        g_direct_sound_globals.primary_sound_buffer->add_ref();
    }
    g_direct_sound_globals.primary_sound_buffer->play(0, 0, 1);
    return true;
}

typedef char BootstrapWindowInfoSize[sizeof(BootstrapWindowInfo60) == 60 ? 1 : -1];
typedef char BootstrapSoundCapsSize[sizeof(BootstrapSoundCaps96) == 96 ? 1 : -1];
typedef char BootstrapSoundDescriptionSize[sizeof(DirectSoundBufferDescription) == 36 ? 1 : -1];
typedef char BootstrapRunningOffset[offsetof(ApplicationBootstrapView, running_04c) == 0x4c ? 1 : -1];
typedef char BootstrapManagerOffset[offsetof(ApplicationBootstrapView, manager_074) == 0x74 ? 1 : -1];
typedef char BootstrapInitialStateOffset[offsetof(ApplicationBootstrapView, initial_state_0b0) == 0xb0 ? 1 : -1];
}
