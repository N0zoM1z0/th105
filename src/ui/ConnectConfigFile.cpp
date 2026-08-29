#include <string.h>

namespace th105 {

extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentDirectoryA(
    unsigned long size, char *buffer);
extern "C" __declspec(dllimport) unsigned long __stdcall GetFileAttributesA(
    const char *path);
extern "C" __declspec(dllimport) unsigned int __stdcall GetPrivateProfileIntA(
    const char *section, const char *key, int default_value, const char *path);
extern "C" __declspec(dllimport) unsigned long __stdcall GetPrivateProfileStringA(
    const char *section, const char *key, const char *default_value,
    char *output, unsigned long output_size, const char *path);

struct ConnectConfigIniView {
    char path_buffer_000[260];

    bool has_file_40f0b0(const char *path);
    unsigned int read_uint_40f100(const char *section, const char *key);
    unsigned long read_string_40f120(
        const char *section, const char *key, char *output, unsigned long size);
};

typedef char ConnectConfigIniView_path_buffer_size[
    sizeof(((ConnectConfigIniView *)0)->path_buffer_000) == 260 ? 1 : -1];

bool ConnectConfigIniView::has_file_40f0b0(const char *path)
{
    GetCurrentDirectoryA(260, path_buffer_000);
    strcat_s(path_buffer_000, 260, "/");
    strcat_s(path_buffer_000, 260, path);
    const unsigned long attributes = GetFileAttributesA(path_buffer_000);
    if (attributes != 0xffffffffu && (attributes & 0x10u) == 0)
        return true;
    return false;
}

unsigned int ConnectConfigIniView::read_uint_40f100(
    const char *section, const char *key)
{
    return GetPrivateProfileIntA(section, key, -1, path_buffer_000);
}

unsigned long ConnectConfigIniView::read_string_40f120(
    const char *section, const char *key, char *output, unsigned long size)
{
    return GetPrivateProfileStringA(
        section, key, "", output, size, path_buffer_000);
}

} // namespace th105
