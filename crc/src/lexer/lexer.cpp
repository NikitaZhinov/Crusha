#include "../../include/lexer/lexer.h"

#include <print>

namespace crc {
    const std::wstring Lexer::INDEPENDENT_SYMBOLS = L"&?;$#@^:\"'|.,(){}[]";
    const std::wstring Lexer::SPECIAL_ALPHABET = L"<>!=+-*/";
    const std::wstring Lexer::SEPARATORS = L" \t\n";

    void Lexer::_addIndependentSymbol(const wchar_t &c, token_t &token, token_line_t &token_line) {
        if (!token.empty()) {
            token_line.push_back(std::move(token));
        }
        token.push_back(c);
        token_line.push_back(std::move(token));
    }

    void Lexer::_addSpecialAlphabet(const wchar_t &c, token_t &token, token_line_t &token_line) {
        if (!token.empty() && SPECIAL_ALPHABET.find(token.back()) == std::wstring::npos) {
            token_line.push_back(std::move(token));
        }
        token.push_back(c);
    }

    void Lexer::_separator(const wchar_t &c, std::wstring &line, token_t &token, token_line_t &token_line) {
        if (c == L'\n') {
            _nextLine(line, token, token_line);
        } else if (!token.empty()) {
            token_line.push_back(std::move(token));
        }
    }

    void Lexer::_nextLine(std::wstring &line, token_t &token, token_line_t &token_line) {
        token_line.push_back(std::move(token));
        _token_list.push_back(std::pair<std::wstring, token_line_t>(std::move(line), std::move(token_line)));
    }

    void Lexer::_read_file() {
        wchar_t c = 0;
        token_t token;
        token_line_t token_line;
        std::wstring line;

        if (_file.is_open()) {
            while (!_file.eof()) {
                c = _file.get();
                line.push_back(c);
                if (INDEPENDENT_SYMBOLS.find(c) != std::wstring::npos) {
                    _addIndependentSymbol(c, token, token_line);
                } else if (SPECIAL_ALPHABET.find(c) != std::wstring::npos) {
                    _addSpecialAlphabet(c, token, token_line);
                } else if (SEPARATORS.find(c) != std::wstring::npos) {
                    _separator(c, line, token, token_line);
                } else {
                    token.push_back(c);
                }
            }

            _nextLine(line, token, token_line);
            _file.close();
        } else {
            throw std::runtime_error("File is not found!");
        }
    }

    Lexer::Lexer(const std::string &file_name) : _file(file_name) {
        try {
            _read_file();
        } catch (const std::runtime_error &err) {
            std::println("File {} is not found!", file_name);
        }
    }

    std::wstring Lexer::getIndependentSymbols() {
        return INDEPENDENT_SYMBOLS;
    }

    std::wstring Lexer::getSpecialAlphabet() {
        return SPECIAL_ALPHABET;
    }

    std::wstring Lexer::getSeparators() {
        return SEPARATORS;
    }

    Lexer::token_file_t Lexer::getTokenList() const {
        return _token_list;
    }
}  // namespace crc
