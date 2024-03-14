#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"
#include "expect-to-be.hpp"
#include "expect-to-equal.hpp"
#include "include/expect-to-include.hpp"

namespace CBSW::Unit::Expect {
    template <class TActual, class TLogic> class ToBase {
    public:
        ToBase(const Info<TActual>& info) noexcept:
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
    protected:
        const Info<TActual>& _info;
    };

    template <class TActual, class TLogic, class = void> class To: public ToBase<TActual, TLogic> {
    public:
       using ToBase<TActual, TLogic>::ToBase;
    };
}
