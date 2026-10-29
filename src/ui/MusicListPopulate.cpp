// JP1.06a MusicList population: real CSV/string/deque lifetimes and locked label.
#include "ui/MenuMusic.hpp"
#include "assets/CsvReader.hpp"
#include "config/ScoreData.hpp"
#include <set>
extern "C" const char music_csv_path[];
namespace th105 {
struct MusicCsvReader : CsvReader {
 MusicCsvReader() {
  row_map_04=0;row_map_capacity_08=0;row_start_0c=0;row_count_10=0;
  outer_iterator_aux_14=0;outer_iterator_owner_18=0;outer_row_position_1c=0;
  inner_iterator_aux_20=0;current_row_24=0;current_field_position_28=0;
 }
};
typedef char MusicCsvReaderSize[sizeof(MusicCsvReader) == 0x30 ? 1 : -1];
struct ScoreMusicLookupView {
 unsigned char prefix[0x44];
 std::set<unsigned> path_hashes_044;
 bool contains_bgm_path(const char *);
};
void MusicList::populate()
{
 rows_004.clear();
 paths_b4.clear();
 titles_c8.clear();
 MusicCsvReader reader;
 reader.load(music_csv_path);
 do {
  std::string title,path;
  reader.next_string(&path);
  paths_b4.push_back(path);
  reader.next_string(&title);
  if(reinterpret_cast<ScoreMusicLookupView *>(get_score_data())->contains_bgm_path(path.c_str()))
   rows_004.push_back(title);
  else
   rows_004.push_back(std::string("<color 808080>\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48\x81\x48</color>"));
 } while(reader.advance_row());
 finalize();
}
}
