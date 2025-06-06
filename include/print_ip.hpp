/**
 * @file
 * @brief Header file with implementation of template function `print_ip`
 * @date 10.05.2025
*/

#ifndef PRINT_IP_H
#define PRINT_IP_H

#include "metafunctions.hpp"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <tuple>



namespace functions {

/**
 * Prints IP address
 * @tparam Integer integer number type, representing IP
 * @param[in] ip IP address to be printed
 * the format is: byte_n.---.byte_2.byte_1, where `n = sizeof(Integer)`
 * @param[in] stream output stream where to print IP address
*/
    template<typename Integer,
            typename Fake = std::enable_if_t<std::is_integral_v<Integer>, void>>
    void print_ip(Integer ip, std::ostream &stream = std::cout) {
        using UInteger = std::make_unsigned_t<Integer>;
        UInteger u_ip = *reinterpret_cast<UInteger *>(&ip);

        if constexpr (sizeof(UInteger) == 1) {
            int value = 0;
            for (std::size_t i = 0; i < 8; ++i)
                value += u_ip & (1 << i);
            stream << value;
            return;
        }

        std::size_t cur_shift = 8 * (sizeof(UInteger) - 1);
        UInteger mask = UInteger(255) << cur_shift;
        for (; mask != 0; mask >>= 8, cur_shift -= 8) {
            stream << ((mask & u_ip) >> cur_shift);
            if (cur_shift != 0)
                stream << '.';
        }
    }

/**
 * Prints IP address
 * @tparam Container type that satisfies Container C++ namedrequirement (except `std::string`)
 * @param[in] ip IP address to be printed
 * the format is: elem_1.elem_2.---.elem_n, where `n = ip.size()`
 * @param[in] stream output stream where to print IP address
*/
    template<typename Container,
            typename Fake = std::enable_if_t<meta::has_iterator_v < Container> &&
                            !meta::is_string_v < Container>, void>>

    void print_ip(const Container &ip, std::ostream &stream = std::cout) {
        if (ip.empty())
            return;
        const char *delim = ".";
        std::copy(ip.begin(), std::prev(ip.end()),
                  std::ostream_iterator<typename Container::value_type>(stream, delim));
        stream << *ip.rbegin();
    }

/**
 * Prints IP address
 * @tparam String only `std::string` is supported
 * @param[in] ip IP address to be printed
 * @param[in] stream output stream where to print IP address
*/
    template<typename String,
            typename Fake = std::enable_if_t<meta::is_string_v < String>, void>>

    void print_ip(const String &ip, std::ostream &stream = std::cout, Fake * /*placeholder*/ = nullptr) {
        stream << ip;
    }

    namespace detail {

        template<std::size_t index, typename... Args>
        void print_ip_tuple_helper(const std::tuple<Args...> &ip, std::ostream &stream = std::cout) {
            if constexpr (index >= sizeof...(Args)) {
                return;
            } else {
                stream << '.' << std::get<index>(ip);
                print_ip_tuple_helper<index + 1, Args...>(ip, stream);
            }
        }

    } // namespace detail

/**
 * Prints IP address
 * @tparam Args... type pack with identical types
 * @param[in] ip IP address to be printed
 * the format is: elem_1.elem_2.---.elem_n, where n is tuple size
 * @param[in] stream output stream where to print IP address
*/
    template<typename... Args,
            typename Fake = std::enable_if_t<meta::check_tuple_v < Args...>, void>>

    void print_ip(const std::tuple<Args...> &ip, std::ostream &stream = std::cout) {
        if constexpr (std::tuple_size<std::tuple<Args...>>::value == 0) {
            return;
        } else {
            stream << std::get<0>(ip);
            detail::print_ip_tuple_helper<1, Args...>(ip, stream);
        }
    }

} // namespace my

#endif // PRINT_IP_H
