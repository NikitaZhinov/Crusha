#include "../../include/args-parser/option.h"

namespace crc {
    Option::Option(const std::string &name, char short_name) : _name(name), _short_name(short_name), _is_call(false) {}

    void Option::setCall(bool is_call) {
        _is_call = is_call;
    }

    void Option::setFiles(const std::vector<std::string> &files) {
        _files = files;
    }

    void Option::setFiles(std::vector<std::string> &&files) {
        _files = std::move(files);
    }

    std::string Option::getName() const noexcept {
        return _name;
    }

    char Option::getShortName() const noexcept {
        return _short_name;
    }

    bool Option::isCall() const noexcept {
        return _is_call;
    }

    auto Option::getFiles() const noexcept {
        return _files;
    }
}  // namespace crc
