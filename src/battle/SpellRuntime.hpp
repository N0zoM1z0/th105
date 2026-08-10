#pragma once

#include "SpellData.hpp"

namespace th105 {

struct FighterSequenceSlot {
    short record_id_00;
    unsigned short field_02;
    unsigned char sprite_04[0x94];
};

struct SequenceRecord4 {
    short record_id_00;
    short record_word_02;
};

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

} // namespace th105
