#include "PackageArchiveStore.hpp"

namespace th105 {

PackageArchiveStore g_package_archive_store;

PackageArchiveStore::PackageArchiveStore() : count_38(0)
{
}

PackageArchiveStore::~PackageArchiveStore()
{
    // The target clears both containers and count before member destruction.
    names_1c.clear();
    entries_2c.clear();
    count_38 = 0;
}

} // namespace th105
