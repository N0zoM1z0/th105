#include "ProfileDeckEdit.hpp"
#include "config/ScoreData.hpp"
#include <map>
#include <algorithm>
namespace th105 {
typedef std::map<int, SpellRecordView> SpellMap;
struct SpellIteratorDequeAtView { SpellMap::iterator &at(unsigned index); };
typedef std::map<int, int> ScoreCountMap;
struct ScoreDeckAvailabilityView {
    unsigned char reserved_000[0x9c];
    ScoreCountMap common_09c;
    ScoreCountMap per_character_0a8[15];
};
int CProfileDeckEdit::available_count_for_index_448df0(int index)
{
    SpellMap::iterator &spell =
        reinterpret_cast<SpellIteratorDequeAtView *>(&filtered_3cc)->at(index);
    ScoreCountMap::iterator found;
    found = reinterpret_cast<ScoreDeckAvailabilityView *>(get_score_data())
                ->per_character_0a8[character_08].find(spell->first);
    if (found != reinterpret_cast<ScoreDeckAvailabilityView *>(get_score_data())
                     ->per_character_0a8[character_08].end()) {
        return found->second < 99 ? found->second : 99;
    }
    SpellMap::iterator &fallback_spell =
        reinterpret_cast<SpellIteratorDequeAtView *>(&filtered_3cc)->at(index);
    ScoreCountMap::iterator fallback;
    fallback = reinterpret_cast<ScoreDeckAvailabilityView *>(get_score_data())
                   ->common_09c.find(fallback_spell->first);
    if (fallback != reinterpret_cast<ScoreDeckAvailabilityView *>(get_score_data())
                        ->common_09c.end())
        return fallback->second < 99 ? fallback->second : 99;
    return 0;
}
}
