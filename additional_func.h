#ifndef SFINAE_IP_ADDITIONAL_FUNC_H
#define SFINAE_IP_ADDITIONAL_FUNC_H

#include <string>
#include <type_traits>

namespace additional
{

    template <typename T>
    struct is_string
    {
        static constexpr bool value = false;
    };

    template <>
    struct is_string<std::string>
    {
        static constexpr bool value = true;
    };

    template <typename T>
    inline constexpr bool is_string_v = is_string<T>::value;

    template<typename T>
    struct has_iterator
    {
    private:
        using yes = signed char;
        template <typename U>
        static yes test(typename U::iterator*);

        using no = unsigned char;
        template <typename U>
        static no  test(...);

    public:
        static constexpr bool value = std::is_same_v<decltype(test<T>(nullptr)), yes>;
    };

    template <typename T>
    inline constexpr bool has_iterator_v = has_iterator<T>::value;

}

#endif //SFINAE_IP_ADDITIONAL_FUNC_H
