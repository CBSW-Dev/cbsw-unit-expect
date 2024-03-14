#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"
#include "expect-exception.hpp"
#include "expect-stream.hpp"
#include "expect-logic.hpp"

#include <sstream>
namespace CBSW::Unit::Expect::Internal {
    namespace {
        template <class TActual, class TLogic> class NotBooleanExceptionMessageBuilder {
        public:
            static std::string build(const TActual& actual) {
                std::stringstream ss;
                ss << Stream<TActual, std::stringstream>(actual);
                ss << " is not a boolean";

                return ss.str();
            }

        };

        template <class TActual, class TLogic> using NotBooleanException =
            ExpectUnaryException<TActual, TLogic, NotBooleanExceptionMessageBuilder<TActual, TLogic>>;

        template <class TActual, class TLogic> class ExpectBooleanExceptionMessageBuilder {
        public:
            static std::string build(const TActual& actual, bool expected) {
                std::stringstream ss;
                ss << Stream<TActual, std::stringstream>(actual);
                ss << " is";
                ss << TLogic::inverseString;
                ss << " ";
                ss << (expected ? "true" : "false");

                return ss.str();
            }
        };

        template <class TActual, class TLogic>
        class ExpectBooleanException: public ::CBSW::Unit::Exception {
        public:
            ExpectBooleanException(const Info<TActual>& info, bool expected) noexcept:
                Exception(info.testCase, ExpectBooleanExceptionMessageBuilder<TActual, TLogic>::build(info.actual, expected), info.filename, info.line)
            {}
        };
    }

    template <class TActual, class TLogic, class = void> class ToBeBoolean {
    public:
        static void run(const Info<TActual>& info, bool expected) {
            throw NotBooleanException<TActual, TLogic>(info);
        }
    };

    //is a boolean, N.B. this is enforced, i.e. truthy is not permitted here
    template <class TActual, class TLogic> class ToBeBoolean<TActual, TLogic, std::enable_if_t<std::is_same_v<bool, TActual>>> {
    public:
        static void run(const Info<TActual>& info, bool expected) {
            if (TLogic::logic(!(info.actual == expected))) {
                throw ExpectBooleanException<TActual, TLogic>(info, expected);
            }
        }
    };
}
