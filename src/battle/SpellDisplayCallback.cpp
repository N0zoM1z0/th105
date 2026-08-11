#include "SpellRuntime.hpp"

namespace th105 {

void PlayerIndexedCallbackView::invoke_indexed_record(
    int record_id,
    int source_token)
{
    if (source_token == 0) {
        active_14c = 0;
        return;
    }

    angle_start_134 = 0.0f;
    angle_end_138 = 360.0f;
    source_12c = 0;
    angle_step_13c = 12.0f;
    color_130 = 15;
    intensity_131 = 5;
    height_scale_144 = 7.0f;
    width_scale_140 = 21.0f;

    SpellRecordView *record =
        spell_data_00->find_local_then_common_spell_record(record_id);
    int name_length = record->name_00.size();
    int width = name_length * 8;
    if (width >= 272)
        width = 272;

    if (!alternate_alignment_132) {
        display_sprite_098.configure_record_display(
            record->batch_resource_40,
            0,
            record->value_48,
            width,
            16,
            10,
            9);
    } else {
        display_sprite_098.configure_record_display(
            record->batch_resource_40,
            0,
            record->value_48,
            width,
            16,
            name_length * 7 - 10,
            9);
    }
    active_14c = 1;
    source_token_150 = source_token;
}

} // namespace th105
