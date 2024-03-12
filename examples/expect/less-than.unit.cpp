#include "test.hpp"

namespace {
    template <bool value> class TestLessThan {
    public:
        bool operator < (int x) const noexcept {
            (void)x;
            return value;
        }
    };

    class NonLessThan {};
}

suite() {
    describe("Less than") {
        it("demonstrates a passing test when comparing numeric literals") {
            expect(1).to.be.lessThan(2);
        }

        it("demonstrates a failing test when comparing numeric literals") {
            expect(1).to.be.lessThan(1);
        }

        it("demonstrates a passing test when comparing numeric variables") {
            int x = 1;
            int y = 2;
            expect(x).to.be.lessThan(y);
        }

        it("demonstrates a failing test when comparing numeric literals") {
            int x = 1;
            int y = 1;
            expect(x).to.be.lessThan(y);
        }

        it("demonstrates a passing test when comparing std::string to const char* literals") {
            expect(std::string("Aello")).to.be.lessThan("Zello");
        }

        it("demonstrates a failing test when comparing std::string to const char* literals") {
            expect(std::string("Hello")).to.be.lessThan("Hello");
        }

        it("demonstrates a passing test when comparing an object with a less than or equal operator") {
            const TestLessThan<true> tlt;
            expect(tlt).to.be.lessThan(1);
        }

        it("demonstrates a failing test when comparing an object with a less than operator") {
            const TestLessThan<false> tlt;
            expect(tlt).to.be.lessThan(1);
        }

        it("demonstrates a failing test due to no comparison operator") {
            const TestLessThan<true> tlt;
            //No comparison operator
            expect(tlt).to.be.lessThan(NonLessThan());
        }
    }
}

//stream operator for the TestCompare Class
template<bool value> std::ostream& operator << (std::ostream& stream, const TestLessThan<value>& compare) {
    return stream << "TestLessThan<" << (value ? "true" : "false") << ">";
}

//stream operator for the NonComparable Class
std::ostream& operator << (std::ostream& stream, const NonLessThan& nonComparable) {
    return stream << "NonLessThan";
}