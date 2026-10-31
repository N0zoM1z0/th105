#include <string>
// Take the actual standard member address to retain its genuine VC8 body.
typedef std::string &(std::string::*StringAppendCountMember)(std::string::size_type, char);
StringAppendCountMember string_append_count_origin_anchor = &std::string::append;
