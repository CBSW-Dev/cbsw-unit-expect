#include "test.hpp"

namespace {
    template <bool value> class TestCompare {
    public:
        bool operator == (int x) const noexcept {
            (void)x;
            return value;
        }
    };

    class NonComparable {};
}

suite() {
    describe("Compare") {
        it("demonstrates a passing test when comparing numeric literals") {
            expect(1).to.equal(1);
        }

        it("demonstrates a failing test when comparing numeric literals") {
            expect(1).to.equal(0);
        }

        it("demonstrates a passing test when comparing numeric variables") {
            int x = 1;
            int y = 1;
            expect(x).to.equal(y);
        }

        it("demonstrates a failing test when comparing numeric literals") {
            int x = 1;
            int y = 0;
            expect(x).to.equal(y);
        }

        it("demonstrates a passing test when comparing boolean literals") {
            expect(true).to.equal(true);
        }

        it("demonstrates a failing test when comparing boolean literals") {
            expect(true).to.equal(false);
        }

        it("demonstrates a passing test when comparing boolean variables") {
            bool x = false;
            bool y = false;
            expect(x).to.equal(y);
        }

        it("demonstrates a failing test when comparing boolean variables") {
            bool x = true;
            bool y = false;
            expect(x).to.equal(y);
        }

        it("demonstrates a passing test when comparing const char* literals") {
            //N.B. it is recommended to convert const char* objects to strings if you want to compare strings,
            //This will compare pointers
            expect("Hello").to.equal("Hello");
        }

        it("demonstrates a failing test when comparing const char* literals") {
            expect("Hello").to.equal("world");
        }

        it("demonstrates a passing test when comparing const char* variables") {
            //both these pointers "should" point to the same location (.bss)
            const char* x = "hello";
            const char* y = "hello";
            expect(x).to.equal(y);
        }

        it("demonstrates a failing test when comparing const char* variables") {
            const char* x = "hello";
            const char* y = "world";
            expect(x).to.equal(y);
        }

        it("demonstrates a passing test when comparing std::string to const char* literals") {
            expect(std::string("Hello")).to.equal("Hello");
        }

        it("demonstrates a failing test when comparing std::string to const char* literals") {
            expect(std::string("Hello")).to.equal("world");
        }

        it("demonstrates a passing test when comparing std::string variables") {
            std::string x = "hello";
            std::string y = "hello";
            expect(x).to.equal(y);
        }

        it("demonstrates a failing test when comparing std::string variables") {
            std::string x = "hello";
            std::string y = "world";
            expect(x).to.equal(y);
        }

        it("demonstrates a passing test when comparing an object with a comparison operator") {
            const TestCompare<true> tc;
            expect(tc).to.equal(1);
        }

        it("demonstrates a failing test when comparing an object with a comparison operator") {
            const TestCompare<false> tc;
            expect(tc).to.equal(1);
        }

        it("demonstrates a failing test due to no comparison operator") {
            const TestCompare<true> tc;
            //No float comparison operator
            expect(tc).to.equal(NonComparable());
        }

        it("demonstrates a passing test when comparing numeric literals (inverting logic)") {
            expect(1).notTo.equal(0);
        }

        it("demonstrates a failing test when comparing numeric literals (inverting logic)") {
            expect(1).notTo.equal(1);
        }

        it("demonstrates a passing test when comparing numeric variables (inverting logic)") {
            int x = 1;
            int y = 0;
            expect(x).notTo.equal(y);
        }

        it("demonstrates a failing test when comparing numeric literals (inverting logic)") {
            int x = 1;
            int y = 1;
            expect(x).notTo.equal(y);
        }

        it("demonstrates a passing test when comparing boolean literals (inverting logic)") {
            expect(true).notTo.equal(false);
        }

        it("demonstrates a failing test when comparing boolean literals (inverting logic)") {
            expect(true).notTo.equal(true);
        }

        it("demonstrates a passing test when comparing boolean variables (inverting logic)") {
            bool x = true;
            bool y = false;
            expect(x).notTo.equal(y);
        }

        it("demonstrates a failing test when comparing boolean variables (inverting logic)") {
            bool x = true;
            bool y = true;
            expect(x).notTo.equal(y);
        }

        it("demonstrates a passing test when comparing const char* literals (inverting logic)") {
            //N.B. it is recommended to convert const char* objects to strings if you want to compare strings,
            //This will compare pointers
            expect("Hello").notTo.equal("world");
        }

        it("demonstrates a failing test when comparing const char* literals (inverting logic)") {
            expect("Hello").notTo.equal("Hello");
        }

        it("demonstrates a passing test when comparing const char* variables (inverting logic)") {
            const char* x = "hello";
            const char* y = "world";
            expect(x).notTo.equal(y);
        }

        it("demonstrates a failing test when comparing const char* variables (inverting logic)") {
            //both these pointers "should" point to the same location (.bss)
            const char* x = "hello";
            const char* y = "hello";
            expect(x).notTo.equal(y);

        }

        it("demonstrates a passing test when comparing std::string to const char* literals (inverting logic)") {
            expect(std::string("Hello")).notTo.equal("world");
        }

        it("demonstrates a failing test when comparing const char* literals (inverting logic)") {
            expect(std::string("Hello")).notTo.equal("Hello");
        }

        it("demonstrates a passing test when comparing std::string variables (inverting logic)") {
            std::string x = "hello";
            std::string y = "world";
            expect(x).notTo.equal(y);
        }

        it("demonstrates a failing test when comparing std::string variables (inverting logic)") {
            std::string x = "hello";
            std::string y = "hello";
            expect(x).notTo.equal(y);
        }

        it("demonstrates a passing test when comparing an object with a comparison operator (inverting logic)") {
            const TestCompare<false> tc;
            expect(tc).notTo.equal(1);
        }

        it("demonstrates a failing test when comparing an object with a comparison operator (inverting logic)") {
            const TestCompare<true> tc;
            expect(tc).notTo.equal(1);
        }

        it("demonstrates a failing test due to no comparison operator (inverting logic)") {
            const TestCompare<true> tc;
            //No comparison operator
            expect(tc).notTo.equal(NonComparable());
        }
    }
}

//stream operator for the TestCompare Class
template<bool value> std::ostream& operator << (std::ostream& stream, const TestCompare<value>& compare) {
    return stream << "TestCompare<" << (value ? "true" : "false") << ">";
}

//stream operator for the NonComparable Class
std::ostream& operator << (std::ostream& stream, const NonComparable& nonComparable) {
    return stream << "NonComparable";
}