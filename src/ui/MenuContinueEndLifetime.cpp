#include "DesignBaseLifetime.hpp"
#include "Menu.hpp"

extern "C" const char menu_continue_design_path[];
extern "C" const char menu_end_design_path[];

namespace th105 {

struct ContinueOwnerView {
    unsigned char unknown_000[0xa4];
    unsigned char active_a4;
};

struct ContinueGameConfigView {
    unsigned char unknown_000[0x71];
    unsigned char continue_flag_71;
};

ContinueGameConfigView *get_game_config_for_continue();
void refresh_continue_network_state();
struct CNetworkBase;
CNetworkBase *get_network_session_for_menu_end();
extern unsigned char g_menu_end_flag;

class CMenuContinue : public Menu {
public:
    explicit CMenuContinue(void *owner);
    virtual ~CMenuContinue();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();

private:
    unsigned char state_04;
    CDesignBase design_08;
    void *owner_3c;
};

CMenuContinue::CMenuContinue(void *owner) : owner_3c(owner)
{
    design_08.load(menu_continue_design_path);
    ContinueOwnerView *owner_view = static_cast<ContinueOwnerView *>(owner);
    if (owner_view->active_a4 == 0) {
        if (get_game_config_for_continue()->continue_flag_71 != 0)
            refresh_continue_network_state();
        else {
            state_04 = 0;
            return;
        }
    }
    state_04 = 10;
}

CMenuContinue::~CMenuContinue()
{
    design_08.virtual_cleanup();
}

class CMenuEnd : public Menu {
public:
    explicit CMenuEnd(void *owner);
    virtual ~CMenuEnd();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();

private:
    // Both callees ignore ECX, but current menu call sites preserve a Menu
    // receiver.  Member views retain that caller-proved source ABI.
    void initialize_runtime_4404f0();
    void hide_profile_message_43f8d0();

    unsigned char state_04;
    CDesignBase design_08;
    void *owner_3c;
};

CMenuEnd::CMenuEnd(void *owner) : owner_3c(owner)
{
    design_08.load(menu_end_design_path);
    state_04 = 0;
    initialize_runtime_4404f0();
    hide_profile_message_43f8d0();
    if (get_network_session_for_menu_end() != 0)
        g_menu_end_flag = 1;
}

CMenuEnd::~CMenuEnd()
{
    g_menu_end_flag = 0;
    design_08.virtual_cleanup();
}

typedef char CMenuContinue_size_must_be_0x40[
    sizeof(CMenuContinue) == 0x40 ? 1 : -1];
typedef char CMenuEnd_size_must_be_0x40[
    sizeof(CMenuEnd) == 0x40 ? 1 : -1];

} // namespace th105
