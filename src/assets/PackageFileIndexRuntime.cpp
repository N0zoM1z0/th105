#include <stdlib.h>
#include "PackageFileIndexNode.hpp"

namespace th105 {

PackageFileIndexNode::~PackageFileIndexNode()
{
    if (path_00 != 0)
        free(path_00);
    if (next_10 != 0)
        delete next_10;
}

} // namespace th105
