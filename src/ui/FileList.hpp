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

// Current RTTI names this 0xB4 polymorphic base CFileList. CMenuReplay places
// its next owned member at +0xBC after a CReplayList at +0x08, independently
// closing the base extent. Retained ResultList adds its character id at +0xB4.
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
    int find_row(const std::string *value) const;
    std::string *row_at(unsigned int index);
    unsigned char row_is_directory(unsigned int index);
    void enter_directory(unsigned int index);

protected:
    std::deque<std::string> rows_004;
    std::deque<unsigned char> flags_018;
    std::deque<unsigned int> handles_02c;
    std::deque<FileListTile> render_items_040;
    std::string path_054;
    std::string filter_070;
    std::string directory_08c;
    int field_a8;
    int field_ac;
    unsigned char field_b0;
    unsigned char reserved_b1[3];
};

class CProfileList : public CFileList {
public:
    CProfileList();
    virtual void populate();
};

class CReplayList : public CFileList {
public:
    CReplayList();
    virtual unsigned int format_item(
        std::string *output,
        std::deque<std::string>::iterator current);
};

typedef char FileListTile_size_must_be_0xA4[
    sizeof(FileListTile) == 0xA4 ? 1 : -1];
typedef char CFileList_size_must_be_0xB4[
    sizeof(CFileList) == 0xB4 ? 1 : -1];
typedef char CProfileList_size_must_be_0xB4[
    sizeof(CProfileList) == 0xB4 ? 1 : -1];
typedef char CReplayList_size_must_be_0xB4[
    sizeof(CReplayList) == 0xB4 ? 1 : -1];
typedef char CFileList_string_iterator_size_must_be_0x0C[
    sizeof(std::deque<std::string>::iterator) == 0x0C ? 1 : -1];

} // namespace th105
