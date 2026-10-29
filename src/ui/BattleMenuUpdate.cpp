// JP1.06a CMenuBattle update. Complete source; canonical owned extent remains nonexact.
#include "ui/Menu.hpp"
#include "ui/MenuCursor.hpp"
#include "ui/ProfileSubmenus.hpp"
#include "input/InputManager.hpp"
#include "input/InputSelection.hpp"
#include "config/GameConfig.hpp"
#include <vector>
extern "C" th105::CInputManager *g_active_menu_input;
extern "C" const char battle_save_select_prompt[], battle_save_title_prompt[], battle_save_success[];
namespace th105 {
void __cdecl dispatch_indexed_event(unsigned);
bool __cdecl is_menu_initial_press(unsigned char,bool,bool,bool);
void __cdecl install_menu_object(void *);
void refresh_continue_network_state();
struct BattlePauseOwner {
 unsigned char prefix_00[0x84];
 int end_pending_84;
};
struct BattlePauseConfig {
 unsigned char prefix_00[0x71];
 unsigned char auto_save_71;
};
struct BattlePauseEntries {
 int &operator[](unsigned index);
};
class BattleMenuUpdateView : public Menu {
public:
 virtual ~BattleMenuUpdateView();
 virtual bool update();
 virtual void render();
 signed char state_04;
 TitleDesignResource design_08;
 UiDesignObject *items_3c[5];
 MenuCursorState cursor_50;
 std::vector<int> entries_64;
 BattlePauseOwner *owner_74;
 int message_result();
 int confirmation_result();
};
#define ENTRY (*reinterpret_cast<BattlePauseEntries *>(&entries_64))[cursor_50.selection]
bool BattleMenuUpdateView::update()
{
 if(owner_74->end_pending_84) return true;
 HoldCounters *input=&g_active_menu_input->hold;
 switch(state_04) {
 case 0:
  if(cursor_50.update()) dispatch_indexed_event(39);
  if(input->buttons[0]==1) {
   dispatch_indexed_event(40);
   switch(ENTRY) {
   case 0:return false;
   case 1:
    install_menu_object(new CProfileKeyConfig(get_player_slot_record(0),0));
    return true;
   case 2:
    install_menu_object(new CProfileKeyConfig(get_player_slot_record(1),1));
    return true;
   case 3:
   case 4:
    if(get_session_setup_option()==1) {
     if(reinterpret_cast<BattlePauseConfig *>(get_game_config())->auto_save_71)
      refresh_continue_network_state();
     else {
      state_04=static_cast<signed char>(ENTRY)*10;
      if(ENTRY==3) show_profile_message(battle_save_select_prompt,false);
      else show_profile_message(battle_save_title_prompt,false);
      return true;
     }
    }
    if(ENTRY==3) owner_74->end_pending_84=1;
    else owner_74->end_pending_84=2;
    return true;
   }
  } else if(input->buttons[1]==1 || is_menu_initial_press(1,false,false,false)) {
   dispatch_indexed_event(41);
   return false;
  }
  return true;
 case 30:
 case 40:
  switch(message_result()) {
  case 3:
   ++state_04;
   refresh_continue_network_state();
   show_profile_result(battle_save_success);
   return true;
  case 4:
   if(state_04==30) owner_74->end_pending_84=1;
   else owner_74->end_pending_84=2;
   // Both native result4 branches join the result2 state reset.
  case 2:
   state_04=0;
   return true;
  }
  return true;
 case 31:
 case 41:
  if(confirmation_result()) {
   if(state_04==31) owner_74->end_pending_84=1;
   else owner_74->end_pending_84=2;
  }
  return true;
 }
 return true;
}
}
