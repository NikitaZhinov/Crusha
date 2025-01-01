#pragma once

#include <string>
#include <vector>

namespace crc {
    class Option {
        std::string _name;
        char _short_name;
        bool _is_call;

        std::vector<std::string> _files;  // for --compile and --build

    public:
        Option() = default;
        Option(const std::string &name, char short_name);

        void setCall(bool is_call);
        void setFiles(const std::vector<std::string> &files);
        void setFiles(std::vector<std::string> &&files);

        std::string getName() const noexcept;
        char getShortName() const noexcept;
        bool isCall() const noexcept;
        auto getFiles() const noexcept;
    };
}  // namespace crc
