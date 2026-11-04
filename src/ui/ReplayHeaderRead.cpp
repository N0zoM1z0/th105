#include "assets/PlainFileReader.hpp"
#include "ReplayHeaderService.hpp"
#include <string>

namespace th105 {

int ReplayHeaderServiceView::read_header_code(const char *path)
{
    std::string filename("");
    filename.append(path);
    PlainFileReader file(filename.c_str());
    if (file.handle == 0)
        return -1;
    int code;
    file.read(&code, sizeof(code));
    return code;
}

} // namespace th105
