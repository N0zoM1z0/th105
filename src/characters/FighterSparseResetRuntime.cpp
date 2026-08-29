#include <stddef.h>
namespace th105 {

struct FighterSparseResetView {
    unsigned char reserved_000[0x4b0];
    unsigned short word_4b0;
    unsigned short word_4b2;
    unsigned char reserved_4b4[2];
    unsigned char byte_4b6;
    unsigned char reserved_4b7[0x16d];
    unsigned char bytes_624[4];
    unsigned char reserved_628[0x108];
    unsigned short word_730;
    unsigned short word_732;
    unsigned short word_734;
    unsigned short word_736;
    unsigned short word_738;
    unsigned char reserved_73a[2];
    float float_73c;
    float float_740;
    float float_744;
    float float_748;
    float float_74c;
    unsigned char bytes_750[11];
    unsigned char reserved_75b;
    unsigned dword_75c;
    unsigned dword_760;
    unsigned short word_764;
    unsigned short word_766;
    unsigned short word_768;
    unsigned short word_76a;
    unsigned short word_76c;
    unsigned short word_76e;
    unsigned short word_770;
    unsigned short word_772;
    unsigned short word_774;
    unsigned short word_776;
    float float_778;
    float float_77c;
    float float_780;
    float float_784;
    float float_788;
    unsigned dword_78c;
    unsigned dword_790;
    unsigned dword_794;
    unsigned dword_798;
    unsigned short word_79c;
    unsigned char reserved_79e[2];
    unsigned short word_7a0;
    unsigned short word_7a2;

    void reset_base_460200();
    int reset_sparse_4776d0();
};

typedef char FighterSparseResetView_size[sizeof(FighterSparseResetView)==0x7a4?1:-1];
typedef char FighterSparseResetView_f73c[offsetof(FighterSparseResetView,float_73c)==0x73c?1:-1];
typedef char FighterSparseResetView_w7a0[offsetof(FighterSparseResetView,word_7a0)==0x7a0?1:-1];

int FighterSparseResetView::reset_sparse_4776d0()
{
    reset_base_460200();
    float_73c = 0.0f;
    float_740 = 0.0f;
    word_730 = 0;
    float_744 = 0.0f;
    word_732 = 0;
    float_748 = 0.0f;
    word_734 = 0;
    float_74c = 0.0f;
    word_736 = 0;
    float_778 = 0.0f;
    word_738 = 0;
    float_77c = 0.0f;
    bytes_750[0] = 0;
    float_780 = 0.0f;
    word_766 = 0;
    float_784 = 0.0f;
    word_768 = 0;
    float_788 = 0.0f;
    word_764 = 0;
    word_76a = 0;
    word_76c = 0;
    word_76e = 0;
    word_770 = 0;
    word_772 = 0;
    word_774 = 0;
    word_7a0 = 0;
    word_7a2 = 0;
    word_4b0 = 0;
    word_4b2 = 0;
    bytes_750[1] = 0;
    bytes_750[3] = 0;
    bytes_750[2] = 0;
    bytes_750[4] = 0;
    bytes_750[5] = 0;
    bytes_750[6] = 0;
    bytes_750[7] = 0;
    bytes_750[8] = 0;
    bytes_750[9] = 0;
    bytes_750[10] = 0;
    word_776 = 0;
    byte_4b6 = 0;
    dword_75c = 0;
    dword_760 = 0;
    bytes_624[0] = 0;
    bytes_624[1] = 0;
    bytes_624[2] = 0;
    bytes_624[3] = 0;
    dword_78c = 0;
    dword_790 = 0;
    dword_794 = 0;
    dword_798 = 0;
    word_79c = 0;
    return 0;
}

} // namespace th105
