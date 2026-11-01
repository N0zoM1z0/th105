// Instantiate only the unchanged original public exception templates.
#define NDEBUG
#include <boost/throw_exception.hpp>
#include <stdexcept>

// Retain the original declaration attribute required by VC8 specialization.
template BOOST_ATTRIBUTE_NORETURN void boost::throw_exception(const std::logic_error &);
template BOOST_ATTRIBUTE_NORETURN void boost::throw_exception(const std::invalid_argument &);
