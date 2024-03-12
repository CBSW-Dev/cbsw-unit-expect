#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"

namespace CBSW::Unit::Expect::Internal {
    template <class TActual, class TExpected, class TLogic, class TMessageBuilder>
    class ExpectException: public ::CBSW::Unit::Exception {
    public:
        ExpectException(const Info<TActual>& info, const TExpected& expected) noexcept:
            Exception(info.testCase, TMessageBuilder::build(info.actual, expected), info.filename, info.line)
        {}
    };
}