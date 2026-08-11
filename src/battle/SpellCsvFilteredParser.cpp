#include "battle/SpellData.hpp"
#include "assets/CsvReader.hpp"

namespace th105 {

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *, const char *, ...);
extern "C" void __cdecl _invalid_parameter_noinfo(void);
extern "C" void __cdecl free(void *);

struct SpellTexturePool {
    unsigned *load_texture(unsigned *, const char *, void *, void *);
    unsigned *create_composite_texture(
        unsigned *, const char *, void *, int, int);
};

extern SpellTexturePool g_spell_texture_pool;
extern unsigned g_spell_texture_load_state;
extern unsigned g_spell_texture_upload_state;
extern unsigned g_spell_composite_upload_state;

extern ShortTreeNode * __cdecl allocate_short_tree_nil_node(void);

static __forceinline short &short_deque_at_checked(
    ShortDeque8 *deque,
    unsigned index)
{
    const unsigned begin = deque->head_0c;
    const unsigned finish = begin + deque->live_count_10;
    if (begin > finish || index + begin > finish || index + begin < begin)
        _invalid_parameter_noinfo();
    const unsigned absolute = index + begin;
    if (absolute >= finish)
        _invalid_parameter_noinfo();
    unsigned block = absolute >> 3;
    if (deque->block_capacity_08 <= block)
        block -= deque->block_capacity_08;
    return deque->blocks_04[block][absolute & 7];
}

static __forceinline unsigned &dword_deque_back_checked(DwordDeque4 *deque)
{
    const unsigned begin = deque->head_0c;
    const unsigned finish = begin + deque->live_count_10;
    if (begin > finish || finish - 1 > finish || finish - 1 < begin)
        _invalid_parameter_noinfo();
    const unsigned absolute = finish - 1;
    if (absolute >= finish)
        _invalid_parameter_noinfo();
    unsigned block = absolute >> 2;
    if (deque->block_capacity_08 <= block)
        block -= deque->block_capacity_08;
    return deque->blocks_04[block][absolute & 3];
}

void __stdcall parse_spell_csv_via_325b0(
    const char *character_name,
    const char *path,
    DwordDeque4 *image_owner,
    SpellTree *destination,
    void *mode_argument)
{
    CsvReader reader;
    reader.load(path);

    ShortTree selected_ids;
    ShortTreeNode *nil = allocate_short_tree_nil_node();
    nil->is_nil_0f = 1;
    nil->left_00 = nil;
    nil->parent_04 = nil;
    nil->right_08 = nil;
    selected_ids.end_node_04 = nil;
    selected_ids.node_count_08 = 0;

    ShortDeque8 *const queued_ids =
        static_cast<ShortDeque8 *>(mode_argument);
    for (unsigned index = 0; index < queued_ids->live_count_10; ++index) {
        const short id = short_deque_at_checked(queued_ids, index);
        ShortTreeInsertResult ignored;
        selected_ids.insert_unique_key(&ignored, &id);
    }

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

        if (image_owner != 0) {
            const short selected_key = static_cast<short>(key);
            ShortTreeIterator selected;
            selected_ids.find_checked(&selected, &selected_key);
            if (selected.owner == 0 || selected.owner != &selected_ids)
                _invalid_parameter_noinfo();

            if (selected.node != nil) {
                char card_path[260];
                wsprintfA(
                    card_path,
                    "data/card/%s/card%03d.bmp",
                    character_name,
                    key);
                unsigned card_handle;
                image_owner->push_back(g_spell_texture_pool.load_texture(
                    &card_handle,
                    card_path,
                    &g_spell_texture_load_state,
                    &g_spell_texture_upload_state));
                parsed.optional_resource_44 = reinterpret_cast<void *>(
                    dword_deque_back_checked(image_owner));
                composite_paths.append(parsed.name_00 + "<br>");
                parsed.value_48 = 16 * batch_count++;

                SpellRecordView record_copy(parsed);
                SpellTreeValue value(key, record_copy);
                SpellTreeInsertResult ignored;
                destination->insert_unique_value(&ignored, &value);
            }
        } else {
            SpellRecordView record_copy(parsed);
            SpellTreeValue value(key, record_copy);
            SpellTreeInsertResult ignored;
            destination->insert_unique_value(&ignored, &value);
        }

        has_next_row = reader.advance_row();
        if (image_owner != 0 && (batch_count == 16 || !has_next_row)) {
            unsigned composite_handle;
            image_owner->push_back(
                g_spell_texture_pool.create_composite_texture(
                    &composite_handle,
                    composite_paths.c_str(),
                    &g_spell_composite_upload_state,
                    0x200,
                    0x100));

            SpellTreeIterator current = {
                destination, destination->end_node_04};
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
        }
    } while (has_next_row);

    ShortTreeIterator first = {
        &selected_ids, selected_ids.end_node_04->left_00};
    ShortTreeIterator last = {&selected_ids, selected_ids.end_node_04};
    selected_ids.erase_range_checked(&last, first, last);
    free(nil);
    reader.clear_rows();
}

} // namespace th105
