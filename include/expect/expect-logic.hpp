#pragma once

#include <string>

namespace CBSW::Unit::Expect {
    class Logic {
    public:
        static bool logic(bool value) noexcept;

        static std::string string;
        static std::string inverseString;
    };

    class InvertingLogic {
    public:
        static bool logic(bool value) noexcept;
        static std::string string;
        static std::string inverseString;
    };
}
