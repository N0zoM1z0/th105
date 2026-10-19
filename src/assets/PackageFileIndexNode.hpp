#pragma once

namespace th105 {

// Current 1.06a package lookup @41BFA0 fixes the three scalar roles.
struct PackageFileIndexNode {
    char *path_00;
    unsigned int archive_index_04;
    unsigned int size_08;
    unsigned int offset_0c;
    PackageFileIndexNode *next_10;

    PackageFileIndexNode(const char *path, unsigned int archive_index,
                         unsigned int size, unsigned int offset);
    PackageFileIndexNode(const PackageFileIndexNode &other);
    ~PackageFileIndexNode();
};

typedef char PackageFileIndexNodeSize[
    sizeof(PackageFileIndexNode) == 0x14 ? 1 : -1];

} // namespace th105
