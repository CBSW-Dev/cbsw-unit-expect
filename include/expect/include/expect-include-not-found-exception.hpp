#pragma once

#include "expect/expect-info.hpp"
#include "expect/expect-exception.hpp"
#include "expect/expect-stream.hpp"
#include "expect/expect-logic.hpp"

#include <sstream>

namespace CBSW::Unit::Expect {
    template <class TActual, class TExpected, class TLogic> class NotFoundExceptionMessageBuilder {
    public:
        static std::string build(const TActual& actual, const TExpected& expected) {
            std::stringstream ss;
            ss << Stream<TExpected, std::stringstream>(expected);
            ss << " was";
            ss << TLogic::inverseString;
            ss << " found in ";
            ss << Stream<TActual, std::stringstream>(actual);

            return ss.str();
        }
    };
    template <class TActual, class TExpected, class TLogic> using NotFoundException =
        ExpectException<TActual, TExpected, TLogic, NotFoundExceptionMessageBuilder<TActual, TExpected, TLogic>>;
}
