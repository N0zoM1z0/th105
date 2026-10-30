#include "input/InputSelection.hpp"
#include "ui/Title.hpp"
#include "ui/UiPrimitives.hpp"
#include "ui/MenuCursorBindings.cpp"
#include <deque>
#include <string>
extern "C" unsigned char profile_editor_records[];
namespace th105 {
struct ConnectHistoryConfig { unsigned char prefix[0x48]; std::deque<std::string> history; };
class CMenuConnectHistoryListView {
public:
 unsigned char prefix[0x2fc];
 unsigned texture;
 UiTileA4 tile;
 std::deque<std::string> rows;
 unsigned char gap_3b8[0x2c];
 MenuCursorState cursor;
 unsigned char gap_3f8[0x850];
 ConnectHistoryConfig *config;
 bool load_history_list_4434b0();
};
typedef char ConfigOffset[offsetof(CMenuConnectHistoryListView,config)==0xc48?1:-1];
bool CMenuConnectHistoryListView::load_history_list_4434b0()
{
 g_title_resource_manager.release_title_resource_handle(texture);
 texture=0;
 rows.clear();
 if(config->history.empty())return false;
 std::string text;
 for(unsigned i=0;i<config->history.size();++i){
  rows.push_back(config->history[i]);
  text+=config->history[i]+"<br>";
 }
 texture=g_title_resource_manager.create_text_texture(text.c_str(),profile_editor_records,256,256,0,0).value;
 tile.set_texture(texture,0,0,256,16);
 cursor.bind_vertical(reinterpret_cast<CInputManager *>(get_combined_menu_input()),rows.size(),1);
 return true;
}
}
