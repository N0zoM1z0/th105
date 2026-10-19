#include <stdlib.h>
#include <string.h>
#include <new>
#include <map>
#include "PackageFileIndexNode.hpp"

namespace th105 {

PackageFileIndexNode::PackageFileIndexNode(
    const char *path, unsigned int archive_index,
    unsigned int size, unsigned int offset)
{
    size_t length = strlen(path) + 1;
    path_00 = new char[length];
    strcpy_s(path_00, length, path);
    archive_index_04 = archive_index;
    size_08 = size;
    offset_0c = offset;
    next_10 = 0;
}

PackageFileIndexNode::PackageFileIndexNode(const PackageFileIndexNode &other)
{
    size_t length = strlen(other.path_00) + 1;
    path_00 = new char[length];
    strcpy_s(path_00, length, other.path_00);
    archive_index_04 = other.archive_index_04;
    size_08 = other.size_08;
    offset_0c = other.offset_0c;
    next_10 = other.next_10;
}

PackageFileIndexNode::~PackageFileIndexNode()
{
    if (path_00 != 0)
        free(path_00);
    if (next_10 != 0)
        delete next_10;
}

typedef std::map<unsigned int, PackageFileIndexNode> PackageEntryMap;
extern PackageEntryMap g_package_entry_map;
unsigned int __cdecl case_insensitive_crc32(const unsigned char *, int);

// @41BCF0: the three temporary owners survive through insert().
void __stdcall register_package_file_entry(
    const char *path, unsigned int archive_index,
    unsigned int size, unsigned int offset)
{
    unsigned int hash = case_insensitive_crc32(
        reinterpret_cast<const unsigned char *>(path),
        static_cast<int>(strlen(path)));
    PackageEntryMap::iterator entry = g_package_entry_map.find(hash);
    if (entry == g_package_entry_map.end()) {
        g_package_entry_map.insert(std::pair<unsigned int, PackageFileIndexNode>(
            hash, PackageFileIndexNode(path, archive_index, size, offset)));
        return;
    }

    PackageFileIndexNode *node = &entry->second;
    while (_stricmp(node->path_00, path) != 0) {
        if (node->next_10 == 0) {
            node->next_10 = new PackageFileIndexNode(
                path, archive_index, size, offset);
            return;
        }
        node = node->next_10;
    }
    node->archive_index_04 = archive_index;
    node->size_08 = size;
    node->offset_0c = offset;
}

} // namespace th105
