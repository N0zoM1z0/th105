#include "SpellData.hpp"

#include "assets/CsvReader.hpp"

namespace th105 {

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *destination,
    const char *format,
    ...);
extern "C" void __cdecl _invalid_parameter_noinfo(void);

struct SpellTexturePool {
    unsigned *load_texture(
        unsigned *result,
        const char *path,
        void *load_state,
        void *upload_state);
    unsigned *create_composite_texture(
        unsigned *result,
        const char *path_list,
        void *upload_state,
        int width,
        int height);
};

extern SpellTexturePool g_spell_texture_pool;
extern unsigned g_spell_texture_load_state;
extern unsigned g_spell_texture_upload_state;
extern unsigned g_spell_composite_upload_state;

__forceinline unsigned &DwordDeque4::back_checked()
{
    const unsigned begin = head_0c;
    if (begin > live_count_10 + begin)
        _invalid_parameter_noinfo();

    const unsigned finish = live_count_10 + head_0c;
    const unsigned position = finish - 1;
    if (position > finish || position < begin)
        _invalid_parameter_noinfo();
    if (position >= live_count_10 + head_0c)
        _invalid_parameter_noinfo();

    unsigned block = position >> 2;
    if (block_capacity_08 <= block)
        block -= block_capacity_08;
    return blocks_04[block][position & 3];
}

void __stdcall parse_spell_csv_and_build_card_resources(
    const char *character_name,
    const char *path,
    DwordDeque4 *image_owner,
    SpellTree *destination)
{
    CsvReader reader;
    reader.load(path);

    String28 composite_paths;
    unsigned batch_count = 0;
    bool has_next_row;

    do {
        SpellRecordView parsed;
        const int key = reader.next_int();
        reader.next_string(&parsed.name_00);
        parsed.selector_1c = static_cast<signed char>(reader.next_int());
        parsed.value_1e = static_cast<short>(reader.next_int());
        reader.next_string(&parsed.description_20);
        parsed.value_3c = static_cast<short>(reader.next_int());
        parsed.value_3e = static_cast<short>(reader.next_int());
        parsed.batch_resource_40 = 0;
        parsed.optional_resource_44 = 0;

        DwordDeque4 *handles = image_owner;
        if (handles != 0) {
            char card_path[260];
            wsprintfA(
                card_path,
                "data/card/%s/card%03d.bmp",
                character_name,
                key);

            unsigned card_handle;
            handles->push_back(
                g_spell_texture_pool.load_texture(
                    &card_handle,
                    card_path,
                    &g_spell_texture_load_state,
                    &g_spell_texture_upload_state));
            parsed.optional_resource_44 = reinterpret_cast<void *>(
                handles->back_checked());
            composite_paths.append(parsed.name_00 + "<br>");
            ++batch_count;

            SpellRecordView record_copy(parsed);
            SpellTreeValue value(key, record_copy);
            SpellTreeInsertResult ignored;
            destination->insert_unique_value(&ignored, &value);
            has_next_row = reader.advance_row();

            if (batch_count != 16 && has_next_row)
                continue;

            unsigned composite_handle;
            handles->push_back(
                g_spell_texture_pool.create_composite_texture(
                    &composite_handle,
                    composite_paths.c_str(),
                    &g_spell_composite_upload_state,
                    0x200,
                    0x100));

            SpellTreeIterator current = {
                destination,
                destination->end_node_04
            };
            for (unsigned remaining = batch_count;
                 remaining != 0;
                 --remaining) {
                current.decrement_checked();
                SpellTreeIterator record = current;
                record.decrement_checked();
                if (record.owner == 0 ||
                    record.node == record.owner->end_node_04)
                    _invalid_parameter_noinfo();
                record.node->value_10.batch_resource_40 =
                    reinterpret_cast<void *>(composite_handle);
            }

            composite_paths.assign("", static_cast<unsigned>(0));
            batch_count = 0;
        } else {
            SpellRecordView record_copy(parsed);
            SpellTreeValue value(key, record_copy);
            SpellTreeInsertResult ignored;
            destination->insert_unique_value(&ignored, &value);
            has_next_row = reader.advance_row();
        }
    } while (has_next_row);

    reader.clear_rows();
}

} // namespace th105
