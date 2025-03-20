#include "../include/args-parser/option.h"

void args::IOption::setName(const std::string& name) {
    _name = name;
}

std::string args::IOption::getName() const {
    return _name;
}
