#pragma once

#include <stddef.h>

namespace th105 {

// Observed runtime view for496540, including the original void entry at slot28.
// All41 action bodies are source hypotheses; canonical equality is unaccepted.
class ReimuObjectActionStateStagingView {
public:
    virtual void slot_00();
    virtual int set_action_sequence_and_finalize(short action, int sequence);
    virtual int set_action_and_finalize(short action);
    virtual int select_sequence(short sequence);
    virtual int reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual void slot_18();
    virtual int set_sequence_frame(short frame);
    virtual unsigned char next_sequence_frame();

    // Slot24 is an opaque layout marker; this source never calls it.
    virtual void slot_24();
    virtual void dispatch_action_state();
    void publish_battle_layout_scalar(float value);
    int has_crossed_stage_surface_while_descending();

    unsigned char unknown_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    float acceleration_x_fc;
    float acceleration_y_100;
    signed char facing_104;
    unsigned char unknown_105[0x0b];
    unsigned char channel_110;
    unsigned char channel_111;
    unsigned char channel_112;
    unsigned char alpha_113;
    unsigned char unknown_114[8];
    float scale_x_11c;
    float scale_y_120;
    float angle_x_124;
    float angle_y_128;
    float heading_12c;
    unsigned char unknown_130[0x0c];
    short action_13c;
    short sequence_13e;
    short frame_140;
    short frame_timer_142;
    int counter_144;
    short sequence_frame_count_148;
    unsigned char unknown_14a[2];
    short frame_limit_14c;
    unsigned char unknown_14e[0x22];
    unsigned char *followed_actor_170;
    short value_174;
    unsigned char unknown_176[0x0a];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x1ab];
    int state_330;
    unsigned char unknown_334[8];
    unsigned char direction_33c;
    unsigned char unknown_33d[3];
    float *parameters_340;
    short state_344;
    unsigned char unknown_346[2];
    unsigned char *fighter_owner_348;
    ReimuObjectActionStateStagingView *parent_object_34c;
    unsigned char unknown_350[0x14];
    short state_364;
    short state_366;
    short state_368;
    short state_36a;
    short state_36c;
    unsigned char unknown_36e[2];
    float state_370;
    float state_374;
    float state_378;
    float state_37c;
    float state_380;
    short state_six_counter_384;
    short phase_counter_386;
};

typedef char ReimuObjectUpdate_x_offset[
    offsetof(ReimuObjectActionStateStagingView, x_ec) == 0xec ? 1 : -1];
typedef char ReimuObjectUpdate_alpha_offset[
    offsetof(ReimuObjectActionStateStagingView, alpha_113) == 0x113 ? 1 : -1];
typedef char ReimuObjectUpdate_channel110_offset[
    offsetof(ReimuObjectActionStateStagingView, channel_110) == 0x110 ? 1 : -1];

typedef char ReimuObjectUpdate_followed170_offset[
    offsetof(ReimuObjectActionStateStagingView, followed_actor_170) == 0x170 ? 1 : -1];

typedef char ReimuObjectUpdate_value174_offset[
    offsetof(ReimuObjectActionStateStagingView, value_174) == 0x174 ? 1 : -1];

typedef char ReimuObjectUpdate_channel111_offset[
    offsetof(ReimuObjectActionStateStagingView, channel_111) == 0x111 ? 1 : -1];
typedef char ReimuObjectUpdate_channel112_offset[
    offsetof(ReimuObjectActionStateStagingView, channel_112) == 0x112 ? 1 : -1];
typedef char ReimuObjectUpdate_sequence_offset[
    offsetof(ReimuObjectActionStateStagingView, sequence_13e) == 0x13e ? 1 : -1];
typedef char ReimuObjectUpdate_phase_offset[
    offsetof(ReimuObjectActionStateStagingView, phase_state_180) == 0x180 ? 1 : -1];
typedef char ReimuObjectUpdate_state330_offset[
    offsetof(ReimuObjectActionStateStagingView, state_330) == 0x330 ? 1 : -1];
typedef char ReimuObjectUpdate_direction33c_offset[
    offsetof(ReimuObjectActionStateStagingView, direction_33c) == 0x33c ? 1 : -1];
typedef char ReimuObjectUpdate_parameters_offset[
    offsetof(ReimuObjectActionStateStagingView, parameters_340) == 0x340 ? 1 : -1];
typedef char ReimuObjectUpdate_owner_offset[
    offsetof(ReimuObjectActionStateStagingView, fighter_owner_348) == 0x348 ? 1 : -1];
typedef char ReimuObjectUpdate_state364_offset[
    offsetof(ReimuObjectActionStateStagingView, state_364) == 0x364 ? 1 : -1];
typedef char ReimuObjectUpdate_parent_offset[
    offsetof(ReimuObjectActionStateStagingView, parent_object_34c) == 0x34c ? 1 : -1];
typedef char ReimuObjectUpdate_state36c_offset[
    offsetof(ReimuObjectActionStateStagingView, state_36c) == 0x36c ? 1 : -1];
typedef char ReimuObjectUpdate_counter384_offset[
    offsetof(ReimuObjectActionStateStagingView, state_six_counter_384) == 0x384 ? 1 : -1];
typedef char ReimuObjectUpdate_view_size[
    sizeof(ReimuObjectActionStateStagingView) == 0x388 ? 1 : -1];

} // namespace th105
