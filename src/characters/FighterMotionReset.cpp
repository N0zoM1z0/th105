namespace th105 {

namespace {

// This is intentionally a prefix view rather than a second Fighter layout.
// The four fields and their offsets are independently observed in the shared
// position integrator and in the target helper at 0x00459970.
struct FighterMotionResetView {
    unsigned char unknown_000[0xf4];
    float x_velocity_f4;
    float y_velocity_f8;
    float x_acceleration_fc;
    float y_acceleration_100;

    void Fighter_zero_velocity_acceleration();
};

typedef char FighterMotionResetView_size_must_be_0x104[
    sizeof(FighterMotionResetView) == 0x104 ? 1 : -1];

} // namespace

void FighterMotionResetView::Fighter_zero_velocity_acceleration()
{
    x_velocity_f4 = 0.0f;
    y_velocity_f8 = 0.0f;
    x_acceleration_fc = 0.0f;
    y_acceleration_100 = 0.0f;
}

} // namespace th105
