#pragma once

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

    virtual bool load_bitmap(const char *path);
    virtual bool load_png(const char *path);
    virtual bool load_from_file(const char *path);
    virtual void copy_from(const CBitmapSourceView *source);

private:
    friend struct TextureFileLoading;
    unsigned char format_04;
    unsigned char reserved_05[3];
    int field_08;
    int field_0c;
    int field_10;
    unsigned int explicit_size_14;
    unsigned int field_18;
    unsigned char *buffer_1c;
};

} // namespace th105
