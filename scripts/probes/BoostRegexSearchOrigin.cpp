// Instantiate the unchanged original public iterator/base search overload.
#define NDEBUG
#include <boost/regex.hpp>
#include <string>
typedef std::string::const_iterator SearchIterator;
typedef std::allocator<boost::sub_match<SearchIterator> > SearchAllocator;
template bool boost::regex_search(
    SearchIterator,SearchIterator,boost::match_results<SearchIterator,SearchAllocator>&,
    const boost::basic_regex<char,boost::regex_traits<char> >&,
    boost::match_flag_type,SearchIterator);
