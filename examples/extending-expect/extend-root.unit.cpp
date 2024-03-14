#include "test.hpp"

namespace {
    class Vegetable {
    public:
        virtual ~Vegetable() = default;

        virtual std::string name() const = 0;
    };

    class Potato: public Vegetable {
    public:
        std::string name() const override { return "potato"; }

        bool operator == (const Vegetable& vegetable) const {
            return this == &vegetable;
        }
    };

    class Radish: public Vegetable {
    public:
        std::string name() const override { return "radish"; }
    };
}

namespace CBSW::Unit::Expect {
    //By inheriting from RootBase, we can still use the existing "to" and "notTo" methods
    template <class TActual> class Root<TActual, std::enable_if_t<std::is_base_of_v<Vegetable, TActual>>>: public RootBase<TActual> {
    public:
        using RootBase<TActual>::RootBase;
        void toBeAPotato() {
            if (this->_info.actual.name() != "potato") {
                throw Exception(this->_info.testCase, this->_info.actual.name() + " is not a potato", this->_info.filename, this->_info.line);
            }
        }
    };
}


suite() {
    describe("Expect Root") {
        it("demonstrates a passing custom vegetable test") {
            Potato potato;
            expect(potato).toBeAPotato();
            //N.B. we can still use the to.equal method as we inherited from RootBase
            expect(potato).to.equal(potato);
        }

        it("demonstrates a failing custom vegetable test") {
            Radish radish;
            expect(radish).toBeAPotato();
        }
    }
}