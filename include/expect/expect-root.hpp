#pragma once
#include <cbsw-unit>

#include "expect-info.hpp"
#include "expect-to.hpp"
#include "expect-logic.hpp"

namespace CBSW::Unit::Expect {
    template <class TActual> class RootBase {
    public:
        using Filename = const char*;
        using LineNumber = std::uint32_t;

        RootBase(const TActual& actual, ::CBSW::Unit::ICase& testCase, Filename filename, LineNumber line) noexcept:
            _info(actual, testCase, filename, line),
            to(_info),
            notTo(_info)
        {}

        To<TActual, Logic> to;
        To<TActual, InvertingLogic> notTo;
    protected:
        Info<TActual> _info;

    };

    template <class TActual, class = void> class Root: public RootBase<TActual> {
    public:
        using RootBase<TActual>::RootBase;
    };
}
