#pragma once

// Native4519E0 compares unsigned start_04, retaining equivalent timestamps.
// The old map<int,20-byte-value> view reproduced layout but not ordering.
// See docs/SCENE_TIMELINE_ORDERING_2026_10_29.md.
#include <set>

namespace th105 {
struct SceneInterpolationEntry24 {
    int object_id_00;
    unsigned int start_04;
    unsigned int end_08;
    union {
        unsigned int uint_0c;
        float float_0c;
        unsigned char byte_0c;
    } target;
    int easing_10;
    int type_14;
};

struct SceneTimelineStartLess {
    bool operator()(const SceneInterpolationEntry24 &a,
                    const SceneInterpolationEntry24 &b) const
    { return a.start_04 < b.start_04; }
};
typedef std::multiset<SceneInterpolationEntry24,SceneTimelineStartLess> SceneTimelineEntries;

typedef char SceneTimelineEntrySize[sizeof(SceneInterpolationEntry24)==0x18?1:-1];
}
