#include "test.hpp"

#include <vector>
#include <algorithm>

namespace {
    class Base {
    public:
        virtual ~Base() = default;
        virtual bool includes(int x) const noexcept = 0;
    };

    class Derived: public Base {
    public:
        Derived(std::initializer_list<int> values):
            _values(values)
        {}

        bool includes(int x) const noexcept override {
            return std::find(_values.begin(), _values.end(), x) != _values.end();
        }
    private:
        std::vector<int> _values;
    };
}

namespace CBSW::Unit::Expect {
    template <class TActual, class TExpected, class TLogic> class ToInclude<TActual, TExpected, TLogic, std::enable_if_t<
        std::is_base_of_v<Base, TActual> && std::is_same_v<int, TExpected>
    >> {
    public:
        static std::string makeMessage(const TActual& actual, const TExpected& expected) {
            std::stringstream ss;
            ss << "Expected Base" << TLogic::string << " to include " << expected;
            return ss.str();
        }

        static void run(const Info<TActual>& info, const TExpected& expected) {
            if (TLogic::logic(!(info.actual.includes(expected)))) {
                throw Exception(info.testCase, makeMessage(info.actual, expected), info.filename, info.line);
            }
        }
    };
}


suite() {
    describe("Expect To Include") {
        it("demonstrates a passing custom test") {
            Derived d1 {1,2,3,4,5,6};
            expect(d1).to.include(4);
        }

        it("demonstrates a failing custom test") {
            Derived d1 {1,2,3,5,6};
            expect(d1).to.include(4);
        }

        it("demonstrates a passing custom test (inverse logic)") {
            Derived d1 {1,2,3,5,6};
            expect(d1).notTo.include(4);
        }

        it("demonstrates a failing custom test (inverse logic)") {
            Derived d1 {1,2,3,4,5,6};
            expect(d1).notTo.include(4);
        }
    }
}