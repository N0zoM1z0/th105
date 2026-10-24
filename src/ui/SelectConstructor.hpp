#pragma once
#include "engine/SceneBase.hpp"
#include "ui/Title.hpp"
#include "ui/UiPrimitives.hpp"
#include "ui/GuideOverlay.hpp"
#include "ui/DesignBaseLifetime.hpp"
#include "battle/EffectSprite.hpp"
#include "battle/EffectManager.hpp"
#include <string>
#include <deque>
#include <vector>
#include <stddef.h>
namespace th105 {
// Complete0x60 base storage: accepted input constructor/destructor evidence.
struct CInputManager {
 CInputManager(); virtual ~CInputManager();
 virtual void update_player_input_counters_from_raw();
 unsigned char bindings_04[0x34]; int hold_38[10];
};
struct CInputManagerCluster : CInputManager {
 virtual void update_player_input_counters_from_raw();
 std::deque<CInputManager *> sources_60;
 signed char active_source_74;
};
// Pointer-only call views, never embedded or instantiated.
struct SelectDesignCall { virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();virtual void load_10(const char *); };
struct SelectSpriteCall { virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();virtual void slot10();virtual void set_texture_14(unsigned,int,int,int,int); };
struct SelectSpriteTextureCall { public:void set_texture_options(unsigned,int,int,unsigned,unsigned,int,int); };
struct SelectEffectCall {
 virtual void slot00();virtual void load_04(const char *,unsigned);
 virtual void slot08();virtual void *spawn_0c(int,float,float,unsigned char,unsigned char,int);
};
// 404C90 writes/returns the hidden four-byte class result and RET16.
struct SelectTextureCall { DesignTextureHandle load_texture(const char *,unsigned *,unsigned *); };
struct SelectPaletteCall { void load_palette(const char *,const unsigned char *,int); };
extern bool g_bootstrap_mode;
extern "C" const int select_ids_6208[],select_ids_6248[],select_ids_6288[];
extern "C" const unsigned char select_palette_6fa258[];
extern "C" const char select_ctor_bg[],select_ctor_names[],select_ctor_rnd_names[],select_ctor_character_design[];
extern "C" const char select_ctor_cursor_format[],select_ctor_back1[],select_ctor_back2[],select_ctor_bg_design[];
extern "C" const char select_ctor_bg_picture_format[],select_ctor_bg_name_format[],select_ctor_music[];
extern "C" const char select_ctor_palette_format[],select_ctor_stand_format[];
extern "C" void *get_network_session();
extern "C" void *get_player_slot_record(int);
extern "C" void *get_score_data();
extern "C" const char *character_key_to_name(unsigned);
class CSelect : public CSceneBase {
public:
 CSelect(); virtual ~CSelect();
 virtual int update();virtual bool render();virtual void unknown_scene_method();
 virtual void on_scene_enter(int);virtual void on_scene_exit(int);
 // Full2ED8 allocation is separately observed in the accepted scene factory.
 // Unknown uninitialized byte ranges are layout evidence, not shaping locals.
 unsigned char fields_008[0x10];
 CInputManagerCluster input_018;
 unsigned char fields_090[3];bool locked_093;
 int choice_count_094;
 std::vector<int> choices_098,variants_0a8,extras_0b8;
 std::string strings_0c8[2];
 unsigned char fields_100[0x50];
 CDesignBase character_design_150;
 DesignTextureHandle cursor_textures_184[2];UiSprite94 cursor_images_18c[2];
 DesignTextureHandle background_2b4;UiSprite94 background_2b8;
 DesignTextureHandle names_34c;UiTileA4 names_350;
 DesignTextureHandle random_names_3f4;UiSprite94 random_names_3f8;
 DesignTextureHandle extra_textures_48c[2];UiSprite94 extra_images_494[2];
 UiDesignObject *slots_5bc[16];
 UiDesignObject *slots_5fc[2];UiDesignObject *slots_604[2];
 int field_60c;void *slots_610[2];UiDesignObject *anchor_618;
 DesignTextureHandle back_textures_61c[2];CSpriteEx back_images_624[2];
 int field_7f4;unsigned char fields_7f8[4];
 CEffectManager<CSelectObject> effects_7fc[15][2];
 unsigned char fields_1954[0x30];
 CDesignBase background_design_1984;
 DesignTextureHandle pictures_19b8[16],names_19f8[16];
 UiSprite94 picture_images_1a38[16],name_images_2378[16];
 UiDesignObject *slots_2cb8[3];UiDesignObject *background_anchor_2cc4,*background_anchor_2cc8;
 DesignTextureHandle music_2ccc;UiTileA4 music_2cd0;
 UiDesignObject *music_anchor_2d74;bool field_2d78;
 int field_2d7c;float field_2d80,field_2d84;
 GuideOverlay guides_2d88[2];
};
#define CHECK_FIELD(n,o) typedef char SelectLayout_##n[(offsetof(CSelect,n)==o)?1:-1]
CHECK_FIELD(input_018,0x18);CHECK_FIELD(choices_098,0x98);
CHECK_FIELD(strings_0c8,0xc8);CHECK_FIELD(character_design_150,0x150);
CHECK_FIELD(cursor_images_18c,0x18c);CHECK_FIELD(background_2b8,0x2b8);
CHECK_FIELD(names_350,0x350);CHECK_FIELD(random_names_3f8,0x3f8);
CHECK_FIELD(extra_images_494,0x494);CHECK_FIELD(slots_5bc,0x5bc);
CHECK_FIELD(back_images_624,0x624);CHECK_FIELD(effects_7fc,0x7fc);
CHECK_FIELD(background_design_1984,0x1984);CHECK_FIELD(pictures_19b8,0x19b8);
CHECK_FIELD(names_19f8,0x19f8);CHECK_FIELD(picture_images_1a38,0x1a38);
CHECK_FIELD(name_images_2378,0x2378);CHECK_FIELD(music_2cd0,0x2cd0);
CHECK_FIELD(guides_2d88,0x2d88);
typedef char SelectCompleteStorage[(sizeof(CSelect)==0x2ed8)?1:-1];
#undef CHECK_FIELD
}
