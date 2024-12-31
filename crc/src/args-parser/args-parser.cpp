#include "args-parser/args-parser.h"

namespace crc {
    bool operator<(const ArgsParser::Option &op_1, const ArgsParser::Option &op_2) {
        return op_1.short_name < op_2.short_name;
    }

    bool operator<(const ArgsParser::Option &op, const std::string &name) {
        return op.name < name;
    }

    bool operator<(const std::string &name, const ArgsParser::Option &op) {
        return name < op.name;
    }

    bool operator<(const ArgsParser::Option &op, char short_name) {
        return op.short_name < short_name;
    }

    bool operator<(char short_name, const ArgsParser::Option &op) {
        return short_name < op.short_name;
    }

    void ArgsParser::_init_options() {
        options.insert({ "compile", 'c' });
        options.insert({ "build", 'b' });
        options.insert({ "version", 'v' });
    }

    std::string ArgsParser::_get_option(const char* arg) {
        std::string option = arg;
        option.erase(option.begin());
        option.erase(option.begin());
        return option;
    }

    void ArgsParser::_get_options(int argc, const char** argv) {
        for (std::size_t i = 1; i < argc; ++i) {
            if (argv[i][0] == '-') {  // this option
                if (argv[i][1] == '-') {  // this name option
                    options.find(_get_option(argv[i]))->is_call = true;
                } else {  // this short name option
                }
            }
        }
    }

    ArgsParser::ArgsParser(int argc, const char** argv) {
        _init_options();
        _get_options(argc, argv);
    }
}  // namespace crc
