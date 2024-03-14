#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"
#include "expect-to-be-greater-than.hpp"
#include "expect-to-be-greater-than-or-equal.hpp"
#include "expect-to-be-less-than.hpp"
#include "expect-to-be-less-than-or-equal.hpp"
#include "expect-to-be-null.hpp"
#include "expect-to-be-boolean.hpp"
#include "expect-to-be-truthy.hpp"

namespace CBSW::Unit::Expect {
    template <class TActual, class TLogic> class ToBeBase {
    public:
        ToBeBase(const Info<TActual>& info) noexcept:
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

        void booleanTrue() {
            return ToBeBoolean<TActual, TLogic>::run(_info, true);
        }

        void booleanFalse() {
            return ToBeBoolean<TActual, TLogic>::run(_info, false);
        }

        void truthy() {
            return ToBeTruthy<TActual, TLogic>::run(_info, true);
        }

        void falsy() {
            return ToBeTruthy<TActual, TLogic>::run(_info, false);
        }
    protected:
        const Info<TActual>& _info;
    };

    template <class TActual, class TLogic, class = void> class ToBe: public ToBeBase<TActual, TLogic> {
    public:
        using ToBeBase<TActual, TLogic>::ToBeBase;
    };
}
