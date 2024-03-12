#include "expect/expect.hpp"

namespace CBSW::Unit::Expect {
    Builder::Builder(::CBSW::Unit::ICase& testCase, Filename filename, LineNumber line) noexcept:
        _testCase(testCase),
        _filename(filename),
        _line(line)
    {}
}