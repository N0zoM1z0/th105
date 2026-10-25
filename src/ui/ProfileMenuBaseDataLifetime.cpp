#include "ProfileMenuBaseDataLifetime.hpp"

namespace th105 {

typedef char ProfileSprite_size_94[sizeof(ProfileCSpriteLifetime) == 0x94 ? 1 : -1];
typedef char ProfileInput_size_68[sizeof(ProfileInputManagerExLifetime) == 0x68 ? 1 : -1];
typedef char ProfileBase_input_off[offsetof(ProfileMenuBaseDataLifetime, input_0d0) == 0xd0 ? 1 : -1];
typedef char ProfileBase_decks_off[offsetof(ProfileMenuBaseDataLifetime, decks_1ac) == 0x1ac ? 1 : -1];
typedef char ProfileBase_size_33c[sizeof(ProfileMenuBaseDataLifetime) == 0x33c ? 1 : -1];

ProfileMenuBaseDataLifetime::ProfileMenuBaseDataLifetime()
    : texture_000(0), sprite_004(), string_098(), string_0b4(), input_0d0(),
      decks_1ac()
{
    texture_000 = 0;
    input_owner_138 = &input_0d0;
}

ProfileMenuBaseDataLifetime::~ProfileMenuBaseDataLifetime()
{
}

} // namespace th105
