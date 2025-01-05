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
                        _options.callOption(_get_option(argv[i++]), argc, argv, i);
                    } else {  // this short name option
                        _options.callOption(argv[i++][1], argc, argv, i);
                    }
                } catch (const std::runtime_error &err) {
                    Error::setTextError(std::format("Undefined option: {}", argv[i]));
                    Error::setTypeError(Error::UndefineOption);
                    break;
                }
            } else {
                Error::setTextError("The expected option");
                Error::setTypeError(Error::UndefineOption);
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

    void ArgsParser::runOptions() {
        if (Error::getTypeError() != Error::None) {
            return;
        }

        try {
            _options.runOptions();
        } catch (const std::runtime_error &ex) {
            Error::setTextError(ex.what());
            Error::setTypeError(Error::UndefineOption);
        }
    }
}  // namespace crc
