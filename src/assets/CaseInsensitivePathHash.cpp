// Shared game path hash. The table is the real zlib get_crc_table provider.
namespace th105 {
extern "C" const unsigned long * __cdecl get_crc_table();
unsigned __cdecl case_insensitive_crc32(
    const unsigned char *bytes,
    int length)
{
    if (bytes == 0)
        return 0;

    const unsigned long *table = get_crc_table();
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

}
