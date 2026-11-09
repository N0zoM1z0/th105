#include "EventEffectRecords.hpp"

namespace th105 {
int __cdecl lookup_event_effect_record(int event_id)
{
    return g_bootstrap_effect_frames.find(event_id)->second;
}
} // namespace th105
