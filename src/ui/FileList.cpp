#include "FileList.hpp"
#include "Title.hpp"

#include <string.h>

namespace th105 {

struct ModulePathTextView {
    unsigned char extra_bytes(unsigned char value);
};

extern ModulePathTextView g_module_path_text;

CFileList::CFileList()
    : field_a8(0), field_ac(4), field_b0(0)
{
}

CFileList::~CFileList()
{
}

int CFileList::item_count() const
{
    return rows_004.size();
}

void CFileList::render_item(float x, float y, unsigned int index)
{
    if (index >= rows_004.size())
        return;
    render_items_040.at(index >> 4).render(x, y, 0, index & 15);
}

bool CFileList::contains(const std::string *value) const
{
    for (std::deque<std::string>::const_iterator it = rows_004.begin();
         it != rows_004.end(); ++it) {
        if (_stricmp(it->c_str(), value->c_str()) == 0)
            return true;
    }
    return false;
}

void CFileList::shutdown()
{
    for (unsigned int i = 0; i < handles_02c.size(); ++i)
        g_title_resource_manager.release_title_resource_handle(handles_02c[i]);
    render_items_040.clear();
    rows_004.clear();
    handles_02c.clear();
}

void CFileList::trim_item_text(std::string *value)
{
    if (field_ac != 0)
        value->erase(value->size() - field_ac, field_ac);

    if (field_a8 != 0) {
        unsigned int position = 0;
        while (position < value->size()) {
            position += g_module_path_text.extra_bytes(
                static_cast<unsigned char>((*value)[position])) + 1;
            if (position >= static_cast<unsigned int>(field_a8))
                value->erase(position, value->size() - position);
        }
    }
}

} // namespace th105
