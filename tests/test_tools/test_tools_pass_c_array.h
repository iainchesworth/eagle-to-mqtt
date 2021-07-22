#ifndef TEST_TOOLS_PASS_C_ARRAY_H
#define TEST_TOOLS_PASS_C_ARRAY_H

#include <array>
#include <cstddef>

namespace test_tools
{

template <typename ARRAY_VALUE_TYPE, std::size_t size>
using CArray = ARRAY_VALUE_TYPE[size];

template <typename ARRAY_VALUE_TYPE, std::size_t array_element_count>
CArray<ARRAY_VALUE_TYPE, array_element_count>& c_array_cast(std::array<ARRAY_VALUE_TYPE, array_element_count>& arg)
{
    {
        return *reinterpret_cast<CArray<ARRAY_VALUE_TYPE, array_element_count>*>(arg.data());
    }
}

}
// namespace test_tools

#endif // TEST_TOOLS_PASS_C_ARRAY_H
