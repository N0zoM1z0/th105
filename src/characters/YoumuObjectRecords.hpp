#pragma once

#include <stddef.h>

namespace th105 {

struct YoumuObjectRecord {
    unsigned int identifier_00;
    float x_04;
    float y_08;
    float field_0c;
    float field_10;
    float field_14;
    float field_18;
    float field_1c;
    float field_20;
    float field_24;
    unsigned char facing_28;
    unsigned char phase_29;
};

struct YoumuObjectRecordRing {
    YoumuObjectRecord *object_record_ring_at(unsigned int index);
};

struct YoumuRecordOwner {
    unsigned char unknown_000[0x7d0];
    YoumuObjectRecordRing records_7d0;
};

struct YoumuObjectRecordState {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_0f4[0x10];
    unsigned char facing_104;
    unsigned char unknown_105[0x03];
    float field_108;
    float field_10c;
    unsigned char unknown_110[0x0c];
    float field_11c;
    float field_120;
    float field_124;
    float field_128;
    float field_12c;
    unsigned char unknown_130[0x20];
    unsigned int field_150;
    unsigned char unknown_154[0x04];
    unsigned int record_identifier_158;
    unsigned char unknown_15c[0x24];
    unsigned int state_180;
    unsigned char phase_184;
    unsigned char unknown_185[0x1c3];
    YoumuRecordOwner *owner_348;

    void reset_for_new_record();
    unsigned char apply_owner_record(unsigned int index);
};

typedef char CheckYoumuObjectRecordPhaseOffset[
    offsetof(YoumuObjectRecord, phase_29) == 0x29 ? 1 : -1];
typedef char CheckYoumuObjectRecordIdentifierOffset[
    offsetof(YoumuObjectRecordState, record_identifier_158) == 0x158 ? 1 : -1];
typedef char CheckYoumuObjectRecordStateOffset[
    offsetof(YoumuObjectRecordState, state_180) == 0x180 ? 1 : -1];
typedef char CheckYoumuObjectRecordOwnerOffset[
    offsetof(YoumuObjectRecordState, owner_348) == 0x348 ? 1 : -1];

} // namespace th105
