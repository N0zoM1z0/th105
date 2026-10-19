#include <string>

// Compiler-library method already identified at 0x4102D0 by the independent
// native CFileList anchor. Its ordinary callable ABI constrains dependent CIL
// template calls. The original TU is unknown; this adds no authored credit.
template void std::allocator<std::string>::destroy(std::string *);
