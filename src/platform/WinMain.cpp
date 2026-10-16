#include <windows.h>
#include <string.h>
#include "platform/ApplicationStartupOptions.hpp"

namespace th105 {
extern const char startup_mutex_name[];
extern const char startup_icon_name[];
extern const char startup_window_class[];
extern const char startup_window_title[];
extern const char startup_title_format[];
extern const char startup_package_b[];
extern const char startup_package_a[];
extern const char startup_package_c[];
extern const char startup_error_message[];
extern const char startup_error_title[];

extern "C" LRESULT __stdcall application_window_proc(HWND, UINT, WPARAM, LPARAM);
bool __cdecl mount_startup_archive(const char *path);

// Entry-only views. The target RTTI/vtables fix the complete five-slot
// order and allocation sizes; no constructor initializes CFade's scalars.
struct StartupSceneManagerView {
    virtual void initialize();
    virtual void shutdown();
    virtual void update();
    virtual unsigned char render();
    virtual void *create_scene(int selector);
};
struct StartupFadeView {
    virtual bool initialize();
    virtual void shutdown();
    virtual bool update();
    virtual bool is_ready();
    virtual bool render();
    unsigned color_04;
    int timer_08;
};
// Only method-call ABI is used here. Full application layout remains
// separate; this extern view does not allocate or construct an application.
struct ApplicationEntryView {
    bool initialize(const ApplicationStartupOptions *options);
    void run();
    void shutdown();
};
extern ApplicationEntryView g_application_entry;
} // namespace th105

extern "C" int __stdcall WinMain(HINSTANCE instance, HINSTANCE previous,
    char *command_line, int show)
{
    HANDLE mutex = CreateMutexA(0, TRUE, th105::startup_mutex_name);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
        return 1;

    char module_path[MAX_PATH];
    GetModuleFileNameA(0, module_path, MAX_PATH);
    strrchr(module_path, '\\')[1] = '\0';
    SetCurrentDirectoryA(module_path);

    int width = GetSystemMetrics(SM_CXEDGE) + GetSystemMetrics(SM_CXDLGFRAME)
        + GetSystemMetrics(SM_CXBORDER) + 640;
    int height = GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYDLGFRAME)
        + GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYCAPTION) + 480;

    WNDCLASSEXA window_class;
    window_class.cbSize = sizeof(window_class);
    window_class.hInstance = instance;
    window_class.lpszClassName = th105::startup_window_class;
    window_class.lpfnWndProc = th105::application_window_proc;
    window_class.style = 0;
    window_class.hIcon = LoadIconA(instance, th105::startup_icon_name);
    window_class.hIconSm = static_cast<HICON>(LoadImageA(
        instance, MAKEINTRESOURCEA(112), IMAGE_ICON, 16, 16, 0));
    window_class.hCursor = LoadCursorA(0, IDC_ARROW);
    window_class.lpszMenuName = 0;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    if (!RegisterClassExA(&window_class))
        return 0;

    char title[MAX_PATH];
    wsprintfA(title, th105::startup_title_format, th105::startup_window_title);
    HWND window = CreateWindowExA(WS_EX_APPWINDOW,
        th105::startup_window_class, title,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, instance, 0);
    if (!window)
        return 0;
    ShowWindow(window, show);
    UpdateWindow(window);

    th105::ApplicationStartupOptions options;
    options.window_00 = window;
    options.instance_04 = instance;
    options.application_callbacks_14 = new th105::StartupSceneManagerView;
    options.secondary_callbacks_1c = new th105::StartupFadeView;
    options.graphics_flag_25 = false;
    options.ime_enabled_23 = true;
    options.flag_27 = true;
    if (!th105::mount_startup_archive(th105::startup_package_b)) {
        CloseHandle(mutex);
        delete static_cast<th105::StartupSceneManagerView *>(options.application_callbacks_14);
        delete static_cast<th105::StartupFadeView *>(options.secondary_callbacks_1c);
        return 0;
    }
    if (!th105::mount_startup_archive(th105::startup_package_a)) {
        CloseHandle(mutex);
        delete static_cast<th105::StartupSceneManagerView *>(options.application_callbacks_14);
        delete static_cast<th105::StartupFadeView *>(options.secondary_callbacks_1c);
        return 0;
    }
    th105::mount_startup_archive(th105::startup_package_c);
    if (th105::g_application_entry.initialize(&options))
        th105::g_application_entry.run();
    else
        MessageBoxA(window, th105::startup_error_message, th105::startup_error_title, 0);
    ShowWindow(window, SW_HIDE);
    th105::g_application_entry.shutdown();
    CloseHandle(mutex);
    return 0;
}

typedef char StartupSceneManagerAllocationSize[sizeof(th105::StartupSceneManagerView) == 4 ? 1 : -1];
typedef char StartupFadeAllocationSize[sizeof(th105::StartupFadeView) == 12 ? 1 : -1];
