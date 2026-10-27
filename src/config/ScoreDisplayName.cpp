#include "ScoreDataDefaults.hpp"
#include "ui/ProfileDeckResourceLifetime.hpp"
#include <deque>
#include <string>

namespace th105 {
int __cdecl selector_random_roll(int limit);

// Bounded existing ScoreData storage view, never instantiated here.
struct ScoreDisplayView : ScoreDataDefaultsView {
    bool select_story_display_name(int character_key, std::string *output);
};

bool ScoreDisplayView::select_story_display_name(int character_key, std::string *output)
{
    unsigned roll = selector_random_roll(10);
    int selected;
    if (roll == 0)
        selected = 15;
    else if (roll < 5)
        selected = secondary_indices_6c[selector_random_roll(secondary_indices_6c.size())];
    else
        selected = character_key;
    roll = selector_random_roll(10);
    signed char category;
    if (roll == 0)
        category = 2;
    else
        category = roll < 4;
    std::deque<int> choices;
    ProfileDeckResourceGroupNative20 resources;
    typedef std::map<int, SpellRecordView> SpellMap;
    SpellMap::iterator it;
    std::map<int, int>::iterator count;
    if (selected == 15) {
        SpellMap &common = reinterpret_cast<SpellMap &>(g_common_spell_tree);
        for (it = common.begin(); it != common.end(); ++it)
            if (it->second.value_3e == category)
                choices.push_back(it->first);
        if (choices.empty())
            return false;
        unsigned key = choices[selector_random_roll(choices.size())];
        *output = reinterpret_cast<SpellDataOwner *>(&resources)->find_local_then_common_spell_record(key)->name_00;
        count = common_counts_9c.find(key);
        if (count == common_counts_9c.end())
            common_counts_9c.insert(std::pair<int, int>(key, 0));
        if (common_counts_9c.find(key)->second++ == 0)
            output->append("<color FF8080> new</color>", 26);
    } else {
        reinterpret_cast<SpellDataOwner *>(&resources)->load_spell_csv_via_32e20(selected, 0, 0);
        for (it = resources.tree_14.begin(); it != resources.tree_14.end(); ++it)
            if (it->second.value_3e == category)
                choices.push_back(it->first);
        if (choices.empty())
            return false;
        unsigned key = choices[selector_random_roll(choices.size())];
        *output = reinterpret_cast<SpellDataOwner *>(&resources)->find_local_then_common_spell_record(key)->name_00;
        count = character_counts_a8[selected].find(key);
        if (count == character_counts_a8[selected].end())
            character_counts_a8[selected].insert(std::pair<int, int>(key, 0));
        if (character_counts_a8[selected].find(key)->second++ == 0)
            output->append("<color FF8080> new</color>", 26);
        reinterpret_cast<SpellDataOwner *>(&resources)->clear_spell_entries();
    }
    return true;
}
} // namespace th105
