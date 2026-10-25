#include "battle/SpellData.hpp"
#include "assets/CsvReader.hpp"
#include "assets/SpellTexturePool.hpp" // composite upload-state declaration
#include "ui/Title.hpp"
#include <set>
#include <map>
#include <deque>

namespace th105 {

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *, const char *, ...);

extern unsigned g_spell_texture_load_state;
extern unsigned g_spell_texture_upload_state;
extern CompositeTextureUploadState g_spell_composite_upload_state;

// 0x004021C0 is an independently compiled checked-string assign operation.
struct FilteredSpellStringAssignView {
    String28 &assign_bytes(const char *text, unsigned count);
};

void SpellDataOwner::parse_spell_csv_via_325b0(
    const char *character_name,
    const char *path,
    DwordDeque4 *image_owner,
    SpellTree *destination,
    void *mode_argument)
{
    typedef std::map<int, SpellRecordView> RecordMap;
    RecordMap *const records = reinterpret_cast<RecordMap *>(destination);
    typedef char map_layout[sizeof(RecordMap) == sizeof(SpellTree) ? 1 : -1];
    typedef char deque_layout[
        sizeof(std::deque<unsigned>) == sizeof(DwordDeque4) ? 1 : -1];
    struct OwningCsvReader : CsvReader {
        OwningCsvReader() {
            row_map_04 = 0;
            row_map_capacity_08 = 0;
            row_start_0c = 0;
            row_count_10 = 0;
            outer_iterator_aux_14 = 0;
            outer_iterator_owner_18 = 0;
            outer_row_position_1c = 0;
            inner_iterator_aux_20 = 0;
            current_row_24 = 0;
            current_field_position_28 = 0;
        }
    } reader;
    reader.load(path);

    std::set<short> selected_ids;
    std::deque<short> *const queued_ids =
        static_cast<std::deque<short> *>(mode_argument);
    for (unsigned index = 0; index < queued_ids->size(); ++index)
        selected_ids.insert((*queued_ids)[index]);

    String28 composite_paths;
    int batch_count = 0;
    bool has_next_row;
    do {
        struct ParsedSpellRow : SpellRecordView {
            ParsedSpellRow() {
                batch_resource_40 = 0;
                optional_resource_44 = 0;
            }
        } parsed;
        const int key = reader.next_int();
        reader.next_string(&parsed.name_00);
        parsed.selector_1c = static_cast<signed char>(reader.next_int());
        parsed.value_1e = static_cast<short>(reader.next_int());
        reader.next_string(&parsed.description_20);
        parsed.value_3c = static_cast<short>(reader.next_int());
        parsed.value_3e = static_cast<short>(reader.next_int());

        if (image_owner != 0) {
            const short selected_key = static_cast<short>(key);
            if (selected_ids.find(selected_key) != selected_ids.end()) {
                char card_path[260];
                wsprintfA(
                    card_path,
                    "data/card/%s/card%03d.bmp",
                    character_name,
                    key);
                unsigned card_handle;
                reinterpret_cast<std::deque<unsigned> *>(image_owner)->push_back(
                    *g_title_resource_manager.load_texture(
                        &card_handle,
                        card_path,
                        &g_spell_texture_load_state,
                        &g_spell_texture_upload_state));
                parsed.optional_resource_44 = reinterpret_cast<void *>(
                    reinterpret_cast<std::deque<unsigned> *>(image_owner)->back());
                composite_paths.append(parsed.name_00 + "<br>");
                parsed.value_48 = 16 * batch_count++;

                records->insert(std::pair<int, SpellRecordView>(key, parsed));
            }
            has_next_row = reader.advance_row();
            if (batch_count == 16 || !has_next_row) {
                TextureHandleResult composite_handle =
                    g_title_resource_manager.create_text_texture(
                        composite_paths.c_str(),
                        &g_spell_composite_upload_state,
                        0x200,
                        0x100,
                        0,
                        0);
                reinterpret_cast<std::deque<unsigned> *>(image_owner)->push_back(
                    composite_handle.value);

                RecordMap::reverse_iterator current = records->rbegin();
                for (int index = 0; index < batch_count; ++index)
                    (current++)->second.batch_resource_40 =
                        reinterpret_cast<void *>(composite_handle.value);
                reinterpret_cast<FilteredSpellStringAssignView *>(&composite_paths)
                    ->assign_bytes("", 0);
                batch_count = 0;
            }
        } else {
            records->insert(std::pair<int, SpellRecordView>(key, parsed));
            has_next_row = reader.advance_row();
        }
    } while (has_next_row);
}

} // namespace th105
