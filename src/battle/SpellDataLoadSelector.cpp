#include "SpellData.hpp"

namespace th105 {

unsigned char SpellDataOwner::load_spell_data(
    int character_key,
    int arg2,
    unsigned char alternate_loader)
{
    if (alternate_loader != 0) {
        if (load_spell_csv_via_32e20(character_key, arg2, 1) == 0) {
            return 0;
        }
    } else if (load_spell_csv_via_325b0(
                   character_key, arg2, load_destination_20) == 0) {
        return 0;
    }
    finalize_loaded_spell_data();
    return 1;
}

} // namespace th105
