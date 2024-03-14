#include "test.hpp"

#include <string>

namespace {
    class Base {
    public:
        virtual ~Base() = default;

        virtual bool booleanValue() const noexcept = 0;
        virtual bool truthyValue() const noexcept = 0;
    };

    class Derived: public Base {
    public:
        Derived(bool boolean, bool truthy):
            _boolean(boolean),
            _truthy(truthy)
        {}

        bool booleanValue() const noexcept override {
            return _boolean;
        }

        bool truthyValue() const noexcept override {
            return _truthy;
        }
    private:
        bool _boolean;
        bool _truthy;
    };
}

namespace CBSW::Unit::Expect {
    template <class TActual, class TLogic> class ToBeBoolean<TActual, TLogic, std::enable_if_t<
        std::is_base_of_v<Base, TActual>
    >> {
    public:
        static std::string makeMessage(const TActual& actual, bool expected) {
            std::stringstream ss;
            ss << "Expected Object" << TLogic::string << " to be " << (expected ? "true" : "false");
            return ss.str();
        }

        static void run(const Info<TActual>& info, bool expected) {
            if (TLogic::logic(!(info.actual.booleanValue() == expected))) {
                throw Exception(info.testCase, makeMessage(info.actual, expected), info.filename, info.line);
            }
        }
    };

    template <class TActual, class TLogic> class ToBeTruthy<TActual, TLogic, std::enable_if_t<
        std::is_base_of_v<Base, TActual>
    >> {
    public:
        static std::string makeMessage(const TActual& actual, bool expected) {
            std::stringstream ss;
            ss << "Expected Object" << TLogic::string << " to be " << (expected ? "truthy" : "falsy");
            return ss.str();
        }

        static void run(const Info<TActual>& info, bool expected) {
            if (TLogic::logic(!(info.actual.truthyValue() == expected))) {
                throw Exception(info.testCase, makeMessage(info.actual, expected), info.filename, info.line);
            }
        }
    };
}

suite() {
    describe("Expect To Be Boolean") {
        it("demonstrates a passing custom test (true-true)") {
            Derived boolean(true, false);
            expect(boolean).to.be.booleanTrue();
        }

        it("demonstrates a passing custom test (false-false)") {
            Derived boolean(false, false);
            expect(boolean).to.be.booleanFalse();
        }

        it("demonstrates a failing custom test (true-false)") {
            Derived boolean(true, false);
            expect(boolean).to.be.booleanFalse();
        }

        it("demonstrates a passing custom test (true-false, inverse logic)") {
            Derived boolean(true, false);
            expect(boolean).notTo.be.booleanFalse();
        }

        it("demonstrates a passing custom test (false-true, inverse logic)") {
            Derived boolean(false, false);
            expect(boolean).notTo.be.booleanTrue();
        }

        it("demonstrates a failing custom test (true-true, inverse logic)") {
            Derived boolean(true, false);
            expect(boolean).notTo.be.booleanTrue();
        }

        it("demonstrates a passing custom test (truthy-truthy)") {
            Derived boolean(false, true);
            expect(boolean).to.be.truthy();
        }

        it("demonstrates a passing custom test (falsy-falsy)") {
            Derived boolean(false, false);
            expect(boolean).to.be.falsy();
        }

        it("demonstrates a failing custom test (truthy-falsy)") {
            Derived boolean(false, true);
            expect(boolean).to.be.falsy();
        }

        it("demonstrates a passing custom test (truthy-falsy, inverse logic)") {
            Derived boolean(false, true);
            expect(boolean).notTo.be.falsy();
        }

        it("demonstrates a passing custom test (falsy-truthy, inverse logic)") {
            Derived boolean(false, false);
            expect(boolean).notTo.be.truthy();
        }

        it("demonstrates a failing custom test (truthy-truthy, inverse logic)") {
            Derived boolean(false, true);
            expect(boolean).notTo.be.truthy();
        }
    }
}