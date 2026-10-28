#include "battle/GameMode.hpp"
#include "input/InputSelection.hpp"
#include "input/InputManager.hpp"

namespace th105 {
extern "C" __declspec(dllimport) void *__stdcall CreateEventA(void *,int,int,const char *);
extern "C" __declspec(dllimport) unsigned __stdcall WaitForSingleObject(void *,unsigned);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);
extern "C" bool __cdecl is_menu_initial_press(unsigned char,bool,bool,bool);
struct SelectEventWait {
    void *handle;
    unsigned wait_ms;
    SelectEventWait():handle(CreateEventA(0,0,0,0)),wait_ms(16){}
    ~SelectEventWait(){CloseHandle(handle);}
    void wait(){WaitForSingleObject(handle,wait_ms);}
};
struct SelectNetworkSessionView {
    virtual void slot00(); virtual void slot04();
    virtual void publish_setup(MatchSetup *);
    virtual bool accept_setup(MatchSetup *);
    virtual void slot10(); virtual void process_ready(); virtual void slot18();
    virtual void advance(); virtual void slot20();
    virtual bool continue_transition();
    virtual bool reached_state(int);
    virtual void slot2c(); virtual void slot30();
    virtual void select_index(int);
    virtual void slot38(); virtual bool disconnected();
    virtual bool ready();
    unsigned char unknown_004[0x200];
    unsigned state_204,state_208;
};
struct SelectNetworkInputView {
    virtual void slot00();
    virtual void update();
};
struct SelectNetworkSceneView {
    virtual void slot00();
    virtual int update_client();
    virtual void slot08(); virtual void slot0c();
    virtual void on_enter(int previous_scene);
    virtual void slot14();
    virtual int update_selection();
    unsigned char unknown_004[8];
    MatchSetup *setup_00c;
    SelectNetworkInputView *first_010,*second_014;
    unsigned char unknown_018[0x2ec0];
    unsigned char pending_2ed8;
    void enter_base_421120(int);
};

void SelectNetworkSceneView::on_enter(int previous_scene)
{
    SelectNetworkSessionView *session=reinterpret_cast<SelectNetworkSessionView *>(get_network_session());
    SelectEventWait event;
    while(!session->reached_state(3)) {
        if(session->disconnected())break;
        event.wait();
    }
    session->state_208=session->state_204;
    enter_base_421120(previous_scene);
    pending_2ed8=0;
}

int SelectNetworkSceneView::update_client()
{
    SelectNetworkSessionView *session=reinterpret_cast<SelectNetworkSessionView *>(get_network_session());
    if(get_game_mode()!=GAME_MODE_NETWORK_WATCH ||
       is_menu_initial_press(1,false,false,false) || session->disconnected())
        return 2;
    if(g_direct_input_backend.is_raw_key_down(0x2a) ||
       g_direct_input_backend.is_raw_key_down(0x36)) {
        for(int i=0;i<9;++i) {
            if(g_direct_input_backend.is_raw_key_down(static_cast<unsigned char>(i)+2))
                session->select_index(i);
        }
    }
    if(pending_2ed8) {
        if(session->ready()) {
            session->process_ready();
            if(session->accept_setup(setup_00c))return 11;
        }
    } else {
        session->advance();
        while(session->continue_transition()) {
            first_010->update();
            second_014->update();
            if(update_selection()==6) {
                session->publish_setup(setup_00c);
                pending_2ed8=1;
                break;
            }
        }
    }
    return 9;
}
}
