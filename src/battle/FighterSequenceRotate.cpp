#include <deque>
#include "battle/EffectSprite.hpp"
#include "ui/CNumberLifetime.hpp"

namespace th105 {

// Runtime-layout view of the real polymorphic sprite copied by 455160.
// Typed scalar members preserve its lifetime and GS classification; this is
// not a byte buffer pretending to own a constructed sprite.
// IColor is the four-byte interface base. The texture belongs to CSpriteBase,
// so its copy occurs after that derived base's ordinary vptr publication.
struct SequenceRotateSpriteBase80 : CNumberColorLifetime {
    SequenceRotateSpriteBase80() : texture_04(0) {}
    virtual ~SequenceRotateSpriteBase80() {}
    virtual void set_color(unsigned);
    virtual void set_vertex_colors(const unsigned *);
    virtual void multiply_color(unsigned);
    unsigned texture_04;
    SpriteVertex28 vertices_08[4];
    float width_78, height_7c;
};
struct SequenceRotateSprite94 : SequenceRotateSpriteBase80 {
    // The original116-byte copy is an ordinary implicit copy of the actual
    // polymorphic base, vertex array and five scalar extension fields.
    virtual void set_texture_options(unsigned, int, int, unsigned, unsigned, int, int);
    virtual void set_texture(unsigned, int, int, int, int);
    virtual void render_rectangle(float, float, float, float);
    virtual void render(float, float);
    virtual void render_plain(float, float);
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

// Complete canonical-exact rotation. The genuine VC8 deque and nontrivial temporary
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
        unsigned char updated_count = static_cast<unsigned char>(
            sequence_controller_55c.live_count_10);
        state_55a = static_cast<signed char>(updated_count);
        return updated_count;
    }
    return static_cast<unsigned char>(count);
}

} // namespace th105
