#pragma once

#include <cbsw-unit>

namespace CBSW::Unit::Expect {
    void initialise(::CBSW::Unit::Runner& runner);
}

#include "expect/expect.hpp"

#include "expect/expect-macro.hpp"