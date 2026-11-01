#include "ui/FileList.hpp"
namespace th105 {
unsigned char CFileList::go_parent_directory()
{
    if (directory_08c == filter_070)
        return true;
    char slash = '/';
    directory_08c.erase(
        directory_08c.find_last_of(&slash, std::string::npos, 1),
        std::string::npos);
    return false;
}
}
