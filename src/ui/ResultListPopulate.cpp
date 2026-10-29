// Complete JP1.06a ResultList population, with native containers and real
// per-append string temporaries. This pointer-only view is never allocated.
#include "ui/FileList.hpp"
#include "ui/ProfileDeckResourceLifetime.hpp"
#include "config/ScoreData.hpp"
#include <deque>
#include <string>
#include <vector>
#include <stddef.h>
extern "C" int __cdecl _sprintf_s(char *,unsigned,const char *,...);
extern "C" const char result_empty_row_format[],result_row_format[];
namespace th105 {
struct ResultRecord24 {
 int character_id,language,spell_id,maximum,current,frames;
};
struct ResultScoreState {
 unsigned char prefix[0x198];
 std::vector<ResultRecord24> records[15];
};
class ResultListPopulateView : public CFileList {
public:
 virtual void populate();
 int character_id_b4;
 std::deque<std::string> indices_b8;
 std::deque<int> labels_cc;
 std::deque<int> values_e0;
 std::deque<short> metadata_f4;
};
typedef char ResultRecordSize[sizeof(ResultRecord24) == 24 ? 1 : -1];
typedef char ResultListViewSize[sizeof(ResultListPopulateView) == 0x108 ? 1 : -1];
typedef char ResultListIndexOffset[offsetof(ResultListPopulateView, indices_b8) == 0xb8 ? 1 : -1];
typedef char ResultListReplayOffset[offsetof(ResultListPopulateView, metadata_f4) == 0xf4 ? 1 : -1];
void ResultListPopulateView::populate()
{
 rows_004.clear();indices_b8.clear();labels_cc.clear();metadata_f4.clear();
 unsigned short languages[4]={'E','N','H','L'};
 ProfileDeckResourceGroupNative20 names;
 int loaded_character=15;
 for(unsigned index=0;index<reinterpret_cast<ResultScoreState *>(get_score_data())->records[character_id_b4].size();++index) {
  ResultRecord24 &record=reinterpret_cast<ResultScoreState *>(get_score_data())->records[character_id_b4][index];
  if(record.character_id!=loaded_character) {
   loaded_character=record.character_id;
   reinterpret_cast<SpellDataOwner *>(&names)->load_spell_csv_via_32e20(loaded_character,1,0);
  }
  SpellRecordView *spell=reinterpret_cast<SpellDataOwner *>(&names)->find_local_then_common_spell_record(record.spell_id);
  if(spell) {
   char row[1024];
   if(record.maximum!=0) {
    _sprintf_s(row,sizeof(row),result_row_format,spell->name_00.c_str(),
     reinterpret_cast<char *>(languages+record.language),record.current,record.maximum,
     record.frames/60,record.frames*100/60%100);
    metadata_f4.push_back(static_cast<unsigned short>(record.spell_id));
   } else {
    _sprintf_s(row,sizeof(row),result_empty_row_format);
    metadata_f4.push_back(-1);
   }
   rows_004.push_back(std::string(row));
   indices_b8.push_back(std::string(row));
   labels_cc.push_back(loaded_character);
   values_e0.push_back(record.language);
  }
 }
 reinterpret_cast<SpellDataOwner *>(&names)->clear_spell_entries();
 finalize();
}
}
