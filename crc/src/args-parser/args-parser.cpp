#include "../../include/args-parser/args-parser.h"

#include <algorithm>
#include <stdexcept>
#include <print>

namespace crc {
    std::string ArgsParser::_get_option(const char* arg) {
        std::string option = arg;
        option.erase(option.begin());
        option.erase(option.begin());
        return option;
    }

    void ArgsParser::_get_options(int argc, const char** argv) {
        for (int i = 1; i < argc; ++i) {
            if (argv[i][0] == '-') {  // this option
                try {
                    if (argv[i][1] == '-') {  // this name option
                        _options.callOption(_get_option(argv[i]), argc, argv, i + 1);
                    } else {  // this short name option
                        _options.callOption(_get_option(argv[i]), argc, argv, i + 1);
                    }
                } catch (const std::runtime_error &err) {
                    std::println("Undefined option: {}", argv[i]);
                    _error = UndefineOption;
                    break;
                }
            } else {
                std::println("The expected option");
                _error = UndefineOption;
                break;
            }
        }
    }

    ArgsParser::ArgsParser(int argc, const char** argv) {
        _get_options(argc, argv);
    }

    auto ArgsParser::getOptions() const {
        return _options;
    }

    ArgsParser::Error ArgsParser::getError() const {
        return _error;
    }

    void ArgsParser::runOptions() {
        if (_error != None) {
            return;
        }

        _options.runOptions();
    }
}  // namespace crc
