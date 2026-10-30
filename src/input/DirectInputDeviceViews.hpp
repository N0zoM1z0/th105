#pragma once
#include <windows.h>

namespace th105 {
struct DirectInput8View;
struct DirectInputDevice8View;
struct DirectInput8VtableView {
    void *slots_00[3];
    long (__stdcall *create_device)(
        DirectInput8View *, const GUID *, DirectInputDevice8View **, void *);
    void *slots_10[3];
    long (__stdcall *initialize)(DirectInput8View *, void *, unsigned long);
};
struct DirectInput8View {
    DirectInput8VtableView *vtable;
};

struct DirectInputDevice8VtableView {
    void *slots_00[6];
    long (__stdcall *set_property)(DirectInputDevice8View *, const GUID *, const void *);
    long (__stdcall *acquire)(DirectInputDevice8View *);
    void *slots_20[3];
    long (__stdcall *set_data_format)(DirectInputDevice8View *, const void *);
    void *slot_30;
    long (__stdcall *set_cooperative_level)(
        DirectInputDevice8View *, HWND, unsigned long);
};
struct DirectInputDevice8View {
    DirectInputDevice8VtableView *vtable;
};

extern HWND g_direct_input_window;
extern DirectInput8View *g_direct_input_interface;
extern DirectInputDevice8View *g_keyboard_device;
extern DirectInputDevice8View *g_mouse_device;
extern const GUID direct_input_class_id;
extern const GUID direct_input_interface_id;
extern const GUID keyboard_device_guid;
extern const GUID mouse_device_guid;
extern const unsigned char keyboard_data_format[];
extern const unsigned char mouse_data_format[];
extern const char direct_input_create_error[];
extern const char direct_input_initialize_error[];
extern const char direct_input_error_title[];
extern const char direct_input_create_keyboard_error[];
extern const char direct_input_set_format_error[];
extern const char direct_input_cooperative_error[];
extern const char direct_input_create_mouse_error[];

extern const char direct_input_property_error[];
} // namespace th105
