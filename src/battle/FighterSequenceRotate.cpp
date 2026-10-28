#include <deque>
#include "battle/EffectSprite.hpp"

namespace th105 {

// Runtime-layout view of the real polymorphic sprite copied by 455160.
// Typed scalar members preserve its lifetime and GS classification; this is
// not a byte buffer pretending to own a constructed sprite.
struct SequenceRotateSprite94 : CSpriteBase {
    SequenceRotateSprite94(const SequenceRotateSprite94 &);
    float pivot_x, pivot_y, scale_x, scale_y, angle;
};

struct SequenceRotateCard {
    short record_id;
    unsigned short field_02;
    SequenceRotateSprite94 sprite;
};

typedef char sequence_sprite_extent[
    sizeof(SequenceRotateSprite94) == 0x94 ? 1 : -1];
typedef char sequence_card_extent[
    sizeof(SequenceRotateCard) == 0x98 ? 1 : -1];
typedef char sequence_deque_extent[
    sizeof(std::deque<SequenceRotateCard>) == 0x14 ? 1 : -1];

// Complete nonexact candidate. The genuine VC8 deque and nontrivial temporary
// reproduce the native checked-front/pop/push and generated cleanup structure.
unsigned char Fighter::rotate_front_spell_sequence_entry_to_back()
{
    unsigned count = sequence_controller_55c.live_count_10;
    if (count > 0) {
        std::deque<SequenceRotateCard> &cards =
            *reinterpret_cast<std::deque<SequenceRotateCard> *>(
                &sequence_controller_55c);
        SequenceRotateCard card = cards.front();
        cards.pop_front();
        cards.push_back(card);
        count = sequence_controller_55c.live_count_10;
        state_55a = static_cast<signed char>(count);
    }
    return static_cast<unsigned char>(count);
}

} // namespace th105
