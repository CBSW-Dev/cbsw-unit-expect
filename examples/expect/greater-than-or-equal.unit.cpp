#include "test.hpp"

namespace {
    template <bool value> class TestGreaterThanOrEqual {
    public:
        bool operator >= (int x) const noexcept {
            (void)x;
            return value;
        }
    };

    class NonGreaterThanOrEqual {};
}

suite() {
    describe("Greater than or equal") {
        it("demonstrates a passing test when comparing numeric literals") {
            expect(1).to.be.greaterThanOrEqualTo(1);
        }

        it("demonstrates a failing test when comparing numeric literals") {
            expect(1).to.be.greaterThanOrEqualTo(2);
        }

        it("demonstrates a passing test when comparing numeric variables") {
            int x = 1;
            int y = 1;
            expect(x).to.be.greaterThanOrEqualTo(y);
        }

        it("demonstrates a failing test when comparing numeric literals") {
            int x = 1;
            int y = 2;
            expect(x).to.be.greaterThanOrEqualTo(y);
        }

        it("demonstrates a passing test when comparing std::string to const char* literals") {
            expect(std::string("Hello")).to.be.greaterThanOrEqualTo("Hello");
        }

        it("demonstrates a failing test when comparing std::string to const char* literals") {
            expect(std::string("Aello")).to.be.greaterThanOrEqualTo("Zello");
        }

        it("demonstrates a passing test when comparing an object with a greater than or equal operator") {
            const TestGreaterThanOrEqual<true> tgtoe;
            expect(tgtoe).to.be.greaterThanOrEqualTo(1);
        }

        it("demonstrates a failing test when comparing an object with a greater than or equal operator") {
            const TestGreaterThanOrEqual<false> tgtoe;
            expect(tgtoe).to.be.greaterThanOrEqualTo(1);
        }

        it("demonstrates a failing test due to no comparison operator") {
            const TestGreaterThanOrEqual<true> tgtoe;
            //No comparison operator
            expect(tgtoe).to.be.greaterThanOrEqualTo(NonGreaterThanOrEqual());
        }
    }
}

//stream operator for the TestCompare Class
template<bool value> std::ostream& operator << (std::ostream& stream, const TestGreaterThanOrEqual<value>& compare) {
    return stream << "TestGreaterThanOrEqual<" << (value ? "true" : "false") << ">";
}

//stream operator for the NonComparable Class
std::ostream& operator << (std::ostream& stream, const NonGreaterThanOrEqual& nonComparable) {
    return stream << "NonGreaterThanOrEqual";
}