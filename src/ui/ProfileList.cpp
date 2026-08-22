#include "FileList.hpp"

namespace th105 {

extern const char profile_file_pattern[];
void create_default_profile_for_list();

// The target CProfileList TU calls the shared String28/std::string assign body
// out of line.  Keep that caller-visible ABI narrow here instead of exposing
// the VC8 std::string implementation and changing constructor codegen.
struct FileListStringAssignView {
    void assign_bytes(const char *source, unsigned int length);
};

CProfileList::CProfileList()
{
    reinterpret_cast<FileListStringAssignView *>(&path_054)
        ->assign_bytes(profile_file_pattern, 13);
    field_a8 = 24;
}

void CProfileList::populate()
{
    CFileList::populate();
    if (rows_004.size() == 0) {
        create_default_profile_for_list();
        CFileList::populate();
    }
}

} // namespace th105
