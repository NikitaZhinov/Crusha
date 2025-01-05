#pragma once

#include "option-list.h"
#include "../error/error.h"

#include <string>
#include <vector>

namespace crc {
    class ArgsParser {
    private:
        OptionList _options;

        static std::string _get_option(const char* arg);
        void _get_options(int argc, const char** argv);

    public:
        ArgsParser(int argc, const char** argv);

        auto getOptions() const;

        void runOptions();
    };
}  // namespace crc
