extern "C" void __cdecl _invalid_parameter_noinfo();

namespace th105 {

struct ResultInputRecord68 {
    unsigned char bytes_00[0x68];
};

struct ResultInputRecordTableView {
    unsigned unknown_00;
    ResultInputRecord68 *begin_04;
    ResultInputRecord68 *end_08;

    ResultInputRecord68 *at(unsigned index);
};

ResultInputRecord68 *ResultInputRecordTableView::at(unsigned index)
{
    if (begin_04 == 0 ||
        !(index < static_cast<unsigned>(end_08 - begin_04)))
        _invalid_parameter_noinfo();
    return begin_04 + index;
}

} // namespace th105
