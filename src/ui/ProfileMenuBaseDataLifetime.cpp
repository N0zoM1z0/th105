#include <deque>
#include <string>
#include <stddef.h>

namespace th105 {

class ProfileIColorLifetime {
public:
    ProfileIColorLifetime() : value_04(0) {}
    virtual ~ProfileIColorLifetime() {}
    virtual void set_color(unsigned int) = 0;
    virtual void set_vertex_colors(const unsigned int *) = 0;
    virtual void multiply_color(unsigned int) = 0;
    unsigned int value_04;
};

struct ProfileSpriteVertexLifetime {
    float x, y, z, rhw;
    unsigned int color;
    float u, v;
};

class ProfileCSpriteBaseLifetime : public ProfileIColorLifetime {
public:
    virtual ~ProfileCSpriteBaseLifetime() {}
    virtual void set_color(unsigned int);
    virtual void set_vertex_colors(const unsigned int *);
    virtual void multiply_color(unsigned int);
    ProfileSpriteVertexLifetime vertices_08[4];
    float texture_width_78;
    float texture_height_7c;
};

class ProfileCSpriteLifetime : public ProfileCSpriteBaseLifetime {
public:
    ProfileCSpriteLifetime() {}
    virtual ~ProfileCSpriteLifetime() {}
    unsigned char copied_extension_080[0x14];
};

class ProfileInputManagerLifetime {
public:
    ProfileInputManagerLifetime();
    virtual ~ProfileInputManagerLifetime();
    virtual void update_player_input_counters_from_raw();
    unsigned char storage_004[0x5c];
};

class ProfileInputManagerExLifetime : public ProfileInputManagerLifetime {
public:
    ProfileInputManagerExLifetime() : ProfileInputManagerLifetime()
    {
        use_injected_input_064 = false;
        injected_mask_060 = 0;
    }
    virtual void build_player_logical_input_mask();
    unsigned short injected_mask_060;
    unsigned short resolved_mask_062;
    bool use_injected_input_064;
    unsigned char reserved_065[3];
};

struct ProfileMenuBaseDataLifetime {
    unsigned int texture_000;
    ProfileCSpriteLifetime sprite_004;
    std::string string_098;
    std::string string_0b4;
    ProfileInputManagerExLifetime input_0d0;
    ProfileInputManagerExLifetime *input_owner_138;
    unsigned char flag_13c;
    unsigned char reserved_13d[3];
    unsigned char block_140[0x34];
    unsigned char block_174[0x34];
    unsigned char flag_1a8;
    unsigned char reserved_1a9[3];
    std::deque<unsigned short> decks_1ac[20];

    ProfileMenuBaseDataLifetime();
    ~ProfileMenuBaseDataLifetime();
};

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
