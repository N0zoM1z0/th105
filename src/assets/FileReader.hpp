#pragma once

extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);
extern "C" __declspec(dllimport) int __stdcall WriteFile(
    void *file, const void *buffer, unsigned long bytes_to_write,
    unsigned long *bytes_written, void *overlapped);
extern "C" __declspec(dllimport) unsigned long __stdcall SetFilePointer(
    void *file, long distance, long *distance_high, unsigned long origin);
extern "C" __declspec(dllimport) void *__stdcall CreateFileA(
    const char *path, unsigned long access, unsigned long share_mode,
    void *security_attributes, unsigned long creation_disposition,
    unsigned long flags, void *template_file);

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

class CFileWriter {
public:
    explicit CFileWriter(const char *path)
    {
        file = CreateFileA(path, 0x40000000u, 0, 0, 2, 0x80, 0);
        if (file == reinterpret_cast<FileHandle>(-1))
            file = 0;
    }

    virtual ~CFileWriter()
    {
        if (file != 0)
            CloseHandle(file);
    }

    virtual bool write(const void *source, FileSize size)
    {
        return WriteFile(file, source, size, &bytes_written, 0) != 0;
    }

    virtual FileSize last_write_size() const { return bytes_written; }

    virtual long seek(long offset, int origin)
    {
        return SetFilePointer(file, offset, 0, origin);
    }

    bool is_open() const { return file != 0; }

protected:
    FileHandle file;
    FileSize bytes_written;
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
