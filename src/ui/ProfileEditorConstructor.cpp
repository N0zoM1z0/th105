#include "ProfileMenu.hpp"
#include <stddef.h>

namespace th105 {

ProfileEditor168::ProfileEditor168()
    : texture_primary_000(0),
      texture_secondary_004(0)
{
}

typedef char ProfileEditorCTileSize[sizeof(CTile) == 0xa4 ? 1 : -1];
typedef char ProfileEditor168Size[sizeof(ProfileEditor168) == 0x168 ? 1 : -1];
typedef char ProfileEditorPrimaryTileOffset[
    offsetof(ProfileEditor168, primary_tile_00c) == 0x0c ? 1 : -1];
typedef char ProfileEditorSecondaryTileOffset[
    offsetof(ProfileEditor168, secondary_tile_0b0) == 0xb0 ? 1 : -1];

} // namespace th105
