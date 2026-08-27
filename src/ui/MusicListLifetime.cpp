#include "MenuMusic.hpp"

namespace th105 {

MusicList::MusicList()
{
    // The target publishes the two inherited CFileList policy words in this
    // order after constructing the two owned string deques.
    field_ac = 0;
    field_a8 = 0;
}

} // namespace th105
