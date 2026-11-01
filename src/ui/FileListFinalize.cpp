// Complete CFileList page/render preparation; canonical root remains nonexact.
// Actual CTile copy lifetime is implicit over the corrected four-byte color base.
#include "ui/FileList.hpp"
#include "ui/Title.hpp"
#include "assets/TextFontOwner.hpp"
#include "battle/EffectSprite.hpp"
#include <string.h>
extern "C" const char profile_ui_effect_label[];
namespace th105 {
class FileListRenderTile : public CSpriteBase {
public:
 FileListRenderTile() {}
 void set_texture(unsigned,int,int,unsigned,unsigned);
 float e80,e84,e88,e8c,e90,e94,e98,e9c,ea0;
};
typedef char FinalizeTileSize[sizeof(FileListRenderTile)==0xa4?1:-1];
// Narrow declarations for the native out-of-line deque push and string assign.
// Their receiver/argument ABIs are unchanged; no replacement STL body is authored.
struct FileListUnsignedDequePushView { void push_back_value(const unsigned &); };
struct FileListStringAssignBytesView { std::string &assign_bytes(const char *,unsigned); };
void CFileList::finalize()
{
 TextFontOwner194 owner;
 TextFontConfig128 config;
 strcpy_s(config.face_000,256,profile_ui_effect_label);
 config.height_108=14;
 config.weight_10c=300;
 config.colors_100[0]=255;
 config.colors_100[1]=160;
 config.colors_100[2]=255;
 config.colors_100[3]=160;
 config.colors_100[4]=255;
 config.colors_100[5]=255;
 config.spacing_x_120=0;
 config.spacing_y_124=2;
 config.outline_111=1;
 owner.configure(&config);
 std::string text;
 std::deque<std::string>::iterator current=rows_004.begin();
 for(unsigned i=0;i<handles_02c.size();++i)
  g_title_resource_manager.release_title_resource_handle(handles_02c[i]);
 handles_02c.clear();
 render_items_040.clear();
 if(current!=rows_004.end()) {
  do {
   unsigned max_width=0;
   unsigned count=0;
   do {
    unsigned width=format_item(&text,current);
    if(max_width<width)max_width=width;
    text.append("<br>",4);
    ++current;
    ++count;
   } while(count<16 && current!=rows_004.end());
   int width=static_cast<int>(max_width*7+4);
   unsigned handle=g_title_resource_manager.create_text_texture(text.c_str(),&owner,width,256,0,0).value;
   reinterpret_cast<FileListUnsignedDequePushView *>(&handles_02c)->push_back_value(handle);
   FileListRenderTile tile;
   tile.set_texture(handle,0,0,width,16);
   reinterpret_cast<std::deque<FileListRenderTile> *>(&render_items_040)->push_back(tile);
   reinterpret_cast<FileListStringAssignBytesView *>(&text)->assign_bytes("",0);
  } while(current!=rows_004.end());
 }
}
}
