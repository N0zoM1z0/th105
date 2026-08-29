#include "battle/BackgroundBase.hpp"

namespace th105 {

void BackgroundBase::set_transition_4654f0(int state, float value)
{
    transition_state_5c = state;
    switch (state) {
    case 0:
    case 2:
        transition_value_60 = value;
        break;
    case 1:
        value_4c = 1.0f;
        break;
    case 3:
        value_4c = 0.0f;
        break;
    }

    {
        unsigned i = 0;
        unsigned count = sprites_b_34.size();
        for (; i < count; ++i) {
            unsigned alpha = static_cast<int>(value_4c * 255.0);
            sprites_b_34[i].set_color((alpha << 24) | 0x00ffffffu);
        }
    }

    {
        unsigned i = 0;
        unsigned count = sprites_a_14.size();
        for (; i < count; ++i) {
            unsigned alpha = static_cast<int>(value_4c * 255.0);
            sprites_a_14[i].set_color((alpha << 24) | 0x00ffffffu);
        }
    }
}

void BackgroundBase::step_transition_4656a0()
{
    unsigned count;
    unsigned i;
    switch (transition_state_5c) {
    case 0:
        i = 0;
        value_4c += transition_value_60;
        if (value_4c >= 1.0f) {
            value_4c = 1.0f;
            transition_state_5c = 1;
        }
        {
            count = sprites_b_34.size();
            for (; i < count; ++i) {
                unsigned alpha = static_cast<int>(value_4c * 255.0);
                sprites_b_34[i].set_color((alpha << 24) | 0x00ffffffu);
            }
        }
        i = 0;
        {
            count = sprites_a_14.size();
            for (; i < count; ++i) {
                unsigned alpha = static_cast<int>(value_4c * 255.0);
                sprites_a_14[i].set_color((alpha << 24) | 0x00ffffffu);
            }
        }
        break;

    case 2:
        i = 0;
        value_4c += transition_value_60;
        if (value_4c <= 0.0f) {
            value_4c = 0.0f;
            transition_state_5c = 3;
        }
        {
            count = sprites_b_34.size();
            for (; i < count; ++i) {
                unsigned alpha = static_cast<int>(value_4c * 255.0);
                sprites_b_34[i].set_color((alpha << 24) | 0x00ffffffu);
            }
        }
        i = 0;
        {
            count = sprites_a_14.size();
            for (; i < count; ++i) {
                unsigned alpha = static_cast<int>(value_4c * 255.0);
                sprites_a_14[i].set_color((alpha << 24) | 0x00ffffffu);
            }
        }
        break;
    }
}

} // namespace th105
