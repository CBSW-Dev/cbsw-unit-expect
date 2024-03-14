#include "pch.hpp"
#include "expect/expect-logic.hpp"

namespace CBSW::Unit::Expect {
    bool Logic::logic(bool value) noexcept {
        return value;
    }

    std::string Logic::string = "";

    std::string Logic::inverseString = " not";

    bool InvertingLogic::logic(bool value) noexcept {
        return !value;
    }

    std::string InvertingLogic::string = " not";

    std::string InvertingLogic::inverseString = "";
}
