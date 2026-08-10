#include "Collision.hpp"

namespace th105 {

namespace {

// Keeping the recovered prefix as a narrow view preserves the target VC8 load
// order; compiling this body through the growing Fighter type hoists +0x170.
struct FighterFacingView {
    unsigned char unknown_000[0xec];
    float x_ec;
    unsigned char unknown_f0[0x14];
    signed char facing_104;
    unsigned char unknown_105[0x6b];
    FighterFacingView *other_fighter_170;
};

} // namespace

bool __fastcall update_fighter_facing_from_other_x(Fighter *fighter)
{
    FighterFacingView *view = reinterpret_cast<FighterFacingView *>(fighter);
    const signed char previous_facing = view->facing_104;
    if (view->x_ec < view->other_fighter_170->x_ec) {
        view->facing_104 = 1;
        return previous_facing != 1;
    }
    if (view->x_ec > view->other_fighter_170->x_ec) {
        view->facing_104 = -1;
        return previous_facing != -1;
    }
    return false;
}

} // namespace th105
