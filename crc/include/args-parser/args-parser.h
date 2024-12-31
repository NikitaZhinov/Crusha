#pragma once

#include <string>
#include <set>

namespace crc {
    class ArgsParser {
    public:
        struct Option {
            std::string name;
            char short_name;
            bool is_call;

            inline void setCall(bool is_call) {
                this->is_call = is_call;
            }
        };

        friend bool operator<(const Option &op_1, const Option &op_2);
        friend bool operator<(const Option &op, const std::string &name);
        friend bool operator<(const std::string &name, const Option &op);
        friend bool operator<(const Option &op, char short_name);
        friend bool operator<(char short_name, const Option &op);

    private:
        std::set<Option, std::less<>> options;

        void _init_options();
        std::string _get_option(const char* arg);
        void _get_options(int argc, const char** argv);

    public:
        ArgsParser(int argc, const char** argv);

        inline auto getOptions() {
            return options;
        }
    };
}  // namespace crc
