#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"
#include "expect-exception.hpp"
#include "expect-stream.hpp"
#include "expect-logic.hpp"

#include <sstream>
namespace CBSW::Unit::Expect {
    namespace {
        template <class TActual, class TLogic> class NotTruthyExceptionMessageBuilder {
        public:
            static std::string build(const TActual& actual) {
                std::stringstream ss;
                ss << Stream<TActual, std::stringstream>(actual);
                ss << " is not truthy";

                return ss.str();
            }

        };

        template <class TActual, class TLogic> using NotTruthyException =
            ExpectUnaryException<TActual, TLogic, NotTruthyExceptionMessageBuilder<TActual, TLogic>>;

        template <class TActual, class TLogic> class ExpectTruthyExceptionMessageBuilder {
        public:
            static std::string build(const TActual& actual, bool expected) {
                std::stringstream ss;
                ss << Stream<TActual, std::stringstream>(actual);
                ss << " is";
                ss << TLogic::inverseString;
                ss << " ";
                ss << (expected ? "truthy" : "falsy");

                return ss.str();
            }
        };

        template <class TActual, class TLogic>
        class ExpectTruthyException: public ::CBSW::Unit::Exception {
        public:
            ExpectTruthyException(const Info<TActual>& info, bool expected) noexcept:
                Exception(info.testCase, ExpectTruthyExceptionMessageBuilder<TActual, TLogic>::build(info.actual, expected), info.filename, info.line)
            {}
        };
    }

    template <class TActual, class TLogic, class = void> class ToBeTruthy {
    public:
        static void run(const Info<TActual>& info, bool expected) {
            throw NotTruthyException<TActual, TLogic>(info);
        }
    };

    //can be compared to a boolean
    template <class TActual, class TLogic> class ToBeTruthy<TActual, TLogic, std::void_t<decltype(std::declval<TActual>() == true)>> {
    public:
        static void run(const Info<TActual>& info, bool expected) {
            if (TLogic::logic(!(info.actual == expected))) {
                throw ExpectTruthyException<TActual, TLogic>(info, expected);
            }
        }
    };
}
