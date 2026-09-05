#include <stddef.h>

namespace th105 {

struct FighterScaledCounterView {
    unsigned char unknown_000[0x4d0];
    float scale_4d0;
    unsigned char unknown_4d4[0x84];
    short counter_558;
    signed char phase_55a;

    int add_scaled_counter(int value);
};

typedef char CheckScaledCounterScale[
    offsetof(FighterScaledCounterView, scale_4d0) == 0x4d0 ? 1 : -1];
typedef char CheckScaledCounterValue[
    offsetof(FighterScaledCounterView, counter_558) == 0x558 ? 1 : -1];
typedef char CheckScaledCounterPhase[
    offsetof(FighterScaledCounterView, phase_55a) == 0x55a ? 1 : -1];

int FighterScaledCounterView::add_scaled_counter(int value)
{
    if (phase_55a >= 4) {
        double scaled = static_cast<double>(value);
        scaled *= 0.5;
        scaled *= scale_4d0;
        int const result = static_cast<int>(scaled);
        counter_558 += result;
        return result;
    }
    if (phase_55a >= 3) {
        double scaled = static_cast<double>(value);
        scaled *= 0.6600000262260437;
        scaled *= scale_4d0;
        int const result = static_cast<int>(scaled);
        counter_558 += result;
        return result;
    }
    int const result = static_cast<int>(scale_4d0 * value);
    counter_558 += result;
    return result;
}

struct FighterFaceFlipView {
    unsigned char unknown_000[0xec];
    float x_ec;
    unsigned char unknown_f0[4];
    float velocity_x_f4;
    unsigned char unknown_f8[0xc];
    signed char facing_104;
    unsigned char unknown_105[0x6b];
    FighterFaceFlipView *peer_170;

    void face_opponent_and_flip_horizontal_velocity();
};

typedef char CheckFaceFlipX[
    offsetof(FighterFaceFlipView, x_ec) == 0xec ? 1 : -1];
typedef char CheckFaceFlipVelocity[
    offsetof(FighterFaceFlipView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckFaceFlipFacing[
    offsetof(FighterFaceFlipView, facing_104) == 0x104 ? 1 : -1];
typedef char CheckFaceFlipPeer[
    offsetof(FighterFaceFlipView, peer_170) == 0x170 ? 1 : -1];

void FighterFaceFlipView::face_opponent_and_flip_horizontal_velocity()
{
    signed char const negative = -1;
    if (facing_104 == 1 && x_ec > peer_170->x_ec) {
        float const old_velocity = velocity_x_f4;
        facing_104 = negative;
        velocity_x_f4 = -old_velocity;
    }
    if (facing_104 == negative && x_ec < peer_170->x_ec) {
        float const old_velocity = velocity_x_f4;
        facing_104 = 1;
        velocity_x_f4 = -old_velocity;
    }
}

} // namespace th105
