#ifndef IS_OPTIONAL_H
#define IS_OPTIONAL_H

#include <optional>
#include <type_traits>

template <typename T>
struct is_optional : std::false_type
{
};

template <typename T>
struct is_optional<std::optional<T>> : std::true_type
{
};

#endif // IS_OPTIONAL_H
