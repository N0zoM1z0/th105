#include "ui/SelectConstructor.hpp"
#include "ui/MenuCursor.hpp"
#include "battle/GameMode.hpp"

namespace th105 {


struct SelectEntryUiEnabledView { unsigned char unknown_00[0x14]; unsigned char enabled; };
struct SelectEntryConfigView {
    unsigned char unknown_00[0x64];
    int identifier_64;
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
    setup_00c=reinterpret_cast<SelectSetupEntryView *>(get_match_setup());
    if(previous_scene!=2)play_bgm(title_bgm_path);
    fields_090[0]=1;
    fields_090[1]=(get_game_mode()!=0 && get_game_mode()!=GAME_MODE_VS_COM) ? 1 : 0;
    MenuCursorState (*cursors)[2]=character_cursors_100;
    for(int side=0;side<2;++side) {
        inputs_010[side]=get_selected_input(side);
        if(inputs_010[side]) {
            CInputManager *input=inputs_010[side];
            input_018.sources_60.push_back(input);
        }
        CInputManager *bound=inputs_010[side];
        bind_cursor(&cursors[side][0],bound,4,false);
        bind_cursor(&cursors[side][1],bound,4,true);
    }
    SelectEntryUiEnabledView *primary=reinterpret_cast<SelectEntryUiEnabledView *>(slots_604[0]);
    fields_090[2]=1;
    primary->enabled=fields_090[0];
    reinterpret_cast<SelectEntryUiEnabledView *>(slots_604[1])->enabled=fields_090[1] &
        (get_game_mode()!=GAME_MODE_VS_PLAYER && get_game_mode()!=GAME_MODE_PRACTICE);
    bind_cursor(&stage_cursor_195c,&input_018,choice_count_094,true);
    bind_cursor(&variant_cursor_1970,&input_018,2,false);
    fields_7f8[0]=0;
    fields_7f8[1]=0;
    state_008=0;
    for(int side=0;side<2;++side) {
        if(setup_00c->random_4c[side]) {
            cursors[side][0].selection=3;
            cursors[side][1].selection=3;
            setup_00c->sides_08[side].character_key_00=15;
        } else {
            int character=setup_00c->sides_08[side].character_key_00;
            for(int index=0;index<15;++index) {
                if(character==select_entry_character_ids[index]) {
                    cursors[side][0].selection=index%4;
                    cursors[side][1].selection=index/4;
                    break;
                }
            }
        }
    }
    if(!setup_00c->random_4c[2]) {
        for(int i=0;i<choice_count_094;++i) {
            if(choices_098[i]==setup_00c->stage_04) {
                stage_cursor_195c.selection=i;
                break;
            }
        }
        if(variants_0a8[stage_cursor_195c.selection]!=setup_00c->bgm_05 &&
           select_ids_6288[stage_cursor_195c.selection]>=0)
            variant_cursor_1970.selection=1;
    }
    reinterpret_cast<SelectEntryUiEnabledView *>(slots_2cb8[2])->enabled=extras_0b8[stage_cursor_195c.selection]>=0;
    setup_00c->identifier_00=get_game_config()->identifier_64;
    bind_character(0,setup_00c->sides_08[0].character_key_00);
    bind_character(1,setup_00c->sides_08[1].character_key_00);
}
}
