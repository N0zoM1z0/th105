#include "assets/FileReader.hpp"
#include "PackageArchiveStore.hpp"
#include <new>
#include <cstring>
#include <string>
#include <vector>

extern "C" __declspec(dllimport) int __stdcall ReadFile(
    void *file, void *buffer, unsigned long size,
    unsigned long *bytes_read, void *overlapped);

namespace th105 {
void __cdecl mt19937_seed_u32(unsigned int seed);
unsigned int __cdecl mt19937_next_u32();
void __stdcall register_package_file_entry(
    const char *path, unsigned int archive_index,
    unsigned int size, unsigned int offset);

// Observed private ECX entry; the ordinary typed helper and real wrapper
// let VC8 generate this boundary without a custom register convention.
static bool load_package_archive_impl(const char *path)
{
    FileHandle file = CreateFileA(path, 0x80000000u, 1, 0, 3, 0x80, 0);
    if (file == reinterpret_cast<FileHandle>(-1))
        return false;

    unsigned int archive_index = g_package_archive_store.names_1c.size();
    g_package_archive_store.names_1c.push_back(std::string(path));
    g_package_archive_store.count_38 = g_package_archive_store.names_1c.size();

    // The target ignores read statuses/counts and trusts the index metadata.
    unsigned short entry_count;
    unsigned int index_size;
    unsigned long bytes_read;
    ReadFile(file, &entry_count, 2, &bytes_read, 0);
    ReadFile(file, &index_size, 4, &bytes_read, 0);
    unsigned char *index = new unsigned char[index_size];
    ReadFile(file, index, index_size, &bytes_read, 0);
    CloseHandle(file);

    mt19937_seed_u32(index_size + 6);
    for (unsigned int i = 0; i < index_size; ++i)
        index[i] ^= static_cast<unsigned char>(mt19937_next_u32());

    unsigned char key = 0xc5;
    unsigned char step = 0x83;
    for (unsigned int i = 0; i < index_size; ++i) {
        index[i] ^= key;
        key += step;
        step += 0x53;
    }

    unsigned char *cursor = index;
    // A one-byte stored length needs at most 255 bytes plus the terminator.
    // The original buffer declaration remains unknown.
    char entry_path[256];
    for (unsigned int i = 0; i < entry_count; ++i) {
        unsigned int offset = *reinterpret_cast<unsigned int *>(cursor);
        cursor += 4;
        unsigned int size = *reinterpret_cast<unsigned int *>(cursor);
        cursor += 4;
        unsigned char length = *cursor++;
        std::memcpy(entry_path, cursor, length);
        entry_path[length] = 0;
        cursor += length;
        register_package_file_entry(entry_path, archive_index, size, offset);
    }
    delete[] index;
    return true;
}

bool __cdecl load_package_archive(const char *path)
{
    return load_package_archive_impl(path);
}

} // namespace th105
