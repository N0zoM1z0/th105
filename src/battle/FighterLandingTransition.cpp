#include <stddef.h>

#include "BattleBackgroundLayout.hpp"

namespace th105 {

struct Fighter;

float __fastcall stage_surface_height_at_x(Fighter *fighter);
int __fastcall is_y_at_or_below_stage_surface(Fighter *fighter);
void dispatch_indexed_event(unsigned index);

class FighterLandingTransitionView {
public:
    virtual void scalar_delete_slot_00();
    virtual void virtual_slot_04();
    virtual void set_action(int action_id);

    unsigned char resolve_stage_surface_landing_transition();
    int has_crossed_stage_surface_while_descending();
    void publish_battle_layout_scalar(float value);
    void dispatch_indexed_event_member(unsigned index);

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    float acceleration_x_fc;
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x27];
    float angle_12c;
    unsigned char unknown_130[0x0c];
    short action_id_13c;
    unsigned char unknown_13e[0x4e];
    float landing_response_x_18c;
    float landing_response_y_190;
};

typedef char FighterLanding_y_offset[
    offsetof(FighterLandingTransitionView, y_f0) == 0xf0 ? 1 : -1];
typedef char FighterLanding_velocity_x_offset[
    offsetof(FighterLandingTransitionView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char FighterLanding_velocity_y_offset[
    offsetof(FighterLandingTransitionView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char FighterLanding_acceleration_y_offset[
    offsetof(FighterLandingTransitionView, acceleration_y_100) == 0x100 ? 1 : -1];
typedef char FighterLanding_angle_offset[
    offsetof(FighterLandingTransitionView, angle_12c) == 0x12c ? 1 : -1];
typedef char FighterLanding_action_offset[
    offsetof(FighterLandingTransitionView, action_id_13c) == 0x13c ? 1 : -1];
typedef char FighterLanding_response_x_offset[
    offsetof(FighterLandingTransitionView, landing_response_x_18c) == 0x18c ? 1 : -1];
typedef char FighterLanding_response_y_offset[
    offsetof(FighterLandingTransitionView, landing_response_y_190) == 0x190 ? 1 : -1];

unsigned char FighterLandingTransitionView::resolve_stage_surface_landing_transition()
{
    Fighter *const fighter = reinterpret_cast<Fighter *>(this);
    if (static_cast<unsigned char>(is_y_at_or_below_stage_surface(fighter)))
        return 0;

    if (static_cast<double>(y_f0) - stage_surface_height_at_x(fighter) <= 5.0
        || action_id_13c == 98 || action_id_13c == 99) {
        y_f0 = stage_surface_height_at_x(fighter);
        return 0;
    }

    if (action_id_13c >= 50 && action_id_13c <= 149) {
        angle_12c = 0.0f;
        landing_response_y_190 = 0.0f;
        landing_response_x_18c = -velocity_x_f4;
        set_action(71);
        angle_12c = 0.0f;
        acceleration_y_100 = 0.5f;
        return 1;
    }

    if (action_id_13c >= 700 && action_id_13c <= 799) {
        angle_12c = 0.0f;
        acceleration_y_100 = 0.5f;
        set_action(704);
        angle_12c = 0.0f;
        velocity_y_f8 = 0.0f;
        acceleration_y_100 = 0.5f;
        if (velocity_x_f4 > 10.0f)
            velocity_x_f4 = 10.0f;
        if (velocity_x_f4 < -10.0f)
            velocity_x_f4 = -10.0f;
        return 1;
    }

    velocity_y_f8 = 0.0f;
    acceleration_y_100 = 0.5f;
    angle_12c = 0.0f;
    if (velocity_x_f4 > 10.0f)
        velocity_x_f4 = 10.0f;
    if (velocity_x_f4 < -10.0f)
        velocity_x_f4 = -10.0f;
    acceleration_y_100 = 0.5f;
    set_action(9);
    return 1;
}

int FighterLandingTransitionView::has_crossed_stage_surface_while_descending()
{
    Fighter *const fighter = reinterpret_cast<Fighter *>(this);
    return static_cast<double>(y_f0) <= stage_surface_height_at_x(fighter)
        && velocity_y_f8 < 0.0f;
}


void FighterLandingTransitionView::publish_battle_layout_scalar(float value)
{
    g_battle_background_layout.set_runtime_scalar(value);
}

void FighterLandingTransitionView::dispatch_indexed_event_member(unsigned index)
{
    dispatch_indexed_event(index);
}

} // namespace th105
