#include "../../include/token/token.h"

#include "../../include/parser/dictionary.h"

#include <cwctype>

static bool __isNumber__(const std::wstring& name) {
    auto it = name.begin();
    while (it != name.end() && std::iswdigit(*it)) {
        ++it;
    }
    return !name.empty() && it == name.end();
}

namespace crc {
    void Token::_defineType() {
        if (Dictionary::isOperator(_name)) {
            _type = Operator;
        } else if (Dictionary::isType(_name)) {
            _type = Type;
        } else if (_name == L"(") {
            _type = RoundBracketOpen;
        } else if (_name == L")") {
            _type = RoundBracketOpen;
        } else if (_name == L"[") {
            _type = SquareBracketOpen;
        } else if (_name == L"]") {
            _type = SquareBracketClose;
        } else if (_name == L"{") {
            _type = CurlyBracketOpen;
        } else if (_name == L"}") {
            _type = CurlyBracketClose;
        } else if (_name == L"var") {
            _type = Var;
        } else if (_name == L"func") {
            _type = Func;
        } else if (_name.at(0) == '"' || _name.at(0) == '\'') {
            _type = Text;
        } else if (__isNumber__(_name)) {
            _type = Int;
        } else if (_name == L";") {
            _type = End;
        } else {
            _type = Name;
        }
    }

    Token::Token(const std::wstring& name) : _name(name) {
        _defineType();
    }

    void Token::setName(const std::wstring& name) {
        _name = name;
        _defineType();
    }

    void Token::setType(TokenType type) {
        _type = type;
    }

    Token::TokenType Token::getType() {
        return _type;
    }

    std::wstring Token::getName() {
        return _name;
    }
}  // namespace crc
