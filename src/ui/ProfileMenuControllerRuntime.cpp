#include <string.h>

namespace th105 {

typedef void *HWND;
typedef void *HIMC;
typedef long LONG;
typedef unsigned long DWORD;

extern "C" LONG __stdcall ImmGetCompositionStringA(
    HIMC context, DWORD index, void *buffer, DWORD size);

struct ProfileMenuControllerRuntime {
    HIMC ime_context_000;
    unsigned unknown_004;
    char primary_008[0x400];
    char work_408[0x400];
    char composition_808[0x100];
    signed char attributes_908[0x100];
    int max_length_a08;
    unsigned char reset_a0c;
    unsigned char primary_pending_a0d;
    unsigned char secondary_pending_a0e;
    unsigned char mode_a0f;
    int cursor_a10;

    void set_mode(unsigned char mode);
    char *take_primary_text();
    char *take_secondary_text();
    void select_profile(const char *text);
    unsigned char consume_reset();
};

extern "C" ProfileMenuControllerRuntime g_profile_menu_controller;
void __cdecl commit_profile_ime_composition();

ProfileMenuControllerRuntime *__cdecl initialize_profile_menu_controller()
{
    g_profile_menu_controller.ime_context_000 = 0;
    g_profile_menu_controller.unknown_004 = 0;
    g_profile_menu_controller.max_length_a08 = 1023;
    memset(g_profile_menu_controller.primary_008, 0,
        sizeof(g_profile_menu_controller.primary_008));
    memset(g_profile_menu_controller.composition_808, 0,
        sizeof(g_profile_menu_controller.composition_808));
    g_profile_menu_controller.reset_a0c = 0;
    g_profile_menu_controller.primary_pending_a0d = 0;
    g_profile_menu_controller.secondary_pending_a0e = 0;
    g_profile_menu_controller.mode_a0f = 0;
    return &g_profile_menu_controller;
}

void ProfileMenuControllerRuntime::set_mode(unsigned char mode)
{
    if (mode_a0f == mode)
        return;
    mode_a0f = mode;
    if (!mode)
        return;
    memset(primary_008, 0, sizeof(primary_008));
    memset(composition_808, 0, sizeof(composition_808));
    cursor_a10 = 0;
}

LONG __cdecl refresh_profile_ime_composition()
{
    if (ImmGetCompositionStringA(
            g_profile_menu_controller.ime_context_000, 0x200, 0, 0))
        commit_profile_ime_composition();

    LONG length = ImmGetCompositionStringA(
        g_profile_menu_controller.ime_context_000,
        8,
        g_profile_menu_controller.composition_808,
        0xff);
    g_profile_menu_controller.composition_808[length] = 0;

    ImmGetCompositionStringA(
        g_profile_menu_controller.ime_context_000,
        0x10,
        g_profile_menu_controller.attributes_908,
        0xff);

    LONG result = ImmGetCompositionStringA(
        g_profile_menu_controller.ime_context_000, 0x80, 0, 0);
    g_profile_menu_controller.secondary_pending_a0e = 1;
    return result;
}

char *ProfileMenuControllerRuntime::take_primary_text()
{
    primary_pending_a0d = 0;
    return primary_008;
}

char *ProfileMenuControllerRuntime::take_secondary_text()
{
    if (!secondary_pending_a0e)
        return 0;
    secondary_pending_a0e = 0;
    return composition_808;
}

void ProfileMenuControllerRuntime::select_profile(const char *text)
{
    strcpy_s(primary_008, sizeof(primary_008), text);
    cursor_a10 = 0;
}

void __cdecl request_profile_input_reset()
{
    if (!g_profile_menu_controller.primary_pending_a0d &&
        !g_profile_menu_controller.secondary_pending_a0e) {
        memset(g_profile_menu_controller.composition_808,
            0,
            sizeof(g_profile_menu_controller.composition_808));
        g_profile_menu_controller.reset_a0c = 1;
    }
}

unsigned char ProfileMenuControllerRuntime::consume_reset()
{
    if (reset_a0c) {
        reset_a0c = 0;
        return 1;
    }
    return 0;
}

typedef char ProfileMenuControllerRuntime_size_must_be_0xa14[
    sizeof(ProfileMenuControllerRuntime) == 0xa14 ? 1 : -1];

} // namespace th105
