#include "pch.hpp"
#include "cbsw-unit-expect-plugin.hpp"
#include "settings/version.hpp"
#include "cbsw-unit-expect.hpp"
#include <iostream>

namespace CBSW::Unit::Expect {
    namespace {
        Plugin plugin;
        void printVersion() {
            std::cout << "\r\ncbsw-unit-expect v" << Version::major() << "." << Version::minor() << "." << Version::revision() << "\r\n" << std::endl;
        }
    }

    int Plugin::initialise(Arguments& arguments, PluginNextHandler& next) {
        for (char* argument: arguments) {
            if (std::string(argument) == "--cbsw-unit-expect-version") {
                printVersion();
                return EXIT_SUCCESS;
            }
        }
        return next.next(arguments);
    }


    void initialise(::CBSW::Unit::Runner& runner) {
        //the plugin is being used, and, because it is declared locally, the constructor will be called as part of the
        //static initialisation routine
        runner.installPlugin(plugin);
    }
}

