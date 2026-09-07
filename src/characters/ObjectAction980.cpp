#include "battle/EffectSprite.hpp"
#include "characters/AnimationSequenceVirtuals.hpp"
#include "characters/CharacterObjectRuntime.hpp"

#include <stddef.h>

namespace th105 {

int __cdecl selector_random_roll(int limit);

struct ObjectAction980OwnerView {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
};

class ObjectAction980View {
public:
    virtual void scalar_delete_slot_00();
    virtual int set_action_sequence_and_finalize(short action, int sequence);
    virtual int set_action_and_finalize(short action);
    virtual int select_sequence(int sequence);
    virtual int reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual int previous_sequence_block();
    virtual int set_sequence_frame(short frame);
    virtual unsigned char next_sequence_frame();
    virtual int previous_sequence_frame();
    virtual void update_slot_28();
    virtual void render_main();
    virtual void render_to_battle_scene();
    virtual void prepare_render_transform();
    virtual void render_color_mode();
    virtual void initialize_action_entry();

    void continue_action_980();

    CEffectSprite sprite_004;
    unsigned char unknown_130[0x0c];
    short action_id_13c;
    short sequence_index_13e;
    unsigned char unknown_140[0x200];
    float *heading_340;
    unsigned char unknown_344[0x04];
    ObjectAction980OwnerView *fighter_owner_348;
    unsigned char unknown_34c[0x18];
    short state_364;
    short state_366;
    unsigned char unknown_368[0x08];
    float state_370;
    float state_374;

    CharacterObjectRuntime *motion_core()
    {
        return reinterpret_cast<CharacterObjectRuntime *>(
            reinterpret_cast<unsigned char *>(this) + 4);
    }

    float &velocity_y_f8()
    {
        return *reinterpret_cast<float *>(
            reinterpret_cast<unsigned char *>(this) + 0xf8);
    }
};

typedef char ObjectAction980_sequence_offset[
    offsetof(ObjectAction980View, sequence_index_13e) == 0x13e ? 1 : -1];
typedef char ObjectAction980_heading_offset[
    offsetof(ObjectAction980View, heading_340) == 0x340 ? 1 : -1];
typedef char ObjectAction980_owner_offset[
    offsetof(ObjectAction980View, fighter_owner_348) == 0x348 ? 1 : -1];
typedef char ObjectAction980_state_offset[
    offsetof(ObjectAction980View, state_370) == 0x370 ? 1 : -1];

__forceinline static float unsigned_random_as_float(int limit)
{
    return static_cast<float>(
        static_cast<unsigned int>(selector_random_roll(limit)));
}

void ObjectAction980View::continue_action_980()
{
    if (heading_340[2] > 0.0f)
        select_sequence(static_cast<int>(heading_340[2]));

    if (sequence_index_13e == 0) {
        state_370 = unsigned_random_as_float(360);
        float const scaled_random = unsigned_random_as_float(10) * 0.01f;
        state_374 = scaled_random + 2.0f;

        ObjectAction980OwnerView *const owner = fighter_owner_348;
        state_364 = static_cast<short>(
            static_cast<int>(sprite_004.object_x_0e8 - owner->x_ec));
        state_366 = static_cast<short>(
            static_cast<int>(sprite_004.object_y_0ec - owner->y_f0));
    }

    if (sequence_index_13e == 1) {
        motion_core()->set_oriented_components_f0_f4(
            heading_340[0], heading_340[1]);
        velocity_y_f8() = 1.0f;
        float const scale =
            unsigned_random_as_float(5) * 0.01f + 0.2f;
        reinterpret_cast<unsigned char *>(this)[0x113] = 0;
        sprite_004.reset_one_118 = scale;
        sprite_004.reset_one_11c = scale;
        state_370 = 0.0f;
    }
}

} // namespace th105
