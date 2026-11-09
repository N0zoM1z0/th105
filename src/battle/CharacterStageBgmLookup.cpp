#include "CharacterPolicyMaps.hpp"

namespace th105 {
unsigned char __cdecl get_stage_for_character(int character_key)
{
    return g_bootstrap_stages.find(character_key)->second;
}

unsigned char __cdecl get_bgm_for_character(int character_key)
{
    return g_bootstrap_bgms.find(character_key)->second;
}
} // namespace th105
