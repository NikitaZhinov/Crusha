#include "../../include/args-parser/args-parser.h"

#include <algorithm>
#include <stdexcept>
#include <print>

namespace crc {
    constexpr bool operator<(const ArgsParser::Option &op, const std::string &name) {
        return op.name < name;
    }

    constexpr bool operator<(const std::string &name, const ArgsParser::Option &op) {
        return name < op.name;
    }

    constexpr bool operator<(const ArgsParser::Option &op, char short_name) {
        return op.short_name < short_name;
    }

    constexpr bool operator<(char short_name, const ArgsParser::Option &op) {
        return short_name < op.short_name;
    }

    constexpr void ArgsParser::_init_options() {
        _options = {
            { "version", 'v', true, false },
            { "compile", 'c', true, false },
            {   "build", 'b', true, false }
        };

        std::sort(_options.begin(), _options.end(),
                  [](const ArgsParser::Option &op_1, const ArgsParser::Option &op_2) { return op_1.short_name < op_2.short_name; });
    }

    std::string ArgsParser::_get_option(const char* arg) {
        std::string option = arg;
        option.erase(option.begin());
        option.erase(option.begin());
        return option;
    }

    void ArgsParser::_get_options(int argc, const char** argv) {
        for (int i = 1; i < argc; ++i) {
            if (argv[i][0] == '-') {  // this option
                auto pos = _options.end();
                if (argv[i][1] == '-') {  // this name option
                    pos = std::lower_bound(_options.begin(), _options.end(), _get_option(argv[i]));
                } else {  // this short name option
                    pos = std::lower_bound(_options.begin(), _options.end(), argv[i][1]);
                }
                if (pos != _options.end()) {
                    pos->is_call = true;
                } else {
                    std::println("Undefined option: {}", argv[i]);
                    _error = UndefineOption;
                }
            }
        }
    }

    void ArgsParser::_check_options() {
        if (_error != None) {
            return;
        }

        std::size_t number_of_called_alone_options = 0;
        std::vector<const Option*> called_alone_options;
        for (const Option &option : _options) {
            if (option.is_alone && option.is_call) {
                ++number_of_called_alone_options;
                called_alone_options.push_back(&option);
            }
        }
        if (number_of_called_alone_options > 1) {
            std::print("The ");
            for (const Option* option : called_alone_options) {
                std::print("{} ({}), ", option->name, option->short_name);
            }
            std::print("\b\b options conflict");
            _error = OptionConflict;
        }
    }

    ArgsParser::ArgsParser(int argc, const char** argv) {
        _init_options();
        _get_options(argc, argv);
        _check_options();
    }

    void ArgsParser::callOptions() {
        if (_error != None) {
            return;
        }

        for (const Option &option : _options) {
            if (option.is_call) {
                // какая-то хуйня
            }
        }
    }
}  // namespace crc
