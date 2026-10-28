#include "ui/SelectConstructor.hpp"
#include "ui/MenuCursor.hpp"
#include "battle/GameMode.hpp"

namespace th105 {
struct SelectSetupEntryView {
    int identifier_00;
    signed char stage_04,bgm_05;
    unsigned char unknown_06[2];
    MatchSetup::Side sides_08[2];
    unsigned seed_48;
    unsigned char random_4c[3];
};
struct SelectEntryPrefix {
    void *vptr_00;
    int scene_id_04,state_08;
    SelectSetupEntryView *setup_0c;
    CInputManager *inputs_10[2];
};
struct SelectEntryUiEnabledView { unsigned char unknown_00[0x14]; unsigned char enabled; };
struct SelectEntryConfigView {
    unsigned char unknown_00[0x64];
    int identifier_64;
};
struct SelectEntryCallView {
    void bind_character_41fb80(int side,int character);
};
CInputManager *get_selected_input(unsigned slot);
SelectEntryConfigView *get_game_config();
extern "C" void __cdecl play_bgm(const char *);
extern "C" const char title_bgm_path[];
extern "C" const int select_entry_character_ids[];
static void bind_cursor(MenuCursorState *cursor,CInputManager *input,int count,bool vertical)
{
    if(input)cursor->input_counter=&input->hold_38[vertical?1:0];
    else cursor->input_counter=0;
    cursor->selection=0;
    cursor->window_start=0;
    cursor->item_count=count;
    cursor->page_size=0;
}

void CSelect::on_scene_enter(int previous_scene)
{
    SelectEntryPrefix *prefix=reinterpret_cast<SelectEntryPrefix *>(this);
    prefix->setup_0c=reinterpret_cast<SelectSetupEntryView *>(get_match_setup());
    if(previous_scene!=2)play_bgm(title_bgm_path);
    fields_090[0]=1;
    fields_090[1]=(get_game_mode()!=0 && get_game_mode()!=GAME_MODE_VS_COM) ? 1 : 0;
    MenuCursorState (*cursors)[2]=reinterpret_cast<MenuCursorState (*)[2]>(fields_100);
    for(int side=0;side<2;++side) {
        prefix->inputs_10[side]=get_selected_input(side);
        if(prefix->inputs_10[side]) {
            CInputManager *input=prefix->inputs_10[side];
            input_018.sources_60.push_back(input);
        }
        CInputManager *bound=prefix->inputs_10[side];
        bind_cursor(&cursors[side][0],bound,4,false);
        bind_cursor(&cursors[side][1],bound,4,true);
    }
    SelectEntryUiEnabledView *primary=reinterpret_cast<SelectEntryUiEnabledView *>(slots_604[0]);
    fields_090[2]=1;
    primary->enabled=fields_090[0];
    reinterpret_cast<SelectEntryUiEnabledView *>(slots_604[1])->enabled=fields_090[1] &
        (get_game_mode()!=GAME_MODE_VS_PLAYER && get_game_mode()!=GAME_MODE_PRACTICE);
    MenuCursorState *stage_cursors=reinterpret_cast<MenuCursorState *>(fields_1954+8);
    bind_cursor(&stage_cursors[0],&input_018,choice_count_094,true);
    bind_cursor(&stage_cursors[1],&input_018,2,false);
    fields_7f8[0]=0;
    fields_7f8[1]=0;
    prefix->state_08=0;
    for(int side=0;side<2;++side) {
        if(prefix->setup_0c->random_4c[side]) {
            cursors[side][0].selection=3;
            cursors[side][1].selection=3;
            prefix->setup_0c->sides_08[side].character_key_00=15;
        } else {
            int character=prefix->setup_0c->sides_08[side].character_key_00;
            for(int index=0;index<15;++index) {
                if(character==select_entry_character_ids[index]) {
                    cursors[side][0].selection=index%4;
                    cursors[side][1].selection=index/4;
                    break;
                }
            }
        }
    }
    if(!prefix->setup_0c->random_4c[2]) {
        for(int i=0;i<choice_count_094;++i) {
            if(choices_098[i]==prefix->setup_0c->stage_04) {
                stage_cursors[0].selection=i;
                break;
            }
        }
        if(variants_0a8[stage_cursors[0].selection]!=prefix->setup_0c->bgm_05 &&
           select_ids_6288[stage_cursors[0].selection]>=0)
            stage_cursors[1].selection=1;
    }
    reinterpret_cast<SelectEntryUiEnabledView *>(slots_2cb8[2])->enabled=extras_0b8[stage_cursors[0].selection]>=0;
    prefix->setup_0c->identifier_00=get_game_config()->identifier_64;
    reinterpret_cast<SelectEntryCallView *>(this)->bind_character_41fb80(0,prefix->setup_0c->sides_08[0].character_key_00);
    reinterpret_cast<SelectEntryCallView *>(this)->bind_character_41fb80(1,prefix->setup_0c->sides_08[1].character_key_00);
}
}
