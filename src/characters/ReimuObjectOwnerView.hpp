#pragma once

// JP1.06a496540 runtime owner view. Lifecycle and original nominal identities
// remain unqualified; the unused380 slot deliberately retains unknown type.
#include "characters/CharacterObject.hpp"
#include <deque>
#include <stddef.h>

class Reimu;

namespace th105 { namespace reimu_object_model {

struct MotionFields {
    float velocity_x, velocity_y;
    unsigned char unknown_08[4];
    float acceleration_y;
};

// Observed sprite storage with motion fields already used by the real owner.
// These model names do not assert original C++ nominal identities.
class EffectSpriteView : public ::CSpriteEx {
public:
    float object_x_0e8, object_y_0ec;
    union {
        unsigned char unknown_0f0[0x10];
        MotionFields motion_0f0;
    };
    signed char object_facing_100;
    unsigned char unknown_101[3];
    float reset_zero_104, reset_zero_108;
    unsigned color_10c;
    int reset_zero_110;
    unsigned char unknown_114[4];
    float reset_one_118, reset_one_11c;
    float reset_zero_120, reset_zero_124, reset_zero_128;
};

class AnimationObjectBaseView {
public:
    EffectSpriteView effect_000;
};

class AnimationObjectView : public AnimationObjectBaseView, public ::Environment {
public:
    virtual ~AnimationObjectView() throw();
    virtual void set_action_sequence(short action, int sequence);
    virtual void set_action(short action);
    virtual void select_sequence(int sequence) = 0;
    virtual void reset_sequence() = 0;
    virtual unsigned char next_sequence_block() = 0;
    virtual void previous_sequence_block() = 0;
    virtual void set_sequence_frame(short frame) = 0;
    virtual unsigned char next_sequence_frame() = 0;
    virtual void previous_sequence_frame() = 0;
    virtual void dispatch_action_state() = 0;
    virtual void render_main();
    virtual void render_to_battle_scene();
    virtual void prepare_render_transform();
    virtual void render_color_mode();
    void *pointer_154;
};

class AttackObjectView : public AnimationObjectView {
public:
    virtual ~AttackObjectView() throw();
    virtual void set_action_sequence(short action, int sequence);
    virtual void set_action(short action);
    virtual void select_sequence(int sequence);
    virtual void reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual void previous_sequence_block();
    virtual void set_sequence_frame(short frame);
    virtual unsigned char next_sequence_frame();
    virtual void previous_sequence_frame();
    virtual void initialize_action_entry() = 0;
    virtual void object_idle();
    ::AttackObjectState state_158;
};

class CharacterObjectView : public ::CObjectBase, public AttackObjectView {
public:
    virtual ~CharacterObjectView();
    unsigned field_338;
    unsigned char field_33c;
    unsigned char unknown_33d[3];
    unsigned *copied_words_340;
    short field_344, field_346;
};

template <typename FighterType, typename ObjectType>
class CharacterObjectExView : public CharacterObjectView {
public:
    virtual ~CharacterObjectExView();
    void *owner_348;
    ObjectType *parent_34c;
    std::deque<ObjectType *> child_refs_350;
    short state_364, state_366, state_368, state_36a, state_36c;
    float state_370, state_374, state_378, state_37c;
    unsigned char unknown_380[4];
    short state_six_counter_384, phase_counter_386;
};

class ReimuObject : public CharacterObjectExView< ::Reimu, ReimuObject> {
public:
    virtual void dispatch_action_state();
    virtual void initialize_action_entry();
    void publish_battle_layout_scalar(float value);
    int has_crossed_stage_surface_while_descending();
};

typedef char MotionSize[sizeof(MotionFields)==0x10?1:-1];
typedef char SpriteSize[sizeof(EffectSpriteView)==0x12c?1:-1];
typedef char SpriteMotion[offsetof(EffectSpriteView,motion_0f0)==0xf0?1:-1];
typedef char AnimationSize[sizeof(AnimationObjectView)==0x158?1:-1];
typedef char SpriteOffset[offsetof(AnimationObjectView,effect_000)==4?1:-1];
typedef char AttackSize[sizeof(AttackObjectView)==0x330?1:-1];
typedef char CommonSize[sizeof(CharacterObjectView)==0x348?1:-1];
typedef char OwnerSize[sizeof(ReimuObject)==0x388?1:-1];
typedef char OwnerParameters[offsetof(ReimuObject,copied_words_340)==0x340?1:-1];
typedef char OwnerParent[offsetof(ReimuObject,parent_34c)==0x34c?1:-1];
typedef char OwnerChildren[offsetof(ReimuObject,child_refs_350)==0x350?1:-1];
typedef char AbsoluteX[offsetof(ReimuObject,effect_000)+offsetof(EffectSpriteView,object_x_0e8)==0xec?1:-1];
typedef char AbsoluteY[offsetof(ReimuObject,effect_000)+offsetof(EffectSpriteView,object_y_0ec)==0xf0?1:-1];
typedef char AbsoluteVelocityX[offsetof(ReimuObject,effect_000)+offsetof(EffectSpriteView,motion_0f0)+offsetof(MotionFields,velocity_x)==0xf4?1:-1];
typedef char AbsoluteVelocityY[offsetof(ReimuObject,effect_000)+offsetof(EffectSpriteView,motion_0f0)+offsetof(MotionFields,velocity_y)==0xf8?1:-1];
typedef char AbsoluteAccelerationY[offsetof(ReimuObject,effect_000)+offsetof(EffectSpriteView,motion_0f0)+offsetof(MotionFields,acceleration_y)==0x100?1:-1];
typedef char AbsoluteFacing[offsetof(ReimuObject,effect_000)+offsetof(EffectSpriteView,object_facing_100)==0x104?1:-1];
typedef char OwnerState[offsetof(ReimuObject,state_364)==0x364?1:-1];
typedef char OwnerFloat[offsetof(ReimuObject,state_370)==0x370?1:-1];
typedef char OwnerUnknown[offsetof(ReimuObject,unknown_380)==0x380?1:-1];
typedef char OwnerCounter[offsetof(ReimuObject,state_six_counter_384)==0x384?1:-1];

} } // namespace th105::reimu_object_model
