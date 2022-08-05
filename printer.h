#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <tuple>

/*!
 * Print ip address presented by string.
 * \param ip The address to print.
 */
template<typename T>
std::enable_if_t<std::is_same<T, std::basic_string<typename T::value_type>>::value, void>
print_ip(const T &ip)
{
    std::cout << ip << std::endl;
}

/*!
 * Print ip address presented by integer.
 * \param ip The address to print.
 */
template<typename T>
typename std::enable_if_t<std::is_integral<T>::value> print_ip(const T& ip)
{
    size_t sz = sizeof(T);

    for (size_t i = 0; i < sz; ++i) {
        std::cout << (0xFF & (ip >> ((sz - i - 1) * 8)));

        (i != sz - 1) ? std::cout << "." : std::cout << std::endl;
    }
}

/*!
 * Print ip address presented by std::vector or std::list.
 * \param ip The address to print.
 */
template<typename T>
typename std::enable_if<std::is_same<typename std::vector<typename T::value_type>, T>::value
                        || std::is_same<typename std::list<typename T::value_type>, T>::value, void>::type
print_ip(const T &ip)
{
    for (auto it = ip.begin() ; it != ip.end(); ++it) {
        if (it != ip.begin())
            std::cout << ".";

        std::cout << *it;
    }

    std::cout << std::endl;
}

/*!
 * Helper function for check all tupple args are same.
 * \param T  typename of element
 * \param Ts initializer list (arguments)
 */
template<typename T, typename... Ts>
using AllSame = std::enable_if_t<std::conjunction_v<std::is_same<T, Ts>...>>;

/*!
 * Print ip address presented by std::tuple.
 * \param ip The address to print.
 */
template<typename T, typename... Args, typename = AllSame<T, Args...>>
void print_ip(std::tuple<T, Args...> ip) {
    std::apply([](auto &&... args) {
        size_t i = 0;
        ((std::cout << args << (i++ != sizeof...(Args) ? "." : "\n")), ...);
    }, ip);
}
