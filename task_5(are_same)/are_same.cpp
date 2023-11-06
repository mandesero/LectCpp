#include <iostream>
#include <type_traits>

template <typename...>
struct are_same : std::true_type{};

template <typename T, typename U, typename... Args>
struct are_same<T, U, Args...> : std::false_type{};

template <typename T, typename... Args>
struct are_same<T, T, Args...> : are_same<T, Args...>{};

template <typename... Args>
constexpr bool are_same_v = are_same<Args...>::value;

int main()
{
    static_assert(are_same_v<int, int32_t, signed int>, "compile assert");
    static_assert(!are_same_v<int, int32_t, unsigned int>, "compile assert");
    return 0;
}