#pragma once
#include <type_traits>

namespace CBSW::Unit::Expect {
    template <class TActual, class TExpected, class = void> struct HasStdFind: std::false_type {};

    //std::find works by iterating from begin to end, and perform *it == end on the iterator,
    //so we cannot use std::find conformity as an SFINAE specialization, as it will be true for any type
    //and only resolved at compile time
    template <class TActual, class TExpected> struct HasStdFind<TActual, TExpected, std::void_t<
        decltype(*std::declval<TActual>().begin() == std::declval<TExpected>())
    >>: std::true_type {};

    template <class TActual, class TExpected> constexpr bool is_std_findable_v = HasStdFind<TActual, TExpected>::value;
}
