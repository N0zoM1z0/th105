#include "SpellData.hpp"

namespace th105 {

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *destination,
    const char *format,
    ...);
const char *__cdecl character_key_to_name(int character_key);

unsigned char SpellDataOwner::load_spell_csv_via_325b0(
    int character_key,
    signed char story_mode,
    void *mode_argument)
{
    char path[260];
    clear_spell_entries();
    if (story_mode) {
        wsprintfA(
            path,
            "data/csv/%s/storySpell.csv",
            character_key_to_name(character_key));
    } else {
        wsprintfA(
            path,
            "data/csv/%s/spellcard.csv",
            character_key_to_name(character_key));
    }
    parse_spell_csv_via_325b0(
        character_key_to_name(character_key),
        path,
        &image_handles_00,
        &local_tree_14,
        mode_argument);
    return 1;
}

unsigned char SpellDataOwner::load_spell_csv_via_32e20(
    int character_key,
    signed char story_mode,
    unsigned char use_owner)
{
    char path[260];
    clear_spell_entries();
    if (story_mode) {
        wsprintfA(
            path,
            "data/csv/%s/storySpell.csv",
            character_key_to_name(character_key));
    } else {
        wsprintfA(
            path,
            "data/csv/%s/spellcard.csv",
            character_key_to_name(character_key));
    }
    if (use_owner) {
        parse_spell_csv_and_build_card_resources(
            character_key_to_name(character_key),
            path,
            &image_handles_00,
            &local_tree_14);
    } else {
        parse_spell_csv_and_build_card_resources(
            character_key_to_name(character_key),
            path,
            0,
            &local_tree_14);
    }
    return 1;
}

} // namespace th105
