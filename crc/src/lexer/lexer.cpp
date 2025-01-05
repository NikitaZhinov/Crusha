#include "../../include/lexer/lexer.h"

#include <print>

namespace crc {
    const std::wstring Lexer::INDEPENDENT_SYMBOLS = L"&?;$#@^:\"'|.,(){}[]";
    const std::wstring Lexer::SPECIAL_ALPHABET = L"<>!=+-*/";
    const std::wstring Lexer::SEPARATORS = L" \t\n";

    void Lexer::_pushToken(token_t &token, token_line_t &token_line) {
        if (!token.empty()) {
            token_line.second.push_back(std::move(token));
        }
    }

    void Lexer::_pushText(wchar_t &c, token_t &token, token_line_t &token_line) {
        wchar_t start_quotation = c;
        wchar_t prev_c = c;
        while (!_file.eof()) {
            c = _file.get();
            if (prev_c != L'\\' && c == start_quotation) {
                token.push_back(c);
                break;
            }
            token.push_back(c);
            prev_c = c;
        }
    }

    void Lexer::_addIndependentSymbol(wchar_t &c, token_t &token, token_line_t &token_line) {
        if (!token.empty()) {
            _pushToken(token, token_line);
        }
        token.push_back(c);
        if (c == L'"' || c == L'\'') {
            _pushText(c, token, token_line);
        }
        _pushToken(token, token_line);
    }

    void Lexer::_addSpecialAlphabet(const wchar_t &c, token_t &token, token_line_t &token_line) {
        if (!token.empty() && SPECIAL_ALPHABET.find(token.back()) == std::wstring::npos) {
            _pushToken(token, token_line);
        }
        token.push_back(c);
    }

    void Lexer::_separator(const wchar_t &c, token_t &token, token_line_t &token_line) {
        if (c == L'\n') {
            _nextLine(token, token_line);
        } else if (!token.empty()) {
            _pushToken(token, token_line);
        }
    }

    void Lexer::_nextLine(token_t &token, token_line_t &token_line) {
        _pushToken(token, token_line);
        _token_list.push_back(std::move(token_line));
    }

    void Lexer::_read_file() {
        wchar_t c = 0;
        token_t token;
        token_line_t token_line;

        if (_file.is_open()) {
            while (!_file.eof()) {
                c = _file.get();
                token_line.first.push_back(c);
                if (INDEPENDENT_SYMBOLS.find(c) != std::wstring::npos) {
                    _addIndependentSymbol(c, token, token_line);
                } else if (SPECIAL_ALPHABET.find(c) != std::wstring::npos) {
                    _addSpecialAlphabet(c, token, token_line);
                } else if (SEPARATORS.find(c) != std::wstring::npos) {
                    _separator(c, token, token_line);
                } else {
                    token.push_back(c);
                }
            }

            _nextLine(token, token_line);
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

    Lexer::token_list_t Lexer::getTokenList() const {
        return _token_list;
    }

    void Lexer::moveTokenList(token_list_t &token_list) {
        token_list = std::move(_token_list);
    }
}  // namespace crc
