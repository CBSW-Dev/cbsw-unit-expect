#include "test.hpp"

namespace {
    template <bool value> class TestLessThanOrEqual {
    public:
        bool operator <= (int x) const noexcept {
            (void)x;
            return value;
        }
    };

    class NonLessThanOrEqual {};
}

suite() {
    describe("Less than or equal") {
        it("demonstrates a passing test when comparing numeric literals") {
            expect(1).to.be.lessThanOrEqualTo(1);
        }

        it("demonstrates a failing test when comparing numeric literals") {
            expect(2).to.be.lessThanOrEqualTo(1);

        }

        it("demonstrates a passing test when comparing numeric variables") {
            int x = 1;
            int y = 1;
            expect(x).to.be.lessThanOrEqualTo(y);
        }

        it("demonstrates a failing test when comparing numeric literals") {
            int x = 2;
            int y = 1;
            expect(x).to.be.lessThanOrEqualTo(y);
        }

        it("demonstrates a passing test when comparing boolean literals") {
            //allowed, but semantically wrong
            expect(true).to.be.lessThanOrEqualTo(true);

        }

        it("demonstrates a failing test when comparing boolean literals") {
            //allowed, but semantically wrong
            expect(true).to.be.lessThanOrEqualTo(false);
        }

        it("demonstrates a passing test when comparing std::string to const char* literals") {
            expect(std::string("Aello")).to.be.lessThanOrEqualTo("Zello");
        }

        it("demonstrates a failing test when comparing std::string to const char* literals") {
            expect(std::string("Zello")).to.be.lessThanOrEqualTo("Hello");
        }

        it("demonstrates a passing test when comparing an object with a less than or equal operator") {
            const TestLessThanOrEqual<true> tltoe;
            expect(tltoe).to.be.lessThanOrEqualTo(1);
        }

        it("demonstrates a failing test when comparing an object with a less than or equal operator") {
            const TestLessThanOrEqual<false> tltoe;
            expect(tltoe).to.be.lessThanOrEqualTo(1);
        }

        it("demonstrates a failing test due to no comparison operator") {
            const TestLessThanOrEqual<true> tltoe;
            //No comparison operator
            expect(tltoe).to.be.lessThanOrEqualTo(NonLessThanOrEqual());
        }
    }
}

//stream operator for the TestCompare Class
template<bool value> std::ostream& operator << (std::ostream& stream, const TestLessThanOrEqual<value>& compare) {
    return stream << "TestLessThanOrEqual<" << (value ? "true" : "false") << ">";
}

//stream operator for the NonComparable Class
std::ostream& operator << (std::ostream& stream, const NonLessThanOrEqual& nonComparable) {
    return stream << "NonLessThanOrEqual";
}