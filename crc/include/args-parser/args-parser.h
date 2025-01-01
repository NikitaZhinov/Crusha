#pragma once

#include <string>
#include <vector>

namespace crc {
    class ArgsParser {
    public:
        struct Option {
            std::string name;
            char short_name;
            bool is_alone;
            bool is_call;

            constexpr inline void setCall(bool is_call) {
                this->is_call = is_call;
            }
        };

        enum Error {
            None = 0,  // There are no errors
            UndefineOption,
            OptionConflict,
        };

        constexpr friend bool operator<(const Option &op, const std::string &name);
        constexpr friend bool operator<(const std::string &name, const Option &op);
        constexpr friend bool operator<(const Option &op, char short_name);
        constexpr friend bool operator<(char short_name, const Option &op);

    private:
        std::vector<Option> _options;
        Error _error;

        constexpr void _init_options();
        std::string _get_option(const char* arg);
        void _get_options(int argc, const char** argv);
        void _check_options();

    public:
        ArgsParser(int argc, const char** argv);

        inline auto getOptions() {
            return _options;
        }

        inline Error getError() {
            return _error;
        }

        void callOptions();
    };
}  // namespace crc
