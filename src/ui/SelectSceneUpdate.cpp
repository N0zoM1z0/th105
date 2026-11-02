#include "ui/SelectConstructor.hpp"
#include "ui/MenuCursor.hpp"
#include "ui/MenuSelect.hpp"
#include "ui/UiSelectionState.hpp"
#include "battle/GameMode.hpp"

namespace th105 {


struct SelectAssignmentFlags { signed char second; unsigned char first; };
CInputManager *get_selected_input(unsigned slot);
signed char get_selected_input_source(unsigned slot);
void __cdecl rebind_selected_input_43b640(int slot,signed char distinct);
void dispatch_indexed_event(unsigned);
void install_menu_object(void *);
extern "C" bool __cdecl is_menu_initial_press(unsigned char,bool,bool,bool);
extern "C" int g_scene_mode;
static void bind_input(MenuCursorState *horizontal,MenuCursorState *vertical,CInputManager *input)
{
    if(input)horizontal->input_counter=&input->hold_38[0];
    else horizontal->input_counter=0;
    if(input)vertical->input_counter=&input->hold_38[1];
    else vertical->input_counter=0;
}
int CSelect::update()
{
    if(has_ui_selection_state_changed())return g_scene_mode==2?2:3;
    for(int i=0;i<2;++i) {
        if(inputs_010[i] && inputs_010[i]->hold_38[4]==1) {
            dispatch_indexed_event(40);
            install_menu_object(new CMenuSelect);
            return 3;
        }
    }
    if(is_menu_initial_press(1,false,false,false))return 2;
    SelectAssignmentFlags *assignment=reinterpret_cast<SelectAssignmentFlags *>(fields_7f8);
    if(get_game_mode()!=GAME_MODE_NETWORK_SERVER) {
        if(assignment->first==0)inputs_010[0]=get_selected_input(0);
        else inputs_010[0]=0;
        if(assignment->second>0)inputs_010[1]=get_selected_input(0);
        else inputs_010[1]=0;
        if(assignment->second==0 && assignment->first==1) {
            inputs_010[0]=get_selected_input(0);
            inputs_010[1]=0;
            assignment->first=0;
        }
    } else if(fields_090[2]) {
        rebind_selected_input_43b640(1,1);
        CInputManager *second=get_selected_input(1);
        if(second) {
            inputs_010[0]=get_selected_input(0);
            inputs_010[1]=second;
            fields_090[2]=0;
        } else if(get_selected_input_source(0)==-1) {
            if(assignment->first==0)inputs_010[0]=get_selected_input(0);
            else inputs_010[0]=0;
            if(assignment->second>0)inputs_010[1]=get_selected_input(0);
            else inputs_010[1]=0;
        } else {
            inputs_010[0]=get_selected_input(0);
            inputs_010[1]=0;
        }
    } else {
        inputs_010[0]=get_selected_input(0);
        inputs_010[1]=get_selected_input(1);
        if(!inputs_010[1])fields_090[2]=1;
    }
    MenuCursorState (*cursors)[2]=character_cursors_100;
    bind_input(&cursors[0][0],&cursors[0][1],inputs_010[0]);
    bind_input(&cursors[1][0],&cursors[1][1],inputs_010[1]);
    input_018.sources_60.clear();
    if(inputs_010[0]) {
        CInputManager *input=inputs_010[0];
        input_018.sources_60.push_back(input);
    }
    if(inputs_010[1]) {
        CInputManager *input=inputs_010[1];
        input_018.sources_60.push_back(input);
    }
    return update_selection();
}
}
