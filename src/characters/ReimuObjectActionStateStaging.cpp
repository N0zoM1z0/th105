// Bounded source phase inside ReimuObject496540, original Japanese1.06a.
// No original function boundary, full-root implementation or exact claim.
#include "ReimuObjectActionStateStaging.hpp"
#include "CharacterObjectEffects.hpp"
#include "CharacterObjectRuntime.hpp"

namespace th105 {

double __cdecl lookup_orientation_sine_quantized_abs(float angle);

bool ReimuObjectActionStateStagingView::try_update_scalar_actions()
{
    switch (action_13c) {
    case 859:
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 &&
                sequence_13e == 0) {
            phase_index_184 = 99;
            state_364 = 0;
        }
        if (sequence_13e == 0) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 0.0f;
        }
        if (sequence_13e == 1)
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + static_cast<double>(0.05f));
        if (phase_state_180 == 6) {
            ++phase_index_184;
            phase_state_180 = 0;
        }
        if (phase_state_180 != 0) {
            ++state_364;
            if (state_364 > 5) {
                state_364 = 0;
                phase_state_180 = 0;
            }
        }
        heading_12c = static_cast<float>(heading_12c - 1.0);
        x_ec = static_cast<float>(static_cast<float>(facing_104) * velocity_x_f4 + x_ec);
        y_f0 += velocity_y_f8;
        if (x_ec > 1680.0 || x_ec < -400.0)
            goto retire;
        goto advance_and_retire_on_completion;

    case 860: {
        const double pulse = lookup_orientation_sine_quantized_abs(
            static_cast<float>(counter_144 * 6));
        scale_x_11c = scale_y_120 = static_cast<float>(pulse * 2.0 + 1.0);
        if (alpha_113 < 25)
            goto retire;
        alpha_113 = static_cast<unsigned char>(alpha_113 - 25);
        goto advance_with_sequence_retirement;
    }
    case 861: {
        const float *const parameters = parameters_340;
        heading_12c = parameters[0];
        reinterpret_cast<CharacterObjectRuntime *>(
            reinterpret_cast<unsigned char *>(this) + 4)->set_oriented_components_f0_f4(
                parameters[0], parameters[1]);
        scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
        scale_y_120 = static_cast<float>(scale_y_120 * static_cast<double>(0.8f));
        if (alpha_113 < 10)
            goto retire;
        alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
        x_ec = static_cast<float>(static_cast<float>(facing_104) * velocity_x_f4 + x_ec);
        y_f0 += velocity_y_f8;
        goto advance_with_sequence_retirement;
    }
    case 980:
        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
            update_ping_pong_motion_and_periodic_spawn();
        goto advance_and_retire_on_completion;

    case 998:
        heading_12c = static_cast<float>(heading_12c + 5.0);
        if (sequence_13e == 0) {
            // The owner is reread after the virtual sequence operation below.
            const unsigned char *const owner = fighter_owner_348;
            if (*reinterpret_cast<const short *>(owner + 0x13c) > 153 &&
                    *reinterpret_cast<const short *>(owner + 0x13c) < 158) {
                x_ec = static_cast<float>(facing_104 * 57 +
                    *reinterpret_cast<const float *>(owner + 0xec));
                y_f0 = static_cast<float>(*reinterpret_cast<const float *>(owner + 0xf0) + 60.0);
            }
            if (*reinterpret_cast<const short *>(owner + 0x13c) > 149 &&
                    *reinterpret_cast<const short *>(owner + 0x13c) < 154) {
                x_ec = static_cast<float>(facing_104 * 57 +
                    *reinterpret_cast<const float *>(owner + 0xec));
                y_f0 = static_cast<float>(*reinterpret_cast<const float *>(owner + 0xf0) + 94.0);
            }
            if (*reinterpret_cast<const short *>(owner + 0x13c) == 158) {
                x_ec = static_cast<float>(facing_104 * 57 +
                    *reinterpret_cast<const float *>(owner + 0xec));
                y_f0 = static_cast<float>(*reinterpret_cast<const float *>(owner + 0xf0) + 100.0);
            }
            if (*reinterpret_cast<const short *>(owner + 0x13c) < 150 ||
                    *reinterpret_cast<const short *>(owner + 0x13c) > 158) {
                next_sequence_block();
                fighter_owner_348[0x751] = 0;
            }
        }
        if (sequence_13e == 1) {
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
        }
        goto advance_and_retire_on_completion;

    case 800: case 801: case 804: case 807: case 808:
    case 810: case 811: case 812: case 815: case 816: case 817:
    case 821: case 822: case 825: case 848:
    case 850: case 851: case 852: case 853: case 854: case 855: case 856: case 858:
    case 866: case 869:
    case 900: case 901: case 902: case 903: case 904: case 905: case 906: case 907: case 908:
    case 951: case 999:
        return false;
    default:
        reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch();
        return true;
    }

advance_with_sequence_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 1)
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
        --state_330;
    return true;

advance_and_retire_on_completion:
    if (!reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        return true;
retire:
    --state_330;
    return true;
}

} // namespace th105
