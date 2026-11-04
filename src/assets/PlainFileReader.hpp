#pragma once

#include <windows.h>

namespace th105 {

class PlainFileReader {
public:
    explicit PlainFileReader(const char *path) {
        handle = CreateFileA(path, 1, 1, 0, 3, 0x80, 0);
        if (handle == INVALID_HANDLE_VALUE) handle = 0;
    }
    virtual ~PlainFileReader() { if (handle) CloseHandle(handle); }
    virtual bool read(void *out, unsigned long count) { return ReadFile(handle, out, count, &last_count, 0) != 0; }
    virtual unsigned long last_read_size() const { return last_count; }
    virtual long seek(long offset, int origin) { return SetFilePointer(handle, offset, 0, origin); }
    virtual unsigned long size() const { return GetFileSize(handle, 0); }
    HANDLE handle;
    unsigned long last_count;
};
typedef char PlainFileReader_size_must_be_12[sizeof(PlainFileReader) == 12 ? 1 : -1];

} // namespace th105
