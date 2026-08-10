#include "SpellData.hpp"

namespace th105 {

extern "C" int __cdecl wsprintfA(
    char *destination,
    const char *format,
    ...);
const char *__cdecl character_key_to_name(int character_key);

unsigned char SpellDataOwner::load_spell_csv_via_325b0(
    int character_key,
    int,
    void *mode_argument)
{
    char path[260];
    clear_spell_entries();
    const char *character_name = character_key_to_name(character_key);
    const char *format =
        static_cast<unsigned char>(
            reinterpret_cast<unsigned long>(mode_argument)) == 0 ?
        "data/csv/%s/spellcard.csv" :
        "data/csv/%s/storySpell.csv";
    wsprintfA(path, format, character_name);
    parse_spell_csv_via_325b0(
        character_name,
        path,
        this,
        &local_tree_14,
        mode_argument);
    return 1;
}

unsigned char SpellDataOwner::load_spell_csv_via_32e20(
    int character_key,
    int,
    unsigned char use_owner)
{
    char path[260];
    clear_spell_entries();
    const char *character_name = character_key_to_name(character_key);
    const char *format = use_owner == 0 ?
        "data/csv/%s/spellcard.csv" :
        "data/csv/%s/storySpell.csv";
    wsprintfA(path, format, character_name);
    parse_spell_csv_and_build_card_resources(
        character_name,
        path,
        use_owner == 0 ? 0 : this,
        &local_tree_14);
    return 1;
}

} // namespace th105
