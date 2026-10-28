#include "ui/SelectConstructor.hpp"
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *,const char *,...);
namespace th105 {
extern "C" const char select_character_portrait_format[];
struct SelectCharacterSpriteView : CSpriteBase {
    virtual void slot10();
    virtual void set_texture_14(unsigned,int,int,unsigned,unsigned);
    float pivot_x,pivot_y,scale_x,scale_y,angle;
};
struct SelectCharacterBindingView : CSelect {
    void bind_character_41fb80(int side,int character);
};
void SelectCharacterBindingView::bind_character_41fb80(int side,int character)
{
    g_title_resource_manager.release_title_resource_handle(extra_textures_48c[side]);
    extra_textures_48c[side]=0;
    void **selected_effects=reinterpret_cast<void **>(fields_1954);
    selected_effects[side]=0;
    if(character!=15) {
        char path[260];
        unsigned width,height;
        wsprintfA(path,select_character_portrait_format,character_key_to_name(character));
        unsigned texture=reinterpret_cast<SelectTextureCall *>(&g_title_resource_manager)
            ->load_texture(path,&width,&height);
        SelectCharacterSpriteView *sprite=reinterpret_cast<SelectCharacterSpriteView *>(&extra_images_494[side]);
        extra_textures_48c[side]=texture;
        sprite->set_texture_14(texture,0,0,width,height);
        if(side!=0) {
            sprite->scale_x=-1.0f;
            sprite->scale_y=1.0f;
        }
        selected_effects[side]=&effects_7fc[character][0];
    }
}
}
