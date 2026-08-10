#pragma once

#include "CollisionList.hpp"

namespace th105 {

struct Fighter;
struct ActorPosition;
struct LocalAabb;
struct WorldAabb;

void __fastcall release_owned_pointer_buffer(void *buffer);

struct HitExchangeIndexedEntry {
    unsigned char unknown_00[0x10];
    int unknown_10;
    int reset_state_14;
    int unknown_18;
    unsigned char reset_flag_1c;
    unsigned char unknown_1d[0x03];
    unsigned char owned_tail_20[0x14];

    __declspec(noinline) void reset_info_manager_indexed_entry();
};

struct InfoManager {
    unsigned char unknown_000[0x16c];
    HitExchangeIndexedEntry indexed_entries_16c[2];
};

extern InfoManager *g_info_manager;

struct FighterActionScratch {
    unsigned char unknown_000[0x104];
    float reset_zero_104;
    float reset_zero_108;
    int reset_minus_one_10c;
    int reset_zero_110;
    unsigned char unknown_114[0x04];
    float reset_one_118;
    float reset_one_11c;
    float reset_zero_120;
    float reset_zero_124;
    float reset_zero_128;

    __declspec(noinline) void reset_fighter_action_scratch();
};

struct AttackCandidateFrame {
    unsigned char unknown_00[0x1c];
    short quantity_1c;
    short owner_multiplier_per_1000_1e;
    short quantity_20;
    short amount_22;
    short boosted_response_quantity_24;
    short threshold_increment_26;
    short result_accumulator_increment_28;
    unsigned short candidate_output_2a;
    unsigned short fighter_output_2c;
    unsigned short result_2e;
    unsigned short result_30;
    short owner_capped_counter_quantity_32;
    unsigned short amount_34;
    unsigned short action_code_36;
    unsigned short alternate_action_code_38;
    unsigned char unknown_3a[0x02];
    float response_3c;
    float response_40;
    short indexed_event_44;
    unsigned short effect_46;
    signed char action_offset_48;
    unsigned char owner_flag_bits_49;
    unsigned char unknown_4a[0x06];
    unsigned flags_50;
};

struct FighterFrame {
    unsigned char unknown_00[0x4c];
    unsigned flags_4c;
    unsigned char unknown_50[0x04];
    LocalAabb *body_aabb_54;
};

struct AttackCandidate {
    unsigned char unknown_000[0x104];
    unsigned char facing_104;
    unsigned char unknown_105[0x63];
    Fighter *source_168;
    Fighter *owner_16c;
    Fighter *related_fighter_170;
    unsigned char unknown_174[0x08];
    signed char scalar_table_index_17c;
    unsigned char unknown_17d[0x03];
    unsigned result_180;
    unsigned char result_slot_184;
    unsigned char unknown_185;
    unsigned short result_186;
    unsigned char unknown_188[0x18];
    unsigned char source_1a0;
    unsigned char unknown_1a1[3];
    AttackCandidateFrame *frame_1a4;

    float calculate_forwarded_quantity();
    float calculate_base_hit_quantity();
    int calculate_descriptor_scaled_quantity_1c();
    int calculate_descriptor_scaled_quantity_20();
};

struct CollisionObjectFrame4c {
    unsigned char unknown_00[0x1c];
    short quantity_1c;
    unsigned char unknown_1e[0x0c];
    unsigned short result_2a;
    unsigned char unknown_2c[0x18];
    short event_44;
    unsigned short effect_46;
    unsigned char unknown_48[0x04];
    unsigned flags_4c;
};

struct CollisionObjectFrame50 {
    unsigned char unknown_00[0x4c];
    unsigned flags_4c;
    unsigned flags_50;
};

struct CollisionObjectClashFrame {
    unsigned char unknown_00[0x10];
    short value_10;
    short value_12;
};

struct CollisionObject {
    unsigned char unknown_000[0x104];
    unsigned char facing_104;
    unsigned char unknown_105[0x53];
    CollisionObjectFrame50 *frame_158;
    unsigned char unknown_15c[0x10];
    void *owner_16c;
    void *owner_170;
    short value_174;
    unsigned char unknown_176[0x0a];
    unsigned result_180;
    unsigned char result_slot_184;
    unsigned char unknown_185;
    unsigned short result_186;
    signed char counter_188;
    signed char gate_189;
    unsigned char unknown_18a[0x16];
    unsigned char source_1a0;
    unsigned char unknown_1a1[0x03];
    CollisionObjectFrame4c *frame_1a4;
    CollisionObjectClashFrame *frame_1a8;
};

struct ByteStrideRange {
    unsigned char unknown_00[0x04];
    unsigned char *begin_04;
    unsigned char *end_08;

    int count_0x88_byte_stride_entries();
};

struct FighterSequenceSlot;
struct SequenceRecord4;

struct FighterSequenceController {
    unsigned unknown_00;
    FighterSequenceSlot **slots_04;
    unsigned slot_capacity_08;
    unsigned head_0c;
    unsigned live_count_10;

    FighterSequenceSlot *entry_at_checked(int index);
    void enqueue_record(const SequenceRecord4 *record);
};

struct Fighter {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    float x_component_f4;
    float y_component_f8;
    float x_component_fc;
    float y_component_100;
    unsigned char facing_104;
    unsigned char unknown_105[0x37];
    short state_13c;
    unsigned char unknown_13e[0x1a];
    FighterFrame *frame_158;
    unsigned char unknown_15c[0x14];
    Fighter *other_fighter_170;
    short value_174;
    short maximum_176;
    int accumulated_hit_quantity_178;
    unsigned char unknown_17c[0x04];
    unsigned result_180;
    unsigned char unknown_184[0x02];
    unsigned short result_186;
    unsigned char unknown_188[0x04];
    float response_18c;
    float response_190;
    unsigned char unknown_194[0x04];
    short scalar_quantity_198;
    unsigned char unknown_19a[0x196];
    int record_key_330;
    signed char player_index_334;
    unsigned char unknown_335[0x147];
    short value_47c;
    unsigned char unknown_47e[0x04];
    short counter_482;
    short unknown_484;
    short floor_486;
    unsigned char unknown_488[0x04];
    short gate_48c;
    short blocker_48e;
    unsigned char unknown_490;
    unsigned char flag_491;
    unsigned char unknown_492[0x02];
    float scalar_494;
    short value_498;
    short value_49a;
    short value_49c;
    unsigned short field_49e;
    short value_4a0;
    short value_4a2;
    short field_4a4;
    short field_4a6;
    short gate_4a8;
    short gate_4aa;
    short gate_4ac;
    short field_4ae;
    unsigned char unknown_4b0[0x08];
    int state_4b8;
    float source_factor_4bc;
    float target_factor_4c0;
    float threshold_scale_4c4;
    float source_modifier_4c8;
    float source_modifier_4cc;
    float factor_4d0;
    float factor_4d4;
    float scale_4d8;
    float x_scale_4dc;
    float y_scale_4e0;
    unsigned char gate_4e4;
    unsigned char unknown_4e5;
    unsigned char gate_4e6;
    unsigned char unknown_4e7[0x03];
    unsigned char state_4ea;
    unsigned char unknown_4eb[0x02];
    unsigned char gate_4ed;
    unsigned char unknown_4ee[0x02];
    unsigned char spell_lookup_4f0[0x44];
    void *spell_nonzero_gate_534;
    unsigned char unknown_538[0x20];
    short counter_558;
    signed char state_55a;
    signed char state_55b;
    FighterSequenceController sequence_controller_55c;
    unsigned char unknown_570[0x94];
    signed char scalar_modifier_table_604[0x20];
    unsigned char unknown_624[0x28];
    int statistic_candidate_64c;
    int post_advance_value_650;
    unsigned char unknown_654;
    unsigned char statistic_enable_655;
    unsigned char unknown_656[0x02];
    void *owned_manager_658;
    unsigned char unknown_65c[0x48];
    float body_overlap_x_6a4;
    float body_overlap_y_6a8;
    float peer_component_6ac;
    void *field_6b0;
    int field_6b4;
    int field_6b8;
    int field_6bc;
    int field_6c0;
    int field_6c4;
    int field_6c8;
    int field_6cc;
    int field_6d0;
    int field_6d4;
    int field_6d8;
    int field_6dc;
    int field_6e0;
    int field_6e4;
    int field_6e8;
    int field_6ec;
    int field_6f0;
    int field_6f4;
    int field_6f8;
    int field_6fc;
    int field_700;
    int field_704;
    int field_708;
    unsigned char unknown_70c[0x18];
    int field_724;
    int field_728;
    signed char state_72c;

    void adjust_counter_482(short amount, int floor_value);
    void adjust_capped_counter_558(short amount);
    void apply_deferred_counter_558(short amount);
    void emit_fighter_effect_433cc0(
        int effect_code,
        float x,
        float y,
        int direction,
        int trailing_value);
    void advance_fighter_sequence_55c();
    unsigned char consume_spell_sequence_entry();
    void prepare_next_spell_sequence_entry();
    void initialize_fighter_battle_state();
    void initialize_fighter_spell_resources();
    void consume_counter_484_steps(char count);
    int select_outcome_path_from_frame_flags(unsigned frame_flags);
    signed char classify_fighter_x_boundary();
    int test_proposed_x_against_stage_height(float delta_x);
};

bool __fastcall update_fighter_facing_from_other_x(Fighter *fighter);

struct CollisionContext {
    unsigned char unknown_00[0x0c];
    Fighter *fighters[2];
    unsigned char unknown_14[0x08];
    int extent_1c;
    int extent_20;
    int extent_24;
    int extent_28;
    CollisionList family_0[2];
    CollisionList family_1[2];
    CollisionList family_2[2];
    int deferred_74[2];
    int deferred_7c[2];

    void reset_collision_extents();
    void accumulate_collision_extents(const int *first, const int *second);
    void accumulate_float_collision_extents(
        WorldAabb *first,
        WorldAabb *second);
    int test_and_accumulate_float_aabb_overlap(
        WorldAabb *first,
        WorldAabb *second);
    void transform_local_aabb_to_world(
        const ActorPosition *actor,
        const LocalAabb *local,
        WorldAabb *world);
    void accumulate_descriptor_extents(
        const struct CollisionAabb *first,
        const struct ShapeWords *descriptor,
        const struct CollisionAabb *second);
    void accumulate_descriptor_pair_extents(
        const struct CollisionAabb *first,
        const struct ShapeWords *first_descriptor,
        const struct CollisionAabb *second,
        const struct ShapeWords *second_descriptor);
    bool try_frame_flag_pair_outcome(
        AttackCandidate *candidate,
        Fighter *fighter);
    bool try_candidate_flag_outcome(
        AttackCandidate *candidate,
        Fighter *fighter);
    void emit_effect_at_collision_center(int effect_code, int direction);
    int test_descriptor_point_inside(
        const struct CollisionAabb *aabb,
        const struct ShapeWords *descriptor,
        int x,
        int y);
    int test_aabb_against_descriptor_shape(
        const struct CollisionAabb *first,
        const struct ShapeWords *descriptor,
        const struct CollisionAabb *second);
    int test_descriptor_shapes_overlap(
        const struct CollisionAabb *first,
        const struct ShapeWords *first_descriptor,
        const struct CollisionAabb *second,
        const struct ShapeWords *second_descriptor);
    int test_group_a_against_primary_box(
        CollisionObject *first,
        CollisionObject *second);
    int test_group_b_against_group_b(
        CollisionObject *source,
        CollisionObject *other);
    int test_group_a_against_group_b(
        CollisionObject *source,
        CollisionObject *other);
    bool try_group_a_vs_group_b_interaction(
        CollisionObject *source,
        CollisionObject *other);
    bool try_group_b_pair_response(
        CollisionObject *source,
        CollisionObject *other);
    void resolve_group_b_object_clash(
        CollisionObject *left,
        CollisionObject *right);
    void reset_hit_exchange_scratch(Fighter *owner, Fighter *fighter);
    void apply_terminal_outcome(
        AttackCandidate *candidate,
        Fighter *fighter);
    bool try_outcome_path_a(AttackCandidate *candidate, Fighter *fighter);
    bool try_outcome_path_b(AttackCandidate *candidate, Fighter *fighter);
    bool dispatch_outcome_path(AttackCandidate *candidate, Fighter *fighter);
    void resolve_general_attack_hit(
        AttackCandidate *candidate,
        Fighter *fighter);
    void apply_forwarded_quantity_to_pair(
        AttackCandidate *candidate,
        Fighter *fighter,
        int quantity,
        int scalar_per_thousand,
        short forwarded_counter_delta,
        signed char use_dynamic_scalar);
    void resolve_attack_candidate_against_fighter(
        AttackCandidate *candidate,
        Fighter *fighter);
    void dispatch_family2_against_family1();
    void dispatch_family1_object_clashes();
    void resolve_fighter_body_collision();
    void run_attack_projectile_collision_phase();
};

struct EffectSink {
    virtual void unknown_00();
    virtual void unknown_04();
    virtual void unknown_08();
    virtual void *emit_effect(
        int effect_code,
        float x,
        float y,
        int direction,
        int one,
        void *context);
    virtual void unknown_10();
    virtual void unknown_14();
    virtual void phase_18(int value);
};

extern EffectSink *g_effect_sink;

void __fastcall reset_fighter_fields_6bc_728(CollisionContext *context);
void __fastcall reset_fighter_fields_6b4_728(CollisionContext *context);
int __fastcall is_state_13c_in_32_95(Fighter *fighter);
int __fastcall is_state_13c_in_96_c7(Fighter *fighter);
int __fastcall is_positive_y_and_state_window(Fighter *fighter);
float __fastcall stage_surface_height_at_x(Fighter *fighter);
int __fastcall is_y_at_or_below_stage_surface(Fighter *fighter);
void dispatch_indexed_event(unsigned index);
void __fastcall prepare_collision_geometry_from_frame(void *object);

struct ActorPosition {
    unsigned char unknown_00[0xec];
    float x;
    float y;
    unsigned char unknown_f4[0x10];
    unsigned char facing;
};

struct LocalAabb {
    int left;
    int top;
    int right;
    int bottom;
};

struct CollisionAabb {
    int left;
    int top;
    int right;
    int bottom;
};

struct ShapeWords {
    int x0;
    int y0;
    int x1;
    int y1;
};

struct WorldAabb {
    float left;
    float top;
    float right;
    float bottom;
};

} // namespace th105
