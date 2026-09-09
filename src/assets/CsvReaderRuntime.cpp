#include <deque>
#include <string>
#include <stdlib.h>
#include <stddef.h>

namespace th105 {

typedef std::deque<std::string> CsvRow;
typedef std::deque<CsvRow> CsvRows;

struct CsvStringAssignCallView {
    std::string *assign_bytes(const char *source, unsigned int length);
    std::string *assign_string(
        const std::string &source, unsigned int position, unsigned int count);
};


struct CsvReaderNativeView {
    CsvRows rows_00;
    CsvRows::iterator row_it_14;
    CsvRow::iterator field_it_20;
    unsigned char parser_comment_2c;
    unsigned char parser_quote_2d;
    unsigned char reserved_2e[2];

    int next_int_40f480();
    std::string *next_string_40f580(std::string *out);
    bool advance_row_40f680();
    void clear_rows_40fdb0() throw();
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

std::string *CsvReaderNativeView::next_string_40f580(std::string *out)
{
    CsvStringAssignCallView *destination =
        reinterpret_cast<CsvStringAssignCallView *>(out);
    if (row_it_14 == rows_00.end())
        return destination->assign_bytes("", 0);
    if (field_it_20 == row_it_14->end())
        return destination->assign_bytes("", 0);
    CsvRow::iterator current = field_it_20;
    ++field_it_20;
    return destination->assign_string(
        *current, 0, static_cast<unsigned int>(-1));
}

bool CsvReaderNativeView::advance_row_40f680()
{
    if (row_it_14 == rows_00.end())
        return false;
    ++row_it_14;
    if (row_it_14 == rows_00.end())
        return false;
    field_it_20 = row_it_14->begin();
    return true;
}

void CsvReaderNativeView::clear_rows_40fdb0() throw()
{
    rows_00.clear();
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
