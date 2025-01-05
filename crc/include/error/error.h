#pragma once

#include <string>

namespace crc {
    class Error {
    public:
        enum TypeError {
            None = 0,  // There are no errors
            UndefineOption,
            Sytax,
        };

    private:
        static TypeError TYPE_ERROR;
        static std::string TEXT_ERROR;
        static std::wstring W_TEXT_ERROR;

    public:
        static void setTypeError(TypeError error);
        static void setTextError(const std::string &text);
        static void setTextError(const std::wstring &text);
        static void setWTextError(const std::wstring &w_text);
        static void setError(TypeError error, const std::string &text);
        static void setError(TypeError error, const std::wstring &text);

        static TypeError getTypeError();
        static std::string getTextError();
        static std::wstring getWTextError();

        static void printError();
    };
}  // namespace crc
