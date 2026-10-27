#include "ScoreDataDefaults.hpp"
#include <cstring>
extern "C" {
__declspec(dllimport) void *__stdcall CreateFileA(const char *, unsigned long, unsigned long, void *, unsigned long, unsigned long, void *);
__declspec(dllimport) int __stdcall CloseHandle(void *);
__declspec(dllimport) unsigned long __stdcall GetFileSize(void *, unsigned long *);
__declspec(dllimport) int __stdcall ReadFile(void *, void *, unsigned long, unsigned long *, void *);
__declspec(dllimport) unsigned long __stdcall SetFilePointer(void *, long, long *, unsigned long);
}
namespace th105 {
class ScoreLoadPlainFile {
public:
    explicit ScoreLoadPlainFile(const char *path) {
        file = CreateFileA(path, 1, 1, 0, 3, 0x80, 0);
        if (file == reinterpret_cast<void *>(-1)) file = 0;
    }
    virtual ~ScoreLoadPlainFile() { if (file) CloseHandle(file); }
    virtual bool read(void *out, unsigned long count) { return ReadFile(file, out, count, &bytes_read, 0) != 0; }
    virtual unsigned long last_read_size() const { return bytes_read; }
    virtual long seek(long off, int origin) { return SetFilePointer(file, off, 0, origin); }
    virtual unsigned long size() const { return GetFileSize(file, 0); }
    void *file;
    unsigned long bytes_read;
};
struct ScoreLoadBuffer {
    unsigned char *data;
    unsigned position;
    explicit ScoreLoadBuffer(unsigned capacity) : position(0) { data = new unsigned char[capacity]; }
    ~ScoreLoadBuffer() { delete[] data; }
    unsigned read_u32() {
        unsigned value = *reinterpret_cast<const unsigned *>(data + position);
        position += 4;
        return value;
    }
    void read(void *out, unsigned count) {
        std::memcpy(out, data + position, count);
        position += count;
    }
};
unsigned __cdecl decode_score_payload_406890(const unsigned char *, unsigned, unsigned char *, unsigned);
bool ScoreDataDefaultsView::load_42f6f0()
{
    ScoreLoadPlainFile file("score.dat");
    if (file.file == 0) {
        initialize_defaults_42ed70();
        return false;
    }
    ScoreLoadBuffer decoded(0x80000);
    ScoreLoadBuffer encoded(0x80000);
    unsigned count = file.size();
    file.read(decoded.data, count);
    for (unsigned index = 0; index < count; ++index)
        encoded.data[index] = decoded.data[count - index - 1] ^ static_cast<unsigned char>(index * 7);
    if (!decode_score_payload_406890(encoded.data, count, decoded.data, 0x80000)) {
        initialize_defaults_42ed70();
        return false;
    }
    decoded.position = 4;
    decoded.read(&flags_04, sizeof(flags_04));
    decoded.read(event_columns_08, sizeof(event_columns_08));
    decoded.read(primary_available_1c, sizeof(primary_available_1c));
    decoded.read(secondary_available_30, sizeof(secondary_available_30));
    music_paths_44.clear();
    count = decoded.read_u32();
    for (unsigned index = 0; index < count; ++index) {
        unsigned key;
        decoded.read(&key, sizeof(key));
        music_paths_44.insert(key);
    }
    available_items_50.clear();
    count = decoded.read_u32();
    for (unsigned index = 0; index < count; ++index) {
        unsigned key;
        decoded.read(&key, sizeof(key));
        available_items_50.insert(key);
    }
    common_counts_9c.clear();
    count = decoded.read_u32();
    for (unsigned index = 0; index < count; ++index) {
        int key = static_cast<int>(decoded.read_u32());
        int value = static_cast<int>(decoded.read_u32());
        common_counts_9c.insert(std::pair<int, int>(key, value));
    }
    unsigned characters = decoded.read_u32();
    for (unsigned character = 0; character < characters; ++character) {
        character_counts_a8[character].clear();
        count = decoded.read_u32();
        for (unsigned index = 0; index < count; ++index) {
            int key = static_cast<int>(decoded.read_u32());
            int value = static_cast<int>(decoded.read_u32());
            character_counts_a8[character].insert(std::pair<int, int>(key, value));
        }
        records_198[character].clear();
        count = decoded.read_u32();
        for (unsigned index = 0; index < count; ++index) {
            ScoreDefaultRecord24 record;
            decoded.read(&record, sizeof(record));
            bool found = false;
            for (unsigned previous = 0; previous < records_198[character].size(); ++previous) {
                if (record.key_00 == records_198[character][previous].key_00 &&
                    record.key_08 == records_198[character][previous].key_08) {
                    found = true;
                    break;
                }
            }
            if (!found) records_198[character].push_back(record);
        }
    }
    refresh_story_progress_42e3f0();
    initialized_00 = 1;
    return true;
}
}

typedef char ScoreLoadFile_size[sizeof(th105::ScoreLoadPlainFile) == 12 ? 1 : -1];
typedef char ScoreLoadBuffer_size[sizeof(th105::ScoreLoadBuffer) == 8 ? 1 : -1];
typedef char ScoreLoadRecord_size[sizeof(th105::ScoreDefaultRecord24) == 24 ? 1 : -1];
