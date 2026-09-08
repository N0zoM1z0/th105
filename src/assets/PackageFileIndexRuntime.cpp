#include <stdlib.h>

namespace th105 {

struct PackageFileIndexNode {
    char *path_00;
    unsigned int offset_04;
    unsigned int size_08;
    unsigned int key_0c;
    PackageFileIndexNode *next_10;

    ~PackageFileIndexNode();
};

PackageFileIndexNode::~PackageFileIndexNode()
{
    if (path_00 != 0)
        free(path_00);
    if (next_10 != 0)
        delete next_10;
}

typedef char PackageFileIndexNodeSize[
    sizeof(PackageFileIndexNode) == 0x14 ? 1 : -1];

} // namespace th105
