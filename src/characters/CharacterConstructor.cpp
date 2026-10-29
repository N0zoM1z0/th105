// JP1.06a Character constructor-facing source. Full557 bytes remain nonexact
// only at the first sprite zero/EH-state store ordering. No original full
// roster subtype layout or opaque member destructor implementation is claimed.
#include "battle/AttackObject.hpp"
#include "battle/GameMode.hpp"
#include "battle/SpellData.hpp"
#include "ui/ProfileDeckResourceLifetime.hpp"
#include "ui/DesignBaseLifetime.hpp"

#include <new>
#include <stddef.h>
#include <vector>
#include <map>

namespace th105 {
class CharacterCtorSprite94 : public IColor {
public:
    CharacterCtorSprite94() {}
    virtual ~CharacterCtorSprite94() {}
    virtual void set_color(unsigned);
    virtual void set_vertex_colors(const unsigned *);
    virtual void multiply_color(unsigned);
    virtual void set_texture_options(unsigned, int, int, unsigned, unsigned, int, int);
    virtual void set_texture(unsigned, int, int, int, int);
    virtual void slot_18();
    virtual void render(float, float);
    SpriteVertex28 vertices_08[4];
    float width_78, height_7c, extension_80[5];
};

struct Header14 {
    unsigned allocator_00;
    void **blocks_04;
    unsigned capacity_08;
    unsigned head_0c;
    unsigned count_10;
    Header14() : blocks_04(0), capacity_08(0), head_0c(0), count_10(0) {}
};

struct CharacterSpellData68 {
    ProfileDeckResourceGroupNative20 core_00;
    Header14 loaded_20;
    Header14 selection_34;
    unsigned char values_48[0x20];
    ~CharacterSpellData68();
};

struct SequenceController14 {
    unsigned unknown_00;
    void **slots_04;
    unsigned capacity_08;
    unsigned head_0c;
    unsigned count_10;
    SequenceController14() : slots_04(0), capacity_08(0), head_0c(0), count_10(0) {}
    ~SequenceController14();
};

struct OwnedDeque65c {
    unsigned unknown_00;
    void **blocks_04;
    unsigned capacity_08;
    unsigned head_0c;
    unsigned count_10;
    OwnedDeque65c() : blocks_04(0), capacity_08(0), head_0c(0), count_10(0) {}
    ~OwnedDeque65c();
};

// Actual render-history owner occupies14 bytes;688 belongs to Character.
struct CharacterPhaseRender14 {
    CharacterPhaseRender14();
    ~CharacterPhaseRender14();
    unsigned char storage_00[0x14];
};

struct ScalarDeque68c {
    unsigned unknown_00;
    void **blocks_04;
    unsigned capacity_08;
    unsigned head_0c;
    unsigned count_10;
    ScalarDeque68c() : blocks_04(0), capacity_08(0), head_0c(0), count_10(0) {}
    ~ScalarDeque68c();
};

struct ShortDeque710 {
    unsigned unknown_00;
    short **blocks_04;
    unsigned capacity_08;
    unsigned head_0c;
    unsigned count_10;
    ShortDeque710() : blocks_04(0), capacity_08(0), head_0c(0), count_10(0) {}
    ~ShortDeque710();
};

struct SpriteHandleResource98 {
    unsigned handle_00;
    CharacterCtorSprite94 sprite_04;
    SpriteHandleResource98() : handle_00(0), sprite_04() {}
    ~SpriteHandleResource98();
};
typedef char SpriteHandleResource98_size[sizeof(SpriteHandleResource98) == 0x98 ? 1 : -1];

struct AnimationSequenceBlock;
typedef std::map<int, AnimationSequenceBlock *> ActionTree0c;

struct Element4 {
    unsigned value_00;
    Element4() : value_00(0) {}
};

class CharacterConstructorView : public ::AttackObject {
public:
    CharacterConstructorView(const MatchSetup::Side *setup);
    virtual ~CharacterConstructorView() = 0;

public:
    int character_key_330;
    unsigned char option_334;
    unsigned char option_335;
    unsigned char reserved_336[2];
    unsigned word_338;
    CharacterCtorSprite94 sprite_33c;
    SpriteHandleResource98 resource_3d0;
    unsigned char reserved_468[0x88];
    CharacterSpellData68 spell_data_4f0;
    short counter_558;
    signed char state_55a;
    signed char state_55b;
    SequenceController14 sequence_55c;
    CharacterCtorSprite94 sprite_570;
    unsigned char scalar_table_604[0x20];
    unsigned char reserved_624[0x28];
    int statistic_candidate_64c;
    int post_value_650;
    unsigned char byte_654;
    unsigned char byte_655;
    unsigned char reserved_656[2];
    void *owned_manager_658;
    OwnedDeque65c owned_deque_65c;
    unsigned field_670;
    CharacterPhaseRender14 subobject_674;
    unsigned unknown_688;
    ScalarDeque68c scalar_deque_68c;
    short word_6a0;
    unsigned char byte_6a2;
    unsigned char byte_6a3;
    float value_6a4;
    float value_6a8;
    float value_6ac;
    void *transition_link_6b0;
    unsigned char reserved_6b4[0x5c];
    ShortDeque710 history_710;
    int field_724;
    int field_728;
    signed char state_72c;
};

typedef char CharacterPhaseSize[sizeof(CharacterPhaseRender14)==0x14?1:-1];
typedef char CharacterSpellSize[sizeof(CharacterSpellData68)==0x68?1:-1];
typedef char C0[offsetof(CharacterConstructorView, character_key_330) == 0x330 ? 1 : -1];
typedef char C1[offsetof(CharacterConstructorView, sprite_33c) == 0x33c ? 1 : -1];
typedef char C2[offsetof(CharacterConstructorView, resource_3d0) + offsetof(SpriteHandleResource98, sprite_04) == 0x3d4 ? 1 : -1];
typedef char C3[offsetof(CharacterConstructorView, spell_data_4f0) == 0x4f0 ? 1 : -1];
typedef char C4[offsetof(CharacterConstructorView, sequence_55c) == 0x55c ? 1 : -1];
typedef char C5[offsetof(CharacterConstructorView, sprite_570) == 0x570 ? 1 : -1];
typedef char C6[offsetof(CharacterConstructorView, owned_deque_65c) == 0x65c ? 1 : -1];
typedef char C7[offsetof(CharacterConstructorView, subobject_674) == 0x674 ? 1 : -1];
typedef char C8[offsetof(CharacterConstructorView, scalar_deque_68c) == 0x68c ? 1 : -1];
typedef char C9[offsetof(CharacterConstructorView, history_710) == 0x710 ? 1 : -1];
typedef char CA[offsetof(CharacterConstructorView, state_72c) == 0x72c ? 1 : -1];

} // namespace th105


namespace th105 {

CharacterConstructorView::CharacterConstructorView(const MatchSetup::Side *setup)
    : word_338(0)
{
    // These are Character-owned pointers embedded in AttackObject storage.
    *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(this) + 0x16c) = this;
    *reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(this) + 0x168) = this;

    ActionTree0c *tree = new ActionTree0c;
    *reinterpret_cast<ActionTree0c **>(reinterpret_cast<unsigned char *>(this) + 0x160) = tree;

    std::vector<DesignTextureHandle> *triplet = new std::vector<DesignTextureHandle>;
    *reinterpret_cast<std::vector<DesignTextureHandle> **>(reinterpret_cast<unsigned char *>(this) + 0x130) = triplet;

    Element4 *elements = new Element4[64];
    *reinterpret_cast<Element4 **>(reinterpret_cast<unsigned char *>(this) + 0x164) = elements;

    transition_link_6b0 = 0;

    character_key_330 = setup->character_key_00;
    option_335 = setup->fighter_option_05;
    option_334 = setup->fighter_option_04;
    reinterpret_cast<SpellDataOwner *>(&spell_data_4f0)->initialize_side_payload_430f70(
        reinterpret_cast<const ShortDeque8 *>(setup->input_payload_08));
    transition_link_6b0 = setup->transition_link_1c;
    if (transition_link_6b0 == 0)
        state_72c = setup->fighter_category_06;
    else
        state_72c = 0;
}

} // namespace th105
