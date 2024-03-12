#include "test.hpp"

int cbsw_unit_main(::CBSW::Unit::Arguments& arguments, ::CBSW::Unit::Runner& runner) {
    CBSW::Unit::Expect::initialise(runner);
    return runner.run();
}