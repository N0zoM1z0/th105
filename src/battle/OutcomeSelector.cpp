#include "Collision.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);

int Fighter::select_outcome_path_from_frame_flags(unsigned frame_flags)
{
    const unsigned char flags = static_cast<unsigned char>(frame_flags);

    if ((flags & 0x10) != 0 || blocker_48e != 0) {
        return 0;
    }

    const unsigned current_flags = frame_158->flags_4c;
    if ((current_flags & 0x200) != 0) {
        return 6;
    }
    if ((current_flags & 0x10) == 0) {
        return 0;
    }

    int *const battle_state =
        *reinterpret_cast<int **>(0x006e4e28);
    const int roll_policy =
        *reinterpret_cast<int *>(0x006e4e34);

    if (is_state_13c_in_96_c7(this) != 0) {
        if (field_6b0 == 0) {
            if (state_72c == 3) {
                if (battle_state[8] == 2) {
                    field_6b8 = 0;
                } else if (battle_state[8] == 3) {
                    field_6b8 = 1;
                } else {
                    field_6b8 =
                        (static_cast<unsigned char>(~flags) >> 1) & 1;
                }
            } else {
                field_6b8 =
                    (static_cast<unsigned char>(~flags) >> 1) & 1;
            }
        }
    } else {
        if (field_6b0 == 0) {
            if (state_72c == 3) {
                field_6b8 = 0;
                field_6b4 = 0;
                if (battle_state[3] <= 0) {
                    goto after_refresh;
                }
            } else if (roll_policy == 0) {
                if (selector_random_roll(100) >= 70) {
                    goto after_refresh;
                }
            } else if (roll_policy == 1 &&
                       selector_random_roll(100) >= 95) {
                goto after_refresh;
            }

            field_6b4 =
                other_fighter_170->x_ec - x_ec <= 0.0f ? 1 : -1;
            if (state_72c == 3) {
                if (battle_state[8] == 2) {
                    field_6b8 = 0;
                } else if (battle_state[8] == 3) {
                    field_6b8 = 1;
                } else {
                    field_6b8 =
                        (static_cast<unsigned char>(~flags) >> 1) & 1;
                }
            } else {
                field_6b8 =
                    (static_cast<unsigned char>(~flags) >> 1) & 1;
            }
        }

after_refresh:
        if (gate_4ed == 0 &&
            ((other_fighter_170->x_ec - x_ec) * field_6b4 > 0.0f ||
             field_6b4 == 0)) {
            return 0;
        }
    }

    if (is_y_at_or_below_stage_surface(this) == 0 ||
        (frame_158->flags_4c & 4) != 0) {
        return (flags & 8) != 0 ? 5 : 0;
    }
    if (field_6b8 <= 0) {
        return (flags & 2) != 0 ? 1 :
            ((static_cast<unsigned char>(~flags) >> 5) & 2);
    }
    if ((flags & 4) != 0) {
        return 3;
    }
    return (static_cast<unsigned char>(~flags) >> 4) & 4;
}

} // namespace th105
