#include <stdlib.h>
#include <string.h>
#include <new>
#include <map>
#include "PackageFileIndexNode.hpp"
#include "PackageArchiveStore.hpp"

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


} // namespace th105
