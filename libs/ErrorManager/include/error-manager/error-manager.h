#pragma once

#include <string>
#include <map>
#include <future>
#include <format>

namespace error {
    /**
     * @brief Detects a list of errors and stops the program if an error is caused.
     */
    class ErrorManager {
        std::map<std::uint64_t, std::string> _errors;

        std::uint64_t _last_error_id;

    public:
        /**
         * @brief Adds an error with id = 0.
         */
        ErrorManager();

        /**
         * @brief Adds an error with id = 0 and sets a message for it.
         *
         * @param defaul_message - error message with id = 0.
         */
        ErrorManager(const std::string& defaul_message);

        /**
         * @brief Copy constructor.
         * Copies error map.
         *
         * @param other - another error manager.
         */
        ErrorManager(const ErrorManager& other);

        /**
         * @brief Move constructor.
         * Moves error map.
         *
         * @param other - another error manager.
         */
        ErrorManager(ErrorManager&& other) noexcept;

        /**
         * @brief Copy operator.
         * Copies error map.
         *
         * @param right - another error manager.
         */
        ErrorManager& operator=(const ErrorManager& right);

        /**
         * @brief Move operator.
         * Moves error map.
         *
         * @param right - another error manager.
         */
        ErrorManager& operator=(ErrorManager&& right) noexcept;

        /**
         * @brief Launches a function that will be monitored for errors.
         * If an error is caused, the error text will be placed in the message, otherwise
         * the error text with id = 0 will be placed in the message.
         * WARNING! The function must be the first parameter of ErrorManager!
         *
         * @tparam Func - function.
         * @tparam Args - function params.
         *
         * @param message - error text.
         * @param func - a function that will be called and checked for errors.
         * @param args - function parameters.
         *
         * @return std::uint64_t - error code.
         */
        template <class Func, class... Args>
        std::uint64_t start(std::string& message, Func func, Args... args);

        /**
         * @brief Causes an error.
         *
         * @param id - id of the error being caused.
         * @param message - addendum to the error text.
         */
        void callError(std::uint64_t id, const std::string& message);

        /**
         * @brief Adds an error with the text.
         *
         * @param message_error - error text.
         */
        void addError(const std::string& message_error);

        /**
         * @brief Adds an error with the id and the text.
         *
         * @param id - error id
         * @param message_error - error text.
         */
        void addError(std::size_t id, const std::string& message_error);
    };

    template <class Func, class... Args>
    inline std::uint64_t ErrorManager::start(std::string& message, Func func,
                                             Args... args) {
        try {
            func(*this, args...);
            message = _errors.find(0)->second;
        } catch (const std::exception& ex) {
            message = ex.what();
        }
        return _last_error_id;
    }
}  // namespace error
