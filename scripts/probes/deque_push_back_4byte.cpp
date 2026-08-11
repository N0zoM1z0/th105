#include <deque>

// Force VC8 SP1 to emit the out-of-line four-byte deque specialization used
// by target function 0x00416A50.
template class std::deque<unsigned long>;
