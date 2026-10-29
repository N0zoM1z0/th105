#include <set>
#include <cstring>
#include "assets/CaseInsensitivePathHash.cpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo();

// Current score/profile runtime prefix used by the music-selection menus.  The
// checked std::set at +0x44 is independently fixed by the current 105-byte
// std::_Tree::find COMDAT and its caller at 0x0042D880.
struct ScoreMusicLookupView {
    unsigned char unknown_000[0x44];
    std::set<unsigned> path_hashes_044;

    bool contains_bgm_path(const char *path);
    void publish_bgm_path(const char *path);
};

bool ScoreMusicLookupView::contains_bgm_path(const char *path)
{
    unsigned key = case_insensitive_crc32(
        reinterpret_cast<const unsigned char *>(path),
        static_cast<int>(std::strlen(path)));
    return path_hashes_044.find(key) != path_hashes_044.end();
}

} // namespace th105

namespace th105 {

unsigned __cdecl get_session_setup_option();
void *__cdecl get_network_session();

void ScoreMusicLookupView::publish_bgm_path(const char *path)
{
    if (get_session_setup_option() != 2 && get_network_session() == 0) {
        unsigned key = case_insensitive_crc32(
            reinterpret_cast<const unsigned char *>(path),
            static_cast<int>(std::strlen(path)));
        path_hashes_044.insert(key);
    }
}

} // namespace th105
