#include "test_tools/test_tools_time.h"

namespace boost::test_tools::tt_detail::impl
{

std::ostream& boost_test_print_type(std::ostream& os, std::chrono::time_point<std::chrono::system_clock> const& time_point)
{
	const std::time_t now_c = std::chrono::system_clock::to_time_t(time_point);
	os << std::put_time(std::localtime(&now_c), "%F %T");

	return os;
}

}
// namespace boost::test_tools::tt_detail::impl

