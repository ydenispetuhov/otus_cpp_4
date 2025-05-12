#ifndef META_H
#define META_H

#include <string>

namespace meta {

	template <int V>
	struct abs {
		static const int value = V < 0 ? -V : V;
	};

	template <int V>
	struct fact {
		static_assert(V > 0);
		static const int value = V * fact<V - 1>::value;
	};

	template <>
	struct fact<0> {
		static const int value = 1;
	};

	template <typename T>
	struct is_int {
		static const bool value = false;
	};

	template <>
	struct is_int<int> {
		static const bool value = true;
	};

    template <typename T>
    struct type_is {
        using type = T;
    };

    template <typename T>
    struct remove_const : type_is<T> {};

    template <typename T>
    struct remove_const<const T> : type_is<T> {};

    template <typename T>
    using remove_const_t = typename remove_const<T>::type;

    template <bool C, class T, class F>
    struct conditional : type_is<T> {};

    template <class T, class F>
    struct conditional<false, T, F> : type_is<F> {};

    template <class T, class F>
    struct conditional<true, T, F> : type_is<T> {};

    template <bool B, class T>
    struct enable_if : type_is<T> {};

    template <class T>
    struct enable_if<false, T> {};

    template<typename T>
    struct has_iterator
    {
    private:
        using yes =   signed char;
        using  no = unsigned char;

        template <typename U>
        static yes test(typename U::iterator*);

        template <typename U>
        static no  test(...);

    public:
        static constexpr bool value = std::is_same_v<decltype(test<T>(nullptr)), yes>;
    };

    template <typename T>
    inline constexpr bool has_iterator_v = has_iterator<T>::value;

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

    template <typename T, typename... Args>
    struct split_pack
    {
        using first = T;
    };

    template <typename... Args>
    struct check_tuple
    {
        static constexpr bool value = true;
    };

    template <typename T>
    struct check_tuple<T>
    {
        static constexpr bool value = true;
    };

    template <typename T, typename U, typename... Args>
    struct check_tuple<T, U, Args...>
    {
        static constexpr bool value = !std::is_same_v<T, U>
                                      ? false
                                      : check_tuple<U, Args...>::value;
    };

    template <typename... Args>
    inline constexpr bool check_tuple_v = check_tuple<Args...>::value;
}

#endif // META_H