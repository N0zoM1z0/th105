#pragma once

namespace th105 {

typedef void *FileHandle;
typedef unsigned long FileSize;

class CFileReader {
public:
    virtual ~CFileReader();
    virtual bool read(void *destination, FileSize size);
    virtual FileSize last_read_size() const;
    virtual long seek(long offset, int origin);
    virtual FileSize size() const;

protected:
    friend class FileReaderOwner;

    FileHandle file;
    FileSize bytes_read;
};

class CPackageFileReader : public CFileReader {
public:
    virtual bool read(void *destination, FileSize size);
    virtual long seek(long offset, int origin);
    virtual FileSize size() const;

    FileSize entry_size;
    FileSize entry_offset;
    FileSize position;
    unsigned char xor_key;
    unsigned char reserved_19[3];
};

class FileReaderOwner {
public:
    FileReaderOwner() : reader(0) {}
    ~FileReaderOwner();

    bool open(const char *path);

    CFileReader *reader;
};

extern void *g_package_file_index;

FileHandle __stdcall open_package_file_entry(
    const char *path,
    FileSize *entry_size,
    FileSize *entry_offset);

} // namespace th105
