#include "ScoreDataDefaults.hpp"
#include "assets/FileReader.hpp"
#include <cstring>
namespace th105 {
struct ScoreSaveBuffer {
    unsigned char *data;
    unsigned position;
    explicit ScoreSaveBuffer(unsigned capacity) : position(0) { data = new unsigned char[capacity]; }
    ~ScoreSaveBuffer() { delete[] data; }
    void write_u32(unsigned value) {
        *reinterpret_cast<unsigned *>(data + position) = value;
        position += 4;
    }
    void write(const void *in, unsigned count) {
        std::memcpy(data + position, in, count);
        position += count;
    }
};
int __cdecl get_current_replay_header_code();
unsigned __cdecl encode_score_payload_4067f0(const unsigned char *, unsigned, unsigned char *, unsigned);
void ScoreDataDefaultsView::persist_42d3f0()
{
    if (!initialized_00)
        return;
    CFileWriter file("score.dat");
    ScoreSaveBuffer serialized(0x80000);
    serialized.write_u32(get_current_replay_header_code());
    serialized.write(&flags_04, sizeof(flags_04));
    serialized.write(event_columns_08, sizeof(event_columns_08));
    serialized.write(primary_available_1c, sizeof(primary_available_1c));
    serialized.write(secondary_available_30, sizeof(secondary_available_30));
    serialized.write_u32(music_paths_44.size());
    for (std::set<unsigned>::iterator it = music_paths_44.begin(); it != music_paths_44.end(); ++it)
        serialized.write_u32(*it);
    serialized.write_u32(available_items_50.size());
    for (std::set<unsigned>::iterator it = available_items_50.begin(); it != available_items_50.end(); ++it)
        serialized.write_u32(*it);
    serialized.write_u32(common_counts_9c.size());
    for (std::map<int, int>::iterator it = common_counts_9c.begin(); it != common_counts_9c.end(); ++it) {
        serialized.write_u32(it->first);
        serialized.write_u32(it->second);
    }
    int characters = 15;
    serialized.write(&characters, sizeof(characters));
    for (int character = 0; character < characters; ++character) {
        serialized.write_u32(character_counts_a8[character].size());
        for (std::map<int, int>::iterator it = character_counts_a8[character].begin();
             it != character_counts_a8[character].end(); ++it) {
            serialized.write_u32(it->first);
            serialized.write_u32(it->second);
        }
        serialized.write_u32(records_198[character].size());
        for (std::vector<ScoreDefaultRecord24>::iterator it = records_198[character].begin();
             it != records_198[character].end(); ++it)
            serialized.write(&*it, sizeof(*it));
    }
    ScoreSaveBuffer encoded(0x80000);
    unsigned count = encode_score_payload_4067f0(serialized.data, serialized.position, encoded.data, 0x80000);
    for (unsigned index = 0; index < count; ++index)
        serialized.data[count - index - 1] = encoded.data[index] ^ static_cast<unsigned char>(index * 7);
    file.write(serialized.data, count);
}
}

typedef char ScoreSaveBuffer_size[sizeof(th105::ScoreSaveBuffer) == 8 ? 1 : -1];
typedef char ScoreSaveWriter_size[sizeof(th105::CFileWriter) == 12 ? 1 : -1];
