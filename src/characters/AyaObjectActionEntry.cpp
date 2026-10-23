#include "characters/AyaObjectActionView.hpp"
#include "engine/AngleAtan2.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);
unsigned int __cdecl mt19937_next_u32();

__forceinline static float unsigned_random_as_float(int limit)
{
    return static_cast<float>(
        static_cast<unsigned int>(selector_random_roll(limit)));
}

__forceinline static float unsigned_mt_mod_as_float(unsigned int limit)
{
    return static_cast<float>(mt19937_next_u32() % limit);
}

void AyaObjectActionView::initialize_action_entry()
{
    velocity_x_f4() = 0.0f;
    velocity_y_f8() = 0.0f;
    state_370 = 0.0f;
    state_374 = 0.0f;
    state_378 = 0.0f;
    state_six_counter_384 = 0;
    state_37c = 0.0f;
    phase_counter_386 = 0;
    state_380 = 0.0f;
    phase_index_184 = 0;
    state_364 = 0;
    state_366 = 0;
    state_368 = 0;
    state_36a = 0;
    state_36c = 0;

    float *shared_heading;
    float shared_scalar;

    switch (action_id_13c) {
    case 800:
        shared_heading = heading_340;
        phase_index_184 = 1;
        sprite_004.reset_one_118 = 2.0f;
        sprite_004.reset_one_11c = 2.0f;
        sprite_004.reset_zero_128 = shared_heading[0];
        state_364 = 3;
        goto action800_810_select;

    case 803: {
        float *const heading = heading_340;
        phase_index_184 = 1;
        select_sequence(static_cast<int>(heading[2]));
        if (sequence_index_13e == 0)
            phase_index_184 = 3;
        return;
    }

    case 804:
        phase_index_184 = 1;
        sprite_004.reset_zero_128 = heading_340[0];
        return;

    case 807: {
        phase_index_184 = 1;
        sprite_004.reset_one_118 = 2.0f;
        sprite_004.reset_one_11c = 2.0f;
        sprite_004.reset_zero_128 = unsigned_mt_mod_as_float(360);
        float *const heading = heading_340;
        sprite_004.reset_zero_120 = 65.0f;
        motion_core()->set_oriented_components_f0_f4(heading[0], heading[1]);
        select_sequence(static_cast<int>(heading_340[2]));
        return;
    }

    case 810:
        shared_heading = heading_340;
        state_17c = 0;
        sprite_004.reset_one_118 = 1.5f;
        phase_index_184 = 1;
        sprite_004.reset_one_11c = 1.5f;
        sprite_004.reset_zero_128 = shared_heading[0];
    action800_810_select:
        select_sequence(static_cast<int>(shared_heading[2]));
        return;

    case 811:
        state_17c = 4;
        goto action801_854_select;

    case 801:
    case 854:
    action801_854_select: {
        float *const heading = heading_340;
        phase_index_184 = 1;
        sprite_004.reset_zero_128 = heading[0];
        select_sequence(static_cast<int>(heading[2]));
        return;
    }

    case 812: {
        CharacterObjectEffectEmitter *const owner = fighter_owner_348;
        state_17c = 8;
        phase_index_184 = 1;
        state_370 = static_cast<float>(175 * sprite_004.object_facing_100) + owner->x_ec;
        state_374 = owner->y_f0 + 130.0f;
        select_sequence(static_cast<int>(heading_340[2]));
        int const sequence = sequence_index_13e;
        switch (sequence) {
        case 0:
            sprite_004.reset_zero_128 =
                -heading_340[0] - static_cast<float>(90 * sprite_004.object_facing_100);
            return;
        case 2:
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            state_374 = unsigned_random_as_float(20) * 0.1f - 1.0f;
            return;
        }
        return;
    }

    case 815:
        sprite_004.reset_zero_128 = heading_340[0];
        return;

    case 816:
        sprite_004.reset_zero_128 = heading_340[0];
        return;

    case 817: {
        {
            float *const heading = heading_340;
            state_17c = 9;
            select_sequence(static_cast<int>(heading[2]));
        }
        int const sequence = sequence_index_13e;
        switch (sequence) {
        case 2: {
            float const scale = unsigned_mt_mod_as_float(10) * 0.1f + 1.0f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            state_370 = unsigned_random_as_float(20) + 10.0f;
            sprite_004.reset_zero_124 = unsigned_random_as_float(25) + 50.0f;
            sprite_004.reset_zero_120 =
                static_cast<float>(sprite_004.object_facing_100) * heading_340[0];
            return;
        }
        case 0: {
            float *const heading = heading_340;
            phase_index_184 = 1;
            sprite_004.reset_zero_128 = heading[0];
            float payload[3] = {0.0f, 0.0f, 1.0f};
            effect_emitter()->spawn_unparented_related_object(
                817,
                sprite_004.object_x_0e8,
                sprite_004.object_y_0ec,
                static_cast<unsigned char>(sprite_004.object_facing_100),
                1,
                reinterpret_cast<const unsigned int *>(payload),
                3);
            return;
        }
        }
        return;
    }

    case 820: {
        state_370 = 0.5f;
        state_17c = 2;
        phase_index_184 = 1;
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 2 || sequence_index_13e == 3) {
            float const scale = unsigned_mt_mod_as_float(50) * 0.01f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_120 = unsigned_mt_mod_as_float(60) + 60.0f;
            sprite_004.reset_zero_124 = unsigned_mt_mod_as_float(60) - 30.0f;
            sprite_004.reset_zero_128 = unsigned_mt_mod_as_float(360);
        }
        if (sequence_index_13e == 4 ||
            sequence_index_13e == 5 ||
            sequence_index_13e == 6) {
            float *const heading = heading_340;
            sprite_004.reset_zero_128 = heading[0];
        }
        return;
    }

    case 821: {
        {
            float *const heading = heading_340;
            state_17c = 6;
            phase_index_184 = 1;
            sprite_004.reset_zero_128 = heading[0];
            select_sequence(static_cast<int>(heading[2]));
        }
        if (sequence_index_13e == 1) {
            if (static_cast<unsigned int>(selector_random_roll(100)) <= 49u)
                state_374 = 1.0f;
            else
                state_374 = -1.0f;
        }
        if (sequence_index_13e == 3) {
            float *const heading = heading_340;
            velocity_x_f4() = heading[1];
            velocity_y_f8() = 0.0f;
        }
        if (sequence_index_13e == 5)
            sprite_004.reset_zero_120 = 80.0f;
        if (sequence_index_13e == 6) {
            sprite_004.reset_zero_120 = 80.0f;
            reinterpret_cast<unsigned char *>(this)[0x113] = 0x80;
        }
        return;
    }

    case 822: {
        {
            float *const heading = heading_340;
            state_17c = 10;
            select_sequence(static_cast<int>(heading[2]));
        }
        int const sequence = sequence_index_13e;
        switch (sequence) {
        case 2: {
            float const scale = unsigned_mt_mod_as_float(10) * 0.1f + 1.0f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            state_370 = unsigned_random_as_float(20) + 10.0f;
            sprite_004.reset_zero_124 = unsigned_random_as_float(25) + 50.0f;
            sprite_004.reset_zero_120 =
                static_cast<float>(sprite_004.object_facing_100) * heading_340[0];
            return;
        }
        case 0: {
            float *const heading = heading_340;
            phase_index_184 = 1;
            sprite_004.reset_zero_128 = heading[0];
            float payload[3] = {0.0f, 0.0f, 1.0f};
            effect_emitter()->spawn_unparented_related_object(
                822,
                sprite_004.object_x_0e8,
                sprite_004.object_y_0ec,
                static_cast<unsigned char>(sprite_004.object_facing_100),
                1,
                reinterpret_cast<const unsigned int *>(payload),
                3);
            return;
        }
        }
        return;
    }

    case 825:
        state_17c = 3;
        phase_index_184 = 1;
        select_sequence(static_cast<int>(heading_340[2]));
        return;

    case 826: {
        state_17c = 7;
        phase_index_184 = 1;
        if (*reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(fighter_owner_348) + 0x60b) == 3)
            phase_index_184 = 2;
        if (*reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(fighter_owner_348) + 0x60b) >= 4)
            phase_index_184 = 3;
        goto action826_861_shared;
    }

    case 850:
        phase_index_184 = 1;
        sprite_004.reset_one_118 = 1.0f;
        sprite_004.reset_one_11c = 2.0f;
        velocity_x_f4() = 10.0f;
        return;

    case 851:
        phase_index_184 = 1;
        sprite_004.reset_one_118 = 1.2f;
        sprite_004.reset_one_11c = 1.2f;
        return;

    case 852: {
        phase_index_184 = 1;
        float scale = unsigned_random_as_float(50) * 0.01f + 1.0f;
        sprite_004.reset_one_118 = scale;
        sprite_004.reset_one_11c = scale;
        sprite_004.reset_zero_128 = unsigned_random_as_float(360);
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 1) {
            scale = unsigned_random_as_float(100) * 0.01f + 1.0f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
        }
        if (sequence_index_13e > 1)
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
        if (sequence_index_13e == 2)
            state_370 = unsigned_random_as_float(20) - 10.0f;
        if (sequence_index_13e == 3)
            state_370 = unsigned_random_as_float(14) - 7.0f;
        return;
    }

    case 853: {
        state_370 = 0.5f;
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0)
            state_344 = 1;
        if (sequence_index_13e == 2 || sequence_index_13e == 3) {
            state_344 = 1;
            float const scale = unsigned_mt_mod_as_float(50) * 0.01f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_120 = unsigned_mt_mod_as_float(60) + 60.0f;
            sprite_004.reset_zero_124 = unsigned_mt_mod_as_float(60) - 30.0f;
            sprite_004.reset_zero_128 = unsigned_mt_mod_as_float(360);
        }
        if (sequence_index_13e == 4 || sequence_index_13e == 6)
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
        if (sequence_index_13e == 4 || sequence_index_13e == 5 || sequence_index_13e == 6 || sequence_index_13e == 7) {
            sprite_004.reset_one_118 = unsigned_random_as_float(35) * 0.01f + 0.85f;
            phase_index_184 = 1;
            sprite_004.reset_zero_128 = heading_340[0];
        }
        return;
    }

    case 855:
        phase_index_184 = 10;
        velocity_x_f4() = 30.0f;
        sprite_004.reset_one_118 = 2.0f;
        sprite_004.reset_one_11c = 2.0f;
        return;

    case 856: {
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 1 || sequence_index_13e == 2 || sequence_index_13e == 3) {
            if (sequence_index_13e == 1) {
                CharacterObjectEffectEmitter *const target = target_170;
                float const dx = (target->x_ec - sprite_004.object_x_0e8) *
                    static_cast<float>(sprite_004.object_facing_100);
                heading_340[0] = -atan2_degrees(
                    (target->y_f0 + 100.0f) - sprite_004.object_y_0ec, dx);
                if (heading_340[0] > 10.0f)
                    heading_340[0] = 10.0f;
                if (heading_340[0] < -10.0f)
                    heading_340[0] = -10.0f;
            } else {
                sprite_004.reset_one_118 = 2.0f;
                sprite_004.reset_one_11c = unsigned_random_as_float(8) * 0.1f + 0.25f;
            }
            sprite_004.reset_zero_128 = heading_340[0];
            phase_index_184 = 1;
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
        }
        if (sequence_index_13e == 4)
            phase_index_184 = 1;
        if (sequence_index_13e == 5) {
            sprite_004.reset_one_11c = 30.0f;
            sprite_004.reset_zero_128 = heading_340[0];
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
        }
        return;
    }

    case 861:
        phase_index_184 = 10;
    action826_861_shared: {
        state_370 = 0.3f;
        sprite_004.reset_one_118 = 0.25f;
        sprite_004.reset_one_11c = 0.25f;
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 1) {
            float *const heading = heading_340;
            sprite_004.reset_zero_120 = heading[0];
            sprite_004.reset_zero_124 = heading[1];
        }
        return;
    }

    case 862: {
        float *const heading = heading_340;
        sprite_004.reset_one_118 = 3.0f;
        sprite_004.reset_one_11c = 2.0f;
        sprite_004.reset_zero_128 = heading[0];
        select_sequence(static_cast<int>(heading[1]));
        return;
    }

    case 900: {
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            float payload[3] = {0.0f, 0.0f, 1.0f};
            effect_emitter()->spawn_parented_related_object(
                900,
                sprite_004.object_x_0e8,
                sprite_004.object_y_0ec + 100.0f,
                static_cast<unsigned char>(sprite_004.object_facing_100),
                1,
                reinterpret_cast<const unsigned int *>(payload),
                3);
            phase_index_184 = 1;
        }
        if (sequence_index_13e == 1) {
            sprite_004.reset_one_118 = 3.0f;
            sprite_004.reset_one_11c = 2.0f;
        }
        if (sequence_index_13e == 3) {
            sprite_004.reset_one_118 = 2.0f;
            sprite_004.reset_one_11c = 2.0f;
            phase_index_184 = 1;
            sprite_004.reset_zero_128 = heading_340[0];
        }
        if (sequence_index_13e == 5) {
            velocity_x_f4() = 30.0f;
            velocity_y_f8() = -2.0f;
        }
        return;
    }

    case 901: {
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            sprite_004.reset_zero_128 = heading_340[0];
            state_370 = heading_340[0];
            state_374 = 270.0f;
            phase_index_184 = 1;
        }
        if (sequence_index_13e == 1)
            sprite_004.reset_zero_128 = heading_340[0];
        if (sequence_index_13e == 2)
            sprite_004.reset_zero_128 = heading_340[0];
        if (sequence_index_13e == 3) {
            sprite_004.reset_zero_128 = heading_340[0];
            phase_index_184 = 1;
        }
        return;
    }

    case 902:
        phase_index_184 = 1;
        sprite_004.reset_one_118 = 1.0f;
        sprite_004.reset_one_11c = 2.0f;
        velocity_x_f4() = heading_340[1];
        return;

    case 903: {
        select_sequence(static_cast<int>(heading_340[2]));
        short const sequence = sequence_index_13e;
        if (sequence == 1 || sequence == 2 || sequence == 3) {
            phase_index_184 = 1;
            sprite_004.reset_zero_128 = heading_340[0];
        }
        if (sequence == 4 || sequence == 5)
            reinterpret_cast<unsigned char *>(this)[0x113] = 0;
        if (sequence == 6) {
            sprite_004.reset_zero_128 = heading_340[0];
            shared_scalar = unsigned_random_as_float(50) * 0.01f;
            sprite_004.reset_one_118 = shared_scalar + 1.0f;
            shared_scalar = unsigned_random_as_float(50) * 0.01f;
            sprite_004.reset_one_11c = shared_scalar + 1.0f;
        }
        if (sequence_index_13e == 7) {
            phase_index_184 = 1;
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            state_370 = -5.0f - unsigned_random_as_float(50) * 0.1f;
        }
        return;
    }

    case 980:
        continue_action_980_596370();
        return;

    case 990:
    case 998:
        sprite_004.reset_zero_128 = 0.0f;
        sprite_004.reset_zero_124 = 60.0f;
        return;

    case 997:
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            velocity_x_f4() = 30.0f;
            velocity_y_f8() = 15.0f;
        }
        return;

    default:
        return;
    }
}

} // namespace th105
