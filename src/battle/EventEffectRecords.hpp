#pragma once

#include <map>

namespace th105 {
typedef std::map<int, int> EventEffectRecordMap;
extern EventEffectRecordMap g_bootstrap_effect_frames;

int __cdecl lookup_event_effect_record(int event_id);
} // namespace th105
