#pragma once

#include "expect-include-no-valid-include-exception.hpp"
#include "expect-include-not-found-exception.hpp"

#include "expect-include-string-sfinae.hpp"
#include "iterable-traits.hpp"
#include "std-find-traits.hpp"
#include "std-search-traits.hpp"

#include <string>
#include <functional>

namespace CBSW::Unit::Expect::Internal {
    //No valid iterable
    template <class TActual, class TExpected, class TLogic, class = void> class ToIncludeIterable_SFINAE_1 {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            throw NoValidIncludeMechanismExpection<TActual, TExpected, TLogic>(info, expected);
        }
    };

    //has a valid find mechanism
    template <class TActual, class TExpected, class TLogic> class ToIncludeIterable_SFINAE_1<TActual, TExpected, TLogic, std::enable_if_t<
        is_std_findable_v<TActual, TExpected>
    >> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            bool found = (std::find(info.actual.begin(), info.actual.end(), expected) != info.actual.end());
            if (TLogic::logic(!found)) {
                throw NotFoundException<TActual, TExpected, TLogic>(info, expected);
            }
        }
    };

    //has a valid std::search mechanism
    template <class TActual, class TExpected, class TLogic> class ToIncludeIterable_SFINAE_1<TActual, TExpected, TLogic, std::enable_if_t<
        is_std_searchable_v<TActual, TExpected>
    >> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            bool found = (std::search(info.actual.begin(), info.actual.end(), expected.begin(), expected.end()) != info.actual.end());
            if (TLogic::logic(!found)) {
                throw NotFoundException<TActual, TExpected, TLogic>(info, expected);
            }
        }
    };

    //forward to next SFINAE handler
    template <class TActual, class TExpected, class TLogic, class = void> class ToIncludeIterable_SFINAE {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            ToIncludeIterable_SFINAE_1<TActual, TExpected, TLogic>::run(info, expected);
        }
    };

    //Specialisation for std::string
    template <class TActual, class TExpected, class TLogic> class ToIncludeIterable_SFINAE<TActual, TExpected, TLogic, std::enable_if_t<
        std::is_same_v<std::string, TActual>
    >> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            ToIncludeString_SFINAE<TActual, TExpected, TLogic>::run(info, expected);
        }
    };
}

