#pragma once

#include "expect-include-no-valid-include-exception.hpp"
#include "expect-include-not-found-exception.hpp"


#include <type_traits>
#include <cstring>

namespace CBSW::Unit::Expect::Internal {
    template <class TActual, class TExpected, class TLogic, class = void> class ToIncludeString_SFINAE {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            throw NoValidIncludeMechanismExpection<TActual, TExpected, TLogic>(info, expected);
        }
    };

    //constructible to a string
    template <class TActual, class TExpected, class TLogic>
    class ToIncludeString_SFINAE<TActual, TExpected, TLogic, std::void_t<decltype(std::string(std::declval<TExpected>()))>> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            std::string expectedAsString(expected);
            bool found = (info.actual.find(expected) != info.actual.npos);

            if (TLogic::logic(!found)) {
                throw NotFoundException<TActual, TExpected, TLogic>(info, expected);
            }
        }
    };

    //expected is a char
    template <class TActual, class TExpected, class TLogic>
    class ToIncludeString_SFINAE<TActual, TExpected, TLogic, std::enable_if_t<std::is_same_v<char, TExpected>>> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            bool found = (info.actual.find(expected) != info.actual.npos);

            if (TLogic::logic(!found)) {
                throw NotFoundException<TActual, TExpected, TLogic>(info, expected);
            }
        }
    };
}
