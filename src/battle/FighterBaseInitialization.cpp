#include "AttackObject.hpp"
#include "Collision.hpp"
#include "GameMode.hpp"

#include <new>

namespace th105 {

namespace {

// These are address-qualified target services, not proposed original names.
// Their incomplete types are deliberately confined to this constructor packet.
extern "C" void __stdcall construct_opaque_array_401250(
    void *destination,
    unsigned count,
    unsigned element_size,
    void (__cdecl *constructor)(void *));

extern void *g_character_vtable_461ac4;
extern void *g_sprite_vtable_461adf;
extern void (__cdecl *g_opaque_element_ctor_461c3a)(void *);

inline unsigned char *bytes(Fighter *fighter)
{
    return reinterpret_cast<unsigned char *>(fighter);
}

inline void store_u32(Fighter *fighter, unsigned offset, unsigned value)
{
    *reinterpret_cast<unsigned *>(bytes(fighter) + offset) = value;
}

inline void store_ptr(Fighter *fighter, unsigned offset, void *value)
{
    *reinterpret_cast<void **>(bytes(fighter) + offset) = value;
}

inline void store_byte(Fighter *fighter, unsigned offset, unsigned char value)
{
    bytes(fighter)[offset] = value;
}

struct ShortTreeHeader {
    void *allocator_00;
    void *sentinel_04;
    unsigned count_08;
};

struct SpellDataOwnerInitializationView {
    void initialize_42d750();
    void initialize_input_430f70(const void *payload);
};

struct FighterSubobject674View {
    void initialize_459630();
};

struct ShortTreeAllocationView {
    void *allocate_nil_43a830();
};

struct OpaqueDwordTriplet {
    unsigned unknown_00;
    unsigned zero_04;
    unsigned zero_08;
    unsigned zero_0c;
};

} // namespace

Fighter *Fighter::initialize_fighter_base_from_setup(
    const MatchSetup::Side *setup)
{
    new (this) AttackObject();
    store_ptr(this, 0x000, g_character_vtable_461ac4);

    // Three embedded CSprite-compatible headers: target stores their vtable
    // and clears the observed scalar tails instead of invoking a standalone
    // constructor.
    store_u32(this, 0x338, 0);
    store_u32(this, 0x340, 0);
    store_ptr(this, 0x33c, g_sprite_vtable_461adf);
    store_u32(this, 0x3d0, 0);
    store_u32(this, 0x3d8, 0);
    store_ptr(this, 0x3d4, g_sprite_vtable_461adf);

    void *spell_data = bytes(this) + 0x4f0;
    reinterpret_cast<SpellDataOwnerInitializationView *>(spell_data)
        ->initialize_42d750();
    store_u32(this, 0x514, 0);
    store_u32(this, 0x518, 0);
    store_u32(this, 0x51c, 0);
    store_u32(this, 0x520, 0);
    store_u32(this, 0x528, 0);
    store_u32(this, 0x52c, 0);
    store_u32(this, 0x530, 0);
    store_u32(this, 0x534, 0);

    store_u32(this, 0x560, 0);
    store_u32(this, 0x564, 0);
    store_u32(this, 0x568, 0);
    store_u32(this, 0x56c, 0);
    store_u32(this, 0x574, 0);
    store_ptr(this, 0x570, g_sprite_vtable_461adf);

    store_u32(this, 0x660, 0);
    store_u32(this, 0x664, 0);
    store_u32(this, 0x668, 0);
    store_u32(this, 0x66c, 0);
    reinterpret_cast<FighterSubobject674View *>(bytes(this) + 0x674)
        ->initialize_459630();
    store_u32(this, 0x690, 0);
    store_u32(this, 0x694, 0);
    store_u32(this, 0x698, 0);
    store_u32(this, 0x69c, 0);
    store_u32(this, 0x714, 0);
    store_u32(this, 0x718, 0);
    store_u32(this, 0x71c, 0);
    store_u32(this, 0x720, 0);

    // The three allocation-backed members are observed as a checked tree, an
    // all-zero 0x10-byte header, and a 64-by-4 opaque array.  Their element
    // semantics remain unresolved, so no invented container facade appears.
    store_ptr(this, 0x168, this);
    store_ptr(this, 0x16c, this);
    ShortTreeHeader *tree = static_cast<ShortTreeHeader *>(operator new(0x0c));
    if (tree) {
        tree->sentinel_04 =
            reinterpret_cast<ShortTreeAllocationView *>(tree)->allocate_nil_43a830();
        reinterpret_cast<unsigned char *>(tree->sentinel_04)[0x15] = 1;
        *reinterpret_cast<void **>(static_cast<unsigned char *>(tree->sentinel_04) + 0x04) = tree->sentinel_04;
        *reinterpret_cast<void **>(tree->sentinel_04) = tree->sentinel_04;
        *reinterpret_cast<void **>(static_cast<unsigned char *>(tree->sentinel_04) + 0x08) = tree->sentinel_04;
        tree->count_08 = 0;
    }
    store_ptr(this, 0x160, tree);

    OpaqueDwordTriplet *triplet =
        static_cast<OpaqueDwordTriplet *>(operator new(0x10));
    if (triplet) {
        triplet->zero_04 = 0;
        triplet->zero_08 = 0;
        triplet->zero_0c = 0;
    }
    store_ptr(this, 0x130, triplet);

    void *opaque_array = operator new(0x100);
    if (opaque_array) {
        construct_opaque_array_401250(
            opaque_array, 4, 0x40, g_opaque_element_ctor_461c3a);
    }
    store_ptr(this, 0x164, opaque_array);

    store_u32(this, 0x6b0, 0);
    store_u32(this, 0x330, static_cast<unsigned>(setup->character_key_00));
    store_byte(this, 0x335, setup->fighter_option_05);
    store_byte(this, 0x334, setup->fighter_option_04);
    reinterpret_cast<SpellDataOwnerInitializationView *>(spell_data)
        ->initialize_input_430f70(setup->input_payload_08);
    store_ptr(this, 0x6b0, setup->transition_link_1c);
    store_byte(
        this,
        0x72c,
        setup->transition_link_1c == 0 ? setup->fighter_category_06 : 0);
    return this;
}

} // namespace th105
