#include <deque>
#include <string>
#include <stdlib.h>
#include <stddef.h>

namespace th105 {

typedef std::deque<std::string> CsvRow;
typedef std::deque<CsvRow> CsvRows;

struct CsvReaderNativeView {
    CsvRows rows_00;
    CsvRows::iterator row_it_14;
    CsvRow::iterator field_it_20;
    unsigned char parser_comment_2c;
    unsigned char parser_quote_2d;
    unsigned char reserved_2e[2];

    int next_int_40f480();
};

int CsvReaderNativeView::next_int_40f480()
{
    if (row_it_14 == rows_00.end())
        return 0;
    if (field_it_20 == row_it_14->end())
        return 0;
    CsvRow::iterator current = field_it_20;
    ++field_it_20;
    return atoi(current->c_str());
}

typedef char CsvRow_size_must_be_0x14[sizeof(CsvRow) == 0x14 ? 1 : -1];
typedef char CsvRows_size_must_be_0x14[sizeof(CsvRows) == 0x14 ? 1 : -1];
typedef char CsvRowsIterator_size_must_be_0x0c[
    sizeof(CsvRows::iterator) == 0x0c ? 1 : -1];
typedef char CsvRowIterator_size_must_be_0x0c[
    sizeof(CsvRow::iterator) == 0x0c ? 1 : -1];
typedef char CsvReaderNativeView_row_it_offset[
    offsetof(CsvReaderNativeView, row_it_14) == 0x14 ? 1 : -1];
typedef char CsvReaderNativeView_field_it_offset[
    offsetof(CsvReaderNativeView, field_it_20) == 0x20 ? 1 : -1];
typedef char CsvReaderNativeView_flags_offset[
    offsetof(CsvReaderNativeView, parser_comment_2c) == 0x2c ? 1 : -1];

} // namespace th105
