#include "../../include/args-parser/option-list.h"

#include <algorithm>
#include <print>

namespace crc {
    void OptionList::_runVersion() {
        std::println("CR Compiler version: {}", CRC_VERSION);
    }

    void OptionList::_runCompile(const Option &option) {
        //
    }

    void OptionList::_runBuild(const Option &option) {}

    void OptionList::_runOption(const Option &option) {
        char short_name = option.getShortName();
        if (short_name == 'v') {
            _runVersion();
        } else if (short_name == 'c') {
            _runCompile(option);
        } else if (short_name == 'b') {
            _runBuild(option);
        } else {
            throw std::runtime_error("Undefine option");
        }
    }

    OptionList::OptionList() {
        _options = { Option("version", 'v'), Option("compile", 'c'), Option("build", 'b') };

        std::sort(_options.begin(), _options.end(), [](const Option &a, const Option &b) { return a.getShortName() < b.getShortName(); });
    }

    auto OptionList::getOptions() {
        return _options;
    }

    void OptionList::callOption(const std::string &option_name, int argc, const char** argv, int &index) {
        auto option = std::lower_bound(_options.begin(), _options.end(), option_name,
                                       [](const Option &op, const std::string &name) { return op.getName() < name; });
        _callOption(option, argc, argv, index);
    }

    void OptionList::callOption(char option_short_name, int argc, const char** argv, int &index) {
        auto option = std::lower_bound(_options.begin(), _options.end(), option_short_name,
                                       [](const Option &op, char short_name) { return op.getShortName() < short_name; });
        _callOption(option, argc, argv, index);
    }

    void OptionList::runOptions() {
        for (const Option &option : _options) {
            if (option.isCall()) {
                _runOption(option);
            }
        }
    }
}  // namespace crc
