#include "battle/ScenarioData.hpp"

namespace th105 {
float __cdecl lookup_orientation_cosine(int value);
float __cdecl lookup_orientation_sine(int value);

bool ScenarioResultResource::update()
{
    if (state_000 == 0)
        return false;

    const signed char previous_phase = phase_001;
    int offset = 0;
    switch (phase_001) {
    case 3: {
        if (counter_004 <= 60)
            alpha_124 = static_cast<unsigned char>((60 - counter_004) * 255 / 60);

        ScenarioResultPositionObject **slot = &primary_03c[1];
        for (; offset < 30; offset += 10, ++slot) {
            const int wave_input = (counter_004 - offset - 10) * 3;
            if (wave_input >= 1 && wave_input <= 89) {
                ScenarioResultPositionObject *object = *slot;
                object->x_04 =
                    (1.0f - lookup_orientation_cosine(wave_input)) * -640.0f;
                object->y_08 = 0.0f;
            }
        }
        if (counter_004 == 60)
            reset();
        break;
    }
    case 1: {
        int index = 0;
        ScenarioResultPositionObject **slot = &primary_03c[1];
        for (; offset < 45; ++index, offset += 15, ++slot) {
            if (counter_004 >= offset + 15 && counter_004 <= offset + 45) {
                ScenarioResultPositionObject *object = *slot;
                const int wave_input = (counter_004 - offset - 15) * 3;
                object->x_04 =
                    (1.0f - lookup_orientation_sine(wave_input)) * 640.0f;
                object->y_08 = 0.0f;
            }
            set_entry_level(index, counter_004 - offset - 15);
        }
        if (counter_004 == 75)
            phase_001 = 2;
        break;
    }
    case 0:
        if (counter_004 <= 30) {
            alpha_124 = static_cast<unsigned char>(counter_004 * 255 / 30);
            if (counter_004 == 30)
                phase_001 = 1;
        }
        break;
    default:
        return true;
    }

    if (phase_001 == previous_phase)
        ++counter_004;
    else
        counter_004 = 0;
    return true;
}
}
