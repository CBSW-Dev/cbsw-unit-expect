#pragma once

#include "expect-binary-operator.hpp"

namespace CBSW::Unit::Expect::Internal {
    namespace {
        class LessThanOrEqualOperator {
        public:
            static const std::string phrase;
            static const std::string string;
            static const std::string symbol;
            template <class TActual, class TExpected> static bool condition(const TActual& actual, const TExpected& expected) noexcept {
                return actual <= expected;
            }

            template <class TActual, class TExpected> using enable_if_t = std::enable_if_t<std::is_same_v<bool, decltype(std::declval<TActual>() <= std::declval<TExpected>())>>;
        };

        const std::string LessThanOrEqualOperator::phrase = "to be less than or equal to";
        const std::string LessThanOrEqualOperator::string = "less than or equals";
        const std::string LessThanOrEqualOperator::symbol = "<=";
    }

    template <class TActual, class TExpected, class TLogic> using ToBeLessThanOrEqual = BinaryOperator<TActual, TExpected, TLogic, LessThanOrEqualOperator>;
}