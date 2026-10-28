#include "ui/SelectConstructor.hpp"
#include "ui/MenuCursor.hpp"
#include "ui/MenuSelect.hpp"
#include "ui/UiSelectionState.hpp"
#include "battle/GameMode.hpp"

namespace th105 {
struct SelectUpdatePrefix {
    void *vptr_00;
    int scene_id_04,state_08;
    void *setup_0c;
    CInputManager *inputs_10[2];
};
struct SelectUpdateDispatch {
    virtual void slot00();virtual void slot04();virtual void slot08();
    virtual void slot0c();virtual void slot10();virtual void slot14();
    virtual int update_selection();
};
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
    SelectUpdatePrefix *prefix=reinterpret_cast<SelectUpdatePrefix *>(this);
    for(int i=0;i<2;++i) {
        if(prefix->inputs_10[i] && prefix->inputs_10[i]->hold_38[4]==1) {
            dispatch_indexed_event(40);
            install_menu_object(new CMenuSelect);
            return 3;
        }
    }
    if(is_menu_initial_press(1,false,false,false))return 2;
    SelectAssignmentFlags *assignment=reinterpret_cast<SelectAssignmentFlags *>(fields_7f8);
    if(get_game_mode()!=GAME_MODE_NETWORK_SERVER) {
        if(assignment->first==0)prefix->inputs_10[0]=get_selected_input(0);
        else prefix->inputs_10[0]=0;
        if(assignment->second>0)prefix->inputs_10[1]=get_selected_input(0);
        else prefix->inputs_10[1]=0;
        if(assignment->second==0 && assignment->first==1) {
            prefix->inputs_10[0]=get_selected_input(0);
            prefix->inputs_10[1]=0;
            assignment->first=0;
        }
    } else if(fields_090[2]) {
        rebind_selected_input_43b640(1,1);
        CInputManager *second=get_selected_input(1);
        if(second) {
            prefix->inputs_10[0]=get_selected_input(0);
            prefix->inputs_10[1]=second;
            fields_090[2]=0;
        } else if(get_selected_input_source(0)==-1) {
            if(assignment->first==0)prefix->inputs_10[0]=get_selected_input(0);
            else prefix->inputs_10[0]=0;
            if(assignment->second>0)prefix->inputs_10[1]=get_selected_input(0);
            else prefix->inputs_10[1]=0;
        } else {
            prefix->inputs_10[0]=get_selected_input(0);
            prefix->inputs_10[1]=0;
        }
    } else {
        prefix->inputs_10[0]=get_selected_input(0);
        prefix->inputs_10[1]=get_selected_input(1);
        if(!prefix->inputs_10[1])fields_090[2]=1;
    }
    MenuCursorState (*cursors)[2]=reinterpret_cast<MenuCursorState (*)[2]>(fields_100);
    bind_input(&cursors[0][0],&cursors[0][1],prefix->inputs_10[0]);
    bind_input(&cursors[1][0],&cursors[1][1],prefix->inputs_10[1]);
    input_018.sources_60.clear();
    if(prefix->inputs_10[0]) {
        CInputManager *input=prefix->inputs_10[0];
        input_018.sources_60.push_back(input);
    }
    if(prefix->inputs_10[1]) {
        CInputManager *input=prefix->inputs_10[1];
        input_018.sources_60.push_back(input);
    }
    return reinterpret_cast<SelectUpdateDispatch *>(this)->update_selection();
}
}
