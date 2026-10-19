#include "FileReader.hpp"
#include "PackageFileIndexNode.hpp"
#include <map>
#include <string>
#include <vector>
#include <cstring>

namespace th105 {

typedef std::map<unsigned int, PackageFileIndexNode> PackageEntryMap;
typedef std::vector<std::string> PackageArchiveNames;

extern PackageEntryMap g_package_entry_map;
extern PackageArchiveNames g_package_archive_names;

unsigned int __cdecl case_insensitive_crc32(const unsigned char *, int);

typedef char PackageMapSize[sizeof(PackageEntryMap) == 12 ? 1 : -1];
typedef char PackageVectorSize[sizeof(PackageArchiveNames) == 16 ? 1 : -1];
typedef char PackageStringSize[sizeof(std::string) == 28 ? 1 : -1];
typedef char PackageIteratorSize[sizeof(PackageEntryMap::iterator) == 8 ? 1 : -1];

// @41BFA0: behavior reviewed; standalone STL call boundaries remain nonexact.
FileHandle __stdcall open_package_file_entry(
    const char *path, FileSize *entry_size, FileSize *entry_offset)
{
    unsigned int hash = case_insensitive_crc32(
        reinterpret_cast<const unsigned char *>(path),
        static_cast<int>(std::strlen(path)));
    PackageEntryMap::iterator entry = g_package_entry_map.find(hash);
    if (entry == g_package_entry_map.end())
        return 0;

    PackageFileIndexNode *node = &entry->second;
    if (node->next_10 != 0) {
        while (_stricmp(node->path_00, path) != 0) {
            node = node->next_10;
            if (node == 0)
                return 0;
        }
    }

    unsigned int archive_index = node->archive_index_04;
    *entry_size = node->size_08;
    *entry_offset = node->offset_0c;
    FileHandle file = CreateFileA(
        g_package_archive_names[archive_index].c_str(),
        0x80000000u, 1, 0, 3, 0x80, 0);
    if (file == reinterpret_cast<FileHandle>(-1))
        return 0;
    SetFilePointer(file, *entry_offset, 0, 0);
    return file;
}

} // namespace th105
