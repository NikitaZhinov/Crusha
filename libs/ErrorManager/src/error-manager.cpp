#include "../include/error-manager/error-manager.h"

error::ErrorManager::ErrorManager() :
    _last_error_id(0),
    _errors({ std::pair<std::uint64_t, std::string>(0, std::string()) }) {}

error::ErrorManager::ErrorManager(const std::string& defaul_message) :
    _last_error_id(0),
    _errors({ std::pair<std::uint64_t, std::string>(0, defaul_message) }) {}

error::ErrorManager::ErrorManager(const ErrorManager& other) :
    _last_error_id(0),
    _errors(other._errors) {}

error::ErrorManager::ErrorManager(ErrorManager&& other) noexcept :
    _last_error_id(0),
    _errors(std::move(other._errors)) {}

error::ErrorManager& error::ErrorManager::operator=(const ErrorManager& right) {
    _errors = right._errors;
    return *this;
}

error::ErrorManager& error::ErrorManager::operator=(ErrorManager&& right) noexcept {
    _errors = std::move(right._errors);
    return *this;
}

void error::ErrorManager::callError(std::uint64_t id, const std::string& message) {
    _last_error_id = id;
    throw std::runtime_error(std::format("{} {}", _errors.find(id)->second, message));
}

void error::ErrorManager::addError(const std::string& message_error) {
    _errors.insert(std::pair<std::uint64_t, std::string>(_errors.size(), message_error));
}

void error::ErrorManager::addError(std::size_t id, const std::string& message_error) {
    _errors.insert(std::pair<std::uint64_t, std::string>(id, message_error));
}
