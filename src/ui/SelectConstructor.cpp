// Complete JP1.06a4231A0 hypothesis, including natural member unwinding.
#include "SelectConstructor.hpp"
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *,const char *,...);
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
// Same real helper and native checked iterator as the accepted 40CC50 body.
// Its visibility tests the four constant-ID inline sites versus loop ID200+i.
void CDesignBase::find_object(UiDesignObject **object, int object_id)
{
 std::map<unsigned int, UiDesignObject *>::iterator it=object_tree_20.find(object_id);
 if(it==object_tree_20.end()) *object=0; else *object=it->second;
}
CSelect::CSelect()
 : background_2b4(0),names_34c(0),random_names_3f4(0),field_60c(0),
   pictures_19b8(),names_19f8(),music_2ccc(0)
{
 unsigned width,height;
 char path[260];char name[128];
 background_2b4=reinterpret_cast<SelectTextureCall *>(&g_title_resource_manager)->load_texture(select_ctor_bg,&width,&height);
 reinterpret_cast<SelectSpriteCall *>(&background_2b8)->set_texture_14(background_2b4,0,0,width,height);
 names_34c=reinterpret_cast<SelectTextureCall *>(&g_title_resource_manager)->load_texture(select_ctor_names,&width,&height);
 names_350.set_texture(names_34c,0,0,256,64);
 random_names_3f4=reinterpret_cast<SelectTextureCall *>(&g_title_resource_manager)->load_texture(select_ctor_rnd_names,&width,&height);
 reinterpret_cast<SelectSpriteCall *>(&random_names_3f8)->set_texture_14(random_names_3f4,0,0,256,64);
 reinterpret_cast<SelectDesignCall *>(&character_design_150)->load_10(select_ctor_character_design);
 int flags;
 unsigned char *network=static_cast<unsigned char *>(get_network_session());
 if(network) {
  slots_610[0]=network+0x27c;slots_610[1]=network+0x310;
  flags=AT(network,int,0x3b0);locked_093=false;
 } else {
  slots_610[0]=static_cast<unsigned char *>(get_player_slot_record(0))+4;
  slots_610[1]=static_cast<unsigned char *>(get_player_slot_record(1))+4;
  flags=AT(get_score_data(),int,4);locked_093=flags==0;
 }
 for(int i=0;i<16;++i) { character_design_150.bind_object_alt(&slots_5bc[i],i+100);slots_5bc[i]->enabled=true; }
 if(locked_093) { slots_5bc[13]->enabled=false;slots_5bc[14]->enabled=false; }
 if(flags&0x100) {
  for(int i=0;i<16;++i) { choices_098.push_back(select_ids_6208[i]);variants_0a8.push_back(select_ids_6248[i]);extras_0b8.push_back(select_ids_6288[i]); }
 } else if(flags!=0) {
  for(int i=0;i<7;++i) { choices_098.push_back(select_ids_6208[i]);variants_0a8.push_back(select_ids_6248[i]);int extra=-1;extras_0b8.push_back(extra); }
 } else {
  for(int i=0;i<5;++i) { choices_098.push_back(select_ids_6208[i]);variants_0a8.push_back(select_ids_6248[i]);int extra=-1;extras_0b8.push_back(extra); }
 }
 choice_count_094=choices_098.size();
 for(int i=0;i<2;++i) {
  wsprintfA(path,select_ctor_cursor_format,i+1);
  cursor_textures_184[i]=reinterpret_cast<SelectTextureCall *>(&g_title_resource_manager)->load_texture(path,&width,&height);
  reinterpret_cast<SelectSpriteCall *>(&cursor_images_18c[i])->set_texture_14(cursor_textures_184[i],0,0,width,height);
  character_design_150.find_object(&slots_5fc[i],i+200);
  character_design_150.bind_object_alt(&slots_604[i],i+300);
 }
 character_design_150.find_object(&anchor_618,400);
 back_textures_61c[0]=reinterpret_cast<SelectTextureCall *>(&g_title_resource_manager)->load_texture(select_ctor_back1,&width,&height);
 back_textures_61c[1]=reinterpret_cast<SelectTextureCall *>(&g_title_resource_manager)->load_texture(select_ctor_back2,&width,&height);
 for(int i=0;i<2;++i) {
  reinterpret_cast<SelectSpriteTextureCall *>(&back_images_624[i])->set_texture_options(back_textures_61c[i],0,0,width,height,0,0);
  back_images_624[i].reset_transform();back_images_624[i].translate(anchor_618->x,anchor_618->y,0);
 }
 reinterpret_cast<SelectDesignCall *>(&background_design_1984)->load_10(select_ctor_bg_design);
 for(int i=0;i<choice_count_094;++i) {
  wsprintfA(path,select_ctor_bg_picture_format,choices_098[i]);
  pictures_19b8[i]=reinterpret_cast<SelectTextureCall *>(&g_title_resource_manager)->load_texture(path,&width,&height);
  reinterpret_cast<SelectSpriteCall *>(&picture_images_1a38[i])->set_texture_14(pictures_19b8[i],0,0,width,height);
  wsprintfA(path,select_ctor_bg_name_format,choices_098[i]);
  names_19f8[i]=reinterpret_cast<SelectTextureCall *>(&g_title_resource_manager)->load_texture(path,&width,&height);
  reinterpret_cast<SelectSpriteCall *>(&name_images_2378[i])->set_texture_14(names_19f8[i],0,0,width,height);
 }
 music_2ccc=reinterpret_cast<SelectTextureCall *>(&g_title_resource_manager)->load_texture(select_ctor_music,&width,&height);
 music_2cd0.set_texture(music_2ccc,0,0,512,16);
 background_design_1984.find_object(&background_anchor_2cc4,100);
 background_design_1984.find_object(&background_anchor_2cc8,200);
 background_design_1984.find_object(&music_anchor_2d74,300);
 for(int i=0;i<3;++i) background_design_1984.bind_object_alt(&slots_2cb8[i],i+500);
 slots_2cb8[0]->enabled=true;slots_2cb8[1]->enabled=true;
 field_2d84=0;field_2d80=0;field_2d7c=0;field_2d78=false;field_7f4=0;
 if(static_cast<int>(get_game_mode())==4 || static_cast<int>(get_game_mode())==5) { guides_2d88[0].load(3);guides_2d88[1].load(4); }
 else { guides_2d88[0].load(90);guides_2d88[1].load(91); }
 for(int i=0;i<15;++i) {
  wsprintfA(name,select_ctor_palette_format,character_key_to_name(i),0);
  reinterpret_cast<SelectPaletteCall *>(&g_bootstrap_mode)->load_palette(name,select_palette_6fa258,16);
  wsprintfA(name,select_ctor_stand_format,character_key_to_name(i));
  SelectEffectCall *manager=reinterpret_cast<SelectEffectCall *>(&effects_7fc[i][0]);
  manager->load_04(name,0);
  manager->spawn_0c(0,static_cast<float>(slots_604[0]->x+32.0),static_cast<float>(slots_604[0]->y+8.0),1,0,0);
  manager->spawn_0c(0,static_cast<float>(slots_604[1]->x+32.0),static_cast<float>(slots_604[1]->y+8.0),1,1,0);
 }
}
#undef AT
}
