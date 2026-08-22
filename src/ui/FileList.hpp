#pragma once

#include <deque>
#include <string>

namespace th105 {

// Binary CTile-compatible page object owned by CFileList.  Current CFileList
// code only needs its polymorphic destruction and four-argument render ABI;
// the 0xA4 size is independently established by current tile consumers.
class FileListTile {
public:
    virtual ~FileListTile();
    void render(float x, float y, int page, int item);

private:
    unsigned char storage_04[0xA0];
};

// Current RTTI names this 0xB8 polymorphic base CFileList.  Retained UI source
// historically used narrower ResultListBase/ProfileNameList facades for the
// same object; keep those compatibility views separate while this shared
// contract records the target-backed physical layout.
class CFileList {
public:
    CFileList();
    virtual ~CFileList();
    virtual void populate();
    virtual void finalize();
    virtual void shutdown();
    virtual unsigned int format_item(
        std::string *output,
        std::deque<std::string>::iterator current);

    int item_count() const;
    void render_item(float x, float y, unsigned int index);
    bool contains(const std::string *value) const;
    void trim_item_text(std::string *value);

protected:
    std::deque<std::string> rows_004;
    std::deque<int> values_018;
    std::deque<unsigned int> handles_02c;
    std::deque<FileListTile> render_items_040;
    std::string path_054;
    std::string filter_070;
    std::string directory_08c;
    int field_a8;
    int field_ac;
    unsigned char field_b0;
    unsigned char reserved_b1[3];
    int character_id_b4;
};

class CProfileList : public CFileList {
public:
    CProfileList();
    virtual void populate();
};

typedef char FileListTile_size_must_be_0xA4[
    sizeof(FileListTile) == 0xA4 ? 1 : -1];
typedef char CFileList_size_must_be_0xB8[
    sizeof(CFileList) == 0xB8 ? 1 : -1];
typedef char CProfileList_size_must_be_0xB8[
    sizeof(CProfileList) == 0xB8 ? 1 : -1];
typedef char CFileList_string_iterator_size_must_be_0x0C[
    sizeof(std::deque<std::string>::iterator) == 0x0C ? 1 : -1];

} // namespace th105
