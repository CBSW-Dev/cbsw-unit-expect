#pragma once

#include "expect-binary-operator.hpp"

namespace CBSW::Unit::Expect {
    namespace {
        class GreaterThanOrEqualOperator {
        public:
            static const std::string phrase;
            static const std::string string;
            static const std::string symbol;
            template <class TActual, class TExpected> static bool condition(const TActual& actual, const TExpected& expected) noexcept {
                return actual >= expected;
            }

            template <class TActual, class TExpected> using enable_if_t = std::enable_if_t<std::is_same_v<bool, decltype(std::declval<TActual>() >= std::declval<TExpected>())>>;
        };

        const std::string GreaterThanOrEqualOperator::phrase = "to be greater than or equal to";
        const std::string GreaterThanOrEqualOperator::string = "greater than or equals";
        const std::string GreaterThanOrEqualOperator::symbol = ">=";
    }

    template <class TActual, class TExpected, class TLogic, class = void> class ToBeGreaterThanOrEqual: public BinaryOperator<TActual, TExpected, TLogic, GreaterThanOrEqualOperator> {};
}