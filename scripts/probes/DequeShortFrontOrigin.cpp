#include <deque>

// Taking the real member address retains its complete standard-library COMDAT.
// No game facade, custom guards, or copied instructions are provided.
typedef short &(std::deque<short>::*DequeShortFrontMember)();
DequeShortFrontMember instantiate_deque_short_front = &std::deque<short>::front;
