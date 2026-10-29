// Complete JP1.06a Character destruction, including both cold range-error tails.
// Natural source905 bytes differs only in one commutative SIB operand byte.
#include "battle/AttackObjectLifetime.cpp"
#include "battle/PatResourceContracts.hpp"
#include "ui/Title.hpp"
#include "ui/DesignBaseLifetime.hpp"
#include "ui/ProfileDeckResourceLifetime.hpp"
#include <deque>
#include <list>
#include <map>
#include <vector>
#include <stddef.h>
namespace th105 {
class CharacterDtorSprite94 : public IColor {
public:
 virtual ~CharacterDtorSprite94() {}
 virtual void set_color(unsigned);
 virtual void set_vertex_colors(const unsigned *);
 virtual void multiply_color(unsigned);
 virtual void set_texture_options(unsigned,int,int,unsigned,unsigned,int,int);
 virtual void set_texture(unsigned,int,int,int,int);
 virtual void slot18();
 virtual void render(float,float);
 SpriteVertex28 vertices_08[4];
 float width_78,height_7c,extension_80[5];
};
struct CharacterSpriteResource98 {
 unsigned handle;
 CharacterDtorSprite94 sprite;
 ~CharacterSpriteResource98();
};
struct CharacterDtorSpell68 {
 ProfileDeckResourceGroupNative20 core;
 std::deque<short> loaded,selection;
 unsigned char values_48[0x20];
 void clear_resources();
 ~CharacterDtorSpell68() { clear_resources(); }
};
struct CharacterSequenceRecord98 {
 short id;
 unsigned short flags;
 CharacterDtorSprite94 sprite;
};
struct CharacterPhaseRecordEC {
 CSpriteEx sprite;
 signed char blend;
};
struct CharacterPhaseOwner14 {
 std::list<CharacterPhaseRecordEC> entries;
 signed char period;
 unsigned char unused_0d;
 short alpha_divisor;
 unsigned mask;
};
struct CharacterWaveHandle4 {
 unsigned value;
 CharacterWaveHandle4() : value(0) {}
};
struct CharacterOwnedManager {
 virtual ~CharacterOwnedManager();
};
struct OpaqueWaveHandleService {
 unsigned char release_handle(unsigned);
};
extern OpaqueWaveHandleService g_wave_handle_service;
struct AnimationSequenceBlock;
typedef std::map<int,AnimationSequenceBlock *> CharacterActionTree;
// Typed accessed base prefix; no overlay instance is constructed.
struct CharacterBaseResourcesView {
 unsigned char prefix_000[0x130];
 std::vector<DesignTextureHandle> *textures_130;
 unsigned char gap_134[0x2c];
 CharacterActionTree *actions_160;
 CharacterWaveHandle4 *waves_164;
};
class CharacterDestructionView : public ::AttackObject {
public:
 virtual ~CharacterDestructionView() = 0;
 int character_key_330;
 unsigned char options_334[4];
 unsigned texture_338;
 CharacterDtorSprite94 sprite_33c;
 CharacterSpriteResource98 resource_3d0;
 unsigned char gap_468[0x88];
 CharacterDtorSpell68 spells_4f0;
 unsigned char counters_558[4];
 std::deque<CharacterSequenceRecord98> sequence_55c;
 CharacterDtorSprite94 sprite_570;
 unsigned char gap_604[0x54];
 CharacterOwnedManager *manager_658;
 std::deque<PatGroup> groups_65c;
 unsigned field_670;
 CharacterPhaseOwner14 phase_674;
 unsigned field_688;
 std::deque<unsigned> textures_68c;
 unsigned char gap_6a0[0x70];
 std::deque<short> history_710;
};
typedef char CharacterDtorSequence[offsetof(CharacterDestructionView,sequence_55c)==0x55c?1:-1];
typedef char CharacterDtorPhase[offsetof(CharacterDestructionView,phase_674)==0x674?1:-1];
typedef char CharacterDtorTextures[offsetof(CharacterDestructionView,textures_68c)==0x68c?1:-1];
typedef char CharacterDtorHistory[offsetof(CharacterDestructionView,history_710)==0x710?1:-1];
CharacterDestructionView::~CharacterDestructionView()
{
 CharacterBaseResourcesView *resources=reinterpret_cast<CharacterBaseResourcesView *>(this);
 for(unsigned i=0;i<resources->textures_130->size();++i)
  g_title_resource_manager.release_title_resource_handle(resources->textures_130->at(i));
 resources->textures_130->clear();
 for(unsigned i=0;i<textures_68c.size();++i)
  g_title_resource_manager.release_title_resource_handle(textures_68c.at(i));
 textures_68c.clear();
 g_title_resource_manager.release_title_resource_handle(texture_338);
 for(unsigned i=0;i<64;++i)
  g_wave_handle_service.release_handle(resources->waves_164[i].value);
 delete[] resources->waves_164;
 delete manager_658;
 delete resources->textures_130;
 delete resources->actions_160;
}
}
