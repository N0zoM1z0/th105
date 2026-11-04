#include "battle/ReplayFilenameFile.hpp"
#include <string>

namespace th105 {

struct ReplayHeaderServiceView {
    int read_header_code(const char *path);
};

int ReplayHeaderServiceView::read_header_code(const char *path)
{
    std::string filename("");
    filename.append(path);
    ReplayFilenameFile file(filename.c_str());
    if (file.handle == 0)
        return -1;
    int code;
    file.read(&code, sizeof(code));
    return code;
}

} // namespace th105
