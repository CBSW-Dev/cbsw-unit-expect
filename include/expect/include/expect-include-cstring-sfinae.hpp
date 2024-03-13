#pragma once

#include "expect-include-no-valid-include-exception.hpp"
#include "expect-include-not-found-exception.hpp"

#include <type_traits>
#include <cstring>

namespace CBSW::Unit::Expect::Internal {


    template <class TActual, class TExpected, class TLogic, class = void> class ToIncludeCString_SFINAE {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {

            throw NoValidIncludeMechanismExpection<TActual, TExpected, TLogic>(info, expected);
        }
    };

    template <class TActual, class TExpected, class TLogic>
    class ToIncludeCString_SFINAE<TActual, TExpected, TLogic, std::enable_if_t<std::is_same_v<char, TExpected>>> {
    public:
        static void run(const Info<TActual>& info, char expected) {
            bool found = false;
            for (const char* it = info.actual; *it != 0; ++it) {
                if (*it == expected) {
                    found = true;
                    break;
                }
            }
            if (TLogic::logic(!found)) {
                throw NotFoundException<TActual, TExpected, TLogic>(info, expected);
            }
        }
    };

    template <class TActual, class TExpected, class TLogic>
    class ToIncludeCString_SFINAE<TActual, TExpected, TLogic, std::enable_if_t<std::is_same_v<char*, std::remove_cv_t<TExpected>>>> {
    public:
        static void run(const Info<TActual>& info, const char* expected) {
            bool found = (::strstr(info.actual, expected) != nullptr);;
            if (TLogic::logic(!found)) {
                throw NotFoundException<TActual, TExpected, TLogic>(info, expected);
            }
        }
    };

    template <class TActual, class TExpected, class TLogic>
    class ToIncludeCString_SFINAE<TActual, TExpected, TLogic, std::enable_if_t<std::is_array_v<TExpected> && std::is_same_v<char, std::remove_extent_t<TExpected>>>> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            bool found = (::strstr(info.actual, expected) != nullptr);;
            if (TLogic::logic(!found)) {
                throw NotFoundException<TActual, TExpected, TLogic>(info, expected);
            }
        }
    };
}
