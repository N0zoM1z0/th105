#include <map>

namespace th105 {

typedef std::map<char, int> EventEffectRecordMap;
extern EventEffectRecordMap g_event_effect_records;

int __cdecl lookup_event_effect_record(char event_id)
{
    return g_event_effect_records.find(event_id)->second;
}

} // namespace th105
