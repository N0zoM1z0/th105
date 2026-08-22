#include "ProfileDeckEdit.hpp"

namespace th105 {

void CProfileDeckEdit::import_deck_counts(const ProfileDeckKeyDeque &source)
{
    counts_3c0.clear();

    for (ProfileDeckKeyDeque::const_iterator it = source.begin();
         it != source.end(); ++it) {
        ProfileDeckCountMap::iterator found = counts_3c0.find(*it);
        if (found == counts_3c0.end()) {
            ++total_3e1;
            counts_3c0.insert(
                std::make_pair(*it, static_cast<signed char>(1)));
        } else if (found->second < 4) {
            ++total_3e1;
            ++found->second;
        }
    }
}

void CProfileDeckEdit::export_deck_counts(ProfileDeckKeyDeque *destination)
{
    destination->clear();

    for (ProfileDeckCountMap::iterator it = counts_3c0.begin();
         it != counts_3c0.end(); ++it) {
        for (int repeat = 0; repeat < it->second && repeat < 4; ++repeat)
            destination->push_back(it->first);
    }
}

} // namespace th105
