#include "ui/FileList.hpp"
namespace th105 {
static inline void truncate_at_last(std::string &path, char separator)
{
    path.erase(path.find_last_of(&separator, std::string::npos, 1), std::string::npos);
}

unsigned char CFileList::go_parent_directory()
{
    if (directory_08c == filter_070)
        return true;
    truncate_at_last(directory_08c, '/');
    return false;
}
}
