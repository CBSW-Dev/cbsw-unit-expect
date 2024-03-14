#include "test.hpp"

#include <string>

namespace {
    class Base {
    public:
        virtual ~Base() = default;
        virtual std::string id() const = 0;

        virtual bool equals(const Base& base) const = 0;
    };

    class Derived: public Base {
    public:
        Derived(const std::string& id):
            _id(id)
        {}

        std::string id() const override {
            return _id;
        }

        bool equals(const Base& base) const override {
            return _id == base.id();
        }
    private:
        std::string _id;
    };
}

namespace CBSW::Unit::Expect {
    //This pattern can be applied to ToBeGreaterThan, ToBeGreaterThanOrEqual, ToBeLessThan, ToBeLessThanOrEqual
    template <class TActual, class TExpected, class TLogic> class ToEqual<TActual, TExpected, TLogic, std::enable_if_t<
        std::is_base_of_v<Base, TActual> && std::is_base_of_v<Base, TExpected>
    >> {
    public:
        static std::string makeMessage(const TActual& actual, const TExpected& expected) {
            std::stringstream ss;
            ss << "Expected Base(" << actual.id() << ") to" << TLogic::string << " equal Base(" << expected.id() << ")";
            return ss.str();
        }

        static void run(const Info<TActual>& info, const TExpected& expected) {
            if (TLogic::logic(!(info.actual.equals(expected)))) {
                throw Exception(info.testCase, makeMessage(info.actual, expected), info.filename, info.line);
            }
        }
    };
}


suite() {
    describe("Expect To Equal") {
        it("demonstrates a passing custom test") {
            Derived d1("bashgrudh");
            Derived d2("bashgrudh");
            expect(d1).to.equal(d2);
        }

        it("demonstrates a failing custom test") {
            Derived d1("bashgrudh");
            Derived d2("fhrejy7dgnbjks");
            expect(d1).to.equal(d2);
        }

        it("demonstrates a passing custom test (inverse logic)") {
            Derived d1("bashgrudh");
            Derived d2("fhrejy7dgnbjks");
            expect(d1).notTo.equal(d2);
        }

        it("demonstrates a failing custom test (inverse logic)") {
            Derived d1("bashgrudh");
            Derived d2("bashgrudh");
            expect(d1).notTo.equal(d2);
        }
    }
}