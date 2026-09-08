#include <stdlib.h>
#include <string.h>

namespace th105 {

struct CBitmapSourceView {
    int field_00;
    int field_04;
    int field_08;
    unsigned char format_0c;
    unsigned char reserved_0d[3];
    unsigned int explicit_size_10;
    const unsigned char *data_14;
};

class CBitmapData {
public:
    CBitmapData();
    virtual ~CBitmapData();
    void copy_from(const CBitmapSourceView *source);

private:
    unsigned char format_04;
    unsigned char reserved_05[3];
    int field_08;
    int field_0c;
    int field_10;
    unsigned int explicit_size_14;
    unsigned int field_18;
    unsigned char *buffer_1c;
};

CBitmapData::CBitmapData()
{
    format_04 = 0;
    buffer_1c = 0;
    field_18 = 0;
    explicit_size_14 = 0;
}

CBitmapData::~CBitmapData()
{
    if (buffer_1c != 0)
        free(buffer_1c);
}

void CBitmapData::copy_from(const CBitmapSourceView *source)
{
    field_08 = source->field_00;
    field_0c = source->field_04;
    field_10 = source->field_08;
    format_04 = source->format_0c;
    explicit_size_14 = source->explicit_size_10;

    if (explicit_size_14 > 0) {
        buffer_1c = new unsigned char[explicit_size_14];
        memcpy(buffer_1c, source->data_14, explicit_size_14);
        return;
    }

    if (format_04 >= 24) {
        buffer_1c = new unsigned char[field_10 * field_0c * 4];
        memcpy(buffer_1c, source->data_14, field_10 * field_0c * 4);
        return;
    }

    buffer_1c = new unsigned char[format_04 * field_10 * field_0c / 8];
    memcpy(buffer_1c, source->data_14, format_04 * field_10 * field_0c / 8);
}

typedef char CBitmapDataSize[sizeof(CBitmapData) == 0x20 ? 1 : -1];
typedef char CBitmapSourceViewSize[sizeof(CBitmapSourceView) == 0x18 ? 1 : -1];

} // namespace th105
