#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"
#include "expect-to-be.hpp"
#include "expect-to-equal.hpp"
#include "include/expect-to-include.hpp"

namespace CBSW::Unit::Expect::Internal {
    template <class TActual, class TLogic> class To {
    public:
        To(const Info<TActual>& info) noexcept:
            be(info),
            _info(info)
        {}

        template <class TExpected> void equal(const TExpected& expected) {
            return ToEqual<TActual, TExpected, TLogic>::run(_info, expected);
        }

        template <class TExpected> void include(const TExpected& expected) {
            return ToInclude<TActual, TExpected, TLogic>::run(_info, expected);
        }

        ToBe<TActual, TLogic> be;
    private:
        const Info<TActual>& _info;
    };
}
