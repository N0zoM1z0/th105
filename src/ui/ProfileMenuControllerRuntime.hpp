#pragma once

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
typedef char ProfileMenuControllerRuntime_size_must_be_0xa14[
    sizeof(ProfileMenuControllerRuntime) == 0xa14 ? 1 : -1];

} // namespace th105
