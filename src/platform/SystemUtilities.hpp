#pragma once

namespace th105 {

struct ModulePathTextView {
    char path[260];
    unsigned char extra_bytes(unsigned char value);
};

extern ModulePathTextView g_module_path_text;

int __stdcall split_path_components(
    char *full_path,
    char *directory,
    char *filename);
void __stdcall read_clipboard_ansi(char *destination, unsigned int size);
unsigned char __stdcall initialize_direct_input(void *window, void *instance);
unsigned char initialize_keyboard_device();

} // namespace th105
