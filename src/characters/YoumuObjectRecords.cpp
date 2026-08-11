#include "YoumuObjectRecords.hpp"

namespace th105 {

unsigned char YoumuObjectRecordState::apply_owner_record(unsigned int index)
{
    YoumuObjectRecord *record =
        owner_348->records_7d0.object_record_ring_at(index);
    if (record->identifier_00 != record_identifier_158) {
        field_150 = record_identifier_158 = record->identifier_00;
        reset_for_new_record();
    }

    unsigned char const phase = record->phase_29;
    if (phase) {
        phase_184 = phase;
        state_180 = 0;
    }

    x_ec = record->x_04;
    y_f0 = record->y_08;
    field_108 = record->field_0c;
    field_10c = record->field_10;
    field_11c = record->field_14;
    field_120 = record->field_18;
    field_124 = record->field_1c;
    field_128 = record->field_20;
    field_12c = record->field_24;
    facing_104 = record->facing_28;
    return phase;
}

} // namespace th105
