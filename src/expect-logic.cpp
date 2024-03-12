#include "pch.hpp"
#include "expect/expect-logic.hpp"

namespace CBSW::Unit::Expect::Internal {
    bool Logic::logic(bool value) noexcept {
        return value;
    }

    std::string Logic::string = "";

    bool InvertingLogic::logic(bool value) noexcept {
        return !value;
    }

    std::string InvertingLogic::string = " not";
}
