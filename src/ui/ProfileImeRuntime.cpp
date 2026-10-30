#include "ProfileMenuControllerRuntime.cpp"
namespace th105 {
void __cdecl commit_profile_ime_composition()
{
    LONG length = ImmGetCompositionStringA(g_profile_menu_controller.ime_context_000,
        0x800,g_profile_menu_controller.composition_808,0xff);
    g_profile_menu_controller.composition_808[length] = 0;
    char suffix[1024];
    strcpy_s(suffix,sizeof(suffix),&g_profile_menu_controller.primary_008[g_profile_menu_controller.cursor_a10]);
    unsigned count;
    if ((int)(1024-g_profile_menu_controller.cursor_a10) < (int)strlen(g_profile_menu_controller.composition_808))
        count = 1024-g_profile_menu_controller.cursor_a10;
    else count = strlen(g_profile_menu_controller.composition_808);
    strncpy_s(&g_profile_menu_controller.primary_008[g_profile_menu_controller.cursor_a10],
        1024-g_profile_menu_controller.cursor_a10,g_profile_menu_controller.composition_808,count);
    g_profile_menu_controller.cursor_a10 += length;
    if ((int)(1024-g_profile_menu_controller.cursor_a10) < (int)strlen(suffix))
        count = 1024-g_profile_menu_controller.cursor_a10;
    else count = strlen(suffix);
    strncpy_s(&g_profile_menu_controller.primary_008[g_profile_menu_controller.cursor_a10],
        1024-g_profile_menu_controller.cursor_a10,suffix,count);
    if (g_profile_menu_controller.cursor_a10 > g_profile_menu_controller.max_length_a08)
        g_profile_menu_controller.cursor_a10 -= length;
    char last = g_profile_menu_controller.primary_008[g_profile_menu_controller.max_length_a08-1];
    if (!profile_non_lead(last)) {
        g_profile_menu_controller.primary_008[g_profile_menu_controller.max_length_a08-1] = 0;
        g_profile_menu_controller.primary_008[g_profile_menu_controller.max_length_a08] = 0;
    } else g_profile_menu_controller.primary_008[g_profile_menu_controller.max_length_a08] = 0;
    memset(g_profile_menu_controller.composition_808,0,sizeof(g_profile_menu_controller.composition_808));
    g_profile_menu_controller.primary_pending_a0d = 1;
}
static void __stdcall move_profile_input_cursor(int direction)
{
    if (direction < 0) {
        if (g_profile_menu_controller.cursor_a10 < 2) g_profile_menu_controller.cursor_a10 = 0;
        else if (!profile_non_lead(g_profile_menu_controller.primary_008[g_profile_menu_controller.cursor_a10-2]))
            g_profile_menu_controller.cursor_a10 -= 2;
        else --g_profile_menu_controller.cursor_a10;
    } else if (direction > 0 && g_profile_menu_controller.primary_008[g_profile_menu_controller.cursor_a10]) {
        if (g_profile_menu_controller.cursor_a10 >= 1022) g_profile_menu_controller.cursor_a10 = 1023;
        if (!profile_non_lead(g_profile_menu_controller.primary_008[g_profile_menu_controller.cursor_a10]))
            g_profile_menu_controller.cursor_a10 += 2;
        else ++g_profile_menu_controller.cursor_a10;
        if (g_profile_menu_controller.cursor_a10 > g_profile_menu_controller.max_length_a08)
            g_profile_menu_controller.cursor_a10 = g_profile_menu_controller.max_length_a08;
    }
}
extern "C" __declspec(dllimport) int __stdcall ToAscii(unsigned,unsigned,const unsigned char *,unsigned short *,unsigned);
extern "C" __declspec(dllimport) long __stdcall DefWindowProcA(void *,unsigned,unsigned,long);
static bool __stdcall process_ime_window_message(void *window,unsigned message,unsigned wparam,long lparam)
{
    if (!g_profile_menu_controller.mode_a0f) return false;
    switch(message) {
    case 0x10d: case 0x10f:
        if (lparam & 8) refresh_profile_ime_composition();
        return true;
    case 0x102:
        switch(wparam) {
        case 8: case 9: return true;
        case 13: request_profile_input_reset(); return false;
        case 27: g_profile_menu_controller.mode_a0f = 0; return true;
        default: insert_profile_input_character(static_cast<char>(wparam)); return false;
        }
    case 0x100:
        switch(wparam) {
        case 13: request_profile_input_reset(); return true;
        case 37: move_profile_input_cursor(-1); return true;
        case 39: move_profile_input_cursor(1); return true;
        case 8:
            if (g_profile_menu_controller.cursor_a10 > 0) {
                move_profile_input_cursor(-1);
                delete_profile_input_character();
            }
            return true;
        case 46: delete_profile_input_character(); return true;
        default:
            unsigned short output[10];
            memset(output,0,sizeof(output));
            return ToAscii(wparam,lparam >> 16,0,output,1) <= 0;
        }
    case 0x10e: commit_profile_ime_composition(); return true;
    case 0x281:
        DefWindowProcA(window,0x281,wparam,lparam & 0x3ffffff0);
        return true;
    case 0x282: return wparam > 0 && wparam <= 5;
    default: return false;
    }
}
}
