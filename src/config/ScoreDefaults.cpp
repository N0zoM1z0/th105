#include "ui/ProfileMenuBaseDataLifetime.hpp"
#include "ui/ProfileDeckResourceLifetime.hpp"
#include "battle/SpellData.hpp"
#include "assets/CsvReader.hpp"
#include <map>
#include <set>
#include <vector>
#include <cstring>
#include <stddef.h>
namespace th105 {
extern SpellTree g_common_spell_tree;
const char *__cdecl character_key_to_name(int);
int __cdecl resolve_scenario_event_name(String28);
// Exact native field widths; original nominal record/class names are unknown.
struct ScoreDefaultRecord24 {
    int key_00, difficulty_04, key_08;
    int sequence_result_count_0c, update_count_10, maximum_observed_14;
    ScoreDefaultRecord24() : sequence_result_count_0c(0), update_count_10(0), maximum_observed_14(0) {}
};
// Bounded view of the fields used by42ED70, not a complete ScoreData class.
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
    std::map<int, int> character_counts_a8[15];
    unsigned char unknown_15c[0x3c];
    std::vector<ScoreDefaultRecord24> records_198[15];
    void initialize_defaults_42ed70();
    void refresh_story_progress_42e3f0();
};
void ScoreDataDefaultsView::initialize_defaults_42ed70()
{
    ProfileMenuBaseDataLifetime defaults;
    defaults.initialize_defaults();
    std::memset(event_columns_08, 0, sizeof(event_columns_08));
    std::memset(primary_available_1c, 0, sizeof(primary_available_1c));
    std::memset(secondary_available_30, 0, sizeof(secondary_available_30));
    available_items_50.clear();
    music_paths_44.clear();
    auxiliary_indices_7c.erase(auxiliary_indices_7c.begin(), auxiliary_indices_7c.end());
    auxiliary_indices_8c.erase(auxiliary_indices_8c.begin(), auxiliary_indices_8c.end());
    ProfileDeckResourceGroupNative20 resources;
    typedef std::map<int, SpellRecordView> SpellMap;
    SpellMap &common = reinterpret_cast<SpellMap &>(g_common_spell_tree);
    for (SpellMap::iterator it = common.begin(); it != common.end(); ++it)
        common_counts_9c.insert(std::pair<int, int>(it->first, 0));
    for (int character = 0; character < 15; ++character) {
        character_counts_a8[character].clear();
        reinterpret_cast<SpellDataOwner *>(&resources)->load_spell_csv_via_32e20(character, 0, 0);
        for (SpellMap::iterator it = resources.tree_14.begin(); it != resources.tree_14.end(); ++it)
            character_counts_a8[character].insert(std::pair<int, int>(it->first, 0));
        reinterpret_cast<SpellDataOwner *>(&resources)->clear_spell_entries();
        std::deque<short> deck;
        defaults.load_character_deck(&deck, character);
        for (unsigned index = 0; index < deck.size(); ++index) {
            std::map<int, int>::iterator count = character_counts_a8[character].find(deck[index]);
            if (count != character_counts_a8[character].end()) {
                ++count->second;
            } else {
                count = common_counts_9c.find(deck[index]);
                if (count != common_counts_9c.end())
                    count->second = count->second > 4 ? count->second : 4;
            }
        }
        records_198[character].clear();
        ScoreDefaultRecord24 record;
        struct OwningCsvReader : CsvReader {
            OwningCsvReader() {
                row_map_04 = 0; row_map_capacity_08 = 0; row_start_0c = 0; row_count_10 = 0;
                outer_iterator_aux_14 = 0; outer_iterator_owner_18 = 0; outer_row_position_1c = 0;
                inner_iterator_aux_20 = 0; current_row_24 = 0; current_field_position_28 = 0;
            }
        } reader;
        String28 path("data/csv/");
        path.append(character_key_to_name(character));
        path.append("/story.csv", 10);
        reader.load(path.c_str());
        int groups = reader.next_int();
        reader.advance_row();
        for (int group = 0; group < groups; ++group) {
            reader.next_int();
            String28 name;
            reader.next_string(&name);
            record.key_00 = resolve_scenario_event_name(name);
            int rows = reader.next_int();
            reader.advance_row();
            for (int row = 0; row < rows; ++row) {
                for (int difficulty = 0; difficulty < 4; ++difficulty) {
                    record.key_08 = reader.next_int();
                    record.difficulty_04 = difficulty;
                    if (record.key_08 < 200) {
                        bool found = false;
                        unsigned index = 0;
                        for (; index < records_198[character].size(); ++index) {
                            if (record.key_00 == records_198[character][index].key_00 &&
                                record.key_08 == records_198[character][index].key_08)
                            {
                                found = true;
                                break;
                            }
                        }
                        if (!found)
                            records_198[character].push_back(record);
                    }
                }
                reader.advance_row();
            }
        }
    }
    primary_available_1c[0] = 1;
    primary_available_1c[1] = 1;
    primary_available_1c[2] = 1;
    std::memset(secondary_available_30, 1, 13);
    available_items_50.insert(10);
    available_items_50.insert(11);
    flags_04 = 0;
    refresh_story_progress_42e3f0();
    initialized_00 = 1;
}
typedef char ScoreDefaults_profile_size[sizeof(ProfileMenuBaseDataLifetime) == 0x33c ? 1 : -1];
typedef char ScoreDefaults_resources_size[sizeof(ProfileDeckResourceGroupNative20) == 0x20 ? 1 : -1];
typedef char ScoreDefaults_record_size[sizeof(ScoreDefaultRecord24) == 0x18 ? 1 : -1];
typedef char ScoreDefaults_common_offset[offsetof(ScoreDataDefaultsView, common_counts_9c) == 0x9c ? 1 : -1];
typedef char ScoreDefaults_character_offset[offsetof(ScoreDataDefaultsView, character_counts_a8) == 0xa8 ? 1 : -1];
typedef char ScoreDefaults_records_offset[offsetof(ScoreDataDefaultsView, records_198) == 0x198 ? 1 : -1];
}
