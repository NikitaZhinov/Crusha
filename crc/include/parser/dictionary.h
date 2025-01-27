#pragma once

#include "../lexer/lexer.h"

#include <string>
#include <set>

namespace crc {
    class Dictionary {
    public:
        enum TypeId {
            Void = 0,
            Int,
            UInt,
            Float,
            UFloat,
            Char,
        };

        struct Type {
            std::wstring name;
            TypeId id = Void;

            friend bool operator<(const Type& t, const std::wstring& name);
            friend bool operator<(const std::wstring& name, const Type& t);
            friend bool operator<(const Type& a, const Type& b);
        };

        struct Operator {
            std::wstring name;
            std::size_t priority = 0;
            bool is_bracket = false;
            bool is_unary = false;
            bool is_prefix = false;

            friend bool operator<(const Operator& op, const std::wstring& name);
            friend bool operator<(const std::wstring& name, const Operator& op);
            friend bool operator<(const Operator& a, const Operator& b);
        };

    private:
        static const std::set<Type, std::less<>> _TYPES;
        static const std::set<Operator, std::less<>> _OPERATORS;

    public:
        static std::set<Type, std::less<>> getTypes();
        static std::set<Operator, std::less<>> getOperators();

        static bool isType(const Lexer::token_t& token);
        static bool isOperator(const Lexer::token_t& token);

        static TypeId getTypeId(const Lexer::token_t& token);
        static std::size_t getOperatorPriority(const Lexer::token_t& token, const Lexer::token_t& prev_token);

        static bool isNameExist(const Lexer::token_t& token);
    };
}  // namespace crc
