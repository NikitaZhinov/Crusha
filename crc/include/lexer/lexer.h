#pragma once

#include <fstream>
#include <list>
#include <string>
#include <vector>

namespace crc {
    class Lexer {
    public:
        using token_t = std::wstring;
        using token_line_t = std::pair<std::wstring, std::vector<token_t>>;
        using token_list_t = std::list<token_line_t>;

    private:
        static const std::wstring INDEPENDENT_SYMBOLS;
        static const std::wstring SPECIAL_ALPHABET;
        static const std::wstring SEPARATORS;

        std::wifstream _file;
        token_list_t _token_list;

        void _pushToken(token_t &token, token_line_t &token_line);
        void _pushText(wchar_t &c, token_t &token, token_line_t &token_line);
        void _addIndependentSymbol(wchar_t &c, token_t &token, token_line_t &token_line);
        void _addSpecialAlphabet(const wchar_t &c, token_t &token, token_line_t &token_line);
        void _separator(const wchar_t &c, token_t &token, token_line_t &token_line);
        void _nextLine(token_t &token, token_line_t &token_line);
        void _read_file();

    public:
        Lexer() = default;
        Lexer(const std::string &file_name);

        static std::wstring getIndependentSymbols();
        static std::wstring getSpecialAlphabet();
        static std::wstring getSeparators();

        token_list_t getTokenList() const;

    protected:
        void moveTokenList(token_list_t &token_list);
    };
}  // namespace crc
