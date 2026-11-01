// Original public Boost regex exception specialization; no replacement body.
#define NDEBUG
#include <boost/regex.hpp>
#include <boost/throw_exception.hpp>
template BOOST_ATTRIBUTE_NORETURN void boost::throw_exception(const boost::regex_error &);
