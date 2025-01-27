#include "../../include/parser/dictionary.h"

namespace crc {
    bool operator<(const Dictionary::Type& t, const std::wstring& name) {
        return t.name < name;
    }

    bool operator<(const std::wstring& name, const Dictionary::Type& t) {
        return name < t.name;
    }

    bool operator<(const Dictionary::Type& a, const Dictionary::Type& b) {
        return a.name < b.name;
    }

    bool operator<(const Dictionary::Operator& op, const std::wstring& name) {
        return op.name < name;
    }

    bool operator<(const std::wstring& name, const Dictionary::Operator& op) {
        return name < op.name;
    }

    bool operator<(const Dictionary::Operator& a, const Dictionary::Operator& b) {
        if (a.name == b.name) {
            return a.priority < b.priority;
        }
        return a.name < b.name;
    }

    const std::set<Dictionary::Type, std::less<>> Dictionary::_TYPES = {
        {    L"int",    Int },
        {   L"uint",   UInt },
        {  L"float",  Float },
        { L"ufloat", UFloat },
        {   L"char",   Char }
    };

    const std::set<Dictionary::Operator, std::less<>> Dictionary::_OPERATORS = {
        {    L"var", 0, false,  true,  true },
        {   L"func", 0, false,  true,  true },

        {      L":", 1, false,  true,  true },
        {     L"++", 1, false,  true, false },
        {     L"--", 1, false,  true, false },
        // {  L"()", 1,  true, false, false },
        // {  L"[]", 1,  true, false, false },
        // {  L"{}", 1,  true, false, false },
        {      L".", 1, false, false, false },
        // {  L"->", 1, false, false, false },

        {     L"++", 2, false,  true,  true },
        {     L"--", 2, false,  true,  true },
        {     L"0+", 2, false,  true,  true },
        {     L"0-", 2, false,  true,  true },
        {      L"!", 2, false,  true,  true },

        {      L"*", 3, false, false, false },
        {      L"/", 3, false, false, false },
        {      L"%", 3, false, false, false },

        {      L"+", 4, false, false, false },
        {      L"-", 4, false, false, false },

        {      L"<", 5, false, false, false },
        {      L">", 5, false, false, false },
        {     L"<=", 5, false, false, false },
        {     L">=", 5, false, false, false },

        {     L"==", 6, false, false, false },
        {     L"!=", 6, false, false, false },

        {    L"and", 7, false, false, false },
        {     L"or", 7, false, false, false },

        {      L"=", 8, false, false, false },
        {     L"+=", 8, false, false, false },
        {     L"-=", 8, false, false, false },
        {     L"*=", 8, false, false, false },
        {     L"/=", 8, false, false, false },
        {     L"%=", 8, false, false, false },

        { L"return", 9, false,  true,  true },

        // {      L",", 10, false, false, false },
    };

    std::set<Dictionary::Type, std::less<>> Dictionary::getTypes() {
        return _TYPES;
    }

    std::set<Dictionary::Operator, std::less<>> Dictionary::getOperators() {
        return _OPERATORS;
    }

    bool Dictionary::isType(const Lexer::token_t& token) {
        return _TYPES.find(token) != _TYPES.end();
    }

    bool Dictionary::isOperator(const Lexer::token_t& token) {
        return _OPERATORS.find(token) != _OPERATORS.end();
    }

    Dictionary::TypeId Dictionary::getTypeId(const Lexer::token_t& token) {
        return _TYPES.find(token)->id;
    }

    std::size_t Dictionary::getOperatorPriority(const Lexer::token_t& token, const Lexer::token_t& prev_token) {
        if (prev_token.empty()) {
            return _OPERATORS.find(token)->priority;
        }
        if ((token == L"-" || token == L"+") && Dictionary::isOperator(prev_token)) {}
    }

    bool Dictionary::isNameExist(const Lexer::token_t& token) {
        return isType(token) || isOperator(token);
    }
}  // namespace crc
