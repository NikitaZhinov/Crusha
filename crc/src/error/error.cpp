#include "../../include/error/error.h"

#include <iostream>

namespace crc {
    Error::TypeError Error::TYPE_ERROR = None;
    std::string Error::TEXT_ERROR;
    std::wstring Error::W_TEXT_ERROR;

    void Error::setTypeError(TypeError error) {
        TYPE_ERROR = error;
    }

    void Error::setTextError(const std::string &text) {
        TEXT_ERROR = text;
    }

    void Error::setTextError(const std::wstring &text) {
        W_TEXT_ERROR = text;
    }

    void Error::setWTextError(const std::wstring &w_text) {
        W_TEXT_ERROR = w_text;
    }

    void Error::setError(TypeError error, const std::string &text) {
        setTypeError(error);
        setTextError(text);
    }

    void Error::setError(TypeError error, const std::wstring &text) {
        setTypeError(error);
        setTextError(text);
    }

    Error::TypeError Error::getTypeError() {
        return TYPE_ERROR;
    }

    std::string Error::getTextError() {
        return TEXT_ERROR;
    }

    std::wstring Error::getWTextError() {
        return W_TEXT_ERROR;
    }

    void Error::printError() {
        if (TEXT_ERROR.empty()) {
            std::wcout << W_TEXT_ERROR << std::endl;
        } else {
            std::cout << TEXT_ERROR << std::endl;
        }
    }
}  // namespace crc
