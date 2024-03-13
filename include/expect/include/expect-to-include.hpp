#pragma once

#include "expect-include-no-valid-include-exception.hpp"
#include "expect-include-array-sfinae.hpp"
#include "expect-include-cstring-sfinae.hpp"
#include "expect-include-iterable-sfinae.hpp"
#include <type_traits>

namespace CBSW::Unit::Expect::Internal {
    template <class TActual, class TExpected, class TLogic, class = void> class ToInclude {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            throw NoValidIncludeMechanismExpection<TActual, TExpected, TLogic>(info, expected);
        }
    };

    template <class TActual, class TExpected, class TLogic> class ToInclude<TActual, TExpected, TLogic, std::enable_if_t<std::is_array_v<TActual>>> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            ToIncludeArray_SFINAE<TActual, TExpected, TLogic>::run(info, expected);
        }
    };

    template <class TActual, class TExpected, class TLogic> class ToInclude<TActual, TExpected, TLogic, std::enable_if_t<std::is_same_v<char*, std::remove_cv_t<TActual>>>> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            ToIncludeCString_SFINAE<TActual, TExpected, TLogic>::run(info, expected);
        }
    };

    template <class TActual, class TExpected, class TLogic> class ToInclude<TActual, TExpected, TLogic, std::enable_if_t<is_iterable_v<TActual>>> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            ToIncludeIterable_SFINAE<TActual, TExpected, TLogic>::run(info, expected);
        }
    };
}
