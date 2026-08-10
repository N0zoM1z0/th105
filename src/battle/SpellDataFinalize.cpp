#include "SpellData.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

namespace {

struct CheckedShortIterator {
    ShortDeque8 *owner;
    unsigned absolute;
};

__forceinline short &dereference_checked(CheckedShortIterator *iterator)
{
    ShortDeque8 *owner = iterator->owner;
    const unsigned absolute = iterator->absolute;
    unsigned block = absolute >> 3;
    const unsigned within_block = absolute & 7;
    if (absolute >= owner->live_count_10 + owner->head_0c) {
        _invalid_parameter_noinfo();
    }
    if (owner->block_capacity_08 <= block) {
        block -= owner->block_capacity_08;
    }
    return owner->blocks_04[block][within_block];
}

__forceinline void increment_checked(CheckedShortIterator *iterator)
{
    ShortDeque8 *owner = iterator->owner;
    if (iterator->absolute >= owner->live_count_10 + owner->head_0c) {
        _invalid_parameter_noinfo();
    }
    ++iterator->absolute;
}

} // namespace

void SpellDataOwner::finalize_loaded_spell_data()
{
    unsigned *selected_values =
        reinterpret_cast<unsigned *>(selected_value_by_index_48);
    selected_values[0] = 0;
    selected_values[1] = 0;
    selected_values[2] = 0;
    selected_values[3] = 0;
    selected_values[4] = 0;
    selected_values[5] = 0;
    selected_values[6] = 0;
    selected_values[7] = 0;

    ShortDeque8 *loaded = &loaded_spell_ids_20;
    CheckedShortIterator current = {loaded, loaded->head_0c};
    if (current.absolute > loaded->live_count_10 + current.absolute) {
        _invalid_parameter_noinfo();
    }

    for (;;) {
        CheckedShortIterator finish = {
            loaded,
            loaded->live_count_10 + loaded->head_0c
        };
        if (loaded->head_0c > finish.absolute) {
            _invalid_parameter_noinfo();
        }
        if (current.owner != finish.owner) {
            _invalid_parameter_noinfo();
        }
        if (current.absolute == finish.absolute) {
            return;
        }

        SpellRecordView *record = find_local_then_common_spell_record(
            dereference_checked(&current));
        if (record != 0 && record->selector_1c == 1) {
            selected_value_by_index_48[
                static_cast<unsigned short>(record->value_1e)] =
                static_cast<unsigned char>(dereference_checked(&current));
        }
        increment_checked(&current);
    }
}

} // namespace th105
