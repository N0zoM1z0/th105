#include "Collision.hpp"

namespace th105 {

namespace {
short &fighter_short_at(Fighter *fighter, unsigned offset)
{
    return *reinterpret_cast<short *>(
        reinterpret_cast<unsigned char *>(fighter) + offset);
}
}

void __fastcall reset_fighter_round_counters_45f610(Fighter *fighter)
{
    fighter->unknown_484 = 1000;
    fighter->counter_482 = 1000;
    fighter->floor_486 = 0;
    fighter_short_at(fighter, 0x488) = 0;
    fighter_short_at(fighter, 0x6a0) = 0;
}

} // namespace th105
