#include "PostSequenceTransition.hpp"

#include <map>

namespace th105 {


typedef std::map<unsigned int, unsigned short> InfoEffectLookupMap;
extern InfoEffectLookupMap g_info_effect_lookup_map;
unsigned int __cdecl current_info_effect_key_43bb90();

int PostSequenceTransitionView::publish_transition_effect_46e040(int effect_id)
{
    return emitter_04.emit(effect_id, 320.0f, 240.0f, 1, 0, 0);
}

void PostSequenceTransitionView::publish_transition_effect_at_46e130(float position)
{
    unsigned int key = current_info_effect_key_43bb90();
    InfoEffectLookupMap::iterator it = g_info_effect_lookup_map.find(key);
    if (it != g_info_effect_lookup_map.end()) {
        emitter_04.emit(
            it->second,
            2000.0f, position, 1, 0, 0);
    }
}

} // namespace th105
