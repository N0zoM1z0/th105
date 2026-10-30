#include "assets/FileReader.cpp"
#include "ui/Title.hpp"
#include "ui/UiPrimitives.hpp"
#include "input/InputSelection.hpp"
#include <deque>
#include <string>
#include <cstring>
extern "C" const char connect_address_list_path[];
extern "C" unsigned char profile_editor_records[];
namespace th105 {
struct AddressFileHandleView { void *vtable; FileHandle file; unsigned last; };
class CMenuConnectAddressListView {
public:
 unsigned char prefix[0x2fc];
 unsigned texture;
 UiTileA4 tile;
 std::deque<std::string> rows;
 unsigned char gap_3b8[0x2c];
 MenuCursorState cursor;
 bool load_address_list_443130();
};
typedef char RowsOffset[offsetof(CMenuConnectAddressListView,rows)==0x3a4?1:-1];
typedef char CursorOffset[offsetof(CMenuConnectAddressListView,cursor)==0x3e4?1:-1];
bool CMenuConnectAddressListView::load_address_list_443130()
{
 g_title_resource_manager.release_title_resource_handle(texture);
 texture=0;
 rows.clear();
 CFileReader file(connect_address_list_path);
 if(!reinterpret_cast<AddressFileHandleView *>(&file)->file)return false;
 if(!file.size())return false;
 char *buffer=new char[file.size()+1];
 buffer[file.size()]=0;
 file.read(buffer,file.size());
 char delimiters[]="\r\n";
 char *context;
 std::string text;
 char *token=strtok_s(buffer,delimiters,&context);
 if(!token)return false;
 text.append(token,std::strlen(token));
 text.append("<br>",4);
 rows.push_back(std::string(token));
 for(int i=1;i<16;++i){
  token=strtok_s(0,delimiters,&context);
  if(!token)break;
  text.append(token,std::strlen(token));
  text.append("<br>",4);
  rows.push_back(std::string(token));
 }
 delete[] buffer;
 texture=g_title_resource_manager.create_text_texture(text.c_str(),profile_editor_records,256,256,0,0).value;
 tile.set_texture(texture,0,0,256,16);
 cursor.bind_vertical(reinterpret_cast<CInputManager *>(get_combined_menu_input()),rows.size(),1);
 return true;
}
}
