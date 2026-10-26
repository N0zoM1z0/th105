#pragma once

#include <map>
#include <set>
#include <vector>

namespace th105 {

// Exact native field widths; original nominal record/class names are unknown.
struct ScoreDefaultRecord24 {
    int key_00, difficulty_04, key_08;
    int sequence_result_count_0c, update_count_10, maximum_observed_14;
    ScoreDefaultRecord24() : sequence_result_count_0c(0), update_count_10(0), maximum_observed_14(0) {}
};
// Bounded view;43E1A0 constructs20 map slots and20 record-vector slots.
// Original nominal type and full owner layout remain unknown.
struct ScoreDataDefaultsView {
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
    void initialize_defaults_42ed70();
    bool load_42f6f0();
    void refresh_story_progress_42e3f0();
};
} // namespace th105
