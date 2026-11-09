#pragma once

#include <map>

namespace th105 {
typedef std::map<int, unsigned char> CharacterPolicyMap;
extern CharacterPolicyMap g_bootstrap_stages;
extern CharacterPolicyMap g_bootstrap_bgms;

unsigned char __cdecl get_stage_for_character(int character_key);
unsigned char __cdecl get_bgm_for_character(int character_key);
} // namespace th105
