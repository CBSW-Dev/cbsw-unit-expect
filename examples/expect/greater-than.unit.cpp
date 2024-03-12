#include "test.hpp"

namespace {
    template <bool value> class TestGreaterThan {
    public:
        bool operator > (int x) const noexcept {
            (void)x;
            return value;
        }
    };

    class NonGreaterThan {};
}

suite() {
    describe("Greater than") {
        it("demonstrates a passing test when comparing numeric literals") {
            expect(2).to.be.greaterThan(1);
        }

        it("demonstrates a failing test when comparing numeric literals") {
            expect(1).to.be.greaterThan(1);
        }

        it("demonstrates a passing test when comparing numeric variables") {
            int x = 2;
            int y = 1;
            expect(x).to.be.greaterThan(y);
        }

        it("demonstrates a failing test when comparing numeric literals") {
            int x = 1;
            int y = 1;
            expect(x).to.be.greaterThan(y);
        }

        it("demonstrates a passing test when comparing boolean literals") {
            //allowed, but semantically wrong
            expect(true).to.be.greaterThan(false);
        }

        it("demonstrates a failing test when comparing boolean literals") {
            //allowed, but semantically wrong
            expect(true).to.be.greaterThan(true);
        }

        it("demonstrates a passing test when comparing std::string to const char* literals") {
            expect(std::string("Zello")).to.be.greaterThan("Hello");
        }

        it("demonstrates a failing test when comparing std::string to const char* literals") {
            expect(std::string("Aello")).to.be.greaterThan("Zello");
        }

        it("demonstrates a passing test when comparing an object with a greater than operator") {
            const TestGreaterThan<true> tgt;
            expect(tgt).to.be.greaterThan(1);
        }

        it("demonstrates a failing test when comparing an object with a greater than operator") {
            const TestGreaterThan<false> tgt;
            expect(tgt).to.be.greaterThan(1);
        }

        it("demonstrates a failing test due to no comparison operator") {
            const TestGreaterThan<true> tgt;
            //No comparison operator
            expect(tgt).to.be.greaterThan(NonGreaterThan());
        }
    }
}

//stream operator for the TestCompare Class
template<bool value> std::ostream& operator << (std::ostream& stream, const TestGreaterThan<value>& compare) {
    return stream << "TestGreaterThan<" << (value ? "true" : "false") << ">";
}

//stream operator for the NonComparable Class
std::ostream& operator << (std::ostream& stream, const NonGreaterThan& nonComparable) {
    return stream << "NonGreaterThan";
}