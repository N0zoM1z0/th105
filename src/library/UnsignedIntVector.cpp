#include <vector>

// Compiler-library context, excluded from authored progress. Compile without
// /GL to preserve the ordinary shared vector ABI; original TU remains unknown.
template class std::vector<unsigned int>;
