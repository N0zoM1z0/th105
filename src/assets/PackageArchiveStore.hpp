#pragma once

#include "PackageFileIndexNode.hpp"
#include "engine/CriticalSectionWrapper.hpp"
#include <map>
#include <string>
#include <vector>
#include <stddef.h>

namespace th105 {

typedef std::map<unsigned int, PackageFileIndexNode> PackageEntryMap;
typedef std::vector<std::string> PackageArchiveNames;

// Observed global object at 0x7028DC. The original class name is unknown.
// Construction/destruction establish the critical-section and container owners.
struct PackageArchiveStore {
    PackageArchiveStore();
    ~PackageArchiveStore();

    CriticalSectionWrapper critical_00;
    PackageArchiveNames names_1c;
    PackageEntryMap entries_2c;
    unsigned int count_38;
};

extern PackageArchiveStore g_package_archive_store;

typedef char PackageArchiveStoreSize[sizeof(PackageArchiveStore) == 0x3c ? 1 : -1];
typedef char PackageArchiveNamesOffset[
    offsetof(PackageArchiveStore, names_1c) == 0x1c ? 1 : -1];
typedef char PackageArchiveEntriesOffset[
    offsetof(PackageArchiveStore, entries_2c) == 0x2c ? 1 : -1];
typedef char PackageArchiveCountOffset[
    offsetof(PackageArchiveStore, count_38) == 0x38 ? 1 : -1];

} // namespace th105
