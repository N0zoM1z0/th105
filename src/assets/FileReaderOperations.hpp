#pragma once

#include "assets/FileReader.hpp"

namespace th105 {

// Capture the real destination/length arguments before virtual reader dispatch.
// This ordinary forwarding helper is inlined naturally, without a forced ABI.
inline bool read_file_buffer(CFileReader *file, void *destination, FileSize size)
{
 return file->read(destination,size);
}

} // namespace th105
