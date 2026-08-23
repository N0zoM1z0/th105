#include <deque>

std::deque<short>::iterator instantiate_deque_short_erase(
    std::deque<short> *deque,
    std::deque<short>::iterator position)
{
    return deque->erase(position);
}
