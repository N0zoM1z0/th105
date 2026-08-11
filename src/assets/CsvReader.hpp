#pragma once

namespace th105 {

// Observed prefix only. The auxiliary words and concrete nested deque types
// remain deliberately opaque until their constructors and iterator ABI are
// reconstructed.
struct CsvReader {
    unsigned unknown_00;
    void *row_map_04;
    unsigned row_map_capacity_08;
    unsigned row_start_0c;
    unsigned row_count_10;
    unsigned outer_iterator_aux_14;
    CsvReader *outer_iterator_owner_18;
    unsigned outer_row_position_1c;
    unsigned inner_iterator_aux_20;
    void *current_row_24;
    unsigned current_field_position_28;
    unsigned char parser_comment_2c;
    unsigned char parser_quote_2d;

    bool load(const char *path);
    int next_int();
    void *next_string(void *out_string);
    bool advance_row();
    void clear_rows();
};

} // namespace th105
