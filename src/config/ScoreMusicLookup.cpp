#include <set>
#include <cstring>

namespace th105 {

const unsigned * __cdecl get_casefold_crc_table_6675c0();
extern "C" void __cdecl _invalid_parameter_noinfo();

// Current score/profile runtime prefix used by the music-selection menus.  The
// checked std::set at +0x44 is independently fixed by the current 105-byte
// std::_Tree::find COMDAT and its caller at 0x0042D880.
struct ScoreMusicLookupView {
    unsigned char unknown_000[0x44];
    std::set<unsigned> path_hashes_044;

    bool contains_bgm_path(const char *path);
};

unsigned __cdecl case_insensitive_crc32(
    const unsigned char *bytes,
    int length)
{
    if (bytes == 0)
        return 0;

    const unsigned *table = get_casefold_crc_table_6675c0();
    unsigned crc = ~0u;

    if (length >= 8) {
        unsigned blocks = static_cast<unsigned>(length) >> 3;
        length -= static_cast<int>(blocks * 8);
        do {
            crc = table[(crc ^ (*bytes++ & 0xdf)) & 0xff] ^ (crc >> 8);
            crc = table[(crc ^ (*bytes++ & 0xdf)) & 0xff] ^ (crc >> 8);
            crc = table[(crc ^ (*bytes++ & 0xdf)) & 0xff] ^ (crc >> 8);
            crc = table[(crc ^ (*bytes++ & 0xdf)) & 0xff] ^ (crc >> 8);
            crc = table[(crc ^ (*bytes++ & 0xdf)) & 0xff] ^ (crc >> 8);
            crc = table[(crc ^ (*bytes++ & 0xdf)) & 0xff] ^ (crc >> 8);
            crc = table[(crc ^ (*bytes++ & 0xdf)) & 0xff] ^ (crc >> 8);
            crc = table[(crc ^ (*bytes++ & 0xdf)) & 0xff] ^ (crc >> 8);
        } while (--blocks != 0);
    }

    while (length != 0) {
        crc = table[(crc ^ (*bytes++ & 0xdf)) & 0xff] ^ (crc >> 8);
        --length;
    }
    return ~crc;
}

bool ScoreMusicLookupView::contains_bgm_path(const char *path)
{
    unsigned key = case_insensitive_crc32(
        reinterpret_cast<const unsigned char *>(path),
        static_cast<int>(std::strlen(path)));
    return path_hashes_044.find(key) != path_hashes_044.end();
}

} // namespace th105
