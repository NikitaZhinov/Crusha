#include "../include/args-parser/args-parser.h"

args::ArgsParser::ArgsParser(int argc, const char** argv) :
    _argc(argc),
    _argv(argv),
    _default_option_exist(false) {}

std::list<args::IOption*> args::ArgsParser::getOptions() const {
    return _option_list;
}

void args::ArgsParser::addOption(IOption* option) {
    _option_list.push_back(option);
}

int args::ArgsParser::callOptions() {
    if (_option_list.front()->getName().empty()) {
        _default_option_exist = true;
    }

    for (int i = 1; i < _argc; ++i) {
        bool is_option = false;
        for (IOption* option : _option_list) {
            if (option->getName() == _argv[i]) {
                int res = option->call(&_argv[i]);
                is_option = true;
                if (!res) {
                    return res;
                }
                break;
            }
        }
        if (!is_option && _default_option_exist) {
            _option_list.front()->call(&_argv[i]);
        }
    }

    return 0;
}
