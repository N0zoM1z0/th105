// Original ScoreData owned-prefix lifetime; constructor306 is canonical exact.
// The destructor is implicit and compiler-owned, not an authored definition.
// See docs/SCORE_OWNER_LIFETIME_2026_11_01.md.
#include "config/ScoreDataDefaults.hpp"
#include <stddef.h>
namespace th105 {
struct ScoreDataLifetimeView {
    unsigned char initialized_00;
    unsigned char unknown_01[3];
    unsigned flags_04;
    unsigned char event_columns_08[20];
    unsigned char primary_available_1c[20];
    unsigned char secondary_available_30[20];
    std::set<unsigned> music_paths_44;
    std::set<unsigned> available_items_50;
    std::vector<int> primary_indices_5c;
    std::vector<int> secondary_indices_6c;
    std::vector<int> auxiliary_indices_7c;
    std::vector<int> auxiliary_indices_8c;
    std::map<int, int> common_counts_9c;
    std::map<int, int> character_counts_a8[20];
    std::vector<ScoreDefaultRecord24> records_198[20];
    ScoreDataLifetimeView();
};

typedef char ScoreLifetimeSize[sizeof(ScoreDataLifetimeView)==0x2d8?1:-1];
typedef char ScoreLifetimeSets[offsetof(ScoreDataLifetimeView,music_paths_44)==0x44?1:-1];
typedef char ScoreLifetimeCounts[offsetof(ScoreDataLifetimeView,common_counts_9c)==0x9c?1:-1];
typedef char ScoreLifetimeMaps[offsetof(ScoreDataLifetimeView,character_counts_a8)==0xa8?1:-1];
typedef char ScoreLifetimeRecords[offsetof(ScoreDataLifetimeView,records_198)==0x198?1:-1];
ScoreDataLifetimeView::ScoreDataLifetimeView()
{
    initialized_00 = 0;
}
// The target has this actual static lifetime. Normal global construction emits
// its implicit destructor and registration callback; no fake destructor body.
ScoreDataLifetimeView g_score_lifetime;
}
