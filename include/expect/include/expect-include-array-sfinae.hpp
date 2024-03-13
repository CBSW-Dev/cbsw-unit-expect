#pragma once

#include "expect-include-no-valid-include-exception.hpp"
#include "expect-include-not-found-exception.hpp"

#include <type_traits>

namespace CBSW::Unit::Expect::Internal {
    template <class TActual, class TExpected, class TLogic, class = void> class ToIncludeArray_SFINAE {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {

            throw NoValidIncludeMechanismExpection<TActual, TExpected, TLogic>(info, expected);
        }
    };

    template <class TActual, class TExpected, class TLogic>
    class ToIncludeArray_SFINAE<TActual, TExpected, TLogic, std::enable_if_t<std::is_same_v<bool, decltype(std::declval<TActual>()[0] == std::declval<TExpected>())>>> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            bool found = false;
            for (std::size_t i = 0; i < std::extent_v<TActual>; ++i) {
                if (info.actual[i] == expected) {
                    found = true;
                    break;
                }
            }
            if (TLogic::logic(!found)) {
                throw NotFoundException<TActual, TExpected, TLogic>(info, expected);
            }
        }
    };
}
