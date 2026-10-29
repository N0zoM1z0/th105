#pragma once

#include "battle/AnimationSpriteState.hpp"
#include "characters/AnimationSequenceVirtuals.hpp"
#include "characters/CharacterObjectEffects.hpp"
#include "characters/CharacterObjectRuntime.hpp"

#include <stddef.h>

namespace th105 {

// Partial primary-subobject view shared by AyaObject's +0x28 and +0x3C methods.
// Never construct or embed this view; 0x388 is the represented prefix only.
// The primary vtable at 0x6C624C binds both methods and selects sequences at +0x0C.
// That callee consumes a low word in a four-byte slot; see the 202-byte witness
// in docs/AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md.

class AyaObjectActionView {
public:
    virtual void scalar_delete_slot_00();
    virtual int set_action_sequence_and_finalize(short action, int sequence);
    virtual int set_action_and_finalize(short action);
    virtual int select_sequence(short sequence);
    virtual int reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual int previous_sequence_block();
    virtual int set_sequence_frame(short frame);
    virtual unsigned char next_sequence_frame();
    virtual int previous_sequence_frame();
    virtual void update_action_state();
    virtual void render_main();
    virtual void render_to_battle_scene();
    virtual void prepare_render_transform();
    virtual void render_color_mode();
    virtual void initialize_action_entry();

    void continue_action_980_596370();

    int has_crossed_stage_surface_while_descending();
    unsigned char advance_frame_and_dispatch();
    unsigned char advance_state_six_counter_conditional(int limit);
    unsigned char advance_phase_counter_conditional(int limit);

    AnimationSpriteState sprite_004;
    unsigned int state_130;
    unsigned char layout_absolute_134;
    unsigned char render_to_battle_135;
    unsigned char unknown_136[2];
    float battle_y_offset_138;
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    short sequence_frame_count_148;
    unsigned char unknown_14a[2];
    short frame_limit_14c;
    unsigned char unknown_14e[2];
    AnimationSequenceFrame *frame_150;
    void *aux_renderer_154;
    AnimationSequenceFrame *frame_158;
    AnimationSequenceBlock *sequence_15c;
    AnimationSequenceTree *sequence_tree_160;
    unsigned int *wave_handles_164;
    void *owner_168;
    CharacterObjectEffectEmitter *related_16c;
    CharacterObjectEffectEmitter *target_170;
    short state_174;
    unsigned char unknown_176[6];
    unsigned char state_17c;
    unsigned char unknown_17d[3];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x1ab];
    int lifetime_330;
    unsigned char unknown_334[0x0c];
    float *heading_340;
    short state_344;
    unsigned char unknown_346[2];
    CharacterObjectEffectEmitter *fighter_owner_348;
    CharacterObjectEffectEmitter *related_34c;
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

    float &velocity_x_f4()
    {
        return *reinterpret_cast<float *>(
            reinterpret_cast<unsigned char *>(this) + 0xf4);
    }
    float &velocity_y_f8()
    {
        return *reinterpret_cast<float *>(
            reinterpret_cast<unsigned char *>(this) + 0xf8);
    }
    CharacterObjectRuntime *motion_core()
    {
        return reinterpret_cast<CharacterObjectRuntime *>(
            reinterpret_cast<unsigned char *>(this) + 4);
    }

    CharacterObjectEffectEmitter *effect_emitter()
    {
        return reinterpret_cast<CharacterObjectEffectEmitter *>(this);
    }
};

typedef char AyaObjectAction_sprite_004_offset[
    offsetof(AyaObjectActionView, sprite_004) == 0x4 ? 1 : -1];
typedef char AyaObjectAction_action_id_13c_offset[
    offsetof(AyaObjectActionView, action_id_13c) == 0x13c ? 1 : -1];
typedef char AyaObjectAction_sequence_index_13e_offset[
    offsetof(AyaObjectActionView, sequence_index_13e) == 0x13e ? 1 : -1];
typedef char AyaObjectAction_state_174_offset[
    offsetof(AyaObjectActionView, state_174) == 0x174 ? 1 : -1];
typedef char AyaObjectAction_phase_state_180_offset[
    offsetof(AyaObjectActionView, phase_state_180) == 0x180 ? 1 : -1];
typedef char AyaObjectAction_phase_index_184_offset[
    offsetof(AyaObjectActionView, phase_index_184) == 0x184 ? 1 : -1];
typedef char AyaObjectAction_lifetime_330_offset[
    offsetof(AyaObjectActionView, lifetime_330) == 0x330 ? 1 : -1];
typedef char AyaObjectAction_heading_340_offset[
    offsetof(AyaObjectActionView, heading_340) == 0x340 ? 1 : -1];
typedef char AyaObjectAction_state_344_offset[
    offsetof(AyaObjectActionView, state_344) == 0x344 ? 1 : -1];
typedef char AyaObjectAction_fighter_owner_348_offset[
    offsetof(AyaObjectActionView, fighter_owner_348) == 0x348 ? 1 : -1];
typedef char AyaObjectAction_related_34c_offset[
    offsetof(AyaObjectActionView, related_34c) == 0x34c ? 1 : -1];
typedef char AyaObjectAction_state_364_offset[
    offsetof(AyaObjectActionView, state_364) == 0x364 ? 1 : -1];
typedef char AyaObjectAction_state_370_offset[
    offsetof(AyaObjectActionView, state_370) == 0x370 ? 1 : -1];
typedef char AyaObjectAction_state_six_counter_384_offset[
    offsetof(AyaObjectActionView, state_six_counter_384) == 0x384 ? 1 : -1];
typedef char AyaObjectAction_phase_counter_386_offset[
    offsetof(AyaObjectActionView, phase_counter_386) == 0x386 ? 1 : -1];
typedef char AyaObjectAction_prefix_size[
    sizeof(AyaObjectActionView) == 0x388 ? 1 : -1];

} // namespace th105
