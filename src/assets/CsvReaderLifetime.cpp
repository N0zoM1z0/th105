namespace th105 {

struct CsvReaderLifetimeView {
    unsigned unknown_00;
    void *row_map_04;
    unsigned row_map_capacity_08;
    unsigned row_start_0c;
    unsigned row_count_10;
    unsigned outer_iterator_aux_14;
    CsvReaderLifetimeView *outer_iterator_owner_18;
    unsigned outer_row_position_1c;
    unsigned inner_iterator_aux_20;
    void *current_row_24;
    unsigned current_field_position_28;
    unsigned char parser_comment_2c;
    unsigned char parser_quote_2d;
    unsigned char reserved_2e[2];

    ~CsvReaderLifetimeView() throw();
    void clear_rows() throw();
};

CsvReaderLifetimeView::~CsvReaderLifetimeView() throw()
{
    clear_rows();
}

typedef char CsvReaderLifetimeView_size_must_be_0x30[
    sizeof(CsvReaderLifetimeView) == 0x30 ? 1 : -1];

} // namespace th105
