#include "ResultMenu.hpp"

#include <cstdio>
#include <cstring>

extern "C" int __cdecl _sprintf_s(
    char *buffer, unsigned int size, const char *format, ...);
extern "C" const char result_empty_row_format[];
extern "C" const char result_row_format[];
extern "C" void __fastcall release_owned_pointer_buffer(void *buffer);

namespace th105 {

struct ResultRecord24 {
    int character_id;
    int language;
    int spell_id;
    int maximum;
    int current;
    int frames;
};

struct ResultRecordVector16 {
    unsigned int allocator_state;
    ResultRecord24 *begin;
    ResultRecord24 *end;
    ResultRecord24 *capacity;

    ResultRecord24 &at(unsigned int index)
    {
        if (begin == 0 ||
            static_cast<unsigned int>(end - begin) <= index)
            _invalid_parameter_noinfo();
        return begin[index];
    }
};

struct ResultScoreState {
    unsigned char reserved_000[0x198];
    ResultRecordVector16 records[15];
};

struct ResultNameResolver {
    unsigned char storage[0x20];

    ResultNameResolver();
    ~ResultNameResolver();
    void load_character(int character_id, int language, int flags);
    ResultString28 *find_spell(int spell_id);
    void cleanup();
};

extern ResultScoreState *get_result_score_state();

__forceinline void ResultStringDeque20::push_back(
    const ResultString28 &value)
{
    if (map_size <= size + 1)
        grow(1);

    unsigned int position = offset + size;
    if (map_size <= position)
        position -= map_size;

    if (map[position] == 0)
        map[position] = static_cast<ResultString28 *>(
            operator new(sizeof(ResultString28)));
    ResultString28 *slot = map[position];
    if (slot != 0) {
        slot->capacity = 15;
        slot->size = 0;
        slot->storage.buffer[0] = 0;
        slot->assign_copy(value, 0, static_cast<unsigned int>(-1));
    }
    ++size;
}

void ResultList::populate()
{
    rows_004.clear();
    indices_b8.clear();
    release_owned_pointer_buffer(&labels_cc);
    release_owned_pointer_buffer(&metadata_f4);

    unsigned short language_names[4] = {'E', 'N', 'H', 'L'};
    ResultNameResolver names;
    int loaded_character = 15;

    unsigned int index = 0;
    for (;;) {
        ResultRecordVector16 &records =
            get_result_score_state()->records[character_id_b4];
        if (records.begin == 0 ||
            static_cast<unsigned int>(records.end - records.begin) <= index) {
            names.cleanup();
            finalize();
            return;
        }

        ResultRecord24 &record =
            get_result_score_state()->records[character_id_b4].at(index);
        if (record.character_id != loaded_character) {
            loaded_character = record.character_id;
            names.load_character(loaded_character, 1, 0);
        }

        ResultString28 *spell_name = names.find_spell(record.spell_id);
        if (spell_name != 0) {
            char row[1024];
            unsigned int replay_id;
            if (record.maximum != 0) {
                _sprintf_s(
                    row,
                    sizeof(row),
                    result_row_format,
                    spell_name->c_str(),
                    reinterpret_cast<char *>(language_names + record.language),
                    record.current,
                    record.maximum,
                    record.frames / 60,
                    record.frames * 100 / 60 % 100);
                replay_id = static_cast<unsigned short>(record.spell_id);
            } else {
                _sprintf_s(row, sizeof(row), result_empty_row_format);
                replay_id = static_cast<unsigned int>(-1);
            }
            metadata_f4.push_back(replay_id);

            ResultString28 text;
            text.assign_buffer(
                row, static_cast<unsigned int>(std::strlen(row)));
            rows_004.push_back(text);
            indices_b8.push_back(text);
            labels_cc.push_back(loaded_character);
            values_e0.push_back(record.language);
        }
        ++index;
    }
}

} // namespace th105
