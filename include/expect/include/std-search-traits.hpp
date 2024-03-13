#pragma once
#include <type_traits>

namespace CBSW::Unit::Expect::Internal {
    template <class TActual, class TExpected, class = void> struct HasStdSearch: std::false_type {};

    //std::serach works by iterating from begin to end (and s_begin to s_end), and perform *it == *s_it on the iterators,
    //so we cannot use std::search conformity as an SFINAE specialization, as it will be true for any type
    //and only resolved at compile time
    template <class TActual, class TExpected> struct HasStdSearch<TActual, TExpected, std::void_t<
        decltype(*std::declval<TActual>().begin() == *std::declval<TExpected>().begin())
    >>: std::true_type {};

    template <class TActual, class TExpected> constexpr bool is_std_searchable_v = HasStdSearch<TActual, TExpected>::value;
}
