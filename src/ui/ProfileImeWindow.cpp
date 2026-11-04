#include "ProfileMenuControllerRuntime.hpp"
#include <stddef.h>

namespace th105 {
extern void *g_bootstrap_window;

struct ImeRect16 { long left, top, right, bottom; };
struct ImePoint8 { long x, y; };
struct ImeCandidateForm32 {
    unsigned index, style;
    ImePoint8 position;
    ImeRect16 area;
};

extern "C" void *__stdcall ImmGetContext(void *window);
extern "C" int __stdcall ImmSetCandidateWindow(void *context, const ImeCandidateForm32 *form);
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(void *window, ImeRect16 *rect);

void initialize_ime_window_state()
{
    g_profile_menu_controller.ime_context_000 = ImmGetContext(g_bootstrap_window);
    ImeRect16 rect;
    ImeCandidateForm32 form;
    form.index = 0;
    form.style = 0x80;
    GetWindowRect(g_bootstrap_window, &rect);
    form.area.left = 0;
    form.area.top = 0;
    form.area.right = rect.right - rect.left;
    form.area.bottom = rect.bottom - rect.top;
    ImmSetCandidateWindow(g_profile_menu_controller.ime_context_000, &form);
}

typedef char ImeCandidateSize[sizeof(ImeCandidateForm32) == 32 ? 1 : -1];
typedef char ImeCandidateAreaOffset[offsetof(ImeCandidateForm32, area) == 16 ? 1 : -1];
}
