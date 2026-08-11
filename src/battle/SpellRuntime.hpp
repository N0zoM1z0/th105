#pragma once

#include "SpellData.hpp"

namespace th105 {

struct PlayerIndexedCallbackView {
    void invoke_indexed_record(int record_id, int zero);
};

struct SpellSpriteWork {
    void *vtable_00;
    unsigned char unknown_04[0x90];

    void load_optional_spell_resource(
        void *resource,
        int zero0,
        int zero1,
        void *global_a,
        void *global_b);
};

struct FighterSequenceSlot {
    short record_id_00;
    unsigned short field_02;
    SpellSpriteWork sprite_04;
};

typedef char FighterSequenceSlot_size_must_be_0x98[
    sizeof(FighterSequenceSlot) == 0x98 ? 1 : -1];

} // namespace th105
