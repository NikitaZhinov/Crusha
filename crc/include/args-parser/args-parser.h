#pragma once

#include "option-list.h"

#include <string>
#include <vector>

namespace crc {
    class ArgsParser {
    public:
        enum Error {
            None = 0,  // There are no errors
            UndefineOption,
            OptionConflict,
        };

    private:
        OptionList _options;
        Error _error;

        static std::string _get_option(const char* arg);
        void _get_options(int argc, const char** argv);

    public:
        ArgsParser(int argc, const char** argv);

        auto getOptions() const;
        Error getError() const;

        void runOptions();
    };
}  // namespace crc
