#pragma once
#include <cbsw-unit>


namespace CBSW::Unit::Expect::Internal {
    template <class TActual> class Info {
    public:
        using Filename = const char*;
        using LineNumber = std::uint32_t;

        Info(const TActual& actual, ::CBSW::Unit::ICase& testCase, Filename filename, LineNumber line):
            actual(actual),
            testCase(testCase),
            filename(filename),
            line(line)
        {}

        Info(const Info& other):
            actual(other.actual),
            testCase(other.testCase),
            line(other.line)
        {}

        Info& operator=(const Info& other) = delete;
        Info& operator=(Info&& other) = delete;
    public:
        const TActual& actual;
        ::CBSW::Unit::ICase& testCase;
        Filename filename;
        LineNumber line;
    };
}
