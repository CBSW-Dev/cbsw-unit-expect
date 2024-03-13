#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"
#include "expect-to-be-greater-than.hpp"
#include "expect-to-be-greater-than-or-equal.hpp"
#include "expect-to-be-less-than.hpp"
#include "expect-to-be-less-than-or-equal.hpp"
#include "expect-to-be-null.hpp"


namespace CBSW::Unit::Expect::Internal {
    template <class TActual, class TLogic> class ToBe {
    public:
        ToBe(const Info<TActual>& info) noexcept:
            _info(info)
        {}

        template <class TExpected> void greaterThan(const TExpected& expected) {
            return ToBeGreaterThan<TActual, TExpected, TLogic>::run(_info, expected);
        }

        template <class TExpected> void greaterThanOrEqualTo(const TExpected& expected) {
            return ToBeGreaterThanOrEqual<TActual, TExpected, TLogic>::run(_info, expected);
        }

        template <class TExpected> void lessThan(const TExpected& expected) {
            return ToBeLessThan<TActual, TExpected, TLogic>::run(_info, expected);
        }

        template <class TExpected> void lessThanOrEqualTo(const TExpected& expected) {
            return ToBeLessThanOrEqual<TActual, TExpected, TLogic>::run(_info, expected);
        }

        void null() {
            return ToBeNull<TActual, TLogic>::run(_info);
        }
    private:
        const Info<TActual>& _info;
    };
}
