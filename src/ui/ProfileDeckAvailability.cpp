#include "ProfileDeckEdit.hpp"
#include "config/ScoreData.hpp"
#include <map>
#include <algorithm>
namespace th105 {
typedef std::map<int, SpellRecordView> SpellMap;
typedef std::deque<SpellMap::iterator> SpellIteratorDeque;
typedef std::map<int, int> ScoreCountMap;
int CProfileDeckEdit::available_count_for_index_448df0(int index)
{
    SpellMap::iterator &spell =
        reinterpret_cast<SpellIteratorDeque &>(filtered_3cc)[index];
    ScoreCountMap::iterator found;
    found = get_score_data()
                ->character_counts_a8[character_08].find(spell->first);
    if (found != get_score_data()
                     ->character_counts_a8[character_08].end()) {
        return found->second < 99 ? found->second : 99;
    }
    SpellMap::iterator &fallback_spell =
        reinterpret_cast<SpellIteratorDeque &>(filtered_3cc)[index];
    ScoreCountMap::iterator fallback;
    fallback = get_score_data()
                   ->common_counts_9c.find(fallback_spell->first);
    if (fallback != get_score_data()
                        ->common_counts_9c.end())
        return fallback->second < 99 ? fallback->second : 99;
    return 0;
}
}
