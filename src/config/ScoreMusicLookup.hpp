#pragma once

#include <set>
#include <stddef.h>

namespace th105 {

// Existing score storage view shared by music publication and both consumers.
// The native checked set at +0x44 belongs to ScoreData's recovered prefix.
struct ScoreMusicLookupView {
    unsigned char unknown_000[0x44];
    std::set<unsigned> path_hashes_044;

    bool contains_bgm_path(const char *path);
    void publish_bgm_path(const char *path);
};

typedef char ScoreMusicLookup_paths_offset[
    offsetof(ScoreMusicLookupView, path_hashes_044) == 0x44 ? 1 : -1];

} // namespace th105
