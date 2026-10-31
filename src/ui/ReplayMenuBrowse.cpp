// JP1.06a446860: complete browse policy; common GS-return tail remains nonexact.
#include "ui/ReplayMenu.hpp"
#include "input/InputManager.hpp"
extern "C" th105::CInputManager *g_active_menu_input;
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *,const char *,...);
namespace th105 {
void dispatch_indexed_event(unsigned);
struct ReplayHeaderServiceView {bool load_recording(const char *);};
ReplayHeaderServiceView *get_replay_header_service();
struct ReplayBrowseRuntimeView {
    template<class T> T &field(unsigned n) {return *reinterpret_cast<T *>(reinterpret_cast<unsigned char *>(this)+n);}
    unsigned char update_browse_state();
    void refresh_file_list();
};
unsigned char ReplayBrowseRuntimeView::update_browse_state()
{
    HoldCounters *input=&g_active_menu_input->hold;
    if(input->horizontal==1) {
        dispatch_indexed_event(39);
        field<MenuCursorState>(0x110).move_page_forward();
    } else if(input->horizontal==-1) {
        dispatch_indexed_event(39);
        field<MenuCursorState>(0x110).move_page_backward();
    } else if(field<MenuCursorState>(0x110).update()) dispatch_indexed_event(39);
    if(input->buttons[0]==1) {
        dispatch_indexed_event(40);
        if(field<CReplayList>(8).row_is_directory(field<MenuCursorState>(0x110).selection)) {
            field<std::list<int> >(0x274).push_back(field<MenuCursorState>(0x110).selection);
            field<CReplayList>(8).enter_directory(field<MenuCursorState>(0x110).selection);
            refresh_file_list();
        } else if(field<CReplayList>(8).row_at(field<MenuCursorState>(0x110).selection)) {
            const char *name=field<CReplayList>(8).row_at(field<MenuCursorState>(0x110).selection)->c_str();
            const char *directory=field<CReplayList>(8).current_directory()->c_str();
            char path[260];
            wsprintfA(path,"%s/%s",directory,name);
            if(get_replay_header_service()->load_recording(path)) g_scene_mode=6;
        }
    } else if(input->buttons[1]==1) {
        dispatch_indexed_event(41);
        if(field<CReplayList>(8).go_parent_directory()) {
            field<signed char>(4)=0;
            field<UiDesignObject *>(0xf4)->set_color(0xffffffffu);
            field<UiDesignObject *>(0xf8)->set_color(0xffffffffu);
        } else {
            field<MenuCursorState>(0x110).selection=field<std::list<int> >(0x274).back();
            field<std::list<int> >(0x274).pop_back();
            refresh_file_list();
        }
    }
    return 1;
}
}
