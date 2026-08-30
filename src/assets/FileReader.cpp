#include "FileReader.hpp"

extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);
extern "C" __declspec(dllimport) int __stdcall ReadFile(
    void *file,
    void *buffer,
    unsigned long bytes_to_read,
    unsigned long *bytes_read,
    void *overlapped);
extern "C" __declspec(dllimport) unsigned long __stdcall SetFilePointer(
    void *file,
    long distance,
    long *distance_high,
    unsigned long origin);
extern "C" __declspec(dllimport) unsigned long __stdcall GetFileSize(
    void *file,
    unsigned long *size_high);
extern "C" __declspec(dllimport) void *__stdcall CreateFileA(
    const char *path,
    unsigned long access,
    unsigned long share_mode,
    void *security_attributes,
    unsigned long creation_disposition,
    unsigned long flags,
    void *template_file);

namespace th105 {

void *g_package_file_index;

CFileReader::~CFileReader()
{
    if (file != 0)
        CloseHandle(file);
}

bool CFileReader::read(void *destination, FileSize size)
{
    return ReadFile(file, destination, size, &bytes_read, 0) != 0;
}

FileSize CFileReader::last_read_size() const
{
    return bytes_read;
}

long CFileReader::seek(long offset, int origin)
{
    return SetFilePointer(file, offset, 0, origin);
}

FileSize CFileReader::size() const
{
    return GetFileSize(file, 0);
}

bool CPackageFileReader::read(void *destination, FileSize size)
{
    if (entry_offset + entry_size < position + size)
        size = entry_offset + entry_size - position;

    ReadFile(file, destination, size, &bytes_read, 0);
    if (bytes_read == 0)
        return false;

    position += bytes_read;
    for (FileSize i = 0; i < size; i++)
        static_cast<unsigned char *>(destination)[i] ^= xor_key;
    return true;
}

long CPackageFileReader::seek(long offset, int origin)
{
    switch (origin) {
    case 0:
        position =
            SetFilePointer(file, entry_offset + offset, 0, 0) - entry_offset;
        return position;
    case 1:
        position = SetFilePointer(file, offset, 0, 1) - entry_offset;
        return position;
    case 2:
        position = SetFilePointer(
                       file,
                       entry_size - offset + entry_offset,
                       0,
                       0) -
            entry_offset;
        return position;
    default:
        return 0;
    }
}

FileSize CPackageFileReader::size() const
{
    return entry_size;
}

FileReaderOwner::~FileReaderOwner()
{
    if (reader != 0)
        delete reader;
}

bool FileReaderOwner::open(const char *path)
{
    if (reader != 0)
        delete reader;

    if (g_package_file_index != 0) {
        CPackageFileReader *package_reader = new CPackageFileReader;
        package_reader->file = 0;
        package_reader->file = open_package_file_entry(
            path,
            &package_reader->entry_size,
            &package_reader->entry_offset);
        package_reader->position = package_reader->entry_offset;
        if (package_reader->file != 0)
            package_reader->xor_key = static_cast<unsigned char>(
                (package_reader->entry_offset >> 1) | 0x23);
        reader = package_reader;
    } else {
        CFileReader *plain_reader = new CFileReader;
        plain_reader->file = CreateFileA(
            path,
            1,
            1,
            0,
            3,
            0x80,
            0);
        if (plain_reader->file == reinterpret_cast<FileHandle>(-1))
            plain_reader->file = 0;
        reader = plain_reader;
    }

    if (reader->file == 0) {
        delete reader;
        reader = 0;
        return false;
    }
    return true;
}

} // namespace th105
