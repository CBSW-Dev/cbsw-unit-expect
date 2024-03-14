#include "test.hpp"

#include <iostream>

namespace {
    class TestBoolean {
    public:
        TestBoolean(bool value):
            _value(value)
        {}

        operator bool() const {
            return _value;
        }

        bool _value;
    };

    class TestNotBoolean {};
}

suite() {
    describe("Boolean") {
        it("demonstrates a passing test with a true value") {
            expect(1 == 1).to.be.booleanTrue();
        }

        it("demonstrates a failing test with a true value") {
            expect(1 == 0).to.be.booleanTrue();
        }

        it("demonstrates a passing test with a false value") {
            expect(1 == 0).to.be.booleanFalse();
        }

        it("demonstrates a failing test with a false value") {
            expect(1 == 1).to.be.booleanFalse();
        }

        it("demonstrates a failing test with a truthy value") {
            int x = 1;
            expect(x).to.be.booleanTrue();
        }

        it("demonstrates a failing test with an object that is castable to boolean") {
            const TestBoolean testBoolean(true);
            expect(testBoolean).to.be.booleanTrue();
        }
    }

    describe("Truthy") {
        it("demonstrates a passing test with a true value") {
            expect(1).to.be.truthy();
        }

        it("demonstrates a failing test with a true value") {
            expect(0).to.be.truthy();
        }

        it("demonstrates a passing test with a false value") {
            expect(0).to.be.falsy();
        }

        it("demonstrates a failing test with a false value") {
            expect(1).to.be.falsy();
        }

        it("demonstrates a passing test with an object that is castable to boolean") {
            const TestBoolean testBoolean(true);
            expect(testBoolean).to.be.truthy();
        }

        it("demonstrates a failing test with an object that is not castable to boolean") {
            const TestNotBoolean notBoolean;
            expect(notBoolean).to.be.truthy();
        }
    }
}


//stream operator for the TestBoolean Class
std::ostream& operator << (std::ostream& stream, const TestBoolean& testBoolean) {
    return stream << "TestBoolean(" << (testBoolean == true ? "true" : "false") << ")";
}

//stream operator for the TestNotBoolean Class
std::ostream& operator << (std::ostream& stream, const TestNotBoolean& notBoolean) {
    return stream << "TestNotBoolean()";
}