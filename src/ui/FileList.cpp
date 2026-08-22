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


unsigned int CFileList::format_item(
    std::string *output,
    std::deque<std::string>::iterator current)
{
    std::string value = *current;
    trim_item_text(&value);
    output->append(value, 0, static_cast<unsigned int>(-1));
    return value.size();
}

int CFileList::find_row(const std::string *value) const
{
    std::deque<std::string>::const_iterator current = rows_004.begin();
    for (; current != rows_004.end(); ++current) {
        if (_stricmp(current->c_str(), value->c_str()) == 0)
            return current - rows_004.begin();
    }
    return -1;
}

std::string *CFileList::row_at(unsigned int index)
{
    if (index >= rows_004.size())
        return 0;
    return &rows_004[index];
}

unsigned char CFileList::row_is_directory(unsigned int index)
{
    if (index >= flags_018.size())
        return 0;
    return flags_018[index];
}

void CFileList::enter_directory(unsigned int index)
{
    if (index < rows_004.size() && flags_018[index])
        directory_08c.append("/" + rows_004[index]);
}

} // namespace th105
