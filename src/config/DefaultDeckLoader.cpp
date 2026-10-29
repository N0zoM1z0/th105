// JP1.06a default character deck CSV loader; complete target463-byte body.
#include "assets/CsvReader.hpp"
#include <deque>
#include <string>
namespace th105 {
const char *__cdecl character_key_to_name(int);
struct DeckCsvReader : CsvReader {
 DeckCsvReader() {
  row_map_04=0;row_map_capacity_08=0;row_start_0c=0;row_count_10=0;
  outer_iterator_aux_14=0;outer_iterator_owner_18=0;outer_row_position_1c=0;
  inner_iterator_aux_20=0;current_row_24=0;current_field_position_28=0;
 }
};
typedef char DeckCsvReaderSize[sizeof(DeckCsvReader) == 0x30 ? 1 : -1];
// Existing profile/battle callers use a member boundary; the receiver is not
// accessed. The original nominal class owner remains unknown.
struct DefaultDeckLoaderView {
 std::deque<unsigned short> *load_default_deck(std::deque<unsigned short> *,int);
};
std::deque<unsigned short> *DefaultDeckLoaderView::load_default_deck(std::deque<unsigned short> *deck,int character)
{
 if(!deck)return 0;
 std::string path = "data/csv/" + std::string(character_key_to_name(character)) + "/deck.csv";
 DeckCsvReader reader;
 reader.load(path.c_str());
 deck->clear();
 for(int i=0;i<20;++i)deck->push_back(static_cast<unsigned short>(reader.next_int()));
 return deck;
}
}
