#pragma once
#include <cbsw-unit>

#include "expect-root.hpp"

namespace CBSW::Unit::Expect {
    class Builder {
    public:
        using Filename = const char*;
        using LineNumber = std::uint32_t;
        Builder(::CBSW::Unit::ICase& testCase, Filename filename, LineNumber line) noexcept;

        template <class TActual> Root<TActual> operator()(const TActual& actual) noexcept {
            return Root<TActual>(actual, _testCase, _filename, _line);
        }
    private:
        ::CBSW::Unit::ICase& _testCase;
        Filename _filename;
        LineNumber _line;
    };
}