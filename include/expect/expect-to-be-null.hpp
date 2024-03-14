#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"
#include "expect-to-be-greater-than.hpp"
#include "expect-to-be-greater-than-or-equal.hpp"
#include "expect-to-be-less-than.hpp"
#include "expect-to-be-less-than-or-equal.hpp"

namespace CBSW::Unit::Expect {
    namespace {
        template <class TActual, class TLogic> class NotNullableExceptionMessageBuilder {
        public:
            static std::string build(const TActual& actual) {
                std::stringstream ss;
                ss << Stream<TActual, std::stringstream>(actual);
                ss << " is not nullable";

                return ss.str();
            }

        };

        template <class TActual, class TLogic> using NotNullableException =
            ExpectUnaryException<TActual, TLogic, NotNullableExceptionMessageBuilder<TActual, TLogic>>;

        template <class TActual, class TLogic> class NotNullExceptionMessageBuilder {
        public:
            static std::string build(const TActual& actual) {
                std::stringstream ss;
                ss << Stream<TActual, std::stringstream>(actual);
                ss << " is";
                ss << TLogic::inverseString;
                ss << " null";

                return ss.str();
            }
        };

        template <class TActual, class TLogic> using NotNullException =
            ExpectUnaryException<TActual, TLogic, NotNullExceptionMessageBuilder<TActual, TLogic>>;
    }

    template <class TActual, class TLogic, class = void> class ToBeNull {
    public:
        static void run(const Info<TActual>& info) {
            throw NotNullableException<TActual, TLogic>(info);
        }
    };

    //can be statically cast to a void*
    template <class TActual, class TLogic> class ToBeNull<TActual, TLogic, std::void_t<decltype(static_cast<void*>(std::declval<std::remove_cv_t<TActual>>()))>> {
    public:
        static void run(const Info<TActual>& info) {
            if (TLogic::logic(!(static_cast<const void*>(info.actual) == nullptr))) {
                throw NotNullException<TActual, TLogic>(info);
            }
        }
    };
}
