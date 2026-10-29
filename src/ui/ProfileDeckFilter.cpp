// JP1.06a deck category selection. Native callable1375 bytes; full owned
// COFF1396 including alignment and five-way table is independently equal.
#include <map>
#include <deque>
#include "battle/SpellData.hpp"
#include "ui/UiPrimitives.hpp"
#include "ui/MenuCursor.hpp"
#include "input/InputManager.hpp"
#include "ui/MenuCursorBindings.cpp"
extern "C" th105::CInputManager *g_active_menu_input;
namespace th105 {
typedef std::map<int, SpellRecordView> FilterSpellMap;
typedef std::map<short, signed char> FilterCountMap;
// Native4300B0 is checked iterator subscripting, not deque.at: no _Xran edge.
// Declaration-only view preserves its observed out-of-line boundary.
struct FilterDequeSubscript { FilterSpellMap::iterator &operator[](unsigned index); };
// Pointer-only view, never constructed. Unaccessed ranges retain native offsets.
struct ProfileDeckFilterView {
 unsigned char prefix_00[0x44];
 UiDesignObject *objects_44[20];
 unsigned char gap_94[0x3b8-0x94];
 FilterSpellMap *local_tree_3b8;
 FilterSpellMap *common_tree_3bc;
 FilterCountMap counts_3c0;
 std::deque<FilterSpellMap::iterator> filtered_3cc;
 unsigned char color_3e0, total_3e1;
 MenuCursorState cursor_3e4, cursor_3f8;
 signed char category_40c;
 void select_filter(signed char category);
 int available_count(int index);
 void show_record(SpellRecordView *record);
};
void ProfileDeckFilterView::select_filter(signed char category)
{
 for (FilterCountMap::iterator it=counts_3c0.begin(); it!=counts_3c0.end();) {
  if (it->second==0) it=counts_3c0.erase(it);
  else ++it;
 }
 if (objects_44[7+category_40c])
  objects_44[7+category_40c]->enabled=false;
 switch(category) {
 case 0:
  filtered_3cc.clear();
  for(FilterSpellMap::iterator it=common_tree_3bc->begin();it!=common_tree_3bc->end();++it)
   filtered_3cc.push_back(it);
  for(FilterSpellMap::iterator it=local_tree_3b8->begin();it!=local_tree_3b8->end();++it)
   filtered_3cc.push_back(it);
  break;
 case 1:
  filtered_3cc.clear();
  for(FilterSpellMap::iterator it=common_tree_3bc->begin();it!=common_tree_3bc->end();++it)
   filtered_3cc.push_back(it);
  break;
 case 2:
  filtered_3cc.clear();
  for(FilterSpellMap::iterator it=local_tree_3b8->begin();it!=local_tree_3b8->end();++it)
   if(it->second.selector_1c==1) filtered_3cc.push_back(it);
  break;
 case 3:
  filtered_3cc.clear();
  for(FilterSpellMap::iterator it=local_tree_3b8->begin();it!=local_tree_3b8->end();++it)
   if(it->second.selector_1c==2) filtered_3cc.push_back(it);
  break;
 case 4:
  if(counts_3c0.empty()) {
   if(category_40c==0) select_filter(3);
   else select_filter(0);
   return;
  }
  filtered_3cc.clear();
  for(FilterSpellMap::iterator it=common_tree_3bc->begin();it!=common_tree_3bc->end();++it)
   if(counts_3c0.find(static_cast<short>(it->first))!=counts_3c0.end()) filtered_3cc.push_back(it);
  for(FilterSpellMap::iterator it=local_tree_3b8->begin();it!=local_tree_3b8->end();++it)
   if(counts_3c0.find(static_cast<short>(it->first))!=counts_3c0.end()) filtered_3cc.push_back(it);
  break;
 }
 category_40c=category;
 if(objects_44[7+category_40c]) objects_44[7+category_40c]->enabled=true;
 cursor_3e4.bind_vertical(g_active_menu_input, filtered_3cc.size(), 15);
 if(available_count(cursor_3e4.selection)) show_record(&(*reinterpret_cast<FilterDequeSubscript *>(&filtered_3cc))[cursor_3e4.selection]->second);
 else {
  objects_44[17]->enabled=false;
  objects_44[5]->enabled=false;
  objects_44[6]->enabled=false;
  objects_44[12]->enabled=false;
  objects_44[13]->enabled=false;
  objects_44[14]->enabled=false;
  objects_44[15]->enabled=false;
  objects_44[16]->enabled=false;
 }
}
}
