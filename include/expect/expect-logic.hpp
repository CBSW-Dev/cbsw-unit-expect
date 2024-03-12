#pragma once

#include <string>

namespace CBSW::Unit::Expect::Internal {
    class Logic {
    public:
        static bool logic(bool value) noexcept;

        static std::string string;
    };

    class InvertingLogic {
    public:
        static bool logic(bool value) noexcept;
        static std::string string;
    };
}
