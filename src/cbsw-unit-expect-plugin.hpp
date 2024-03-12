#pragma once
#include <cbsw-unit>

namespace CBSW::Unit::Expect {
    class Plugin: public ::CBSW::Unit::Plugin {
    public:
        int initialise(Arguments& arguments, PluginNextHandler& next) override;
    };
}
