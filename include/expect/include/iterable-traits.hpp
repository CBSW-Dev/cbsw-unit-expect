#pragma once
#include <type_traits>

namespace CBSW::Unit::Expect::Internal {
    namespace {
        template <class T, class = void> struct IterableTraits_HasBeginAndEnd: std::false_type {};
        template <class T> struct IterableTraits_HasBeginAndEnd<T, std::enable_if_t<
            std::is_same_v<decltype(std::declval<T>().begin()),decltype(std::declval<T>().end())>
        >>: std::true_type {};

        template <class T> constexpr bool IterableTraits_HasBeginAndEnd_v = IterableTraits_HasBeginAndEnd<T>::value;

        template <class T, class = void> struct IterableTraits_HasDereferenceableIterator: std::false_type {};
        template <class T> struct IterableTraits_HasDereferenceableIterator<T, std::void_t<decltype(*std::declval<T>().begin())>>: std::true_type {};

        template <class T> constexpr bool IterableTraits_HasDereferenceableIterator_v = IterableTraits_HasDereferenceableIterator<T>::value;

        template <class T, class = void> struct IterableTraits_HasIncrementableIterator: std::false_type {};
        template <class T> struct IterableTraits_HasIncrementableIterator<T, std::void_t<decltype(++std::declval<T>().begin())>>: std::true_type {};

        template <class T> constexpr bool IterableTraits_HasIncrementableIterator_v = IterableTraits_HasIncrementableIterator<T>::value;
    }
    template <class T, class = void> struct IsIterable: std::false_type {};

    template <class T> struct IsIterable<T, std::enable_if_t<
        IterableTraits_HasBeginAndEnd_v<T> &&
        IterableTraits_HasDereferenceableIterator_v<T> &&
        IterableTraits_HasIncrementableIterator_v<T>
    >>: std::true_type {};

    template <class T> constexpr bool is_iterable_v = IsIterable<T>::value;
}
