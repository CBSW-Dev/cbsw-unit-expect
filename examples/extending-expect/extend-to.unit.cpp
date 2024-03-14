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
    //By inheriting from ToBase, we can still use the existing "be" methods
    template <class TActual, class TLogic> class To<TActual, TLogic, std::enable_if_t<std::is_base_of_v<Vegetable, TActual>>>: public ToBase<TActual, TLogic> {
    public:
        using ToBase<TActual, TLogic>::ToBase;
        void beAPotato() {
            if (TLogic::logic(this->_info.actual.name() != "potato")) {
                throw Exception(this->_info.testCase, this->_info.actual.name() + " is" + TLogic::inverseString + " a potato", this->_info.filename, this->_info.line);
            }
        }
    };
}


suite() {
    describe("Expect To") {
        it("demonstrates a passing custom vegetable test") {
            Potato potato;
            expect(potato).to.beAPotato();
            //N.B. we can still use the to.equal method as we inherited from RootBase
            expect(potato).to.equal(potato);
        }

        it("demonstrates a failing custom vegetable test") {
            Radish radish;
            expect(radish).to.beAPotato();
        }

        it("demonstrates a passing custom vegetable test (inverse logic)") {
            Radish radish;
            expect(radish).notTo.beAPotato();
        }

        it("demonstrates a failing custom vegetable test") {
            Potato potato;
            expect(potato).notTo.beAPotato();
        }
    }
}