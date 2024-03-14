#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"
#include "expect-exception.hpp"
#include "expect-stream.hpp"
#include "expect-logic.hpp"

#include <sstream>
#include <type_traits>

namespace CBSW::Unit::Expect {
    namespace {
        template <class TActual, class TExpected, class TLogic, class TOperator> class BinaryOperatorExceptionMessageBuilder {
        public:
            static std::string build(const TActual& actual, const TExpected& expected) {
                std::stringstream ss;
                ss << "Expected ";
                ss << Stream<TActual, std::stringstream>(actual);
                ss << TLogic::string;
                ss << " ";
                ss << TOperator::phrase;
                ss << " ";
                ss << Stream<TExpected, std::stringstream>(expected);
                return ss.str();
            }
        };
        template <class TActual, class TExpected, class TLogic, class TOperator> using BinaryOperatorException =
            ExpectException<TActual, TExpected, TLogic, BinaryOperatorExceptionMessageBuilder<TActual, TExpected, TLogic, TOperator>>;

        template <class TActual, class TExpected, class TLogic, class TOperator> class NoBinaryOperatorExceptionMessageBuilder {
        public:
            static std::string build(const TActual& actual, const TExpected& expected) {
                std::stringstream ss;
                ss << "No valid ";
                ss << TOperator::string;
                ss << " operator (";
                ss << TOperator::symbol;
                ss << ") for ";
                ss << Stream<TActual, std::stringstream>(actual);
                ss << " and ";
                ss << Stream<TExpected, std::stringstream>(expected);
                return ss.str();
            }
        };
        template <class TActual, class TExpected, class TLogic, class TOperator> using NoBinaryOperatorOperatorException =
            ExpectException<TActual, TExpected, TLogic, NoBinaryOperatorExceptionMessageBuilder<TActual, TExpected, TLogic, TOperator>>;
    }

    template <class TActual, class TExpected, class TLogic, class TOperator, class = void> class BinaryOperator {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            throw NoBinaryOperatorOperatorException<TActual, TExpected, TLogic, TOperator>(info, expected);
        }
    };

    template <class TActual, class TExpected, class TLogic, class TOperator> class BinaryOperator<TActual, TExpected, TLogic, TOperator, typename TOperator::enable_if_t<TActual, TExpected>> {
    public:
        static void run(const Info<TActual>& info, const TExpected& expected) {
            if (TLogic::logic(!(TOperator::condition(info.actual, expected)))) {
                throw BinaryOperatorException<TActual, TExpected, TLogic, TOperator>(info, expected);
            }
        }
    };
}