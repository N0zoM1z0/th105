#include "Collision.hpp"

namespace th105 {

int g_fighter_state_4b8_default;

struct FighterEmbeddedState3d0 {
    void step();
};

void __fastcall process_fighter_transient_status(Fighter *fighter)
{
    unsigned char *raw = reinterpret_cast<unsigned char *>(fighter);
    unsigned short &pending_48a =
        *reinterpret_cast<unsigned short *>(raw + 0x48a);

    if (fighter->gate_48c != 0) {
        --fighter->gate_48c;
    }
    if (pending_48a != 0) {
        fighter->gate_48c = pending_48a;
        pending_48a = 0;
    }

    fighter->peer_component_6ac = 0.0f;
    fighter->x_scale_4dc = 1.0f;
    fighter->y_scale_4e0 = 1.0f;

    if (fighter->value_174 < 0) {
        fighter->value_174 = 0;
    }
    if (fighter->value_47c < 0) {
        fighter->value_47c = 0;
    }
    if (fighter->value_174 > fighter->maximum_176) {
        fighter->value_174 = fighter->maximum_176;
    }
    if (!is_state_13c_in_32_95(fighter)) {
        fighter->value_47c = fighter->value_174;
    }

    reinterpret_cast<FighterEmbeddedState3d0 *>(raw + 0x3d0)->step();

    int &countdown_670 = *reinterpret_cast<int *>(raw + 0x670);
    if (countdown_670 > 0) {
        --countdown_670;
    }

    unsigned short const gate_4b2 =
        *reinterpret_cast<unsigned short *>(raw + 0x4b2);
    if (gate_4b2 != 0) {
        fighter->state_4b8 = 16;
    } else {
        fighter->state_4b8 = g_fighter_state_4b8_default;
    }

    signed char *entry = fighter->scalar_modifier_table_604;
    if (fighter->unknown_4e5 != 0) {
        int remaining = 32;
        do {
            *entry = entry[32] < 0 ? 0 : 4;
            ++entry;
        } while (--remaining != 0);
    } else {
        int remaining = 32;
        do {
            unsigned int const value =
                static_cast<unsigned char>(entry[32]);
            *entry++ = value &
                ((static_cast<signed char>(value) < 0) - 1);
        } while (--remaining != 0);
    }
}

} // namespace th105
