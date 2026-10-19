#include "PackageFileIndexNode.cpp"

namespace th105 {

unsigned int __cdecl case_insensitive_crc32(const unsigned char *, int);

// @41BCF0: the three temporary owners survive through insert().
void __stdcall register_package_file_entry(
    const char *path, unsigned int archive_index,
    unsigned int size, unsigned int offset)
{
    unsigned int hash = case_insensitive_crc32(
        reinterpret_cast<const unsigned char *>(path),
        static_cast<int>(strlen(path)));
    PackageEntryMap::iterator entry = g_package_archive_store.entries_2c.find(hash);
    if (entry == g_package_archive_store.entries_2c.end()) {
        g_package_archive_store.entries_2c.insert(std::pair<unsigned int, PackageFileIndexNode>(
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
