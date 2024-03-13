#pragma once

#include "expect/expect-info.hpp"
#include "expect/expect-exception.hpp"
#include "expect/expect-stream.hpp"
#include "expect/expect-logic.hpp"

#include <sstream>

namespace CBSW::Unit::Expect::Internal {
    template <class TActual, class TExpected, class TLogic> class NoValidIncludeMechanismExpectionMessageBuilder {
    public:
        static std::string build(const TActual& actual, const TExpected& expected) {
            std::stringstream ss;
            ss << "No valid include mechanism for ";
            ss << Stream<TActual, std::stringstream>(actual);
            ss << " and ";
            ss << Stream<TExpected, std::stringstream>(expected);
            return ss.str();
        }
    };
    template <class TActual, class TExpected, class TLogic> using NoValidIncludeMechanismExpection =
        ExpectException<TActual, TExpected, TLogic, NoValidIncludeMechanismExpectionMessageBuilder<TActual, TExpected, TLogic>>;

}
