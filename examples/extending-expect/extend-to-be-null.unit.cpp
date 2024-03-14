#include "test.hpp"

#include <string>

namespace {
    class Base {
    public:
        virtual ~Base() = default;

        virtual bool isNull() const noexcept = 0;
    };

    class NullObject: public Base {
    public:
        bool isNull() const noexcept override {
            return true;
        }
    };

    class NonNullObject: public Base {
    public:
        bool isNull() const noexcept override {
            return false;
        }
    };
}

namespace CBSW::Unit::Expect {
    template <class TActual, class TLogic> class ToBeNull<TActual, TLogic, std::enable_if_t<
        std::is_base_of_v<Base, TActual>
    >> {
    public:
        static std::string makeMessage(const TActual& actual) {
            std::stringstream ss;
            ss << "Expected Object" << TLogic::string << " to be null";
            return ss.str();
        }

        static void run(const Info<TActual>& info) {
            if (TLogic::logic(!(info.actual.isNull()))) {
                throw Exception(info.testCase, makeMessage(info.actual), info.filename, info.line);
            }
        }
    };
}


suite() {
    describe("Expect To Be Null") {
        it("demonstrates a passing custom test (null)") {
            NullObject nullObject;
            expect(nullObject).to.be.null();
        }

        it("demonstrates a failing custom test (non-null)") {
            NonNullObject nonNullObject;
            expect(nonNullObject).to.be.null();
        }

        it("demonstrates a passing custom test (non-null, inverse logic)") {
            NonNullObject nonNullObject;
            expect(nonNullObject).notTo.be.null();
        }

        it("demonstrates a failing custom test (null, inverse logic)") {
            NullObject nullObject;
            expect(nullObject).notTo.be.null();
        }
    }
}