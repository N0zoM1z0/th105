// JP1.06a CMenuBattle constructor; complete800-byte source remains six stack-home bytes nonexact.
#include "ui/Menu.hpp"
#include "ui/MenuCursor.hpp"
#include "ui/MenuCursorBindings.cpp"
#include "ui/UiPrimitives.hpp"
#include "ui/DesignBaseLifetime.hpp"
#include "battle/GameMode.hpp"
#include <vector>
extern "C" th105::CInputManager *g_active_menu_input;
extern "C" const char battle_menu_story_path[], battle_menu_normal_path[], battle_menu_practice_path[];
namespace th105 {
struct BattleController;
class BattleMenuConstructorView : public Menu {
public:
 BattleMenuConstructorView(BattleController *owner);
 virtual ~BattleMenuConstructorView();
 virtual void unknown_menu_method();
 virtual bool update();
 virtual void render();
 signed char state_04;
 CDesignBase design_08;
 UiDesignObject *items_3c[5];
 MenuCursorState cursor_50;
 std::vector<int> menu_entries_64;
 BattleController *owner_74;
};
typedef char BattleMenuSize[sizeof(BattleMenuConstructorView)==0x78?1:-1];
BattleMenuConstructorView::BattleMenuConstructorView(BattleController *owner)
 : owner_74(owner)
{
 menu_entries_64.clear();
 if(get_game_mode()==0 || get_game_mode()==1 || get_game_mode()==2) {
  design_08.load(battle_menu_story_path);
  menu_entries_64.push_back(0);
  menu_entries_64.push_back(1);
  menu_entries_64.push_back(3);
  menu_entries_64.push_back(4);
  for(unsigned i=0;i<menu_entries_64.size();++i) {
   design_08.bind_object_alt(&items_3c[i],100+10*i);
   items_3c[i]->enabled=true;
  }
 } else if(get_game_mode()==7) {
  design_08.load(battle_menu_practice_path);
  menu_entries_64.push_back(0);
  menu_entries_64.push_back(1);
  menu_entries_64.push_back(4);
  for(unsigned i=0;i<menu_entries_64.size();++i) {
   design_08.bind_object_alt(&items_3c[i],100+10*i);
   items_3c[i]->enabled=true;
  }
 } else {
  design_08.load(battle_menu_normal_path);
  menu_entries_64.push_back(0);
  menu_entries_64.push_back(1);
  menu_entries_64.push_back(2);
  menu_entries_64.push_back(3);
  menu_entries_64.push_back(4);
  for(unsigned i=0;i<menu_entries_64.size();++i) {
   design_08.bind_object_alt(&items_3c[i],100+10*i);
   items_3c[i]->enabled=true;
  }
 }
 cursor_50.bind_vertical(g_active_menu_input,menu_entries_64.size(),0);
 state_04=0;
}
}
