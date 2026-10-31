// JP1.06a444830: complete connect main-state policy and owning regex lifetimes.
// See docs/CONNECT_MAIN_STATE_EXACT_2026_10_31.md.
#include "ui/Menu.hpp"
#include "ui/MenuCursor.hpp"
#include "input/InputManager.hpp"
#include "platform/SystemUtilities.hpp"
#include <string>
#include <vector>
#include <stddef.h>
extern "C" th105::CInputManager *g_active_menu_input;
extern "C" const char connect_main_select_prompt[]="\x90\xda\x91\xb1\x90\xe6\x82\xf0\x91\x49\x91\xf0\x82\xb5\x82\xc4\x82\xad\x82\xbe\x82\xb3\x82\xa2";
extern "C" const char connect_main_join_suffix[]="\x20\x82\xd6\x90\xda\x91\xb1\x82\xb5\x82\xdc\x82\xb7";
extern "C" const char connect_main_regex[]="(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\:(\\d{1,5})";
namespace th105 {
// Current4449AC prepares the existing path/text service receiver for40D160.
struct ClipboardModulePathView {void read_clipboard(char *,unsigned);};
void dispatch_indexed_event(unsigned);
bool is_menu_initial_press(unsigned char,bool,bool,bool);
// Ordinary external library contracts. The observed owning subobjects retain
// their true lifetime and layout; no library implementation is claimed here.
struct RegexSharedOwner { void *object; void *control; };
struct RegexSubMatch {
    std::string::const_iterator first, last;
    bool matched;
};
class EndpointRegex {
public:
    EndpointRegex(const char *, unsigned);
    ~EndpointRegex();
private:
    RegexSharedOwner expression;
};
class EndpointMatches {
public:
    explicit EndpointMatches(const std::allocator<RegexSubMatch> &);
    ~EndpointMatches();
    std::string str(int) const;
private:
    std::vector<RegexSubMatch> matches;
    std::string::const_iterator base;
    RegexSubMatch unmatched;
    RegexSharedOwner named_subexpressions;
    int last_closed_paren;
};
typedef char CheckRegexSize[sizeof(EndpointRegex)==8?1:-1];
typedef char CheckSubMatchSize[sizeof(RegexSubMatch)==20?1:-1];
typedef char CheckMatchesSize[sizeof(EndpointMatches)==56?1:-1];
bool search_endpoint(const std::string &, EndpointMatches &, const EndpointRegex &, unsigned);
struct ConnectMainConfig {
    unsigned char unknown_00[0x38];
    unsigned server_port_38;
    unsigned short address_3c[4];
    unsigned remote_port_44;
};
class ConnectMainStateView : public Menu {
public:
    template<class T> T &field(unsigned n) {return *reinterpret_cast<T *>(reinterpret_cast<unsigned char *>(this)+n);}
    bool update_main_state();
    unsigned reset_host_editor();
    void begin_endpoint_edit();
    bool load_address_list();
    bool load_history_list();
    void parse_endpoint(const std::string &);
};
bool ConnectMainStateView::update_main_state()
{
    HoldCounters *input=&g_active_menu_input->hold;
    if(field<MenuCursorState>(0x3bc).update()) dispatch_indexed_event(39);
    if(input->buttons[0]==1) {
        dispatch_indexed_event(40);
        field<signed char>(9)=0;
        switch(field<MenuCursorState>(0x3bc).selection) {
        case 0:
            field<unsigned>(0x428)=field<ConnectMainConfig *>(0xc48)->server_port_38;
            field<signed char>(8)=1;
            reset_host_editor();
            break;
        case 1:
            for(int i=0;i<4;++i)
                field<unsigned short>(0x420+2*i)=field<ConnectMainConfig *>(0xc48)->address_3c[i];
            field<unsigned>(0x428)=field<ConnectMainConfig *>(0xc48)->remote_port_44;
            field<signed char>(8)=2;
            begin_endpoint_edit();
            break;
        case 2:
            if(load_address_list()) {
                show_profile_result(connect_main_select_prompt);
                field<signed char>(8)=3;
            }
            break;
        case 3:
            if(load_history_list()) {
                show_profile_result(connect_main_select_prompt);
                field<signed char>(8)=4;
            }
            break;
        case 4: {
            char clipboard[1024];
            reinterpret_cast<ClipboardModulePathView *>(&g_module_path_text)
                ->read_clipboard(clipboard,sizeof(clipboard));
            std::string text(clipboard);
            EndpointRegex pattern(connect_main_regex,0);
            EndpointMatches matches((std::allocator<RegexSubMatch>()));
            if(search_endpoint(text,matches,pattern,0)) {
                field<signed char>(8)=5;
                std::string message;
                message=matches.str(0)+connect_main_join_suffix;
                parse_endpoint(matches.str(0));
                show_profile_message(message.c_str(),true);
            }
            break;
        }
        case 5:field<signed char>(8)=6;break;
        case 6:return false;
        }
    } else if(input->buttons[1]==1) {
        dispatch_indexed_event(41);
        return false;
    }
    if(is_menu_initial_press(1,false,false,false)) {
        dispatch_indexed_event(41);
        return false;
    }
    return true;
}
}
