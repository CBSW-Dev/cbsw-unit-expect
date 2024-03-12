#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"
#include "expect-to.hpp"
#include "expect-logic.hpp"

namespace CBSW::Unit::Expect::Internal {
    template <class TActual> class Root {
    public:
        using Filename = const char*;
        using LineNumber = std::uint32_t;

        Root(const TActual& actual, ::CBSW::Unit::ICase& testCase, Filename filename, LineNumber line) noexcept:
            _info(actual, testCase, filename, line),
            to(_info),
            notTo(_info)
        {}

        To<TActual, Logic> to;
        To<TActual, InvertingLogic> notTo;
    private:
        Info<TActual> _info;

    };
}
