#pragma once

#include "option.h"

#include <stdexcept>

namespace crc {
    class OptionList {
        std::vector<Option> _options;

        template <class ForwardIt> void _callVersion(ForwardIt option);
        template <class ForwardIt> void _callCompile(ForwardIt option, int argc, const char** argv, int &index);
        template <class ForwardIt> void _callBuild(ForwardIt option, int argc, const char** argv, int &index);
        template <class ForwardIt> void _callOption(ForwardIt option, int argc, const char** argv, int &index);

        void _runVersion();
        void _runCompile(const Option &option);
        void _runBuild(const Option &option);
        void _runOption(const Option &option);

    public:
        OptionList();

        auto getOptions();

        void callOption(const std::string &option_name, int argc, const char** argv, int &index);
        void callOption(char option_short_name, int argc, const char** argv, int &index);

        void runOptions();
    };

    template <class ForwardIt> inline void OptionList::_callVersion(ForwardIt option) {
        option->setCall(true);
    }

    template <class ForwardIt> inline void OptionList::_callCompile(ForwardIt option, int argc, const char** argv, int &index) {
        option->setCall(true);
        std::vector<std::string> files;
        files.reserve(argc - index);
        while (index < argc && argv[index][0] != '-') {
            files.push_back(argv[index]);
            ++index;
        }
        --index;
        option->setFiles(std::move(files));
    }

    template <class ForwardIt> inline void OptionList::_callBuild(ForwardIt option, int argc, const char** argv, int &index) {
        _callCompile(option, argc, argv, index);
    }

    template <class ForwardIt> inline void OptionList::_callOption(ForwardIt option, int argc, const char** argv, int &index) {
        if (option == _options.end()) {
            throw std::runtime_error("Undefined option");
        }

        char short_name = option->getShortName();
        if (short_name == 'v') {
            _callVersion(option);
        } else if (short_name == 'c') {
            _callCompile(option, argc, argv, index);
        } else if (short_name == 'b') {
            _callBuild(option, argc, argv, index);
        }
    }
}  // namespace crc
