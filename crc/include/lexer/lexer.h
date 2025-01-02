#pragma once

#include <fstream>
#include <list>
#include <string>
#include <vector>

namespace crc {
    class Lexer {
    public:
        using token_t = std::wstring;
        using token_line_t = std::vector<token_t>;
        using token_file_t = std::list<std::pair<std::wstring, token_line_t>>;

    private:
        static const std::wstring INDEPENDENT_SYMBOLS;
        static const std::wstring SPECIAL_ALPHABET;
        static const std::wstring SEPARATORS;

        std::wifstream _file;
        token_file_t _token_list;

        void _addIndependentSymbol(const wchar_t &c, token_t &token, token_line_t &token_line);
        void _addSpecialAlphabet(const wchar_t &c, token_t &token, token_line_t &token_line);
        void _separator(const wchar_t &c, std::wstring &line, token_t &token, token_line_t &token_line);
        void _nextLine(std::wstring &line, token_t &token, token_line_t &token_line);
        void _read_file();

    public:
        Lexer() = default;
        Lexer(const std::string &file_name);

        static std::wstring getIndependentSymbols();
        static std::wstring getSpecialAlphabet();
        static std::wstring getSeparators();

        token_file_t getTokenList() const;
    };
}  // namespace crc
